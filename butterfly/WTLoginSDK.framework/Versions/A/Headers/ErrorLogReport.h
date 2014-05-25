//
//  ErrorLogReport.h
//  WnsSDK
//
//  Created by 猛 闫 on 12-11-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WloginSdk.h"

/**
 * WNS Logger类
 */
@interface ErrorLogReport : NSObject
{
    NSString*       userAccount;
    uint32_t        appid;
    WloginSdk*      wloginSdk;
    
    NSString        *_logFile;
    NSFileHandle    *_fileHandle;
    NSString        *_logDate;
    
    NSMutableArray  *_caches;       // 缓存的日志信息
    NSTimer         *_timer;        // 指定的时间也异步写一次log
    
    NSLock          *_lock;
    BOOL            _canSaveLogOpt; // 当前是否可以异步写文件
}

@property (nonatomic, retain) NSString*        userAccount;
@property (nonatomic, assign) uint32_t         appid;
@property (nonatomic, retain) WloginSdk*       wloginSdk;

@property(nonatomic, retain)    NSString        *logFile;
@property(nonatomic, retain)    NSMutableArray  *caches;

//单例模式
+ (ErrorLogReport*)singleton;

//写log
- (void)writeLog:(uint32_t)thread file:(const char *)file line:(int)line func:(const char *)func msg:(NSString *)fmt, ...;
- (void)writeLog:(uint32_t)thread file:(const char *)file line:(int)line func:(const char *)func msg:(NSString *)fmt arguments:(va_list)args;

//log写磁盘
-(int)syncLog;

//上传log文件
////指定日期，如@"20130401"
-(int)uploadLogWithDay:(NSString *)day;
////指定起止时间，时间格式为UNIX时间戳
-(int)uploadLogFromDay:(time_t)fromDay toDay:(time_t)toDay;
////上传今日的log
-(int)uploadLog;

@end



