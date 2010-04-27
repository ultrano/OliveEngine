//#pragma once
//#include "OvMemObject.h"
//#include <vector>
//#include <deque>
//class OvValueStream : OvMemObject
//{
//
//private:
//
//	//! defend the copy constructor
//	//! if you need copying other, use OvValueStream::Copy();
//
//	OvValueStream(OvValueStream&){};
//
//	OvValueStream(const OvValueStream&){};
//
//public:
//
//	static const OvValueStream	NONE;
//
//	OvValueStream();
//	~OvValueStream();
//
//	OvValueStream&	PushInt(IN const int& rInputArg);
//	OvValueStream&	PushShort(IN const short& rInputArg);
//	OvValueStream&	PushFloat(IN const float& rInputArg);
//	OvValueStream&	PushBool(IN const bool& rInputArg);
//	OvValueStream&	PushString(IN const string& rInputArg);
//	OvValueStream&	PushString(size_t stArgSize,IN  const char* rInputArg);
//	OvValueStream&	PushByte(size_t stStreamSize,IN BYTE* pInputStream);
//
//	OvValueStream&	PopInt(OUT int& rOutputArg);
//	OvValueStream&	PopShort(OUT short& rOutputArg);
//	OvValueStream&	PopFloat(OUT float& rOutputArg);
//	OvValueStream&	PopBool(OUT bool& rOutputArg);
//	OvValueStream&	PopString(OUT string& rOutputArg);
//	OvValueStream&	PopByte(size_t stStreamSize,OUT BYTE* pOutputStream);
//
//	OvValueStream&	SkipByte(size_t stSkipByteSize);
//
//	template<typename Type_0>
//	OvValueStream&	PushStruct(Type_0& rInputArg);
//
//	template<typename Type_0>
//	OvValueStream&	PopStruct(Type_0& rInputArg);
//
//	BYTE*			GetStream();
//
//	DWORD			GetStreamSize();
//
//	void			Clear();
//
//	bool			Copy(OvValueStream& rStream);
//
//	void			ResetReadCursor();
//
//private:
//
//	vector<BYTE> m_Stream;
//	DWORD		 m_dStreamCursor;
//};
//
//
//
//template<typename Type_0>
//OvValueStream&	OvValueStream::PushStruct(Type_0& rInputArg)
//{
//	return PushByte(sizeof(Type_0),(BYTE*)&rInputArg);
//};
//
//template<typename Type_0>
//OvValueStream&	OvValueStream::PopStruct(Type_0& rInputArg)
//{
//	return PopByte(sizeof(Type_0),(BYTE*)&rInputArg);
//}
//bool	operator ==( OvValueStream& rValueStream0, OvValueStream& rValueStream1);
//bool	operator !=( OvValueStream& rValueStream0, OvValueStream& rValueStream1);
//bool	operator ==(const OvValueStream& rValueStream0,const OvValueStream& rValueStream1);
//bool	operator !=(const OvValueStream& rValueStream0,const OvValueStream& rValueStream1);