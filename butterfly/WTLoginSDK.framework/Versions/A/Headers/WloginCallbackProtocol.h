//
//  WloginCallbackProtocol.h
//  WTLoginSDKForIOS
//
//  Created by jiezhao on 11-8-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WloginUserInfo.h"
#import "WloginMbPhoneInfo.h"

@class WloginErrInfo;
@class MemSig;

#ifndef __WLOGIN_RETURN_VALUE__
#define __WLOGIN_RETURN_VALUE__

typedef enum{
    NONE_FUNCTION = 0,
    LOGIN_WITH_PASSWD,
    CHECH_PIC,
    REFRESH_PIC,
    NAME_TO_UIN,
    EXCHANGE_SIG,
    EXCHANGE_SIG_A1,
    CHECK_ChALLENGE,
    CHECK_SMS,
    REFRESH_SMS,
    EXCHANGE_SIG_D2,
    QUICK_LOGIN,
} NOW_FUNCTION;


typedef enum{
    WLOGIN_SECCESS = 0,              //成功
    WLOGIN_NETWORK_ERROR = 0x1,       //网络错误
    WLOGIN_NEED_PIC = 0x2,           //需要验证码 或 验证码错误重新输入
    WLOGIN_NEED_SMS_CODE = 0xa0,           //需要短信验证码 或 短信验证码错误重新输入
    WLOGIN_SMS_CODE_ERROR = 0xa3,           //需要短信验证码 或 短信验证码错误重新输入
    WLOGIN_PWD_SIG_ERROR = 0x5,       //记住密码签名错误，需要用户输入密码登录
    WLOGIN_STATE_ERROR = 0x6,       //状态错误： 可能是上一个流程登录流程没有结束，需要等待返回或调用resetLoginProcess； 或者没有在登录流程中，却调用刷新验证码等函数
    WLOGIN_REJECTED_TIP = 0x10,      //登录错误，终断流程，展示错误提示
    WLOGIN_ERROR_LOCAL = 0x11,      //登录错误，SDK错误   ＃＃上报返回码，业务无需关心
    WLOGIN_RESET_USER = 0x12,      //前端reset登录流程    ＃＃上报返回码，业务无需关心
    WLOGIN_NETWORK_NOT_CONNETED = 0x13,       //网络没有连接
} RETURN_VALUES;

typedef enum{
    WLOGIN_ERROR_ACTION_NONE,              //建议不对用户输入做操作
    WLOGIN_ERROR_INPUT_PWD_AGAIN,   //建议清空密码框，并提示用户输入密码
} RETURN_ACTION_TPYE;

#endif

@protocol WloginCallbackProtocol <NSObject>

-(void)loginSuccessSig:(NSMutableArray *)sigArray andBaseInfo:(WloginUserInfo *)userInfo andPasswdSig:(NSMutableData *)pwdSig tag:(long)tag;

//会终断登录流程
-(void)loginFailed:(RETURN_VALUES)result withMsg:(NSString *)errorMsg __attribute__((deprecated("use 'loginFailed:andRst:withErrInfo:' instead!!!")));
-(void)loginFailed:(RETURN_VALUES)result withErrInfo:(WloginErrInfo *)errInfo tag:(long)tag;

-(void)showPicture:(NSData *)pictureData __attribute__((deprecated("use 'showPicture:wording' instead!!!")));
-(void)showPicture:(NSData *)pictureData wording:(NSDictionary *)wordingDic tag:(long)tag;

-(void)inputSmsCode:(WloginMbPhoneInfo *)sMbPhone tag:(long)tag;
-(void)inputSmsCodeError:(WloginErrInfo *)errInfo tag:(long)tag;

//快速登录成功
-(void)quickLoginSuccess:(uint64_t)ddwUin appid:(uint32_t)dwAppid data:(NSData *)data tag:(long)tag;
//快速登录失败
-(void)quickLoginFailed:(RETURN_VALUES)result withErrInfo:(WloginErrInfo *)errInfo tag:(long)tag;

@end
