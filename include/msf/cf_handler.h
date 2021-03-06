﻿//
// (C) Copyright by Victor Derks
//
// See README.TXT for the details of the software licence.
//
#pragma once

#include "msf_base.h"
#include "util.h"

namespace msf
{

/// <summary>Base class for the Clipboard format handlers.</summary>
class ClipboardFormatHandler
{
public:
    virtual ~ClipboardFormatHandler() = default;

    ClipboardFormatHandler(const ClipboardFormatHandler&) = delete;
    ClipboardFormatHandler(ClipboardFormatHandler&&) = delete;
    ClipboardFormatHandler& operator=(const ClipboardFormatHandler&) = delete;
    ClipboardFormatHandler& operator=(ClipboardFormatHandler&&) = delete;

    [[nodiscard]] CLIPFORMAT GetClipFormat() const noexcept
    {
        return m_clipFormat;
    }

    [[nodiscard]] bool CanGetData() const noexcept
    {
        return m_canGetData;
    }

    [[nodiscard]] bool CanSetData() const noexcept
    {
        return m_canSetData;
    }

    [[nodiscard]] virtual HRESULT Validate(const FORMATETC& formatEtc) const noexcept
    {
        if (formatEtc.dwAspect != DVASPECT_CONTENT)
            return DV_E_DVASPECT;

        if (!IsBitSet(formatEtc.tymed, TYMED_HGLOBAL))
            return DV_E_TYMED;

        if (formatEtc.lindex != -1)
            return DV_E_LINDEX;

        return S_OK;
    }

    virtual void GetData(const FORMATETC&, STGMEDIUM&) const noexcept(false)
    {
    }

    virtual void SetData(const FORMATETC&, STGMEDIUM&, bool /*release*/) noexcept(false)
    {
    }

    [[nodiscard]] bool IsValid(const FORMATETC& formatEtc, const STGMEDIUM& stgmedium) const noexcept
    {
        return SUCCEEDED(Validate(formatEtc)) && formatEtc.tymed == stgmedium.tymed;
    }

protected:
    ClipboardFormatHandler(CLIPFORMAT clipFormat, bool canGetData, bool canSetData) noexcept
        : m_clipFormat{clipFormat},
          m_canGetData{canGetData},
          m_canSetData{canSetData}
    {
    }

    ClipboardFormatHandler(PCWSTR format, bool canGetData, bool canSetData)
        : m_clipFormat{Win32::RegisterClipboardFormat(format)},
          m_canGetData{canGetData},
          m_canSetData{canSetData}
    {
    }

private:
    CLIPFORMAT m_clipFormat;
    bool m_canGetData;
    bool m_canSetData;
};

} // namespace msf
