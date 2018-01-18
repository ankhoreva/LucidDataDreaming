function [code_A,code_B,... % these are matrices of sizes of A,B holding the calculated code per patch
    bitCountPerTable,...        % denotes how many bits were used to build this code
    numKernelsPerAlternative] = ... % this is for statistics (internal)
    BuildWalshHadamardCodes(tableInd,width,currFiltImgs_A, currFiltImgs_B, ...
                                visualizeFilterDistributions,numTables,hA,wA,hB,wB,insideInfo  , classType , ColorChannels , WHK_with_Cb_Cr)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% A] INITIALIZATIONS
maxFilterRange = 2*256*width*width+1;%always odd
minFilterValue = -floor(maxFilterRange/2);

MIN_BINS = 2;   % the minimal number of bins
YCbCrRatio = 8; % the ratio between number of bins we give to Y vs chroma, for a given WH filter

% 'hand-crafting' the number of bins per filter
% This is done according to distance of the WH filter from the origin (empirical)
% index is the snake order (these "number of bins" are designed for y and we use divide by YCbCrRatio for the color channels
repsTable = 2*ones(4*width-1,1);
repsTable(1) = 32; % (1,1)
repsTable(2) = 8; % (1,2)
repsTable(3) = 2; % (2,2)
repsTable(4) = 8; % (2,1)
% 'hand-crafting' the choice of filters
if (visualizeFilterDistributions)
    filters = 1 : 12;
else
    switch width
        case 2
            filters = [1,2,3,4,6]; 
        case 4
            % these are the WH indices of the 7 kernels we want to work with
            filters = [1,2,3,4,10,13,17]; 
        case 8
            % these are the WH indices of the 8 kernels we want to work with
            % and these are their LOCATIONS in the currFiltImgs_A structure:
            filters = [1,2,3,4,7,10,13,17];%,18,21];%14,16];%    add either ,22,23  or ,14,16  or  ,5,6   or ,11,12
        case 16
            % these are the WH indices of the 8 kernels we want to work with
            filters = [1,2,3,4,7,10,13,17];
        case 32
            % these are the WH indices of the 8 kernels we want to work with
            filters = [1,2,3,4,7,10,13,17];
             
        otherwise
            error(['Patch width ' num2str(width) 'is not supported']);
    end
end

if (ColorChannels == 1) % Gray level images, delete Cb/Cr kernels
	t = 1;
    filters_temp = zeros(1,length(filters));
    for k = 1: length(filters)
        CompareFilter = double(WHK_with_Cb_Cr(filters(k)));
        if (mod(CompareFilter ,3) == 1) % kernel is Y
            filters_temp(t) = ceil(CompareFilter/3);
            t = t + 1;
        end
    end
    filters = filters_temp(1:t-1);
end


maxIterations = max(filters);
numFilters = length(filters);

code_A = zeros(hA,wA,'uint32');
code_B = zeros(hB,wB,'uint32');
channelInd = 0;
nextBit = 1;
numBinsY = repsTable(1);

debugDisp(insideInfo,['>>>>>>>>> Coding table number ' num2str(tableInd)   ' >>>>>>>']);


%% A] BUILDING OF CODES for A and B (iterating through the kernels)
        % at each iteration we append to the code the bin index 
        % of the patch projected on the current WH code
        
% t1=0; t2=0; t3=0; t4=0, t5=0; % these are profiling timers
for iteration = 1 : maxIterations
    % show('iteration',iteration);
    % tic
    channelInd = channelInd + 1; % start with r and change cyclicly
    if (channelInd > 3)
        channelInd = 1;
        % need this to know how many bins to use
        snakeInd = 1 + floor(iteration/3); % the index of the filter that we are going to
        numBinsY = repsTable(snakeInd);
    end
    
    % keep going if this current filter is in the 'filters' list
    if (~ismember(iteration,filters))
        continue
    end
    
    % retrieve current filter applied on A / B
    currFiltImg_A = currFiltImgs_A{iteration};
    currFiltImg_B = currFiltImgs_B{iteration};
    
    if (mod(iteration-1,3) == 0) % current channel is Y channel
        numBins = numBinsY;
    else
        numBins = round(max(MIN_BINS,numBinsY/YCbCrRatio));
    end
    
    % 1) Build bin map with random offset - this is a lookup-table for binning (bin edges).
    %    --------------------------------
    %           This is done by taking a relatively small joint sample of patches from A and B,
    %           and placing bin edges such that the sample distributes evenly into the bins. In
    %           addition, bins are shifted at a random amount (first and last bin won't contain the same amounts)
    %       'binMapForUse' is the lookup table that holds the bin index for each projection value
    %    --------------------------------
    
    % t1 = t1 + toc; % this is nothing
    % tic
    
    % trying to divide into equal portions according to sample percentiles
    % sampleResolution = 21;
    jointSample = [currFiltImg_A(hA+1:21:end-hA) currFiltImg_B(hB+1:13:end-hB)];
    fact = 100/numBins; halfFact = fact/2;
    shift = fact*rand(1) - halfFact; % = fact*(rand[0,1]-0.5) = fact*rand[-0.5,0.5]
    
    % edges is of length numBins+1
    percentiles = BoundBy(shift+(0:fact:100),0,100);
    percentiles(1) = 0; percentiles(end) = 100;
    edges = floor(prctile(double(jointSample),percentiles))-minFilterValue;
    edges(1) = 1; edges(end) = maxFilterRange; % these are the limits (might not appear in sample)
    binMapForUse = zeros(1,maxFilterRange,'uint32'); % c style ranging from 0 to numBins-1 (arbitrary initialization)
    for i = 1 : numBins
        binMapForUse(edges(i):edges(i+1)) = bitshift(i-1,nextBit-1);
    end
    
    % t2= t2 + toc;
    % tic
    
    % 2) Construct the code image
    %    ------------------------
       
    d1 = currFiltImg_A - minFilterValue;
    d2 = currFiltImg_B - minFilterValue;
    
    useC = 1;
    if (useC)
            if (strcmp(classType,'int16'))
                    [bins_A,bins_B] = CalculateImageOfBinIndices_16s(binMapForUse,d1,d2); % MEX function
            else
                    [bins_A,bins_B] = CalculateImageOfBinIndices_32s(binMapForUse,d1,d2); % MEX function
            end
    else
        bins_A = binMapForUse(d1);
        bins_B = binMapForUse(d2); %isequal(bins_C,bins_A) % isequal(bins_D,bins_B)
    end

    % appending the current bin numbers the forming code
    code_A = bitor(code_A, bins_A);
    code_B = bitor(code_B, bins_B);
    
    numBitsForBinning = log2(numBins);
    nextBit = nextBit + numBitsForBinning;
    if (nextBit > 32)
        debugDisp(insideInfo,['current bit is: ' num2str(nextBit) ' - aborting loop']);
        break
    end
    
    %  t5 = t5 + toc;
    
    % 3) visualization
    %    -------------
    if ( visualizeFilterDistributions)
        valsA = currFiltImg_A - minFilterValue;
        valsB = currFiltImg_B - minFilterValue;
        [minVal,maxVal] = bounds([valsA(:);valsB(:)]);
        valsA = valsA((valsA > minVal) & (valsA < maxVal));
        valsB = valsB(valsB > minVal & valsB <maxVal);
        common = double([valsA; valsB]);
        nA = histc(valsA(:),edges);
        nB = histc(valsB(:),edges);
        figure(21);
        subplot(numFilters,numTables,1+(iteration-1)*numTables + (tableInd-1));
        bar([nA(1:end-1),nB(1:end-1)]);% axis off;
        if (tableInd ==1)
            figure(22);
            subplot('Position',[(iteration-1)*1/numFilters 0.1 (1/numFilters)-0.02 0.8]);
            hist(double([valsA(:);valsB(:)]),50); hold;
            for i = 1 : length(edges)-1
                plot([edges(i),edges(i)], [0,100],'-r') ; axis off;
            end
            title(['SD: ' num2str(int32(std(common(:))))]);
        end
    end
    
end                       % end maxIterations on kernels loop

bitCountPerTable = nextBit - 1;
numKernelsPerAlternative = iteration;

