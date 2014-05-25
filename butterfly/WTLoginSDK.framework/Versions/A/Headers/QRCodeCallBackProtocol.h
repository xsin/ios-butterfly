//
//  QRCodeCallBackProtocol.h
//  wtlogin_demo
//
//  Created by 然 刘 on 12-7-2.
//  Copyright (c) 2012年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum{
    QRCODE_SUCCESS = 0,            //成功
    QRCODE_NETWORK_ERROR = 0x1,    //网络错误
    QRCODE_SCAN_STR_UNKNOWN = 0x2, //二维码无法识别
    QRCODE_STATE_ERROR = 0x6,      //状态错误： 可能是上一个调用流程没有结束，需要等待返回
    QRCODE_ERROR_SERVER = 0x10,    //server错误
    QRCODE_ERROR_LOCAL = 0x11,     //SDK错误
} QRCODE_RETURE_VALUES;

@protocol QRCodeCallBackProtocol <NSObject>

//二维码认证回调
-(void)qrCodeVerify_succ:(uint32_t)dwStTime withAppName:(NSString *)appName;
-(void)qrCodeVerify_failed:(QRCODE_RETURE_VALUES)cResult withMsg:(NSString *)errorMsg;

//二维码靠近回调
-(void)qrCodeConfirm_succ:(uint32_t)dwStTime withAppName:(NSString *)appName;;
-(void)qrCodeConfirm_failed:(QRCODE_RETURE_VALUES)cResult withMsg:(NSString *)errorMsg;

//其他错误回调接口
-(void)qrCodeFailed:(QRCODE_RETURE_VALUES)result withMsg:(NSString *)errorMsg;

@end
