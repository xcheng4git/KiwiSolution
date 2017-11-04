#pragma once

#include <vector>
using namespace std;

class CBookmarkEx
{
public:
	enum { CHKBOX, TXTBOX };
	CBookmarkEx(int type_, const wchar_t* bookmark_, int nsub_) {
		type = type_; bookmark = bookmark_; nsub = nsub_;
	}

public:
	int type;
	const wchar_t* bookmark;
	int nsub;
};

class CBookmarks;
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

	vector<int> _vHaveDataSubform;               //<若干子表是否有数据>
	vector<vector<CString>> _vvSubformRecid;     //<若干子表<若干行的form_recid值>>

	vector<vector<CBookmarkEx>> _vvBookmarks;  //预设，<若干子表<每行中的若干单元格的WORD文档中的书签类>>>
	vector<vector<int>> _vvSubformFlags;				//预设，<若干子表<每行标记单选框是哪种有无，子表的行，列>
	vector<string> _vSubformQueryString;
	
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

	void PrintData(CBookmarkEx &theBookmark, int subform, int row, char *data, CBookmarks &bookmarks);
};

