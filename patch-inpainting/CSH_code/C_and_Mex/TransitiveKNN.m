function [CSH_ann,numUniqueResultsPerPixel] = TransitiveKNN(A,B,locInds,k,k_ToUse,width)

[hA,wA,dA] = size(A);
[hB,wB,dB] = size(B);

% transitive colusure of deg 2
k_ToUse_square = k_ToUse^2;
overSafeResults = zeros(hA,wA,k_ToUse_square);
copyInd = 0;
for i = 1 : k_ToUse
    i
    for j = 1 : k_ToUse
        copyInd = copyInd + 1;
        resulti = locInds(:,:,i);
        resultj = locInds(:,:,j);
        result = resulti(resultj);
        overSafeResults(:,:,copyInd) = result;
    end
end
% compute errors
errorMat = zeros(hA,wA,k_ToUse_square);
for i = 1 : k_ToUse_square
    i
    errorMat(:,:,i) = ... % Mapping error calculation
        GetErrorMeanAndImage(overSafeResults(:,:,i),hB,wB,hA,wA,width,A,B,width);
end

% sort and take k best errors ([wrong] assumption: used for speed/simplicity: "exact-same-error" ==> "exact-same-mapping")
% ---> therefore we take the k mappins of the k smallest [unique!] errors)
br_boundary_to_ignore = width-1;
numUniqueResultsPerPixel = zeros(hA-br_boundary_to_ignore,wA-br_boundary_to_ignore);
CSH_ann = zeros(hA,wA,2,k);
CSH_errors = zeros(hA,wA,k);
for i = 1 : hA-br_boundary_to_ignore
    i
    for j = 1 : wA-br_boundary_to_ignore
        [sErrors,sInds] = sort(squeeze(errorMat(i,j,:)));
        OSR = overSafeResults(i,j,:);
        sOSR = OSR(sInds);
        uOSRinds = find(diff(sOSR)~=0); % giving up (possibly) on the last index (diff gives a 1-shorter vector)
        kActual = length(uOSRinds);
        numUniqueResultsPerPixel(i,j) = min(k,kActual);
        if kActual >= k
            uOSRinds = uOSRinds(1:k);
        else
            uOSRinds(kActual+1:k) = uOSRinds(end); % returning duplicate copies in this case
        end
%         CSH_ann_inds(i,j,:) = sOSR(uOSRinds);
        [CSH_ann(i,j,2,:),CSH_ann(i,j,1,:)] = ind2sub([hB,wB],sOSR(uOSRinds));
        CSH_errors(i,j,:) = sErrors(uOSRinds);
    end
end
