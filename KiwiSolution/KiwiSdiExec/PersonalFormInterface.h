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
	vector<vector<vector<int>>> _vvvParameters;     //预设，<若干子表<若干行<若干单元格的控件id或单选组序号>>>
	vector<vector<int>> _vvSubformStructure;        //预设，<若干子表<子表的行数，列数，若干列的控件类型>>
	vector<vector<int>> _vvSubformRecordRange;	    //预设，<若干子表<查询记录条数范围>>
	//vector<vector<vector<CString>>> _vvvBookmarks;  //预设，<若干子表<若干行<若干单元格的WORD文档中的书签名>>>
	//vector<int> _vSubformFlags;						//预设，<若干子表的单选框是哪种有无>

	vector<int> _vHaveDataSubform;               //<若干子表是否有数据>
	vector<vector<CString>> _vvSubformRecid;     //<若干子表<若干行的form_recid值>>

protected:
	CString m_strCurrentFile;
	CString m_strCurrentFolder;
	CFont m_fontEdit;
	CBitmap m_bmpClose;

protected:
	void DoSaveForm();
	void DoUpdateForm();
	void DoShowForm();
	void DoPrintForm(CString &templateName);

private:
	void ShowData(int type, int nID, char *data);
	void GetData(int type, int nID, CString &data);
	void GetData(int type, int nID, int &data);
	void GetData(int type, int nID, double &data);
};

