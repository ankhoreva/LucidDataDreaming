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

/* This function computes the next step in a series of GCK kernels
The function does not assume zero-padded edges exist, but erroneous results will be produced if these are not considered
The size of the resulting matrix is the same as the source image
Source image type must be int16 and must have three channel
bCurAlphaPos - Bollean defining if current kernel is positive alpha-related relative to last kernel
nDelta - delta between current and last kernels
bHorizMovement - Bollean defining if current step's delta is horizontal or vertical 
Output image type is int16 and single channel; Number of columns is three times the number of columns in a single channel of the source image
*/

/*******************************************************************************/
/* mexFUNCTION                                                                 */
/* Gateway routine for use with MATLAB.                                        */
/*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  short *pInputImage16s, *ptrIn1, *ptrIn2, *ptrIn3, *beginIn;
  short *pOutputImage16s, *ptrOut1, *ptrOut2, *ptrOut3, *beginOut;

  bool*           bCurAlphaPos;
  bool*           bHorizMovement;
  unsigned short* pDeltaStep;
  unsigned short* pKernelSize;

  mwSize ndim, dims;

  int i, j, m, n;
  int nSingleChannelColNum;/* Number of columns in single channel */
  int nFirstRow, nLastRow; /* Matlab indices */
  int nFirstCol, nLastCol; /* Matlab indices */
  int nRowDeltaStep, nColDelta;
  int nCurIterStep, nCurIterDetlaStep, nSecChannelStep, nSecIterDetlaStep, nThirdChannelStep, nThirdIterDetlaStep;
  int times;
  
  unsigned int    nCumSumCurIter;
  int diff;


  if (nrhs < 5 || nrhs > 6 || nlhs!=1)
    mexErrMsgTxt("Usage: outputImage=GCKFilterSingleStep16s_C3(inputImage16s, nWidth16u, bCurAlphaPos, nDelta, bHorizMovement, debugFlag(opt));\n");
                                                                                                                                          
  if (mxGetClassID(prhs[0]) != mxINT16_CLASS || mxGetClassID(prhs[1]) != mxUINT16_CLASS ||
      mxGetClassID(prhs[2]) != mxLOGICAL_CLASS || mxGetClassID(prhs[3]) != mxUINT16_CLASS ||
      mxGetClassID(prhs[4]) != mxLOGICAL_CLASS)
    mexErrMsgTxt("Input image must be a int16 matrix, kernel size must be a uint16 scalar, current alpha related kernel must be boolean, the delta step must be uint16, and the horizontal movement must be boolean!");

  if (nrhs == 6)
  {
    debugEnable = (int)mxGetScalar(prhs[6]);
  }
  else
    debugEnable = 0;

  /* Get inputs */
  pInputImage16s = (short*)mxGetPr(prhs[0]);
  pKernelSize    = (unsigned short*)mxGetPr(prhs[1]);
  bCurAlphaPos   = (bool*)mxGetPr(prhs[2]);
  pDeltaStep     = (unsigned short*)mxGetPr(prhs[3]);
  bHorizMovement = (bool*)mxGetPr(prhs[4]);

  /* Get sizes of variables (Opposite on purpose)*/
  m = mxGetM(prhs[0]); /* Width */
  n = mxGetN(prhs[0]); /* Height */
  nSingleChannelColNum = n/3;   
  

  /* Create output matrix */
  plhs[0] = mxCreateNumericMatrix(m, n, mxINT16_CLASS, false);
  pOutputImage16s = (short*)mxGetPr(plhs[0]);
  

  /* Initialize filter parameters */
  if (*bHorizMovement)
  {
    nFirstRow = 1;
    nLastRow  = m;
    nFirstCol = *pKernelSize; 
    nLastCol  = nSingleChannelColNum-*pKernelSize+1; /* added + 1 */

    nRowDeltaStep = (*pDeltaStep) * m;
    nColDelta     = 0;
  }
  else
  {
    nFirstRow = *pKernelSize;
    nLastRow  = m-*pKernelSize+1;
    nFirstCol = 1; 
    nLastCol  = nSingleChannelColNum; /* added + 1 */

    nRowDeltaStep = 0;
    nColDelta     = *pDeltaStep;
  }
  
  /* optimization related */
/*   nLastCol = nLastCol + 1;
/*   nLastRow = nLastRow + 1; */
  diff = nColDelta + nRowDeltaStep;
  beginIn = pInputImage16s+nFirstRow-nColDelta;
  beginOut = pOutputImage16s+nFirstRow-nColDelta;
    
  /* Filter single step */
  if (*bCurAlphaPos)
  {
    for (j=nFirstCol; j<nLastCol; j++)
    {
      nCurIterStep        = j*m;
      nCurIterDetlaStep   = nCurIterStep - nRowDeltaStep; 

      nSecChannelStep     = (j+nSingleChannelColNum)*m;
      nSecIterDetlaStep   = nSecChannelStep - nRowDeltaStep; 

      nThirdChannelStep   = (j+2*nSingleChannelColNum)*m;
      nThirdIterDetlaStep = nThirdChannelStep - nRowDeltaStep; 

      ptrIn1 = beginIn + nCurIterDetlaStep;
      ptrOut1 = beginOut + nCurIterDetlaStep;
      ptrIn2 = beginIn + nSecIterDetlaStep;
      ptrOut2 = beginOut + nSecIterDetlaStep;
      ptrIn3 = beginIn + nThirdIterDetlaStep;
      ptrOut3 = beginOut + nThirdIterDetlaStep;      
      
      times = nLastRow-nFirstRow;
      for (i=times ; i--; )
/*      for (i=nFirstRow; i<nLastRow; i++) /* this is the same but slower */
      {       
        ptrOut1[diff] = ptrIn1[diff] + ptrIn1[0] + ptrOut1[0];
        ptrOut2[diff] = ptrIn2[diff] + ptrIn2[0] + ptrOut2[0];
        ptrOut3[diff] = ptrIn3[diff] + ptrIn3[0] + ptrOut3[0];

        ptrOut1++; ptrIn1++;
        ptrOut2++; ptrIn2++;
        ptrOut3++; ptrIn3++;

/* Original version 
/*        pOutputImage16s[nCurIterStep+i] = pInputImage16s[nCurIterStep+i] + 
/*           pInputImage16s[nCurIterDetlaStep+i-nColDelta] +pOutputImage16s[nCurIterDetlaStep+i-nColDelta];

/*        pOutputImage16s[nSecChannelStep+i] = pInputImage16s[nSecChannelStep+i] + 
/*           pInputImage16s[nSecIterDetlaStep+i-nColDelta] +pOutputImage16s[nSecIterDetlaStep+i-nColDelta];

/*        pOutputImage16s[nThirdChannelStep+i] = pInputImage16s[nThirdChannelStep+i] + 
/*           pInputImage16s[nThirdIterDetlaStep+i-nColDelta] +pOutputImage16s[nThirdIterDetlaStep+i-nColDelta]; */
     }
    }
  }
  else
  {
    for (j=nFirstCol; j<nLastCol; j++)
    {
      nCurIterStep      = j*m;
      nCurIterDetlaStep = nCurIterStep - nRowDeltaStep; 

      nSecChannelStep     = (j+nSingleChannelColNum)*m;
      nSecIterDetlaStep   = nSecChannelStep - nRowDeltaStep; 

      nThirdChannelStep   = (j+2*nSingleChannelColNum)*m;
      nThirdIterDetlaStep = nThirdChannelStep - nRowDeltaStep; 

      ptrIn1 = beginIn + nCurIterDetlaStep;
      ptrOut1 = beginOut + nCurIterDetlaStep;
      ptrIn2 = beginIn + nSecIterDetlaStep;
      ptrOut2 = beginOut + nSecIterDetlaStep;
      ptrIn3 = beginIn + nThirdIterDetlaStep;
      ptrOut3 = beginOut + nThirdIterDetlaStep;      

      times = nLastRow-nFirstRow;
      for (i=times ; i--; )
/*      for (i=nFirstRow; i<nLastRow; i++) /* this is the same but slower */
      {
        ptrOut1[diff] = ptrIn1[diff] - ptrIn1[0] - ptrOut1[0];
        ptrOut2[diff] = ptrIn2[diff] - ptrIn2[0] - ptrOut2[0];
        ptrOut3[diff] = ptrIn3[diff] - ptrIn3[0] - ptrOut3[0];
        
        ptrOut1++; ptrIn1++;
        ptrOut2++; ptrIn2++;
        ptrOut3++; ptrIn3++;
      
/* Original version
/*        pOutputImage16s[nCurIterStep+i] = pInputImage16s[nCurIterStep+i] - 
/*           pInputImage16s[nCurIterDetlaStep+i-nColDelta] -pOutputImage16s[nCurIterDetlaStep+i-nColDelta];

/*        pOutputImage16s[nSecChannelStep+i] = pInputImage16s[nSecChannelStep+i] - 
/*           pInputImage16s[nSecIterDetlaStep+i-nColDelta] -pOutputImage16s[nSecIterDetlaStep+i-nColDelta];

/*        pOutputImage16s[nThirdChannelStep+i] = pInputImage16s[nThirdChannelStep+i] - 
/*           pInputImage16s[nThirdIterDetlaStep+i-nColDelta] -pOutputImage16s[nThirdIterDetlaStep+i-nColDelta]; */

		}
    }
  }
}