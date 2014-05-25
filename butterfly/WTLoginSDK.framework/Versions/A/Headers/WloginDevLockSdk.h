//
//  WloginDevLockSdk.h
//  WTLoginSDKForIOS
//
//  Created by krisyiliu on 13-12-10.
//
//

#import <Foundation/Foundation.h>
#import "DevLockCallBackProtocol.h"
#import "WloginTranCallbackProtocol.h"
#import "WloginSdk.h"
#import "WloginDevLocStatusInfo.h"


@interface WloginDevLockSdk : NSObject

/**** 初始化设备管理接口 ***********************/
/* 输入参数:
 * sdk          WTLogin的SDK，用于提取登陆态相关信息
 * dwAppid      业务APPID，比如手Q应该填16
 * dwSmdAppId   安平分配的APPID，用于配置短信内容，以及成本结算（业务需提供短信结算内码）
 * delegate     回调类
 *******************************************/
-(id)initWithDevLockSdk:(id)sdk andAppId:(uint32_t)dwAppid andSmsAppId:(uint32_t)dwSmdAppId andDelegate:(id)delegate;

// 重置设备锁流程; 开启一个新设备锁序列
// 当用户主动终止设备锁流程时，应调用此接口
-(void)resetDevLockProcess;

// 查询设备锁开通状况
-(DEVLOCK_RETURN_VALUES)queryDevLockStatus:(NSString *)userAccount;

// 关闭设备锁
-(DEVLOCK_RETURN_VALUES)closeDevLock:(NSString *)userAccount;

// 请求发送短信
-(DEVLOCK_RETURN_VALUES)askDevLockSms:(NSString *)userAccount;

// 验证短信并开通设备锁, code为用户输入的短信验证码
-(DEVLOCK_RETURN_VALUES)checkDevLockSms:(NSString *)userAccount andCode:(NSString*)code;

// 直接开通设备锁, 当在信任设备上操作时，可直接开启设备锁
// 返回失败的场景：
//  1 状态不正确：cAllow不为1
//  2 服务端返回不正确：没有返回tlv_Setup,或者tlv_SppKey
-(DEVLOCK_RETURN_VALUES)openDevLockDirectly:(NSString *)userAccount;

// 验证票据并开通设备锁, code为其它页面带来的安全中心派发的票据
-(DEVLOCK_RETURN_VALUES)checkDevLockSmsSig:(NSString *)userAccount andSmsSig:(NSData *)sig;

// 设置消息类型
// 三个参数类型分别为：查询状态、拉取短信、验证短信
// 手Q不用调用本接口
-(DEVLOCK_RETURN_VALUES)setMsgType:(uint16_t)wQueryStutus andGetMsg:(uint16_t)wGetMsg andCheckSms:(uint16_t)wCheckSms;

@end
