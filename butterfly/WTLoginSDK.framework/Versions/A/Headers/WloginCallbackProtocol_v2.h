//
//  WloginCallbackProtocol_v2.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-5-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WloginMbPhoneInfo.h"

@class WloginSdk_v2;
@class WloginUserInfo;
@class WloginErrInfo;

#ifndef __WLOGIN_V2_RETURN_VALUE__
#define __WLOGIN_V2_RETURN_VALUE__

typedef enum{
    WLOGIN_V2_SECCESS = 0,              //成功
    WLOGIN_V2_NETWORK_ERROR = 0x1,       //网络错误
    WLOGIN_V2_NEED_PIC = 0x2,           //需要验证码 或 验证码错误重新输入
    WLOGIN_V2_NEED_SMS_CODE = 0xa0,           //需要短信验证码 或 短信验证码错误重新输入
    WLOGIN_V2_PWD_SIG_ERROR = 0x5,       //记住密码签名错误，需要用户输入密码登录
    WLOGIN_V2_STATE_ERROR = 0x6,       //状态错误： 可能是上一个流程登录流程没有结束，需要等待返回或调用resetLoginProcess； 或者没有在登录流程中，却调用刷新验证码等函数
    WLOGIN_V2_REJECTED_TIP = 0x10,      //登录错误，展示错误提示
    WLOGIN_V2_ERROR_LOCAL = 0x11,      //登录错误，SDK错误   ＃＃上报返回码，业务无需关心
    WLOGIN_V2_RESET_USER = 0x12,      //前端reset登录流程    ＃＃上报返回码，业务无需关心
    WLOGIN_V2_NETWORK_NOT_CONNETED = 0x13,       //网络没有连接
} RETURN_VALUES_V2;

#endif


@protocol WloginCallbackProtocol_v2 <NSObject>

/*******!!!重要，下面回调在2014-2月将会被废除！请修改业务代码，适配新的WTLogin回调接口********/
// 老的输入密码回调接口，兼容老业务代码
-(void)showPicture_v2:(WloginSdk_v2 *)sdk andPicData:(NSData *)pictureData __attribute__((deprecated("use 'showPicture_v2:andPicData:andWording:tag' instead!!!")));
-(void)showPicture_v2:(WloginSdk_v2 *)sdk andPicData:(NSData *)pictureData andWording:(NSDictionary *)wordingDic __attribute__((deprecated("use 'showPicture_v2:andPicData:andWording:tag' instead!!!")));
// 老的登录成功回调
-(void)loginSuccessSig_v2:(WloginSdk_v2 *)sdk andSig:(NSMutableArray *)sigArray andBaseInfo:(WloginUserInfo *)userInfo __attribute__((deprecated("use 'loginSuccessSig_v2:andSig:andBaseInfo:tag' instead!!!")));;
-(void)loginFailed_v2:(WloginSdk_v2 *)sdk andRst:(RETURN_VALUES_V2)result withErrInfo:(WloginErrInfo *)errInfo __attribute__((deprecated("use 'loginFailed_v2:andRst:withErrInfo:tag' instead!!!")));
/*******!!!重要，上面回调在2014-2月将会被废除！请修改业务代码，适配新的WTLogin回调接口********/


/*********下面是新的WTLogin回调接口********/
-(void)showPicture_v2:(WloginSdk_v2 *)sdk andPicData:(NSData *)pictureData andWording:(NSDictionary *)wordingDic tag:(long)tag;

-(void)inputSmsCode_v2:(WloginSdk_v2 *)sdk andMbPhoneInfo:(WloginMbPhoneInfo *)sMbPhone tag:(long)tag;
-(void)inputSmsCodeError_v2:(WloginSdk_v2 *)sdk andErrInfo:(WloginErrInfo *)errorMsg tag:(long)tag;

-(void)loginSuccessSig_v2:(WloginSdk_v2 *)sdk andSig:(NSMutableArray *)sigArray andBaseInfo:(WloginUserInfo *)userInfo tag:(long)tag;
//该会调会终断流程
-(void)loginFailed_v2:(WloginSdk_v2 *)sdk andRst:(RETURN_VALUES_V2)result withErrInfo:(WloginErrInfo *)errInfo tag:(long)tag;

//快速登录完成，需由快速登录处理方实现
-(void)quickLoginEnd_v2:(WloginSdk_v2 *)sdk andUrl:(NSURL *)url tag:(long)tag;

@end
