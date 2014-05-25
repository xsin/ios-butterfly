//
//  WloginDevLocStatusInfo.m
//  WTLoginSDKForIOS
//
//  Created by ellenliu on 13-12-13.
//
//

#import "WloginDevLocStatusInfo.h"

@implementation WloginDevLocStatusInfo

@synthesize dwDevSetup;

@synthesize cAllowSet;

@synthesize sProtectInfo;
@synthesize sWarnTitle;
@synthesize sWarnMsg;
@synthesize wWarnInfoType;
@synthesize sWarnInfo;

@synthesize sCountryCode;
@synthesize sPhoneNo;
@synthesize dwMbPhoneStatus;
@synthesize wAvailMsgCnt;
@synthesize wTimeLimit;

@synthesize wMbGuideType;
@synthesize sMbGuideMsg;
@synthesize wMbGuideInfoType;
@synthesize sMbGuideInfo;

- (void)dealloc
{
    [sProtectInfo release];
    sProtectInfo = nil;
    
    [sWarnTitle release];
    sWarnTitle = nil;
    
    [sWarnMsg release];
    sWarnMsg = nil;
    
    [sWarnInfo release];
    sWarnInfo = nil;
    
    [sCountryCode release];
    sCountryCode = nil;
    
    [sPhoneNo release];
    sPhoneNo = nil;
    
    [sMbGuideMsg release];
    sMbGuideMsg = nil;
    
    [sMbGuideInfo release];
    sMbGuideInfo = nil;
    
    [super dealloc];
}

@end
