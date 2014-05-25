//
//  DevLockCallBackProtocol.h
//  WTLoginSDKForIOS
//
//  Created by krisyiliu on 13-12-9.
//
//
/***设备锁回调定义*****/

#import <Foundation/Foundation.h>
#import "WloginErrInfo.h"
#import "WloginDevLocStatusInfo.h"

typedef enum{
    WLOGIN_DEV_SECCESS       = 0,        // 操作成功
    WLOGIN_DEV_NETWORK_ERROR = 0x1,      // 网络错误
    // 状态错误：
    // 1. 可能是上一个调用流程没有结束
    // 2. 可能是查询操作queryDevLockStatus没有成功
    WLOGIN_DEV_STATE_ERROR   = 0x6,      // 状态错误：需要等待返回或调用resetDevLockProcess
    WLOGIN_DEV_ERROR_SERVER  = 0x10,     // server错误
    WLOGIN_DEV_ERROR_LOCAL   = 0x11,     // SDK错误
} DEVLOCK_RETURN_VALUES;

// 短信验证失败
#define WLOGIN_DEV_CODE_FAIL   (1209)

@protocol DevLockCallBackProtocol <NSObject>


/**** 执行设备锁状态查询的结果 *******************/
/* 后台查询成功；安平返回设备锁状态信息
 * dwSetup    是否开通设备锁的状态（0表示未开通，1表示开通）
 * detailInfo 设备锁在界面上的相关展示内容
 *******************************************/
-(void)onQueryStatusSucc:(uint32_t)dwSetup andDetail:(WloginDevLocStatusInfo *)detailInfo;

// 设备锁状态查询失败的回调
-(void)onQueryStatusFail:(DEVLOCK_RETURN_VALUES)result withError:(WloginErrInfo *)errorMsg;


/**** 成功发送短信的回调 **********************/
/* 后台发送短信成功后的回调
 * wAvailMsgCnt  当天剩余的免费短信条数
 * wTimeLimit    触发下次发送短信的时间
 *******************************************/
-(void)onAskSmsSucc:(uint16_t)wAvailMsgCnt andTimeLimit:(uint16_t)wTimeLimit;

// 发送短信失败的回调
// wAvailMsgCnt 和 wTimeLimit同时为0，表示服务端没有下发这2个数据（比如网络超时时)
-(void)onAskSmsFail:(DEVLOCK_RETURN_VALUES)result andAvailMsgCnt:(uint16_t)wAvailMsgCnt andTimeLimit:(uint16_t)wTimeLimit withError:(WloginErrInfo *)errorMsg;

// 成功开通设备锁(通过验证短信或者票据)的回调
-(void)onOpenDevLockSucc;

// 开通设备锁失败的回调
-(void)onOpenDevLockFail:(DEVLOCK_RETURN_VALUES)result withError:(WloginErrInfo *)errorMsg;

// 短信验证失败的回调
-(void)onCheckSmsCodeFailed:(WloginErrInfo *)errorMsg;

// 成功关闭设备锁的回调
-(void)onCloseDevLockSucc;

// 关闭设备锁操作失败的回调
-(void)onCloseDevLockFail:(DEVLOCK_RETURN_VALUES)result withError:(WloginErrInfo *)errorMsg;

// 设备锁相关操作失败的回调
-(void)onDevLockFail:(DEVLOCK_RETURN_VALUES)result withError:(WloginErrInfo *)errorMsg;


@end
