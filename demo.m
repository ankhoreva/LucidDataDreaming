cd lucid_data_dreaming

addpath(genpath('src'));
%% inpainting
addpath(genpath('patch-inpainting'));
%% blending
addpath(genpath('PoissonEdiitng'));


img =imread('img.jpg');
gt = imread('gt.png');

% generate a new synthetic image
[im1, gt1, prev_mask1]= lucid_dream(img,gt,0);   

figure(1)
hold on
subplot(2,2,1)
imagesc(img)
title('Original image');
subplot(2,2,2)
imagesc(im1)
title('Synthetic image');
subplot(2,2,3)
imagesc(gt)
title('Original mask');
subplot(2,2,4)
imagesc(gt1)
title('Synthetic mask');


% generate a pair of consequent frames
[im1, gt1, prev_mask1, im2, gt2, prev_mask2, Flow_B, Flow_F]= lucid_dream(img,gt, 1);   

figure(1)
hold on
subplot(3,2,1)
imagesc(img)
title('Original image');
subplot(3,2,3)
imagesc(im1)
title('Synthetic image #1');
subplot(3,2,4)
imagesc(im2)
title('Synthetic image #2');
subplot(3,2,2)
imagesc(gt)
title('Original mask');
subplot(3,2,5)
imagesc(gt1)
title('Synthetic mask #1');
subplot(3,2,6)
imagesc(gt2)
title('Synthetic mask #2');
