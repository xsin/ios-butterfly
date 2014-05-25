#ifndef __OI_STR2_H__
#define __OI_STR2_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CHECK_RETURN(__fun) do { \
    if(__fun != 0) return -1; \
} while(0)

uint64_t WtLoginSwitch(uint64_t);
#define htonll(x) WtLoginSwitch((x))
#define ntohll(x) WtLoginSwitch((x))

#define  GetWord   WT_GetWord
#define  GetDWord  WT_GetDWord

int AddChar(char **p, int *piLenLeft, char cValue);
int AddDWord(char **p, int *piLenLeft, unsigned int lValue);
int AddString(char **p, int *piLenLeft, char *pBuf, unsigned short shBufLen);
int AddString2(char **p, int *piLenLeft, char *pBuf, unsigned short shBufLen);
int AddWord(char **p, int *piLenLeft, unsigned short shValue);
int GetBuffer(char **p, int *piLen, char *pBuf, int *piBufLen);
int GetBuffer2(char **p, int *piLen, char *pBuf, int *piBufLen);
int GetChar(char **p, int *piLen, char *cValue);
int GetDWord(char **p, int *piLen, unsigned int *plValue);
int GetString(char **p, int *piLen, char *pBuf, int iBufLen);
int GetString2(char **p, int *piLen, char *pBuf, int iBufLen);
int GetString_B(char **p, int *piLen, char *pBuf, int iBufLen);
int GetWord(char **p, int *piLen, unsigned short *pshValue);
char *MyGetToken(char *sToken, int iTokenSize, char *sString, char *sSeparator);
char *Str_Trim(char *s);
void *my_bsearch (const void *key, const void *base, size_t nmemb, size_t size, int *piEqual,  int (*compar) (const void *, const void *));

int AddBuffer(char **p, int *piLenLeft, char *pBuf, int shBufLen);

int GetDDWord(char **p, int *piLen, uint64_t *pddwValue);
int AddDDWord(char **p, int *piLenLeft, uint64_t ddwValue);

void WloginHexRead(char* sStr, int iLen, char *pDest, int *iDestLen);

const char* DumpHex(const void *pMem, size_t uDumpOffset, size_t uDumpLen);

const char *DumpPackage(const void *pPkg, int iPkgLen);

#ifdef __cplusplus
}
#endif

#endif

