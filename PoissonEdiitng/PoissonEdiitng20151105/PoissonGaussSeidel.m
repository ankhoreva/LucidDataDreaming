% PoissonGaussSeidel reconstructs an image based on the Poisson equation
%
% dst = PoissonGaussSeidel(src, Fh, Fv, msk, itr, th, verbose)
%
%
%Output parameter:
% dst: reconstructed image
%
%
%Input parameters:
% src: initial image
% Fh: forward horizontal difference map
% Fv: forward vertical difference map
% msk: pixels whose value is greater than zero are processed
% itr (optional): maximum iteration (default: 1024)
% th (optional): stopping criteria (default: 1E-3)
% verbose (optional): if true, display at each iteration (default: false)
%
%
%Example:
% X = double(imread('img.jpg'));
% msk = ones(size(img));
% msk(1,:,:) = 0;
% msk(:,1,:) = 0;
% msk(size(img,1),:,:) = 0;
% msk(:,size(img,2),:) = 0;
% [Fh Fv] = imgrad(X);
% Fh = Fh * 2;
% Y = PoissonGaussSeidel(X, Fh, Fv, msk);
%
%
%Version: 20120619

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Poisson Image Reconstruction by Gauss-Seidel Algorithm   %
%                                                          %
% Copyright (C) 2012 Masayuki Tanaka. All rights reserved. %
%                    mtanaka@ctrl.titech.ac.jp             %
%                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function dst = PoissonGaussSeidel(src, Fh, Fv, msk, itr, th, verbose)

if( nargin < 5 )
 itr = 1024;
end

if( nargin < 6 )
 th = 1E-3;
end

if( nargin < 7 )
 verbose = false;
end

K=[0,1,0;1,0,1;0,1,0];
lap = grad2lap(Fh,Fv);

df0 = 1E32;
dst = src;
dst0 = dst;
for i = 1:itr
 
 row = 1;

 col = 1;
 for cha=1:size(src,3)
  if( msk(row,col,cha) > 0 )
   d = ( lap(row,col,cha) + dst(row+1,col,cha) + dst(row,col+1,cha) ) / 2 - dst(row,col,cha);
   dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
  end
 end
 
 for col=2:size(src,2)-1
  for cha=1:size(src,3)
   if( msk(row,col,cha) > 0 )
    d = ( lap(row,col,cha) + dst(row+1,col,cha) + dst(row,col-1,cha) + dst(row,col+1,cha) ) / 3 - dst(row,col,cha);
    dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
   end
  end
 end

 col = size(src,2);
 for cha=1:size(src,3)
  if( msk(row,col,cha) > 0 )
   d = ( lap(row,col,cha) + dst(row+1,col,cha) + dst(row,col-1,cha) ) / 2 - dst(row,col,cha);
   dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
  end
 end
 
 for row=2:size(src,1)-1
  
  col = 1;
  for cha=1:size(src,3)
   if( msk(row,col,cha) > 0 )
    d = ( lap(row,col,cha) + dst(row+1,col,cha) + dst(row-1,col,cha) + dst(row,col+1,cha) ) / 3 - dst(row,col,cha);
    dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
   end
  end
  
  for col=2:size(src,2)-1
   for cha=1:size(src,3)
    if( msk(row,col,cha) > 0 )
     d = ( lap(row,col,cha) + dst(row+1,col,cha) + dst(row-1,col,cha) + dst(row,col-1,cha) + dst(row,col+1,cha) ) / 4 - dst(row,col,cha);
     dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
    end
   end
  end
  
  col = size(src,2);
  for cha=1:size(src,3)
   if( msk(row,col,cha) > 0 )
    d = ( lap(row,col,cha) + dst(row+1,col,cha) + dst(row-1,col,cha) + dst(row,col-1,cha) ) / 3 - dst(row,col,cha);
    dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
   end
  end

 end

 row = size(src,1);

 col = 1;
 for cha=1:size(src,3)
  if( msk(row,col,cha) > 0 )
   d = ( lap(row,col,cha) + dst(row-1,col,cha) + dst(row,col+1,cha) ) / 2 - dst(row,col,cha);
   dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
  end
 end

 for col=2:size(src,2)-1
  for cha=1:size(src,3)
   if( msk(row,col,cha) > 0 )
    d = ( lap(row,col,cha) + dst(row-1,col,cha) + dst(row,col-1,cha) + dst(row,col+1,cha) ) / 3 - dst(row,col,cha);
    dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
   end
  end
 end

 col = size(src,2);
 for cha=1:size(src,3)
  if( msk(row,col,cha) > 0 )
   d = ( lap(row,col,cha) + dst(row-1,col,cha) + dst(row,col-1,cha) ) / 2 - dst(row,col,cha);
   dst( row, col, cha ) = dst( row, col, cha ) + 1.9 * d;
  end
 end

 dif = abs(dst-dst0);
 df = max(dif(:));
 
 if( verbose )
  fprintf('%d %g %g\n',i, df, abs(df0 - df)/df0);
 end
 
 if( abs(df0 - df)/df0 < th )
  break;
 end
 dst0 = dst;
 df0 = df;
end

function lap = grad2lap(Fh, Fv)
lap = circshift(Fh,[0,1]) + circshift(Fv,[1,0]) - Fh - Fv;
