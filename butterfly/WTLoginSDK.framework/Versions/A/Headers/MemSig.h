//
//  MemSig.h
//  WTLoginSDKForIOS
//
//  Created by jiezhao on 11-8-23.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface MemSig : NSObject <NSCoding>{
    NSString *sigName;
    uint32_t dwAppid;
    NSData *sig;
    NSData *sigKey;
    
    // time
    uint32_t dwSigTime;
    // validate time
    uint32_t dwValidTime;
    // description
    NSString *sigDesc;
}

@property (retain, nonatomic)  NSData *sig;
@property (retain, nonatomic)  NSData *sigKey;
@property (copy, nonatomic)  NSString *sigName;
@property (assign, nonatomic)  uint32_t dwAppid;

@property (copy, nonatomic)  NSString *sigDesc;
@property (assign, nonatomic)  uint32_t dwSigTime;
@property (assign, nonatomic)  uint32_t dwValidTime;

@end
