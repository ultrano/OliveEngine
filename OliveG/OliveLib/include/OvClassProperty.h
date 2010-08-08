#pragma once


//The Functions Must be Included in Const & Destructor
//Constructor << AddLink();
//Destructor  << RemoveLink();
#define OvLinkObject_DECL(__classname) private:\
	__classname*	mh_lpNext;\
	__classname*	mh_lpPrev;\
	static __classname*	msh_lpHead;\
	static __classname*	msh_lpTail;\
	inline void				AddLink()\
{\
	if (msh_lpTail)\
	{\
	msh_lpTail->mh_lpNext = this;\
	mh_lpPrev		=	msh_lpTail;\
	msh_lpTail			=	this;\
	}else{\
	msh_lpHead	=	this;\
	}\
	msh_lpTail	=	this;\
};\
	inline void				RemoveLink()\
{\
	if(msh_lpTail == this)\
	msh_lpTail	=	mh_lpPrev;\
	if(msh_lpHead == this)\
	msh_lpHead	=	mh_lpNext;\
	if (mh_lpNext)\
	mh_lpNext->mh_lpPrev = mh_lpPrev;\
	if (mh_lpPrev)\
	mh_lpPrev->mh_lpNext = mh_lpNext;\
};\
	inline __classname*		GetNextLink()const{return mh_lpNext;}; \
	inline __classname*		GetPrevLink()const{return mh_lpPrev;}; 

#define OvLinkObject_IMPL(__classname) \
	__classname* __classname::msh_lpHead(0);\
	__classname* __classname::msh_lpTail(0);