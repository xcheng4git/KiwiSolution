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
	vector<vector<vector<int>>> _vvvParameters;     //Ԥ�裬<�����ӱ�<������<���ɵ�Ԫ��Ŀؼ�id��ѡ�����>>>
	vector<vector<int>> _vvSubformStructure;        //Ԥ�裬<�����ӱ�<�ӱ�������������������еĿؼ�����>>
	vector<vector<int>> _vvSubformRecordRange;	    //Ԥ�裬<�����ӱ�<��ѯ��¼������Χ>>

	vector<int> _vHaveDataSubform;               //<�����ӱ��Ƿ�������>
	vector<vector<CString>> _vvSubformRecid;     //<�����ӱ�<�����е�form_recidֵ>>

	vector<vector<CBookmarkEx>> _vvBookmarks;  //Ԥ�裬<�����ӱ�<ÿ���е����ɵ�Ԫ���WORD�ĵ��е���ǩ��>>>
	vector<vector<int>> _vvSubformFlags;				//Ԥ�裬<�����ӱ�<ÿ�б�ǵ�ѡ�����������ޣ��ӱ���У���>
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

