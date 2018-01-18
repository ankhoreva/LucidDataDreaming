#include <string.h>

#include <mex.h>
#include <matrix.h>
#include <math.h>

int DoIt(short *mCurrFiltersImg , short *mCurrFiltersImgTarget,
                        unsigned int A_FiltersPtr, unsigned int B_FiltersPtr)
{
          int nDiffSqr32s;
          nDiffSqr32s = (int)(mCurrFiltersImg[A_FiltersPtr] - mCurrFiltersImgTarget[B_FiltersPtr]);
          return nDiffSqr32s * nDiffSqr32s;
}

void CalcSqrDifferenceAndTakeBest( short *mCurrFiltersImg, short *mCurrFiltersImgTarget,
        unsigned int **pCurrBestError32u, unsigned int **pCurrBestMapping32u, unsigned int nCurrCandMapping32u,
        unsigned int nCurIterOffset32u , unsigned int nKernels) 
{
          ///// declarations     
          unsigned int nCurError32u , ReminderBestError;
          int nDiffSqr32s;
          int k;
          unsigned int A_FiltersPtr , B_FiltersPtr;
         
          if (*pCurrBestMapping32u[0] == nCurrCandMapping32u)
				return;
          
          A_FiltersPtr = nKernels * nCurIterOffset32u;
          B_FiltersPtr = nKernels * nCurrCandMapping32u;
		  ReminderBestError = *pCurrBestError32u[0];
          // first WH kernel (DC)
          nCurError32u = DoIt(mCurrFiltersImg,mCurrFiltersImgTarget,A_FiltersPtr, B_FiltersPtr);
          if (nCurError32u > ReminderBestError)
             return;
          
          A_FiltersPtr++; B_FiltersPtr++;
		  ReminderBestError -= nCurError32u;
          // all the rest (in pairs)
          for (k = 1; (k < nKernels-1); k = k + 2)
          {
                nCurError32u = DoIt(mCurrFiltersImg,mCurrFiltersImgTarget,A_FiltersPtr, B_FiltersPtr);
                A_FiltersPtr++; B_FiltersPtr++;
                nCurError32u += DoIt(mCurrFiltersImg,mCurrFiltersImgTarget,A_FiltersPtr, B_FiltersPtr);
                A_FiltersPtr++; B_FiltersPtr++;
                if (nCurError32u > ReminderBestError)
                      return;
				ReminderBestError -= nCurError32u;
          }          
          if ((nKernels & 1) == 0) //Even number of kernels, check lust o
          {
                nCurError32u = DoIt(mCurrFiltersImg,mCurrFiltersImgTarget,A_FiltersPtr, B_FiltersPtr);
                if (nCurError32u > ReminderBestError)
                      return;
          }
          
          *pCurrBestError32u[0]   = (*pCurrBestError32u[0] - ReminderBestError);
          *pCurrBestMapping32u[0] = nCurrCandMapping32u;          
}


/* This function performs propagation by neighbours of NN mapping
 * Error output image type is uint32 and single channel
 * Row mapping output image is uint16 and single channel
 * Column mapping output image is uint16 and single channel
 */

/*******************************************************************************/
/* mexFUNCTION                                                                 */
/* Gateway routine for use with MATLAB.                                        */
/*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
          unsigned int   *pBestErrorsImg32u, *pCodebookImgA32u, *pCodebookImgB32u, *pBestMapping32u, *pHashTableImgB32u, *pHashTableImgA32u;
          unsigned short *pHashsNoe16u, *pSequencyOrder16u;
          bool           *pDownwardFlag;
          
          short          *mCurrFiltersImg, *mCurrFiltersImgTarget;
          
          unsigned int   *pCurrBestError32u, *pCurrBestMapping32u;
         
          
          unsigned int  nCurrTypeHashVal32u, nCurrCandMapping32u, nCurrTypeMapping32u;
          unsigned int nCurrLocA32u;
               
          
          int i, j; // Counters
          int m, n, mTarget, mHashTable, nHashTable, nKernels, nKernelsTarget; // Input size
          int nSingleChannelColNum;// Number of columns in single channel
          
          int nProjectionToTestDiffNoe; // Number of GCK projections in the input images to test differences between input iteration pixel to its candidates
          int nSequencyLevelsNum;       // Number of sequency levels
          
          int nHashTableCounter;
          
          int nFirstRowForward, nLastRowForward, nFirstColForward, nLastColForward; // Matlab indices
          int nFirstRowBack, nLastRowBack, nFirstColBack, nLastColBack;
          int nLeftRightOffset, nLeftRightTargetOffset, nTopBotOffset, nTopBotTargetOffset;  // Direction of propagation depending on current loop running direction (downwards/upwards)
          
          unsigned int nCurIterStep, nCurIterOffset;
          unsigned int nHorizNeighbourMapping32u, nVerticalNeighbourMapping32u;
          
          int advances = 0;
          unsigned int candBeforeLoop;
          
          if (nrhs < 11 || nrhs > 12 || nlhs!=0)
             mexErrMsgTxt("Usage: GCKCodebookPropagation16s(nBestErrorsImg32u, nBestMapping32u, nCurrFiltImgs_A16s, nCurrFiltImgs_B16s, nCodebookImgA32u, nCodebookImgB32u, nHashTableImgB32u, nHashsNoe16u, nSequencyOrder16u, nSequencyLevels16u, bDownwardFlag));\n");
          
          if (mxGetClassID(prhs[0]) != mxUINT32_CLASS ||
                  mxGetClassID(prhs[1]) != mxUINT32_CLASS || mxGetClassID(prhs[2]) != mxINT16_CLASS   ||
                  mxGetClassID(prhs[3]) != mxINT16_CLASS   || mxGetClassID(prhs[4]) != mxUINT32_CLASS ||
                  mxGetClassID(prhs[5]) != mxUINT32_CLASS || mxGetClassID(prhs[6]) != mxUINT32_CLASS || mxGetClassID(prhs[7]) != mxUINT32_CLASS ||
                  mxGetClassID(prhs[8]) != mxUINT16_CLASS  || mxGetClassID(prhs[9]) != mxUINT16_CLASS  ||
                  mxGetClassID(prhs[10]) != mxUINT16_CLASS  || mxGetClassID(prhs[11]) != mxLOGICAL_CLASS)
          {
             mexErrMsgTxt("Input best errors image must be a uint32 matrix, input linear mapping image must be a uint32 matrix, input and target GCK projections images must be int16 matrices inside a cell array, input and target codebook images must be a uint32 matrices, Hash table of target image must be a uint32 matrix, number of indices in each hash entry must be a uint8 scalar, sequency order of GCK kernels must be a uint8 vector, sequency levels of GCK kernels must be a uint8 vector and downwarads or upwards iteration must be a boolean!");
          }

          // Get inputs
          pBestErrorsImg32u        = (unsigned int*)mxGetPr(prhs[0]);
          pBestMapping32u          = (unsigned int*)mxGetPr(prhs[1]);
          mCurrFiltersImg          = (short*)mxGetPr(prhs[2]);
          mCurrFiltersImgTarget    = (short*)mxGetPr(prhs[3]);
          pCodebookImgA32u         = (unsigned int*)mxGetPr(prhs[4]);
          pCodebookImgB32u         = (unsigned int*)mxGetPr(prhs[5]);
          pHashTableImgA32u        = (unsigned int*)mxGetPr(prhs[6]);
          pHashTableImgB32u        = (unsigned int*)mxGetPr(prhs[7]);
          pHashsNoe16u             = (unsigned char*)mxGetPr(prhs[8]);
          pSequencyOrder16u        = (unsigned char*)mxGetPr(prhs[9]);
          pDownwardFlag            = (bool*)mxGetPr(prhs[11]);
          
          
          // Get sizes of variables (Opposite on purpose)//
          m = mxGetM(prhs[0]); // Width
          n = mxGetN(prhs[0]); // Height
          nSingleChannelColNum = n; // Num of elements in input image column
          
          nKernels       = mxGetM(prhs[2]);
          nKernelsTarget = mxGetM(prhs[3]);
          
          
          if (nKernels != nKernelsTarget)
             mexErrMsgTxt("Number of projection images for input and target images must be the same!");
       
          mTarget = mxGetM(prhs[5]); // Height of image B
          
          mHashTable = mxGetM(prhs[6]); // Width of hash table
          nHashTable = mxGetN(prhs[6]); // Height of hash table
          
          // Sequency params
          nProjectionToTestDiffNoe = mxGetM(prhs[9]);
          nSequencyLevelsNum       = mxGetM(prhs[10]);
          
          // Initialize filter parameters
          if (*pDownwardFlag) {
            // Filter downwards
            nFirstRowForward = (int)1;
            nLastRowForward  = m;
            nFirstColForward = (int)1;
            nLastColForward  = nSingleChannelColNum;

            nLeftRightOffset       = m;
            nTopBotOffset          = 1;
            nLeftRightTargetOffset = mTarget;
            nTopBotTargetOffset    = 1;
          }
          else {
            // Filter upards
            nLastRowBack  = (int)0;
            nFirstRowBack = m-(int)2;
            nLastColBack  = (int)0;
            nFirstColBack = nSingleChannelColNum-(int)2;

            nLeftRightOffset       = -m;
            nTopBotOffset          = -1;
            nLeftRightTargetOffset = -mTarget;
            nTopBotTargetOffset    = -1;
          }
          
          if (*pDownwardFlag) {
                    // Begin looping on input image pixels forwards
                for (j=nFirstColForward; j<nLastColForward; j++) {
                          nCurIterStep = j*m;

                          for (i=nFirstRowForward; i<nLastRowForward; i++) {
                                    nCurIterOffset = nCurIterStep+i;

                                    pCurrBestError32u   = &pBestErrorsImg32u[nCurIterOffset];
                                    pCurrBestMapping32u = &pBestMapping32u[nCurIterOffset];
                                    candBeforeLoop =  pCurrBestMapping32u[0] ;

                                    nHorizNeighbourMapping32u    = pBestMapping32u[nCurIterOffset - nLeftRightOffset];
                                    nVerticalNeighbourMapping32u = pBestMapping32u[nCurIterOffset - nTopBotOffset];

                                    // Collect candidates
                                    // ## Type 1 ## 
                                    // Current pixel best mapping's entry in target image hash table
                                    nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1;
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                      &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;// -1 for matlab2C;
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                                &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }
                                    // ## NEW - Type A ##
                                    nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1; // index into hash table
                                    nCurrLocA32u = pHashTableImgA32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C // first A-candidate
                                    nCurrCandMapping32u = pBestMapping32u[nCurrLocA32u];// its current best candidate

                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                      &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pBestMapping32u[pHashTableImgA32u[nCurrTypeHashVal32u +=  mHashTable]-1];// -1 for matlab2C; A index
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                                &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }
                                    // Right of the left pixel best mapping's
                                    nCurrTypeMapping32u = nHorizNeighbourMapping32u + nLeftRightTargetOffset;
                                    nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;

                                    // ## Type 2 - lr ## 
                                    // Test for original candidate
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrTypeMapping32u, nCurIterOffset,nKernels);
                                    // Test for cadidates in hash table with the same entry
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C;
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);

                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;// -1 for matlab2C;
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                                &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }
                                    // ## Type 2 - tb ## 
                                    // Bottom of the top pixel best mapping's - Or otherwise
                                    nCurrTypeMapping32u = nVerticalNeighbourMapping32u + nTopBotTargetOffset;
                                    nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;

                                    // Test for original candidate
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrTypeMapping32u, nCurIterOffset,nKernels);
                                    // Test for cadidats in hash table with the same entry
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C;
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;// -1 for matlab2C;
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                                &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }

                                    if (candBeforeLoop !=  pCurrBestMapping32u[0] )
                                              advances = advances + 1;

                          }
                }
                // mexPrintf("***********************************************\n");
                // mexPrintf("***** advances down: %d, out of: %d **********\n", advances, (nLastColForward - nFirstColForward)*(nLastRowForward - nFirstRowForward));
                // mexPrintf("***********************************************\n");

      }
      else {
                // Begin looping on input image pixels backwards
                for (j=nFirstColBack; j>=nLastColBack; j--) {
                          nCurIterStep = j*m;

                          for (i=nFirstRowBack; i>=nLastRowBack; i--) {
                                    nCurIterOffset = nCurIterStep+i;
                                    pCurrBestError32u   = &pBestErrorsImg32u[nCurIterOffset];
                                    pCurrBestMapping32u = &pBestMapping32u[nCurIterOffset];
                                    candBeforeLoop =  pCurrBestMapping32u[0] ;

                                    nHorizNeighbourMapping32u    = pBestMapping32u[nCurIterOffset - nLeftRightOffset];
                                    nVerticalNeighbourMapping32u = pBestMapping32u[nCurIterOffset - nTopBotOffset];

                                    // Collect candidates
                                    // ## Type 1 ## 
                                    // Current pixel best mapping's entry in target image hash table
                                    nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1;

                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                      &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;// -1 for matlab2C;
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                                &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }

                                    // ## NEW - Type A ##
                                    nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1; // index into hash table
                                    nCurrLocA32u = pHashTableImgA32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C // first A-candidate
                                    nCurrCandMapping32u = pBestMapping32u[nCurrLocA32u];// its current best candidate

                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                      &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pBestMapping32u[pHashTableImgA32u[nCurrTypeHashVal32u +=  mHashTable]-1];// -1 for matlab2C; A index
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget, &pCurrBestError32u,
                                                                &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }
                                              
                                    // Right of the left pixel best mapping's
                                    nCurrTypeMapping32u = nHorizNeighbourMapping32u + nLeftRightTargetOffset;
                                    nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;

                                    // ## Type 2 - lr ## 
                                    // Test for original candidate
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrTypeMapping32u, nCurIterOffset,nKernels);

                                    // Test for cadidates in hash table with the same entry
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C;
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;// -1 for matlab2C;
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                                &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }

                                    // ## Type 2 - tb ## 
                                    // Bottom of the top pixel best mapping's - Or otherwise
                                    nCurrTypeMapping32u = nVerticalNeighbourMapping32u + nTopBotTargetOffset;
                                    nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;

                                    // Test for original candidate
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrTypeMapping32u, nCurIterOffset,nKernels);

                                    // Test for cadidats in hash table with the same entry
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;// -1 for matlab2C;
                                              CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                      &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) {
                                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;// -1 for matlab2C;
                                                        CalcSqrDifferenceAndTakeBest(mCurrFiltersImg, mCurrFiltersImgTarget,
                                                                &pCurrBestError32u, &pCurrBestMapping32u, nCurrCandMapping32u, nCurIterOffset,nKernels);
                                    }

                                    if (candBeforeLoop !=  pCurrBestMapping32u[0] )
                                              advances = advances + 1;                              }
                }
                // mexPrintf("***********************************************\n");
                // mexPrintf("***** advances up: %d, out of: %d **********\n", advances, (nLastColBack - nFirstColBack)*(nLastRowBack - nFirstRowBack));
                // mexPrintf("***********************************************\n");
      }        

          
}
