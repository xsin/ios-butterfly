//
//  WloginRegisterCallBackProtocol.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum{
    WLOGIN_REG_SECCESS_V2 = 0,              //成功
    WLOGIN_REG_NETWORK_ERROR_V2 = 0x1,       //网络错误
    WLOGIN_REG_STATE_ERROR_V2 = 0x6,       //状态错误： 可能是上一个调用流程没有结束，需要等待返回或调用resetTranProcess
    WLOGIN_REG_ERROR_SERVER_V2 = 0x10,      //server错误
    WLOGIN_REG_ERROR_LOCAL_V2 = 0x11,      //SDK错误
    WLOGIN_REG_PARA_ERROR_V2 = 0x12,      //参数错误
} REG_RETURN_VALUES_V2;


@protocol WloginRegisterCallBackProtocol_v2 <NSObject>

//查询回调
-(void)regCheck_secc:(BOOL)isNeedSMS;
-(void)regCheck_accountFailed:(BOOL)isNeedSMS andMsg:(NSString *)msg;

//请求下行短信回调
-(void)regReqSmsCode_secc:(NSString *)msg;
-(void)regReqSmsCode_needUpSms:(NSString *)recvNo andSendMsg:(NSString *)msg;
-(void)regReqSmsCode_nextResentTime:(uint16_t)wNextRecentTime andTimeOut:(uint16_t)wTimeOut;


//提交短信code回调
-(void)regCheckSmsCode_secc;
-(void)regCheckSmsCode_codeFailed:(NSString *)msg;


//上行短信状态查询
-(void)regCheckUpSms_secc;
-(void)regCheckUpSms_notRecv:(uint16_t)wNextCheckTime andTimeOut:(uint16_t)wTimeOut;
-(void)regCheckUpSms_codeFailed:(NSString *)msg;


//提交密码获取获取号码
-(void)regGetAcctount_secc:(NSString *)account andQQAccount:(NSString *)qqAccount andPwd:(NSString *)pwd;
-(void)regEmailActivation_secc:(NSString *)url;
-(void)regGetAcctount_pwdFailed:(NSString *)msg;

// 手机号码成功后，获得一个签名
-(void)regPhoneNoActivation_secc:(NSData *)msgValidSig;


//异常跳转URL
@optional    //兼容旧版本不带msg
-(void)regReqFailed_jumpUrl:(NSString *)url;
@required    //建议新版带msg
-(void)regReqFailed_jumpUrl:(NSString *)url withMsg:(NSString *)errorMsg;


//其他错误回调接口
-(void)regFailed:(REG_RETURN_VALUES_V2)result withMsg:(NSString *)errorMsg;


@end
