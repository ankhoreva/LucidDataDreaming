function [m,M]=bounds(A,silent)
if (nargin<2)
    silent = 0;
end
m = min(A);
M = max(A);
if ((~isempty(silent)) && ~silent)
    disp(['< ' num2str([m M]) ' >']);
end