#include "OvConstDefineUtil.h"

CONST_GROUP_BEGIN(OvMatVSConst)

//CONST_DECL_BOOL(Bool_IsSkinned,0)

CONST_DECL_FLOAT(matrix,Matrix_ViewProject,0,4)
CONST_DECL_FLOAT(matrix,Matrix_WorldViewProject,4,4)
CONST_DECL_FLOAT(float4x3,Float4x3_View,8,3)
CONST_DECL_FLOAT(float3,Float3_ViewPos,11,1)
CONST_DECL_FLOAT(float4x3,Float4x3_World,12,3)
CONST_DECL_FLOAT_ARRAY(float4x3,Matrix_MatrixPalette,25,12,3)

CONST_DECL_FLOAT(float,Float_LastRegister,87,1)

CONST_GROUP_END