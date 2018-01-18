function [ new_seg, new_img ] = spline_transform_multi( img, seg, mask )

%shift=[-0.10:0.01:0.10];
shift=[-0.05:0.005:0.05];

% randomly sample the points on the object boundary
[M,N]=find(mask>0);
w=max(N)-min(N);
h=max(M)-min(M); 
bound=imdilate(mask,strel('disk',1))-mask;
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
[x,y]=find(mask>=0);
xy=[x,y]';
avals = fnval(st,xy);

% transform matrix
transform_matrix= zeros([size(seg),2]);
transform_matrix(:,:,1)=sparse(x,y,avals(1,:)-xy(1,:),size(seg,1),size(seg,2));
transform_matrix(:,:,2)=sparse(x,y,avals(2,:)-xy(2,:),size(seg,1),size(seg,2));

% transformed object and mask
new_img = imwarp(img,transform_matrix);
new_seg = imwarp(mask,transform_matrix,'nearest');
new_seg=imerode(new_seg,strel('disk',1));
seg(new_seg>0)=new_seg(new_seg>0);
new_seg=uint8(seg);

new_img(cat(3,new_seg,new_seg,new_seg)==0)=0;
new_img=uint8(new_img);

 else % no transformation
   new_seg=uint8(seg);
   new_seg(mask>0)=mask(mask>0);
   new_img=img;
end
else  % no transformation
   new_seg=uint8(seg);
   new_seg(mask>0)=mask(mask>0);
   new_img=img;
end

end

