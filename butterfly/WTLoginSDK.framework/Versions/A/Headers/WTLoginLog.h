//
//  WTLoginLog.h
//  WTLoginSDKForIOS
//
//  Created by jiezhao on 11-9-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <pthread.h>
#import <libgen.h>

#import "WtloginPlatformInfo.h"
#import "WloginLogProtocol_v2.h"
#import "ErrorLogReport.h"

#ifndef __WTLOGIN_LOG_H__
#define __WTLOGIN_LOG_H__

#define WTLOGIN_ERRREPORT

enum {
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_TRACE = 4,
};

extern int wtlogin_login_level;
extern int wtlogin_innerlog_ctl; // 内部LOG控制
#define LOGIN_DETAIL_INFO(__dic) do { \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate loginInfo:__dic]; \
    }\
} while (0)

#define ERR_REPORT [ErrorLogReport singleton]

//FOECE_LOG
#ifdef WTLOGIN_ERRREPORT


extern struct timeval stLastTime;
extern struct timeval stCurTime;
extern long long ddwDiff;

#define  TIME_LOG(fmt, args...) do { \
gettimeofday(&stCurTime,NULL); \
ddwDiff=(((long long)(stCurTime.tv_sec-stLastTime.tv_sec)*1000+(long long)(stCurTime.tv_usec-stLastTime.tv_usec)/1000));\
NSLog(@"[%s][%d]%s costtime:%lld" , basename(__FILE__), __LINE__, __FUNCTION__, ddwDiff); \
stLastTime=stCurTime;\
} while (0)


#define FOECE_LOG(fmt, args...) do { \
    if( wtlogin_innerlog_ctl ) [ERR_REPORT writeLog:pthread_mach_thread_np(pthread_self()) file:__FILE__ line:__LINE__ func:__func__ msg:fmt, ## args]; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#else

#define FOECE_LOG(fmt, args...) do { \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#endif

//ERROR_LOG
#ifdef WTLOGIN_ERRREPORT

#define ERROR_LOG(fmt, args...) do { \
    if( wtlogin_innerlog_ctl ) [ERR_REPORT writeLog:pthread_mach_thread_np(pthread_self()) file:__FILE__ line:__LINE__ func:__func__ msg:fmt, ## args]; \
    if(LOG_LEVEL_ERROR > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#else

#define ERROR_LOG(fmt, args...) do { \
    if(LOG_LEVEL_ERROR > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#endif

//WARN_LOG
#ifdef WTLOGIN_ERRREPORT

#define WARN_LOG(fmt, args...) do { \
    if( wtlogin_innerlog_ctl ) [ERR_REPORT writeLog:pthread_mach_thread_np(pthread_self()) file:__FILE__ line:__LINE__ func:__func__ msg:fmt, ## args]; \
    if(LOG_LEVEL_WARN > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#else

#define WARN_LOG(fmt, args...) do { \
    if(LOG_LEVEL_WARN > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#endif

//INFO_LOG
#ifdef WTLOGIN_ERRREPORT

#define INFO_LOG(fmt, args...) do { \
    if( wtlogin_innerlog_ctl ) [ERR_REPORT writeLog:pthread_mach_thread_np(pthread_self()) file:__FILE__ line:__LINE__ func:__func__ msg:fmt, ## args]; \
    if(LOG_LEVEL_INFO > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#else

#define INFO_LOG(fmt, args...) do { \
    if(LOG_LEVEL_INFO > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#endif

//TRACE_LOG
#ifdef WTLOGIN_ERRREPORT

#define TRACE_LOG(fmt, args...) do { \
    if( wtlogin_innerlog_ctl ) [ERR_REPORT writeLog:pthread_mach_thread_np(pthread_self()) file:__FILE__ line:__LINE__ func:__func__ msg:fmt, ## args]; \
    if(LOG_LEVEL_TRACE > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)

#else

#define TRACE_LOG(fmt, args...) do { \
    if(LOG_LEVEL_TRACE > wtlogin_login_level) break; \
    if (wtloginLogDelegate) { \
        [wtloginLogDelegate log:__FILE__ func:__FUNCTION__ line:__LINE__ msg:[NSString stringWithFormat:fmt, ## args]]; \
    }\
    else { \
        NSLog(@"[%s][%d]%s " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ## args); \
    }\
} while (0)


#endif


#endif
