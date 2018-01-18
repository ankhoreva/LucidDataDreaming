function VisualizeReconstruction(A,AfromB,algoName,imgName,br_boundary_to_ignore,name)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
         
%% show A from B
AtoAfromB = double(A-AfromB); 
AtoAfromB = AtoAfromB(1:end-br_boundary_to_ignore,1:end-br_boundary_to_ignore,:);
squareError = AtoAfromB(:,:,1).^2 + AtoAfromB(:,:,2).^2 + AtoAfromB(:,:,3).^2;
RMSE = sqrt(mean2(squareError));

diffNorm = sqrt(AtoAfromB(:,:,1).^2 + AtoAfromB(:,:,2).^2 + AtoAfromB(:,:,3).^2);
detailsImshow = 'Image A reconstructed from img B';

h_rec = figure; 
subplot 121; 
imshow(uint8(AfromB)); title([imgName ' ' algoName ' ' detailsImshow]);

subplot 122;
clims_3_97 = prctile(diffNorm(:),[3,97]);
imshow(diffNorm,clims_3_97); colormap jet; 
title(['Reconstruction error image    RMSE: ' num2str(RMSE)  '   ML2E: ' num2str(mean2(diffNorm))]);
if exist('name','var')
    set(h_rec,'name',name);
end
