function stacked_patch = ConvertToStackedFormat(patch)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

stacked_patch = cat(1,patch(:,:,1),patch(:,:,2),patch(:,:,3));