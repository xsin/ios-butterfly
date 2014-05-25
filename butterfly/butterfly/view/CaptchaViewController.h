//
//  CaptchaViewController.h
//  WtloginDemo
//
//  Created by gavinsu on 13-6-6.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WTLoginSDK/WloginCallbackProtocol_v2.h>

extern NSString * const kLoginResultNotification;   //登录结果通知

@interface CaptchaViewController : UIViewController<WloginCallbackProtocol_v2>

@property (nonatomic, strong) NSDictionary *wordingDic;

-(void)setPicData:(NSData *)data;

@end
