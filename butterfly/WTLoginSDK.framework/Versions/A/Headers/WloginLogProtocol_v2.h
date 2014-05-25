//
//  WloginLogProtocol_v2.h
//  WTLoginSDKForIOS
//
//  Created by jiezhao on 12-11-15.
//
//

#import <Foundation/Foundation.h>

@protocol WloginLogProtocol_v2 <NSObject>

- (void)log:(const char *)file func:(const char *)func line:(int)line  msg:(NSString *)msg;

- (void)loginInfo:(NSMutableDictionary *)infoDic;

@end
