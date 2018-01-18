function outputIm = TextureFlatten(destIm, imMask, threshold)
%TEXTUREFLATTEN Flattens image according to threshold using Poisson
%   
%   Parameters
%   DESTIM: image to texture flatten
%   THRESHOLD: threshold for edge detection

edgeImage = edge(rgb2gray(destIm),'canny',threshold);

[height, width, ~] = size(destIm);

laplacian = [0 -1 0; -1 4 -1; 0 -1 0];
l1 = conv2(double(destIm(:,:,1)), laplacian, 'same');
l2 = conv2(double(destIm(:,:,2)), laplacian, 'same');
l3 = conv2(double(destIm(:,:,3)), laplacian, 'same');
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
            
            if edgeImage(y,x) == 1
                b(count,1) = b(count,1) + l1(y,x);
                b(count,2) = b(count,2) + l2(y,x);
                b(count,3) = b(count,3) + l3(y,x);
            else
                if edgeImage(y-1,x) == 1
                     b(count,1) = b(count,1) + d1(y,x) - d1(y-1,x);
                     b(count,2) = b(count,2) + d2(y,x) - d2(y-1,x);
                     b(count,3) = b(count,3) + d3(y,x) - d3(y-1,x);
                end
                
                if edgeImage(y,x-1) == 1
                     b(count,1) = b(count,1) + d1(y,x) - d1(y,x-1);
                     b(count,2) = b(count,2) + d2(y,x) - d2(y,x-1);
                     b(count,3) = b(count,3) + d3(y,x) - d3(y,x-1);
                end
                
                if edgeImage(y+1,x) == 1
                     b(count,1) = b(count,1) + d1(y,x) - d1(y+1,x);
                     b(count,2) = b(count,2) + d2(y,x) - d2(y+1,x);
                     b(count,3) = b(count,3) + d3(y,x) - d3(y+1,x);
                end
                
                if edgeImage(y,x+1) == 1
                     b(count,1) = b(count,1) + d1(y,x) - d1(y,x+1);
                     b(count,2) = b(count,2) + d2(y,x) - d2(y,x+1);
                     b(count,3) = b(count,3) + d3(y,x) - d3(y,x+1);
                end
            end
        end
    end
end

%% Determines new points and fills in image.
outputIm = double(destIm);
for channel = 1:3
    % TODO: use Gauss Seidel instead of mldivide
    points = A\b(:,channel);
    for k = 1:num_pixels
        outputIm(Y(k),X(k),channel) = points(k);
    end
end
outputIm = uint8(outputIm);

end

