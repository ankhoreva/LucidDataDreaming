function Mat = BoundBy(Mat,minVal,maxVal)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Mat = min(maxVal,max(minVal,Mat));