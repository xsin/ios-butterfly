//
//  WloginProtocolBuff.h
//  WloginIOSPlatformSDK
//
//  Created by jiezhao on 11-8-19.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WTLoginLog.h"


#ifndef APPAND_UIN32_DATA
#define APPAND_UIN32_DATA(__para) do{ \
uint32_t __paraNet = htonl(__para); \
[buff appendBytes:&__paraNet length:sizeof(uint32_t)];\
TRACE_LOG(@#__para" = %u", __para);\
}while(0)
#endif

#ifndef APPAND_UIN16_DATA
#define APPAND_UIN16_DATA(__para) do{ \
uint16_t __paraNet = htons(__para); \
[buff appendBytes:&__paraNet length:sizeof(uint16_t)];\
TRACE_LOG(@#__para" = %u", __para);\
}while(0)
#endif

#ifndef APPAND_UIN8_DATA
#define APPAND_UIN8_DATA(__para) do{ \
uint8_t __paraNet = __para;\
[buff appendBytes:&__paraNet length:sizeof(uint8_t)];\
TRACE_LOG(@#__para" = %u", __para);\
}while(0)
#endif

#ifndef APPAND_UIN64_DATA
#define APPAND_UIN64_DATA(__para) do{ \
uint64_t __paraNet = htonll(__para);\
[buff appendBytes:&__paraNet length:sizeof(uint64_t)];\
TRACE_LOG(@#__para" = %llu", __para);\
}while(0)
#endif

@protocol WloginProtocolBuff <NSObject>


-(int)decode:(char **)buff andBuffLen:(int *)piLen;

-(int)encode:(NSMutableData *)buff;


@end
