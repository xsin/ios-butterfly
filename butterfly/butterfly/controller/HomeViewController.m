//
//  HomeViewController.m
//  butterfly
//
//  Created by jeakeyliang on 14-5-17.
//  Copyright (c) 2014年 jeakeyliang. All rights reserved.
//

#import "HomeViewController.h"

@interface HomeViewController ()

@end

@implementation HomeViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        self.title=self.main_title;
    }
    return self;
}

- (void)loadView
{
    [super loadView];
    
    self.title=self.main_title;
    UIWebView *mainWebview = [[UIWebView alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    NSURL *url = [NSURL URLWithString:self.webview_url];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    [mainWebview loadRequest:request];
    [self.view addSubview:mainWebview];
    [mainWebview release];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
