//
// (C) Copyright by Victor Derks <vba64@xs4all.nl>
//
// See README.TXT for the details of the software licence.
//
#pragma once


#include "msfbase.h"
#include "pidl.h"


_COM_SMARTPTR_TYPEDEF(IPersistFolder2, __uuidof(IPersistFolder2));


namespace MSF
{

class IPersistFolder2Ptr : public ::IPersistFolder2Ptr
{
public:
	// Constructs a smart-pointer from any other smart pointer.
	//
	template<typename _OtherIID> IPersistFolder2Ptr(const _com_ptr_t<_OtherIID>& p) :
		::IPersistFolder2Ptr(p)
	{
	}


	// Constructs a smart-pointer from any IUnknown-based interface pointer.
	//
	template<typename _InterfaceType> IPersistFolder2Ptr(_InterfaceType* p) :
		::IPersistFolder2Ptr(p)
	{
	}


	void Initialize(ITEMIDLIST* pidl)
	{
		RaiseExceptionIfFailed(GetInterfacePtr()->Initialize(pidl));
	}


	void Initialize(const TCHAR* szFilename)
	{
		CPidl pidl(szFilename);

		Initialize(pidl);
	}


	CPidl GetCurFolder()
	{
		ITEMIDLIST* pidl;
		RaiseExceptionIfFailed(GetInterfacePtr()->GetCurFolder(&pidl));

		return pidl;
	}
};

}