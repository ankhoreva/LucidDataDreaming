function currFiltImgs = GetFirstFilter3ChannelsMexS(I,width,classType)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if (ndims(I) == 3) % RGB image
    if strcmp(classType,'int16')
        currFiltImg_r = ApplyPlusKernel8u16s(I(:,:,1),width); 
        currFiltImg_g = ApplyPlusKernel8u16s(I(:,:,2),width);
        currFiltImg_b = ApplyPlusKernel8u16s(I(:,:,3),width);
    else
        currFiltImg_r = ApplyPlusKernel8u32s(I(:,:,1),width); 
        currFiltImg_g = ApplyPlusKernel8u32s(I(:,:,2),width);
        currFiltImg_b = ApplyPlusKernel8u32s(I(:,:,3),width);
    end
    currFiltImgs = cat(3,currFiltImg_r, currFiltImg_g, currFiltImg_b);
else
    if strcmp(classType,'int16')
        currFiltImgs = ApplyPlusKernel8u16s(I(:,:),width); 
    else
        currFiltImgs = ApplyPlusKernel8u32s(I(:,:),width); 
    end
end