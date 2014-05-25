//
//  QuickLoginViewController.h
//  WtloginDemo
//
//  Created by gavinsu on 13-10-15.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WTLoginSDK/WloginCallbackProtocol_v2.h>

@interface QuickLoginViewController : UIViewController<UITableViewDataSource, UITableViewDelegate, WloginCallbackProtocol_v2>

@property (nonatomic, strong) NSURL          *url;
@property (nonatomic, copy)   NSString       *sourceApplication;

- (void)dataSourceArrayInit;

@end
