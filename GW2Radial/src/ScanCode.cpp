﻿#include <ScanCode.h>

namespace GW2Radial
{
ScanCode GetScanCode(KeyLParam lParam) {
    if (lParam.extendedFlag)
    {
        if (lParam.scanCode != 0x45)
            lParam.scanCode |= 0xE000;
    } else
    {
        if (lParam.scanCode == 0x45)
            lParam.scanCode = 0xE11D45;
        else if (lParam.scanCode == 0x54)
            lParam.scanCode = 0xE037;
    }

    return ScanCode(lParam.scanCode);
}

std::wstring GetScanCodeName(ScanCode scanCode) {
	if(IsMouse(scanCode))
	{
	    switch(scanCode)
	    {
		case ScanCode::LBUTTON:
			return L"M1";
		case ScanCode::RBUTTON:
			return L"M2";
		case ScanCode::MBUTTON:
			return L"M3";
		case ScanCode::X1BUTTON:
			return L"M4";
		case ScanCode::X2BUTTON:
			return L"M5";
		default:
			return L"[Error]";
	    }
	}

	if (scanCode >= ScanCode::NUMROW_1 && scanCode <= ScanCode::NUMROW_9) {
		wchar_t c = wchar_t(scanCode) - 1 + 0x30;
		return std::wstring(1, c);
	}
	if (ScanCode_t(scanCode) == ScanCode_t(ScanCode::NUMROW_0))
		return L"0";

	if (IsUniversalModifier(ScanCode(scanCode))) {
		switch (scanCode) {
		case ScanCode::SHIFT:
			return L"SHIFT";
		case ScanCode::CONTROL:
			return L"CONTROL";
		case ScanCode::ALT:
			return L"ALT";
		case ScanCode::META:
			return L"META";
		}
	}

	wchar_t keyName[50];
	if (GetKeyNameTextW(uint(scanCode) << 16, keyName, int(std::size(keyName))) != 0)
		return keyName;

	return L"[Error]";
}
}