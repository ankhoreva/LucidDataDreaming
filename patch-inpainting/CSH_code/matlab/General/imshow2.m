function imshow2(img1,img2,img3,img4,img5,img6,img7,img8,img9,img10)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[h,w] = FindClosestMultiple(nargin);
H = num2str(h); W = num2str(w);

figure;
handles = [];
sameSize = 1;
for i = 1 : nargin
    I = num2str(i);
    str = ['h',I,' = subplot(',H,',',W,',',I,'); imshow(img',I,'); title(inputname(',I,'))'];
    eval(str);%  axis equal
    handles = [handles,'h',I,','];
    sizeEq = eval(['size(img1)~=size(img' num2str(i) ')']);
    if (sum(sizeEq(1:2))<2)
        sameSize = 0;
    end
end
if (sameSize)
    eval(['linkAxes([',handles(1:end-1),']);']);
end


    
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