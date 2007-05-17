//
// (C) Copyright by Victor Derks <vba64@xs4all.nl>
//
// See README.TXT for the details of the software licence.
//
#pragma once


#include "msfbase.h"
#include "util.h"
#include "formatetc.h"
#include "enumformatetcptr.h"


namespace MSF
{

class IDataObjectPtr : public ::IDataObjectPtr
{
public:
	IDataObjectPtr() : ::IDataObjectPtr()
	{
	}


	explicit IDataObjectPtr(const CLSID& clsid, IUnknown* pOuter = NULL, DWORD dwClsContext = CLSCTX_ALL) :
		::IDataObjectPtr(clsid, pOuter, dwClsContext)
	{
	}


	// Purpose: Constructs a smart-pointer from any IUnknown-based interface pointer.
	template<typename _InterfaceType> IDataObjectPtr(_InterfaceType* p) :
		::IDataObjectPtr(p)
	{
	}


	// Purpose: Constructs a smart-pointer from any other smart pointer.
	template<typename _OtherIID> IDataObjectPtr(const _com_ptr_t<_OtherIID>& p) :
		::IDataObjectPtr(p)
	{
	}


	IDataObjectPtr(IDataObject* pInterface) :
		::IDataObjectPtr(pInterface)
	{
	}


	bool IsSupportedFormat(CLIPFORMAT clipformat, DWORD dwDirection)
	{
		IEnumFORMATETCPtr renumformatetc = EnumFormatEtc(dwDirection);

		CFormatEtc formatetc;
		while (renumformatetc.Next(formatetc))
		{
			if (formatetc.cfFormat == clipformat)
				return true;

			formatetc.Dispose();
		}

		return false;
	}


	bool IsSupportedFormat(LPCTSTR lpszFormat, DWORD dwDirection)
	{
		return IsSupportedFormat(RegisterCf(lpszFormat), dwDirection);
	}


	IEnumFORMATETCPtr EnumFormatEtc(DWORD dwDirection)
	{
		IEnumFORMATETCPtr renumformatetc;

		RaiseExceptionIfFailed(GetInterfacePtr()->EnumFormatEtc(dwDirection, &renumformatetc));

		return renumformatetc;
	}


	void GetData(const FORMATETC& formatetc, STGMEDIUM& stgmedium)
	{
		RaiseExceptionIfFailed(GetInterfacePtr()->GetData(&const_cast<FORMATETC&>(formatetc), &stgmedium));
	}


	void SetData(const FORMATETC& formatetc, const STGMEDIUM& stgmedium, bool fRelease)
	{
		RaiseExceptionIfFailed(GetInterfacePtr()->SetData(&const_cast<FORMATETC&>(formatetc), &const_cast<STGMEDIUM&>(stgmedium), fRelease));
	}
};

} // end MSF namespace