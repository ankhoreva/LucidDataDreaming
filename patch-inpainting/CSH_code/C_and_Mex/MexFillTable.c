/* % types: hTables_B is uint32
/* % MexFillArray(hTables_B,indices_B_flat,...
/*                                              uint16(hashBits),uint16(hB),uint16(wB),uint16(indices_offset)); */

#include <string.h> 
#include <mex.h>
#include <matrix.h>

/*******************************************************************************/
/* mexFUNCTION                                                                 */
/* Gateway routine for use with MATLAB.                                        */
/*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
          
           unsigned int *hTables_B, *indices_B_flat ;
           unsigned int entry;
           unsigned int *localTables;

          int i, first,last;
          int tableSize;
          unsigned short hashBits, hB, wB, indices_offset;
          char *hashPtrs;
          
          /* Get inputs */
          hTables_B = (unsigned int *)mxGetPr(prhs[0]);         
          indices_B_flat = (unsigned int *)mxGetPr(prhs[1]);
          hashBits = (unsigned short)mxGetScalar(prhs[2]);
          hB = (unsigned short)mxGetScalar(prhs[3]);
          wB = (unsigned short)mxGetScalar(prhs[4]);
          indices_offset = (unsigned short)mxGetScalar(prhs[5]);
          
          tableSize = (1<<hashBits);
          first = hB;
          last = hB*wB - hB;
        
/*           mexPrintf(">> hashBits: %d,hB: %d,wB: %d,indices_offset: %d, tableSize: %d \n",
/*                   hashBits,hB,wB,indices_offset,tableSize);   */               
         
          hashPtrs = malloc(tableSize * sizeof (char));
          
          memset(hashPtrs, 0, tableSize * sizeof (char));
          localTables = hTables_B;
          indices_B_flat = indices_B_flat + indices_offset;
          
          for (i = first; i < last; i++) {
                    entry = indices_B_flat[i] - 1; /* -1 from matlab to c; */
                    localTables[entry + hashPtrs[entry]*tableSize] = i+1; /* + 1 from c to matlab */
                    hashPtrs[entry] = 1;
          }       
          
          free(hashPtrs);
}

          
          
