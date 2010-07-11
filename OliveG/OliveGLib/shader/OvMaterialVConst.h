#include "OvConstDefineUtil.h"

CONST_GROUP_BEGIN(OvMatVSConst)

//CONST_DECL_BOOL(Bool_IsSkinned,0)

CONST_DECL_FLOAT(matrix,ViewProject,0,4)
CONST_DECL_FLOAT(matrix,WorldViewProject,4,4)
CONST_DECL_FLOAT(float4x3,View,8,3)
CONST_DECL_FLOAT(float3,ViewPos,11,1)
CONST_DECL_FLOAT(float4,Time,12,1)
CONST_DECL_FLOAT(float4x3,World,13,3)
CONST_DECL_FLOAT_ARRAY(float4x3,MatrixPalette,25,13,3)

CONST_DECL_FLOAT(float,Float_LastRegister,88,1)

CONST_GROUP_END