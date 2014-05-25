//
//  LoginService.h
//  YaWtloginDemo
//
//  Created by gavinsu on 13-7-2.
//  Copyright (c) 2013年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WTLoginSDK/WloginSdk_v2.h>

///////////////////////////////////////////////////////////////////////////

//macro define
#define WTSharedService [LoginService sharedLoginService]

///////////////////////////////////////////////////////////////////////////

@interface LoginService : NSObject

@property (nonatomic, strong) NSArray           *sigArray;
@property (nonatomic, strong) WloginUserInfo    *userInfo;

/*
 * 获取全局LoginService对象
 */
+ (LoginService*)sharedLoginService;

/*
 * 初始化
 */
- (void)initialize;

@end
