/*
qqcrypt.h

*/


#ifndef _INCLUDED_OICQCRYPT_H_
#define _INCLUDED_OICQCRYPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define WTLOGIN_MD5_DIGEST_LENGTH	16


void WtloginOicqEncrypt(unsigned short shVersion, const char* pInBuf, int nInBufLen, const char* pKey, char* pOutBuf, int *pOutBufLen);
char WtloginOicqDecrypt(unsigned short shVersion, const char* pInBuf, int nInBufLen, const char* pKey, char* pOutBuf, int *pOutBufLen);

char *WloginRandStr(char* buffer, int len);
char *WloginRandIntStr(char* buffer, int len);

//base64
void wtlogin_base64_encode(const unsigned char *in, int len, char *out, int *out_len);
int wtlogin_base64_decode(const char *in, int len, unsigned char *out, int *out_len);

int wtlogin_base64_encode_url(const unsigned char *in_str, int length, char *out_str,int *ret_length);
int wtlogin_base64_decode_url(const unsigned char *in_str, int length, char *out_str, int *ret_length);


void WtloginMd5HashBuffer(char *outBuffer, const char *inBuffer, int length);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _INCLUDED_OICQCRYPT_H_

