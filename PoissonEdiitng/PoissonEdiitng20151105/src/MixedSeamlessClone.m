function outputIm = MixedSeamlessClone(destIm,sourceIm,imMask,offsetY,offsetX)
%MIXEDSEAMLESSCLONE Blends SOURCEIM into DESTIM using IMMASK
%
%   Parameters
%   DESTIM: background image
%   SOURCEIM: m by n image to blend into DESTIM
%   IMMASK: m by n matrix of logicals to determine which pixels of SOURCEIM
%       to use
%   OFFSETY: offset to use for source image in vertical direction
%   OFFSETX: offset to use for source image in horizontal direction
%
% This function differs from SEAMLESSCLONE in that it uses a mixed
% gradient. Since most of the source image is empty, we will incorporate
% more of the destination image.

% get dimensions of source image
[height, width, ~] = size(sourceIm);

% number of valid neighbors
N = imfilter(ones(height,width),[0 1 0; 1 0 1; 0 1 0]);

% get number of pixels to determine and create index matrix
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

% Separate into components
s1 = double(sourceIm(:,:,1));
s2 = double(sourceIm(:,:,2));
s3 = double(sourceIm(:,:,3));
d1 = double(destIm(:,:,1));
d2 = double(destIm(:,:,2));
d3 = double(destIm(:,:,3));

% In each row of the matrix, we will have 5 elements of fewer, so we use a
% sparse matrix to save space
A = spalloc(num_pixels,num_pixels,5*num_pixels);

% 3 because we need one for each channel
b = zeros(num_pixels,3);

% keep track of amount of pixels added so far
count = 0;

%% Constructs the system of linear equations
% iterate over each pixel in the image
for x = 1:width
    for y = 1:height
        
        % only add points that are in mask
        if imMask(y,x) == 1
            count = count + 1;
            A(count,count) = N(y,x);
            
            % take care of neighbors
            % top boundary
            if y ~= 1
                if imMask(y-1,x) == 1
                    index = indices(y-1,x);
                    A(count,index) = -1;
                else
                    b(count,1) = b(count,1) + d1(y-1+offsetY,x+offsetX);
                    b(count,2) = b(count,2) + d2(y-1+offsetY,x+offsetX);
                    b(count,3) = b(count,3) + d3(y-1+offsetY,x+offsetX);
                end
                
                destGrad1 = d1(y+offsetY,x+offsetX)-d1(y-1+offsetY,x+offsetX);
                sourceGrad1 = s1(y,x) - s1(y-1,x);
                destGrad2 = d2(y+offsetY,x+offsetX)-d2(y-1+offsetY,x+offsetX);
                sourceGrad2 = s2(y,x) - s2(y-1,x);
                destGrad3 = d3(y+offsetY,x+offsetX)-d3(y-1+offsetY,x+offsetX);
                sourceGrad3 = s3(y,x) - s3(y-1,x);
                
                if abs(destGrad1) > abs(sourceGrad1)
                    b(count,1) = b(count,1) + destGrad1;
                else
                    b(count,1) = b(count,1) + sourceGrad1;
                end
                
                if abs(destGrad2) > abs(sourceGrad2)
                    b(count,2) = b(count,2) + destGrad2;
                else
                    b(count,2) = b(count,2) + sourceGrad2;
                end
                
                if abs(destGrad3) > abs(sourceGrad3)
                    b(count,3) = b(count,3) + destGrad3;
                else
                    b(count,3) = b(count,3) + sourceGrad3;
                end
            end
            
            % left boundary
            if x ~= 1
                if imMask(y,x-1) == 1
                    index = indices(y,x-1);
                    A(count,index) = -1;
                else
                    b(count,1) = b(count,1) + d1(y+offsetY,x-1+offsetX);
                    b(count,2) = b(count,2) + d2(y+offsetY,x-1+offsetX);
                    b(count,3) = b(count,3) + d3(y+offsetY,x-1+offsetX);
                end
                
                destGrad1 = d1(y+offsetY,x+offsetX)-d1(y+offsetY,x-1+offsetX);
                sourceGrad1 = s1(y,x) - s1(y,x-1);
                destGrad2 = d2(y+offsetY,x+offsetX)-d2(y+offsetY,x-1+offsetX);
                sourceGrad2 = s2(y,x) - s2(y,x-1);
                destGrad3 = d3(y+offsetY,x+offsetX)-d3(y+offsetY,x-1+offsetX);
                sourceGrad3 = s3(y,x) - s3(y,x-1);
                
                if abs(destGrad1) > abs(sourceGrad1)
                    b(count,1) = b(count,1) + destGrad1;
                else
                    b(count,1) = b(count,1) + sourceGrad1;
                end
                
                if abs(destGrad2) > abs(sourceGrad2)
                    b(count,2) = b(count,2) + destGrad2;
                else
                    b(count,2) = b(count,2) + sourceGrad2;
                end
                
                if abs(destGrad3) > abs(sourceGrad3)
                    b(count,3) = b(count,3) + destGrad3;
                else
                    b(count,3) = b(count,3) + sourceGrad3;
                end
            end
            
            % bottom boundary
            if y ~= height
                if imMask(y+1,x) == 1
                    index = indices(y+1,x);
                    A(count,index) = -1;
                else
                    b(count,1) = b(count,1) + d1(y+1+offsetY,x+offsetX);
                    b(count,2) = b(count,2) + d2(y+1+offsetY,x+offsetX);
                    b(count,3) = b(count,3) + d3(y+1+offsetY,x+offsetX);
                end
                
                destGrad1 = d1(y+offsetY,x+offsetX)-d1(y+1+offsetY,x+offsetX);
                sourceGrad1 = s1(y,x) - s1(y+1,x);
                destGrad2 = d2(y+offsetY,x+offsetX)-d2(y+1+offsetY,x+offsetX);
                sourceGrad2 = s2(y,x) - s2(y+1,x);
                destGrad3 = d3(y+offsetY,x+offsetX)-d3(y+1+offsetY,x+offsetX);
                sourceGrad3 = s3(y,x) - s3(y+1,x);
                
                if abs(destGrad1) > abs(sourceGrad1)
                    b(count,1) = b(count,1) + destGrad1;
                else
                    b(count,1) = b(count,1) + sourceGrad1;
                end
                
                if abs(destGrad2) > abs(sourceGrad2)
                    b(count,2) = b(count,2) + destGrad2;
                else
                    b(count,2) = b(count,2) + sourceGrad2;
                end
                
                if abs(destGrad3) > abs(sourceGrad3)
                    b(count,3) = b(count,3) + destGrad3;
                else
                    b(count,3) = b(count,3) + sourceGrad3;
                end
            end
            
            % right boundary
            if x ~= width
                if imMask(y,x+1) == 1
                    index = indices(y,x+1);
                    A(count,index) = -1;
                else
                    b(count,1) = b(count,1) + d1(y+offsetY,x+1+offsetX);
                    b(count,2) = b(count,2) + d2(y+offsetY,x+1+offsetX);
                    b(count,3) = b(count,3) + d3(y+offsetY,x+1+offsetX);
                end
                
                destGrad1 = d1(y+offsetY,x+offsetX)-d1(y+offsetY,x+1+offsetX);
                sourceGrad1 = s1(y,x) - s1(y,x+1);
                destGrad2 = d2(y+offsetY,x+offsetX)-d2(y+offsetY,x+1+offsetX);
                sourceGrad2 = s2(y,x) - s2(y,x+1);
                destGrad3 = d3(y+offsetY,x+offsetX)-d3(y+offsetY,x+1+offsetX);
                sourceGrad3 = s3(y,x) - s3(y,x+1);
                
                if abs(destGrad1) > abs(sourceGrad1)
                    b(count,1) = b(count,1) + destGrad1;
                else
                    b(count,1) = b(count,1) + sourceGrad1;
                end
                
                if abs(destGrad2) > abs(sourceGrad2)
                    b(count,2) = b(count,2) + destGrad2;
                else
                    b(count,2) = b(count,2) + sourceGrad2;
                end
                
                if abs(destGrad3) > abs(sourceGrad3)
                    b(count,3) = b(count,3) + destGrad3;
                else
                    b(count,3) = b(count,3) + sourceGrad3;
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
        outputIm(Y(k)+offsetY,X(k)+offsetX,channel) = points(k);
    end
end
outputIm = uint8(outputIm);
end

