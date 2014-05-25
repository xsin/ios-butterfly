//
//  WloginRegisterCallBackProtocol.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum{
    WLOGIN_REG_SECCESS = 0,              //成功
    WLOGIN_REG_NETWORK_ERROR = 0x1,       //网络错误
    WLOGIN_REG_STATE_ERROR = 0x6,       //状态错误： 可能是上一个调用流程没有结束，需要等待返回或调用resetTranProcess
    WLOGIN_REG_ERROR_SERVER = 0x10,      //server错误
    WLOGIN_REG_ERROR_LOCAL = 0x11,      //SDK错误
} REG_RETURN_VALUES;


@protocol WloginRegisterCallBackProtocol <NSObject>

//查询回调
-(void)regStep0_secc;
-(void)regStep0_accountFailed:(NSString *)msg;

//注册第一步回调接口
-(void)regStep1_secc:(NSString *)msg;
-(void)regStep1_needPic:(NSData *)picData;
-(void)regStep1_upSms:(NSString *)recvNo andSendMsg:(NSString *)msg;
-(void)regStep1_jumpUrl:(NSString *)url;
-(void)regStep1_notRecvUpSms:(uint16_t)wNextCheckTime andTimeOut:(uint16_t)wTimeOut;
-(void)regStep1_nextResentTime:(uint16_t)wNextRecentTime andTimeOut:(uint16_t)wTimeOut;

//注册第二步
-(void)regStep2_secc;
-(void)regStep2_codeFailed:(NSString *)msg;

//注册第三步
-(void)regStep3_secc:(NSString *)account andPwd:(NSString *)pwd;
-(void)regStep3_pwdFailed:(NSString *)msg;


//其他错误回调接口
-(void)regFailed:(REG_RETURN_VALUES)result withMsg:(NSString *)errorMsg;


@end
