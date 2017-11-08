#pragma once

#include <windows.h>  
/* Data structure for MD5 (Message-Digest) computation */
typedef struct {
	ULONG i[2];                          /* number of _bits_ handled mod 2^64 */
	ULONG buf[4];                                           /* scratch buffer */
	unsigned char in[64];                                     /* input buffer */
	unsigned char digest[16];            /* actual digest after MD5Final call */
} MD5_CTX;


#define MD5DIGESTLEN 16  

#define PROTO_LIST(list)    list  


/*
* MTS: Each of these assumes MD5_CTX is locked against simultaneous use.
*/
typedef void(WINAPI* PMD5Init) PROTO_LIST((MD5_CTX *));
typedef void(WINAPI* PMD5Update) PROTO_LIST((MD5_CTX *, const unsigned char *, unsigned int));
typedef void(WINAPI* PMD5Final)PROTO_LIST((MD5_CTX *));

class CUtility
{
public:
	CUtility();
	~CUtility();
public:
	static CString Crypt(CString &inStr);

public:
	static CString GetModuleDirectory();
	static CString GetGuid();

	static CString MarriageStatus2String(int marriageStatus);
	static CString WorkingStatus2String(int workingStatus);

private:
	
};

class MyCryptByMD5{
public:
	const char * md5(const char * str);
	const char * Hex2ASC(const BYTE *Hex, int Len);
	PMD5Init MD5Init;
	PMD5Update MD5Update;
	PMD5Final MD5Final;
};

