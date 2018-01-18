#include <string.h> 
#include <mex.h>
#include <matrix.h>

int debugEnable = 0;

#define debugPrint if (debugEnable != 0) mexPrintf


#define PIXEL_PTR    (pImg, i, j, nStep, type) ((type*)((mxUINT8_CLASS*)pImg+(i)*nStep)+(j))
#define PIXEL_PTR_8U (pImg, i, j, nStep) PIXEL_PTR(pImg, i, j, nStep, mxUINT8_CLASS)
#define PIXEL_PTR_16U(pImg, i, j, nStep) PIXEL_PTR(pImg, i, j, nStep, mxUINT16_CLASS)
#define PIXEL_PTR_32U(pImg, i, j, nStep) PIXEL_PTR(pImg, i, j, nStep, mxUINT32_CLASS)
#define PIXEL_PTR_64U(pImg, i, j, nStep) PIXEL_PTR(pImg, i, j, nStep, mxUINT64_CLASS)
#define PIXEL_PTR_32F(pImg, i, j, nStep) PIXEL_PTR(pImg, i, j, nStep, mxSINGLE_CLASS)
#define PIXEL_PTR_64F(pImg, i, j, nStep) PIXEL_PTR(pImg, i, j, nStep, mxDOUBLE_CLASS)

/* This function computes a DC rectangle kernel of source size for the source image 
The function does not assume zero-padded edges exist, but for reasonable results these should be considered
The result image is the rectangle DC kernel of the source image, anchored on the top-left pixel of the kernel
The size of the resulting matrix is the same as the source image
Source image type must be uint8 and must be single channel
Output image type is int16
*/

/*******************************************************************************/
/* mexFUNCTION                                                                 */
/* Gateway routine for use with MATLAB.                                        */
/*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  unsigned char* pInputImage8u;
  short*         pOutputImage16s;

  mxArray*      pIntegralImage;
  unsigned int* pIntegImgData=NULL;

  int i, j, m, n;
  int nInputImgStep, nOutputImgStep, nCurIterStep, nLastIterStep, nPlusKernelStep, nPlusKernelLastIterStep, nCurColumnShift;
  unsigned short KernelSize;
  unsigned int    nCumSumCurIter;
  
  /* for optimization */
  short* outPtrShort;
  unsigned int *inPtr1, *inPtr2, *inPtr3, *inPtr4;
  /* for optimization that is disabled */
  unsigned int *outPtrUInt;
  unsigned char *inPtr1_char;


  if (nrhs < 2 || nrhs > 3 || nlhs!=1)
    mexErrMsgTxt("Usage: outputImage=ApplyPlusKernel8u16s(inputImage8u, nWidth16u, debugFlag(opt));\n");
                                                                                                                                          
  if (mxGetClassID(prhs[0]) != mxUINT8_CLASS || mxGetClassID(prhs[1]) != mxUINT16_CLASS)
    mexErrMsgTxt("Input image must be a uint8 matrix and kernel size must be a uint16 scalar!");

  if (nrhs == 3)
  {
    debugEnable = (int)mxGetScalar(prhs[2]);
  }
  else
    debugEnable = 0;

  /* Get inputs */
  pInputImage8u = (unsigned char* )mxGetPr(prhs[0]);
  KernelSize   = *((unsigned short* )mxGetPr(prhs[1]));

  /* Get sizes of variables (Opposite on purpose)*/
  m = mxGetM(prhs[0]); /* Width */
  n = mxGetN(prhs[0]); /* Height */
   
  /* Define steps depths */
  nInputImgStep  = m;
  nOutputImgStep = m*4;
 
  /* Create Integral Image matrix */
  pIntegralImage = mxCreateNumericMatrix(m, n, mxUINT32_CLASS, false);
  pIntegImgData  = mxGetData(pIntegralImage);

  /* Create output matrix */
  plhs[0] = mxCreateNumericMatrix(m, n, mxINT16_CLASS, false);
  pOutputImage16s = (short*)mxGetPr(plhs[0]);
 

  /* Calc intergral image */
  pIntegImgData[0] = (unsigned int)pInputImage8u[0];
  for (i=1; i<m; i++)
    pIntegImgData[i] = pIntegImgData[i-1] + (unsigned int)pInputImage8u[i];
  
  for (j=1; j<n; j++)
  {
    nLastIterStep = (j-1)*m;
    nCurIterStep = j*m;
    nCumSumCurIter = 0;
    
/* This is ok but doesn't make a big difference - together with the one below
    outPtrUInt = pIntegImgData + nCurIterStep; /* unsigned int
    inPtr1_char = pInputImage8u + nCurIterStep;
    inPtr2 = pIntegImgData + nLastIterStep; /* unsigned int
*/

    for (i=0; i<m; i++)
    {
      nCumSumCurIter = nCumSumCurIter + (unsigned int)pInputImage8u[nCurIterStep+i];
      pIntegImgData[nCurIterStep+i] = pIntegImgData[nLastIterStep+i] + nCumSumCurIter;
      
/* This is ok but doesn't make a big difference
      nCumSumCurIter = nCumSumCurIter + (unsigned int)inPtr1_char[0];
      outPtrUInt[0] = inPtr2[0] + nCumSumCurIter;
      outPtrUInt++; inPtr1_char++; inPtr2++;
*/
    }
  }  
  

  /* Calc DC kernel result */
  pOutputImage16s[0] = (short)pIntegImgData[(KernelSize-1)*m+KernelSize-1];

  for (i=KernelSize; i<m; i++)
    pOutputImage16s[i-KernelSize+1] = 
              (short)pIntegImgData[i + (KernelSize-1)*m] - 
              (short)pIntegImgData[i-KernelSize + (KernelSize-1)*m];

  for (j=KernelSize; j<n; j++)
    pOutputImage16s[(j-KernelSize+1)*m] = 
              (short)pIntegImgData[j*m + KernelSize-1] - 
              (short)pIntegImgData[(j-KernelSize)*m + KernelSize-1];


  for (j=KernelSize; j<n; j++)
  {
    nCurIterStep = j*m;

    nPlusKernelLastIterStep = (j-KernelSize)*m;
    nPlusKernelStep         = (j-KernelSize+1)*m;
    
    outPtrShort = pOutputImage16s + nPlusKernelStep+1;
    inPtr1 = pIntegImgData + nCurIterStep+KernelSize;
    inPtr2 = pIntegImgData + nPlusKernelLastIterStep+KernelSize;
    inPtr3 = pIntegImgData + nCurIterStep;
    inPtr4 = pIntegImgData + nPlusKernelLastIterStep;

    for (i=KernelSize; i<m; i++)
    {
/* original
      nCurColumnShift = i-KernelSize;
      pOutputImage16s[nPlusKernelStep+nCurColumnShift+1] = 
         (short)pIntegImgData[nCurIterStep+i] 
        -(short)pIntegImgData[nPlusKernelLastIterStep+i] 
        -(short)pIntegImgData[nCurIterStep+nCurColumnShift]
        +(short)pIntegImgData[nPlusKernelLastIterStep+nCurColumnShift];
*/
      /* optimized */
      outPtrShort[0] = (short)(inPtr1[0] - inPtr2[0] - inPtr3[0] + inPtr4[0]);
      outPtrShort++; inPtr1++; inPtr2++; inPtr3++; inPtr4++;
    }
    
    
    
    
    
  }  
}