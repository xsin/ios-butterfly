//
//  DetailViewController.h
//  butterfly
//
//  Created by jeakeyliang on 14-6-2.
//
//

#import <Cordova/CDVViewController.h>
#import <Cordova/CDVCommandDelegateImpl.h>
#import <Cordova/CDVCommandQueue.h>
#import "MBProgressHUD.h"

@interface DetailViewController : CDVViewController
@property (nonatomic,strong) UIWebView *mainWebview;
@property (nonatomic, retain) NSString *webview_url;
@property (nonatomic, retain) NSString *main_title;
@end

