//
//  UCViewController.h
//  butterfly
//
//  Created by 吴 嘉骏 on 14-5-18.
//  Copyright (c) 2014年 jeakeyliang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WTLoginSDK/WloginSdk_v2.h>
#import <WTLoginSDK/WloginErrInfo.h>
#import "QRCodeInterfaceProtocol.h"

extern WloginSdk_v2 *g_loginSdk;


@interface UCViewController : UIViewController<UIActionSheetDelegate, QRCodeInterfaceProtocol>
@property (nonatomic, retain) NSString *webview_url;
@property (nonatomic, retain) NSString *main_title;

@end
