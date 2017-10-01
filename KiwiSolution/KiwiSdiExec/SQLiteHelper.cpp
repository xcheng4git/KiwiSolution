#include "stdafx.h"
#include "SQLiteHelper.h"

//utf-8 -->GB3212  
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
//GB2312-->UTF-8 
char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

CSQLiteHelper::CSQLiteHelper()
{
}


CSQLiteHelper::~CSQLiteHelper()
{
}

void CSQLiteHelper::execSQL(const char *sql)
{
	sqlite3_exec(db, sql, 0, 0, 0);
}

char **CSQLiteHelper::rawQuery(const char *sql, int *row, int *column, char **result)
{
	sqlite3_get_table(db, sql, &result, row, column, 0);
	return result;
}

void CSQLiteHelper::openDB(char *path)
{
	int last = sqlite3_open(path, &db);
	if (SQLITE_OK != last)
	{
		AfxMessageBox(L"打开数据库出错!");
		return;
		PostQuitMessage(0);
	}
}

void CSQLiteHelper::closeDB()
{
	sqlite3_close(db);
}