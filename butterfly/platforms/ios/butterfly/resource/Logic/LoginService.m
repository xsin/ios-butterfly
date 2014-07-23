//
//  LoginService.m
//  YaWtloginDemo
//
//  Created by gavinsu on 13-7-2.
//  Copyright (c) 2013年 tencent. All rights reserved.
//

#import "LoginService.h"

@implementation LoginService

/*
 * 获取全局LoginService对象
 */
+ (LoginService*)sharedLoginService
{
    static LoginService *s_loginservice = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        s_loginservice = [[LoginService alloc] init];
    });
    return s_loginservice;
}

- (void)initialize
{
}

- (void)dealloc
{
    _sigArray = nil;
    _userInfo = nil;
}

@end
