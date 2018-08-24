function [im1, gt1, prev_mask1, im2, gt2, prev_mask2, Flow_B, Flow_F]= lucid_dream(img,gt, consequent_frames)   
%   Input:
%    img - image
%    gt  - ground truth segmentation mask
%   Output:
%    im* - synthesized image (im1, im2)
%    gt* - synthesized mask (gt1, gt2)
%    prev_mask* - synthesized previous frame mask for im1, im2 (prev_mask1, prev_mask2)
%    Flow_B, Flow_F - backward and forward optical flow between im1 and im2
%    consequent_frames - 0: generate 1 new image, 1: generate a pair of
%    consequent frames with optical flow
%% inpainting
addpath(genpath('patch-inpainting'));
addpath(genpath('/patch-inpainting/CSH_code'));

%% blending
addpath(genpath('../PoissonEdiitng'));
%% --------------------    
    
    
if size(img,3)<3
img=cat(3,img,img,img);
end 
object_ids=unique(gt); object_ids(1)=[];  
   
%% randomly choose objects to manipulate

  number_of_objects= randsample(numel(object_ids),1);
  possible_combinations = nchoosek(object_ids,number_of_objects);
  mask_object_ids=possible_combinations(randsample(size(possible_combinations,1),1),:);
  mask=double(gt).*double(ismember(gt,mask_object_ids)>0);

%% create inpainted background image
% random augmentation: flipping, illumination change

seg=gt;

% inpainting
  back_img=patch_inpaint(img,imdilate(gt,strel('disk',7)),0);
 
% paste other objects or not     
  if  randsample(2,1)-1
     mask3=cat(3,mask,mask,mask);
     mask3 = imdilate(mask3,strel('disk',2));
     back_img(mask3==0)=img(mask3==0);
  else
      seg(mask==0)=0;
  end
  
seg_backgr=zeros(size(seg));
seg_backgr(mask==0)=seg(mask==0);  

% random flipping     
 if  randsample(2,1)-1
    back_img = fliplr(back_img);    
    seg_backgr=fliplr(seg_backgr);
 end
 
% random illumination change 
if  randsample(2,1)-1
 back_img=uint8(255*change_illumination(back_img));
end

mask_old=mask;

%% create img_1

if  randsample(2,1)-1 % transform, randomly place & blend
[new_seg, new_img] = spline_transform_multi(img, seg_backgr, mask_old); % transform
mask=double(new_seg).*double(ismember(new_seg,mask_object_ids)>0);
[new_img, new_seg] = blend_mask_multi(seg_backgr, new_img, back_img,mask); % place & blend
else % just randomly place & blend
[new_img, new_seg]=blend_mask_multi(seg_backgr, img, back_img, mask_old);
end
% standard augmentation: scale, rotate, flip, illumination change
[im_1,gt_1,bb_1]= augment_image_mask_illumination_deform_random_img_multi(new_img,new_seg);

im1=im_1;
gt1=uint8(gt_1);
prev_mask1=uint8(1*(bb_1));

if consequent_frames
%% create img_2

% need to decide what's foreground and background
number_of_objects= randsample(numel(object_ids),1);
possible_combinations = nchoosek(object_ids,number_of_objects);
mask_object_ids_fg=possible_combinations(randsample(size(possible_combinations,1),1),:);
mask_fg=double(gt_1).*double(ismember(gt_1,mask_object_ids_fg)>0);% objects to manipulate
mask_bg=double(gt_1).*double(mask_fg==0); % background objects

% inpainting for background img_1
back_img_1=patch_inpaint(im_1,imdilate(gt_1,strel('disk',7)),0); 
% pasting background object
back_img_obj_1=back_img_1;
mask3=cat(3,mask_fg,mask_fg,mask_fg);
mask3 = imdilate(mask3,strel('disk',2));
back_img_obj_1(mask3==0)=im_1(mask3==0);

% imshow(im_1)
% figure(2)
% imshow(back_img_1)

% type of deformation
transf_id=randsample(3,1);
if transf_id < 3
% type of foreground transformation  
fogr_id=randsample(3,1);
fogr_var=[1,1;1,0;0,1];
fogr=fogr_var(fogr_id,:);
end

if transf_id==1 % foreground and background transformation
[back_img_2, F_Flowb, B_Flowb, back_gt_2]= augment_background(back_img_obj_1, mask_bg,back_img_1); % transform background
[new_seg2, new_img2, new_bb2,  F_Flowf, B_Flowf ] =  augment_foreground(im_1, mask_fg, back_img_2,back_gt_2,fogr(1),fogr(2)); % augment foreground

% generate optical flow
mask_fg2=double(new_seg2).*double(ismember(new_seg2,mask_object_ids_fg)>0);
new_seg3f=cat(3, mask_fg2, mask_fg2);
Flow_B=B_Flowf.*(new_seg3f>0)+B_Flowb.*(new_seg3f<=0);
new_seg3f=cat(3, mask_fg, mask_fg);
Flow_F=F_Flowf.*(new_seg3f>0)+F_Flowb.*(new_seg3f<=0);

elseif transf_id==2 % just foreground transformation
[new_seg2, new_img2, new_bb2,  F_Flowf, B_Flowf ] =  augment_foreground(im_1, mask_fg, back_img_obj_1,mask_bg,fogr(1),fogr(2));
mask_fg2=double(new_seg2).*double(ismember(new_seg2,mask_object_ids_fg)>0);
new_seg3f=cat(3, mask_fg2, mask_fg2);
Flow_B=B_Flowf.*(new_seg3f>0);
new_seg3f=cat(3, mask_fg, mask_fg);
Flow_F=F_Flowf.*(new_seg3f>0);

elseif transf_id==3 % just background transformation
[back_img_2, F_Flowb, B_Flowb, back_gt_2] = augment_background(back_img_obj_1, mask_bg,back_img_1);
[new_seg2, new_img2, new_bb2] =  augment_foreground(im_1, mask_fg,back_img_2,back_gt_2,0,0);
Flow_B=B_Flowb;
Flow_F=F_Flowb;
end

im2=new_img2;
gt2=uint8(new_seg2);
prev_mask2=uint8(1*(new_bb2));
end    

% new_img2=warp_image(im_1,Flow_B(:,:,1),Flow_B(:,:,2));
% figure(1)
% hold on
% subplot(2,2,1)
% imshow(im_1)
% subplot(2,2,2)
% imshow(uint8(new_img2))
% subplot(2,2,3)
% imshow(im2)
% subplot(2,2,4)
% imshow(im2-uint8(new_img2))

end 


