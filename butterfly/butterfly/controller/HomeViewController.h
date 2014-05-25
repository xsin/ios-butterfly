//
//  HomeViewController.h
//  butterfly
//
//  Created by jeakeyliang on 14-5-17.
//  Copyright (c) 2014年 jeakeyliang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZBarSDK.h"

@interface HomeViewController : UIViewController<UINavigationControllerDelegate,UIImagePickerControllerDelegate,ZBarReaderDelegate>
{
    int num;
    BOOL upOrdown;
    NSTimer * timer;
}

@property (nonatomic,strong) UIWebView *mainWebview;
@property (nonatomic, strong) UIImageView * line;
@property (nonatomic, retain) NSString *webview_url;
@property (nonatomic, retain) NSString *main_title;
@end
