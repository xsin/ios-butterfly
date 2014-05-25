//
//  WloginEnum.h
//  WTLoginSDKForIOS
//
//  Created by gavinsu on 13-9-23.
//
//

#ifndef WTLoginSDKForIOS_WloginEnum_h
#define WTLoginSDKForIOS_WloginEnum_h

//本文件的目的：把公共的enum的定义都集中到这里

//提示语的语言类型
typedef enum{
    WTLOGIN_LANGUAGE_UNSET = 0,           //未设置
    WTLOGIN_LANGUAGE_ZHCN = 2052,         //简体中文
    WTLOGIN_LANGUAGE_ZHTW = 1028,         //繁体中文
    WTLOGIN_LANGUAGE_EN   = 1033,         //英文
} WTLOGIN_LANGUAGE;

typedef enum{
    WTLOGIN_QUICKLOGIN_CONFORM = 1,       //确认使用快速登录
    WTLOGIN_QUICKLOGIN_CANCEL  = 2,       //取消使用快速登录
} WTLOGIN_QUICKLOGIN_ACTION;

typedef enum{
    WTLOGIN_QUICKLOGIN_USE_MOBILEQQ = 1,  //使用手Q快速登录
    WTLOGIN_QUICKLOGIN_USE_WEIXIN   = 2,  //使用微信快速登录
} WTLOGIN_QUICKLOGIN_USEAPP;

#endif
