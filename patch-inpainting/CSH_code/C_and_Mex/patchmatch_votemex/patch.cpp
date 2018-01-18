
#include "patch.h"
#include <math.h>

static char AdobePatentID_P876E1[] = "AdobePatentID=\"P876E1\"";

template<>
int fast_patch_dist<1, 0>(int *adata, BITMAP *b, int bx, int by, int maxval, Params *p) {
  //if (IS_MASK && bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int *row2 = ((int *) b->line[by])+bx;
  {
    unsigned int c1 = adata[0];
    unsigned int c2 = row2[0];
    int dr = (c1&255)-(c2&255);
    int dg = ((c1>>8)&255)-((c2>>8)&255);
    int db = (c1>>16)-(c2>>16);
    return dr*dr+dg*dg+db*db;
  }
}

template<>
int fast_patch_dist<2, 0>(int *adata, BITMAP *b, int bx, int by, int maxval, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 2; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    adata += 2;
  }
  return ans;
}

/// MY NEW FUNCTION!!! ///
// flattenedKernels mat is a width^2 by width^2 mat of the form: [g(1) g(2) g(3) ... g(w^2)], where g(i) is a flattened width^2 kernel
//                                                                      relevant to the ith pixel (row-by-row) of the patch
// distances is a width by width matrix, which holds the 'gaussian'-weighted distances between the 2 patches, using different weighting 
// for each pixel in the patch being in the center
int  weighted_fast_patch_dist(BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int width, 
                                                                                    double *flattenedKernels, double *distanceWeights, int factor, int print, int cutoff) 
{
          if (print)
                    mexPrintf("\n-----  in weighted_fast_patch_dist  -----\n");
          double distances[64];
          memset((void *) distances, 0, sizeof(double) * 64);          
          int kernelEntry = 0;
          int width2 = width*width;
          int debugInd = 0;
          int debugArr[64];
          int sumDist2 = 0;
          for (int dy = 0; dy < width; dy++) 
          {
                    int *rowA = ((int *) a->line[ay+dy])+ax;
                    int *rowB = ((int *) b->line[by+dy])+bx;
                    for (int dx = 0; dx < width; dx++) 
                    {             
                              unsigned int c1 = rowA[dx];
                              unsigned int c2 = rowB[dx];
                              int dr = (c1&255)-(c2&255);
                              int dg = ((c1>>8)&255)-((c2>>8)&255);
                              int db = (c1>>16)-(c2>>16);            
                              int dist2 = dr*dr+dg*dg+db*db;
                              sumDist2 += dist2;
                              debugArr[debugInd++] = dist2; // the regular square distance
                              // weighted distances, according to the possible width^2 locations of the pixel in the patch
                              for (int ind = 0; ind < width2 ; ind++) // this loop covers one row of flattenedKernels at a time (and all the rows of distances)
                                        distances[ind] += flattenedKernels[kernelEntry++] * dist2;
                    }
          }
          
          double exponent;
          if (print)
                    mexPrintf("\n~~~   Printing the width^2 distance weights  ~~~~~~\n");
          // after finding the wieghted distances, we wish to get a gaussian decaying weight on the contribution of the pixel vote
          for (int ind = 0; ind < width2 ; ind++) // this loop covers one row of flattenedKernels at a time (and all the rows of distances)
          {
                    if (distances[ind] < cutoff)
                   {
                              exponent = (distances[ind]/factor)*(distances[ind]/factor);
                              distanceWeights[ind] = exp(-exponent);
                    }
                    else
                              distanceWeights[ind] = 0;
                    
                    if (print && (ind%10 ==1)) 
                               mexPrintf("Ind: %d out of width2: %d, distanceWeights (result)  %.4f (distances %.4f)  (over) factor:  %d (is) exponent: %f, \n",
                                                                        ind, width2,distanceWeights[ind], distances[ind],factor,exponent);
          }          
          
          if (print) {
                    int ind;
                     mexPrintf("\n~~~   Dist Array - the wieghted width^2 distances ~~~~~~\n");
                    ind = 0;
                    for (int i = 0; i < width; i++) {
                              mexPrintf("~~~~~~~  row %d ~~~~~~~~~\n", i);
                              for (int j = 0; j < width; j++)
                                        mexPrintf("%d ", debugArr[ind++]);
                    }
                     mexPrintf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                     mexPrintf("\n~~~  Weight Array - the resulting weightes for voting  ~~~~~~\n");
                    ind = 0;
                    for (int i = 0; i < width; i++) {
                              mexPrintf("~~~~~~~  row %d ~~~~~~~~~\n", i);
                              for (int j = 0; j < width; j++)
                                        mexPrintf("%.4f (%.4f) ", distanceWeights[ind], distances[ind++]);
                    }
                     mexPrintf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
          }
          if (print)
                    mexPrintf("\n-----  finished weighted_fast_patch_dist  -----\n");

//           mexPrintf("\n~~~   sumDist2 : %d  ~~~~~~\n", sumDist2);

            return sumDist2;
}

// this returns a SINGLE gaussian center-weighted Euclidean distance
int  gaussian_fast_patch_dist(BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int width, 
							  double *flattenedKernel, double &distanceWeight, int factor, int print,int cutoff) 
{
          double distance = 0;
          int kernelEntry = 0;
          int width2 = width*width;
//           int debugInd = 0;
//           int debugArr[64];
          int sumDist2 = 0;
          for (int dy = 0; dy < width; dy++) 
          {
                    int *rowA = ((int *) a->line[ay+dy])+ax;
                    int *rowB = ((int *) b->line[by+dy])+bx;
//                     if (print)
//                               mexPrintf("\nline-------- dy: %d, ay: %d, ax: %d, by: %d, bx: %d\n ", dy, ay, ax, by, bx);

                    for (int dx = 0; dx < width; dx++) 
                    {             
                              unsigned int c1 = rowA[dx];
                              unsigned int c2 = rowB[dx];
//                               if (print)
//                                         mexPrintf("c1: %d, c2: %d ", c1, c2);
                              int dr = (c1&255)-(c2&255);
                              int dg = ((c1>>8)&255)-((c2>>8)&255);
                              int db = (c1>>16)-(c2>>16);            
                              int dist2 = dr*dr+dg*dg+db*db;
                              sumDist2 += dist2;
//                               debugArr[debugInd++] = dist2;
//                               for (int ind = 0; ind < width2 ; ind++) // this loop covers one row of flattenedKernels at a time (and all the rows of distances)
                               distance += flattenedKernel[kernelEntry++] * dist2;
                    }
//                     if (print)
//                               mexPrintf("\n");

          }
          
          double exponent;
//           for (int ind = 0; ind < width2 ; ind++) // this loop covers one row of flattenedKernels at a time (and all the rows of distances)
//           {
          if (distance < cutoff)
          {
                    exponent = (distance/factor)*(distance/factor);
                    distanceWeight = exp(-exponent);
          }
          else
                    distanceWeight = 0;
          
//                     if (print) 
//                                mexPrintf("PRINT  %.4f (%.4f) exponent: %f \n", distanceWeights[ind], distances[ind],exponent);
//           }          
          
          if (print) 
           {
                    mexPrintf("gaussian_fast_patch_dist - sumDist2: %d, distanceWeight: %.4f  exponent: %.4f = w_distance: %.4f  (over) fact: %d\n",
                            sumDist2, distanceWeight, exponent, distance,factor);
          }

          
//           mexPrintf("\n~~~   sumDist2 : %d  ~~~~~~\n", sumDist2);

            return sumDist2;
}


template<>
int fast_patch_dist<3, 0>(int *adata, BITMAP *b, int bx, int by, int maxval, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 3; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    adata += 3;
  }
  return ans;
}

template<>
int fast_patch_dist<4, 0>(int *adata, BITMAP *b, int bx, int by, int maxval, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 4; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    adata += 4;
  }
  return ans;
}

template<>
int fast_patch_dist<5, 0>(int *adata, BITMAP *b, int bx, int by, int maxval, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 5; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[4];
      unsigned int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    adata += 5;
  }
  return ans;
}

template<>
int fast_patch_dist<6, 0>(int *adata, BITMAP *b, int bx, int by, int maxval, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 6; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[4];
      unsigned int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[5];
      unsigned int c2 = row2[5];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    adata += 6;
  }
  return ans;
}

template<>
int fast_patch_dist<7, 0>(int *adata, BITMAP *b, int bx, int by, int maxval, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  
  for (int dy = 0; dy < 7; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[4];
      unsigned int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[5];
      unsigned int c2 = row2[5];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      unsigned int c1 = adata[6];
      unsigned int c2 = row2[6];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    adata += 7;
  }
  return ans;
}

template<>
int fast_patch_nobranch<1, 0>(int *adata, BITMAP *b, int bx, int by, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int *row2 = ((int *) b->line[by])+bx;
  {
    unsigned int c1 = adata[0];
    unsigned int c2 = row2[0];
    int dr = (c1&255)-(c2&255);
    int dg = ((c1>>8)&255)-((c2>>8)&255);
    int db = (c1>>16)-(c2>>16);
    return dr*dr+dg*dg+db*db;
  }
}

template<>
int fast_patch_nobranch<2, 0>(int *adata, BITMAP *b, int bx, int by, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 2; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    adata += 2;
  }
  return ans;
}

template<>
int fast_patch_nobranch<3, 0>(int *adata, BITMAP *b, int bx, int by, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 3; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    adata += 3;
  }
  return ans;
}

template<>
int fast_patch_nobranch<4, 0>(int *adata, BITMAP *b, int bx, int by, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 4; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    adata += 4;
  }
  return ans;
}

template<>
int fast_patch_nobranch<5, 0>(int *adata, BITMAP *b, int bx, int by, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 5; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[4];
      unsigned int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    adata += 5;
  }
  return ans;
}

template<>
int fast_patch_nobranch<6, 0>(int *adata, BITMAP *b, int bx, int by, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 6; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[4];
      unsigned int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[5];
      unsigned int c2 = row2[5];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    adata += 6;
  }
  return ans;
}

template<>
int fast_patch_nobranch<7, 0>(int *adata, BITMAP *b, int bx, int by, Params *p) {
  //if (bmask && ((int *) bmask->line[by])[bx]) { return INT_MAX; }
  int ans = 0;
  for (int dy = 0; dy < 7; dy++) {
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      unsigned int c1 = adata[0];
      unsigned int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[1];
      unsigned int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[2];
      unsigned int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[3];
      unsigned int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[4];
      unsigned int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[5];
      unsigned int c2 = row2[5];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    {
      unsigned int c1 = adata[6];
      unsigned int c2 = row2[6];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
    }
    adata += 7;
  }
  return ans;
}

template<>
int patch_dist_ab<1, 0, 0>(Params *p, BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int maxval, RegionMasks *region_masks) {
  int *row1 = ((int *) a->line[ay])+ax;
  int *row2 = ((int *) b->line[by])+bx;
  {
    int c1 = row1[0];
    int c2 = row2[0];
    int dr = (c1&255)-(c2&255);
    int dg = ((c1>>8)&255)-((c2>>8)&255);
    int db = (c1>>16)-(c2>>16);
    return dr*dr+dg*dg+db*db;
  }
}

template<>
int patch_dist_ab<2, 0, 0>(Params *p, BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int maxval, RegionMasks *region_masks) {
  int ans = 0;
  for (int dy = 0; dy < 2; dy++) {
    int *row1 = ((int *) a->line[ay+dy])+ax;
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      int c1 = row1[0];
      int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[1];
      int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
  }
  return ans;
}

template<>
int patch_dist_ab<3, 0, 0>(Params *p, BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int maxval, RegionMasks *region_masks) {
  int ans = 0;
  for (int dy = 0; dy < 3; dy++) {
    int *row1 = ((int *) a->line[ay+dy])+ax;
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      int c1 = row1[0];
      int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[1];
      int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[2];
      int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
  }
  return ans;
}

template<>
int patch_dist_ab<4, 0, 0>(Params *p, BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int maxval, RegionMasks *region_masks) {
  int ans = 0;
  for (int dy = 0; dy < 4; dy++) {
    int *row1 = ((int *) a->line[ay+dy])+ax;
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      int c1 = row1[0];
      int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[1];
      int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[2];
      int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[3];
      int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
  }
  return ans;
}

template<>
int patch_dist_ab<5, 0, 0>(Params *p, BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int maxval, RegionMasks *region_masks) {
  int ans = 0;
  for (int dy = 0; dy < 5; dy++) {
    int *row1 = ((int *) a->line[ay+dy])+ax;
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      int c1 = row1[0];
      int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[1];
      int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[2];
      int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[3];
      int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[4];
      int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
  }
  return ans;
}

template<>
int patch_dist_ab<6, 0, 0>(Params *p, BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int maxval, RegionMasks *region_masks) {
  int ans = 0;
  for (int dy = 0; dy < 6; dy++) {
    int *row1 = ((int *) a->line[ay+dy])+ax;
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      int c1 = row1[0];
      int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[1];
      int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[2];
      int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[3];
      int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[4];
      int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[5];
      int c2 = row2[5];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
  }
  return ans;
}

template<>
int patch_dist_ab<7, 0, 0>(Params *p, BITMAP *a, int ax, int ay, BITMAP *b, int bx, int by, int maxval, RegionMasks *region_masks) {
  int ans = 0;
  for (int dy = 0; dy < 7; dy++) {
    int *row1 = ((int *) a->line[ay+dy])+ax;
    int *row2 = ((int *) b->line[by+dy])+bx;
    {
      int c1 = row1[0];
      int c2 = row2[0];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[1];
      int c2 = row2[1];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[2];
      int c2 = row2[2];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[3];
      int c2 = row2[3];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[4];
      int c2 = row2[4];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[5];
      int c2 = row2[5];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
    {
      int c1 = row1[6];
      int c2 = row2[6];
      int dr = (c1&255)-(c2&255);
      int dg = ((c1>>8)&255)-((c2>>8)&255);
      int db = (c1>>16)-(c2>>16);
      ans += dr*dr+dg*dg+db*db;
      if (ans > maxval) { return ans; }
    }
  }
  return ans;
}
