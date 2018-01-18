function [annErrorImage,meanRMS] = GetErrorMeanAndImage(ann,hB,wB,hA,wA,br_boundary_to_ignore,A,B,width, ...
                                        descriptor_mode, patch_mode,A_patch,B_patch,patch_params)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

rowMap = ann(:,:,2);       rowMap = BoundBy(rowMap,1,hB-width + 1); % GUY - correction of last patch including bug
colMap = ann(:,:,1);       colMap = BoundBy(colMap,1,wB-width + 1); % GUY - correction of last patch including bug

% GUY - correction of last patch including bug
if (br_boundary_to_ignore > 0)
    br_boundary_to_ignore = br_boundary_to_ignore - 1;
end


if (~descriptor_mode)
    if (exist('patch_mode') && patch_mode)
        dA_patch = double(A_patch);
        dB_patch = double(B_patch);
        hA = patch_params.hA;
        wA = patch_params.wA;
        dA = patch_params.dA;
        hB = patch_params.hB;
        wB = patch_params.wB;
        dB = patch_params.dB;
        annErrorImage = zeros(hA,wA);
        for i = 1 : hA
            for j = 1 : wA
                indA = (i-1)*wA + j;
                indB = (ann(i,j,2)-1)*wB + ann(i,j,1);
                annErrorImage(i,j) = norm(dA_patch(:,indA)-dB_patch(:,indB));                
            end
        end
        meanRMS = mean2(annErrorImage);
        return;
    else
        if (ndims(A) == 3) % RGB image error calculation
            annErrorImage = GetAnnError_C3(A,B,uint16(rowMap),uint16(colMap),uint16(0),uint16(br_boundary_to_ignore), uint16(width));
        else % Gray level image error calculation
            annErrorImage = GetAnnError_GrayLevel_C1(A,B,uint16(rowMap),uint16(colMap),uint16(0),uint16(br_boundary_to_ignore), uint16(width));
        end
    end
else    
    if (ndims(A) == 3)
        [h w Dim] = size(A);
        % Make data to be DIM*(W*H)
        A = reshape(A,hA*wA,Dim);
        B = reshape(B,hB*wB,Dim);
        A = A';
        B = B';
    else
        [Dim a] = size(A);
    end
    ann_row = rowMap + (colMap-1)*hB;
    
    annErrorImage = sqrt(sum((A-B(:,ann_row)).^2));% Calculate descriptors errors according to mapping
    annErrorImage = reshape(annErrorImage,hA,wA);
end
meanRMS = mean2(annErrorImage(1 : hA - br_boundary_to_ignore,1 : wA - br_boundary_to_ignore));
