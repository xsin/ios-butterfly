//
//  WloginSdk_v2.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-5-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WloginCallbackProtocol_v2.h"
#import "WloginLogProtocol_v2.h"
#import "WloginSdk.h"
#import "WloginTranSdk.h"
#import "WloginEnum.h"


@class MSFConnect;


//登录方式
typedef enum{
    LOGIN_V2_GEN_PASSWD_SIG = LOGIN_GEN_PASSWD_SIG,       //使用密码登录，记住密码
    LOGIN_V2_MD5_GEN_PASSWD_SIG = LOGIN_MD5_GEN_PASSWD_SIG,   //使用密码MD5登录，记住密码
    LOGIN_V2_WITH_PASSWD_SIG_GEN = 0x7,             //使用密码签名登录，记住密码
} LOGIN_FLAG_V2;

//最低允许的票据获取方式
typedef enum{
    LOGIN_V2_ALLOW_PWD_INPUT=0x10,               //必须让用户输入密码
    LOGIN_V2_ALLOW_PWD_SIG=0x20,                //最低允许使用记住密码票据登录
    LOGIN_V2_ALLOW_EXCHAGE=0x30,                 //最低允许使用换票的方式
    LOGIN_V2_ALLOW_MEM_SIG=0x40,                 //最低允许使用内存中的票据
} LOGIN_ALLOW_FLAG_V2;


@interface WloginSdk_v2 : NSObject <WloginCallbackProtocol>
{
#if __has_feature(objc_arc_weak)
	id __weak               defaultDeleaget;
#elif __has_feature(objc_arc)
	id __unsafe_unretained  defaultDeleaget;
#else
	id                      defaultDeleaget;
#endif
    
    uint32_t dwFailedCount;
}

@property (readonly) uint32_t dwFailedCount;

//
-(WloginSdk *)globalWtloginSdk;

@property (readonly) NSData* guid;

@property (readonly) NSString* guidString;


/***********************************************************************/
// 初始化接口，用来初始化SDK基本信息
//
/***********************************************************************/
/*
 初始化客户端基本信息
 (NSString *)strVer             客户端版本号，格式为 x.x.x.x， 例如，客户端版本为1.1，传入参数为 @"1.1.0.0" 
 */
-(id)initWithBasicInfo_v2:(NSString *)strVer;

//初始化并设置log回调delegate
-(id)initWithBasicInfo_v2:(NSString *)strVer withLogDelegaet:(id<WloginLogProtocol_v2>)delegate;

/*
 获取记住密码接口, 上次登录用户
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 */
-(NSString *)lastLoginUser;

/*
 能否找到记住密码票据
 */
-(BOOL)hasPasswordSig_v2:(NSString *)userAccount;
//清除记住密码票据
-(void)clearPasswordSig_v2:(NSString *)userAccount;



/*
 ******************************************************************************************************
 －－－－－－－－－－－－－－－－－－－－－－－已废除的登录入口函数－－－－－－－－－－－－－－－－－－－－－－－－
 －－－－－－－－－－－－－－－－－－－－请切换到getUserSigAndBasicInfoByLogin_v2／getUserSigAndBasicInfoByExchage_v2－－－－

-(RETURN_VALUES_V2)getUserSigAndBasicInfo_v2:(NSString *)userAccount andAppid:(uint32_t)dwAppid andSigBitmap:(uint32_t)dwBitmap 
                            andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList 
                               andExpireTime:(uint32_t)dwTime andAllow:(LOGIN_ALLOW_FLAG_V2)allowFlag andDelegate:(id)delegate;

-(RETURN_VALUES_V2)getUserSigAndBasicInfo_v2:(NSString *)userAccount andAppid:(uint32_t)dwAppid andSigBitmap:(uint32_t)dwBitmap 
                               andExpireTime:(uint32_t)dwTime andAllow:(LOGIN_ALLOW_FLAG_V2)allowFlag andDelegate:(id)delegate;

 */



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*******************                                                                                  *******************///
///*******************                            WTLogin 调用方式（2）                                    *******************///
///*******************                                                                                  *******************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  1、isNeedLoginWithPasswd_v2 判断是否需要密码登录
//     (1) 如果需要，调用 getUserSigAndBasicInfoByLogin_v2，该函数支持使用密码和记住密码票据登录，详见LOGIN_FLAG_V2
//     (2) 如果不需要，进入步骤2
//  2、调用 checkLocalSigValid_v2 判断所需票据是否有效
//     (1) 如果有效，直接调用 getMemUserSig_v2 获取本地票据
//     (2) 如果无效，则调用 getUserSigAndBasicInfoByExchage_v2 更新本地票据
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
 判断是否需要用密码登录
 */
-(BOOL)isNeedLoginWithPasswd_v2:(NSString *)userAccount andAppid:(uint32_t)dwAppid;


/*
 判断本地票据是否有效
 */
-(BOOL)checkLocalSigValid_v2:(NSString *)userAccount andAppid:(uint32_t)dwAppid andSigType:(uint32_t)dwSigType;



/*
 ******************************************************************************************************
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－登录入口函数－－－－－－－－－－－－－－－－－－－－－－－－－－－－
 1、由直接通过输入密码，或者使用密码签名登录
 2、该函数确定会产生网络操作
 
 ******************************************************************************************************
输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
(uint32_t)dwAppid                  登录的Appid
(uint32_t)dwBitmap                 拉取签名bitmap
(id)delegate                       回调函数

多业务登录时，需要设置
(uint32_t)dwAppidListNum           同时登录的appid个数，最大10个
(uint32_t *)adwAppidList           同时登录的appid list
(NSString *)userPasswd           用户密码 / 密码一次MD5
(LOGIN_FLAG_V2)flag              登录方式，具体见LOGIN_FLAG_V2定义

*/
-(RETURN_VALUES_V2)getUserSigAndBasicInfoByLogin_v2:(NSString *)userAccount
                                           andAppid:(uint32_t)dwAppid
                                       andSigBitmap:(uint32_t)dwBitmap
                                   andOtherAppidNum:(uint32_t)dwAppidListNum
                                  andOtherAppidList:(uint32_t *)adwAppidList
                                             andPwd:(id)userPasswd
                                       andLoginFlag:(LOGIN_FLAG_V2)flag
                                        andDelegate:(id)delegate;

-(RETURN_VALUES_V2)getUserSigAndBasicInfoByLogin_v2:(NSString *)userAccount
                                           andAppid:(uint32_t)dwAppid
                                       andSigBitmap:(uint32_t)dwBitmap
                                             andPwd:(id)userPasswd
                                       andLoginFlag:(LOGIN_FLAG_V2)flag
                                        andDelegate:(id)delegate;



///并发调用
-(RETURN_VALUES_V2)getUserSigAndBasicInfoByLogin_v2:(NSString *)userAccount
                                           andAppid:(uint32_t)dwAppid
                                       andSigBitmap:(uint32_t)dwBitmap
                                   andOtherAppidNum:(uint32_t)dwAppidListNum
                                  andOtherAppidList:(uint32_t *)adwAppidList
                                             andPwd:(id)userPasswd
                                       andLoginFlag:(LOGIN_FLAG_V2)flag
                                        andDelegate:(id)delegate
                                                tag:(long*)pTag;

-(RETURN_VALUES_V2)getUserSigAndBasicInfoByLogin_v2:(NSString *)userAccount
                                           andAppid:(uint32_t)dwAppid
                                       andSigBitmap:(uint32_t)dwBitmap
                                             andPwd:(id)userPasswd
                                       andLoginFlag:(LOGIN_FLAG_V2)flag
                                        andDelegate:(id)delegate
                                                tag:(long*)pTag;





/*
 ******************************************************************************************************
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－换票入口函数－－－－－－－－－－－－－－－－－－－－－－－－－
 1、通过本地有效的A2换取票据
 2、该函数确定会产生网络操作
 
 ******************************************************************************************************
 输入参数：
 (NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppid                  登录的Appid
 (uint32_t)dwBitmap                 拉取签名bitmap
 (id)delegate                       回调函数
 
 多业务登录时，需要设置
 (uint32_t)dwAppidListNum           同时登录的appid个数，最大10个
 (uint32_t *)adwAppidList           同时登录的appid list
 
 
 */
-(RETURN_VALUES_V2)getUserSigAndBasicInfoByExchage_v2:(NSString *)userAccount
                                             andAppid:(uint32_t)dwAppid
                                         andSigBitmap:(uint32_t)dwBitmap
                                     andOtherAppidNum:(uint32_t)dwAppidListNum
                                    andOtherAppidList:(uint32_t *)adwAppidList
                                          andDelegate:(id)delegate;

-(RETURN_VALUES_V2)getUserSigAndBasicInfoByExchage_v2:(NSString *)userAccount
                                             andAppid:(uint32_t)dwAppid
                                         andSigBitmap:(uint32_t)dwBitmap
                                          andDelegate:(id)delegate;


//并发调用
-(RETURN_VALUES_V2)getUserSigAndBasicInfoByExchage_v2:(NSString *)userAccount
                                             andAppid:(uint32_t)dwAppid
                                         andSigBitmap:(uint32_t)dwBitmap
                                     andOtherAppidNum:(uint32_t)dwAppidListNum
                                    andOtherAppidList:(uint32_t *)adwAppidList
                                          andDelegate:(id)delegate
                                                  tag:(long*)pTag;

-(RETURN_VALUES_V2)getUserSigAndBasicInfoByExchage_v2:(NSString *)userAccount
                                             andAppid:(uint32_t)dwAppid
                                         andSigBitmap:(uint32_t)dwBitmap
                                          andDelegate:(id)delegate
                                                  tag:(long*)pTag;


/*
 ******************************************************************************************************
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－换票入口函数－－－－－－－－－－－－－－－－－－－－－－－－－－－－
 1、MSF跳转，通过A2和D2获取票据
 2、该函数确定会产生网络操作
 
 ******************************************************************************************************
 输入参数：
 (MemSig *)sigTGT              MSF跳转传入的A2
 (MemSig *)sigD2               MSF跳转传入的D2
 (NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppid                  登录的Appid
 (uint32_t)dwBitmap                 拉取签名bitmap
 (id)delegate                       回调函数
 
 多业务登录时，需要设置
 (uint32_t)dwAppidListNum           同时登录的appid个数，最大10个
 (uint32_t *)adwAppidList           同时登录的appid list
 
 登录控制参数
 (uint32_t)dwTime                   指定票据有效期，添0表示使用默认值，由于小票（ST）是由业务验证的，因此需要业务传入票据有效期
 (LOGIN_ALLOW_FLAG_V2)allowFlag     最低允许的获取登录票据的方式
 
 */
-(RETURN_VALUES_V2)getUserSigAndBasicInfoByMSF_v2:(MemSig *)sigTgt
                                            andD2:(MemSig *)sigD2
                                       forAccount:(NSString *)userAccount
                                         andAppid:(uint32_t)dwAppid
                                     andSigBitmap:(uint32_t)dwBitmap
                                 andOtherAppidNum:(uint32_t)dwAppidListNum
                                andOtherAppidList:(uint32_t *)adwAppidList
                                      andDelegate:(id)delegate;

-(RETURN_VALUES_V2)getUserSigAndBasicInfoByMSF_v2:(MemSig *)sigTgt
                                            andD2:(MemSig *)sigD2
                                       forAccount:(NSString *)userAccount
                                         andAppid:(uint32_t)dwAppid
                                     andSigBitmap:(uint32_t)dwBitmap
                                 andOtherAppidNum:(uint32_t)dwAppidListNum
                                andOtherAppidList:(uint32_t *)adwAppidList
                                      andDelegate:(id)delegate
                                              tag:(long*)pTag;


/*
 ******************************************************************************************************
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－跳转登录入口函数－－－－－－－－－－－－－－－－－－－－－－－－－－－－
 1、已登陆App1通过getJumpLoginBuff_v2生成跳转登录buff，通过自定义URL传给App2
 2、App2通过调用getUserSigAndBasicInfoByJump_v2，完成登录
 3、该函数确定会产生网络操作
 
 ******************************************************************************************************
 通过票据buff跳转登录
 输入参数：
 (NSData *)sigBuff             tiao
 (MemSig *)sigD2               MSF跳转传入的D2
 (NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwForAppid          跳转的目的Appid
 (uint32_t)dwBitmap            拉取签名bitmap
 */
//adwAppidList中的Appid，只能换取ST小票
-(RETURN_VALUES_V2)getUserSigAndBasicInfoByJump_v2:(NSData *)sigBuff
                                       forAccount:(NSString *)userAccount
                                         andAppid:(uint32_t)dwAppid
                                     andSigBitmap:(uint32_t)dwBitmap
                                 andOtherAppidNum:(uint32_t)dwAppidListNum
                                andOtherAppidList:(uint32_t *)adwAppidList
                                      andDelegate:(id)delegate;

/*
 获取票据Buff
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppid            跳转登录的Appid
 */
-(NSData *)getJumpLoginBuff_v2:(NSString *)userAccount andAppid:(uint32_t)dwAppid;



/*
 ******************************************************************************************************
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－获取OPENKEY或ACCESSTOKEN入口函数－－－－－－－－－－－－－－－－－－－－－－－－－－－－
 1、通过本地有效的A2换取OPENKEY或ACCESSTOKEN
 2、该函数确定会产生网络操作
 
 ******************************************************************************************************
 输入参数：
 (NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwByAppid           业务所申请的WTLogin系统的Appid
 (uint32_t)dwForOpenid         业务所申请的OPEN系统的Appid
 (uint32_t)dwBitmap            WLOGIN_GET_OPENKEY或WLOGIN_GET_TOKEN，二者不可同时请求
 */
-(RETURN_VALUES_V2)getOpenSig_v2:(NSString *)userAccount
                      andByAppid:(uint32_t)dwByAppid
                    andForOpenid:(uint32_t)dwForOpenid
                    andSigBitmap:(uint32_t)dwBitmap
                     andDelegate:(id)delegate;

-(RETURN_VALUES_V2)getOpenSig_v2:(NSString *)userAccount
                      andByAppid:(uint32_t)dwByAppid
                    andForOpenid:(uint32_t)dwForOpenid
                    andSigBitmap:(uint32_t)dwBitmap
                     andDelegate:(id)delegate
                             tag:(long*)pTag;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*******************                            后续为回调处理函数                                        *******************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 用户输入密码登录,获取票据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (NSString *)userPasswd        用户密码 / 密码一次MD5
 (uint32_t)dwBitmap            拉取签名bitmap
 (LOGIN_FLAG_V2)flag              登录方式，具体见LOGIN_FLAG_V2定义
 
 */
-(RETURN_VALUES_V2)loginWithPasswd_v2:(NSString *)userAccount andPwd:(id)userPasswd andLoginFlag:(LOGIN_FLAG_V2)flag  andDelegate:(id)delegate;

/*
 刷新验证码
 */
-(RETURN_VALUES_V2)refreshPictureData_v2:(id)delegate;
-(RETURN_VALUES_V2)refreshPictureData_v2:(id)delegate tag:(long)tag;

/*
 验证用户输入验证码，成功返回票据
 输入参数：(NSString *)userInput         用户输入验证码
 */
-(RETURN_VALUES_V2)checkPictureAndLogin_v2:(NSString *)userInput andDelegate:(id)delegate;
-(RETURN_VALUES_V2)checkPictureAndLogin_v2:(NSString *)userInput andDelegate:(id)delegate tag:(long)tag;

/*
  发送短信验证码
 */
-(RETURN_VALUES_V2)refreshSmsCode_v2:(uint32_t)smsAppId andDelegate:(id)delegate;
-(RETURN_VALUES_V2)refreshSmsCode_v2:(uint32_t)smsAppId andDelegate:(id)delegate tag:(long)tag;

/*
 验证用户输入短信验证码，成功返回票据
 输入参数：(NSString *)userInput         用户输入验证码
 */
-(RETURN_VALUES_V2)checkSmsCodeAndLogin_v2:(NSString *)userInput andDelegate:(id)delegate;
-(RETURN_VALUES_V2)checkSmsCodeAndLogin_v2:(NSString *)userInput andDelegate:(id)delegate tag:(long)tag;


#ifdef MOBILEQQ

/***********************************************************************/
-(void)setMSFConnect:(MSFConnect*)conn;

#endif

/*
 重置登录，取消登录
 */
-(BOOL)resetLoginProcess_v2;
-(BOOL)resetLoginProcess_v2:(long)tag;


//设置代理
-(void)setLoginDelegate:(id)delegate;
-(void)setLoginDelegate:(id)delegate tag:(long)tag;




/***********************************************************************/
// SDK数据获取接口，直接返回，不需要网络操作
//
/***********************************************************************/

/*
 获取本地票据，不判断超时，同步返回
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppid                  登录的Appid
 (uint32_t)dwBitmap                 拉取签名bitmap
 (id)delegate                       回调函数
 
 多业务登录时，需要设置
 (uint32_t)dwAppidListNum           同时登录的appid个数，最大10个
 (uint32_t *)adwAppidList           同时登录的appid list
 
 */
-(NSMutableArray *)getMemUserSig_v2:(NSString *)userAccount andAppid:(uint32_t)dwAppid andSigBitmap:(uint32_t)dwBitmap
                   andOtherAppidNum:(uint32_t)dwAppidListNum andOtherAppidList:(uint32_t *)adwAppidList;

-(NSMutableArray *)getMemUserSig_v2:(NSString *)userAccount andAppid:(uint32_t)dwAppid andSigBitmap:(uint32_t)dwBitmap;


/*
 获取本地OPEN票据，不判断超时，同步返回
 输入参数：(NSString *)userAccount    用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppidNum               open appid个数，最大10个
 (uint32_t *)adwAppidList           open appid list
 */
-(NSMutableArray*)getMemOpenSig_v2:(NSString *)userAccount  andAppidNum:(uint32_t)dwAppidNum andAppidList:(uint32_t *)adwAppidList;

/*
 获取本地SKEY票据，不判断超时，同步返回
 输入参数：(NSString *)userAccount    用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (NSArray*)domainList               取PSKEY的domain list
 */
-(NSMutableArray*)getMemSKeySig_v2:(NSString *)userAccount andDomainList:(NSArray *)domainList;

/*
 登录后获取用户基本资料，仅在登录成功后有效
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 返回值：  (WloginUserInfo *)userInfo    用户基本资料
 */
-(WloginUserInfo *)getBasicUserInfo_v2:(NSString *)userAccount;


/*
 清除用户登录数据
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 返回值：  YES                           成功
 NO                            失败
 */
-(BOOL)clearUserLoginData_v2:(NSString *)userAccount;

/*
 切换用户
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 返回值：  YES                           成功
 NO                            失败
 */
-(BOOL)switchUser_v2:(NSString *)userAccount;


//////////////////////////////////
//////////////////////////////////
//

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


//获取Server返回的错误码
-(uint8_t)serverReplyErrorCode;
//判断当前错误需要执行那些后续操作
-(RETURN_ACTION_TPYE)serverReplyErrorActionType;

//判断是否是name帐号
-(BOOL)isNameAccount:(NSString *)userAccount;

-(uint32_t)serverTime;

-(void)setWtloginTimeout:(uint16_t)wTimeout;

//log等级 0～5，默认为0，不打印任何log
-(void)setLogLevel:(int)logLever;

/*
 指定服务器登录
 */
-(void)setRemortServer:(NSString *)sIp andPort:(uint16_t)wPort;

//设置提示语的语言类型
-(void)setLanguage:(WTLOGIN_LANGUAGE)lang;

/* 添加SKEY的domain，不能超过5个
 * True  添加成功
 * False 添加失败
 **/
-(BOOL)addSKeyDomain:(NSString*)domain;

/* 清空SKEY的域名列表 */
-(void)clearSKeyDomainList;

//历史登录列表
-(NSArray *)loginUserHistory;

//ksid
-(NSData *)ksid;

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
-(BOOL)canQuickLogin_v2:(NSString *)scheme;

/*
 读取快速登录的用户列表
 其中每个元素都是WloginUserInfo类型，注意：只sNickName, sFaceUrl, quickLoginData字段有效.
 */
- (NSArray *)readUserListFromPasteboard_v2;

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
-(BOOL)quickLogin_v2:(uint32_t)dwAppid subAppid:(uint32_t)dwSubAppid scheme:(NSString *)scheme useApp:(WTLOGIN_QUICKLOGIN_USEAPP)useApp;

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
-(BOOL)quickLogin_v2:(uint32_t)dwAppid subAppid:(uint32_t)dwSubAppid scheme:(NSString *)scheme;

/*
 处理快速登录结果
 输入参数：
 (NSURL *)url                    快速登录处理方传给发起方的url
 (uint64_t *)pddwUin             当快速登录成功(返回值==WLOGIN_V2_SECCESS)后，用于返回uin
 */
-(RETURN_VALUES_V2)quickLoginResult_v2:(NSURL *)url outAction:(WTLOGIN_QUICKLOGIN_ACTION *)pAction outUin:(uint64_t *)pddwUin;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*******************                            快速登录处理方                                          *******************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 处理快速登录的url
 输入参数：
 (NSURL *)url                    快速登录发起方传给处理方的url
 (NSString *)sourceApplication   要快速登录的app的bundleID，本参数从- (BOOL)application:openURL:sourceApplication:annotation中的sourceApplication获得
 (NSString *)userAccount         要快速登录的帐号
 */
-(RETURN_VALUES_V2)quickLoginStart_v2:(NSURL *)url userAccount:(NSString *)userAccount sourceApplication:(NSString *)sourceApplication andDelegate:(id)delegate tag:(long *)pTag;

/*
 取消快速登录
 输入参数：
 (NSURL *)url                    快速登录发起方传给处理方的url
 */
-(RETURN_VALUES_V2)quickLoginCancelled_v2:(NSURL *)url andDelegate:(id)delegate tag:(long *)pTag;

//主动快速登录
/*
输入参数：
    (NSString *)userAccount         要快速登录的帐号
    (uint32_t)dwSelfAppid           自己的Appid
    (uint32_t)dwSelfSubAppid        自己的SubAppid
    (uint32_t)dwDstAppid            对方的Appid
    (uint32_t)dwDstSubAppid         对方的SubAppid
    (NSString *)DstSourceApplication   对方的bundleID，形如"com.tencent.mobileqq"的字符串
    (NSString *)DstScheme           能拉起对方App的Url Scheme
*/
-(RETURN_VALUES_V2)quickLoginActiveStart_v2:(NSString *)userAccount
                                  SelfAppid:(uint32_t)dwSelfAppid
                               SelfSubAppid:(uint32_t)dwSelfSubAppid
                                   DstAppid:(uint32_t)dwDstAppid
                                DstSubAppid:(uint32_t)dwDstSubAppid
                       DstSourceApplication:(NSString *)DstSourceApplication
                                  DstScheme:(NSString *)DstScheme
                                andDelegate:(id)delegate
                                        tag:(long*)pTag;

/*
 从剪贴板上删除帐号
 输入参数：
    (NSString *)userAccount         要删除的帐号
 返回值：
    0   :   成功
    <0  :   失败
 */
-(int32_t)deleteUserFromPasteboard_v2:(NSString *)userAccount;

@end
