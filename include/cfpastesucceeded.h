//
// (C) Copyright by Victor Derks <vba64@xs4all.nl>
//
// See README.TXT for the details of the software licence.
//
#pragma once


#include "cfeffect.h"


namespace MSF
{

class CCfPasteSucceeded
{
public:

	static void Set(IDataObject* pdataobject, DWORD dwEffect)
	{
		RaiseExceptionIfFailed(SetImpl(pdataobject, dwEffect));
	}


	static void SetOptional(IDataObject* pdataobject, DWORD dwEffect)
	{
		HRESULT hr = SetImpl(pdataobject, dwEffect);
		if (FAILED(hr))
		{
			ATLTRACE2(atlTraceCOM, 0, _T("CCfPasteSucceeded::SetOptional failed, hr=%x\n"), hr);
		}
	}

private:

	static HRESULT SetImpl(IDataObject* pdataobject, DWORD dwEffect)
	{
		return SetCfEffect(CFSTR_PASTESUCCEEDED, pdataobject, dwEffect);
	}
};

} // end of MSF namespace