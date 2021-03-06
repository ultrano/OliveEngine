
	#define CONST_GROUP_BEGIN(group)
	#define CONST_GROUP_END
	#define CONST_DECL_FLOAT(type,name,regindex,count) type name : register(c##regindex);
	#define CONST_DECL_FLOAT_ARRAY(type,name,arraycount,regindex,count) type name[arraycount] : register(c##regindex);
	#define CONST_DECL_BOOL(name,regindex) bool name : register(b##regindex);


#ifdef CONST_DECLARE_IN_APPLICATION
	#pragma once


	#undef CONST_GROUP_BEGIN
	#undef CONST_GROUP_END
	#undef CONST_DECL_FLOAT
	#undef CONST_DECL_FLOAT_ARRAY
	#undef CONST_DECL_BOOL

	#define CONST_GROUP_BEGIN(group) namespace group{
	#define CONST_DECL_FLOAT(type,name,regindex,count) const OvShaderConstInfo name(#type,#name,regindex,count);
	#define CONST_DECL_FLOAT_ARRAY(type,name,arraycount,regindex,count) const OvShaderConstInfo name(arraycount,#type,#name,regindex,count);
	#define CONST_DECL_BOOL(name,regindex) const OvShaderConstInfo name("bool",#name,regindex,1);
	#define CONST_GROUP_END };
#endif
