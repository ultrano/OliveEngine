//#include "OvValueStream.h"
//
//const OvValueStream	OvValueStream::NONE;
//
//OvValueStream::OvValueStream():m_dStreamCursor(0)
//{
//	Clear();
//
//}
//OvValueStream::~OvValueStream()
//{
//	Clear();
//}
//
//OvValueStream&	OvValueStream::PushInt(const int& rInputArg)
//{
//	PushByte(sizeof(int),(BYTE*)&rInputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PushShort(IN const short& rInputArg)
//{
//	PushByte(sizeof(short),(BYTE*)&rInputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PushFloat(const float& rInputArg)
//{
//	PushByte(sizeof(float),(BYTE*)&rInputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PushBool(const bool& rInputArg)
//{
//	PushByte(sizeof(bool),(BYTE*)&rInputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PushString(size_t stArgSize, const char* rInputArg)
//{
//	PushInt((int)(sizeof(char)*stArgSize));
//	PushByte(sizeof(char)*stArgSize,(BYTE*)rInputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PushString(const string& rInputArg)
//{
//	PushString(sizeof(char)*rInputArg.size(),rInputArg.data());
//	return *this;
//}
//OvValueStream&	OvValueStream::PushByte(size_t stStreamSize,IN BYTE* pInputStream)
//{
//	try
//	{
//		for (size_t i = 0 ; i < stStreamSize ; ++i)
//		{
//			m_Stream.push_back(pInputStream[i]);
//		}
//	}
//	catch(...)
//	{
//		OvAssertMsg("Invaild Memory Access");
//	}
//	return *this;
//}
//
//OvValueStream&	OvValueStream::PopInt(int& rOutputArg)
//{
//	PopByte(sizeof(int),(BYTE*)&rOutputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PopShort(OUT short& rOutputArg)
//{
//	PopByte(sizeof(short),(BYTE*)&rOutputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PopFloat(float& rOutputArg)
//{
//	PopByte(sizeof(float),(BYTE*)&rOutputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PopBool(bool& rOutputArg)
//{
//	PopByte(sizeof(bool),(BYTE*)&rOutputArg);
//	return *this;
//}
//OvValueStream&	OvValueStream::PopString(string& rOutputArg)
//{
//	int iStringSize = 0;
//	PopInt(iStringSize);
//	rOutputArg.resize(iStringSize);
//	PopByte(sizeof(char)*iStringSize,(BYTE*)&rOutputArg[0]);
//	return *this;
//}
//
//OvValueStream&	OvValueStream::PopByte(size_t stStreamSize,OUT BYTE* pOutputStream)
//{
//	if (pOutputStream)
//	{
//		size_t stSize = m_Stream.size() - m_dStreamCursor;
//		if (stSize < stStreamSize)
//		{
//			OvAssertMsg("OverPop Stream");
//		}
//		else
//		{
//			try
//			{
//				for (size_t i=0;i<stStreamSize;++i)
//				{
//					pOutputStream[i] = m_Stream[m_dStreamCursor];
//					++m_dStreamCursor;
//				}
//			}
//			catch(...)
//			{
//				OvAssertMsg("Invaild Memory Access");
//			}
//		}
//	}
//	return *this;
//}
//OvValueStream&	OvValueStream::SkipByte(size_t stSkipByteSize)
//{
//	size_t stSize = m_Stream.size() - m_dStreamCursor;
//	if (stSize < stSkipByteSize)
//	{
//		OvAssertMsg("OverSkip Stream");
//	}
//	else
//	{
//		m_dStreamCursor += stSkipByteSize;
//	}
//	return *this;
//
//}
//
//BYTE*			OvValueStream::GetStream()
//{
//	if (m_Stream.size())
//	{
//		return &(m_Stream.front());
//	}
//	return NULL;
//}
//
//DWORD			OvValueStream::GetStreamSize()
//{
//	return m_Stream.size();
//}
//
//void			OvValueStream::Clear()
//{
//	m_Stream.clear();
//	m_dStreamCursor = 0;
//}
//
//bool			OvValueStream::Copy(OvValueStream& rStream)
//{
//	if (rStream.GetStreamSize())
//	{
//		m_Stream.resize(rStream.GetStreamSize());
//		if (m_Stream.size() != rStream.GetStreamSize())
//		{
//			return false;
//		}
//
//		if (memcpy((void*)&(m_Stream[0]),(void*)rStream.GetStream(),rStream.GetStreamSize()) == NULL)
//		{
//			return false;
//		}
//		m_dStreamCursor = 0;
//		return true;
//	}
//	return false;
//}
//
//void			OvValueStream::ResetReadCursor()
//{
//	m_dStreamCursor = 0;
//}
//
//bool	operator ==( OvValueStream& rValueStream0, OvValueStream& rValueStream1)
//{
//	return (rValueStream0.GetStream() == rValueStream1.GetStream()) && (rValueStream0.GetStreamSize() == rValueStream1.GetStreamSize());
//}
//bool	operator !=( OvValueStream& rValueStream0, OvValueStream& rValueStream1)
//{
//	return (rValueStream0.GetStream() != rValueStream1.GetStream()) || (rValueStream0.GetStreamSize() != rValueStream1.GetStreamSize());
//}
//
//bool	operator ==(const OvValueStream& rValueStream0,const OvValueStream& rValueStream1)
//{
//	return (((OvValueStream&)rValueStream0) == ((OvValueStream&)rValueStream1));
//}
//bool	operator !=(const OvValueStream& rValueStream0,const OvValueStream& rValueStream1)
//{
//	return (((OvValueStream&)rValueStream0) != ((OvValueStream&)rValueStream1));
//}