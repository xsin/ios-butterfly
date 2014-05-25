//
//  LoginViewController.m
//  WtloginDemo
//
//  Created by gavinsu on 13-6-6.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import "LoginViewController.h"
#import "CaptchaViewController.h"
#import "LoginService.h"

#define ALERT_TAG_ERRINFO 10

@interface LoginViewController ()

@property (nonatomic, strong) UIImageView *bgView;
@property (nonatomic, strong) UIButton      *bgButton;

@property (nonatomic, strong) UIImageView *titleView;
@property (nonatomic, strong) UIImageView *inputView;

@property (nonatomic, strong) UITextField   *uinField;
@property (nonatomic, strong) UITextField   *passwdField;

@property (nonatomic, strong) UIButton    *loginButton;

@property (nonatomic, assign) uint16_t    wErrorAddType;
@property (nonatomic, copy)   NSString    *sErrorAdd;

@end

@implementation LoginViewController

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
    
    //bgView
    _bgView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, MainScreenWidth, MainScreenHeight)];
    _bgView.image = [UIImage imageNamed:@"main_bg"];
    [self.view addSubview:_bgView];
    
    _bgButton = [[UIButton alloc] initWithFrame:UIScreen.mainScreen.bounds];
    _bgButton.backgroundColor = [UIColor clearColor];
    [_bgButton addTarget:self action:@selector(_onBgButton:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_bgButton];
    
    //titleView
    _titleView = [[UIImageView alloc] initWithFrame:CGRectMake(91, 51, 138, 39)];
    _titleView.image = [UIImage imageNamed:@"title"];
    [self.view addSubview:_titleView];
    
    //inputView
    _inputView = [[UIImageView alloc] initWithFrame:CGRectMake(20, 123, 280, 93)];
    _inputView.image = [UIImage imageNamed:@"qqpwd_input"];
    [self.view addSubview:_inputView];
    
    //uinField
    _uinField = [[UITextField alloc] initWithFrame:CGRectMake(36, 132, 260, 31)];
    _uinField.backgroundColor = [UIColor clearColor];
    _uinField.placeholder = @"支持QQ号/邮箱/手机号登录";
    _uinField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
    _uinField.clearButtonMode = UITextFieldViewModeWhileEditing;
    _uinField.text = @"";
    [_uinField addTarget:self action:@selector(_onUinField:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [self.view addSubview:_uinField];
    
    //passwdField
    _passwdField = [[UITextField alloc] initWithFrame:CGRectMake(36, 179, 260, 31)];
    _passwdField.backgroundColor = [UIColor clearColor];
    _passwdField.placeholder = @"密码";
    _passwdField.clearButtonMode = UITextFieldViewModeWhileEditing;
    _passwdField.text = @"";
    _passwdField.secureTextEntry = YES;
    [_passwdField addTarget:self action:@selector(_onPasswdField:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [self.view addSubview:_passwdField];
    
    //loginButton
    _loginButton = [UIButton buttonWithType:UIButtonTypeCustom];
    _loginButton.backgroundColor = [UIColor clearColor];
    _loginButton.frame = CGRectMake(20, 238, 280, 40);
    [_loginButton setTitle:@"登录" forState:UIControlStateNormal];
    [_loginButton setBackgroundImage:[UIImage imageNamed:@"button_bg_gr"] forState:UIControlStateNormal];
    [_loginButton setBackgroundImage:[UIImage imageNamed:@"button_bg_gr"] forState:UIControlStateHighlighted];
    [_loginButton addTarget:self action:@selector(_onLoginBottonPress:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_loginButton];
    
    [NSDefaultNotificationCenter addObserver:self selector:@selector(onLoginResult:) name:kLoginResultNotification object:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - kLoginResultNotification 

- (void)onLoginResult:(NSNotification*)notification
{
    [[self presentingViewController] dismissModalViewControllerAnimated:YES];
}

#pragma mark - WloginCallbackProtocol_v2

-(void)loginSuccessSig_v2:(WloginSdk_v2 *)sdk andSig:(NSMutableArray *)sigArray andBaseInfo:(WloginUserInfo *)userInfo tag:(long)tag
{
    WTSharedService.sigArray = sigArray;
    WTSharedService.userInfo = userInfo;
    
    [self dismissModalViewControllerAnimated:YES];
}

-(void)loginFailed_v2:(WloginSdk_v2 *)sdk andRst:(RETURN_VALUES_V2)result withErrInfo:(WloginErrInfo *)errInfo tag:(long)tag
{
    NSLog(@"FailUin:%@", errInfo.sErrorUserAccount);

    
    dispatch_async(dispatch_get_main_queue(), ^{
        DLog(@"tagcode %d", sdk.serverReplyErrorCode);
        _wErrorAddType = errInfo.wErrorAddType;
        _sErrorAdd = errInfo.sErrorAdd;
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:errInfo.sErrorTitle
                                                        message:errInfo.sErrorMsg
                                                       delegate:self
                                              cancelButtonTitle:@"确定"
                                              otherButtonTitles:nil];
        alert.tag = ALERT_TAG_ERRINFO;
        [alert show];
    });
}

-(void)inputPassword_v2:(WloginSdk_v2 *)sdk andAccount:(NSString *)account tag:(long)tag
{
    [_passwdField becomeFirstResponder];
    
    RETURN_VALUES_V2 retValue = [sdk loginWithPasswd_v2:_uinField.text andPwd:_passwdField.text andLoginFlag:LOGIN_V2_GEN_PASSWD_SIG andDelegate:self];
    if (retValue != WLOGIN_V2_SECCESS) {
        DLog(@"TAG_LOGIN loginWithPasswd_v2 retValue = %d", retValue);
    }
}

-(void)showPicture_v2:(WloginSdk_v2 *)sdk andPicData:(NSData *)pictureData andWording:(NSDictionary *)wordingDic tag:(long)tag
{
    CaptchaViewController *vc = [[CaptchaViewController alloc] initWithNibName:nil bundle:nil];
    [vc setPicData:pictureData];
    vc.wordingDic = wordingDic;
    [self presentModalViewController:vc animated:NO];
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView.tag == ALERT_TAG_ERRINFO)  {
        if (_wErrorAddType == 1) {
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:_sErrorAdd]];
        }
    }
}

#pragma mark - Private

- (void)_onLoginBottonPress:(id)sender
{
    if (![self _checkParam]) {
        return;
    }
   
    RETURN_VALUES_V2 retValue;

    if ([g_loginSdk hasPasswordSig_v2:_uinField.text]) {
        [[g_loginSdk globalWtloginSdk] setLoginSubAppid:LOGIN_SUBAPPID];
        retValue = [g_loginSdk getUserSigAndBasicInfoByLogin_v2:_uinField.text
                                                       andAppid:LOGIN_APPID
                                                   andSigBitmap:LOGIN_SIGBITMAP
                                                         andPwd:nil
                                                   andLoginFlag:LOGIN_V2_WITH_PASSWD_SIG_GEN
                                                    andDelegate:self];
    } else {
        [[g_loginSdk globalWtloginSdk] setLoginSubAppid:LOGIN_SUBAPPID];
        retValue = [g_loginSdk getUserSigAndBasicInfoByLogin_v2:_uinField.text
                                                       andAppid:LOGIN_APPID
                                                   andSigBitmap:LOGIN_SIGBITMAP
                                                         andPwd:_passwdField.text
                                                   andLoginFlag:LOGIN_V2_GEN_PASSWD_SIG
                                                    andDelegate:self];
    }
    
    if (retValue != WLOGIN_V2_SECCESS) {
        DLog(@"getUserSigAndBasicInfoByLogin_v2 ret: %d", retValue);
        return;
    }
}

- (void)_onUinField:(id)sender
{
    if (_uinField.text.length == 0) {
        [_uinField becomeFirstResponder];
        return;
    }
    
    if ([g_loginSdk hasPasswordSig_v2:_uinField.text]) {
        _passwdField.text = @"********";
    } else {
        [_passwdField becomeFirstResponder];
    }
}

- (void)_onPasswdField:(id)sender
{
    if (![self _checkParam]) {
        return;
    }
}

- (void)_onBgButton:(id)sender
{
    for (UIView *v in self.view.subviews) {
        if ([v isKindOfClass:[UITextView class]] || [v isKindOfClass:[UITextField class]]) {
            [v resignFirstResponder];
        }
    }
}

-(BOOL)_checkParam
{
    if (_uinField.text.length == 0) {
        [_uinField becomeFirstResponder];
        return NO;
    }
    
    if (_passwdField.text.length == 0) {
        [_passwdField becomeFirstResponder];
        return NO;
    }
    return YES;
}

@end
