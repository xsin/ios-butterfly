//
//  CaptchaViewController.m
//  WtloginDemo
//
//  Created by gavinsu on 13-6-6.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import "CaptchaViewController.h"
#import "MainViewController.h"
#import "LoginService.h"

NSString * const kLoginResultNotification = @"kLoginResultNotification";

@interface CaptchaViewController ()

@property (nonatomic, strong) UIImageView *bgView;

@property (nonatomic, strong) UILabel *wordingLabel;    //提示语
@property (nonatomic, strong) UIImageView *picImage;    //验证码图片
@property (nonatomic, strong) UIButton *refressButton;  //换一张
@property (nonatomic, strong) UITextField *picCodeText; //输入验证码的区域
@property (nonatomic, strong) UIButton *submitButton;   //提交

@end

@implementation CaptchaViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)setWordingDic:(NSDictionary *)wordingDic
{
    _wordingDic = wordingDic;
}

-(void)setPicData:(NSData *)data
{
    if (!_picImage) {
        _picImage = [[UIImageView alloc] init];
    }
    _picImage.image = [UIImage imageWithData:data];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
   
    //bgView
    _bgView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, MainScreenWidth, MainScreenHeight)];
    _bgView.image = [UIImage imageNamed:@"main_bg"];
    [self.view addSubview:_bgView];
    
    //wordingLabel
    _wordingLabel = [[UILabel alloc] initWithFrame:CGRectMake(5, 5, 310, 30)];
    _wordingLabel.backgroundColor = [UIColor clearColor];
    _wordingLabel.textColor = [UIColor whiteColor];
    _wordingLabel.numberOfLines = 0;
    [self.view addSubview:_wordingLabel];
    if (_wordingDic) {
        _wordingLabel.text = [_wordingDic objectForKey:@"pic_reason"];
    }
    _wordingLabel.font = [UIFont systemFontOfSize:14.0f];
    [_wordingLabel sizeToFit];
   
    //picImage
    if (!_picImage) {
        _picImage = [[UIImageView alloc] init];
    }
    _picImage.frame = CGRectMake(25, 53, 100, 53);
    [self.view addSubview:_picImage];
    
    //refressButton
    _refressButton = [[UIButton alloc] initWithFrame:CGRectMake(153, 71, 130, 16)];
    [_refressButton setTitle:@"看不清除，换一张" forState:UIControlStateNormal];
    _refressButton.titleLabel.font = [UIFont systemFontOfSize:14.0f];
    [_refressButton addTarget:self action:@selector(_onNextButton:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_refressButton];
   
    //picCodeText
    _picCodeText = [[UITextField alloc] initWithFrame:CGRectMake(31, 130, 260, 31)];
    _picCodeText.backgroundColor = [UIColor whiteColor];
    _picCodeText.placeholder = @"验证码";
    _picCodeText.clearButtonMode = UITextFieldViewModeWhileEditing;
    [_picCodeText addTarget:self action:@selector(_onSubmitButton:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [self.view addSubview:_picCodeText];
    
    //submitButton
    _submitButton = [[UIButton alloc] initWithFrame:CGRectMake(20, 188, 280, 40)];
    _submitButton.backgroundColor = [UIColor whiteColor];
    [_submitButton setTitle:@"验证" forState:UIControlStateNormal];
    [_submitButton setBackgroundImage:[UIImage imageNamed:@"button_bg_gr"] forState:UIControlStateNormal];
    [_submitButton setBackgroundImage:[UIImage imageNamed:@"button_bg_gr"] forState:UIControlStateHighlighted];
    [_submitButton addTarget:self action:@selector(_onSubmitButton:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_submitButton];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - WloginCallbackProtocol_v2

-(void)loginSuccessSig_v2:(WloginSdk_v2 *)sdk andSig:(NSMutableArray *)sigArray andBaseInfo:(WloginUserInfo *)userInfo tag:(long)tag
{
    WTSharedService.sigArray = sigArray;
    WTSharedService.userInfo = userInfo;
    
    [self dismissModalViewControllerAnimated:NO];
    [NSDefaultNotificationCenter postNotificationName:kLoginResultNotification object:nil userInfo:nil];
}

-(void)loginFailed_v2:(WloginSdk_v2 *)sdk andRst:(RETURN_VALUES_V2)result withErrInfo:(WloginErrInfo *)errInfo tag:(long)tag
{
    NSLog(@"FailUin:%@", errInfo.sErrorUserAccount);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self dismissModalViewControllerAnimated:YES];
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:errInfo.sErrorTitle
                                                        message:errInfo.sErrorMsg
                                                       delegate:self
                                              cancelButtonTitle:@"确定"
                                              otherButtonTitles:nil];
        [alert show];
    });
}

-(void)showPicture_v2:(WloginSdk_v2 *)sdk andPicData:(NSData *)pictureData andWording:(NSDictionary *)wordingDic tag:(long)tag
{
    [self setPicData:pictureData];
    _wordingDic = wordingDic;
}

#pragma mark - Private

- (void)_onNextButton:(id)sender
{
    RETURN_VALUES_V2 retValue;
    retValue = [g_loginSdk refreshPictureData_v2:self];
    if (retValue != WLOGIN_V2_SECCESS) {
        DLog(@"refreshPictureData_v2 ret: %d", retValue);
        return;
    }
}

- (void)_onSubmitButton:(id)sender
{
    if (_picCodeText.text.length == 0) {
        [_picCodeText becomeFirstResponder];
        return;
    }
    
    RETURN_VALUES_V2 retValue;
    retValue = [g_loginSdk checkPictureAndLogin_v2:_picCodeText.text andDelegate:self];
    if (retValue != WLOGIN_V2_SECCESS) {
        DLog(@"checkPictureAndLogin_v2 ret: %d", retValue);
        return;
    }
}

@end
