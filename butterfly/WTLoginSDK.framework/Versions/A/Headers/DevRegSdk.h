//
//  DevRegSdk.h
//  QQPassport
//
//  Created by 然 刘 on 12-8-6.
//  Copyright (c) 2012年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WTLoginSDK/WloginSdk.h"
#import "WTLoginSDK/WloginTranSdk.h"
#import "WTLoginSDK/WtloginPlatformInfo.h"
#import "WTLoginSDK/WloginTranCallbackProtocol.h"

#import "DevRegCallBackProtocol.h"

@class DevRegCmd;

@interface DevRegSdk : NSObject <WloginTranCallbackProtocol> {
    id devRegDelegate;
    uint32_t dwPushAppid;
    uint32_t dwPushSubAppid;
    uint64_t ddwAccountUin;
    
    WloginTranSdk *devRegTransportSdk;
    
    int iDevRegState;
    DevRegCmd *devRegCmd;
}


typedef enum{
    DEVREG_CLEAR_NO = 0,            //不清空未读消息数量 
    DEVREG_CLEAR_YES = 1,            //清空未读消息数量 
} WTLOGIN_SEVREG_CLEAR_FLAG;

typedef enum{
    DEVREG_OVER_USER = 0,            //未读消息个数由用户指定
    DEVREG_OVER_ZERO = 1,            //全部读完
} WTLOGIN_DEVREG_OVER_FLAG;

typedef enum{
    DEVREG_OffLINE_LOGOUT = 1,            //用户主动下线
    DEVREG_OffLINE_OFF = 2,            //用户关闭push
} WTLOGIN_DEVREG_OffLINE_FLAG;


// 初始化接口
-(id)initWithDevRegSdk:(WloginSdk *)sdk andAppid:(uint32_t)dwAppid andUin:(uint64_t)ddwUin andDelegate:(id)delegate;

//平台类型业务，需要传入subappid
-(id)initWithDevRegSdk:(WloginSdk *)sdk andAppid:(uint32_t)dwAppid andSubAppid:(uint32_t)dwSubAppid andUin:(uint64_t)ddwUin andDelegate:(id)delegate;

// ios设备注册
-(DEVREG_RETURN_VALUES)iosDevReg:(NSData *)token withClearFlag:(WTLOGIN_SEVREG_CLEAR_FLAG)cClearFlag;
// app注销(ios设备下线)
-(DEVREG_RETURN_VALUES)iosDevOffLine:(WTLOGIN_DEVREG_OffLINE_FLAG)wOffLineType;
// app上报已读消息数量
-(DEVREG_RETURN_VALUES)iosDevReport:(WTLOGIN_DEVREG_OVER_FLAG)cOverFlag withMsgCount:(uint16_t)wMsgCount;

@end
