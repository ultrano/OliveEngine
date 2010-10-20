#pragma once

template<typename Type0>
class OvBitFlags : public OvMemObject
{
public:
	OvBitFlags():m_flags(0){};
	inline void	SetFlag(int _flag_bit,bool _set);
	inline bool	GetFlag(int _flag_bit);
	inline void	Clear( bool check = false );
protected:
private:
	Type0	m_flags;
};

template<typename Type0>
inline void	OvBitFlags<Type0>::SetFlag(int _flag_bit,bool _set)
{
	if (_set)
	{
		m_flags |= 1<<_flag_bit;
	}else{
		m_flags &= ~(1<<_flag_bit);
	}
}

template<typename Type0>
inline bool	OvBitFlags<Type0>::GetFlag(int _flag_bit)
{
	return (( m_flags & ( 1 << _flag_bit ) ) == 1);
}

template<typename Type0>
inline void	OvBitFlags<Type0>::Clear( bool check )
{
	m_flags = check? -1 : 0;
}

typedef	OvBitFlags<unsigned char>	Ov8SetFlags;
typedef	OvBitFlags<unsigned short>	Ov16SetFlags;
typedef	OvBitFlags<unsigned int>	Ov32SetFlags;