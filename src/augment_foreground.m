function [ new_seg2, new_img2, bb1, Flow, Flowb ] = augment_foreground( img, seg, back_img, mask_bgr, ifshift, iftransform )

shift=[-0.05:0.005:0.05];%[-0.10:0.01:0.10];

[M,N]=find(seg>0);
w=max(N)-min(N);
h=max(M)-min(M); 
bound=imdilate(seg,strel('disk',1))-seg;

if iftransform
% randomly sample the points on the object boundary
[x,y]=find(bound);
if ~isempty(x)
 if numel(x)>4
 num_points=5;
 rand_p=randsample(numel(x),num_points);
 movingPoints=zeros(num_points,2);fixedPoints=zeros(num_points,2);

% randomly shift the points 
 for l=1:numel(rand_p)
 fixedPoints(l,1)=x(rand_p(l))+ h*shift(randsample(numel(shift),1));
 fixedPoints(l,2)=y(rand_p(l))+ w*shift(randsample(numel(shift),1));
 movingPoints(l,1)=x(rand_p(l));
 movingPoints(l,2)=y(rand_p(l));
 end

% fit thin-plate smoothing spline
st = tpaps(movingPoints',fixedPoints');
x = (1: size(seg, 2));
y = (1: size(seg, 1));
[xx,yy]         = meshgrid(x,y);
xy=[xx(:),yy(:)]';
avals = fnval(st,xy);


% transform matrix
transform_matrix= zeros([size(seg),2]);
transform_matrix(:,:,1)=reshape(avals(1,:)-xx(:)',size(seg,1),size(seg,2));
transform_matrix(:,:,2)=reshape(avals(2,:)-yy(:)',size(seg,1),size(seg,2));

% transformed object and mask
new_img = imwarp(img,transform_matrix);
new_seg = imwarp(seg,transform_matrix,'nearest');
new_img(cat(3,new_seg,new_seg,new_seg)==0)=0;
new_img=uint8(new_img);

 else % no transformation
   transform_matrix= zeros([size(seg),2]);
   new_seg=uint8(seg);
   new_img=img;
end
else  % no transformation
   transform_matrix= zeros([size(seg),2]);
   new_seg=uint8(seg);
   new_img=img;
end    
else  % no transformation
   transform_matrix= zeros([size(seg),2]);
   new_seg=uint8(seg);
   new_img=img;
end        
  

X_transb=transform_matrix(:,:,1);
Y_transb=transform_matrix(:,:,2);

[new_img2, new_seg2]=blend_mask_transf(new_seg, new_img, back_img,ifshift); 

[x,y]=find(new_seg>0);
[x2,y2]=find(new_seg2>0);

X_trans2=zeros(size(seg));
Y_trans2=zeros(size(seg));
X_trans2(seg>0)=-X_transb(seg>0);
Y_trans2(seg>0)=-Y_transb(seg>0);

if isempty(x)
Tx=X_trans2; Ty=Y_trans2;
else
Tx=X_trans2+(seg>0).*(min(x2)-min(x)); Ty=Y_trans2+(seg>0).*(min(y2)-min(y));
end

X_transb2=zeros(size(seg));
Y_transb2=zeros(size(seg));
X_transb2(new_seg2>0)=X_transb(new_seg>0);
Y_transb2(new_seg2>0)=Y_transb(new_seg>0);
if isempty(x)
Txb=X_transb2; Tyb=Y_transb2;
else
Txb= X_transb2-(new_seg2>0).*(min(x2)-min(x)); Tyb=Y_transb2-(new_seg2>0).*(min(y2)-min(y));
end

Flow=cat(3, Tx,Ty); Flowb=cat(3, Txb,Tyb);

new_seg=mask_bgr;
new_seg(new_seg2>0)=new_seg2(new_seg2>0);
new_seg2=new_seg;
 

%% prev frame mask generation

  seg=new_seg2;
  [M,N]=find(seg>0);
  w=max(N)-min(N);
  h=max(M)-min(M); 
  
bb1=uint8(seg);
   
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
bb1 = uint8(imdilate(bb1,strel('disk',5)));
end
end



end

function [clonedIm, clonedSeg]=blend_mask_transf(seg, img, back_img, ifshift)    

noshift=~ifshift;
   
if size(img,3)<3
        img=cat(3,img,img,img);
end
    
    
[M,N]=find(seg>0);
topM=min(M);
bottomM=max(M);
leftN=min(N);
rightN=max(N);  
seg2=seg(topM:bottomM, leftN:rightN);
img2=img(topM:bottomM, leftN:rightN,:);
imMask=seg2;

max_offsetY = [max(-floor(0.05*size(imMask,1)),-topM+1):1:min(floor(0.05*size(imMask,1)),size(back_img,1)-bottomM-1)];
max_offsetX = [max(-floor(0.05*size(imMask,2)),-leftN+1):1:min(floor(0.05*size(imMask,2)),size(back_img,2)-rightN-1)];

if (size(max_offsetY,2)==1)||isempty(max_offsetY)||noshift
    offsetY=topM;
else
    offsetY = topM+max_offsetY(randsample(numel(max_offsetY),1));
end

if (size(max_offsetX,2)==1)||isempty(max_offsetX)||noshift
    offsetX=leftN;
else
    offsetX = leftN+max_offsetX(randsample(numel(max_offsetX),1));
end

clonedIm = SeamlessClone_trimap(back_img,img2,imMask,offsetY,offsetX);

clonedSeg=zeros(size(back_img,1),size(back_img,2));
clonedSeg(offsetY:size(imMask,1)+offsetY-1,offsetX:size(imMask,2)+offsetX-1)=imMask;
end

