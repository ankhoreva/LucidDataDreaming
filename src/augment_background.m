function [transformed_image, F_Flow, B_Flow, transformed_mask]= augment_background(img,gt, back_img)

pad_size = [round(max(size(img,1))/2),round(max(size(img,2))/2)];
padded_image        = padarray(img, pad_size, 'symmetric');
padded_bimage        = padarray(back_img, pad_size, 'symmetric');

%% affine
% rotation angle
angle_var=[-3:1:3];
angle = angle_var(randsample(numel(angle_var),1));
angle_param = angle*pi/180; 

% scale factor
scale=[0.95:0.005:1.05]; 
scale_x=scale(randsample(numel(scale),1));
scale_y=scale(randsample(numel(scale),1));
      
% translation
[w,h,~]=size(img);
shift_x=[-round(0.05*w):round(0.05*w)];
shift_y=[-round(0.05*h):round(0.05*h)];

tx = shift_x(randsample(numel(shift_x),1));
ty = shift_y(randsample(numel(shift_y),1)); % y translation

sc = scale_x*cos(angle_param);
ss = scale_y*sin(angle_param);

T = [ sc -ss  0;
      ss  sc  0;
      tx  ty  1];

% t_nonsim = affine2d(T);
Tshift  = [ 1  0  0;
                0  1  0;
                -size(padded_image,2)/2 -size(padded_image,1)/2  1 ];
Tshift1  = [ 1  0  0;
                0  1  0;
                -size(img,2)/2 -size(img,1)/2  1 ];        

Tbg  = affine2d(Tshift * T * inv(Tshift1));
Tbg_flow       = affine2d((Tshift1) * T * inv(Tshift1));

% Transform padded image
transformed_image   = imwarp( padded_image, Tbg, 'OutputView',  imref2d(size(img)));    
transformed_bimage   = imwarp( padded_bimage, Tbg, 'OutputView',  imref2d(size(back_img)));

% Transform mask
transformed_mask = imwarp(gt+1,Tbg_flow,'nearest', 'OutputView', imref2d(size(gt)));
mask_3d = cat(3,transformed_mask,transformed_mask,transformed_mask);
    
transformed_image(mask_3d==0) =  transformed_bimage(mask_3d==0);
transformed_mask=transformed_mask-1;
transformed_mask(transformed_mask<0)=0;
% Forward flow
% Transform pixel locs. with t_nonsim
% [xx,yy]=find(transformed_mask>=0);
x = (1: size(transformed_mask, 2));
y = (1: size(transformed_mask, 1));
[xx,yy]         = meshgrid(x,y);
[t_xx,t_yy]     = transformPointsForward (Tbg_flow, xx(:), yy(:));
% Reshape motion
FX        =  reshape( (t_xx -xx(:) ), [ size(xx, 1) size(xx, 2) ]) ;
FY        =  reshape( (t_yy -yy(:) ), [ size(yy, 1) size(yy, 2) ]) ;
F_Flow=cat(3, FX,FY);
%Backward flow
[t_xx,t_yy]     = transformPointsInverse(Tbg_flow,  xx(:), yy(:));
BX        =  reshape( (t_xx -xx(:) ), [ size(xx, 1) size(xx, 2) ]) ;
BY        =  reshape( (t_yy -yy(:) ), [ size(yy, 1) size(yy, 2) ]) ;
B_Flow=cat(3, BX,BY);

end
            

     

