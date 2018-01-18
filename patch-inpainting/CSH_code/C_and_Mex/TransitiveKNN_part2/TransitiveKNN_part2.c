/*
 * TransitiveKNN_part2.c
 *
 * Code generation for function 'TransitiveKNN_part2'
 *
 * C source code generated on: Wed Nov 19 10:38:03 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "TransitiveKNN_part2.h"

/* Type Definitions */
#ifndef struct_emxArray__common
#define struct_emxArray__common

struct emxArray__common
{
  void *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray__common*/

#ifndef typedef_emxArray__common
#define typedef_emxArray__common

typedef struct emxArray__common emxArray__common;

#endif                                 /*typedef_emxArray__common*/

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_boolean_T*/

#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T

typedef struct emxArray_boolean_T emxArray_boolean_T;

#endif                                 /*typedef_emxArray_boolean_T*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

/* Variable Definitions */
static const volatile char_T *emlrtBreakCheckR2012bFlagVar;
static emlrtRSInfo emlrtRSI = { 14, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRSInfo b_emlrtRSI = { 15, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRSInfo c_emlrtRSI = { 17, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRSInfo d_emlrtRSI = { 18, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRSInfo e_emlrtRSI = { 20, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRSInfo f_emlrtRSI = { 28, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRSInfo g_emlrtRSI = { 34, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRSInfo h_emlrtRSI = { 11, "squeeze",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/squeeze.m" };

static emlrtRSInfo i_emlrtRSI = { 22, "squeeze",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/squeeze.m" };

static emlrtRSInfo j_emlrtRSI = { 52, "squeeze",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/squeeze.m" };

static emlrtRSInfo k_emlrtRSI = { 9, "eml_int_forloop_overflow_check",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtRSInfo l_emlrtRSI = { 12, "eml_int_forloop_overflow_check",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtRSInfo m_emlrtRSI = { 20, "sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/sort.m" };

static emlrtRSInfo n_emlrtRSI = { 34, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo o_emlrtRSI = { 50, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo p_emlrtRSI = { 62, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo q_emlrtRSI = { 63, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo r_emlrtRSI = { 66, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo s_emlrtRSI = { 68, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo t_emlrtRSI = { 69, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo u_emlrtRSI = { 70, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo v_emlrtRSI = { 71, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo w_emlrtRSI = { 76, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo x_emlrtRSI = { 78, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRSInfo y_emlrtRSI = { 84, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

emlrtRSInfo ab_emlrtRSI = { 19, "eml_assert_valid_dim",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"
};

emlrtRSInfo bb_emlrtRSI = { 86, "eml_matrix_vstride",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m"
};

emlrtRSInfo cb_emlrtRSI = { 50, "prodsize",
  "C:/Program Files/MATLAB/R2013b/toolbox/shared/coder/coder/+coder/+internal/prodsize.m"
};

emlrtRSInfo db_emlrtRSI = { 49, "prodsize",
  "C:/Program Files/MATLAB/R2013b/toolbox/shared/coder/coder/+coder/+internal/prodsize.m"
};

static emlrtRSInfo eb_emlrtRSI = { 37, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo fb_emlrtRSI = { 42, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo gb_emlrtRSI = { 134, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo hb_emlrtRSI = { 138, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo ib_emlrtRSI = { 139, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo jb_emlrtRSI = { 141, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo kb_emlrtRSI = { 148, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo lb_emlrtRSI = { 150, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo mb_emlrtRSI = { 154, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo nb_emlrtRSI = { 159, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo ob_emlrtRSI = { 142, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo pb_emlrtRSI = { 161, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo qb_emlrtRSI = { 163, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo rb_emlrtRSI = { 166, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo sb_emlrtRSI = { 168, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo tb_emlrtRSI = { 173, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo ub_emlrtRSI = { 176, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo vb_emlrtRSI = { 178, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo wb_emlrtRSI = { 182, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo xb_emlrtRSI = { 184, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo yb_emlrtRSI = { 185, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo ac_emlrtRSI = { 186, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRSInfo bc_emlrtRSI = { 189, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

emlrtRSInfo cc_emlrtRSI = { 20, "eml_sort_le",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_le.m" };

emlrtRSInfo dc_emlrtRSI = { 53, "eml_sort_le",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_le.m" };

static emlrtRSInfo ec_emlrtRSI = { 102, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtRSInfo fc_emlrtRSI = { 100, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtRSInfo gc_emlrtRSI = { 40, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtRSInfo hc_emlrtRSI = { 16, "min",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/min.m" };

static emlrtRSInfo ic_emlrtRSI = { 18, "eml_min_or_max",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_min_or_max.m" };

emlrtRSInfo jc_emlrtRSI = { 59, "eml_min_or_max",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_min_or_max.m" };

emlrtRSInfo kc_emlrtRSI = { 124, "eml_min_or_max",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_min_or_max.m" };

emlrtRSInfo lc_emlrtRSI = { 55, "prodsize",
  "C:/Program Files/MATLAB/R2013b/toolbox/shared/coder/coder/+coder/+internal/prodsize.m"
};

static emlrtRSInfo mc_emlrtRSI = { 41, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtRSInfo nc_emlrtRSI = { 232, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtRSInfo oc_emlrtRSI = { 230, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtRSInfo pc_emlrtRSI = { 30, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo qc_emlrtRSI = { 31, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo rc_emlrtRSI = { 32, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo sc_emlrtRSI = { 34, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo tc_emlrtRSI = { 36, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo uc_emlrtRSI = { 37, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo vc_emlrtRSI = { 38, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo wc_emlrtRSI = { 40, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo xc_emlrtRSI = { 20, "eml_index_prod",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_index_prod.m" };

static emlrtRSInfo yc_emlrtRSI = { 61, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo ad_emlrtRSI = { 24, "indexIntRelop",
  "C:/Program Files/MATLAB/R2013b/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"
};

emlrtRSInfo bd_emlrtRSI = { 233, "indexIntRelop",
  "C:/Program Files/MATLAB/R2013b/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"
};

static emlrtRSInfo cd_emlrtRSI = { 48, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo dd_emlrtRSI = { 49, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo ed_emlrtRSI = { 56, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo fd_emlrtRSI = { 67, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo gd_emlrtRSI = { 69, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo hd_emlrtRSI = { 71, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo id_emlrtRSI = { 72, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo jd_emlrtRSI = { 75, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRSInfo kd_emlrtRSI = { 76, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

emlrtRSInfo ld_emlrtRSI = { 16, "eml_is_permutation",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_is_permutation.m"
};

emlrtRSInfo md_emlrtRSI = { 21, "eml_is_permutation",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_is_permutation.m"
};

emlrtRSInfo nd_emlrtRSI = { 12, "all",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/ops/all.m" };

emlrtRSInfo od_emlrtRSI = { 225, "indexIntRelop",
  "C:/Program Files/MATLAB/R2013b/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"
};

static emlrtMCInfo emlrtMCI = { 52, 9, "eml_int_forloop_overflow_check",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtMCInfo b_emlrtMCI = { 51, 15, "eml_int_forloop_overflow_check",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

emlrtMCInfo c_emlrtMCI = { 20, 5, "eml_assert_valid_dim",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"
};

emlrtMCInfo d_emlrtMCI = { 18, 15, "eml_assert_valid_dim",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"
};

static emlrtMCInfo e_emlrtMCI = { 46, 9, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtMCInfo f_emlrtMCI = { 45, 19, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

emlrtMCInfo g_emlrtMCI = { 65, 1, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

emlrtMCInfo h_emlrtMCI = { 123, 9, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

emlrtMCInfo i_emlrtMCI = { 122, 19, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtMCInfo j_emlrtMCI = { 239, 9, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtMCInfo k_emlrtMCI = { 33, 5, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtMCInfo l_emlrtMCI = { 32, 15, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRTEInfo emlrtRTEI = { 1, 60, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRTEInfo b_emlrtRTEI = { 47, 1, "permute",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/permute.m" };

static emlrtRTEInfo c_emlrtRTEI = { 127, 5, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtRTEInfo d_emlrtRTEI = { 15, 9, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRTEInfo e_emlrtRTEI = { 16, 9, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRTEInfo f_emlrtRTEI = { 17, 9, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRTEInfo g_emlrtRTEI = { 19, 9, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRTEInfo h_emlrtRTEI = { 1, 11, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRTEInfo i_emlrtRTEI = { 33, 6, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtRTEInfo j_emlrtRTEI = { 34, 1, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRTEInfo k_emlrtRTEI = { 21, 5, "squeeze",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/squeeze.m" };

static emlrtRTEInfo l_emlrtRTEI = { 51, 1, "squeeze",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/squeeze.m" };

static emlrtRTEInfo m_emlrtRTEI = { 52, 1, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRTEInfo n_emlrtRTEI = { 53, 1, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRTEInfo o_emlrtRTEI = { 61, 5, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRTEInfo p_emlrtRTEI = { 78, 13, "eml_sort",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort.m" };

static emlrtRTEInfo q_emlrtRTEI = { 27, 5, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRTEInfo r_emlrtRTEI = { 1, 20, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRTEInfo s_emlrtRTEI = { 145, 5, "eml_sort_idx",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_sort_idx.m" };

static emlrtRTEInfo t_emlrtRTEI = { 1, 14, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

emlrtRTEInfo u_emlrtRTEI = { 71, 1, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtRTEInfo v_emlrtRTEI = { 72, 1, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtRTEInfo w_emlrtRTEI = { 1, 1, "TransitiveKNN_part2_api", "" };

static emlrtRTEInfo x_emlrtRTEI = { 12, 1, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtRTEInfo y_emlrtRTEI = { 13, 5, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtBCInfo emlrtBCI = { -1, -1, 14, 49, "errorMat",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo b_emlrtBCI = { -1, -1, 14, 51, "errorMat",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo c_emlrtBCI = { -1, -1, 15, 39, "overSafeResults",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo d_emlrtBCI = { -1, -1, 15, 41, "overSafeResults",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo e_emlrtBCI = { -1, -1, 22, 29, "uOSRinds",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtECInfo emlrtECI = { -1, 22, 29, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtBCInfo f_emlrtBCI = { -1, -1, 24, 13, "uOSRFinalinds",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtECInfo b_emlrtECI = { -1, 24, 13, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtBCInfo g_emlrtBCI = { -1, -1, 25, 13, "uOSRFinalinds",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo h_emlrtBCI = { -1, -1, 28, 20, "CSH_ann",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo i_emlrtBCI = { -1, -1, 28, 22, "CSH_ann",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtECInfo c_emlrtECI = { -1, 28, 10, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtBCInfo j_emlrtBCI = { -1, -1, 28, 37, "CSH_ann",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo k_emlrtBCI = { -1, -1, 28, 39, "CSH_ann",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtECInfo d_emlrtECI = { -1, 28, 27, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtBCInfo l_emlrtBCI = { -1, -1, 30, 22, "sortedErrors",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo m_emlrtBCI = { -1, -1, 30, 24, "sortedErrors",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtECInfo e_emlrtECI = { -1, 30, 9, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m" };

static emlrtDCInfo emlrtDCI = { 8, 34, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 1 };

static emlrtDCInfo b_emlrtDCI = { 8, 34, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 4 };

static emlrtDCInfo c_emlrtDCI = { 8, 59, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 1 };

static emlrtDCInfo d_emlrtDCI = { 8, 59, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 4 };

static emlrtDCInfo e_emlrtDCI = { 9, 17, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 1 };

static emlrtDCInfo f_emlrtDCI = { 9, 17, "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 4 };

static emlrtBCInfo n_emlrtBCI = { -1, -1, 16, 16, "OSR", "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo o_emlrtBCI = { -1, -1, 20, 34, "numUniqueResultsPerPixel",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo p_emlrtBCI = { -1, -1, 20, 36, "numUniqueResultsPerPixel",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo q_emlrtBCI = { -1, -1, 25, 42, "uOSRinds",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo r_emlrtBCI = { -1, -1, 28, 63, "sOSR", "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtBCInfo s_emlrtBCI = { -1, -1, 30, 31, "sErrors",
  "TransitiveKNN_part2",
  "D:/Dropbox/CSH/CSH_code_v3/C_and_Mex/TransitiveKNN_part2.m", 0 };

static emlrtRSInfo pd_emlrtRSI = { 14, "eml_index_rdivide",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m"
};

static emlrtRSInfo qd_emlrtRSI = { 45, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtRSInfo rd_emlrtRSI = { 51, "eml_int_forloop_overflow_check",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtRSInfo sd_emlrtRSI = { 239, "find",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/find.m" };

static emlrtRSInfo td_emlrtRSI = { 46, "diff",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/datafun/diff.m" };

static emlrtRSInfo ud_emlrtRSI = { 33, "ind2sub",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/elmat/ind2sub.m" };

static emlrtRSInfo vd_emlrtRSI = { 52, "eml_int_forloop_overflow_check",
  "C:/Program Files/MATLAB/R2013b/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_uint8_T *y);
static const mxArray *b_emlrt_marshallOut(emxArray_real_T *u);
static void b_emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void b_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static const mxArray *b_message(const emlrtStack *sp, const mxArray *b,
  emlrtMCInfo *location);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *k, const
  char_T *identifier);
static const mxArray *c_emlrt_marshallOut(emxArray_real_T *u);
static void c_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void check_forloop_overflow_error(const emlrtStack *sp);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void d_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void diff(const emlrtStack *sp, const emxArray_real_T *x, emxArray_real_T
                 *y);
static int32_T div_s32(const emlrtStack *sp, int32_T numerator, int32_T
  denominator);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *overSafeResults, const char_T *identifier, emxArray_real_T *y);
static void eml_sort(const emlrtStack *sp, const emxArray_real_T *x,
                     emxArray_real_T *y, emxArray_int32_T *idx);
static void eml_sort_idx(const emlrtStack *sp, const emxArray_real_T *x,
  emxArray_int32_T *idx);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *A, const
  char_T *identifier, emxArray_uint8_T *y);
static const mxArray *emlrt_marshallOut(emxArray_real_T *u);
static void emxEnsureCapacity(const emlrtStack *sp, emxArray__common *emxArray,
  int32_T oldNumel, int32_T elementSize, const emlrtRTEInfo *srcLocation);
static void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
static void emxFree_int32_T(emxArray_int32_T **pEmxArray);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
static void emxInit_boolean_T(const emlrtStack *sp, emxArray_boolean_T
  **pEmxArray, int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T
  doPush);
static void emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void emxInit_uint8_T(const emlrtStack *sp, emxArray_uint8_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
static void error(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_uint8_T *ret);
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static const mxArray *message(const emlrtStack *sp, const mxArray *b, const
  mxArray *c, emlrtMCInfo *location);
static void squeeze(const emlrtStack *sp, const emxArray_real_T *a,
                    emxArray_real_T *b);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_uint8_T *y)
{
  g_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(emxArray_real_T *u)
{
  const mxArray *y;
  static const int32_T iv8[2] = { 0, 0 };

  const mxArray *m4;
  y = NULL;
  m4 = mxCreateNumericArray(2, (int32_T *)&iv8, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m4, (void *)u->data);
  mxSetDimensions((mxArray *)m4, u->size, 2);
  emlrtAssign(&y, m4);
  return y;
}

static void b_emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_int32_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_int32_T *)emlrtMallocMex(sizeof(emxArray_int32_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_int32_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (int32_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void b_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static const mxArray *b_message(const emlrtStack *sp, const mxArray *b,
  emlrtMCInfo *location)
{
  const mxArray *pArray;
  const mxArray *m7;
  pArray = b;
  return emlrtCallMATLABR2012b(sp, 1, &m7, 1, &pArray, "message", TRUE, location);
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *k, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(k), &thisId);
  emlrtDestroyArray(&k);
  return y;
}

static const mxArray *c_emlrt_marshallOut(emxArray_real_T *u)
{
  const mxArray *y;
  static const int32_T iv9[3] = { 0, 0, 0 };

  const mxArray *m5;
  y = NULL;
  m5 = mxCreateNumericArray(3, (int32_T *)&iv9, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m5, (void *)u->data);
  mxSetDimensions((mxArray *)m5, u->size, 3);
  emlrtAssign(&y, m5);
  return y;
}

static void c_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 *
 */
static void check_forloop_overflow_error(const emlrtStack *sp)
{
  const mxArray *y;
  static const int32_T iv4[2] = { 1, 34 };

  const mxArray *m1;
  char_T cv2[34];
  int32_T i;
  static const char_T cv3[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o',
    'l', 'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o',
    'p', '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  const mxArray *b_y;
  static const int32_T iv5[2] = { 1, 23 };

  char_T cv4[23];
  static const char_T cv5[23] = { 'c', 'o', 'd', 'e', 'r', '.', 'i', 'n', 't',
    'e', 'r', 'n', 'a', 'l', '.', 'i', 'n', 'd', 'e', 'x', 'I', 'n', 't' };

  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = sp;
  b_st.tls = sp->tls;
  y = NULL;
  m1 = mxCreateCharArray(2, iv4);
  for (i = 0; i < 34; i++) {
    cv2[i] = cv3[i];
  }

  emlrtInitCharArrayR2013a(sp, 34, m1, cv2);
  emlrtAssign(&y, m1);
  b_y = NULL;
  m1 = mxCreateCharArray(2, iv5);
  for (i = 0; i < 23; i++) {
    cv4[i] = cv5[i];
  }

  emlrtInitCharArrayR2013a(sp, 23, m1, cv4);
  emlrtAssign(&b_y, m1);
  st.site = &rd_emlrtRSI;
  b_st.site = &vd_emlrtRSI;
  error(&st, message(&b_st, y, b_y, &emlrtMCI), &b_emlrtMCI);
}

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void d_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 *
 */
static void diff(const emlrtStack *sp, const emxArray_real_T *x, emxArray_real_T
                 *y)
{
  int32_T iyLead;
  boolean_T overflow;
  const mxArray *b_y;
  static const int32_T iv6[2] = { 1, 36 };

  const mxArray *m2;
  char_T cv6[36];
  int32_T i;
  static const char_T cv7[36] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o',
    'l', 'b', 'o', 'x', ':', 'a', 'u', 't', 'o', 'D', 'i', 'm', 'I', 'n', 'c',
    'o', 'm', 'p', 'a', 't', 'i', 'b', 'i', 'l', 'i', 't', 'y' };

  emxArray_real_T *b_y1;
  real_T work_data_idx_0;
  int32_T m;
  real_T tmp1;
  real_T tmp2;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = sp;
  c_st.tls = sp->tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  if (x->size[0] == 0) {
    iyLead = y->size[0] * y->size[1];
    y->size[0] = 0;
    y->size[1] = 1;
    emxEnsureCapacity(sp, (emxArray__common *)y, iyLead, (int32_T)sizeof(real_T),
                      &t_emlrtRTEI);
  } else {
    st.site = &gc_emlrtRSI;
    if (muIntScalarMin_sint32(x->size[0] - 1, 1) < 1) {
      iyLead = y->size[0] * y->size[1];
      y->size[0] = 0;
      y->size[1] = 0;
      emxEnsureCapacity(sp, (emxArray__common *)y, iyLead, (int32_T)sizeof
                        (real_T), &t_emlrtRTEI);
    } else {
      overflow = (x->size[0] != 1);
      if (overflow) {
      } else {
        b_y = NULL;
        m2 = mxCreateCharArray(2, iv6);
        for (i = 0; i < 36; i++) {
          cv6[i] = cv7[i];
        }

        emlrtInitCharArrayR2013a(sp, 36, m2, cv6);
        emlrtAssign(&b_y, m2);
        st.site = &qd_emlrtRSI;
        c_st.site = &td_emlrtRSI;
        error(&st, b_message(&c_st, b_y, &e_emlrtMCI), &f_emlrtMCI);
      }

      emxInit_real_T(sp, &b_y1, 1, &v_emlrtRTEI, TRUE);
      iyLead = b_y1->size[0];
      b_y1->size[0] = x->size[0] - 1;
      emxEnsureCapacity(sp, (emxArray__common *)b_y1, iyLead, (int32_T)sizeof
                        (real_T), &v_emlrtRTEI);
      i = x->size[0] - 1;
      if (!(i == 0)) {
        i = 1;
        iyLead = 0;
        work_data_idx_0 = x->data[0];
        st.site = &fc_emlrtRSI;
        if (2 > x->size[0]) {
          overflow = FALSE;
        } else {
          overflow = (x->size[0] > 2147483646);
        }

        if (overflow) {
          b_st.site = &l_emlrtRSI;
          check_forloop_overflow_error(&b_st);
        }

        for (m = 2; m <= x->size[0]; m++) {
          tmp1 = x->data[i];
          st.site = &ec_emlrtRSI;
          tmp2 = work_data_idx_0;
          work_data_idx_0 = tmp1;
          tmp1 -= tmp2;
          i++;
          b_y1->data[iyLead] = tmp1;
          iyLead++;
        }
      }

      i = b_y1->size[0];
      iyLead = y->size[0] * y->size[1];
      y->size[0] = i;
      emxEnsureCapacity(sp, (emxArray__common *)y, iyLead, (int32_T)sizeof
                        (real_T), &t_emlrtRTEI);
      iyLead = y->size[0] * y->size[1];
      y->size[1] = 1;
      emxEnsureCapacity(sp, (emxArray__common *)y, iyLead, (int32_T)sizeof
                        (real_T), &t_emlrtRTEI);
      i = b_y1->size[0];
      for (iyLead = 0; iyLead < i; iyLead++) {
        y->data[iyLead] = b_y1->data[iyLead];
      }

      emxFree_real_T(&b_y1);
    }
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

static int32_T div_s32(const emlrtStack *sp, int32_T numerator, int32_T
  denominator)
{
  int32_T quotient;
  uint32_T absNumerator;
  uint32_T absDenominator;
  int32_T quotientNeedsNegation;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }

    emlrtDivisionByZeroErrorR2012b(0, sp);
  } else {
    if (numerator >= 0) {
      absNumerator = (uint32_T)numerator;
    } else {
      absNumerator = (uint32_T)-numerator;
    }

    if (denominator >= 0) {
      absDenominator = (uint32_T)denominator;
    } else {
      absDenominator = (uint32_T)-denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    absNumerator /= absDenominator;
    if ((uint32_T)quotientNeedsNegation) {
      quotient = -(int32_T)absNumerator;
    } else {
      quotient = (int32_T)absNumerator;
    }
  }

  return quotient;
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *overSafeResults, const char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  f_emlrt_marshallIn(sp, emlrtAlias(overSafeResults), &thisId, y);
  emlrtDestroyArray(&overSafeResults);
}

/*
 *
 */
static void eml_sort(const emlrtStack *sp, const emxArray_real_T *x,
                     emxArray_real_T *y, emxArray_int32_T *idx)
{
  int32_T dim;
  int32_T vlen;
  emxArray_real_T *vwork;
  int32_T i1;
  uint32_T unnamed_idx_0;
  int32_T vstride;
  int32_T k;
  boolean_T b3;
  emxArray_int32_T *iidx;
  int32_T ix;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  st.site = &n_emlrtRSI;
  dim = 2;
  if (x->size[0] != 1) {
    dim = 1;
  }

  st.site = &o_emlrtRSI;
  if (dim <= 1) {
    vlen = x->size[0];
  } else {
    vlen = 1;
  }

  emxInit_real_T(sp, &vwork, 1, &m_emlrtRTEI, TRUE);
  i1 = vwork->size[0];
  vwork->size[0] = vlen;
  emxEnsureCapacity(sp, (emxArray__common *)vwork, i1, (int32_T)sizeof(real_T),
                    &m_emlrtRTEI);
  i1 = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)y, i1, (int32_T)sizeof(real_T),
                    &n_emlrtRTEI);
  unnamed_idx_0 = (uint32_T)x->size[0];
  i1 = idx->size[0];
  idx->size[0] = (int32_T)unnamed_idx_0;
  emxEnsureCapacity(sp, (emxArray__common *)idx, i1, (int32_T)sizeof(int32_T),
                    &o_emlrtRTEI);
  st.site = &p_emlrtRSI;
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x->size[0];
    k = 2;
  }

  st.site = &q_emlrtRSI;
  st.site = &q_emlrtRSI;
  st.site = &r_emlrtRSI;
  i1 = -1;
  st.site = &s_emlrtRSI;
  st.site = &t_emlrtRSI;
  if (1 > vstride) {
    b3 = FALSE;
  } else {
    b3 = (vstride > 2147483646);
  }

  if (b3) {
    b_st.site = &l_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }

  dim = 1;
  b_emxInit_int32_T(sp, &iidx, 1, &p_emlrtRTEI, TRUE);
  while (dim <= vstride) {
    st.site = &u_emlrtRSI;
    i1++;
    st.site = &v_emlrtRSI;
    ix = i1 + 1;
    for (k = 0; k < vlen; k++) {
      vwork->data[k] = x->data[ix - 1];
      st.site = &w_emlrtRSI;
      ix += vstride;
    }

    st.site = &x_emlrtRSI;
    eml_sort_idx(&st, vwork, iidx);
    ix = i1;
    for (k = 0; k < vlen; k++) {
      y->data[ix] = vwork->data[iidx->data[k] - 1];
      idx->data[ix] = iidx->data[k];
      st.site = &y_emlrtRSI;
      ix += vstride;
    }

    dim++;
  }

  emxFree_int32_T(&iidx);
  emxFree_real_T(&vwork);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/*
 *
 */
static void eml_sort_idx(const emlrtStack *sp, const emxArray_real_T *x,
  emxArray_int32_T *idx)
{
  uint32_T unnamed_idx_0;
  int32_T k;
  boolean_T overflow;
  boolean_T guard2 = FALSE;
  emxArray_int32_T *idx0;
  int32_T i;
  int32_T i2;
  int32_T j;
  int32_T pEnd;
  int32_T p;
  int32_T q;
  int32_T qEnd;
  int32_T kEnd;
  boolean_T guard1 = FALSE;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  unnamed_idx_0 = (uint32_T)x->size[0];
  k = idx->size[0];
  idx->size[0] = (int32_T)unnamed_idx_0;
  emxEnsureCapacity(sp, (emxArray__common *)idx, k, (int32_T)sizeof(int32_T),
                    &q_emlrtRTEI);
  st.site = &eb_emlrtRSI;
  if (x->size[0] == 0) {
    st.site = &fb_emlrtRSI;
  } else {
    st.site = &gb_emlrtRSI;
    overflow = (x->size[0] > 2147483646);
    if (overflow) {
      b_st.site = &l_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

    for (k = 1; k <= x->size[0]; k++) {
      idx->data[k - 1] = k;
    }

    st.site = &hb_emlrtRSI;
    st.site = &hb_emlrtRSI;
    if (1 > x->size[0] - 1) {
      overflow = FALSE;
    } else {
      overflow = (x->size[0] - 1 > 2147483645);
    }

    if (overflow) {
      b_st.site = &l_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

    for (k = 1; k <= x->size[0] - 1; k += 2) {
      st.site = &ib_emlrtRSI;
      st.site = &ib_emlrtRSI;
      guard2 = FALSE;
      if (x->data[k - 1] <= x->data[k]) {
        guard2 = TRUE;
      } else if (muDoubleScalarIsNaN(x->data[k])) {
        guard2 = TRUE;
      } else {
        overflow = FALSE;
      }

      if (guard2 == TRUE) {
        overflow = TRUE;
      }

      if (overflow) {
      } else {
        st.site = &jb_emlrtRSI;
        idx->data[k - 1] = k + 1;
        st.site = &ob_emlrtRSI;
        idx->data[k] = k;
      }
    }

    b_emxInit_int32_T(sp, &idx0, 1, &s_emlrtRTEI, TRUE);
    k = idx0->size[0];
    idx0->size[0] = x->size[0];
    emxEnsureCapacity(sp, (emxArray__common *)idx0, k, (int32_T)sizeof(int32_T),
                      &r_emlrtRTEI);
    i = x->size[0];
    for (k = 0; k < i; k++) {
      idx0->data[k] = 1;
    }

    i = 2;
    while (i < x->size[0]) {
      st.site = &kb_emlrtRSI;
      i2 = i << 1;
      j = 1;
      st.site = &lb_emlrtRSI;
      for (pEnd = 1 + i; pEnd < x->size[0] + 1; pEnd = qEnd + i) {
        p = j;
        q = pEnd - 1;
        st.site = &mb_emlrtRSI;
        qEnd = j + i2;
        if (qEnd > x->size[0] + 1) {
          qEnd = x->size[0] + 1;
        }

        k = 0;
        st.site = &nb_emlrtRSI;
        kEnd = qEnd - j;
        while (k + 1 <= kEnd) {
          st.site = &pb_emlrtRSI;
          guard1 = FALSE;
          if (x->data[idx->data[p - 1] - 1] <= x->data[idx->data[q] - 1]) {
            guard1 = TRUE;
          } else if (muDoubleScalarIsNaN(x->data[idx->data[q] - 1])) {
            guard1 = TRUE;
          } else {
            overflow = FALSE;
          }

          if (guard1 == TRUE) {
            overflow = TRUE;
          }

          if (overflow) {
            idx0->data[k] = idx->data[p - 1];
            st.site = &qb_emlrtRSI;
            p++;
            if (p == pEnd) {
              while (q + 1 < qEnd) {
                st.site = &rb_emlrtRSI;
                k++;
                idx0->data[k] = idx->data[q];
                st.site = &sb_emlrtRSI;
                q++;
              }
            }
          } else {
            idx0->data[k] = idx->data[q];
            st.site = &tb_emlrtRSI;
            q++;
            if (q + 1 == qEnd) {
              while (p < pEnd) {
                st.site = &ub_emlrtRSI;
                k++;
                idx0->data[k] = idx->data[p - 1];
                st.site = &vb_emlrtRSI;
                p++;
              }
            }
          }

          st.site = &wb_emlrtRSI;
          k++;
        }

        st.site = &xb_emlrtRSI;
        st.site = &yb_emlrtRSI;
        for (k = 0; k + 1 <= kEnd; k++) {
          st.site = &ac_emlrtRSI;
          idx->data[(j + k) - 1] = idx0->data[k];
        }

        j = qEnd;
        st.site = &bc_emlrtRSI;
      }

      i = i2;
    }

    emxFree_int32_T(&idx0);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *A, const
  char_T *identifier, emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  b_emlrt_marshallIn(sp, emlrtAlias(A), &thisId, y);
  emlrtDestroyArray(&A);
}

static const mxArray *emlrt_marshallOut(emxArray_real_T *u)
{
  const mxArray *y;
  static const int32_T iv7[4] = { 0, 0, 0, 0 };

  const mxArray *m3;
  y = NULL;
  m3 = mxCreateNumericArray(4, (int32_T *)&iv7, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m3, (void *)u->data);
  mxSetDimensions((mxArray *)m3, u->size, 4);
  emlrtAssign(&y, m3);
  return y;
}

static void emxEnsureCapacity(const emlrtStack *sp, emxArray__common *emxArray,
  int32_T oldNumel, int32_T elementSize, const emlrtRTEInfo *srcLocation)
{
  int32_T newNumel;
  int32_T i;
  void *newData;
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel = (int32_T)emlrtSizeMulR2012b((uint32_T)newNumel, (uint32_T)
      emxArray->size[i], srcLocation, sp);
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i = (int32_T)emlrtSizeMulR2012b((uint32_T)i, 2U, srcLocation, sp);
    }

    newData = emlrtCallocMex((uint32_T)i, (uint32_T)elementSize);
    if (newData == NULL) {
      emlrtHeapAllocationErrorR2012b(srcLocation, sp);
    }

    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, (uint32_T)(elementSize * oldNumel));
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }

    emxArray->data = newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = TRUE;
  }
}

static void emxFree_boolean_T(emxArray_boolean_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_boolean_T *)NULL) {
    if ((*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_boolean_T *)NULL;
  }
}

static void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if ((*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if ((*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxFree_uint8_T(emxArray_uint8_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_uint8_T *)NULL) {
    if ((*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_uint8_T *)NULL;
  }
}

static void emxInit_boolean_T(const emlrtStack *sp, emxArray_boolean_T
  **pEmxArray, int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T
  doPush)
{
  emxArray_boolean_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_boolean_T *)emlrtMallocMex(sizeof(emxArray_boolean_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_boolean_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (boolean_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_int32_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_int32_T *)emlrtMallocMex(sizeof(emxArray_int32_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_int32_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (int32_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_uint8_T(const emlrtStack *sp, emxArray_uint8_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush)
{
  emxArray_uint8_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_uint8_T *)emlrtMallocMex(sizeof(emxArray_uint8_T));
  if ((void *)*pEmxArray == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_uint8_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (uint8_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  if ((void *)emxArray->size == NULL) {
    emlrtHeapAllocationErrorR2012b(srcLocation, sp);
  }

  emxArray->allocatedSize = 0;
  emxArray->canFreeData = TRUE;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void error(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "error", TRUE, location);
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_uint8_T *ret)
{
  int32_T iv10[3];
  boolean_T bv0[3];
  int32_T i;
  static const int8_T iv11[3] = { -1, -1, 3 };

  int32_T iv12[3];
  for (i = 0; i < 3; i++) {
    iv10[i] = iv11[i];
    bv0[i] = TRUE;
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "uint8", FALSE, 3U, iv10, bv0, iv12);
  ret->size[0] = iv12[0];
  ret->size[1] = iv12[1];
  ret->size[2] = iv12[2];
  ret->allocatedSize = ret->size[0] * ret->size[1] * ret->size[2];
  ret->data = (uint8_T *)mxGetData(src);
  ret->canFreeData = FALSE;
  emlrtDestroyArray(&src);
}

static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", FALSE, 0U, 0);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv13[3];
  boolean_T bv1[3];
  int32_T i;
  int32_T iv14[3];
  for (i = 0; i < 3; i++) {
    iv13[i] = -1;
    bv1[i] = TRUE;
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", FALSE, 3U, iv13, bv1, iv14);
  ret->size[0] = iv14[0];
  ret->size[1] = iv14[1];
  ret->size[2] = iv14[2];
  ret->allocatedSize = ret->size[0] * ret->size[1] * ret->size[2];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = FALSE;
  emlrtDestroyArray(&src);
}

static const mxArray *message(const emlrtStack *sp, const mxArray *b, const
  mxArray *c, emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  const mxArray *m6;
  pArrays[0] = b;
  pArrays[1] = c;
  return emlrtCallMATLABR2012b(sp, 1, &m6, 2, pArrays, "message", TRUE, location);
}

/*
 *
 */
static void squeeze(const emlrtStack *sp, const emxArray_real_T *a,
                    emxArray_real_T *b)
{
  int32_T k;
  boolean_T overflow;
  int32_T sqsz[3];
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  st.site = &h_emlrtRSI;
  k = 3;
  while ((k > 2) && (a->size[2] == 1)) {
    k = 2;
  }

  if (k <= 2) {
    k = b->size[0];
    b->size[0] = 1;
    emxEnsureCapacity(sp, (emxArray__common *)b, k, (int32_T)sizeof(real_T),
                      &k_emlrtRTEI);
    st.site = &i_emlrtRSI;
    if (1 > a->size[2]) {
      overflow = FALSE;
    } else {
      overflow = (a->size[2] > 2147483646);
    }

    if (overflow) {
      b_st.site = &l_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

    for (k = 1; k <= a->size[2]; k++) {
      b->data[0] = a->data[k - 1];
    }
  } else {
    for (k = 0; k < 3; k++) {
      sqsz[k] = 1;
    }

    if (a->size[2] != 1) {
      sqsz[0] = a->size[2];
    }

    k = b->size[0];
    b->size[0] = sqsz[0];
    emxEnsureCapacity(sp, (emxArray__common *)b, k, (int32_T)sizeof(real_T),
                      &l_emlrtRTEI);
    st.site = &j_emlrtRSI;
    if (1 > a->size[2]) {
      overflow = FALSE;
    } else {
      overflow = (a->size[2] > 2147483646);
    }

    if (overflow) {
      b_st.site = &l_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

    for (k = 0; k + 1 <= a->size[2]; k++) {
      b->data[k] = a->data[k];
    }
  }
}

/*
 * function [CSH_ann,numUniqueResultsPerPixel,sortedErrors] = TransitiveKNN_part2(A,B,k,width,overSafeResults,errorMat)
 */
void TransitiveKNN_part2(const emlrtStack *sp, const emxArray_uint8_T *A, const
  emxArray_uint8_T *B, real_T k, real_T width, const emxArray_real_T
  *overSafeResults, const emxArray_real_T *errorMat, emxArray_real_T *CSH_ann,
  emxArray_real_T *numUniqueResultsPerPixel, emxArray_real_T *sortedErrors)
{
  real_T d0;
  int32_T plast;
  int32_T i0;
  real_T d1;
  int32_T idx;
  emxArray_real_T *b_CSH_ann;
  int32_T i;
  emxArray_real_T *OSR;
  emxArray_real_T *sOSR;
  emxArray_real_T *uOSRinds;
  emxArray_real_T *uOSRFinalinds;
  emxArray_real_T *sErrors;
  emxArray_int32_T *r0;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  emxArray_int32_T *v1;
  emxArray_real_T *r1;
  emxArray_real_T *b_overSafeResults;
  emxArray_real_T *b_errorMat;
  emxArray_int32_T *b_ii;
  emxArray_real_T *b_sErrors;
  int32_T j;
  int32_T isrc;
  boolean_T b0;
  boolean_T exitg4;
  boolean_T guard2 = FALSE;
  const mxArray *y;
  const mxArray *m0;
  uint32_T siz_idx_0;
  uint32_T siz_idx_1;
  int32_T exitg3;
  boolean_T guard1 = FALSE;
  boolean_T b;
  const mxArray *b_y;
  static const int32_T iv0[2] = { 1, 36 };

  char_T cv0[36];
  static const char_T cv1[36] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'i', 'n', 'd', '2', 's', 'u', 'b', '_', 'I', 'n', 'd',
    'e', 'x', 'O', 'u', 't', 'O', 'f', 'R', 'a', 'n', 'g', 'e' };

  int32_T b_v1[1];
  int32_T c_v1[1];
  int32_T iv1[3];
  uint32_T insz[4];
  uint32_T outsz[4];
  boolean_T exitg2;
  boolean_T b_guard1 = FALSE;
  static const int8_T iv2[4] = { 2, 3, 4, 1 };

  boolean_T b1;
  int32_T iwork[4];
  int32_T inc[4];
  static const int8_T iv3[4] = { 1, 2, 3, 0 };

  boolean_T b2;
  int32_T exitg1;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &st;
  e_st.tls = st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /* 'TransitiveKNN_part2:3' [hA,wA,dA] = size(A); */
  /* 'TransitiveKNN_part2:4' [hB,wB,dB] = size(B); */
  /*  sort by errors and then take the k mappings of the k smallest [unique!] errors */
  /* 'TransitiveKNN_part2:7' br_boundary_to_ignore = width-1; */
  /* 'TransitiveKNN_part2:8' numUniqueResultsPerPixel = zeros(hA-br_boundary_to_ignore,wA-br_boundary_to_ignore); */
  d0 = (real_T)A->size[0] - (width - 1.0);
  d0 = emlrtNonNegativeCheckFastR2012b(d0, &b_emlrtDCI, sp);
  plast = (int32_T)emlrtIntegerCheckFastR2012b(d0, &emlrtDCI, sp);
  d0 = (real_T)A->size[1] - (width - 1.0);
  d0 = emlrtNonNegativeCheckFastR2012b(d0, &d_emlrtDCI, sp);
  emlrtIntegerCheckFastR2012b(d0, &c_emlrtDCI, sp);
  i0 = numUniqueResultsPerPixel->size[0] * numUniqueResultsPerPixel->size[1];
  numUniqueResultsPerPixel->size[0] = plast;
  emxEnsureCapacity(sp, (emxArray__common *)numUniqueResultsPerPixel, i0,
                    (int32_T)sizeof(real_T), &emlrtRTEI);
  d0 = (real_T)A->size[0] - (width - 1.0);
  d0 = emlrtNonNegativeCheckFastR2012b(d0, &b_emlrtDCI, sp);
  emlrtIntegerCheckFastR2012b(d0, &emlrtDCI, sp);
  d0 = (real_T)A->size[1] - (width - 1.0);
  d0 = emlrtNonNegativeCheckFastR2012b(d0, &d_emlrtDCI, sp);
  plast = (int32_T)emlrtIntegerCheckFastR2012b(d0, &c_emlrtDCI, sp);
  i0 = numUniqueResultsPerPixel->size[0] * numUniqueResultsPerPixel->size[1];
  numUniqueResultsPerPixel->size[1] = plast;
  emxEnsureCapacity(sp, (emxArray__common *)numUniqueResultsPerPixel, i0,
                    (int32_T)sizeof(real_T), &emlrtRTEI);
  d0 = (real_T)A->size[0] - (width - 1.0);
  d0 = emlrtNonNegativeCheckFastR2012b(d0, &b_emlrtDCI, sp);
  d1 = (real_T)A->size[1] - (width - 1.0);
  d1 = emlrtNonNegativeCheckFastR2012b(d1, &d_emlrtDCI, sp);
  idx = (int32_T)emlrtIntegerCheckFastR2012b(d0, &emlrtDCI, sp) * (int32_T)
    emlrtIntegerCheckFastR2012b(d1, &c_emlrtDCI, sp);
  for (i0 = 0; i0 < idx; i0++) {
    numUniqueResultsPerPixel->data[i0] = 0.0;
  }

  b_emxInit_real_T(sp, &b_CSH_ann, 4, &h_emlrtRTEI, TRUE);

  /* 'TransitiveKNN_part2:9' CSH_ann = zeros(k,hA,wA,2); */
  d0 = emlrtNonNegativeCheckFastR2012b(k, &f_emlrtDCI, sp);
  emlrtIntegerCheckFastR2012b(d0, &e_emlrtDCI, sp);
  i0 = b_CSH_ann->size[0] * b_CSH_ann->size[1] * b_CSH_ann->size[2] *
    b_CSH_ann->size[3];
  b_CSH_ann->size[0] = (int32_T)k;
  emxEnsureCapacity(sp, (emxArray__common *)b_CSH_ann, i0, (int32_T)sizeof
                    (real_T), &emlrtRTEI);
  d0 = emlrtNonNegativeCheckFastR2012b(k, &f_emlrtDCI, sp);
  emlrtIntegerCheckFastR2012b(d0, &e_emlrtDCI, sp);
  plast = A->size[0];
  i0 = b_CSH_ann->size[0] * b_CSH_ann->size[1] * b_CSH_ann->size[2] *
    b_CSH_ann->size[3];
  b_CSH_ann->size[1] = plast;
  emxEnsureCapacity(sp, (emxArray__common *)b_CSH_ann, i0, (int32_T)sizeof
                    (real_T), &emlrtRTEI);
  d0 = emlrtNonNegativeCheckFastR2012b(k, &f_emlrtDCI, sp);
  emlrtIntegerCheckFastR2012b(d0, &e_emlrtDCI, sp);
  plast = A->size[1];
  i0 = b_CSH_ann->size[0] * b_CSH_ann->size[1] * b_CSH_ann->size[2] *
    b_CSH_ann->size[3];
  b_CSH_ann->size[2] = plast;
  b_CSH_ann->size[3] = 2;
  emxEnsureCapacity(sp, (emxArray__common *)b_CSH_ann, i0, (int32_T)sizeof
                    (real_T), &emlrtRTEI);
  d0 = emlrtNonNegativeCheckFastR2012b(k, &f_emlrtDCI, sp);
  idx = (int32_T)emlrtIntegerCheckFastR2012b(d0, &e_emlrtDCI, sp) * A->size[0] *
    A->size[1] << 1;
  for (i0 = 0; i0 < idx; i0++) {
    b_CSH_ann->data[i0] = 0.0;
  }

  /* 'TransitiveKNN_part2:10' sortedErrors = zeros(hA,wA,k); */
  plast = A->size[0];
  i0 = sortedErrors->size[0] * sortedErrors->size[1] * sortedErrors->size[2];
  sortedErrors->size[0] = plast;
  emxEnsureCapacity(sp, (emxArray__common *)sortedErrors, i0, (int32_T)sizeof
                    (real_T), &emlrtRTEI);
  plast = A->size[1];
  i0 = sortedErrors->size[0] * sortedErrors->size[1] * sortedErrors->size[2];
  sortedErrors->size[1] = plast;
  emxEnsureCapacity(sp, (emxArray__common *)sortedErrors, i0, (int32_T)sizeof
                    (real_T), &emlrtRTEI);
  i0 = sortedErrors->size[0] * sortedErrors->size[1] * sortedErrors->size[2];
  sortedErrors->size[2] = (int32_T)k;
  emxEnsureCapacity(sp, (emxArray__common *)sortedErrors, i0, (int32_T)sizeof
                    (real_T), &emlrtRTEI);
  idx = A->size[0] * A->size[1] * (int32_T)k;
  for (i0 = 0; i0 < idx; i0++) {
    sortedErrors->data[i0] = 0.0;
  }

  /*  CSH_errors = zeros(hA,wA,k); */
  /* 'TransitiveKNN_part2:12' for i = 1 : hA-br_boundary_to_ignore */
  d0 = (real_T)A->size[0] - (width - 1.0);
  emlrtForLoopVectorCheckR2012b(1.0, 1.0, d0, mxDOUBLE_CLASS, (int32_T)d0,
    &x_emlrtRTEI, sp);
  i = 0;
  emxInit_real_T(sp, &OSR, 1, &d_emlrtRTEI, TRUE);
  emxInit_real_T(sp, &sOSR, 1, &e_emlrtRTEI, TRUE);
  emxInit_real_T(sp, &uOSRinds, 1, &f_emlrtRTEI, TRUE);
  emxInit_real_T(sp, &uOSRFinalinds, 1, &g_emlrtRTEI, TRUE);
  emxInit_real_T(sp, &sErrors, 1, &emlrtRTEI, TRUE);
  emxInit_int32_T(sp, &r0, 2, &emlrtRTEI, TRUE);
  emxInit_boolean_T(sp, &x, 2, &emlrtRTEI, TRUE);
  b_emxInit_int32_T(sp, &ii, 1, &i_emlrtRTEI, TRUE);
  b_emxInit_int32_T(sp, &v1, 1, &j_emlrtRTEI, TRUE);
  c_emxInit_real_T(sp, &r1, 2, &emlrtRTEI, TRUE);
  d_emxInit_real_T(sp, &b_overSafeResults, 3, &emlrtRTEI, TRUE);
  d_emxInit_real_T(sp, &b_errorMat, 3, &emlrtRTEI, TRUE);
  b_emxInit_int32_T(sp, &b_ii, 1, &emlrtRTEI, TRUE);
  emxInit_real_T(sp, &b_sErrors, 1, &emlrtRTEI, TRUE);
  while (i <= (int32_T)d0 - 1) {
    /* 'TransitiveKNN_part2:13' for j = 1 : wA-br_boundary_to_ignore */
    d1 = (real_T)A->size[1] - (width - 1.0);
    emlrtForLoopVectorCheckR2012b(1.0, 1.0, d1, mxDOUBLE_CLASS, (int32_T)d1,
      &y_emlrtRTEI, sp);
    j = 0;
    while (j <= (int32_T)d1 - 1) {
      /* 'TransitiveKNN_part2:14' [sErrors,sInds] = sort(squeeze(errorMat(i,j,:))); */
      idx = errorMat->size[2];
      i0 = errorMat->size[1];
      plast = emlrtDynamicBoundsCheckFastR2012b(j + 1, 1, i0, &b_emlrtBCI, sp);
      i0 = errorMat->size[0];
      isrc = emlrtDynamicBoundsCheckFastR2012b(i + 1, 1, i0, &emlrtBCI, sp);
      i0 = b_errorMat->size[0] * b_errorMat->size[1] * b_errorMat->size[2];
      b_errorMat->size[0] = 1;
      b_errorMat->size[1] = 1;
      b_errorMat->size[2] = idx;
      emxEnsureCapacity(sp, (emxArray__common *)b_errorMat, i0, (int32_T)sizeof
                        (real_T), &emlrtRTEI);
      for (i0 = 0; i0 < idx; i0++) {
        b_errorMat->data[b_errorMat->size[0] * b_errorMat->size[1] * i0] =
          errorMat->data[((isrc + errorMat->size[0] * (plast - 1)) +
                          errorMat->size[0] * errorMat->size[1] * i0) - 1];
      }

      st.site = &emlrtRSI;
      squeeze(&st, b_errorMat, OSR);
      st.site = &emlrtRSI;
      b_st.site = &m_emlrtRSI;
      eml_sort(&b_st, OSR, sErrors, v1);

      /* 'TransitiveKNN_part2:15' OSR = squeeze(overSafeResults(i,j,:)); */
      idx = overSafeResults->size[2];
      i0 = overSafeResults->size[1];
      plast = emlrtDynamicBoundsCheckFastR2012b(j + 1, 1, i0, &d_emlrtBCI, sp);
      i0 = overSafeResults->size[0];
      isrc = emlrtDynamicBoundsCheckFastR2012b(i + 1, 1, i0, &c_emlrtBCI, sp);
      i0 = b_overSafeResults->size[0] * b_overSafeResults->size[1] *
        b_overSafeResults->size[2];
      b_overSafeResults->size[0] = 1;
      b_overSafeResults->size[1] = 1;
      b_overSafeResults->size[2] = idx;
      emxEnsureCapacity(sp, (emxArray__common *)b_overSafeResults, i0, (int32_T)
                        sizeof(real_T), &emlrtRTEI);
      for (i0 = 0; i0 < idx; i0++) {
        b_overSafeResults->data[b_overSafeResults->size[0] *
          b_overSafeResults->size[1] * i0] = overSafeResults->data[((isrc +
          overSafeResults->size[0] * (plast - 1)) + overSafeResults->size[0] *
          overSafeResults->size[1] * i0) - 1];
      }

      st.site = &b_emlrtRSI;
      squeeze(&st, b_overSafeResults, OSR);

      /* 'TransitiveKNN_part2:16' sOSR = OSR(sInds); */
      i0 = sOSR->size[0];
      sOSR->size[0] = v1->size[0];
      emxEnsureCapacity(sp, (emxArray__common *)sOSR, i0, (int32_T)sizeof(real_T),
                        &emlrtRTEI);
      idx = v1->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        plast = OSR->size[0];
        isrc = v1->data[i0];
        sOSR->data[i0] = OSR->data[emlrtDynamicBoundsCheckFastR2012b(isrc, 1,
          plast, &n_emlrtBCI, sp) - 1];
      }

      /* 'TransitiveKNN_part2:17' uOSRinds = find(diff(sOSR)~=0); */
      st.site = &c_emlrtRSI;
      b_st.site = &c_emlrtRSI;
      diff(&b_st, sOSR, r1);
      i0 = x->size[0] * x->size[1];
      x->size[0] = r1->size[0];
      x->size[1] = r1->size[1];
      emxEnsureCapacity(&st, (emxArray__common *)x, i0, (int32_T)sizeof
                        (boolean_T), &emlrtRTEI);
      idx = r1->size[0] * r1->size[1];
      for (i0 = 0; i0 < idx; i0++) {
        x->data[i0] = (r1->data[i0] != 0.0);
      }

      b_st.site = &mc_emlrtRSI;
      isrc = x->size[0] * x->size[1];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = isrc;
      emxEnsureCapacity(&b_st, (emxArray__common *)ii, i0, (int32_T)sizeof
                        (int32_T), &c_emlrtRTEI);
      c_st.site = &oc_emlrtRSI;
      if (1 > isrc) {
        b0 = FALSE;
      } else {
        b0 = (isrc > 2147483646);
      }

      if (b0) {
        d_st.site = &l_emlrtRSI;
        check_forloop_overflow_error(&d_st);
      }

      plast = 1;
      exitg4 = FALSE;
      while ((exitg4 == FALSE) && (plast <= isrc)) {
        guard2 = FALSE;
        if (x->data[plast - 1]) {
          c_st.site = &nc_emlrtRSI;
          idx++;
          ii->data[idx - 1] = plast;
          if (idx >= isrc) {
            exitg4 = TRUE;
          } else {
            guard2 = TRUE;
          }
        } else {
          guard2 = TRUE;
        }

        if (guard2 == TRUE) {
          plast++;
        }
      }

      if (idx <= isrc) {
      } else {
        y = NULL;
        m0 = mxCreateString("Assertion failed.");
        emlrtAssign(&y, m0);
        c_st.site = &sd_emlrtRSI;
        error(&c_st, y, &j_emlrtMCI);
      }

      if (isrc == 1) {
        if (idx == 0) {
          i0 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity(&b_st, (emxArray__common *)ii, i0, (int32_T)sizeof
                            (int32_T), &emlrtRTEI);
        }
      } else {
        if (1 > idx) {
          idx = 0;
        }

        i0 = b_ii->size[0];
        b_ii->size[0] = idx;
        emxEnsureCapacity(&b_st, (emxArray__common *)b_ii, i0, (int32_T)sizeof
                          (int32_T), &emlrtRTEI);
        for (i0 = 0; i0 < idx; i0++) {
          b_ii->data[i0] = ii->data[i0];
        }

        i0 = ii->size[0];
        ii->size[0] = b_ii->size[0];
        emxEnsureCapacity(&b_st, (emxArray__common *)ii, i0, (int32_T)sizeof
                          (int32_T), &emlrtRTEI);
        idx = b_ii->size[0];
        for (i0 = 0; i0 < idx; i0++) {
          ii->data[i0] = b_ii->data[i0];
        }
      }

      i0 = uOSRinds->size[0];
      uOSRinds->size[0] = ii->size[0];
      emxEnsureCapacity(&st, (emxArray__common *)uOSRinds, i0, (int32_T)sizeof
                        (real_T), &emlrtRTEI);
      idx = ii->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        uOSRinds->data[i0] = ii->data[i0];
      }

      /*  giving up (possibly) on the last index (diff gives a 1-shorter vector) */
      /* 'TransitiveKNN_part2:18' kActual = length(uOSRinds); */
      st.site = &d_emlrtRSI;

      /* 'TransitiveKNN_part2:19' uOSRFinalinds = zeros(k,1); */
      i0 = uOSRFinalinds->size[0];
      uOSRFinalinds->size[0] = (int32_T)k;
      emxEnsureCapacity(sp, (emxArray__common *)uOSRFinalinds, i0, (int32_T)
                        sizeof(real_T), &emlrtRTEI);
      idx = (int32_T)k;
      for (i0 = 0; i0 < idx; i0++) {
        uOSRFinalinds->data[i0] = 0.0;
      }

      /* 'TransitiveKNN_part2:20' numUniqueResultsPerPixel(i,j) = min(k,kActual); */
      st.site = &e_emlrtRSI;
      b_st.site = &hc_emlrtRSI;
      c_st.site = &ic_emlrtRSI;
      i0 = numUniqueResultsPerPixel->size[0];
      plast = numUniqueResultsPerPixel->size[1];
      numUniqueResultsPerPixel->data[(emlrtDynamicBoundsCheckFastR2012b(i + 1, 1,
        i0, &o_emlrtBCI, sp) + numUniqueResultsPerPixel->size[0] *
        (emlrtDynamicBoundsCheckFastR2012b(j + 1, 1, plast, &p_emlrtBCI, sp) - 1))
        - 1] = muDoubleScalarMin(k, uOSRinds->size[0]);

      /* 'TransitiveKNN_part2:21' if kActual >= k */
      if (uOSRinds->size[0] >= k) {
        /* 'TransitiveKNN_part2:22' uOSRFinalinds = uOSRinds(1:k); */
        if (1.0 > k) {
          idx = 0;
        } else {
          i0 = uOSRinds->size[0];
          emlrtDynamicBoundsCheckFastR2012b(1, 1, i0, &e_emlrtBCI, sp);
          i0 = uOSRinds->size[0];
          plast = (int32_T)k;
          idx = emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &e_emlrtBCI, sp);
        }

        emlrtVectorVectorIndexCheckR2012b(uOSRinds->size[0], 1, 1, idx,
          &emlrtECI, sp);
        i0 = uOSRFinalinds->size[0];
        uOSRFinalinds->size[0] = idx;
        emxEnsureCapacity(sp, (emxArray__common *)uOSRFinalinds, i0, (int32_T)
                          sizeof(real_T), &emlrtRTEI);
        for (i0 = 0; i0 < idx; i0++) {
          uOSRFinalinds->data[i0] = uOSRinds->data[i0];
        }
      } else {
        /* 'TransitiveKNN_part2:23' else */
        /* 'TransitiveKNN_part2:24' uOSRFinalinds(1:kActual) = uOSRinds; */
        if (1 > uOSRinds->size[0]) {
          idx = 0;
        } else {
          i0 = (int32_T)k;
          emlrtDynamicBoundsCheckFastR2012b(1, 1, i0, &f_emlrtBCI, sp);
          i0 = (int32_T)k;
          plast = uOSRinds->size[0];
          idx = emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &f_emlrtBCI, sp);
        }

        i0 = uOSRinds->size[0];
        emlrtSizeEqCheck1DFastR2012b(idx, i0, &b_emlrtECI, sp);
        i0 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = idx;
        emxEnsureCapacity(sp, (emxArray__common *)r0, i0, (int32_T)sizeof
                          (int32_T), &emlrtRTEI);
        for (i0 = 0; i0 < idx; i0++) {
          r0->data[r0->size[0] * i0] = i0;
        }

        idx = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < idx; i0++) {
          uOSRFinalinds->data[r0->data[i0]] = uOSRinds->data[i0];
        }

        /* 'TransitiveKNN_part2:25' uOSRFinalinds(kActual+1:k) = uOSRinds(end); */
        if ((real_T)uOSRinds->size[0] + 1.0 > k) {
          i0 = 0;
          plast = 0;
        } else {
          i0 = uOSRFinalinds->size[0];
          plast = (int32_T)(uOSRinds->size[0] + 1U);
          i0 = emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &g_emlrtBCI, sp)
            - 1;
          plast = uOSRFinalinds->size[0];
          isrc = (int32_T)k;
          plast = emlrtDynamicBoundsCheckFastR2012b(isrc, 1, plast, &g_emlrtBCI,
            sp);
        }

        isrc = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = plast - i0;
        emxEnsureCapacity(sp, (emxArray__common *)r0, isrc, (int32_T)sizeof
                          (int32_T), &emlrtRTEI);
        idx = plast - i0;
        for (plast = 0; plast < idx; plast++) {
          r0->data[r0->size[0] * plast] = i0 + plast;
        }

        idx = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < idx; i0++) {
          plast = uOSRinds->size[0];
          isrc = uOSRinds->size[0];
          uOSRFinalinds->data[r0->data[i0]] = uOSRinds->
            data[emlrtDynamicBoundsCheckFastR2012b(isrc, 1, plast, &q_emlrtBCI,
            sp) - 1];
        }

        /*  returning duplicate copies in this case */
      }

      /*  NN results: */
      /* 'TransitiveKNN_part2:28' [CSH_ann(:,i,j,2),CSH_ann(:,i,j,1)] = ind2sub([hB,wB],sOSR(uOSRFinalinds)); */
      st.site = &f_emlrtRSI;
      siz_idx_0 = (uint32_T)B->size[0];
      siz_idx_1 = (uint32_T)B->size[1];
      idx = uOSRFinalinds->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        plast = v1->size[0];
        isrc = (int32_T)uOSRFinalinds->data[i0];
        emlrtDynamicBoundsCheckFastR2012b(isrc, 1, plast, &r_emlrtBCI, &st);
      }

      b_st.site = &pc_emlrtRSI;
      b_st.site = &qc_emlrtRSI;
      c_st.site = &xc_emlrtRSI;
      b_st.site = &qc_emlrtRSI;
      plast = (int32_T)siz_idx_0 * (int32_T)siz_idx_1;
      b_st.site = &rc_emlrtRSI;
      i0 = uOSRFinalinds->size[0];
      idx = 0;
      do {
        exitg3 = 0;
        if (idx <= i0 - 1) {
          guard1 = FALSE;
          if (sOSR->data[(int32_T)uOSRFinalinds->data[idx] - 1] >= 1.0) {
            c_st.site = &yc_emlrtRSI;
            if (plast >= sOSR->data[(int32_T)uOSRFinalinds->data[idx] - 1]) {
              b = TRUE;
            } else {
              guard1 = TRUE;
            }
          } else {
            guard1 = TRUE;
          }

          if (guard1 == TRUE) {
            b = FALSE;
          }

          if (!b) {
            b = FALSE;
            exitg3 = 1;
          } else {
            idx++;
          }
        } else {
          b = TRUE;
          exitg3 = 1;
        }
      } while (exitg3 == 0);

      if (b) {
      } else {
        b_y = NULL;
        m0 = mxCreateCharArray(2, iv0);
        for (isrc = 0; isrc < 36; isrc++) {
          cv0[isrc] = cv1[isrc];
        }

        emlrtInitCharArrayR2013a(&st, 36, m0, cv0);
        emlrtAssign(&b_y, m0);
        b_st.site = &rc_emlrtRSI;
        e_st.site = &ud_emlrtRSI;
        error(&b_st, b_message(&e_st, b_y, &k_emlrtMCI), &l_emlrtMCI);
      }

      b_st.site = &sc_emlrtRSI;
      i0 = v1->size[0];
      v1->size[0] = uOSRFinalinds->size[0];
      emxEnsureCapacity(&b_st, (emxArray__common *)v1, i0, (int32_T)sizeof
                        (int32_T), &emlrtRTEI);
      idx = uOSRFinalinds->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        v1->data[i0] = (int32_T)sOSR->data[(int32_T)uOSRFinalinds->data[i0] - 1]
          - 1;
      }

      b_st.site = &tc_emlrtRSI;
      i0 = ii->size[0];
      ii->size[0] = v1->size[0];
      emxEnsureCapacity(&b_st, (emxArray__common *)ii, i0, (int32_T)sizeof
                        (int32_T), &emlrtRTEI);
      idx = v1->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        c_st.site = &pd_emlrtRSI;
        ii->data[i0] = div_s32(&c_st, v1->data[i0], (int32_T)siz_idx_0);
      }

      b_st.site = &uc_emlrtRSI;
      i0 = OSR->size[0];
      OSR->size[0] = ii->size[0];
      emxEnsureCapacity(&st, (emxArray__common *)OSR, i0, (int32_T)sizeof(real_T),
                        &emlrtRTEI);
      idx = ii->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        OSR->data[i0] = ii->data[i0] + 1;
      }

      b_st.site = &vc_emlrtRSI;
      b_st.site = &vc_emlrtRSI;
      i0 = v1->size[0];
      emxEnsureCapacity(&b_st, (emxArray__common *)v1, i0, (int32_T)sizeof
                        (int32_T), &emlrtRTEI);
      idx = v1->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        v1->data[i0] -= ii->data[i0] * (int32_T)siz_idx_0;
      }

      b_st.site = &wc_emlrtRSI;
      i0 = sOSR->size[0];
      sOSR->size[0] = v1->size[0];
      emxEnsureCapacity(&st, (emxArray__common *)sOSR, i0, (int32_T)sizeof
                        (real_T), &emlrtRTEI);
      idx = v1->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        sOSR->data[i0] = v1->data[i0] + 1;
      }

      idx = b_CSH_ann->size[0];
      i0 = v1->size[0];
      v1->size[0] = idx;
      emxEnsureCapacity(sp, (emxArray__common *)v1, i0, (int32_T)sizeof(int32_T),
                        &emlrtRTEI);
      for (i0 = 0; i0 < idx; i0++) {
        v1->data[i0] = i0;
      }

      i0 = b_CSH_ann->size[1];
      plast = i + 1;
      emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &h_emlrtBCI, sp);
      i0 = b_CSH_ann->size[2];
      plast = j + 1;
      emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &i_emlrtBCI, sp);
      b_v1[0] = v1->size[0];
      emlrtSubAssignSizeCheckR2012b(b_v1, 1, *(int32_T (*)[1])sOSR->size, 1,
        &c_emlrtECI, sp);
      idx = sOSR->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        b_CSH_ann->data[((v1->data[i0] + b_CSH_ann->size[0] * i) +
                         b_CSH_ann->size[0] * b_CSH_ann->size[1] * j) +
          b_CSH_ann->size[0] * b_CSH_ann->size[1] * b_CSH_ann->size[2]] =
          sOSR->data[i0];
      }

      idx = b_CSH_ann->size[0];
      i0 = v1->size[0];
      v1->size[0] = idx;
      emxEnsureCapacity(sp, (emxArray__common *)v1, i0, (int32_T)sizeof(int32_T),
                        &emlrtRTEI);
      for (i0 = 0; i0 < idx; i0++) {
        v1->data[i0] = i0;
      }

      i0 = b_CSH_ann->size[1];
      plast = i + 1;
      emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &j_emlrtBCI, sp);
      i0 = b_CSH_ann->size[2];
      plast = j + 1;
      emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &k_emlrtBCI, sp);
      c_v1[0] = v1->size[0];
      emlrtSubAssignSizeCheckR2012b(c_v1, 1, *(int32_T (*)[1])OSR->size, 1,
        &d_emlrtECI, sp);
      idx = OSR->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        b_CSH_ann->data[(v1->data[i0] + b_CSH_ann->size[0] * i) +
          b_CSH_ann->size[0] * b_CSH_ann->size[1] * j] = OSR->data[i0];
      }

      /*  sorted errors: */
      /* 'TransitiveKNN_part2:30' sortedErrors(i,j,:) = sErrors(uOSRFinalinds); */
      i0 = sortedErrors->size[0];
      plast = i + 1;
      emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &l_emlrtBCI, sp);
      i0 = sortedErrors->size[1];
      plast = j + 1;
      emlrtDynamicBoundsCheckFastR2012b(plast, 1, i0, &m_emlrtBCI, sp);
      idx = sortedErrors->size[2];
      i0 = v1->size[0];
      v1->size[0] = idx;
      emxEnsureCapacity(sp, (emxArray__common *)v1, i0, (int32_T)sizeof(int32_T),
                        &emlrtRTEI);
      for (i0 = 0; i0 < idx; i0++) {
        v1->data[i0] = i0;
      }

      idx = uOSRFinalinds->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        plast = sErrors->size[0];
        isrc = (int32_T)uOSRFinalinds->data[i0];
        emlrtDynamicBoundsCheckFastR2012b(isrc, 1, plast, &s_emlrtBCI, sp);
      }

      iv1[0] = 1;
      iv1[1] = 1;
      iv1[2] = v1->size[0];
      emlrtSubAssignSizeCheckR2012b(iv1, 3, *(int32_T (*)[1])uOSRFinalinds->size,
        1, &e_emlrtECI, sp);
      i0 = b_sErrors->size[0];
      b_sErrors->size[0] = uOSRFinalinds->size[0];
      emxEnsureCapacity(sp, (emxArray__common *)b_sErrors, i0, (int32_T)sizeof
                        (real_T), &emlrtRTEI);
      idx = uOSRFinalinds->size[0];
      for (i0 = 0; i0 < idx; i0++) {
        b_sErrors->data[i0] = sErrors->data[(int32_T)uOSRFinalinds->data[i0] - 1];
      }

      plast = v1->size[0];
      for (i0 = 0; i0 < plast; i0++) {
        sortedErrors->data[(i + sortedErrors->size[0] * j) + sortedErrors->size
          [0] * sortedErrors->size[1] * v1->data[i0]] = b_sErrors->data[i0];
      }

      j++;
      emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
    }

    i++;
    emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
  }

  emxFree_real_T(&b_sErrors);
  emxFree_int32_T(&b_ii);
  emxFree_real_T(&b_errorMat);
  emxFree_real_T(&b_overSafeResults);
  emxFree_real_T(&r1);
  emxFree_int32_T(&v1);
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_int32_T(&r0);
  emxFree_real_T(&sErrors);
  emxFree_real_T(&uOSRFinalinds);
  emxFree_real_T(&uOSRinds);
  emxFree_real_T(&sOSR);
  emxFree_real_T(&OSR);

  /* 'TransitiveKNN_part2:34' CSH_ann = permute(CSH_ann,[2,3,4,1]); */
  st.site = &g_emlrtRSI;
  for (i0 = 0; i0 < 4; i0++) {
    insz[i0] = (uint32_T)b_CSH_ann->size[i0];
  }

  outsz[0] = insz[1];
  outsz[1] = insz[2];
  outsz[2] = 2U;
  outsz[3] = insz[0];
  i0 = CSH_ann->size[0] * CSH_ann->size[1] * CSH_ann->size[2] * CSH_ann->size[3];
  CSH_ann->size[0] = (int32_T)insz[1];
  CSH_ann->size[1] = (int32_T)insz[2];
  CSH_ann->size[2] = 2;
  CSH_ann->size[3] = (int32_T)insz[0];
  emxEnsureCapacity(&st, (emxArray__common *)CSH_ann, i0, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  b_st.site = &cd_emlrtRSI;
  b = TRUE;
  if (!((b_CSH_ann->size[0] == 0) || (b_CSH_ann->size[1] == 0) ||
        (b_CSH_ann->size[2] == 0))) {
    plast = 0;
    idx = 0;
    exitg2 = FALSE;
    while ((exitg2 == FALSE) && (idx + 1 < 5)) {
      b_guard1 = FALSE;
      if (b_CSH_ann->size[iv2[idx] - 1] != 1) {
        if (plast > iv2[idx]) {
          b = FALSE;
          exitg2 = TRUE;
        } else {
          plast = iv2[idx];
          b_guard1 = TRUE;
        }
      } else {
        b_guard1 = TRUE;
      }

      if (b_guard1 == TRUE) {
        idx++;
      }
    }
  }

  if (b) {
    plast = b_CSH_ann->size[0] * b_CSH_ann->size[1] * b_CSH_ann->size[2] << 1;
    b_st.site = &dd_emlrtRSI;
    c_st.site = &k_emlrtRSI;
    if (1 > plast) {
      b1 = FALSE;
    } else {
      b1 = (plast > 2147483646);
    }

    if (b1) {
      c_st.site = &l_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }

    for (idx = 0; idx + 1 <= plast; idx++) {
      CSH_ann->data[idx] = b_CSH_ann->data[idx];
    }
  } else {
    for (i0 = 0; i0 < 4; i0++) {
      iwork[i0] = 1;
    }

    for (idx = 0; idx < 3; idx++) {
      b_st.site = &ed_emlrtRSI;
      iwork[idx + 1] = iwork[idx] * (int32_T)insz[idx];
    }

    for (i0 = 0; i0 < 4; i0++) {
      inc[i0] = iwork[iv3[i0]];
    }

    for (i0 = 0; i0 < 4; i0++) {
      iwork[i0] = 0;
    }

    plast = 0;
    do {
      isrc = 0;
      for (idx = 0; idx < 3; idx++) {
        b_st.site = &fd_emlrtRSI;
        b_st.site = &fd_emlrtRSI;
        isrc += iwork[idx + 1] * inc[idx + 1];
      }

      b_st.site = &gd_emlrtRSI;
      c_st.site = &k_emlrtRSI;
      if (1U > insz[1]) {
        b2 = FALSE;
      } else {
        b2 = (insz[1] > 2147483646U);
      }

      if (b2) {
        c_st.site = &l_emlrtRSI;
        check_forloop_overflow_error(&c_st);
      }

      for (idx = 1; idx <= (int32_T)insz[1]; idx++) {
        CSH_ann->data[plast] = b_CSH_ann->data[isrc];
        b_st.site = &hd_emlrtRSI;
        plast++;
        b_st.site = &id_emlrtRSI;
        isrc += inc[0];
      }

      idx = 1;
      do {
        exitg1 = 0;
        b_st.site = &jd_emlrtRSI;
        iwork[idx]++;
        b_st.site = &kd_emlrtRSI;
        c_st.site = &ad_emlrtRSI;
        if (iwork[idx] < (int32_T)outsz[idx]) {
          exitg1 = 2;
        } else if (idx + 1 == 4) {
          exitg1 = 1;
        } else {
          iwork[idx] = 0;
          idx++;
        }
      } while (exitg1 == 0);
    } while (!(exitg1 == 1));
  }

  emxFree_real_T(&b_CSH_ann);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

void TransitiveKNN_part2_api(emlrtStack *sp, const mxArray * const prhs[6],
  const mxArray *plhs[3])
{
  emxArray_uint8_T *A;
  emxArray_uint8_T *B;
  emxArray_real_T *overSafeResults;
  emxArray_real_T *errorMat;
  emxArray_real_T *CSH_ann;
  emxArray_real_T *numUniqueResultsPerPixel;
  emxArray_real_T *sortedErrors;
  real_T k;
  real_T width;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  emxInit_uint8_T(sp, &A, 3, &w_emlrtRTEI, TRUE);
  emxInit_uint8_T(sp, &B, 3, &w_emlrtRTEI, TRUE);
  d_emxInit_real_T(sp, &overSafeResults, 3, &w_emlrtRTEI, TRUE);
  d_emxInit_real_T(sp, &errorMat, 3, &w_emlrtRTEI, TRUE);
  b_emxInit_real_T(sp, &CSH_ann, 4, &w_emlrtRTEI, TRUE);
  c_emxInit_real_T(sp, &numUniqueResultsPerPixel, 2, &w_emlrtRTEI, TRUE);
  d_emxInit_real_T(sp, &sortedErrors, 3, &w_emlrtRTEI, TRUE);

  /* Marshall function inputs */
  emlrt_marshallIn(sp, emlrtAlias(prhs[0]), "A", A);
  emlrt_marshallIn(sp, emlrtAlias(prhs[1]), "B", B);
  k = c_emlrt_marshallIn(sp, emlrtAliasP(prhs[2]), "k");
  width = c_emlrt_marshallIn(sp, emlrtAliasP(prhs[3]), "width");
  e_emlrt_marshallIn(sp, emlrtAlias(prhs[4]), "overSafeResults", overSafeResults);
  e_emlrt_marshallIn(sp, emlrtAlias(prhs[5]), "errorMat", errorMat);

  /* Invoke the target function */
  TransitiveKNN_part2(sp, A, B, k, width, overSafeResults, errorMat, CSH_ann,
                      numUniqueResultsPerPixel, sortedErrors);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(CSH_ann);
  plhs[1] = b_emlrt_marshallOut(numUniqueResultsPerPixel);
  plhs[2] = c_emlrt_marshallOut(sortedErrors);
  sortedErrors->canFreeData = FALSE;
  emxFree_real_T(&sortedErrors);
  numUniqueResultsPerPixel->canFreeData = FALSE;
  emxFree_real_T(&numUniqueResultsPerPixel);
  CSH_ann->canFreeData = FALSE;
  emxFree_real_T(&CSH_ann);
  errorMat->canFreeData = FALSE;
  emxFree_real_T(&errorMat);
  overSafeResults->canFreeData = FALSE;
  emxFree_real_T(&overSafeResults);
  B->canFreeData = FALSE;
  emxFree_uint8_T(&B);
  A->canFreeData = FALSE;
  emxFree_uint8_T(&A);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

void TransitiveKNN_part2_atexit(emlrtStack *sp)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  sp->tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(sp);
  emlrtLeaveRtStackR2012b(sp);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void TransitiveKNN_part2_initialize(emlrtStack *sp, emlrtContext *aContext)
{
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  sp->tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(sp, FALSE, 0U, 0);
  emlrtEnterRtStackR2012b(sp);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void TransitiveKNN_part2_terminate(emlrtStack *sp)
{
  emlrtLeaveRtStackR2012b(sp);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (TransitiveKNN_part2.c) */
