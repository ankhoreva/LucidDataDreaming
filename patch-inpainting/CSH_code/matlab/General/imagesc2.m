function imagesc2(img1,img2,img3,img4,img5,img6,img7,img8,img9,img10)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[h,w] = FindClosestMultiple(nargin);
H = num2str(h); W = num2str(w);

figure;
handles = [];
for i = 1 : nargin
    I = num2str(i);
    isUint8str = ['strcmp(''uint8'',class(img' I '))'];
    isUint8 = eval(isUint8str);
    if (~isUint8)
        prcstr = ['[pctiles_1_99] = prctile(double(img',I,'(:)),[1,99]);'];
        eval(prcstr);
        pctiles_1_99(2) = max(pctiles_1_99(1)+1,pctiles_1_99(2));
        str = ['h',I,' = subplot(',H,',',W,',',I,'); imagesc(img',I,',pctiles_1_99); title(inputname(',I,'))'];
    else
        str = ['h',I,' = subplot(',H,',',W,',',I,'); imagesc(img',I,'); title(inputname(',I,'))'];
    end
    eval(str); 
    axis off;
    handles = [handles,'h',I,','];
end
eval(['linkAxes([',handles(1:end-1),']);']);



function [h,w] = FindClosestMultiple(N)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (N < 4)
    h = 1; w = N;
    return;
end
while(length(factor(N)) ~= 2)
    N = N + 1;
end
h = min(factor(N)); w = max(factor(N));