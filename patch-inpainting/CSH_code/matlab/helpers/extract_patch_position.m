function [im_patch_pos_X  im_patch_pos_Y] = extract_patch_position(im_size,  patch_w, im_grid_step )

x = 1:im_grid_step:im_size(2) - patch_w+1;
y = 1:im_grid_step:im_size(1) - patch_w+1;
[X Y] = meshgrid(y,x);

im_patch_pos_X = reshape(Y,1,numel(Y));
im_patch_pos_Y = reshape(X,1,numel(X));

end

