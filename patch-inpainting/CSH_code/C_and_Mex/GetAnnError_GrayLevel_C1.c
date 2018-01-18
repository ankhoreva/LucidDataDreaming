#include <string.h> 
#include <mex.h>
#include <matrix.h>
#include <math.h>


int debugEnable = 0;

#define debugPrint if (debugEnable != 0) mexPrintf

/* This function computes the RMS error between two images
Source reference image type must be uint8 and must have three channel
source row and column maps images must by same size as source refernce image
source target image can be of unique size
Output image type is single precision and single channel, and is the same size
  as the source refernce image
*/

/*******************************************************************************/
/* mexFUNCTION                                                                 */
/* Gateway routine for use with MATLAB.                                        */
/*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
          float          *pOutputImage32f;
          unsigned short *pInputRowMap16u,  *pInputColMap16u;
          unsigned short *pTopLeftOrg, *pBotRightMarg, *pKernelSize;
          unsigned char  *pInputRefImage8u, *pInputTargetImage8u;
          
          unsigned short nPropRow16u, nPropCol16u;  /* Indices of propagation */
          
          int nErrorAccum, nElementSqrDiff;
          
          mxArray *pMxArray[1];
          
          int i, j, iRoi, jRoi;
          int m, n, mTarget, nTarget;
          int mOutput, nOutput;
          int nSingleChannelColNum,  nSingleChannelColNumTarget;/* Number of columns in single channel */
          int nNumOfChannelElements, nNumOfChannelElementsTarget;
          int nNumOfROIElements;
          int nFirstRow, nLastRow; /* Matlab indices */
          int nFirstCol, nLastCol; /* Matlab indices */
          int nCurIterStep, nCurIterOffset, nCurIterStepTarget, nCurIterOffsetTarget;
          int nRoiOffset, nRoiOffsetTarget;
          
          if (nrhs < 7 || nrhs > 8 || nlhs!=1)
                    mexErrMsgTxt("Usage: outputImage=GetANNError_C3(inputRefImage8u_C3, inputTargetImage8u_C3, rowMapping16u, colMapping16u, TLboundary16u, BRboundary16u, nWidth16u, debugFlag(opt));\n");
          
          if (mxGetClassID(prhs[0]) != mxUINT8_CLASS || mxGetClassID(prhs[1]) != mxUINT8_CLASS ||
                  mxGetClassID(prhs[2]) != mxUINT16_CLASS || mxGetClassID(prhs[3]) != mxUINT16_CLASS ||
                  mxGetClassID(prhs[4]) != mxUINT16_CLASS|| mxGetClassID(prhs[5]) != mxUINT16_CLASS ||
                  mxGetClassID(prhs[6]) != mxUINT16_CLASS)
                    mexErrMsgTxt("input and target images must be uint8 matrices, row and column mapping images must be a uint16 matrices, top-left and bottom-right of ROI must be a uint16 scalars and kernel size must be a uint16 scalar!");
          
          if (nrhs == 8) {
                    debugEnable = (int)mxGetScalar(prhs[7]);
          }
          else
                    debugEnable = 0;
          
          /* Get inputs */
          pInputRefImage8u    = (unsigned char*)mxGetPr(prhs[0]);
          pInputTargetImage8u = (unsigned char*)mxGetPr(prhs[1]);
          pInputRowMap16u     = (unsigned short*)mxGetPr(prhs[2]);
          pInputColMap16u     = (unsigned short*)mxGetPr(prhs[3]);
          pTopLeftOrg         = (unsigned short*)mxGetPr(prhs[4]);
          pBotRightMarg       = (unsigned short*)mxGetPr(prhs[5]);
          pKernelSize         = (unsigned short*)mxGetPr(prhs[6]);
          
          
          /* Get sizes of variables (Opposite on purpose)*/
          m = mxGetM(prhs[0]); /* Width */
          n = mxGetN(prhs[0]); /* Height */
          nSingleChannelColNum = n;
          
          mTarget = mxGetM(prhs[1]); /* Width target */
          nTarget = mxGetN(prhs[1]); /* Height target */
          nSingleChannelColNumTarget = nTarget;
          
          nNumOfChannelElements       = nSingleChannelColNum * m;
          nNumOfChannelElementsTarget = nSingleChannelColNumTarget * mTarget;
          
          /* Calc steps
          /* Create output matrix */
          mOutput = m-(*pBotRightMarg)-(*pTopLeftOrg);
          nOutput = nSingleChannelColNum-(*pBotRightMarg)-(*pTopLeftOrg);
          mOutput = m;
          nOutput = nSingleChannelColNum;
          plhs[0] = mxCreateNumericMatrix(mOutput, nOutput, mxSINGLE_CLASS, false);
          pOutputImage32f = (float*)mxGetPr(plhs[0]);
          
          /* Initialize filter parameters */
          nFirstRow = (int)(*pTopLeftOrg);
          nLastRow  = (int)m-(*pBotRightMarg);
          nFirstCol = (int)(*pTopLeftOrg);
          nLastCol  = (int)nSingleChannelColNum-(*pBotRightMarg);
          
          nNumOfROIElements = (*pKernelSize)*(*pKernelSize);
          
          for (j=nFirstCol; j<nLastCol; j++) {
                    nCurIterStep       = j*m;
                    nCurIterStepTarget = j*mTarget;
                    
                    for (i=nFirstRow; i<nLastRow; i++) {
                              nCurIterOffset = nCurIterStep+i;
                              nPropCol16u = pInputColMap16u[nCurIterOffset];
                              nPropRow16u = pInputRowMap16u[nCurIterOffset];
                              
                              nCurIterOffsetTarget = (int)((nPropRow16u-1) + (nPropCol16u-1)*mTarget); /* Translating matlab to C */
                              
                              nErrorAccum = 0;
                              for (jRoi = 0; jRoi<(*pKernelSize); jRoi++) {
                                        nRoiOffset       = nCurIterOffset + jRoi*m;
                                        nRoiOffsetTarget = nCurIterOffsetTarget + jRoi*mTarget;
                                        for (iRoi = 0; iRoi<(*pKernelSize); iRoi++) 
                                        {
                                                  nElementSqrDiff = (int)pInputRefImage8u[nRoiOffset] - (int)pInputTargetImage8u[nRoiOffsetTarget];
                                                  nErrorAccum += nElementSqrDiff*nElementSqrDiff;
                                                  nRoiOffset++;
                                                  nRoiOffsetTarget++;
                                        }
                              }
                              
                              pOutputImage32f[nCurIterOffset] = sqrt(nErrorAccum );/* / (float)nNumOfROIElements; */
                    }
          }
          
}