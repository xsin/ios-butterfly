//
//  QRCodeInterface.m
//  wtlogin_demo
//
//  Created by 然 刘 on 12-7-2.
//  Copyright (c) 2012年 tencent. All rights reserved.
//

#import "QRCodeInterface.h"

#import "WTLoginSDK/SBJson.h"
#import "WTLoginSDK/WTLoginLog.h"
#import "WTLoginSDK/QRCodeSdk.h"

#import "ZXingWidgetController.h"
#import "QRCodeInterfaceProtocol.h"

@implementation QRCodeInterface

-(id)initWithQRCodeInterface:(WloginSdk_v2 *)sdk andUin:(NSString *)userAccount andAppid:(uint32_t)dwAppid andDelegate:(id)delegate
{
    self = [super init];
    if (self) {
        qrAccount = [userAccount copy];
        wloginSdk_v2 = sdk;
        [wloginSdk_v2 retain];
        
        dwQrAppid = dwAppid;
        
        qrCodeSdk = [[QRCodeSdk alloc] initWithQRCodeSdk:sdk andDelegate:self];
        qrCodeInterfaceDelegate = delegate;
    }
    return self;
}

-(void)dealloc
{
    [qrAccount release];
    [scanResult release];
    [wloginSdk_v2 release];
    [qrCodeSdk release];
    [super dealloc];
}


-(int)parseandVerifyQRCode:(NSString *)scanString
{
    if ([qrCodeSdk verifyQRCode:scanString forAccount:qrAccount andAppid:dwQrAppid] == QRCODE_SCAN_STR_UNKNOWN) {
        DLog(@"verifyQRCode failed");
        return -1;
    }
    
    return 0;
}

-(void)parseandConfirmQRCodeWithData:(NSData *)data
{
    [qrCodeSdk confirmQRCode:scanResult withT:QRCODE_TLV_MIBAO andData:data];
}

-(void)qrCodeVerify_succ:(uint32_t)dwStTime withAppName:(NSString *)appName
{
    DLog(@"dwStTime = %u", dwStTime);
    
    //card上下跳
    if (qrCodeInterfaceDelegate != nil && [qrCodeInterfaceDelegate respondsToSelector:@selector(didCheckQRSuccess:forUin:)]) {
        [qrCodeInterfaceDelegate didCheckQRSuccess:[NSString stringWithFormat:@"%@(%u)",appName,[qrCodeSdk getAppidByLoginQRCode:scanResult]] forUin:qrAccount];
    }

}

-(void)qrCodeVerify_failed:(uint8_t)cResult withMsg:(NSString *)errorMsg
{
    DLog(@"cResult = 0x%x", cResult);
    [self stopCapture];
    
    if (qrCodeInterfaceDelegate != nil && [qrCodeInterfaceDelegate respondsToSelector:@selector(qrLoginFailed:withMsg:)]) {
        [qrCodeInterfaceDelegate qrLoginFailed:cResult withMsg:errorMsg];
    }
}

-(void)qrCodeConfirm_succ:(uint32_t)dwStTime withAppName:(NSString *)appName
{
    DLog(@"dwStTime = %u", dwStTime);
    
    if (qrCodeInterfaceDelegate != nil && [qrCodeInterfaceDelegate respondsToSelector:@selector(didConfirmQRSuccess:forUin:)]) {
        [qrCodeInterfaceDelegate didConfirmQRSuccess:[NSString stringWithFormat:@"%@(%u)",appName,[qrCodeSdk getAppidByLoginQRCode:scanResult]] forUin:qrAccount];
    }
}

-(void)qrCodeConfirm_failed:(uint8_t)cResult withMsg:(NSString *)errorMsg
{
    DLog(@"cResult = 0x%x", cResult);
    
    if (qrCodeInterfaceDelegate != nil && [qrCodeInterfaceDelegate respondsToSelector:@selector(qrLoginFailed:withMsg:)]) {
        [qrCodeInterfaceDelegate qrLoginFailed:cResult withMsg:errorMsg];
    }
}

-(void)qrCodeFailed:(QRCODE_RETURE_VALUES)result withMsg:(NSString *)errorMsg
{
    DLog(@"QRCODE_RETURN_VALUES = 0x%x", result);
    
    if (qrCodeInterfaceDelegate != nil && [qrCodeInterfaceDelegate respondsToSelector:@selector(qrLoginFailed:withMsg:)]) {
        [qrCodeInterfaceDelegate qrLoginFailed:result withMsg:errorMsg];
    }
}

- (void)stopCapture
{
    [widController stopCapture];
    widController = nil;
}

-(UIViewController *)startScanQRByController
{
    widController = [[ZXingWidgetController alloc] initWithDelegate:self showCancel:YES OneDMode:NO];
    QRCodeReader* qrcodeReader = [[QRCodeReader alloc] init];
    NSSet *readers = [[NSSet alloc ] initWithObjects:qrcodeReader,nil];
    widController.readers = readers;
    
    //NSBundle *mainBundle = [NSBundle mainBundle];
    //widController.soundToPlay =
    //[NSURL fileURLWithPath:[mainBundle pathForResource:@"beep-beep" ofType:@"aiff"] isDirectory:NO];
    
    widController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:widController];
    
    return navController;
}

#pragma mark -
#pragma mark ZXingDelegateMethods

- (void)zxingController:(ZXingWidgetController*)controller didScanResult:(NSString *)result 
{
    scanResult = [result copy];
    DLog(@"scanResult = %@", result);
    
    [self stopCapture];
    
    int iRet = [self parseandVerifyQRCode:scanResult];
    if (iRet == 0) {
        DLog(@"parseandVerifyQRCode success");
        
        if (qrCodeInterfaceDelegate != nil && [qrCodeInterfaceDelegate respondsToSelector:@selector(didScanQRSuccess)]) {
            [qrCodeInterfaceDelegate didScanQRSuccess];
        }
    } else {
        UIAlertView *alert = [[UIAlertView alloc]
                              initWithTitle:@"扫描结果"
                              message:result 
                              delegate:self
                              cancelButtonTitle:@"ok" 
                              otherButtonTitles:nil];
        [alert show];
    }

    [controller dismissModalViewControllerAnimated:NO];
}

- (void)zxingControllerDidCancel:(ZXingWidgetController*)controller 
{
    [self stopCapture];
}


@end
