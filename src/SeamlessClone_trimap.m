function outputIm = SeamlessClone2(destIm,sourceIm,imMask,LY,LX)
destIm=double(destIm);
sourceIm=double(sourceIm);
[Lh Lv] = imgrad(destIm);
[Gh Gv] = imgrad(sourceIm);

X = destIm;
Fh = Lh;
Fv = Lv;

w = size(imMask,2)-1;
h = size(imMask,1)-1;

msk = zeros(size(X));
imMask=cat(3,imMask,imMask,imMask);
msk(LY:LY+h,LX:LX+w,:) = imMask;
X(msk>0) = sourceIm(imMask>0);

msk=double(imdilate(msk,strel('disk',1))-imerode(msk,strel('disk',1)));
imMask = msk(LY:LY+h,LX:LX+w,:);
msk = zeros(size(X));
msk(LY:LY+h,LX:LX+w,:) = imMask;

Fh(msk>0) = Gh(imMask>0);
Fv(msk>0) = Gv(imMask>0);


outputIm = PoissonGaussSeidel( X, Fh, Fv, msk, 500, 0.001);
outputIm=uint8(outputIm);
end