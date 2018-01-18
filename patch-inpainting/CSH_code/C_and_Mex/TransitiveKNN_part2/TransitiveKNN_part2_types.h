/*
 * TransitiveKNN_part2_types.h
 *
 * Code generation for function 'TransitiveKNN_part2'
 *
 * C source code generated on: Wed Nov 19 10:38:03 2014
 *
 */

#ifndef __TRANSITIVEKNN_PART2_TYPES_H__
#define __TRANSITIVEKNN_PART2_TYPES_H__

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    real_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /*typedef_emxArray_real_T*/
#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T
struct emxArray_uint8_T
{
    uint8_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_uint8_T*/
#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T
typedef struct emxArray_uint8_T emxArray_uint8_T;
#endif /*typedef_emxArray_uint8_T*/

#endif
/* End of code generation (TransitiveKNN_part2_types.h) */
