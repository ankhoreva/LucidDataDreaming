function outputIm = IlluminationChange(destIm, imMask)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
[height, width, ~] = size(destIm);

d1 = double(destIm(:,:,1));
d2 = double(destIm(:,:,2));
d3 = double(destIm(:,:,3));

% number of valid neighbors
N = imfilter(ones(height,width),[0 1 0; 1 0 1; 0 1 0]);
num_pixels = length(find(imMask));
[Y,X] = find(imMask);
indices = zeros(height,width);
count = 1;
for i = 1:num_pixels
   y = Y(i);
   x = X(i);
   indices(y,x) = count;
   count = count + 1;
end

% create sparse matrix for each pixel
A = spalloc(num_pixels,num_pixels,5*num_pixels);
b = zeros(num_pixels,3);
count = 0;

beta = 0.2

for x = 1:width
    for y = 1:height
        if imMask(y,x) == 1
            count = count + 1;
            A(count,count) = N(y,x);

            if y ~= 1
                if imMask(y-1,x) == 1
                    index = indices(y-1,x);
                    A(count,index) = -1; 
                else
                     b(count,1) = b(count,1) + d1(y-1,x);
                     b(count,2) = b(count,2) + d2(y-1,x);
                     b(count,3) = b(count,3) + d3(y-1,x);
                end
            end

            if x ~= 1
                if imMask(y,x-1) == 1
                    index = indices(y,x-1);
                    A(count,index) = -1; 
                else
                     b(count,1) = b(count,1) + d1(y,x-1);
                     b(count,2) = b(count,2) + d2(y,x-1);
                     b(count,3) = b(count,3) + d3(y,x-1);
                end

            end

            if y ~= height
                if imMask(y+1,x) == 1
                    index = indices(y+1,x);
                    A(count,index) = -1; 
                else
                     b(count,1) = b(count,1) + d1(y+1,x);
                     b(count,2) = b(count,2) + d2(y+1,x);
                     b(count,3) = b(count,3) + d3(y+1,x);
                end
            end

            if x ~= width
                if imMask(y,x+1) == 1
                    index = indices(y,x+1);
                    A(count,index) = -1; 
                else
                     b(count,1) = b(count,1) + d1(y,x+1);
                     b(count,2) = b(count,2) + d2(y,x+1);
                     b(count,3) = b(count,3) + d3(y,x+1);
                end
            end
            
            
        end
    end
end


end

