//
//  AppDelegate.m
//  butterfly
//
//  Created by jeakeyliang on 14-5-17.
//  Copyright (c) 2014年 jeakeyliang. All rights reserved.
//
#import "AppDelegate.h"
#import "HomeViewController.h"
#import "LoginService.h"
#import "MainViewController.h"
#import "QuickLoginViewController.h"

static BOOL bQuickLogin;

WloginSdk_v2 *g_loginSdk;

@interface AppDelegate ()
@property (strong, nonatomic) QuickLoginViewController *quickViewController;


@end


@implementation AppDelegate

- (NSString *)stringByEncodeUrl
{
    CFStringRef validCharsToBeEscaped = CFSTR("!*'();:@&=+$,/?%#[]");
    
    CFStringRef urlString = CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, (__bridge CFStringRef)(self), NULL, validCharsToBeEscaped, kCFStringEncodingUTF8);
    NSString *encodedUrl = [NSString stringWithString:(__bridge NSString *)urlString];
    CFRelease(urlString);
    
    return encodedUrl;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    
    LoggerSetViewerHost(NULL, (CFStringRef)@"10.66.39.28", (UInt32)54947);
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        g_loginSdk = [[WloginSdk_v2 alloc]initWithBasicInfo_v2:@"1.0.0.0"];
    });
    
    //    [g_loginSdk setLogLevel:5];
    //    [g_loginSdk setLanguage:WTLOGIN_LANGUAGE_ZH];
    
    //  [g_loginSdk setRemortServer:@"121.14.101.81" andPort:443];
    //    [g_loginSdk setRemortServer:@"121.14.80.26" andPort:443];
    //    [g_loginSdk setRemortServer:@"183.60.18.58" andPort:443];
    
    [WTSharedService initialize];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    
    self.quickViewController = [[QuickLoginViewController alloc] initWithNibName:nil bundle:nil];
    
    [self.window makeKeyAndVisible];
    
//    读取menu.json
    
    NSString *path = [[NSBundle mainBundle]  pathForResource:@"tab_bar" ofType:@"json"];
    NSData *data = [[NSData alloc] initWithContentsOfFile:path ];
    NSDictionary * jdata = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
    NSArray* tabs = [jdata objectForKey:@"tabs"];
    
    /*
     初始化viewcontroller
     */
    NSMutableArray *viewControllers = [[NSMutableArray alloc] init];
    
    for (NSUInteger i = 0; i < [tabs count]; i++){
        NSDictionary* tab=[tabs objectAtIndex:i];
        
        HomeViewController *vc = [[HomeViewController alloc] init];
        vc.main_title=[tab objectForKey:@"title"];
        vc.webview_url=[tab objectForKey:@"url"];
        
        UINavigationController *homeNav = [[UINavigationController alloc] initWithRootViewController:vc];
        
        [vc release];
        
        if (i==4) {
            MainViewController *uc = [[MainViewController alloc] init];
            uc.main_title=[tab objectForKey:@"title"];
            uc.webview_url=[tab objectForKey:@"url"];
            UINavigationController *ucNav = [[UINavigationController alloc] initWithRootViewController:uc];
            [uc release];
            UITabBarItem *ucNavItem = [[UITabBarItem alloc] initWithTitle:[tab objectForKey:@"title"] image:[UIImage imageNamed:[tab objectForKey:@"icon_normal"]] tag:i];
            
            [ucNavItem setFinishedSelectedImage:[UIImage imageNamed:[tab objectForKey:@"icon_normal"]] withFinishedUnselectedImage:[UIImage imageNamed:[tab objectForKey:@"icon_active"]]];
            uc.tabBarItem = ucNavItem;
            [ucNavItem release];
            homeNav = ucNav;
            
        }
        
        UITabBarItem *homeItem = [[UITabBarItem alloc] initWithTitle:[tab objectForKey:@"title"] image:[UIImage imageNamed:[tab objectForKey:@"icon_normal"]] tag:i];
//        UITabBarItem *homeItem = [[UITabBarItem alloc] initWithTabBarSystemItem:UITabBarSystemItemFavorites tag:i];
        [homeItem setFinishedSelectedImage:[UIImage imageNamed:[tab objectForKey:@"icon_normal"]] withFinishedUnselectedImage:[UIImage imageNamed:[tab objectForKey:@"icon_active"]]];
        vc.tabBarItem = homeItem;
        [homeItem release];
        
        [viewControllers addObject:homeNav];
        
    }
    
    
    
    // 创建UITabBarController实例
    UIImage* tabBarBackground = [UIImage imageNamed:[jdata objectForKey:@"bg"]];
    [[UITabBar appearance] setBackgroundImage:[tabBarBackground resizableImageWithCapInsets:UIEdgeInsetsZero]];
    
    UITabBarController *tabBarController = [[UITabBarController alloc] init];
    tabBarController.delegate = self; // 设置代理
    [tabBarController setViewControllers:viewControllers animated:YES];
    
    self.window.rootViewController = tabBarController;
    [tabBarController release];
    
    
    return YES;
}
#pragma mark - TabBarController Delegate
- (BOOL)tabBarController:(UITabBarController *)tabBarController
shouldSelectViewController:(UIViewController *)viewController
{
    
    return YES; // flag
} // 视图将要切换时调用， viewController为将要显示的控制器

- (void)tabBarController:(UITabBarController *)tabBarController
 didSelectViewController:(UIViewController *)viewController
{

} // 视图已经切换后调用， viewController 是已经显示的控制器

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    if (bQuickLogin) {
        bQuickLogin = NO;
        self.window.rootViewController = self.quickViewController;
        [self.quickViewController dataSourceArrayInit];
    } else {
//        MainViewController *mainVC = [[MainViewController alloc] initWithNibName:nil bundle:nil];
//        self.viewController = [[UINavigationController alloc] initWithRootViewController:mainVC];;
//        self.window.rootViewController = self.viewController;
    }
    
    [self.window makeKeyAndVisible];
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}
- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    bQuickLogin = YES;
    if ([url.absoluteString hasPrefix:@"mqqOpensdkQLogin"]) {
        self.window.rootViewController = self.quickViewController;
        [self.quickViewController dataSourceArrayInit];
        self.quickViewController.url = url;
        self.quickViewController.sourceApplication = sourceApplication;
    }
    if ([url.absoluteString hasPrefix:@"wtloginmqq"]) {
        self.window.rootViewController = self.quickViewController;
        [self.quickViewController dataSourceArrayInit];
        self.quickViewController.url = url;
        self.quickViewController.sourceApplication = sourceApplication;
    }
    
    return YES;
}

@end
