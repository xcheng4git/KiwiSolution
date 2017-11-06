#include "stdafx.h"
#include "Utility.h"


CUtility::CUtility()
{
}


CUtility::~CUtility()
{
}

CString CUtility::GetModuleDirectory()
{
	/////////////////////////////////////
	//开发时获得当前工作路径
	wchar_t pFileName[MAX_PATH];
	int nPos = GetCurrentDirectory(MAX_PATH, pFileName);
	CString strFullPath(pFileName);
	if (nPos < 0)
		return CString("");
	else
		return strFullPath;

	///////////////////////////////////////
	////获得exe文件所在目录
	//HMODULE hMod = GetModuleHandle(0);
	//wchar_t pFileName[MAX_PATH];
	//GetModuleFileName(hMod, pFileName, MAX_PATH);

	//CString strFullPath(pFileName);
	//int nPos = strFullPath.ReverseFind(_T('\\'));
	//if (nPos < 0)
	//	return CString("");
	//else
	//	return strFullPath.Left(nPos);
}

CString CUtility::GetGuid()
{
	GUID guid;
	CoCreateGuid(&guid);

	CString strGuid;
	strGuid.Format(_T("%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x"), guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return strGuid;
}

CString CUtility::MarriageStatus2String(int marriageStatus)
{
	CString strText;
	switch (marriageStatus) {
	case 0:
		strText.Format(_T("%s"), _T("未婚"));
		break;
	case 1:
		strText.Format(_T("%s"), _T("已婚"));
		break;
	case 2:
		strText.Format(_T("%s"), _T("离异"));
		break;
	case 3:
		strText.Format(_T("%s"), _T("丧偶"));
		break;
	}

	return strText;
}

CString CUtility::WorkingStatus2String(int workingStatus)
{
	CString strText;

	switch (workingStatus) {
	case 0:
		strText.Format(_T("%s"), _T("在职"));
		break;
	case 1:
		strText.Format(_T("%s"), _T("内退"));
		break;
	}

	return strText;
}
