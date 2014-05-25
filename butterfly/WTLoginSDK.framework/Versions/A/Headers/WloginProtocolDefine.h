//
//  WloginProtocolDefine.h
//  WloginIOSPlatformSDK
//
//  Created by jiezhao on 11-8-19.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef  __WLOGIN_PROTOCOL_DEFINE_H__
#define  __WLOGIN_PROTOCOL_DEFINE_H__


#define STX     0x2
#define ETX     0x3


typedef enum{
    PROTOCOL_SECCESS = 0,              //成功
    PROTOCOL_NETWORK_ERROR = 0x1,       //网络错误
    PROTOCOL_NEED_CHALLENGE = 0x3,      //需要挑战
    PROTOCOL_NOT_CONNETED = 0x5,       //没有连接
    PROTOCOL_NEED_PIC = 0x2,           //需要验证码 或 验证码错误重新输入
    PROTOCOL_NEED_SMS_CODE = 0xa0,           //需要短信验证码
    PROTOCOL_SMS_CODE_ERROR = 0xa3,           //短信验证码错误重新输入
    PROTOCOL_INFO_ERROR = 0x4,          //没有足够的信息
    PROTOCOL_PKG_ERROR = 0x6,          //回包错误
    
    PROTOCOL_INFO_TIP = 0x12,      //错误，不需要终断流程，展示错误提示
    PROTOCOL_ERROR_TIP = 0x13,      //登录错误，终断流程，展示错误提示
    PROTOCOL_REJECTED_TIP = 0x10,      //登录错误，终断流程，展示错误提示，重新输入密码
    
    PROTOCOL_TOO_LARGE_PKG = 0x11,     //包长过长
    PROTOCOL_CLT_RETRY = 0x100,      // 客户端重试
} RETURN_VALUES_P;

typedef enum{
    //正常流程
    SERVER_RETURN_SECCESS = 0,              //成功
    SERVER_RETURN_NEED_PIC = 0x2,           //需要验证码 或 验证码错误重新输入
    SERVER_RETURN_NEED_SMS_CODE = 0xa0,     //需要短信验证码
    SERVER_RETURN_SMS_CODE_ERROR = 0xa3,     //短信验证码错误重新输入
    SERVER_RETURN_NEED_CHALLENGE = 0x3,      //需要挑战
    
    //错误，需要提示用户，不需要终断流程
    SERVER_RETURN_SMS_CODE_FEQ_LMT = 0xa1,  //短信频率限制
    SERVER_RETURN_SMS_CODE_GET_FLD = 0xa2,  //短信获取失败
    
    //错误，需要提示用户，需要终断流程
    SERVER_RETURN_INFO_ERROR = 0x6,          //没有足够的信息
    SERVER_RETURN_ILLEGAL_REQ = 0x9,         //非法请求，或者请求超时
    SERVER_RETURN_OPERATE_TIMEOUT = 0x9b,    //请求超时
    
    SERVER_RETURN_TIME_OUT = 0x9a,          //后端系统超时
    /*这类错误有很多，这里没有列全，default处理*/
    
    //错误，需要提示用户，需要终断流程，需要用户重新输入密码
    SERVER_RETURN_PWD_ERROR = 0x1,       //密码错误
    SERVER_RETURN_ACCOUNT_ERROR = 0x5,  //name帐号错误或非法
    SERVER_RETURN_A2_TIME_OUT = 0xf,        //A2超期
    SERVER_RETURN_TGTGT_TIME_OUT = 0x10,        //A1超期
    SERVER_RETURN_UIN_ERROR = 0x12,        //号码不存在
    SERVER_RETURN_NAME_UIN_CHGE = 0xb0,        //name帐号绑定关系变化
    SERVER_RETURN_NEED_NAME = 0xc,        //必须用name帐号登录
    SERVER_RETURN_NOT_CFT = 0x2b,        //非财富通帐号
    SERVER_RETURN_REJECTED_CFT = 0x2c,        //不允许财富通帐号登录
    SERVER_RETURN_ECDH_DISABLE = 0xb4,   // 禁用ECDH
    
} SERVER_RETURN_VALUE;

#endif

