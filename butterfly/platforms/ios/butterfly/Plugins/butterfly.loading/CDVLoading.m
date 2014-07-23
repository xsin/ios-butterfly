/*
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 "License"); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */

#import "CDVLoading.h"



@implementation CDVLoading




- (void)showloading:(CDVInvokedUrlCommand*)command
{
   
    UITabBarController* tabbar=(UITabBarController*)[self getCurrentRootViewController];
    UINavigationController* nav=(UINavigationController*)tabbar.selectedViewController;
    self.HUD = [MBProgressHUD showHUDAddedTo:nav.view animated:YES];

}


- (void)hideloading:(CDVInvokedUrlCommand *)command
{
    UITabBarController* tabbar=(UITabBarController*)[self getCurrentRootViewController];
    UINavigationController* nav=(UINavigationController*)tabbar.selectedViewController;
    [MBProgressHUD hideHUDForView:nav.view animated:YES];
//	[self.HUb hide:YES afterDelay:3];
}
-(UIViewController *)getCurrentRootViewController {
    
    
    UIViewController *result;
    
    
    // Try to find the root view controller programmically
    
    
    // Find the top window (that is not an alert view or other window)
    
    
    UIWindow *topWindow = [[UIApplication sharedApplication] keyWindow];
    
    
    if (topWindow.windowLevel != UIWindowLevelNormal)
    
    
    {
        
        
        NSArray *windows = [[UIApplication sharedApplication] windows];
        
        
        for(topWindow in windows)
        
        
        {
            
            
            if (topWindow.windowLevel == UIWindowLevelNormal)
            
            
            break;
            
            
        }
        
        
    }
    
    
    UIView *rootView = [[topWindow subviews] objectAtIndex:0];
    
    
    id nextResponder = [rootView nextResponder];
    
    
    if ([nextResponder isKindOfClass:[UIViewController class]])
    
    
    result = nextResponder;
    
    
    else if ([topWindow respondsToSelector:@selector(rootViewController)] && topWindow.rootViewController != nil)
    
    
    result = topWindow.rootViewController;
    
    
    else
    
    
    NSAssert(NO, @"ShareKit: Could not find a root view controller.  You can assign one manually by calling [[SHK currentHelper] setRootViewController:YOURROOTVIEWCONTROLLER].");
    
    
    return result;    
    
    
}

@end
