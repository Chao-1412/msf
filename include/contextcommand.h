//
// (C) Copyright by Victor Derks <vba64@xs4all.nl>
//
// See README.TXT for the details of the software licence.
//
#pragma once


#include "msfbase.h"


namespace MSF
{

class CContextCommand
{
public:
	virtual ~CContextCommand() throw()
	{
	}

	virtual void operator()(const CMINVOKECOMMANDINFO* /* pici */,
	                        const std::vector<CString>& /* filenames */)
	{
	}
};

} // end namespace MSF