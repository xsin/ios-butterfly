//
//  DevRegCallBackProtocol.h
//  QQPassport
//
//  Created by 然 刘 on 12-8-6.
//  Copyright (c) 2012年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum{
    DEVREG_SUCCESS = 0,            //成功
    DEVREG_NETWORK_ERROR = 0x1,    //网络错误
    DEVREG_STATE_ERROR = 0x6,      //状态错误： 可能是上一个调用流程没有结束，需要等待返回
    DEVREG_ERROR_SERVER = 0x10,    //server错误
    DEVREG_ERROR_LOCAL = 0x11,     //SDK错误
} DEVREG_RETURN_VALUES;


typedef enum{
    DEVREG_TYPE_REG = 1,            //对应iosDevReg的返回
    DEVREG_TYPE_OFFLINE = 2,    //对应iosDevOffLine的返回
    DEVREG_TYPE_REPORT = 3,      //对应iosDevReport的返回
} DEVREG_RETURN_TYPE;


@protocol DevRegCallBackProtocol <NSObject>

// ios设备注册回调
- (void)iosDevReg_succ:(DEVREG_RETURN_TYPE)type;
- (void)iosDevReg_failed:(DEVREG_RETURN_TYPE)type withResult:(DEVREG_RETURN_VALUES)result withMsg:(NSString *)errorMsg;

@end
