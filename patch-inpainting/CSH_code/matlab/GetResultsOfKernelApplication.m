function [CFIs_A,CFIs_B,nSequencyOrder16u,nSequencyLevels16u , WHK_with_Cb_Cr] = ...
    GetResultsOfKernelApplication(A,B,TLboundary,BRboundary,width,classType,maxKernels,hA,wA,dA,hB,wB )
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% the last 4 parameters are relevant to 'patch' mode, which means that A and B contain flattened
% patches, i.e. they are of the size: % size(A) = [width^2,hA*wA,dA]
% IMPORTANT: note that in this case, we will add at the bottom and right zero padding of (width-1)

if (exist('hA'))
    patch_mode = 1;
else
    patch_mode = 0;
end
% t0 = 0;
% t1 = 0; t2 = 0; t3 = 0; t4 = 0; t5 = 0;
% 
% i0 = tic;
if (~patch_mode)
    %% A] Padding
    % pre padding of '2*width' is for the fast and correct initialization of the first 'width' rows/cols
    preA = padarray(A,[TLboundary,TLboundary],0,'pre');
    preB = padarray(B,[TLboundary,TLboundary],0,'pre');
    
    % sizes
    [pad_hA,pad_wA,dA] = size(preA);
    [pad_hB,pad_wB,dB] = size(preB);
else
    shrink_hA = hA - width + 1; % hA includes a BR boundary of size (width-1)
    shrink_wA = wA - width + 1;
    shrink_hB = hB - width + 1;
    shrink_wB = wB - width + 1;
end

ChannelColors = dA; % Tells if this is Y/Cb/Cr or Y only image
%% B] Traverse order and filter specifications
% obtaining GCKs traverse data
[GCKs2D,snakeOrder,deltas1D,alphaDirs1D] = GetGCKTraverseParams(width);


% Define the sequnece in which the kernels are used for candidate check
switch(width)
    case 2
        % 6 kernels ussage
        nSequencyOrder16u   = uint16([1,2,3,4,6,5])';
        nSequencyLevels16u  = uint16([1 3])'; % GUY: Not used for now
        filters = [1,2,3,4,7,10];
         % this is in ordered form:
         filtersY = intersect(filters,1:3:10);
        % the Y-FILTER INDEX from which we come FOR THE COMPUTATION
        procFilterIndToUse =  [0 1 4 5];
        % the SNAKE INDEX from which we come FOR THE COMPUTATION
        procSnakeIndToUse =  [0 1 2 3];
        LastCbCrFilterIndex = 3;

case 4
        %17 kernels version
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        nSequencyOrder16u   = uint16([1,4,10,2,3,13,17,7,16,14,15,5,11,6,12,8,9])';
        nSequencyLevels16u  = uint16([1 3  5 ])'; % GUY: Not used for now
        filters = [1,2,3,4,5,6,7,8,9,10,11,12,13,16,19,22,25];
         % this is in ordered form:
        filtersY = intersect(filters,1:3:25);
        % the Y-FILTER INDEX from which we come FOR THE COMPUTATION
        procFilterIndToUse =  [0 1 4 7 10 13 14 15 16];
        % the SNAKE INDEX from which we come FOR THE COMPUTATION
        procSnakeIndToUse =  [0 1 2 3 4 5 6 7 8];
        LastCbCrFilterIndex = 12;
%         
% 
    case 8
        nSequencyOrder16u   = uint16([1,  4,10,  2,3,  13,17,  7,18,21,16,14,15,5,6,11,12, 8,9,22,23,19,20])';
        nSequencyLevels16u  = uint16([1 3  5  7  17  23])';
        % these are all the filters we will use in the algorithm
        filters = sort([1,4,10,  2,3,13,25,  7,28,46,22,16,19,5,6,11,12,  8,9,49,73,31,43]);
        % this is in ordered form:
        % index:    1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23
        % filters:  1  2  3  4  5  6  7  8  9  10  11  12  13  16  19  22  25  28  31  43  46  49  73
        filtersY = intersect(filters,1:3:80); % [1,4,7,10,13,16,19,22,25,28,31,43,46,49,73]

        % these two length 25 = 5x5 vectors will guide the computation during the snake-order scan. They
        % will tell the computation which cell to use as the previous in the computation.
        % the Y-FILTER INDEX from which we come FOR THE COMPUTATION
        procFilterIndToUse =  [0 1 4 7 10 13 14 15 16 17 18 -1  -1  -1  14  20  21 -1 -1  -1 -1 -1  -1 -1  18];
        % the SNAKE INDEX from which we come FOR THE COMPUTATION
        procSnakeIndToUse =   [0 1 2 3  4  5  6  7  8  9 10 -1  -1  -1   6  15  16 -1 -1  -1 -1 -1  -1 -1  10];
        LastCbCrFilterIndex = 12;
        
    case 16
        % 47 kernels version (out of 147)
         OptFilterSequence = [ 1,2,3,10,4,13,12,11,46,7,25,28,16,22,49,106,109,31,43,19,5,6,76,73,145, 34,40,70,52,103,112,79,67,142,8,9,82,58,64,37,55,100,139,115,85,97,61];

         filters = uint16(sort(OptFilterSequence));
         nFilters = length(filters);
         nSequencyOrder16u = zeros(nFilters,1,'uint16');
         for i = 1 : nFilters
             nSequencyOrder16u(i) = find(OptFilterSequence(i)==filters);
         end
         nSequencyLevels16u  = uint16([1 3  5  7  17  42])';
         % these are all the filters we will use in the algorithm
         filtersY = intersect(filters,1:3:145);

        % these two length 49 = 7*7 vectors will guide the computation during the snake-order scan. 
        % They will tell the computation which cell to use as the previous in the computation.
        % the Y-FILTER INDEX from which we come FOR THE COMPUTATION
        % the SNAKE INDEX from which we come FOR THE COMPUTATION
        procFilterIndToUse =  [0 1 4 7 10 13:36 -1 -1 -1 28 38:43 -1 -1 -1 -1 -1 -1 -1 36 45 46];
        procSnakeIndToUse =   [0 :28 -1 -1 -1 20 33 34 35 36 37 38 -1 -1 -1 -1 -1 -1 -1 28 47 48];

        LastCbCrFilterIndex = 12;    

    case 32
    
    
        % 89 kernels version (out of 243)
         OptFilterSequence =      [1, 3,  2,     4,    10,    25,    13,    28,     7,    46,    22,    16,    76,   145,    73,   106,    49,    31,    43,   109,   148,    19,   190,    70,    40,    79,    34,    52,...
                                                                 5,   142,   103,     6,   112,    37,   151,    67,    11,   55,    82,   241,   187,   100,   193,   139,   115,    64,    58,    85,   238,    12,    97,   154,   136,   184,...
                                                                 118,    61,   196,    88,   157,   235,    94,    91,   133,   181,   121,   130,   199,   124,   232,   127,   160,   178,   163,   175,   202,   8,   229,   166,   172,...
                                                                 205,   226,     9,   208,   223,   169,   211,   220,   214,   217];

         filters = uint16(sort(OptFilterSequence));
         nFilters = length(filters);
         nSequencyOrder16u = zeros(nFilters,1,'uint16');
         for i = 1 : nFilters
             nSequencyOrder16u(i) = find(OptFilterSequence(i)==filters);
         end
         nSequencyLevels16u  = uint16([1 3  5  7  17  42])';
         % these are all the filters we will use in the algorithm
         filtersY = intersect(filters,1:3:243);

        % these two length 49 = 7*7 vectors will guide the computation during the snake-order scan. 
        % They will tell the computation which cell to use as the previous in the computation.
        % the Y-FILTER INDEX from which we come FOR THE COMPUTATION
        % the SNAKE INDEX from which we come FOR THE COMPUTATION
        procFilterIndToUse =  [0 1:3:10 13:88];
        procSnakeIndToUse =   0:80;

        LastCbCrFilterIndex = 12;   

end % switch(width)

WHK_with_Cb_Cr = filters;

if (ChannelColors == 1) % Y only image
    filtersY = double(filtersY);
    procFilterIndToUse(1) = 0;
    for t = 2:length(procFilterIndToUse)
        if (procFilterIndToUse(t)  ~= -1)
            u = find(filtersY == filters(procFilterIndToUse(t)));
            procFilterIndToUse(t) = u;
        end
    end
    % procSnakeIndToUse remains the same
    TempSequency = zeros(1,length(filtersY));
    t = 1;
    for k = 1: length(nSequencyOrder16u)
        filter_to_compare = filters(nSequencyOrder16u(k));
        if (ismember(filter_to_compare , filtersY))
            u = find(filtersY == filter_to_compare);
            TempSequency(t) = u;
            t = t + 1;
        end
    end
    nSequencyOrder16u = uint16(TempSequency)';
    filtersY = ceil(filtersY/3); % Translate to only Y world from the Y/Cb/Cr coordinates
    filters = filtersY;
end    
    



%% C] Allocations
if (~patch_mode)
    currFiltImgs_A = zeros(pad_hA,pad_wA,length(filters),classType);
    currFiltImgs_B = zeros(pad_hB,pad_wB,length(filters),classType);
else
    currFiltImgs_A = zeros(shrink_hA,shrink_wA,length(filters),classType);
    currFiltImgs_B = zeros(shrink_hB,shrink_wB,length(filters),classType);
end    

deltas1D = uint16(deltas1D);

%     t0 = toc(i0);

%% D] Computations
% 1) first kernel (all plus = DC) is done using integral images (in a mex function)
%                 iTime = tic;
if (~patch_mode)
    width = uint16(width);
    currFiltImgs_A(:,:,1:ChannelColors) = GetFirstFilter3ChannelsMexS(preA,width,classType);
    currFiltImgs_B(:,:,1:ChannelColors) = GetFirstFilter3ChannelsMexS(preB,width,classType);
else
%     i1 = tic;

    A = double(A);  B = double(B); 
    wid2 = width*width;

    a = cell(1,3);
    b = cell(1,3);
    
    [~,~,ddA] = size(A);
    
    if (ddA>1) % in case each channel is separate
        a{1} = A(:,:,1);
        a{2} = A(:,:,2);
        a{3} = A(:,:,3);
        b{1} = B(:,:,1);
        b{2} = B(:,:,2);
        b{3} = B(:,:,3);
    else
        a{1} = A(1:wid2,:);
        a{2} = A(wid2+1:2*wid2,:);
        a{3} = A(2*wid2+1:3*wid2,:);
        b{1} = B(1:wid2,:);
        b{2} = B(wid2+1:2*wid2,:);
        b{3} = B(2*wid2+1:3*wid2,:);
    end

    DC_filter = ones(1,wid2);
%     t1 = toc(i1);
%     i2 = tic;
    for i = 1 : ChannelColors
        resA = DC_filter*(a{i});
        resB = DC_filter*(b{i});
        currFiltImgs_A(:,:,i) = reshape(resA,[shrink_wA,shrink_hA])'; % this looks like this because the patches were given in row-major order
        currFiltImgs_B(:,:,i) = reshape(resB,[shrink_wB,shrink_hB])';        
    end

%         t2 = toc(i2);

%     CompareWithImfilter(grayA,filter_j,SnakeImages(:,:,Y,X));
end
%                 totI = totI + toc(iTime);

% 2) rest of kernels - done in a Gray-Code-Kernels fashion. NOTICE: loop follows snake ordering, but
% some of the projections are skipped and therefore, the computation of one projection from a
% previous ISN'T always according to the snake ordering (since the previous might not be ready).
% Instead, the compuations ordering is defined by the arrays 'procFilterIndToUse' and 'procSnakeIndToUse'.
%                 filtTime = tic;

if (ChannelColors == 1) % Y only image
    currFilter = 2;
    for iteration = 1 : maxKernels
        if (iteration < maxKernels)
            snakeInd = 1 + iteration; % the index of the filter that we are going source_to
            if (procFilterIndToUse(snakeInd) == -1)
                continue
            end
            
            if (~patch_mode)
                width = uint16(width);
                source_from = procFilterIndToUse(snakeInd);
                currFiltImgs_A(:,:,currFilter) = ProceedOneSnakeStepFor3ChannelsMexTailored(currFiltImgs_A(:,:,source_from), snakeOrder,deltas1D,...
                    alphaDirs1D,snakeInd,procSnakeIndToUse,pad_hA,pad_wA,width, classType,1);
                currFiltImgs_B(:,:,currFilter) = ProceedOneSnakeStepFor3ChannelsMexTailored(currFiltImgs_B(:,:,source_from),snakeOrder,deltas1D,...
                    alphaDirs1D,snakeInd,procSnakeIndToUse,pad_hB,pad_wB,width, classType,1);
            else
                Y = snakeOrder(1,snakeInd); X = snakeOrder(2,snakeInd);
                filter_j = GCKs2D(:,:,Y,X);
                flat_filter_j = filter_j(:);
                resA = imfilter(A,flat_filter_j);
                resB = imfilter(B,flat_filter_j);
                currFiltImgs_A(:,:,currFilter) = reshape(resA,[shrink_wA,shrink_hA])';
                currFiltImgs_B(:,:,currFilter) = reshape(resB,[shrink_wB,shrink_hB])';
            end
            
            currFilter = currFilter + 1;
        end
    end
else
    currFilter = 4;
    channelInd = 0;
    
     
    for iteration = 1 : maxKernels
        %           show('iteration',iteration);
        channelInd = channelInd + 1; % start with r and change cyclicly
        if (channelInd > 3 && iteration < maxKernels)
            channelInd = 1;
            if (~ismember(iteration,filtersY))
                continue
            end
            yOnly = (iteration > LastCbCrFilterIndex);
            addition = 2*(1-yOnly);
            snakeInd = 1 + floor(iteration/3); % the index of the filter that we are going source_to
            
            if (~patch_mode)
                source_from = procFilterIndToUse(snakeInd); source_to = source_from + addition;
                currFiltImgs_A(:,:,currFilter:currFilter+addition) = ...
                    ProceedOneSnakeStepFor3ChannelsMexTailored(currFiltImgs_A(:,:,source_from:source_to),...
                    snakeOrder,deltas1D,alphaDirs1D,snakeInd,procSnakeIndToUse,pad_hA,pad_wA,width, classType,yOnly);
                currFiltImgs_B(:,:,currFilter:currFilter+addition) = ...
                    ProceedOneSnakeStepFor3ChannelsMexTailored(currFiltImgs_B(:,:,source_from:source_to),...
                    snakeOrder,deltas1D,alphaDirs1D,snakeInd,procSnakeIndToUse,pad_hB,pad_wB,width, classType,yOnly);
%                 figure; imagesc(currFiltImgs_A(:,:,currFilter:currFilter+addition));
            else                
                Y = snakeOrder(1,snakeInd); X = snakeOrder(2,snakeInd);
                filter_j = GCKs2D(:,:,Y,X);
                flat_filter_j = filter_j(:)';
                % 1 or 3 channels
                for filtChan = 1 : 1 + addition
%                 i3 = tic;
                    resA = flat_filter_j*(a{filtChan});
                    resB = flat_filter_j*(b{filtChan});
%                 t3 = t3 + toc(i3);
%                 i4 = tic;
                    currFiltImgs_A(:,:,currFilter - 1 + filtChan) = reshape(resA,[shrink_wA,shrink_hA])';
                    currFiltImgs_B(:,:,currFilter - 1 + filtChan) = reshape(resB,[shrink_wB,shrink_hB])';
%                 t4 = t4 + toc(i4);

%                     figure; imagesc(currFiltImgs_A(:,:,currFilter - 1 + filtChan));
                end

            end
            currFilter = currFilter + 1 + addition;
        end
    end
end

i5 = tic;
% Maxmimum allowed kernel projection value to be is 2^16-1.
% This is because when error is calculated, then kernel projections
% difference is powered by 2.
% Thus the error for maximum difference is ((2^16-1)^2) ~ 2^32 which is max
% int32. So to prevent overflow on next algorithm stages, I devide the
% results by 4
if (width == 32)
    MaxVal = 2^16-1;
    MinVal = - MaxVal;
    currFiltImgs_A = BoundBy((currFiltImgs_A / 4) , MinVal , MaxVal);
    currFiltImgs_B = BoundBy((currFiltImgs_B / 4) , MinVal , MaxVal);
end


%% E] Collection into cell arrays (which aren't contiguous in memory)
CFIs_A = cell(1,length(filters));
CFIs_B = cell(1,length(filters));

if (~patch_mode)
    for iteration = 1 : length(filters)
        CFIs_A{iteration} = currFiltImgs_A(TLboundary+1:end,TLboundary+1:end,iteration);
        CFIs_B{iteration} = currFiltImgs_B(TLboundary+1:end,TLboundary+1:end,iteration);
    end
else
    for iteration = 1 : length(filters) % we pad by (width-1) since we create an image from the patches
        CFIs_A{iteration} = padarray(currFiltImgs_A(:,:,iteration),[width-1,width-1],0,'post'); 
        CFIs_B{iteration} = padarray(currFiltImgs_B(:,:,iteration),[width-1,width-1],0,'post');
    end
end
%     t5 = toc(i5);
% 
% 
% t0
% t1
% t2
% t3
% t4
% t5
% 
% sum = t0+t1+t2+t3+t4+t5


% CFIs_A_P = CFIs_A; CFIs_B_P = CFIs_B; 
% save ('CFIS_patches.mat', 'CFIs_A_P', 'CFIs_B_P');
% load ('CFIS_patches.mat', 'CFIs_A_P', 'CFIs_B_P');
% keyboard
% % % Calculate the ratio between kernel energy and patch energy

% Check how many of the patch energy is calculated
% % % % [h w d] = size(A);
% % % % Kernel_Energy = zeros(h,w);
% % % % for iteration = 1 : length(filters)
% % % %     Kernel_Energy = Kernel_Energy  + double(CFIs_A{iteration}).^2;
% % % % end
% % % % 
% % % % Patch_Energy = zeros(h,w);
% % % % for H = 1:h-width
% % % %     for W = 1:w-width
% % % %         Patch_Energy(H,W)  = sum(sum((double(A(H:H+width-1,W:W+width-1)).^2)));
% % % %     end
% % % % end
% % % % NORM_FACTOR = 8*23;
% % % % EnergyRatio = mean2(Kernel_Energy(1:end-width,1:end-width))/(mean2(Patch_Energy)*NORM_FACTOR)
% % % 
% % % CFI_STD_A = zeros(length(filters),1);
% % % CFI_STD_B= zeros(length(filters),1);
% % % for iteration = 1 : length(filters)
% % %     CFI_STD_A(iteration) = std2(CFIs_A{iteration});
% % %     CFI_STD_B(iteration) = std2(CFIs_B{iteration});
% % % end
% % % 
% % %     [a1 b1] = sort(CFI_STD_A,'descend');
% % %     [a2 b2] = sort(CFI_STD_B,'descend');    
% % %     
% % %     keyboard;

