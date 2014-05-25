//
//  WloginTranSdk.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-3-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WloginSdk.h"
#import "WloginTranCallbackProtocol.h"

@interface WloginTranSdk : NSObject {
    id transport;
    
#if __has_feature(objc_arc_weak)
    __weak id tranDelegate;
#else
    __unsafe_unretained id tranDelegate;
#endif
    
    int iInTranProcess;
    id wloginSdkHelper;
}

-(id)initWithWtloginSdk:(id)sdk andDelegate:(id)delegate;

/*
 设置透传的回调代理
 输入参数：(id)delegate       用于透传的代理
 */
-(void)setTranDelegate:(id)delegate;

/*
 业务透传函数，使用申请相关权限
 输入参数：(NSString *)userAccount       用户帐号，可以是name帐号或者是十进制QQ号码字符串
 (uint32_t)dwAppid             已经登录的Appid
 (uint32_t)dwRole              申请权限后分配的Role
 (NSData *)data                需要透传的数据
 */
-(TRAN_RETURN_VALUES)sendToWtloginTran:(NSString *)userAccount andAppid:(uint32_t)dwAppid andRole:(uint32_t)dwRole andData:(NSData *)data;

-(TRAN_RETURN_VALUES)sendToWtloginTran:(uint32_t)dwAppid andRole:(uint32_t)dwRole andData:(NSData *)data;


-(TRAN_RETURN_VALUES)sendToWtloginTranMSF:(NSString *)userAccount andAppid:(uint32_t)dwAppid andRole:(uint32_t)dwRole andData:(NSData *)data;

-(TRAN_RETURN_VALUES)sendToWtloginTranMSF:(uint32_t)dwAppid andRole:(uint32_t)dwRole andData:(NSData *)data;

/*
 重置透传
 */
-(BOOL)resetTranProcess;


@end
