#pragma once
#include <sqlite3.h>

class CSQLiteHelper
{
public:
	CSQLiteHelper();
	virtual ~CSQLiteHelper();

	sqlite3 *db;
	void execSQL(const char *sql);
	char**rawQuery(const char *sql, int *row, int *column, char **result);
	void openDB(char *path);
	void closeDB();

};

char* U2G(const char* utf8);
char* G2U(const char* gb2312);