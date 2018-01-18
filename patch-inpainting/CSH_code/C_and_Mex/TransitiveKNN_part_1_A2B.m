function overSafeResults = TransitiveKNN_part_1_A2B(A,locInds_A2A,locInds_A2B,k_ToUse)

[hA,wA,dA] = size(A);

% transitive colusure of deg 2
k_ToUse_square = k_ToUse^2;
overSafeResults = zeros(hA,wA,k_ToUse_square);
copyInd = 0;
for i = 1 : k_ToUse
    for j = 1 : k_ToUse
        copyInd = copyInd + 1;
        resulti = locInds_A2B(:,:,i);
        resultj = locInds_A2A(:,:,j);
        result = resulti(resultj);
        overSafeResults(:,:,copyInd) = result;
    end
end

return