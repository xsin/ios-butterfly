//
//  AppDelegate.h
//  butterfly
//
//  Created by jeakeyliang on 14-5-17.
//  Copyright (c) 2014年 jeakeyliang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WTLoginSDK/WloginSdk_v2.h>

extern WloginSdk_v2 *g_loginSdk;


@interface AppDelegate : UIResponder <UIApplicationDelegate, UITabBarControllerDelegate>

@property (strong, nonatomic) UIWindow *window;

@end
