function firstKernel = ApplyPlusKernel(grayA,width)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
grayA = double(grayA);
%% integral image method
widthM1 = width-1;
integralImg = zeros(size(grayA),'int32');
integralImg(1,:) = cumsum(grayA(1,:));
[hA,wA] = size(grayA);
for i = 2 : hA
    cumsumJ = 0;
    for j = 1 : wA
        cumsumJ = cumsumJ + grayA(i,j);
        integralImg(i,j) = integralImg(i-1,j) + cumsumJ;
    end
end

if (width <=8)
    firstKernel = zeros(size(grayA),'int16');
else
    firstKernel = zeros(size(grayA),'int32');
end

firstKernel(1,1) = integralImg(1+widthM1,1+widthM1);
integralImg(1,:) = cumsum(grayA(1,:));
for i = 2 : hA - width
    firstKernel(i,1) = integralImg(i+widthM1,1+widthM1) - integralImg(i-1,1+widthM1);
end
for j = 2 : wA - width
    firstKernel(1,j) = integralImg(1+widthM1,j+widthM1) - integralImg(1+widthM1,j-1);
end

for i = 2 : hA - width
    for j = 2 : wA - width
        firstKernel(i,j) = integralImg(i+widthM1,j+widthM1) - integralImg(i+widthM1,j-1)...
                             - integralImg(i-1,j+widthM1) + integralImg(i-1,j-1);
    end
end

% % D E B U G % % % % % % 
% filter = ones(width,width);
% CompareWithImfilter(grayA,filter,firstKernel);

return

%% log method - takes log(width) computations per image pixel
if (width <=8)
    firstKernel = int16(grayA);
else
    firstKernel = int32(grayA);
end
[hA,wA] = size(grayA);
widthM1 = width-1; widthP1 = width+1;
cols_range = widthP1 : wA - widthM1;
rows_range = widthP1 : hA - widthM1;
k = log2(width);
for level = 1 : k
    skip = 2^(level-1);
    firstKernel(rows_range,1:end-skip) = ...
            firstKernel(rows_range,1:end-skip) + firstKernel(rows_range,1+skip:end);
end

for level = 1 : k
    skip = 2^(level-1);
    firstKernel(1:end-skip,cols_range) = ...
            firstKernel(1:end-skip,cols_range) + firstKernel(1+skip:end,cols_range);
end
% % D E B U G % % % % % % 
% filter = ones(width,width);
% CompareWithImfilter(grayA,filter,firstKernel);
