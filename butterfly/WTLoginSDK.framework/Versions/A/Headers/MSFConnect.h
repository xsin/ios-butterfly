//
//  MSFConnect.h
//  MSFSDKTest
//
//  Created by jiezhao on 13-4-2.
//
//

#import <Foundation/Foundation.h>

#import "MSFConnectProtocol.h"

@interface MSFConnect : NSObject <NSURLConnectionDelegate, NSURLConnectionDataDelegate>


//发送数据, 异步接口，成功后通过delegate回调
-(int)sendData:(NSData *)data withTimeout:(NSTimeInterval)timeout param:(NSDictionary*)param delegate:(id<MSFConnectProtocol>)delegate;

//取消当前请求，包括清除Delegate
- (void)cancel:(long)tag;

@end
