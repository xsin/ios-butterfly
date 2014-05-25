//
//  WtloginAccountSdk.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-4-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WtloginAccountCallBackProtocol.h"
#import "MemSig.h"
#import "WloginSdk_v2.h"

@interface WtloginAccountSdk : NSObject {

    BOOL iInAccountProcess;
    WloginTranSdk *tranSdk;
#if __has_feature(objc_arc_weak)
	__weak id tranDelegate;
#else
	__unsafe_unretained id tranDelegate;
#endif
    
    WloginSdk_v2 *wloginSdk;
}

//初始化
-(id)initAccountWithWtloginSdk:(WloginSdk_v2 *)sdk;


/*
 NOTE!!! 本接口仅为手Q提供!!!
 name换uin
 输入参数：(NSArray *)accArray           name帐号的数组，每个元素为NSString*类型，可以是email或手机号;总个数最多30个
 */
-(ACCOUNT_RETURN_VALUES)name2uin_v2:(NSString *)loginAccount forAccArray:(NSArray *)accArray andDelegate:(id)delegate;

//重置流程
-(void)resetAccountProcess;



@end
