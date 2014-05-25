//
//  QuickLoginStateViewController.m
//  WtloginDemo
//
//  Created by gavinsu on 13-6-7.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import "QuickLoginStateViewController.h"

@interface QuickLoginStateViewController ()

@property (nonatomic, strong) UIActivityIndicatorView *activityIndicator;
@property (nonatomic, strong) UILabel *activityLabel;

@end

@implementation QuickLoginStateViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    _activityIndicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    _activityIndicator.frame = CGRectMake(0, 0, 50, 50);
    _activityIndicator.center = self.view.center;
    [_activityIndicator startAnimating];
    [self.view addSubview:_activityIndicator];
    
    _activityLabel = [[UILabel alloc] initWithFrame:CGRectMake(0,
                                                               _activityIndicator.frame.origin.y + _activityIndicator.frame.size.height,
                                                               MainScreenWidth,
                                                               20.0f)];
    _activityLabel.backgroundColor = [UIColor clearColor];
    _activityLabel.text = @"正在快速登录中...";
    _activityLabel.textAlignment = NSTextAlignmentCenter;
    [self.view addSubview:_activityLabel];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - WloginCallbackProtocol_v2

-(void)quickLoginEnd_v2:(WloginSdk_v2 *)sdk andUrl:(NSURL *)url tag:(long)tag
{
    [self performSelector:@selector(_openUrl:) withObject:url afterDelay:3.0f];
}

-(void)_openUrl:(NSURL *)url
{
    [[UIApplication sharedApplication] openURL:url];
}

@end
