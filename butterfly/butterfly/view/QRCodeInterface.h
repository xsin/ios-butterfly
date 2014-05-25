//
//  QRCodeInterface.h
//  wtlogin_demo
//
//  Created by 然 刘 on 12-7-2.
//  Copyright (c) 2012年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WTLoginSDK/WloginSdk_v2.h"

#import "WTLoginSDK/QRCodeSdk.h"
#import "WTLoginSDK/QRCodeCallBackProtocol.h"
#import "QRCodeReader.h"
#import "ZXingWidgetController.h"

@interface QRCodeInterface : NSObject <ZXingDelegate> {
    NSString * qrAccount;
    uint32_t dwQrAppid;
    QRCodeSdk *qrCodeSdk;
    
    WloginSdk_v2 *wloginSdk_v2;
    id qrCodeInterfaceDelegate;
    
    ZXingWidgetController *widController;
    NSString *scanResult;
    
}

-(id)initWithQRCodeInterface:(WloginSdk_v2 *)sdk andUin:(NSString *)userAccount andAppid:(uint32_t)dwAppid andDelegate:(id)delegate;

-(int)parseandVerifyQRCode:(NSString *)scanString;
-(void)parseandConfirmQRCodeWithData:(NSData *)data;


-(UIViewController *)startScanQRByController;
-(void)stopCapture;

@end
