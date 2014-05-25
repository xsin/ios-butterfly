//
//  WloginSdk.h
//  WloginIOSPlatformSDK
//
//  Created by jiezhao on 11-8-16.
//  Copyright 2011年 Tencent，即时通信产品部，server平台中心. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WloginUserInfo.h"
#import "MemSig.h"
#import "WloginCallbackProtocol.h"
#import "WloginTranCallbackProtocol.h"

#include "wtlogin_oi_tea.h"
#import "WloginEnum.h"



#ifndef __WTLOGIN_SIG_BITMAP_DEFINE__
#define __WTLOGIN_SIG_BITMAP_DEFINE__

#define WLOGIN_GET_A4 0x1
#define WLOGIN_GET_A5 0x2
#define WLOGIN_GET_MINIA2 0x4
#define WLOGIN_GET_A8   0x10
#define WLOGIN_GET_STWEB    0x20
#define WLOGIN_GET_TGT  0x40
#define WLOGIN_GET_ST   0x80
#define WLOGIN_GET_LSKEY  0x200
#define WLOGIN_GET_D3_1  0x400
#define WLOGIN_GET_SKEY  0x1000
#define WLOGIN_GET_SIG64  0x2000
#define WLOGIN_GET_OPENKEY  0x4000
#define WLOGIN_GET_TOKEN  0x8000
#define WLOGIN_GET_ST_NEW  0x10000
#define WLOGIN_GET_VKEY  0x20000
#define WLOGIN_GET_D2    0x40000
#define WLOGIN_GET_SID   0x80000
#define WLOGIN_GET_PSKEY 0x100000
#define WLOGIN_GET_AQ_SIG  0x200000  /* 安全中心票据，用于解锁、解封、解无线登录保护 */
#define WLOGIN_GET_NOPICSIG 0x80000000  //NoPicSig, 免验证码签名的票据，不提供给业务，仅有svr生成，且client在请求中带上


#endif


#define WTLOGIN_MOBILEQQ_APPID (0x10)               //手Q Appid
#define WTLOGIN_OPEN_APPID (0x2a9e5427)     //第三方业务主Appid

//登录方式
typedef enum{
    LOGIN_GEN_PASSWD_SIG = 0x1,       //使用密码登录，记住密码
    LOGIN_MD5_GEN_PASSWD_SIG = 0x3,   //使用密码MD5登录，记住密码
    LOGIN_WITH_PASSWD_SIG = 0x10,     //使用密码签名登录
} LOGIN_FLAG;


@class UserLoginProcessManager;
@class UserLoginProcess;

/*
 wlogin登录 iOS SDK
 */
@interface WloginSdk : NSObject {
    UserLoginProcessManager * userLoginProcessManager;
    dispatch_queue_t wtlogin_queue;
    
    //临时userProcess，只能在回调函数中使用
    UserLoginProcess *tmpProcess;
    
}


/***********************************************************************/
// 初始化接口，用来初始化SDK基本信息
//
/***********************************************************************/
/*
 初始化客户端基本信息
 (NSString *)strVer             客户端版本号，格式为 x.x.x.x， 例如，客户端版本为1.1，传入参数为 @"1.1.0.0" 
 (uint32_t)dwClientType         客户端类型，IOS平台，填写 1
 */
-(id)initWithBasicInfo:(NSString *)strVer andClientType:(uint32_t)dwClientType  andDelegate:(id)delegate;
/*
 设置设备IMEI
 */
-(void)setDeviceIMEI:(NSString *)sImei;

/*
 设置设备支持的验证码类型
 */
-(void)setClientPicInfo:(uint16_t)wPicType CapType:(uint8_t)cCapType PicRetType:(uint8_t)cPicRetType;

/*
 指定服务器登录
 */
-(void)setRemortServer:(NSString *)sIp andPort:(uint16_t)wPort;

/*
 指定登录的subappid
 */
-(void)setLoginSubAppid:(uint32_t)dwSubAppid;


/*
 设置拉取头像的类别
 
 wFaceImgType取值范围为1~5，如果请求包中取值非法，则server端默认返回cImgType=1 对应的头像url。
 取值和分辨率关系如下：
 40*40静态   = 1
 40*40动态gif = 2
 100*100   = 3 <不区分动静态>
 140*140   = 4 <不区分动静态>
 高清原图  = 5 <不区分动静态>
 */
-(void)setFaceImgType:(uint16_t)wFaceImgType;

-(void)setLanguage:(WTLOGIN_LANGUAGE)lang;

/* 添加SKEY的domain，不能超过5个
 * True  添加成功
 * False 添加失败
 **/
-(BOOL)addSKeyDomain:(NSString*)domain;

/* 清空域名列表 */
-(void)clearSKeyDomainList;

/***********************************************************************/
// 登录相关接口，网络操作是通过异步回调实现
//
/***********************************************************************/
/*
 检查用户是否需要输入密码登录
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串, 第三方业务支持填写Openid
         (uint32_t)dwAppid             登录的Appid，第三方业务填写第三方业务Appid
 返回值：  NO                           不需要密码登陆，可以直接调用 getStWithoutPasswd 获取票据
         YES                            需要密码登录，需要调用 getStWithPasswd
 */
-(BOOL)isNeedLoginWithPasswd:(NSString *)userAccount andAppid:(uint32_t)dwAppid;


/*
 获取登录相关票据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
         (uint32_t)dwAppid             登录的Appid，填0则根据Appid权限跳转
         (uint32_t)dwForAppid          跳转的目的Appid
         (uint32_t)dwBitmap            拉取签名bitmap
 */
-(RETURN_VALUES)loginByExchangeSig:(NSString *)userAccount byAppid:(uint32_t)dwByAppid forAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap;

-(RETURN_VALUES)loginByExchangeSig:(NSString *)userAccount byAppid:(uint32_t)dwByAppid forAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap tag:(long*)pTag;

//adwAppidList中的Appid，只能换取ST小票，第三方业务无此接口
-(RETURN_VALUES)loginByExchangeSig:(NSString *)userAccount byAppid:(uint32_t)dwByAppid forAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap
                  andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList;

-(RETURN_VALUES)loginByExchangeSig:(NSString *)userAccount byAppid:(uint32_t)dwByAppid forAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap
                  andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList  tag:(long*)pTag;

/*
 获取登录相关票据
 输入参数：
 (MemSig *)sigTGT              MSF跳转传入的A2
 (MemSig *)sigD2               MSF跳转传入的D2
 (NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwForAppid          跳转的目的Appid
 (uint32_t)dwBitmap            拉取签名bitmap
 */
//adwAppidList中的Appid，只能换取ST小票
-(RETURN_VALUES)loginByExchangeSig:(MemSig *)sigTGT byD2:(MemSig *)sigD2 forAccount:(NSString *)userAccount andAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap
                  andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList;

-(RETURN_VALUES)loginByExchangeSig:(MemSig *)sigTGT byD2:(MemSig *)sigD2 forAccount:(NSString *)userAccount andAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap
                  andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList tag:(long*)pTag;



/*
 用户输入密码登录,获取票据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
         (uint32_t)dwAppid             登录的Appid，第三方业务填写第三方业务Appid
         (NSString *)userPasswd        用户密码 / 密码一次MD5 / 密码签名sig
         (uint32_t)dwBitmap            拉取签名bitmap
         (LOGIN_FLAG)flag              登录方式，具体见LOGIN_FLAG定义
 
 说明： 当用密码登录时，userPasswd填写密码，NSString，登录成功后，回调函数返回记住密码签名，调用方可根据用户选择保存
       当用记住密码签名登录时，userPasswdSig填写签名，NSData，登录成功后，回调函数返回记住密码签名，调用方可根据用户选择保存
 */
-(RETURN_VALUES)loginWithPasswd:(NSString *)userAccount andAppid:(uint32_t)dwAppid andPasswd:(id)userPasswd andSigBitmap:(uint32_t)dwBitmap andLoginFlag:(LOGIN_FLAG)flag;

-(RETURN_VALUES)loginWithPasswd:(NSString *)userAccount andAppid:(uint32_t)dwAppid andPasswd:(id)userPasswd andSigBitmap:(uint32_t)dwBitmap andLoginFlag:(LOGIN_FLAG)flag tag:(long*)pTag;

//appidList中的Appid，只能换取ST小票，第三方业务无此接口
-(RETURN_VALUES)loginWithPasswd:(NSString *)userAccount andAppid:(uint32_t)dwAppid andPasswd:(id)userPasswd andSigBitmap:(uint32_t)dwBitmap 
                   andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList andLoginFlag:(LOGIN_FLAG)flag;

-(RETURN_VALUES)loginWithPasswd:(NSString *)userAccount andAppid:(uint32_t)dwAppid andPasswd:(id)userPasswd andSigBitmap:(uint32_t)dwBitmap
               andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList andLoginFlag:(LOGIN_FLAG)flag tag:(long*)pTag;

/*
 刷新验证码
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 */
-(RETURN_VALUES)refreshPictureData:(NSString *)userAccount;
-(RETURN_VALUES)refreshPictureData:(NSString *)userAccount byTag:(long)tag;

/*
 验证用户输入验证码，成功返回票据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
         (NSString *)userInput         用户输入验证码
 */
-(RETURN_VALUES)checkPictureAndLogin:(NSString *)userAccount andPicInputString:(NSString *)userInput;
-(RETURN_VALUES)checkPictureAndLogin:(NSString *)userAccount andPicInputString:(NSString *)userInput byTag:(long)tag;

/*
 重新发送短信验证码
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 */
-(RETURN_VALUES)refreshSmsCode:(NSString *)userAccount andSmsAppId:(uint32_t)dwSmsAppID;
-(RETURN_VALUES)refreshSmsCode:(NSString *)userAccount andSmsAppId:(uint32_t)dwSmsAppID byTag:(long)tag;

/*
 验证用户输入短信验证码，成功返回票据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (NSString *)userInput         用户输入验证码
 */
-(RETURN_VALUES)checkSmsCodeAndLogin:(NSString *)userAccount andSmsInputString:(NSString *)userInput;
-(RETURN_VALUES)checkSmsCodeAndLogin:(NSString *)userAccount andSmsInputString:(NSString *)userInput byTag:(long)tag;

/*
 重置登录，取消登录
 */
-(BOOL)resetLoginProcess;
-(BOOL)resetLoginProcess:(long)tag;


/***********************************************************************/
// SDK数据获取接口，直接返回，不需要网络操作
//
/***********************************************************************/

/*
 清除用户登录数据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
         (uint32_t)dwAppid             登录的Appid
 返回值：  YES                           成功
         NO                            失败
 */
-(BOOL)clearUserLoginData:(NSString *)userAccount andAppid:(uint32_t)dwAppid;

-(BOOL)clearUserLoginData:(NSString *)userAccount;

/*
 登录后获取用户基本资料，仅在登录成功后有效
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 返回值：  (WloginUserInfo *)userInfo    用户基本资料
 */
-(WloginUserInfo *)getBasicUserInfo:(NSString *)userAccount;


/*
 获取票据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppid             登录的Appid，第三方业务填写第三方业务Appid
 (uint32_t)dwBitmap            拉取签名bitmap
 (int32_t)dwTime               票据过期时间，0表示使用Server返回超时时间，－1表示不进行有效期判断
 */
-(BOOL)userSigArray:(NSMutableArray *)loginSigArray forUser:(NSString *)userAccount forAppid:(uint32_t)dwAppid andSigBitmap:(uint32_t)dwBitmap 
               andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList andExpireTime:(int32_t)dwTime;


/********************************************************************************************/
//App跳转登录
/********************************************************************************************/
/*
 通过票据buff跳转登录
 输入参数：
 (NSData *)sigBuff             跳转登录的sigbuff，通过userSigBuff生成
 (NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwForAppid          跳转的目的Appid
 (uint32_t)dwBitmap            拉取签名bitmap
 */
//adwAppidList中的Appid，只能换取ST小票
-(RETURN_VALUES)loginByExchangeSig:(NSData *)sigBuff forAccount:(NSString *)userAccount andAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap
                  andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList;

-(RETURN_VALUES)loginByExchangeSig:(NSData *)sigBuff forAccount:(NSString *)userAccount andAppid:(uint32_t)dwForAppid andSigBitmap:(uint32_t)dwBitmap
                  andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList  tag:(long*)pTag;


/*
 获取票据Buff
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppid            跳转登录的Appid
 */
-(NSData *)userSigBuff:(NSString *)userAccount andAppid:(uint32_t)dwAppid;


// 取Open票据的接口
-(BOOL)userOpenSigArray:(NSMutableArray *)loginOpenSigArray forUser:(NSString *)userAccount  andAppidNum:(uint32_t)dwAppidNum andAppidList:(uint32_t *)adwAppidList;

// 取SKEY票据的接口
-(BOOL)userSKeySigArray:(NSMutableArray *)loginSKeySigArray forUser:(NSString *)userAccount andDomainList:(NSArray *)domainList;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*******************                            快速登录发起方                                          *******************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 判断能否使用快速登录的功能
 输入参数：
 (NSString *)scheme              本app的URL Scheme；因一个app可有多个URL Scheme，故需发起方在此指定。关于URL Scheme请见《iOS App Programming Guide--Implementing Custom URL Schemes》
 返回值：
 YES                             可以使用快速登录功能
 NO                              不满足快速登录的条件
 */
-(BOOL)canQuickLogin:(NSString *)scheme;

/*
 读取快速登录的用户列表
 其中每个元素都是WloginUserInfo类型，注意：只sNickName, sFaceUrl, quickLoginData字段有效.
 */
- (NSArray *)readUserListFromPasteboard;

/*
 快速登录
 输入参数：
 (uint32_t)dwAppid               业务的dwAppid
 (uint32_t)dwSubAppid            业务的dwSubAppid
 (NSString *)scheme              本app的URL Scheme；因一个app可有多个URL Scheme，故需发起方在此指定。关于URL Scheme请见《iOS App Programming Guide--Implementing Custom URL Schemes》
 返回值：
 YES                             不表示快速登录成功完成了，仅表示满足快速登录的条件，且开始了快速登录的流程
 NO                              失败（因为不满足快速登录的条件）
 */
-(BOOL)quickLogin:(uint32_t)dwAppid subAppid:(uint32_t)dwSubAppid scheme:(NSString *)scheme useApp:(WTLOGIN_QUICKLOGIN_USEAPP)useApp;

/*
 处理快速登录结果
 输入参数：
 (NSURL *)url                    快速登录处理方传给发起方的url
 (WTLOGIN_QUICKLOGIN_ACTION *)pAction 返回动作
 (uint64_t *)pddwUin             当快速登录成功(返回值==WLOGIN_V2_SECCESS)后，用于返回uin
 */
-(RETURN_VALUES)quickLoginResult:(NSURL *)url outAction:(WTLOGIN_QUICKLOGIN_ACTION *)pAction outUin:(uint64_t *)pddwUin;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*******************                            快速登录处理方                                          *******************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 处理快速登录的url
 输入参数：
 (NSURL *)url                    快速登录发起方传给处理方的url
 */
-(RETURN_VALUES)quickLoginStart:(NSURL *)url userAccount:(NSString *)userAccoun sourceApplication:(NSString *)sourceApplication andDelegate:(id)delegate tag:(long*)pTag;

-(RETURN_VALUES)quickLoginCancelled:(NSURL *)url andDelegate:(id)delegate tag:(long*)pTag;

-(RETURN_VALUES)quickLoginActiveStart:(NSString *)userAccount
                            SelfAppid:(uint32_t)dwSelfAppid
                         SelfSubAppid:(uint32_t)dwSelfSubAppid
                             DstAppid:(uint32_t)dwDstAppid
                          DstSubAppid:(uint32_t)dwDstSubAppid
                 DstSourceApplication:(NSString *)DstSourceApplication
                            DstScheme:(NSString *)DstScheme
                          andDelegate:(id)delegate
                                  tag:(long*)pTag;

-(int32_t)deleteUserFromPasteboard:(NSString *)userAccount;

/********************************************************************************************/
/********************************************************************************************/

//获取Server返回的错误码
-(uint8_t)serverReplyErrorCode;
//判断当前错误需要执行那些后续操作
-(RETURN_ACTION_TPYE)serverReplyErrorActionType;


//判断是否是name帐号
-(BOOL)isNameAccount:(NSString *)userAccount;

-(BOOL)hasRememberPwdSig:(NSString *)userAccount;
-(void)clearRememberPwdSig:(NSString *)userAccount;

-(NSMutableDictionary *)sdkNameDictionary;
-(NSMutableDictionary *)sdkSigDictionary;
-(uint32_t)serverTime;
-(uint32_t)sdkVerForApp;
-(uint32_t)sdkPubNoForApp;
-(uint32_t)sdkClientTypeForApp;
-(id)sdkServerInfo;
-(void)setDelegate:(id)delegate;
-(NSString *)sigTypeToName:(uint32_t)dwSigType;
-(uint16_t)sigTypeToTlvT:(uint32_t)dwSigType;

-(void)setWtloginTimeout:(uint16_t)wTimeout;

-(void)setSdkDispatchQueue:(dispatch_queue_t)dq;

//测试用
-(void)clearKsid;
-(NSString*)ksidString;

//log等级 0～5，默认为0，不打印任何log
-(void)setLogLevel:(int)logLever;

-(id)customDataByTag:(long)tag;

@end
