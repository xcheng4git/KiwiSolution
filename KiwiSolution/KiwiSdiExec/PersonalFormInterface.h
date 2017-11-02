#pragma once

#include <vector>
using namespace std;

class CPersonalFormInterface
{
public:
	CPersonalFormInterface();
	~CPersonalFormInterface();

	enum { EDITBX, DATEPKR, RADIOBTN, EDITNUM };
public:
	void SetCurrentFile(CString filePath);
	int m_FormID;
	virtual void ShowEditbox(int nID, char *data) = 0;
	virtual void ShowRadiobtn(int nWhich, char *data) = 0;
	virtual void ShowDatapicker(int nID, char *data) = 0;

	virtual void GetNumber(int nWhich, int &num) = 0;
	virtual void GetString(int nID, CString &str) = 0;

	virtual BOOL hasData(int isub, int irow) = 0;
protected:
	vector<vector<vector<int>>> _vvvParameters;
	vector<vector<int>> _vvSubformStructure;
	vector<int> _vHaveDataSubform;
	vector<vector<CString>> _vvSubformRecid;
	vector<vector<int>> _vvSubformRecordRange;

protected:
	CString m_strCurrentFile;
	CString m_strCurrentFolder;
	CFont m_fontEdit;
	CBitmap m_bmpClose;

protected:
	void DoSaveForm();
	void DoUpdateForm();
	void DoShowForm();
	
private:
	void ShowData(int type, int nID, char *data);
	void GetData(int type, int nID, CString &data);
	void GetData(int type, int nID, int &data);
	void GetData(int type, int nID, double &data);
};

