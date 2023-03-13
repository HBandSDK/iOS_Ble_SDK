//
//  JL_BinCharge.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_ScanSetting) {
    JL_ScanTimeout     = 0x00, //超时结束
    JL_ScanInterrupt   = 0x01, //打断结束
    JL_ScanFail        = 0x02, //开启扫描失败
    JL_Scaning         = 0x03, //正在扫描
};

typedef NS_ENUM(UInt8, JL_ReverberationFunType) {
    JL_ReverberationAndDynamicType       = 0x00, //支持混响和动态限幅器
    JL_OnlyReverberationType             = 0x01, //仅支持混响
    JL_OnlyDynamicLimiterType            = 0x02, //仅支持动态限幅器
};

typedef void(^JL_CMD_VALUE_BK)(uint32_t value);
typedef void(^JL_LOW_DELAY_BK)(uint16_t mtu, uint32_t delay);

@interface JL_BinChargeManager : JL_FunctionBaseManager

#pragma mark ---> 通知固件App的信息
// @param flag  未知
-(void)cmdSetAppInfo:(uint8_t)flag;

#pragma mark ---> 设置通讯MTU
// @param mtu app请求mtu⼤⼩
// @param result 实际设置的Mtu⼤⼩
-(void)cmdSetMTU:(uint16_t)mtu Result:(JL_CMD_VALUE_BK __nullable)result;

#pragma mark ---> 开启蓝⽛扫描
// @param timeout 超时时间
// @param result  0:成功 1:失败
-(void)cmdBTScanStartTimeout:(uint16_t)timeout Result:(JL_CMD_VALUE_BK __nullable)result;

#pragma mark ---> 推送蓝⽛扫描结果
// 返回【蓝⽛数据结构】数组
// @see JLBTModel
extern NSString *kJL_MANAGER_BT_LIST_RESULT;

#pragma mark ---> 停⽌蓝⽛扫描（APP-->固件）
// @param reason  0：超时结束  1：打断结束  2：开启扫描失败  3：正在扫描
// @param result  0：成功  1：失败
-(void)cmdBTScanStopReason:(JL_ScanSetting)reason Result:(JL_CMD_VALUE_BK __nullable)result;

#pragma mark ---> 停⽌蓝⽛扫描（固件-->APP）
// 0：超时结束  1：打断结束  2：开启扫描失败  3：正在扫描
extern NSString *kJL_MANAGER_BT_SCAN_STOP_NOTE;

#pragma mark ---> 通知固件连接指定的蓝⽛设备
// @param addr 蓝⽛设备地址【设置0x00 00 00 00 00 00 则是断开外设的连接】
// @param result  0：成功  1：失败
-(void)cmdBTConnectAddress:(NSData*)addr Result:(JL_CMD_VALUE_BK __nullable)result;

extern NSString *kJL_MANAGER_ID3_Title;
extern NSString *kJL_MANAGER_ID3_Artist;
extern NSString *kJL_MANAGER_ID3_Album;
extern NSString *kJL_MANAGER_ID3_Time;

#pragma mark ---> 主动设置ID3播放状态
-(void)setID3_Status:(uint8_t)st;

#pragma mark ---> ID3 播放/暂停
-(void)cmdID3_PP;

#pragma mark ---> ID3 上一曲
-(void)cmdID3_Before;

#pragma mark ---> ID3 下一曲
-(void)cmdID3_Next;

#pragma mark ---> ID3 开启/暂停 音乐信息推送
-(void)cmdID3_PushEnable:(BOOL)enable;

#pragma mark ---> 设置高低音 [-12,+12]
-(void)cmdSetLowPitch:(int)p_low HighPitch:(int)p_high;

#pragma mark ---> 设置混响值[深度和强度][0,100]、限幅值[-60,0]
-(void)cmdSetReverberation:(int)depthValue
            IntensityValue:(int)intensityValue
       DynamicLimiterValue:(int)dynamicLimiterValue
          SwtichReverState:(int)reverOn
                   FunType:(JL_ReverberationFunType)type;

#pragma mark ---> 获取低延时参数
-(void)cmdGetLowDelay:(JL_LOW_DELAY_BK __nullable)result;


@end

NS_ASSUME_NONNULL_END
