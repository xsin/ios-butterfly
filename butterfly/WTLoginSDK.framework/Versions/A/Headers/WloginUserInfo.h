//
//  WloginUserInfo.h
//  WloginIOSPlatformSDK
//
//  Created by jiezhao on 11-8-18.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface WloginUserInfo : NSObject <NSCoding>{
    uint32_t dwUserUin;             //用户QQ号码
    NSString *sUserMainAccount;     //主显帐号
    
    uint16_t wFaceId;               //头像id，使用逻辑可以登录oidb.server.com上查看
    uint8_t cAge;                   //年龄
    uint8_t cGender;                //性别，0 未知， 1 男， 2 女 
    NSString *sNickName;            //昵称
    
    NSString *sFaceUrl;             //自定义头像URL
    
    NSData   *quickLoginData;       //用于快速登录的数据
}

@property (assign) uint32_t dwUserUin;
@property (retain) NSString *sUserMainAccount;

@property (assign) uint16_t wFaceId;
@property (assign) uint8_t cAge;
@property (assign) uint8_t cGender;
@property (retain) NSString *sNickName;

@property (copy) NSString *sFaceUrl;
@property (retain) NSData *quickLoginData;


-(WloginUserInfo *)userinfo;

//与快速登录，通过剪贴板读写数据有关.begin.
+ (NSArray *)readUserInfoListFromPasteboard:(NSData *)guid inData:(NSData *)inData;
+ (int)insertUserInfoToPasteboard:(WloginUserInfo *)userInfo guid:(NSData *)guid key:(NSData *)key inData:(NSData *)inData outData:(NSMutableData *)outData;
+ (int)deleteUserInfoFromPasteboard:(uint32_t)dwUin          guid:(NSData *)guid key:(NSData *)key inData:(NSData *)inData outData:(NSMutableData *)outData;
//与快速登录，通过剪贴板读写数据有关.end.

@end

