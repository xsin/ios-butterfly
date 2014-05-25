//
//  MainViewController.h
//  WtloginDemo
//
//  Created by gavinsu on 13-6-6.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WTLoginSDK/WloginSdk_v2.h>
#import <WTLoginSDK/WloginErrInfo.h>
#import "QRCodeInterfaceProtocol.h"

extern WloginSdk_v2 *g_loginSdk;

@interface MainViewController : UIViewController<UIActionSheetDelegate, QRCodeInterfaceProtocol>
@property (nonatomic, retain) NSString *webview_url;
@property (nonatomic, retain) NSString *main_title;

@end
