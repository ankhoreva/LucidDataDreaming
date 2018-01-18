function [CSH_ann,CSH_bnn,numUniqueResultsPerPixel,sortedErrors] = ...
    HashingSchemeNewKNN_LargeK(A,B,k,calcBnn,HashingSchemeParams,bMask,patch_mode)
% This is a new, accelerated KNN version, meant for large values of k (over ~15)
% Unlike the original version, it does not guarantee to return k distince NN for each patch

HashingSchemeParams.KNN_enrichment_mode = 0; % don't use this for this fast version (since it slows down a lot)

CSH_bnn = [];
[hA,wA,dA] = size(A);
[hB,wB,dB] = size(B);

% 1] sqrt NN computation
width = HashingSchemeParams.width;

k_ToUse = ceil(sqrt(3)*sqrt(k));
k_ToUse_square = k_ToUse^2;

if isequal(A,B)
    
    CSH_ann_sqrt_A2A = HashingSchemeNew(A,A,k_ToUse,calcBnn,HashingSchemeParams,'none', bMask,patch_mode);
    % convert to 'indices' representation
    locInds_A2A = sub2ind([hA,wA],squeeze(CSH_ann_sqrt_A2A(:,:,2,:)),squeeze(CSH_ann_sqrt_A2A(:,:,1,:)));
    
    % 2] combine the k_ToUse^2 transitively expanded results
    overSafeResults = TransitiveKNN_part_1_A2A(A,locInds_A2A,k_ToUse);
    
else
    % A => A
    CSH_ann_sqrt_A2A = HashingSchemeNew(A,A,k_ToUse,calcBnn,HashingSchemeParams,'none', bMask,patch_mode);
    % convert to 'indices' representation
    locInds_A2A = sub2ind([hB,wB],squeeze(CSH_ann_sqrt_A2A(:,:,2,:)),squeeze(CSH_ann_sqrt_A2A(:,:,1,:)));

    % A => B
    CSH_ann_sqrt_A2B = HashingSchemeNew(A,B,k_ToUse,calcBnn,HashingSchemeParams,'none', bMask,patch_mode);
    % convert to 'indices' representation
    locInds_A2B = sub2ind([hB,wB],squeeze(CSH_ann_sqrt_A2B(:,:,2,:)),squeeze(CSH_ann_sqrt_A2B(:,:,1,:)));

    % 2] combine the k_ToUse^2 transitively expanded results
    overSafeResults = TransitiveKNN_part_1_A2B(A,locInds_A2A,locInds_A2B,k_ToUse);
end

% 3] compute errors of k_ToUse_square options
errorMat = zeros(hA,wA,k_ToUse_square);
for i = 1 : k_ToUse_square
%     fprintf('error calculation (%d out of %d)\n',i,k_ToUse_square);
    errorMat(:,:,i) = ... % Mapping error calculation
        GetErrorMeanAndImage(overSafeResults(:,:,i),hB,wB,hA,wA,width,A,B,width);
end

% 4] Sort errors and take (upd to) k unique best ones
[CSH_ann,numUniqueResultsPerPixel,sortedErrors] = TransitiveKNN_part2_mex(A,B,k,width,overSafeResults,errorMat);
% [CSH_ann,numUniqueResultsPerPixel] = TransitiveKNN_part2(A,B,k,width,overSafeResults,errorMat);


if 0
    figure; imagesc(numUniqueResultsPerPixel); colorbar;
    hist2(numUniqueResultsPerPixel,100)
    imagesc2(numUniqueResultsPerPixel<k)
    mSortedErrors = mean(sortedErrors(1:end-(width-1),1:end-(width-1),:),3);
    figure; imagesc(mSortedErrors); title(['mean Errors, with mean of: ' num2str(mean2(mSortedErrors))]);
end
