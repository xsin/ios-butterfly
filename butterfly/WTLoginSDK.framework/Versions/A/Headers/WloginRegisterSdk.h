//
//  WloginRegisterSdk.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WloginTranCallbackProtocol.h"
#import "WloginRegisterCallBackProtocol.h"

#import "WloginSdk.h"


typedef enum{
    WLOGIN_REG_NO = 0,            //QQ号码注册
    WLOGIN_REG_PHONE = 0x1,       //手机号注册
    WLOGIN_REG_ID = 0x2,          //ID注册
} REG_TYPE;

typedef enum{
    WLOGIN_REG_COUNTRY_CHINA = 86,            //中国
    WLOGIN_REG_COUNTRY_TAIWAN = 186,          //台湾
    WLOGIN_REG_COUNTRY_HONGKANG = 152,          //香港
    WLOGIN_REG_COUNTRY_USA = 174,           //美国
} REG_COUNTRY_DEFINE;


typedef enum{
    WLOGIN_REG_LANG_UNKONW = 0,            //未知语言
    WLOGIN_REG_LANG_ENGLISH = 1,          //英语
    WLOGIN_REG_LANG_SIMPLIFIED = 2,          //简体中文，目前只支持简体中文
    WLOGIN_REG_LANG_TRADITIONAL = 3,          //繁体中文
    WLOGIN_REG_LANG_JAPANESE = 4,           //日语
    WLOGIN_REG_LANG_FRANCE = 5,           //法语
} REG_LANG_DEFINE;

typedef enum{
    WLOGIN_REG_PIC_JPG = 0,            //JPG
    WLOGIN_REG_PIC_PNG = 1,          //PNG
    WLOGIN_REG_PIC_GIF = 2,          //GIF
} REG_PIC_DEFINE;


@interface WloginRegisterSdk : NSObject <WloginTranCallbackProtocol>

//初始化接口
-(id)initWithRegWtloginSdk:(id)sdk andCountry:(REG_COUNTRY_DEFINE)cCountry andLang:(REG_LANG_DEFINE)cLang andAppid:(uint32_t)dwAppid andDelegate:(id)delegate;

//国家和语言设置接口
-(void)setCountry:(REG_COUNTRY_DEFINE)cCountry andLanguage:(REG_LANG_DEFINE)cLang;
//图片验证码设置接口
-(void)setPicType:(REG_PIC_DEFINE)cPicType;


//注册流程重置接口
-(void)resetRegProcess;

//检查手机帐号或ID帐号是否可以注册
-(REG_RETURN_VALUES)registerCheckAccount:(NSString *)account andType:(REG_TYPE)type;

//提交验证手机号码
-(REG_RETURN_VALUES)registerSubmitPhoneNo:(NSString *)phoneNo andAppName:(NSString *)appName andAppVer:(NSString *)appVer;

//安全逻辑，提交图片验证码
-(REG_RETURN_VALUES)registerCheckPicCode:(NSString *)code andType:(uint8_t)cType;

//安全逻辑，检查Server是否收到上行短信
-(REG_RETURN_VALUES)registerCheckUpSmsState:(NSString *)phoneNo;

//重新发送短信验证码，下行短信
-(REG_RETURN_VALUES)registerResendSms;

//提交server下发的短信验证码
-(REG_RETURN_VALUES)registerSubmitSmsCode:(NSString *)smsCode;

//提交密码
-(REG_RETURN_VALUES)registerGetAccount:(NSString *)userPwd;



-(NSString *)phoneNoForReg;


@end
