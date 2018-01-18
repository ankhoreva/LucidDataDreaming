function nextFiltImgs = ProceedOneSnakeStepFor3ChannelsMexTailored(currFiltImgs,snakeOrder,deltas1D,alphaDirs1D,snakeInd,procs,ImgH,ImgW,width,classType,yOnly)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
prevInd = procs(snakeInd);
% prevY = snakeOrder(1,snakeInd-1); prevX = snakeOrder(2,snakeInd-1);
prevY = snakeOrder(1,prevInd); prevX = snakeOrder(2,prevInd);
Y = snakeOrder(1,snakeInd); X = snakeOrder(2,snakeInd);

if (Y == prevY)  % -> moving horizontally
          if (prevX < X)
                    delta_j = deltas1D(prevX);
                    dir_j = alphaDirs1D(prevX);
          else
                    delta_j = deltas1D(X);
                    dir_j = -1*alphaDirs1D(X);
          end
          LRnotUD = true;
else % (X == prevX) -> moving vertically
          if (prevY < Y)
                    delta_j = deltas1D(prevY);
                    dir_j = alphaDirs1D(prevY);
          else
                    delta_j = deltas1D(Y);
                    dir_j = -1*alphaDirs1D(Y);
          end
          LRnotUD = false;
end

bCurAlphaPos = dir_j==1;
if strcmp(classType,'int16')
          if (yOnly)
                   nextFiltImgs = GCKFilterSingleStep16s_yOnly_C3_OPTER2(currFiltImgs, uint16(width), bCurAlphaPos, uint16(delta_j), LRnotUD);
          else
                   nextFiltImgs = GCKFilterSingleStep16s_C3(currFiltImgs, uint16(width), bCurAlphaPos, uint16(delta_j), LRnotUD);
                   nextFiltImgs = reshape(nextFiltImgs, size(currFiltImgs));
          end
else
          if (yOnly)
                   nextFiltImgs = GCKFilterSingleStep32s_C3_Y_Only(currFiltImgs, uint16(width), bCurAlphaPos, uint16(delta_j), LRnotUD);
          else
                   nextFiltImgs = GCKFilterSingleStep32s_C3(currFiltImgs, uint16(width), bCurAlphaPos, uint16(delta_j), LRnotUD);
                   nextFiltImgs = reshape(nextFiltImgs, size(currFiltImgs));
          end
end
