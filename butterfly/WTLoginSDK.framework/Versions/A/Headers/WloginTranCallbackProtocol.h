//
//  WloginTranCallbackProtocol.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-1-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef __WLOGIN_TRAN_RETURN_VALUE__
#define __WLOGIN_TRAN_RETURN_VALUE__

typedef enum{
    WLOGIN_TRAN_SECCESS = 0,              //成功
    WLOGIN_TRAN_NETWORK_ERROR = 0x1,       //网络错误
    WLOGIN_TRAN_SIG_ERROR = 0x2,       //找不到票据
    WLOGIN_TRAN_STATE_ERROR = 0x6,       //状态错误： 可能是上一个调用流程没有结束，需要等待返回或调用resetTranProcess
    WLOGIN_TRAN_ERROR_SERVER = 0x10,      //server错误
    WLOGIN_TRAN_ERROR_LOCAL = 0x11,      //SDK错误
    WLOGIN_TRAN_NETWORK_NOT_CONNETED = 0x12,       //网络没有连接
} TRAN_RETURN_VALUES;

#endif

@class WloginTranSdk;

//旧版本回调函数，不建议使用
@protocol WloginTranCallbackProtocol <NSObject>

-(void)tranSuccessWithData:(NSData *)data;

-(void)tranFailed:(TRAN_RETURN_VALUES)result withMsg:(NSString *)errorMsg;

@end



//新版本回调函数
@protocol WloginTranCallbackProtocol_v2 <NSObject>

-(void)tranSuccess_v2:(WloginTranSdk *)tranSdk withData:(NSData *)data;

-(void)tranFailed_v2:(WloginTranSdk *)tranSdk result:(TRAN_RETURN_VALUES)result withMsg:(NSString *)errorMsg;

@end

