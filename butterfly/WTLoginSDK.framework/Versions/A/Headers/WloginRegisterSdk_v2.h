//
//  WloginRegisterSdk.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WloginTranCallbackProtocol.h"
#import "WloginRegisterCallBackProtocol_v2.h"

#import "WloginSdk.h"


typedef enum{
    WLOGIN_REG_NO_V2 = 0x0,            //QQ号码注册
    WLOGIN_REG_PHONE_V2 = 0x1,       //手机号注册
    WLOGIN_REG_ID_V2 = 0x2,          //ID注册
    WLOGIN_REG_EMAIL_V2 = 0x3,          //email注册
} REG_TYPE_V2;

typedef enum{
    WLOGIN_REG_COUNTRY_CHINA_V2 = 86,            //中国
    WLOGIN_REG_COUNTRY_TAIWAN_V2 = 186,          //台湾
    WLOGIN_REG_COUNTRY_HONGKANG_V2 = 152,          //香港
    WLOGIN_REG_COUNTRY_USA_V2 = 174,           //美国
} REG_COUNTRY_DEFINE_V2;


typedef enum{
    WLOGIN_REG_LANG_UNKONW_V2 = 0,            //未知语言
    WLOGIN_REG_LANG_ENGLISH_V2 = 1,          //英语
    WLOGIN_REG_LANG_SIMPLIFIED_V2 = 2,          //简体中文，目前只支持简体中文
    WLOGIN_REG_LANG_TRADITIONAL_V2 = 3,          //繁体中文
    WLOGIN_REG_LANG_JAPANESE_V2 = 4,           //日语
    WLOGIN_REG_LANG_FRANCE_V2 = 5,           //法语
} REG_LANG_DEFINE_V2;

typedef enum{
    WLOGIN_REG_PIC_JPG_V2 = 0,            //JPG
    WLOGIN_REG_PIC_PNG_V2 = 1,          //PNG
    WLOGIN_REG_PIC_GIF_V2 = 2,          //GIF
} REG_PIC_DEFINE_V2;


@interface WloginRegisterSdk_v2 : NSObject <WloginTranCallbackProtocol>

//初始化接口
-(id)initWithRegWtloginSdk:(id)sdk andCountry:(REG_COUNTRY_DEFINE_V2)cCountry andLang:(REG_LANG_DEFINE_V2)cLang andAppid:(uint32_t)dwAppid andDelegate:(id)delegate;
-(void)setAppUrl:(NSString *)appUrl;

//国家和语言设置接口
-(void)setCountry:(REG_COUNTRY_DEFINE_V2)cCountry andLanguage:(REG_LANG_DEFINE_V2)cLang;
//图片验证码设置接口
-(void)setPicType:(REG_PIC_DEFINE_V2)cPicType;
// 设置用户昵称
-(void)setUserNick:(NSString *)nick;


//注册流程重置接口
-(void)resetRegProcess;
    
//检查手机帐号或ID帐号是否可以注册
-(REG_RETURN_VALUES_V2)registerCheckAccount:(NSString *)account andType:(REG_TYPE_V2)type;

//提交验证手机号码
-(REG_RETURN_VALUES_V2)registerSubmitPhoneNo:(NSString *)phoneNo andAppName:(NSString *)appName andAppVer:(NSString *)appVer;

//检查Server是否收到上行短信
-(REG_RETURN_VALUES_V2)registerCheckUpSmsState:(NSString *)phoneNo;

//重新发送短信验证码，下行短信
-(REG_RETURN_VALUES_V2)registerResendSms;

//提交server下发的短信验证码
-(REG_RETURN_VALUES_V2)registerSubmitSmsCode:(NSString *)smsCode;

//提交密码
-(REG_RETURN_VALUES_V2)registerGetAccount:(NSString *)userPwd;

//email注册自定义URL拉起处理函数
-(BOOL)registerEmailHandleOpenURL:(NSURL *)url;


-(NSString *)phoneNoForReg;


@end
