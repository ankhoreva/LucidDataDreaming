function [m,M] = bounds2(A,silent)
% [m,M] = bounds2(A,silent)
if ~exist('silent','var')
    silent = 1;
end
[m,M] = bounds(A(:),silent);
if nargout<2
    m = [m,M];
end