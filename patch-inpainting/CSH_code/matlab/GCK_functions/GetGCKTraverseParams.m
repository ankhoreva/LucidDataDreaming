function [res2DforDebug,snakeOrder,deltas1D,alphaDirs1D] = GetGCKTraverseParams(width)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

widthM1 = width-1;
k = log2(width);
if (floor(k)~=k)
          error('width isn''t a power of 2!');
end

tree{1} = 1; tree{2} = [1 1]; tree{2*width-1} = 1;tree{3} = [1 -1]; 

%% 1D kernels
for parent = 2 : widthM1
          sign = 2*mod(parent,2)-1;
          mult = sign*[-1,1];
          tree{2*parent} = [tree{parent} mult(1)*tree{parent}]; % left child
          tree{2*parent+1} = [tree{parent} mult(2)*tree{parent}]; % right child
end

res1D = zeros(width,width);
for ind = width : 2*width-1
          res1D(ind-width+1,:) = tree{ind};
end

%% 1D deltas and 1D 'alpha directions'
treeDeltas1D = zeros(1,2*width-2);
treeDirs1D = zeros(1,2*width-2);
treeDirs1D(1) = -1; % root initialization
for child = 2 : 2*width - 2
          parent1 = floor(child/2);
          parent2 = floor((child+1)/2);
          if (parent1==parent2)
                    treeDeltas1D(child) = 2^floor(log2(parent1));
                    if((parent1==1)||(mod(parent1,2)==0))
                              treeDirs1D(child) = -1;
                    else
                              treeDirs1D(child) = 1;
                    end
          else
                    treeDeltas1D(child) = treeDeltas1D(parent1);
                    treeDirs1D(child) = treeDirs1D(parent1);
          end
end
deltas1D = treeDeltas1D(end-(widthM1-1):end); % these are the leaves
alphaDirs1D = treeDirs1D(end-(widthM1-1):end); % these are the leaves
%% 2D kernels

res2DforDebug = zeros(width,width,width,width);
% D E B U G
% figure; place = 1;
for row = 1 : width
          for col = 1 : width
                    kernel = res1D(row,:)'*res1D(col,:);
                    % D E B U G
                    %         subplot(width,width,place); place = place + 1;
                    %         imshow(kernel);
                    res2DforDebug(:,:,row,col) = kernel;
          end
end

snakeOrder = [];
%% snake traverse

for i = 1 : width
          clear vec
          is = i*ones(1,i);
          one2i = 1:i;
          vec = [is; one2i];
          swappedVec = fliplr(flipud(vec(:,1:end-1)));
          order = [vec swappedVec];
          if (mod(i,2)==1)
                    order = fliplr(order);
          end
          snakeOrder = [snakeOrder order];
end


