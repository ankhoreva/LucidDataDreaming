#include <string.h>
#include <mex.h>
#include <matrix.h>
#include <math.h>

#define CONV_TO_LINEAR_MAPPING(Offset,K) ((Offset)*K)


/* Calculate distance between two projections */
int CalcDist(int *pCurrFiltImgs_A16s , int *pCurrFiltImgs_B16s,
             unsigned int A_FiltersPtr, unsigned int B_FiltersPtr)
{
      int nDiffSqr32s;
      nDiffSqr32s = (int)(pCurrFiltImgs_A16s[A_FiltersPtr] - pCurrFiltImgs_B16s[B_FiltersPtr]);
      return nDiffSqr32s * nDiffSqr32s;
}

/* Take candiate with best error */
void CompareDistToInverseCandidate(unsigned int ReferenceError, unsigned int *pBestErrorsImg32u, unsigned int *pBestMapping32u, 
                                   unsigned int nCurrCandMapping32u,unsigned int nCurIterOffset32u,  int kOfKNN) 
{
      int index, worstInd;
      unsigned int worstError , CurrIterrationConv , Temp;

      /* 1) a] check if candidate already appears in list - if so we don't bother calculating its error
      /*      b] find the index of the current worst candidate. (this is the candidate we will replace) */

	  Temp = CurrIterrationConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset32u,kOfKNN);
	  for (index = 0; index < kOfKNN; index++) 
      {
            if (pBestMapping32u[Temp++] == nCurrCandMapping32u)
                return;
	  }
	
	  Temp = CurrIterrationConv;
      worstError = 0; worstInd = 1;
	  for (index = 0; index < kOfKNN; index++) 
      {
            if (pBestErrorsImg32u[Temp] > worstError)
            {
                worstError = pBestErrorsImg32u[Temp];
                worstInd = index;
            }
			Temp++;
      }
      if (ReferenceError > worstError)
          return;

	  Temp = CurrIterrationConv + worstInd;
      /* 2)  move the contents of the first candidate to the worst position */
      pBestErrorsImg32u[Temp] = pBestErrorsImg32u[CurrIterrationConv] ;
      pBestMapping32u[Temp]   = pBestMapping32u[CurrIterrationConv];


      /* 3) place the new error and candidate in the first  position (which is vacant now) */
      pBestErrorsImg32u[CurrIterrationConv]   = ReferenceError;
      pBestMapping32u[CurrIterrationConv]     = nCurrCandMapping32u;
}


/* Take candiate with best error */
void CalcSqrDifferenceAndTakeBest( int *pCurrFiltImgs_A16s, int *pCurrFiltImgs_B16s,
                                   unsigned int *pBestErrorsImg32u, unsigned int *pBestMapping32u, 
                                   unsigned int nCurrCandMapping32u,unsigned int nCurIterOffset32u,  
                                   int nKernels, int hA , int wA , int kOfKNN) 
{
      unsigned int nCurError32u , ReminderBestError;
      int index, worstInd;
      unsigned int A_FiltersPtr , B_FiltersPtr;
      unsigned int worstError , CurrIterrationConv , Temp;

      /* 1) a] check if candidate already appears in list - if so we don't bother calculating its error
      /*      b] find the index of the current worst candidate. (this is the candidate we will replace) */

	  Temp = CurrIterrationConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset32u,kOfKNN);
      
	  for (index = 0; index < kOfKNN; index++) 
      {
            if (pBestMapping32u[Temp++] == nCurrCandMapping32u)
                return;
	  }
	
	  Temp = CurrIterrationConv;
      worstError = 0; worstInd = 1;
	  nCurError32u = 0;
	  for (index = 0; index < kOfKNN; index++) 
      {
            if (pBestErrorsImg32u[Temp] > worstError)
            {
                worstError = pBestErrorsImg32u[Temp];
                worstInd = index;
            }
			Temp++;
      }

      /* 2) calculate the estimated error */
      A_FiltersPtr = nKernels * nCurIterOffset32u;
      B_FiltersPtr = nKernels * nCurrCandMapping32u;
	  ReminderBestError = worstError;
      /* first WH kernel (DC) */
      nCurError32u = CalcDist(pCurrFiltImgs_A16s,pCurrFiltImgs_B16s,A_FiltersPtr, B_FiltersPtr);
      if (nCurError32u > ReminderBestError)
         return;
      
      A_FiltersPtr++; B_FiltersPtr++;
	  ReminderBestError -= nCurError32u;
      /* all the rest (in pairs)*/
      for (index = 1; (index < nKernels-1); index = index + 2)
      {
            nCurError32u = CalcDist(pCurrFiltImgs_A16s,pCurrFiltImgs_B16s,A_FiltersPtr, B_FiltersPtr);
            A_FiltersPtr++; B_FiltersPtr++;
            nCurError32u += CalcDist(pCurrFiltImgs_A16s,pCurrFiltImgs_B16s,A_FiltersPtr, B_FiltersPtr);
            A_FiltersPtr++; B_FiltersPtr++;
            if (nCurError32u > ReminderBestError)
                  return;
			ReminderBestError -= nCurError32u;
      }          
      if ((nKernels & 1) == 0) /*Even number of kernels, check lust o */
      {
            nCurError32u = CalcDist(pCurrFiltImgs_A16s,pCurrFiltImgs_B16s,A_FiltersPtr, B_FiltersPtr);
            if (nCurError32u > ReminderBestError)
                  return;
      }
      
	  Temp = CurrIterrationConv + worstInd;
      /* 3)  move the contents of the first candidate to the worst position */
      pBestErrorsImg32u[Temp] = pBestErrorsImg32u[CurrIterrationConv] ;
      pBestMapping32u[Temp]   = pBestMapping32u[CurrIterrationConv];


      /* 4) place the new error and candidate in the first  position (which is vacant now)*/
      pBestErrorsImg32u[CurrIterrationConv]   =  (worstError - ReminderBestError);
      pBestMapping32u[CurrIterrationConv]     = nCurrCandMapping32u;
/*	
	  /* Make sure not to check inverse on the boundaries*/
	  Temp = nCurIterOffset32u % hA;
      if ((nCurIterOffset32u < hA) || (nCurIterOffset32u > hA*(wA-1)) || (Temp == 1) || (Temp == 0))
		  return;
	  /* 5) For this version, the assumption is that both A and B images are the same
	  /*    Therefore if b is the match for patch a, than also a is a match for patch b, since this is the same image*/
	  CompareDistToInverseCandidate(nCurError32u, pBestErrorsImg32u, pBestMapping32u, nCurIterOffset32u , nCurrCandMapping32u ,kOfKNN);

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
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{
      unsigned int   *pBestErrorsImg32u, *pCodebookImgA32u, *pCodebookImgB32u, *pBestMapping32u, *pHashTableImgB32u, *pHashTableImgA32u;
      unsigned short *pHashsNoe16u, *pSequencyOrder16u, *pSequencyLevels16u;
      bool           *pDownwardFlag;
      
      int            *pCurrFiltImgs_A16s, *pCurrFiltImgs_B16s;
      int            nKernels , nKernelsTarget;
      unsigned int   nSingleChannelColNum;/* Number of columns in single channel; */
      
      
      unsigned int  nCurrTypeHashVal32u, nCurrCandMapping32u,nCurrCandMapping32u_2, nCurrTypeMapping32u;
      unsigned int nCurrLocA32u;
      
      int i, j; /* Counters */
      int m, n, mTarget, mHashTable, nHashTable;
      
      int nProjectionToTestDiffNoe; /* Number of GCK projections in the input images to test differences between input iteration pixel to its candidates*/
      int nSequencyLevelsNum;       /* Number of sequency levels*/
      
      int nHashTableCounter;
      
      int nFirstRowForward, nLastRowForward, nFirstColForward, nLastColForward; /* Matlab indices*/
      int nFirstRowBack, nLastRowBack, nFirstColBack, nLastColBack;
      int nLeftRightOffset, nLeftRightTargetOffset, nTopBotOffset, nTopBotTargetOffset;  /* Direction of propagation depending on current loop running direction (downwards/upwards)*/
      
      unsigned int nNumOfElements, nNumOfTargetElements, nNumOfElementsHashTable;
      unsigned int nCurIterStep, nCurIterOffset;
      unsigned int nHorizNeighbourMapping32u, nVerticalNeighbourMapping32u,CordConv;
      unsigned int CandidateBestMapping , CandidateBestMappingConv;
      int kOfKNN;
      int loc,ind , ind2;
      
      if (nrhs < 11 || nrhs > 13 || nlhs!=0)
                mexErrMsgTxt("Usage: GCKCodebookPropagation16s(nBestErrorsImg32u, nBestMapping32u, nCurrFiltImgs_A16s, nCurrFiltImgs_B16s, nCodebookImgA32u, nCodebookImgB32u, nHashTableImgB32u, nHashsNoe16u, nSequencyOrder16u, nSequencyLevels16u, bDownwardFlag, kOfKNN));\n");
      
      if (mxGetClassID(prhs[0]) != mxUINT32_CLASS ||
              mxGetClassID(prhs[1]) != mxUINT32_CLASS || mxGetClassID(prhs[2]) != mxINT32_CLASS  ||
              mxGetClassID(prhs[3]) != mxINT32_CLASS  || mxGetClassID(prhs[4]) != mxUINT32_CLASS ||
              mxGetClassID(prhs[5]) != mxUINT32_CLASS || mxGetClassID(prhs[6]) != mxUINT32_CLASS || mxGetClassID(prhs[7]) != mxUINT32_CLASS ||
              mxGetClassID(prhs[8]) != mxUINT16_CLASS  || mxGetClassID(prhs[9]) != mxUINT16_CLASS  ||
              mxGetClassID(prhs[10]) != mxUINT16_CLASS  || mxGetClassID(prhs[11]) != mxLOGICAL_CLASS || mxGetClassID(prhs[12]) != mxUINT32_CLASS)
                mexErrMsgTxt("Input best errors image must be a uint32 matrix, input linear mapping image must be a uint32 matrix, input and target GCK projections images must be int16 matrices inside a cell array, input and target codebook images must be a uint32 matrices, Hash table of target image must be a uint32 matrix, number of indices in each hash entry must be a uint8 scalar, sequency order of GCK kernels must be a uint8 vector, sequency levels of GCK kernels must be a uint8 vector and downwarads or upwards iteration must be a boolean!");
      
      
      /* Get inputs*/
      pBestErrorsImg32u        = (unsigned int*)mxGetPr(prhs[0]);
      pBestMapping32u          = (unsigned int*)mxGetPr(prhs[1]);
      pCurrFiltImgs_A16s       = (int*)mxGetPr(prhs[2]);
      pCurrFiltImgs_B16s       = (int*)mxGetPr(prhs[3]);
      pCodebookImgA32u         = (unsigned int*)mxGetPr(prhs[4]);
      pCodebookImgB32u         = (unsigned int*)mxGetPr(prhs[5]);
      pHashTableImgA32u        = (unsigned int*)mxGetPr(prhs[6]);
      pHashTableImgB32u        = (unsigned int*)mxGetPr(prhs[7]);
      pHashsNoe16u             = (unsigned short*)mxGetPr(prhs[8]);
      pSequencyOrder16u        = (unsigned short*)mxGetPr(prhs[9]);
      pSequencyLevels16u       = (unsigned short*)mxGetPr(prhs[10]);
      pDownwardFlag            = (bool*)mxGetPr(prhs[11]);
      kOfKNN = *(unsigned int*)mxGetPr(prhs[12]);
      
      /* Get sizes of variables (Opposite on purpose)*/
      m = mxGetM(prhs[4]); /* Width*/
      n = mxGetN(prhs[4]); /* Height*/
      
      nSingleChannelColNum = n; /* Num of elements in input image column*/
         
      nKernels       = mxGetM(prhs[2]);
      nKernelsTarget = mxGetM(prhs[3]);
          
      if (nKernels != nKernelsTarget)
         mexErrMsgTxt("Number of projection images for input and target images must be the same!");

      mTarget = mxGetM(prhs[5]); /* Height of image B*/
      
      
      mHashTable = mxGetM(prhs[6]); /* Width of hash table*/
      nHashTable = mxGetN(prhs[6]); /* Height of hash table*/
      
      /* Sequency params*/
      nProjectionToTestDiffNoe = mxGetM(prhs[9]);
      nSequencyLevelsNum       = mxGetM(prhs[10]);
      
      if (mxGetN(prhs[9])>1 || mxGetN(prhs[10])>1)
                mexErrMsgTxt("Input sequency order of GCK kernels and sequency levels of GCK kernels must be column vectors!");
      
      
      /* Get input and target images num of elements*/
      nNumOfElements          = mxGetN(prhs[2]); /* Get number of elements in projections matrix (source)*/
      nNumOfTargetElements    = mxGetN(prhs[3]); /* Get number of elements in projections matrix (destination)*/
      nNumOfElementsHashTable = mHashTable * nHashTable;
     
      /* Initialize filter parameters*/
      if (*pDownwardFlag) 
	  {		/* Filter downwards*/
            nFirstRowForward = (int)1;
            nLastRowForward  = m;
            nFirstColForward = (int)1;
            nLastColForward  = nSingleChannelColNum;
            
            nLeftRightOffset       = m;
            nTopBotOffset          = 1;
            nLeftRightTargetOffset = mTarget;
            nTopBotTargetOffset    = 1;
      }
      else
	  {
            /* Filter upards*/
            nLastRowBack  = (int)0;
            nFirstRowBack = m-(int)2;
            nLastColBack  = (int)0;
            nFirstColBack = nSingleChannelColNum-(int)2;
            
            nLeftRightOffset       = -m;
            nTopBotOffset          = -1;
            nLeftRightTargetOffset = -mTarget;
            nTopBotTargetOffset    = -1;
      }
      
      if (*pDownwardFlag) 
      {
            /* Begin looping on input image pixels forwards*/
            for (j=nFirstColForward; j<nLastColForward; j++) 
			{
                  nCurIterStep = j*m;
                      
                  for (i=nFirstRowForward; i<nLastRowForward; i++) 
				  {
                        nCurIterOffset = nCurIterStep+i;
                       
                        /* Collect candidates
                        /* ## Type 1 ##
                        /* Current pixel best mapping's entry in target image hash table*/
                        nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1;
                        
                        nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C*/
                        CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
													 nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                        
						for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) 
						{
                                  nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;/* -1 for matlab2C;*/
                                  CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
															   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                        }
                        
                        /* ## NEW - Type A ##*/
                        nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1; /* index into hash table*/
                        nCurrLocA32u = pHashTableImgA32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C /* first A-candidate*/
                        
						CordConv = CONV_TO_LINEAR_MAPPING(nCurrLocA32u,kOfKNN);
                        for  (ind = 0; ind < kOfKNN; ind++)
                        {
                              nCurrCandMapping32u = pBestMapping32u[CordConv++];/* its current best candidate*/
                              
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                        }
                        
                        for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) 
						{
                              loc = pHashTableImgA32u[nCurrTypeHashVal32u +=  mHashTable]-1;
							  CordConv = CONV_TO_LINEAR_MAPPING(loc,kOfKNN);
                              for  (ind = 0; ind < kOfKNN; ind++) 
                              {         
                                    nCurrCandMapping32u = pBestMapping32u[CordConv++];/* -1 for matlab2C; A index*/
                                    CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
												                 nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              }

                        }

                        /* ## Type 2 - lr ##
                        /* Right of the left pixel best mapping's*/
						CordConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset - nLeftRightOffset,kOfKNN);
                        for  (ind = 0; ind < kOfKNN; ind++) 
                        {
                              nHorizNeighbourMapping32u    = pBestMapping32u[CordConv++];
                              nCurrTypeMapping32u = nHorizNeighbourMapping32u + nLeftRightTargetOffset;
                              nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;
                              
                              /* Test for original candidate*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrTypeMapping32u, nCurIterOffset,nKernels,m,n, kOfKNN);
                              
                              /* Test for cadidates in hash table with the same entry*/
                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C;*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);

							  for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) 
							  {
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;/* -1 for matlab2C;*/
                                    CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
																 nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              }
                        }
                        
                        /* ## Type 2 - tb ##
                        /* Bottom of the top pixel best mapping's - Or otherwise*/
						CordConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset - nTopBotOffset,kOfKNN);
                        for  (ind = 0; ind < kOfKNN; ind++) 
						{
                              nVerticalNeighbourMapping32u = pBestMapping32u[CordConv++];
                              nCurrTypeMapping32u = nVerticalNeighbourMapping32u + nTopBotTargetOffset;
                              nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;
                              /* Test for original candidate*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrTypeMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              /* Test for cadidats in hash table with the same entry*/
                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C;*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) 
							  {
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;/* -1 for matlab2C;*/
                                    CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
																 nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              }
                        }
                        
                        /* TYPE 4: if images are the same, check your candidates mapping*/
                        CordConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset,kOfKNN);
                        for  (ind = 0; ind < kOfKNN; ind++) 
						{
                              CandidateBestMapping = pBestMapping32u[CordConv+ind];
                              if (CandidateBestMapping != nCurIterOffset)
                              {
                                  CandidateBestMappingConv = CONV_TO_LINEAR_MAPPING(CandidateBestMapping,kOfKNN);
                                  for (ind2 = 0 ; ind2 <  kOfKNN; ind2++) 
                                  {
                                         nCurrTypeMapping32u = pBestMapping32u[CandidateBestMappingConv + ind2];
										 if (nCurrTypeMapping32u != nCurIterOffset)
										 {
	                                        /* Find the mapping candidates*/
		                                    CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
																		 nCurrTypeMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
										 }
                                 }
                            }
                        }
                  }
            }
      }
      else 
	  {
            /* Begin looping on input image pixels backwards*/
            for (j=nFirstColBack; j>=nLastColBack; j--)
			{
                  nCurIterStep = j*m;
                  for (i=nFirstRowBack; i>=nLastRowBack; i--) 
				  {
                        nCurIterOffset = nCurIterStep+i;
                        
                        /* Collect candidates
                        /* ## Type 1 ##
                        /* Current pixel best mapping's entry in target image hash table*/
                        nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1;
                        
                        nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C*/
                        CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
													 nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                        
                        for (nHashTableCounter=1; nHashTableCounter < (*pHashsNoe16u); nHashTableCounter++) 
						{
                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;/* -1 for matlab2C;*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                        }
                        
                        /* ## NEW - Type A ##*/
                        nCurrTypeHashVal32u = pCodebookImgA32u[nCurIterOffset]-1; /* index into hash table*/
                        nCurrLocA32u = pHashTableImgA32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C /* first A-candidate*/
                        CordConv = CONV_TO_LINEAR_MAPPING(nCurrLocA32u,kOfKNN);
                        for  (ind = 0; ind < kOfKNN; ind++)
                        {
                              nCurrCandMapping32u = pBestMapping32u[CordConv++];/* its current best candidate*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                        }
                        
                        for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++)
						{
                              loc = pHashTableImgA32u[nCurrTypeHashVal32u +=  mHashTable]-1;
							  CordConv = CONV_TO_LINEAR_MAPPING(loc,kOfKNN);
                              for  (ind = 0; ind < kOfKNN; ind++) 
                              {         
                                  nCurrCandMapping32u = pBestMapping32u[CordConv++];/* -1 for matlab2C; A index*/
                                  CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
															   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              }
                        }
                        CordConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset - nLeftRightOffset,kOfKNN);
                        /* Right of the left pixel best mapping's*/
                        for  (ind = 0; ind < kOfKNN; ind++) 
                        {
							  nHorizNeighbourMapping32u    = pBestMapping32u[CordConv++];
                              
							  nCurrTypeMapping32u = nHorizNeighbourMapping32u + nLeftRightTargetOffset;
							  nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;
		                      
							  /* ## Type 2 - lr ##
							  /* Test for original candidate*/
							  CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrTypeMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
		                      
							  /* Test for cadidats in hash table with the same entry*/
							  nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C;*/
							  CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
							  
							  for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) 
							  {
									nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;/* -1 for matlab2C;*/
									CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
																 nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
							  }
                        }
                        /* ## Type 2 - tb ##
                        /* Bottom of the top pixel best mapping's - Or otherwise*/
						CordConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset - nTopBotOffset,kOfKNN);
                        for  (ind = 0; ind < kOfKNN; ind++) 
						{
                              nVerticalNeighbourMapping32u = pBestMapping32u[CordConv++];
                              nCurrTypeMapping32u = nVerticalNeighbourMapping32u + nTopBotTargetOffset;
                              nCurrTypeHashVal32u = pCodebookImgB32u[nCurrTypeMapping32u]-1;
                              
                              /* Test for original candidate*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
														   nCurrTypeMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              /* Test for cadidats in hash table with the same entry*/
                              nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u]-1;/* -1 for matlab2C;*/
                              CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
					                                       nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              
                              for (nHashTableCounter=1; nHashTableCounter<(*pHashsNoe16u); nHashTableCounter++) 
							  {
                                    nCurrCandMapping32u = pHashTableImgB32u[nCurrTypeHashVal32u +=  mHashTable]-1;/* -1 for matlab2C;*/
                                    CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
																 nCurrCandMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
                              }
                        }

                        /* TYPE 4: if images are the same, check your candidates mapping*/
                        CordConv = CONV_TO_LINEAR_MAPPING(nCurIterOffset,kOfKNN);
                        for  (ind = 0; ind < kOfKNN; ind++) 
						{
                              CandidateBestMapping = pBestMapping32u[CordConv+ind];
                              if (CandidateBestMapping != nCurIterOffset)
                              {
                                  CandidateBestMappingConv = CONV_TO_LINEAR_MAPPING(CandidateBestMapping,kOfKNN);
                                  for (ind2 = 0 ; ind2 <  kOfKNN; ind2++) 
                                  {
                                         nCurrTypeMapping32u = pBestMapping32u[CandidateBestMappingConv + ind2];
										 if (nCurrTypeMapping32u != nCurIterOffset)
										 {
			                                /* Find the mapping candidates*/
	                                        CalcSqrDifferenceAndTakeBest(pCurrFiltImgs_A16s, pCurrFiltImgs_B16s, pBestErrorsImg32u, pBestMapping32u,
		                                                                 nCurrTypeMapping32u, nCurIterOffset, nKernels,m,n, kOfKNN);
										 }
                                 }
                            }
                        }
                  }
            }
      }
}
