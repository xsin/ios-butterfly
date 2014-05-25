//
//  MainViewController.m
//  WtloginDemo
//
//  Created by gavinsu on 13-6-6.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import "MainViewController.h"
#import "LoginViewController.h"
#import "CaptchaViewController.h"
#import "QRCodeInterface.h"
#import "LoginService.h"
#include <sys/time.h>

enum TAG {
    TAG_ACTIONSHEET_1 = 1000
};

struct timeval stDemoLastTime;
struct timeval stDemoCurTime;
long long ddwDemoDiff;

#define  TIME_LOG(fmt, args...) do { \
gettimeofday(&stDemoCurTime,NULL); \
ddwDemoDiff=(((long long)(stDemoCurTime.tv_sec-stDemoLastTime.tv_sec)*1000+(long long)(stDemoCurTime.tv_usec-stDemoLastTime.tv_usec)/1000));\
NSLog(@"[%s][%d]%s costtime:%lld " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ddwDemoDiff, ## args); \
stDemoLastTime=stDemoCurTime;\
} while (0)



@interface MainViewController ()

@property (nonatomic, strong) UILabel *mainAccountLabel;        //主显帐号
@property (nonatomic, strong) UILabel *mainAccountContentLabel; 
@property (nonatomic, strong) UILabel *uinLabel;                //QQ号码
@property (nonatomic, strong) UILabel *uinContentLabel;
@property (nonatomic, strong) UILabel *nickLabel;               //昵称
@property (nonatomic, strong) UILabel *nickContentLabel;
@property (nonatomic, strong) UILabel *faceidLabel;             //头像ID
@property (nonatomic, strong) UILabel *faceidContentLabel;
@property (nonatomic, strong) UILabel *sexLabel;                //性别
@property (nonatomic, strong) UILabel *sexContentLabel;
@property (nonatomic, strong) UILabel *ageLabel;                //年龄
@property (nonatomic, strong) UILabel *ageContentLabel;

@property (nonatomic, strong) UITextView *sigTextView;          //sigTextView

@property (nonatomic, strong) QRCodeInterface *qrCodeInterface;

@end

@implementation MainViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        dispatch_async(dispatch_get_current_queue(), ^{
            [self _loginCheck];
        });
        
        _qrCodeInterface = [QRCodeInterface alloc];
    }
    return self;
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    self.navigationItem.title = @"登录成功";

    //leftItem
    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc]initWithTitle:@"二维码"
                                                                style:UIBarButtonItemStyleBordered
                                                               target:self
                                                               action:@selector(_clickLeftButton)];
    [self.navigationItem setLeftBarButtonItem:leftItem];

    //rightItem
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc]initWithTitle:@"操作"
                                                                style:UIBarButtonItemStyleBordered
                                                               target:self
                                                               action:@selector(_clickRightButton)];
    [self.navigationItem setRightBarButtonItem:rightItem];
    
    [self _updateSigArrayAndBaseInfo];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    [NSDefaultNotificationCenter addObserver:self selector:@selector(onLoginResult:) name:kLoginResultNotification object:nil];
    
    //mainAccount
    _mainAccountLabel = [[UILabel alloc] init];
    _mainAccountLabel.frame = CGRectMake(0, 20, MainScreenWidth/2 - 10, 20);
    _mainAccountLabel.text = @"主显帐号";
    _mainAccountLabel.textAlignment = NSTextAlignmentRight;
    [self.view addSubview:_mainAccountLabel];
    
    _mainAccountContentLabel = [[UILabel alloc] init];
    _mainAccountContentLabel.frame = CGRectMake(MainScreenWidth/2 + 10,
                                                _mainAccountLabel.frame.origin.y,
                                                _mainAccountLabel.frame.size.width,
                                                _mainAccountLabel.frame.size.height);
    [self.view addSubview:_mainAccountContentLabel];
    
    //uin
    _uinLabel = [[UILabel alloc] init];
    _uinLabel.frame = CGRectMake(_mainAccountLabel.frame.origin.x,
                                 _mainAccountLabel.frame.origin.y + _mainAccountLabel.frame.size.height + 5,
                                 _mainAccountLabel.frame.size.width,
                                 _mainAccountLabel.frame.size.height);
    _uinLabel.text = @"QQ号码";
    _uinLabel.textAlignment = NSTextAlignmentRight;
    [self.view addSubview:_uinLabel];
    
    _uinContentLabel = [[UILabel alloc] init];
    _uinContentLabel.frame = CGRectMake(_mainAccountContentLabel.frame.origin.x,
                                        _mainAccountContentLabel.frame.origin.y + _mainAccountContentLabel.frame.size.height + 5,
                                        _mainAccountContentLabel.frame.size.width,
                                        _mainAccountContentLabel.frame.size.height);
    [self.view addSubview:_uinContentLabel];
   
    //nick
    _nickLabel = [[UILabel alloc] init];
    _nickLabel.frame = CGRectMake(_uinLabel.frame.origin.x,
                                  _uinLabel.frame.origin.y + _uinLabel.frame.size.height + 5,
                                  _uinLabel.frame.size.width,
                                  _uinLabel.frame.size.height);
    _nickLabel.text = @"昵称";
    _nickLabel.textAlignment = NSTextAlignmentRight;
    [self.view addSubview:_nickLabel];
    
    _nickContentLabel = [[UILabel alloc] init];
    _nickContentLabel.frame = CGRectMake(_uinContentLabel.frame.origin.x,
                                         _uinContentLabel.frame.origin.y + _uinContentLabel.frame.size.height + 5,
                                         _uinContentLabel.frame.size.width,
                                         _uinContentLabel.frame.size.height);
    [self.view addSubview:_nickContentLabel];
    
    //faceid
    _faceidLabel = [[UILabel alloc] init];
    _faceidLabel.frame = CGRectMake(_nickLabel.frame.origin.x,
                                    _nickLabel.frame.origin.y + _nickLabel.frame.size.height + 5,
                                    _nickLabel.frame.size.width,
                                    _nickLabel.frame.size.height);
    _faceidLabel.text = @"头像ID";
    _faceidLabel.textAlignment = NSTextAlignmentRight;
    [self.view addSubview:_faceidLabel];
    
    _faceidContentLabel = [[UILabel alloc] init];
    _faceidContentLabel.frame = CGRectMake(_nickContentLabel.frame.origin.x,
                                           _nickContentLabel.frame.origin.y + _nickContentLabel.frame.size.height + 5,
                                           _nickContentLabel.frame.size.width,
                                           _nickContentLabel.frame.size.height);
    [self.view addSubview:_faceidContentLabel];
    
    //sex
    _sexLabel = [[UILabel alloc] init];
    _sexLabel.frame = CGRectMake(_faceidLabel.frame.origin.x,
                                 _faceidLabel.frame.origin.y + _faceidLabel.frame.size.height + 5,
                                 _faceidLabel.frame.size.width,
                                 _faceidLabel.frame.size.height);
    _sexLabel.text = @"性别";
    _sexLabel.textAlignment = NSTextAlignmentRight;
    [self.view addSubview:_sexLabel];
    
    _sexContentLabel = [[UILabel alloc] init];
    _sexContentLabel.frame = CGRectMake(_faceidContentLabel.frame.origin.x,
                                        _faceidContentLabel.frame.origin.y + _faceidContentLabel.frame.size.height + 5,
                                        _faceidContentLabel.frame.size.width,
                                        _faceidContentLabel.frame.size.height);
    [self.view addSubview:_sexContentLabel];
   
    //age
    _ageLabel = [[UILabel alloc] init];
    _ageLabel.frame = CGRectMake(_sexLabel.frame.origin.x,
                                 _sexLabel.frame.origin.y + _sexLabel.frame.size.height + 5,
                                 _sexLabel.frame.size.width,
                                 _sexLabel.frame.size.height);
    _ageLabel.text = @"年龄";
    _ageLabel.textAlignment = NSTextAlignmentRight;
    [self.view addSubview:_ageLabel];
    
    _ageContentLabel = [[UILabel alloc] init];
    _ageContentLabel.frame = CGRectMake(_sexContentLabel.frame.origin.x,
                                        _sexContentLabel.frame.origin.y + _sexContentLabel.frame.size.height + 5,
                                        _sexContentLabel.frame.size.width,
                                        _sexContentLabel.frame.size.height);
    [self.view addSubview:_ageContentLabel];
   
    _sigTextView = [[UITextView alloc] init];
    _sigTextView.frame = CGRectMake(10,
                                    _ageContentLabel.frame.origin.y + _ageContentLabel.frame.size.height + 5,
                                    MainScreenWidth - 2 * 10,
                                    MainScreenHeight - (_ageContentLabel.frame.origin.y + _ageContentLabel.frame.size.height + 5) - 20 - 44);
    _sigTextView.editable = NO;
    [self.view addSubview:_sigTextView];
    
    [self _updateSigArrayAndBaseInfo];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Public

- (void)onLoginResult:(NSNotification*)notification
{
    [self _updateSigArrayAndBaseInfo];
}

- (void)_updateSigArrayAndBaseInfo
{
    if (WTSharedService.userInfo == nil) {
        return;
    }
    
    _mainAccountContentLabel.text = WTSharedService.userInfo.sUserMainAccount;
    _uinContentLabel.text = [NSString stringWithFormat:@"%u", WTSharedService.userInfo.dwUserUin];
    _faceidContentLabel.text = [NSString stringWithFormat:@"%u", WTSharedService.userInfo.wFaceId];
    if (WTSharedService.userInfo.cGender == 0) {
        _sexContentLabel.text = @"未知";
    }
    else if(WTSharedService.userInfo.cGender == 1) {
        _sexContentLabel.text = @"男";
    }
    else {
        _sexContentLabel.text = @"女";
    }
    _ageContentLabel.text = [NSString stringWithFormat:@"%u", WTSharedService.userInfo.cAge];
    _nickContentLabel.text = WTSharedService.userInfo.sNickName;
   
    static BOOL bSwitch = YES;
    if (bSwitch) {
        _sigTextView.backgroundColor = [UIColor grayColor];
    } else {
        _sigTextView.backgroundColor = [UIColor whiteColor];
    }
    bSwitch = !bSwitch;
    
    _sigTextView.text = [NSString stringWithFormat:@"共%d种票据\n", WTSharedService.sigArray.count];
    MemSig *key;
    for (key in WTSharedService.sigArray) {
        _sigTextView.text = [_sigTextView.text stringByAppendingString:[key description]];
        _sigTextView.text = [_sigTextView.text stringByAppendingString:@"\n\n"];
    }


}

#pragma mark - Private

-(void)_loginCheck
{
    NSString *userAccount = [g_loginSdk lastLoginUser];
    
    if ([g_loginSdk isNeedLoginWithPasswd_v2:[g_loginSdk lastLoginUser] andAppid:LOGIN_APPID]) {
        LoginViewController *loginVC = [[LoginViewController alloc] initWithNibName:nil bundle:nil];
        [self presentModalViewController:loginVC animated:NO];
    } else {
        if ([g_loginSdk checkLocalSigValid_v2:userAccount andAppid:LOGIN_APPID andSigType:WLOGIN_GET_TGT]) {
            WTSharedService.sigArray = [g_loginSdk getMemUserSig_v2:userAccount andAppid:LOGIN_APPID andSigBitmap:LOGIN_SIGBITMAP];
            WTSharedService.userInfo = [g_loginSdk getBasicUserInfo_v2:userAccount];
        } else {
            RETURN_VALUES_V2 retValue = [g_loginSdk getUserSigAndBasicInfoByLogin_v2:userAccount
                                                                            andAppid:LOGIN_APPID
                                                                        andSigBitmap:LOGIN_SIGBITMAP
                                                                              andPwd:nil
                                                                        andLoginFlag:LOGIN_V2_WITH_PASSWD_SIG_GEN
                                                                         andDelegate:self];
            if (retValue != WLOGIN_V2_SECCESS) {
                DLog(@"getUserSigAndBasicInfo_v2 ret: %d", retValue);
                return;
            }
        }
    }
}

- (void)_clickLeftButton
{
    //初始化
    _qrCodeInterface = [_qrCodeInterface initWithQRCodeInterface:g_loginSdk andUin:[NSString stringWithFormat:@"%u", WTSharedService.userInfo.dwUserUin] andAppid:LOGIN_APPID andDelegate:self];
    [self presentModalViewController:[_qrCodeInterface startScanQRByController] animated:YES];
}

- (void)_clickRightButton
{
    UIActionSheet *actionSheet = [[UIActionSheet alloc]
                                  initWithTitle:nil
                                  delegate:self
                                  cancelButtonTitle:@"取消"
                                  destructiveButtonTitle:nil
                                  otherButtonTitles:@"切换用户",
                                                    @"注销帐号",
                                                    @"跳转第三方",
                                                    @"MSF跳转换票",
                                                    @"换票续期",
                                                    @"获取本地票据",
                                                    @"获取OPENID/OPENKEY",
                                                    @"主动快速登录",
                                                    @"保存密码登录",
                                                    @"接口性能",
                                                    nil];
    actionSheet.tag = TAG_ACTIONSHEET_1;
    
    [actionSheet showFromBarButtonItem:self.navigationItem.rightBarButtonItem animated:YES];
}

#pragma mark - WloginCallbackProtocol_v2

-(void)loginSuccessSig_v2:(WloginSdk_v2 *)sdk andSig:(NSMutableArray *)sigArray andBaseInfo:(WloginUserInfo *)userInfo tag:(long)tag
{
    TIME_LOG(@"loginSuccessSig_v2");
    
    self.navigationItem.title = @"登录成功";
    
    WTSharedService.sigArray = sigArray;
    WTSharedService.userInfo = userInfo;
    [self _updateSigArrayAndBaseInfo];
}

-(void)loginFailed_v2:(WloginSdk_v2 *)sdk andRst:(RETURN_VALUES_V2)result withErrInfo:(WloginErrInfo *)errInfo tag:(long)tag
{
    NSLog(@"FailUin:%@", errInfo.sErrorUserAccount);

    if (errInfo.wErrorCode == 0xf) { //A2过期
        [[g_loginSdk globalWtloginSdk] setLoginSubAppid:LOGIN_SUBAPPID];
        RETURN_VALUES_V2 retValue = [g_loginSdk getUserSigAndBasicInfoByLogin_v2:[g_loginSdk lastLoginUser]
                                                                        andAppid:LOGIN_APPID
                                                                    andSigBitmap:LOGIN_SIGBITMAP
                                                                          andPwd:nil
                                                                    andLoginFlag:LOGIN_V2_WITH_PASSWD_SIG_GEN
                                                                     andDelegate:self];
        DLog(@"retValue: 0x%x", retValue);
    } else {
        self.navigationItem.title = @"登录失败";
        
        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:errInfo.sErrorTitle
                                                            message:[NSString stringWithFormat:@"(0x%x) %@", errInfo.wErrorCode, errInfo.sErrorMsg]
                                                           delegate:self
                                                  cancelButtonTitle:@"确定"
                                                  otherButtonTitles:nil];
            [alert show];
        });
    }
}

#pragma mark - WloginCallbackProtocol_v2:QuickLogin

-(void)quickLoginEnd_v2:(WloginSdk_v2 *)sdk andUrl:(NSURL *)url tag:(long)tag
{
    [self performSelector:@selector(_openUrl:) withObject:url afterDelay:2.0f];
}

-(void)_openUrl:(NSURL *)url
{
    [[UIApplication sharedApplication] openURL:url];
}

#pragma mark - QRCodeInterfaceProtocol

-(void)didScanQRSuccess
{
    
}

-(void)didCheckQRSuccess:(NSString *)appName forUin:(NSString *)account
{
    UIAlertView *alert = [[UIAlertView alloc]
                          initWithTitle:@"提示"
                          message: [NSString stringWithFormat:@"确认授权PC登录%@吗？", appName]
                          delegate:self
                          cancelButtonTitle:@"取消"
                          otherButtonTitles:@"确认登录", nil];
    [alert show];
}
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex  // after animation
{
    if (buttonIndex == 1) {
        [_qrCodeInterface parseandConfirmQRCodeWithData:nil];
    }
    else {
        //qrCodeInterface
    }
}

-(void)didConfirmQRSuccess:(NSString *)appName forUin:(NSString *)account
{
    UIAlertView *alert = [[UIAlertView alloc]
                          initWithTitle:@"提示"
                          message:[NSString stringWithFormat:@"授权PC登录%@成功", appName]
                          delegate:nil
                          cancelButtonTitle:@"ok"
                          otherButtonTitles:nil];
    [alert show];
}

-(void)qrLoginFailed:(uint8_t)cResult withMsg:(NSString *)msg
{
    UIAlertView *alert = [[UIAlertView alloc]
                          initWithTitle:@"提示"
                          message:msg
                          delegate:nil
                          cancelButtonTitle:@"ok"
                          otherButtonTitles:nil];
    [alert show];
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) { //切换用户
        LoginViewController *loginVC = [[LoginViewController alloc] initWithNibName:nil bundle:nil];
        [self presentModalViewController:loginVC animated:NO];
    }
    else if (buttonIndex == 1) { //注销
        [g_loginSdk clearUserLoginData_v2:[g_loginSdk lastLoginUser]];
        LoginViewController *loginVC = [[LoginViewController alloc] initWithNibName:nil bundle:nil];
        [self presentModalViewController:loginVC animated:NO];
    }
    else if (buttonIndex == 2)
    {
        //跳转第三方
        uint32_t adwAppidList[1] = {LOGIN_APPID};
        RETURN_VALUES_V2 retValue = [g_loginSdk getUserSigAndBasicInfoByExchage_v2:[g_loginSdk lastLoginUser]
                                                                          andAppid:WTLOGIN_OPEN_APPID
                                                                      andSigBitmap:WLOGIN_GET_TOKEN
                                                                  andOtherAppidNum:(sizeof(adwAppidList)/sizeof(adwAppidList[0]))
                                                                 andOtherAppidList:adwAppidList
                                                                       andDelegate:self];
        if (retValue != WLOGIN_V2_SECCESS) {
            [self _showErrMsg:[NSString stringWithFormat:@"换票错误：0x%x", retValue]];
        }
    }
    else if (buttonIndex == 3)
    {
        //MSF跳转
        NSString *sTmpA2= @"c2b9cb6eb6129deac40707bf37bda39f1406f9b2ba6479c796a0d7ffe92a76706f6efb8f532a8360615e614127af480aa7193ecc771fa12173c7ec8dfb7231cd07bda3a53a386493";
		NSString *sTmpD2= @"cc75a524f26fbb6e8d2c2e5b120afd35fd94bc0ad1ccbf73ff54725d615c2693ba657e192dcbe905";
		NSString *sTmpD2Key = @"728067db000000000000000000000000";
        
        MemSig *sigTgt = [[MemSig alloc]init];
        MemSig *sigD2 = [[MemSig alloc] init];
        
        sigTgt.sig = [self WloginHexRead:[sTmpA2 UTF8String] andLen:[sTmpA2 length]];
        sigD2.sig = [self WloginHexRead:[sTmpD2 UTF8String] andLen:[sTmpD2 length]];
        sigD2.sigKey = [self WloginHexRead:[sTmpD2Key UTF8String] andLen:[sTmpD2Key length]];
        
        [g_loginSdk getUserSigAndBasicInfoByMSF_v2:sigTgt
                                             andD2:sigD2
                                        forAccount:[g_loginSdk lastLoginUser]
                                          andAppid:549000910
                                      andSigBitmap:LOGIN_SIGBITMAP
                                  andOtherAppidNum:0
                                 andOtherAppidList:NULL
                                       andDelegate:self];
         
    }
    else if (buttonIndex == 4)
    {
        //换票续期
        RETURN_VALUES_V2 retValue = [g_loginSdk getUserSigAndBasicInfoByExchage_v2:[g_loginSdk lastLoginUser] andAppid:LOGIN_APPID andSigBitmap:LOGIN_SIGBITMAP andDelegate:self];
        if (retValue != WLOGIN_V2_SECCESS) {
            [self _showErrMsg:[NSString stringWithFormat:@"换票错误：0x%x", retValue]];
        }
    }
    else if (buttonIndex == 5)
    {
        //获取本地票据
        NSMutableArray *tempArray = [g_loginSdk getMemUserSig_v2:[g_loginSdk lastLoginUser] andAppid:LOGIN_APPID andSigBitmap:LOGIN_SIGBITMAP];
        
        UIAlertView *alert = [[UIAlertView alloc]
                              initWithTitle:@"提示"
                              message: [tempArray description]
                              delegate:nil
                              cancelButtonTitle:@"ok"
                              otherButtonTitles:nil];
        [alert show];
    }
    else if (buttonIndex == 6)
    {
        //获取OPENID/OPENKEY
        RETURN_VALUES_V2 retValue = [g_loginSdk getOpenSig_v2:[g_loginSdk lastLoginUser]
                                                  andByAppid:LOGIN_APPID
                                                 andForOpenid:100619284
//                                                andSigBitmap:WLOGIN_GET_OPENKEY
                                                andSigBitmap:WLOGIN_GET_TOKEN
                                                  andDelegate:self];
        if (retValue != WLOGIN_V2_SECCESS) {
            DLog(@"getOpenSig_v2 ret: %d", retValue);
            return;
        }
    }
    else if (buttonIndex == 7)
    {
        long tag = 0;
        RETURN_VALUES_V2 retValue = [g_loginSdk quickLoginActiveStart_v2:[g_loginSdk lastLoginUser]
                                                               SelfAppid:0x10
                                                            SelfSubAppid:0x1
                                                                DstAppid:0x11
                                                             DstSubAppid:0x1
                                                    DstSourceApplication:@"com.wtlogin.QuickLoginApp"
                                                               DstScheme:@"quickloginapp"
                                                             andDelegate:self
                                                                     tag:&tag];
        if (retValue != WLOGIN_V2_SECCESS) {
            DLog(@"quickLoginActiveStart_v2 ret: %d", retValue);
            return;
        }
    }
    else if (buttonIndex == 8) // 保存密码登录
    {
        long tag = 0;
        RETURN_VALUES_V2 retValue = [g_loginSdk getUserSigAndBasicInfoByLogin_v2:[g_loginSdk lastLoginUser] andAppid:LOGIN_APPID andSigBitmap:LOGIN_SIGBITMAP andPwd:nil andLoginFlag:LOGIN_V2_WITH_PASSWD_SIG_GEN andDelegate:self tag:&tag];
        if (retValue != WLOGIN_V2_SECCESS) {
            [self _showErrMsg:[NSString stringWithFormat:@"保存密码登录错误：0x%x", retValue]];
        }
    }
    else if(buttonIndex == 9) // 接口性能
    {
        [g_loginSdk setLogLevel:2];
        TIME_LOG();
        
        NSString* userAccount = [g_loginSdk lastLoginUser];
        TIME_LOG(@"lastLoginUser");
        
        [g_loginSdk checkLocalSigValid_v2:userAccount andAppid:LOGIN_APPID andSigType:WLOGIN_GET_TGT];
        TIME_LOG(@"checkLocalSigValid_v2");
        
        NSMutableArray *tempArray = [g_loginSdk getMemUserSig_v2:userAccount andAppid:LOGIN_APPID andSigBitmap:LOGIN_SIGBITMAP];
        TIME_LOG(@"getMemUserSig_v2");
        
        [g_loginSdk isNeedLoginWithPasswd_v2:userAccount andAppid:LOGIN_APPID];
        TIME_LOG(@"isNeedLoginWithPasswd_v2");
        
        RETURN_VALUES_V2 retValue = [g_loginSdk getUserSigAndBasicInfoByLogin_v2:userAccount
                                                                        andAppid:LOGIN_APPID
                                                                    andSigBitmap:LOGIN_SIGBITMAP
                                                                          andPwd:nil
                                                                    andLoginFlag:LOGIN_V2_WITH_PASSWD_SIG_GEN
                                                                     andDelegate:self];
        TIME_LOG(@"getUserSigAndBasicInfoByLogin_v2");
        sleep(2);
        
        TIME_LOG();
        retValue = [g_loginSdk getUserSigAndBasicInfoByExchage_v2:userAccount andAppid:LOGIN_APPID andSigBitmap:LOGIN_SIGBITMAP andDelegate:self];
        TIME_LOG(@"getUserSigAndBasicInfoByExchage_v2");
      //  [g_loginSdk setLogLevel:5];

    }
}

#pragma mark - Private

- (NSData *) WloginHexRead:(const char*) sStr andLen:(int)iLen
{
    int iCount, iDestCount;
    char buff[3];
    uint32_t temp;
    uint8_t tmpChar;
    
    NSMutableData *tmpData = [[NSMutableData alloc] initWithCapacity:32];
    
    for (iCount = 0, iDestCount=0; iCount < iLen; iCount+=2, iDestCount++) {
        buff[0] = sStr[iCount];
        buff[1] = sStr[iCount+1];
        buff[2] = '\0';
        sscanf(buff, "%x", &temp);
        tmpChar = temp;
        
        [tmpData appendBytes:&tmpChar length:sizeof(tmpChar)];
    }
    return tmpData;
}

#pragma mark - Private

- (void)_showErrMsg:(NSString *)msg
{
    UIAlertView *alert = [[UIAlertView alloc]
                          initWithTitle:@"错误"
                          message:msg
                          delegate:nil
                          cancelButtonTitle:@"确定"
                          otherButtonTitles:nil];
    [alert show];
}

@end
