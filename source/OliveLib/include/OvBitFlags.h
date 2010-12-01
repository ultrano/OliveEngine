#pragma once

template<typename Type0>
class OvBitFlags : public OvMemObject
{
public:
	OvBitFlags():m_flags(0){};
	inline void	SetFlag(OvInt _flag_bit,OvBool _set);
	inline OvBool	GetFlag(OvInt _flag_bit);
	inline void	Clear( OvBool check = false );
protected:
private:
	Type0	m_flags;
};

template<typename Type0>
inline void	OvBitFlags<Type0>::SetFlag(OvInt _flag_bit,OvBool _set)
{
	if (_set)
	{
		m_flags |= 1<<_flag_bit;
	}else{
		m_flags &= ~(1<<_flag_bit);
	}
}

template<typename Type0>
inline OvBool	OvBitFlags<Type0>::GetFlag(OvInt _flag_bit)
{
	return (( m_flags & ( 1 << _flag_bit ) ) != 0);
}

template<typename Type0>
inline void	OvBitFlags<Type0>::Clear( OvBool check )
{
	m_flags = check? -1 : 0;
}

typedef	OvBitFlags<unsigned char>	Ov8SetFlags;
typedef	OvBitFlags<unsigned short>	Ov16SetFlags;
typedef	OvBitFlags<OvUInt>	Ov32SetFlags;
