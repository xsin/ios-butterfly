//
//  WloginErrInfo.h
//  WTLoginSDKForIOS
//
//  Created by gavinsu on 13-3-21.
//
//

#import <Foundation/Foundation.h>

@interface WloginErrInfo : NSObject //错误信息
{
    NSString    *sErrorUserAccount;  //错误发生的帐号
    uint16_t    wErrorCode;         //错误码
    NSString*   sErrorTitle;        //标题
    NSString*   sErrorMsg;          //提示语
    uint16_t    wErrorAddType;      //附加信息的类型
    NSString*   sErrorAdd;          //附加信息
}

@property (assign)  uint16_t    wErrorCode;
@property (copy)    NSString*   sErrorTitle;
@property (copy)    NSString*   sErrorMsg;
@property (assign)  uint16_t    wErrorAddType;
@property (copy)    NSString*   sErrorAdd;
@property (copy)    NSString*   sErrorUserAccount;

@end
