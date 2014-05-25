//
//  QRCodeInterfaceProtocol.h
//  QQPassport
//
//  Created by  on 12-8-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol QRCodeInterfaceProtocol <NSObject>

-(void)didScanQRSuccess;

-(void)didCheckQRSuccess:(NSString *)appName forUin:(NSString *)account;

-(void)qrLoginFailed:(uint8_t)cResult withMsg:(NSString *)msg;

-(void)didConfirmQRSuccess:(NSString *)appName forUin:(NSString *)account;


@end
