//
//  MSFConnectProtocol.h
//  MSFSDKTest
//
//  Created by jiezhao on 13-4-2.
//
//

#import <Foundation/Foundation.h>

@class MSFConnect;

@protocol MSFConnectProtocol <NSObject>

//与svr建连接立
- (void)msfconnection:(MSFConnect *)connection didConnectToHost:(NSString *)host port:(uint16_t)port param:(NSDictionary*)param;

//收到数据（一个完整的包）
- (void)msfconnection:(MSFConnect *)connection didReceiveData:(NSData *)data param:(NSDictionary*)param;

//出错
- (void)msfconnection:(MSFConnect *)connection didFailWithError:(NSError *)error param:(NSDictionary*)param;

@end
