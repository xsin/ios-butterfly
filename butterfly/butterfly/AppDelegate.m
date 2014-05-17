//
//  AppDelegate.m
//  butterfly
//
//  Created by jeakeyliang on 14-5-17.
//  Copyright (c) 2014年 jeakeyliang. All rights reserved.
//

#import "AppDelegate.h"
#import "HomeViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
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

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
