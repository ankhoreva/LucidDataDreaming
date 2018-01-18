/* % types: hTables_B is uint32
/* %%            MexMappingFunction(binMapForUse,d1,d2); uint32 = (uint32,int16,int16)
/* %                bins_A = binMapForUse(d1); */

#include <string.h> 
#include <mex.h>
#include <matrix.h>

/*******************************************************************************/
/* mexFUNCTION                                                                 */
/* Gateway routine for use with MATLAB.                                        */
/*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
          
          unsigned int *bins_A, *bins_B; /* outputs */
          unsigned int *binMapForUse; /* input1 */
          short *d1, *d2; /* inputs 2 and 3 */
          int i,m,n,frameSize;
                    
          /* Get inputs */
          binMapForUse = (unsigned int *)mxGetPr(prhs[0]);         
          d1 = (short *)mxGetPr(prhs[1]);
          d2 = (short *)mxGetPr(prhs[2]);
          
          /* Get sizes of variables (image A)*/
          m = mxGetM(prhs[1]); /* Width */
          n = mxGetN(prhs[1]); /* Height */
          frameSize = m*n;
          
           /* Create output matrices */
          plhs[0] = mxCreateNumericMatrix(m, n, mxUINT32_CLASS, false);
          bins_A = (unsigned int*)mxGetPr(plhs[0]);
                    
          for (i = 0; i < frameSize; i++)
                    bins_A[i] = binMapForUse[d1[i]-1];
          
          /* Get sizes of variables (image B)*/
          m = mxGetM(prhs[2]); /* Width */
          n = mxGetN(prhs[2]); /* Height */
          frameSize = m*n;
          
          plhs[1] = mxCreateNumericMatrix(m, n, mxUINT32_CLASS, false);
          bins_B = (unsigned int*)mxGetPr(plhs[1]);
              
          for (i = 0; i < frameSize; i++)
                    bins_B[i] = binMapForUse[d2[i]-1];                    
          
}

          
          
