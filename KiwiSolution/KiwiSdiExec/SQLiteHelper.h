#pragma once
#include <sqlite3.h>

class CSQLiteHelper
{
public:
	CSQLiteHelper();
	virtual ~CSQLiteHelper();

	sqlite3 *db;
	void execSQL(char *sql);
	char**rawQuery(char *sql, int *row, int *column, char **result);
	void openDB(char *path);
	void closeDB();

};

char* U2G(const char* utf8);
char* G2U(const char* gb2312);