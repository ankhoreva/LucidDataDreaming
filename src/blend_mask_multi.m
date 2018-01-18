function [clonedIm2, new_seg]=blend_mask_multi(seg_or, img, back_img, mask)    

% random scaling
scale=[0.85:0.05:1.15];
scale_ind=randsample(numel(scale),1);
   
if size(img,3)<3
   img=cat(3,img,img,img);
end
    
% crop the object    
[M,N]=find(mask>0);
topM=min(M);
bottomM=max(M);
leftN=min(N);
rightN=max(N);
seg=zeros(size(seg_or));
seg(mask>0)=mask(mask>0);
seg2=seg(topM:bottomM, leftN:rightN);
img2=img(topM:bottomM, leftN:rightN,:);
  
% re-scale randomly
ih=min(max(round(size(seg2,1)*scale(scale_ind)),100),size(back_img,1)-50);
iw=min(max(round(size(seg2,2)*scale(scale_ind)),100),size(back_img,2)-50);
imMask=imresize(seg2,[ih,iw],'nearest');
img2=imresize(img2,[ih,iw]);

% random placement
max_offsetY = size(back_img,1)-size(imMask,1);
max_offsetX = size(back_img,2)-size(imMask,2);
offsetY = randsample(max_offsetY,1);
offsetX = randsample(max_offsetX,1);

% blended image
clonedIm2 = SeamlessClone_trimap(back_img,img2,imMask,offsetY,offsetX);

% segmentation mask
 new_seg=zeros(size(back_img,1),size(back_img,2));
 new_seg(offsetY:size(imMask,1)+offsetY-1,offsetX:size(imMask,2)+offsetX-1)=imMask;
 new_seg2=seg_or;
 new_seg2(new_seg>0)=new_seg(new_seg>0);
 new_seg=new_seg2;
 
end

  
  
  
  
  
  
  
  
        