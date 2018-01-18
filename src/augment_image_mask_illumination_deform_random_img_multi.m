function [im1_rot_crop,gt_rot_crop,bb1_rot_crop]= augment_image_mask_illumination_deform_random_img_multi(im0,gt0)

% im1_rot_crop - augmented image
% gt_rot_crop - augmented mask
% bb1_rot_crop - previous frame mask


shift=[-0.05:0.005:0.05];

if  randsample(2,1)-1
     illumination=1;
 else
     illumination=0;
 end
 
  if  randsample(2,1)-1
    flip=1;
 else
    flip=0;
  end
  
 if  randsample(2,1)-1
    rotate=1;
 else
    rotate=0;
 end
 
 
resize=1;

im_dim1 = size(im0,1);
im_dim2 = size(im0,2);
angle_var=[-30:2:30];
angle = angle_var(randsample(numel(angle_var),1));

% generate previous frame mask
im1=im0;
gt1=double(gt0);
seg=gt1;
[M,N]=find(gt1>0);
w=max(N)-min(N);
h=max(M)-min(M); 
bb1=zeros(size(seg)); 
bound=imdilate(seg,strel('disk',1))-seg;
[x,y]=find(bound);
if ~isempty(x)
    if numel(x)>4
num_points=5;
rand_p=randsample(numel(x),num_points);
movingPoints=zeros(num_points,2);
fixedPoints=zeros(num_points,2);

for l=1:numel(rand_p)
fixedPoints(l,1)=x(rand_p(l))+ h*shift(randsample(numel(shift),1));
fixedPoints(l,2)=y(rand_p(l))+ w*shift(randsample(numel(shift),1));
movingPoints(l,1)=x(rand_p(l));
movingPoints(l,2)=y(rand_p(l));
end

% fit thin-plate smoothing spline
st = tpaps(movingPoints',fixedPoints');
[x,y]=find(seg>=0);
xy=[x,y]';
avals = fnval(st,xy);


% transform matrix
transform_matrix= zeros([size(seg),2]);
transform_matrix(:,:,1)=sparse(x,y,avals(1,:)-xy(1,:),size(seg,1),size(seg,2));
transform_matrix(:,:,2)=sparse(x,y,avals(2,:)-xy(2,:),size(seg,1),size(seg,2));

% transformed mask
bb1 = imwarp(seg,transform_matrix,'nearest');
bb1 = imdilate(bb1,strel('disk',5));
end
end

 gt1=uint8(gt1);
 bb1=uint8(bb1);
    
      im1_rot_crop=im1;
      gt_rot_crop =gt1;
      bb1_rot_crop=bb1;
 
          if rotate
          
            im1_rot_crop = rotate_image(im1, angle, 'bicubic'); 
            gt_rot_crop = rotate_image(gt1, angle, 'nearest');
            bb1_rot_crop = rotate_image(bb1, angle, 'nearest');
            if resize,
                im1_rot_crop = imresize(im1_rot_crop, [im_dim1, im_dim2], 'bicubic');
                gt_rot_crop = imresize(gt_rot_crop, [im_dim1, im_dim2], 'nearest');
                bb1_rot_crop = imresize(bb1_rot_crop, [im_dim1, im_dim2], 'nearest');
             end
            end          

            if flip
                gt_rot_crop=uint8(gt_rot_crop);
                 bb1_rot_crop=uint8(1*(bb1_rot_crop));
                im1_rot_crop=fliplr(im1_rot_crop);
                gt_rot_crop=fliplr(gt_rot_crop);
                 bb1_rot_crop=fliplr(bb1_rot_crop);
            end
            
              if illumination
              im1_rot_crop=uint8(255*change_illumination(im1_rot_crop));
              gt_rot_crop=uint8(gt_rot_crop);
              bb1_rot_crop=uint8(1*(bb1_rot_crop));
              end
 end
            

     

