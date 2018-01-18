function imagesc2scaled(img1,img2,img3,img4,img5,img6,img7,img8,img9,img10)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[h,w] = FindClosestMultiple(nargin);
H = num2str(h); W = num2str(w);

topLimit = 2^30;
bottomLimit = -1^30;
for i = 1 : nargin    
    I = num2str(i);
    str = ['[pctiles_1_99] = prctile(double(img',I,'(:)),[1,99]);'];
    eval(str);  
    pct1 = pctiles_1_99(1);
    pct99 = pctiles_1_99(2);
    topLimit = min(topLimit,pct99);
    bottomLimit = max(bottomLimit,pct1);
end

if (topLimit <= bottomLimit)
    topLimit = bottomLimit + 1;
end

clims = [bottomLimit, topLimit];


figure;
handles = [];
for i = 1 : nargin
    I = num2str(i);
    str = ['h',I,' = subplot(',H,',',W,',',I,'); imagesc(img',I,',clims); title(inputname(',I,'))'];
    eval(str); axis off;
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