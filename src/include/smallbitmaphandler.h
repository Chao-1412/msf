//
// (C) Copyright by Victor Derks
//
// See README.TXT for the details of the software licence.
//
#pragma once


#include "custommenuhandler.h"


namespace MSF
{

class CSmallBitmapHandler : public CCustomMenuHandler
{
public:

    // Purpose: small helper class to free managed handle.
    // For more advanced features use bitmap class in WTL or MFC
    class CBitmap
    {
    public:
        CBitmap(HBITMAP handle = nullptr) : m_handle(handle)
        {
        }

        ~CBitmap()
        {
            if (m_handle)
            {
                ATLVERIFY(DeleteObject(m_handle));
            }
        }


        HBITMAP GetHandle() const
        {
            return m_handle;
        }

    private:

        HBITMAP m_handle;
    };


    CSmallBitmapHandler(CString strText, UINT nResID) :
        m_strText(strText),
        m_bitmap(LoadBitmap(nResID))
    {
    }


    CSmallBitmapHandler(UINT nTextID, UINT nResID) :
        m_strText(LoadString(nTextID)),
        m_bitmap(LoadBitmap(nResID))
    {
    }


    void InitializeItemInfo(CMenuItemInfo& menuiteminfo) override
    {
        menuiteminfo.SetString(m_strText);
        menuiteminfo.SetCheckMarkBmps(nullptr, m_bitmap.GetHandle());
    }

private:

    static HBITMAP LoadBitmap(UINT nResID) noexcept
    {
        HBITMAP hbitmap = ::LoadBitmap(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(nResID));
        ATLASSERT(hbitmap && "Failed to load the bitmap, check resource id, etc");
        return hbitmap;
    }

    // Member variables.
    CString m_strText;
    CBitmap m_bitmap;
};

} // end namespace MSF
