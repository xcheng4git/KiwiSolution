#pragma once
class CUtility
{
public:
	CUtility();
	~CUtility();

public:
	static CString GetModuleDirectory();
	static CString GetGuid();

	static CString MarriageStatus2String(int marriageStatus);
};

