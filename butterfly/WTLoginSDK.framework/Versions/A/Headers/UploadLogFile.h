//
//  UploadLogFile.h
//  WTLoginSDKForIOS
//
//  Created by gavinsu on 13-4-2.
//
//

#import <Foundation/Foundation.h>
#import "MemSig.h"

#define MAX_LOG_FILE_SIZE (1024 * 1024)    //每个日志文件的最大大小，1MB

typedef enum {
     DATA_TYPE_JSON = 0      //json格式
    ,DATA_TYPE_FILE = 1      //文件格式
} DATA_TYPE;


@interface UploadLogFile : NSObject
{
    
@private
    NSMutableURLRequest* urlRequest_;
    
}

@property (nonatomic, retain) NSMutableURLRequest* urlRequest_;

//打包
-(NSData *)makeLogPkg:(DATA_TYPE)dataType data:(NSData *)data uin:(uint32_t)uin appid:(uint32_t)appid st:(MemSig*)st createTime:(time_t)createTime;

//上传
-(void)uploadLogPkg:(NSData *)data delegate:(id)target succSel:(SEL)succSelector faildSel:(SEL)faildSelector;

@end
