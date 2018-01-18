// 4-byte Integer Hashing (By Thomas Wang or Robert Jenkins) //
///////////////////////////////////////////////////////////////

#include "mex.h"

#define uint32_t unsigned long int


// Thomas Wang has an integer hash using multiplication that's faster than any of mine on my Core 2 duo using gcc -O3, and it passes my favorite sanity tests well. I've had reports it doesn't do well with integer sequences with a multiple of 34.

uint32_t hash_1( uint32_t a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

// Thomas has 64-bit integer hashes too. I don't have any of those yet.
// Here's a way to do it in 6 shifts:
uint32_t hash_2( uint32_t a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
}

//Or 7 shifts, if you don't like adding those big magic constants:
uint32_t hash_3( uint32_t a)
{
    a -= (a<<6);
    a ^= (a>>17);
    a -= (a<<9);
    a ^= (a<<4);
    a -= (a<<3);
    a ^= (a<<10);
    a ^= (a>>15);
    return a;
}

// Thomas Wang has a function that does it in 6 shifts (provided you use the low bits, hash & (SIZE-1), rather than the high bits if you can't use the whole value):
uint32_t hash_4( uint32_t a)
{
    a += ~(a<<15);
    a ^=  (a>>10);
    a +=  (a<<3);
    a ^=  (a>>6);
    a += ~(a<<11);
    a ^=  (a>>16);
    return a;
}

// Here's one that takes 4 shifts. You need to use the bottom bits, and you need to use at least the bottom 11 bits. It doesn't achieve avalanche at the high or the low end. It does pass my integer sequences tests, and all settings of any set of 4 bits usually maps to 16 distinct values in bottom 11 bits.
uint32_t hash_5( uint32_t a)
{
    a = (a^0xdeadbeef) + (a<<4);
    a = a ^ (a>>10);
    a = a + (a<<7);
    a = a ^ (a>>13);
    return a;
}

// And this one isn't too bad, provided you promise to use at least the 17 lowest bits. Passes the integer sequence and 4-bit tests.
uint32_t hash_6( uint32_t a)
{
    a = a ^ (a>>4);
    a = (a^0xdeadbeef) + (a<<5);
    a = a ^ (a>>11);
    return a;
}

// 4-byte integer hash, full avalanche

// I was able to do it in 6 shifts.
uint32_t hash_7( uint32_t a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
}
// These magic constants also worked: 0x7fb9b1ee, 0xab35dd63, 0x41ed960d, 0xc7d0125e, 0x071f9f8f, 0x55ab55b9 .

// If you don't like big magic constants, here's another hash with 7 shifts:
uint32_t hash_8( uint32_t a)
{
    a -= (a<<6);
    a ^= (a>>17);
    a -= (a<<9);
    a ^= (a<<4);
    a -= (a<<3);
    a ^= (a<<10);
    a ^= (a>>15);
    return a;
}


// Another hash is Thomas Wang's function,
uint32_t hash_9( uint32_t a)
{
    a += ~(a<<15);
    a ^=  (a>>10);
    a +=  (a<<3);
    a ^=  (a>>6);
    a += ~(a<<11);
    a ^=  (a>>16);
    return a;
}

//////////////////////////
/* The gateway function */
//////////////////////////
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    /* I N P U T S */

    //Declarations
    const mxArray *xData;
    const mxArray *param2;
    const mxArray *param3;
    uint32_t *xValues;
    uint32_t *outArray;
    int i,j;
    int rowLen, colLen;
    int functionNum;
    int numBits;
    uint32_t bitmask;
    uint32_t (*fun)(uint32_t);

    //Copy input pointer x
    xData = prhs[0];
    param2 = prhs[1]; 
    param3 = prhs[2];

    //Get matrix x
    xValues = (unsigned long int*)(mxGetPr(xData));
    rowLen = mxGetN(xData);
    colLen = mxGetM(xData); 
    // Get params
    functionNum = (int)(mxGetScalar(param2));
    numBits = (int)(mxGetScalar(param3));
    
//    printf("------ I N P U T S ------\n");
//    printf("-- functionNum: %d --\n",functionNum);    
//    printf("-- numBits: %d --\n",numBits);    
//    printf("-------------------------\n");
    
    bitmask = (1<<numBits) - 1;
//    printf("bitmask: %d\n", bitmask);

    /* O U T P U T S */

    //Allocate memory and assign output pointer
    plhs[0] = mxCreateNumericMatrix(colLen, rowLen, mxUINT32_CLASS, mxREAL); //mxREAL is our data-type
    //Get a pointer to the data space in our newly allocated memory
    outArray = (unsigned long int*)(mxGetPr(plhs[0]));
    

    /* C A L C U L A T I O N */
    
    switch (functionNum) {
        case 1: fun = &hash_1; break;
        case 2: fun = &hash_2; break;
        case 3: fun = &hash_3; break;
        case 4: fun = &hash_4; break;
        case 5: fun = &hash_5; break;
        case 6: fun = &hash_6; break;
        case 7: fun = &hash_7; break;
        case 8: fun = &hash_8; break;
        case 9: fun = &hash_9; break;
    }
       
    for(i=0;i<rowLen;i++)
    {
        for(j=0;j<colLen;j++) 
        {
            outArray[(i*colLen)+j] = (*fun)(xValues[(i*colLen)+j]) & bitmask;
//            if (i<3 && j<3)
//                printf("in: %u   out: %u\n", hash_1(xValues[(i*colLen)+j]), outArray[(i*colLen)+j]);
        }
    }

}