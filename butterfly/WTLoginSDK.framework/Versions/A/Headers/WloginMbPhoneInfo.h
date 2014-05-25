//
//  WloginMbPhoneInfo.h
//  WTLoginSDKForIOS
//
//  Created by ellenliu on 13-12-17.
//
//

#import <Foundation/Foundation.h>

/********** 设备锁逻辑中，完成密保手机相关逻辑的信息 *********/
@interface WloginMbPhoneInfo : NSObject
{
    NSString*   sProtectInfo; // 设备登录保护介绍

    NSString*   sCountryCode; // 电话国际号
    NSString*   sPhoneNo;     // 手机号码
    uint32_t    dwMbPhoneStatus; // 1:可以用下行短信进行验证; 其他：不能用下行短信进行验证
    uint16_t    wAvailMsgCnt; // 当天剩余的免费短信条数
    uint16_t    wTimeLimit;   // 在wTimeLimit秒内，不允许下发短信
    
    uint16_t    wMbGuideType; // 1: 引导绑定密保手机; 2: 引导修改密保手机
    NSString*   sMbGuideMsg;  // 引导用户绑定/修改/删除密保的提示语
    uint16_t    wMbGuideInfoType;// wMbGuideInfoType=1时，GuideInfo为url
    NSString*   sMbGuideInfo;
    
    NSString*   sUnionVerifyUrl;
}

@property (copy)    NSString*   sProtectInfo;

@property (copy)    NSString*   sCountryCode;
@property (copy)    NSString*   sPhoneNo;
@property (assign)  uint32_t    dwMbPhoneStatus;
@property (assign)  uint16_t    wAvailMsgCnt;
@property (assign)  uint16_t    wTimeLimit;
@property (copy)  NSString*   sUnionVerifyUrl;

@property (assign)  uint16_t    wMbGuideType;
@property (copy)    NSString*   sMbGuideMsg;
@property (assign)  uint16_t    wMbGuideInfoType;
@property (copy)    NSString*   sMbGuideInfo;

@end
