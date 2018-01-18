function patches_RGB = ConvertPatchArrayFromYCbCr2RGB(patches_YCbCr)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

patches_RGB = patches_YCbCr;
[h,w] = size(patches_YCbCr);
width = sqrt(h/3);

for ind = 1 : w
    patch = patches_YCbCr(:,ind);
    rgb_patch = ycbcr2rgb(reshape(patch,[width,width,3]));
    patches_RGB(:,ind) = rgb_patch(:);
end