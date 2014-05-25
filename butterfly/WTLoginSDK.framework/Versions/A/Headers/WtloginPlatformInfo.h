//
//  WtloginPlatformInfo.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MemSig.h"
#import "WloginEnum.h"

@class RemortServerList;

#define MAXADDRS 32

#define MAX_GUID_CNT_IN_PASTEBOARD  8   //剪贴板中GUID的最大个数

#define ECDH_SHARE_KEY_LEN          16
#define ECDH_CLIENT_PUBKEY_LEN      128  // Client PubKeyLen

@class SafeSingleItemWrapper;

typedef enum{
    NET_STATE_3G = 1,
    NET_STATE_WIFI = 2,
    NET_STATE_NO_CONN = 0,
} NET_STATE_TYPE;



@interface WtloginPlatformInfo : NSObject  {
    NSString *macAddr;
    NSString *ipStr;
    uint32_t clientIp;
    NSString *devType;
    NSString *iosVer;
    NSString *devName; // 设备类型，比如 xxx的iphone
    NSString *osName;
    
    char *if_names[MAXADDRS];  
    char *ip_names[MAXADDRS];  
    char *hw_addrs[MAXADDRS];  
    unsigned long ip_addrs[MAXADDRS];  
    
    int nextAddr; 
    
    NSString *filePath;
    NSMutableDictionary *wtloginConfigDic;
    
    NSData *guid;
    uint8_t cIsNew;     //cNewInstall
    uint8_t cIsDiff;    //cGuidChg
    uint8_t cIsGetGuid; //cReadGuid
    uint8_t cGUIDSrc;   //GUID来源
    uint8_t cReadFailFlag;  //读取失败标志
    uint8_t cDevChgFlag;    //设备信息是否改变的标志位。对iOS来说，只关注bit3；bit3==0:表示不变；bit3==1:表示改变
    
    SafeSingleItemWrapper *ksidWrapper;
    
    MemSig *deviceSig;
    
    uint32_t dwMyVer;
    uint32_t dwMyPubNo;
    uint32_t dwMyClientType;
    
    NSString *sigFilePath;
    NSMutableDictionary *sigDictionary;
    
    //服务器地址
    RemortServerList *stServerinfo;
    
    NSString *wtloginIosSdkVer;
    NSString *wtloginBuildTime;
    uint32_t wtloginBigVer;
    
    //时间差
    int32_t dwDiffTime;
    //客户端ip
    uint32_t dwClientIP;
    
    //登录用户记录
    NSString *loginFilePath;
    NSMutableDictionary *userLoginInfo;
    
    //语言
    WTLOGIN_LANGUAGE lang;
    
    //ECDH
    NSData *ecdhShareKey;
    NSData *ecdhCliPubKey;
    uint32_t   dwEcdhSvrEnable;     // 服务端是否支持ECDH

    
    // PSKEY的domain
    NSMutableArray *domainList;
}

@property (readonly) NSString *macAddr;
@property (readonly) NSString *ipStr;
@property (readonly) uint32_t clientIp;
@property (readonly) NSString *devType;
@property (readonly) NSString *iosVer;
@property (readonly) NSString *osName;
@property (readonly) NSString *devName;

@property (retain)   NSData *guid;
@property (readonly) uint8_t cIsNew;
@property (readonly) uint8_t cIsDiff;
@property (readonly) uint8_t cIsGetGuid;
@property (readonly) uint8_t cGUIDSrc;
@property (readonly) uint8_t cReadFailFlag;
@property (readonly) uint8_t cDevChgFlag;

@property (retain) MemSig *deviceSig;

@property (assign) uint32_t dwMyVer;
@property (assign) uint32_t dwMyPubNo;
@property (assign) uint32_t dwMyClientType;

@property (readonly) NSMutableDictionary *nameDictionary;
@property (readonly) NSMutableDictionary *sigDictionary;

@property (readonly) RemortServerList *stServerinfo;


@property (readonly) NSString *wtloginIosSdkVer;
@property (readonly) NSString *wtloginBuildTime;
@property (readonly) uint32_t wtloginBigVer;

@property (assign, atomic) int32_t dwDiffTime;
@property (assign, atomic) uint32_t dwClientIP;

@property (assign) WTLOGIN_LANGUAGE lang;
@property (assign) uint32_t dwEcdhSvrEnable;
@property (readonly) NSData* ecdhShareKey;
@property (readonly) NSData* ecdhCliPubKey;

@property (readonly) NSMutableArray* domainList;


+(NET_STATE_TYPE)wtloginNetState;
+(NSString *)wtloginCrtCarrierName;

+(NSString *)dataSafeFilePathWithName:(NSString *)fileName;


-(void)wtloginPlatformDataInit;

-(id)configObjectForKey:(id)key;
-(void)setConfigObject:(id)object forKey:(id)key;

-(NET_STATE_TYPE)netState;
-(NSString *)crtCarrierName;

-(NSData *)tgtgtKeyFromKeyChain;

-(NSData *)ksidFromKeyChain;
-(BOOL)setKsidToKeyChain:(NSData *)data;

-(void)resetKeyChain;

-(BOOL)setKsidToConfig:(NSData *)data forAccount:(NSString *)account;
-(NSData *)ksidForUser:(NSString *)account;

-(BOOL)setSavePwdSigToConfig:(NSData *)data andNoPicSig:(NSData *)noPicSig forAccount:(uint32_t)dwUin;
-(NSData *)pwdSigUser:(uint32_t)dwUin;
-(NSData *)noPicSigUser:(uint32_t)dwUin;
-(void)clearPwdSigUser:(uint32_t)dwUin;


-(void)clearNameToUin:(NSString *)name;
-(BOOL)setNameToConfig:(NSString *)name forUin:(uint32_t)dwUin;


-(BOOL)setSigVailidateTime:(uint32_t)dwTime bySigType:(uint32_t)dwType;
-(uint32_t)sigVailidateBySigType:(uint32_t)dwType;

-(BOOL)resetLastLoginInfo;
-(uint32_t)lastLoginTime;
-(NSString *)lastLoginSdkVer;
-(NSString *)lastLoginAppVer;


-(NSString *)appMainBundleIndentify;
-(NSString *)appBundleShortVersionString;

-(void)writeSigDataTofile;

-(NSString *)guidForReport;
-(int)readGuidArrayFromPasteBoard:(NSMutableArray *)marray; //for tlv0x168

- (BOOL)tryDecrypt:(NSData *)inData byKey:(NSData *)inKey andOutData:(NSMutableData *)outData;

-(void)setECDHShareKey:(char *)pSharekey andPubKey:(char*)pPubKey andPubKeyLen:(int32_t)dwPubKeyLen;
-(void)enableECDH;
-(void)disableECDH;

-(void)addDomain:(NSString*)domain;
-(void)RemoveDomainList;

-(void)setLastLoginUserAccount:(NSString *)userAcctout;
-(NSString *)lastLoginUserAccount;
-(NSArray *)loginUserList;

@end


#ifndef WTLOGIN_PLATFORM_INFO
#define WTLOGIN_PLATFORM_INFO

extern WtloginPlatformInfo *wtloginPlatformInfo;
extern id wtloginLogDelegate;

void InitWtloginPlatformInfo();
void FreeWtloginPlatformInfo();


#endif