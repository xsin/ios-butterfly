//
//  WtloginAccountCallBackProtocol.h
//  WTLoginSDKForIOS
//
//  Created by  on 12-4-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum{
    WLOGIN_ACCOUNT_SECCESS = 0,              //成功
    WLOGIN_ACCOUNT_NETWORK_ERROR = 0x1,       //网络错误
    WLOGIN_ACCOUNT_STATE_ERROR = 0x6,       //状态错误： 可能是上一个调用流程没有结束，需要等待返回或调用resetTranProcess
    WLOGIN_ACCOUNT_ERROR_SERVER = 0x10,      //server错误
    WLOGIN_ACCOUNT_ERROR_LOCAL = 0x11,      //SDK错误
} ACCOUNT_RETURN_VALUES;

@class WtloginAccountSdk;

@protocol WtloginAccountCallBackProtocol <NSObject>

//NOTE!!! 本接口仅为手Q提供!!!
//name2uin的回调
//result == 0 : 正确，dict中每个元素为 {NSString *acount : NSNumber uin}
//       != 0 : 错误
-(void)onName2Uin_v2:(WtloginAccountSdk*)accountSDK withResult:(int)result dict:(NSDictionary *)dict;


@end
