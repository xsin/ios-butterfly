//
//  WloginDevLocStatusInfo.h
//  WTLoginSDKForIOS
//
//  Created by ellenliu on 13-12-13.
//
//

#import <Foundation/Foundation.h>

@interface WloginDevLocStatusInfo : NSObject
{
    uint32_t    dwDevSetup;   // 设备登录保护是否开通(0未开通、1开通)
    
    char        cAllowSet;    // 是否允许不验证手机短信(0不可以、1可以)
    
    NSString*   sProtectInfo; // 设备登录保护介绍
    NSString*   sWarnTitle;   // 提示语标题
    NSString*   sWarnMsg;     // 如果length=0，不需要向用户弹出提示; 在开启设备登录保护时，提示内容
    uint16_t    wWarnInfoType;// usWarningInfoType=1时，WarnInfo为url
    NSString*   sWarnInfo;
    
    NSString*   sCountryCode; // 电话国际号
    NSString*   sPhoneNo;     // 手机号码
    uint32_t    dwMbPhoneStatus; // 1:可以用下行短信进行验证; 其他：不能用下行短信进行验证
    uint16_t    wAvailMsgCnt; // 当天剩余的免费短信条数
    uint16_t    wTimeLimit;   // 在wTimeLimit秒内，不允许下发短信

    uint16_t    wMbGuideType; // 1: 引导绑定密保手机; 2: 引导修改密保手机
    NSString*   sMbGuideMsg;  // 引导用户绑定/修改/删除密保的提示语
    uint16_t    wMbGuideInfoType;// wMbGuideInfoType=1时，GuideInfo为url
    NSString*   sMbGuideInfo;
}

@property (assign)  uint32_t    dwDevSetup;
@property (assign)  char        cAllowSet;
@property (copy)    NSString*   sProtectInfo;
@property (copy)    NSString*   sWarnTitle;
@property (copy)    NSString*   sWarnMsg;
@property (assign)  uint16_t    wWarnInfoType;
@property (copy)    NSString*   sWarnInfo;

@property (copy)    NSString*   sCountryCode;
@property (copy)    NSString*   sPhoneNo;
@property (assign)  uint32_t    dwMbPhoneStatus;
@property (assign)  uint16_t    wAvailMsgCnt;
@property (assign)  uint16_t    wTimeLimit;

@property (assign)  uint16_t    wMbGuideType;
@property (copy)    NSString*   sMbGuideMsg;
@property (assign)  uint16_t    wMbGuideInfoType;
@property (copy)    NSString*   sMbGuideInfo;

@end
