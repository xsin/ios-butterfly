//
//  QRCodeSdk.h
//  wtlogin_demo
//
//  Created by 然 刘 on 12-7-2.
//  Copyright (c) 2012年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QRCodeCallBackProtocol.h"
#import "WloginTranCallbackProtocol.h"


@class MemSig;
@class WloginTranSdk;
@class QRCodeCmd;
@class WloginSdk;


typedef enum{
    QRCODE_TLV_NONE = 0,           //没有tlv
    QRCODE_TLV_MIBAO = 1,          //密保签名
    QRCODE_TLV_LOGIN_STATE = 2,    //登录状态（隐身，在线等）
    QRCODE_TLV_CONFIRM_MSG = 3,    //二维码登录确认界面提示语
    QRCODE_TLV_LOGIN_ACCOUNT = 4,    //登录时用户输入的账号
    QRCODE_TLV_LOGIN_CITY = 5,    //二维码登录pc的登录地
    QRCODE_TLV_PTAPPID = 6,     //pc拉取二维码的appid
    QRCODE_TLV_WTAPPID = 7,     //手机扫二维码的appid
    QRCODE_TLV_MAX = 64,        //最大个数
} QRCODE_TLV_TYPE;


@interface QRCodeSdk : NSObject <WloginTranCallbackProtocol> {
    
#if __has_feature(objc_arc_weak)
	__weak id qrCodeDelegate;
#else
	__unsafe_unretained id qrCodeDelegate;
#endif
    
    uint64_t ddwAccountUin;
    MemSig *accountTGTSig;
    
    WloginTranSdk * qrCodeTransportSdk;
    id wtloginSdkHelper;
    
    int iQRCodeState;
    QRCodeCmd *qrCodeCmd;
    
    NSMutableDictionary *uploadTlvDataDic;
}

//初始化接口
-(id)initWithQRCodeSdk:(id)sdk andDelegate:(id)delegate;

//认证二维码，uploadData 验证的时候携带数据
-(QRCODE_RETURE_VALUES)verifyQRCode:(NSString *)qrScanStr forAccount:(NSString *)userAccount andAppid:(uint32_t)dwAppid;
//获取verify返回的tlv数据
-(NSData *)getVerifyTlvDataBy:(QRCODE_TLV_TYPE)wTlvT;

//确认二维码
-(QRCODE_RETURE_VALUES)confirmQRCode:(NSString *)qrScanStr withT:(QRCODE_TLV_TYPE)wTlvT andData:(NSData *)uploadData;
//确认二维码时提交多个TLV
-(BOOL)addConfirmUploadTlv:(QRCODE_TLV_TYPE)wTlvT andData:(NSData *)uploadData;

//判断是否是登录二维码
-(BOOL)isValiedLoginQRCode:(NSString *)scanString;

//获取appid
-(uint32_t)getAppidByLoginQRCode:(NSString *)scanString;

@end
