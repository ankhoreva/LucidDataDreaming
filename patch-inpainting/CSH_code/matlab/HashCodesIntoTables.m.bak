function [hTables_A,hTables_B,indices_A,indices_B,indices_B_flat,indices_B_offset] = ...
    HashCodesIntoTables(hA,wA,hB,wB,maxBits,bitCountPerTable,tableInd,numHashs,...
    code_A,code_B,hTables_A,hTables_B,insideInfo)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
hashMethod = 1; % 1 or 4 are the best
hashFact = 32;

if (bitCountPerTable(tableInd) >  maxBits)
    NeedToHash = true;
else NeedToHash = false;
end

% tic;
hashBits = min(maxBits, log2(hashFact) * bitCountPerTable(tableInd));
codeBits = bitCountPerTable(tableInd);
debugDisp(insideInfo,['-------- table ' num2str(tableInd) ' --------']);
debugShow(insideInfo, '[codeBits hashBits]',[codeBits hashBits]);
% TRICK (1) (the use of 'hB+2' is for not pointing to first or last column)
% new randomized initialization - further rounds get the previous initialization
if (tableInd == 1)
    hTables_A = randi([hA+2,hA*(wA-1)],2^hashBits,numHashs,'uint32');
    hTables_B = randi([hB+2,hB*(wB-1)],2^hashBits,numHashs,'uint32');
end

TestTableFillAmount = 0;
if (TestTableFillAmount)
    TestTableFillValue = 10000;
    hTables_A = TestTableFillValue * ones(2^hashBits,numHashs,'uint32');
    hTables_B = TestTableFillValue * ones(2^hashBits,numHashs,'uint32');
end

if (strcmp(class(code_A),'uint64'))
    if (NeedToHash)
        code_A = hash64(code_A,hashMethod,hashBits);
        code_B = hash64(code_B,hashMethod,hashBits);
    end
end

if (NeedToHash)
    indices_A = hash(code_A,hashMethod,hashBits)+1; % hashing is here! (of A codes) - MEX
else
    indices_A = code_A + 1;
end
% toc2 = toc
% tic
indices_A_flat = indices_A(:) ; % I keep index 1 for non-initialization
indices_A_offset = hA;
indices_A_flat = [ ones(hA,1) ; indices_A_flat ; ones(hA,1)];
% toc3 = toc
% tic
% TRICKS - (for coping with boundaries during propagation)
% explanation: the problem is that when we somehow point to a pixel in image B, we automatically
% (in propagation) move to the t/b/l/r neighbors. These neighbors must not be out of bounds.
% The solution is to limit the ways to get to image B, such that we will never fall in the 1-pixel
% bondary of the image (Actually we only care about the first and last hB pixels because of the way
% the data is sorted in memory).
% The 2 ways we point to image B are:
% 1) Through 'hTables_B' - we don't let it point to first/last column (see TRICK (1) and TRICK (3) )
% 2) Through 'bestMappingNewA' - I don't want to bound it constantly with min/max so I do it
%      indirectly, meaning that I allow it to be anything, but then, before going back to the hash
%      function, I make the function  'indices_B_flat'  padded from both sides in order to deal with
%      the bad pointer (see TRICK (2))

if (NeedToHash)
    indices_B = hash(code_B,hashMethod,hashBits)+ 1; % hashing is here! (of B codes) - MEX
else
    indices_B = code_B + 1;
end
% tic4 = toc

% tic
indices_B_flat = indices_B(:) ; % I keep index 1 for non-initialization
% TRICK (2) - we pad by a column of ones ('ones(hB,1)') from both start and end, to avoid doing ifs in propagation.
% Therefore we will access it using the offset indices_B_offset = hB;
indices_B_offset = hB;
indices_B_flat = [ ones(hB,1) ; indices_B_flat ; ones(hB,1)];

if (insideInfo)
    codesNum = size(unique(code_B(:)),1);
    totalSize = size(code_B(:),1); pixelsToCode = totalSize/codesNum;
    debugShow(insideInfo, '[codesNum,totalSize,pixelsToCode]',[codesNum,totalSize,pixelsToCode]);
    hashCodesNum = size(unique(indices_B_flat),1);
    debugDisp(insideInfo,['Clashing (of hash): ' num2str(codesNum) ' codeNums turned into ' num2str(hashCodesNum)...
        ' hashCodeNums, which is ' num2str(100*(codesNum-hashCodesNum)/codesNum) ' %']);
end
% toc5 = toc % 45% of all -
% tic
% 1) c-code style:
% types: hTables_B is uint32
% hTables_C = hTables_B;
% tic
% for j = 1 : 100
% MexFillArray(hTables_B,indices_B_flat,uint16(hashBits),uint16(hB),uint16(wB),uint16(indices_B_offset));
% end
% mextoc = toc
% keyboard
% tic
useC =1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (useC) % (these are MEX functions)
    MexFillTable(hTables_A,indices_A_flat,uint16(hashBits), uint16(hA),uint16(wA),uint16(indices_A_offset)); % designed for numHashs=2;
    MexFillTable(hTables_B,indices_B_flat,uint16(hashBits), uint16(hB),uint16(wB),uint16(indices_B_offset)); % designed for numHashs=2;
else
    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    hashPtrs = ones(2^hashBits,1);
    for i = hB + 1  : hB*wB - hB % TRICK (3) (we don't allow hTables_B to point to first or last column)
        entry = indices_B_flat(indices_B_offset + i);
        hTables_B(entry,hashPtrs(entry)) = i;
        hashPtrs(entry) = min(hashPtrs(entry) + 1 ,numHashs);
    end
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    hashPtrs = ones(2^hashBits,1);
    for i = hA + 1  : hA*wA - hA % TRICK (3) (we don't allow hTables_B to point to first or last column)
        entry = indices_A_flat(indices_A_offset + i);
        hTables_A(entry,hashPtrs(entry)) = i;
        hashPtrs(entry) = 1;
    end
end

% How many of the table is filled
if (TestTableFillAmount)
    u = find (hTables_A ~= TestTableFillValue);
    FillPercent = (100*length(u))/((2^hashBits)*numHashs);
    NumCells = length(u);
    disp([num2str(FillPercent) '% of table A (' num2str(NumCells) ' cells) is filled with codes']);
    u = find (hTables_B ~= TestTableFillValue);
    FillPercent = (100*length(u))/((2^hashBits)*numHashs);
    NumCells = length(u);
    disp([num2str(FillPercent) '% of table B (' num2str(NumCells) ' cells) is filled with codes']);
end
% 2) matlab style: (for only one alternative!) - NOT UP TO DATE (DONT USE THIS!)
%           hTables_B(indices_B_flat) = (1:hB*wB)'; % currently one B representative per table entry
% toc6 = toc % 55% of all
%%%%%%%%%%%%%%%%%%%%%%%%%%%
