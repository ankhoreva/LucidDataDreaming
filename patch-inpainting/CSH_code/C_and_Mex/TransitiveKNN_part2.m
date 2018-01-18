function [CSH_ann,numUniqueResultsPerPixel,sortedErrors] = TransitiveKNN_part2(A,B,k,width,overSafeResults,errorMat)

[hA,wA,dA] = size(A);
[hB,wB,dB] = size(B);

% sort by errors and then take the k mappings of the k smallest [unique!] errors
br_boundary_to_ignore = width-1;
numUniqueResultsPerPixel = zeros(hA-br_boundary_to_ignore,wA-br_boundary_to_ignore);
CSH_ann = zeros(k,hA,wA,2);
sortedErrors = zeros(hA,wA,k);
% CSH_errors = zeros(hA,wA,k);
for i = 1 : hA-br_boundary_to_ignore
    for j = 1 : wA-br_boundary_to_ignore
        [sErrors,sInds] = sort(squeeze(errorMat(i,j,:)));
        OSR = squeeze(overSafeResults(i,j,:));
        sOSR = OSR(sInds);
        uOSRinds = find(diff(sOSR)~=0); % giving up (possibly) on the last index (diff gives a 1-shorter vector)
        kActual = length(uOSRinds);
        uOSRFinalinds = zeros(k,1);
        numUniqueResultsPerPixel(i,j) = min(k,kActual);
        if kActual >= k
            uOSRFinalinds = uOSRinds(1:k);
        else
            uOSRFinalinds(1:kActual) = uOSRinds;
            uOSRFinalinds(kActual+1:k) = uOSRinds(end); % returning duplicate copies in this case
        end
        % NN results:
        [CSH_ann(:,i,j,2),CSH_ann(:,i,j,1)] = ind2sub([hB,wB],sOSR(uOSRFinalinds));
        % sorted errors:
        sortedErrors(i,j,:) = sErrors(uOSRFinalinds);
    end
end

CSH_ann = permute(CSH_ann,[2,3,4,1]);
