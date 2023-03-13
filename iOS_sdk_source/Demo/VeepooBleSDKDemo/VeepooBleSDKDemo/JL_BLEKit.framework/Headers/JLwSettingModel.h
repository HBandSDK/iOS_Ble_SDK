//
//  LtvSettingModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(UInt8, WatchSettingFunc) {
    ///传感器功能
    WatchSettingFunc_SensorFunction = 0x01 ,
    ///久坐提醒
    WatchSettingFunc_SedentaryReminder = 0x02,
    ///连续测量心率
    WatchSettingFunc_ContinuousHeartRateMeasurement = 0x03,
    ///运动心率提醒
    WatchSettingFunc_ExerciseHeartRateReminder = 0x04,
    ///压力自动检测
    WatchSettingFunc_AutomaticPressureDetection = 0x05,
    ///睡眠检测
    WatchSettingFunc_SleepMonitoring = 0x06,
    ///跌倒检测
    WatchSettingFunc_FallDetection = 0x07,
    ///抬腕检测
    WatchSettingFunc_WristLiftDetection = 0x08,
    ///个人信息
    WatchSettingFunc_PersonInfo  = 0x09,
    /// 蓝牙断开提醒
    WatchSettingFunc_DisconnectReminder = 0xA,
    /// 血氧测量提醒
    WatchSettingFunc_OxygenSturation = 0x0B,
    /// 紧急联系人
    WatchSettingFunc_EmergencyContact = 0x0C
};

///提醒模式
typedef NS_ENUM(UInt8, WatchRemindType) {
    /// 亮屏
    WatchRemind_BrightScreen = 0x00,
    ///震动
    WatchRemind_Shake        = 0x01,
    /// 打电话（抬腕不支持该提示）
    WatchRemind_Call         = 0x02
};

///连续测量心率模式
typedef NS_ENUM(UInt8, WatchConsequentType) {
    //智能
    WatchConsequent_Intelligent = 0x00,
    //实时
    WatchConsequent_realTime = 0x01
};

/// 连续血氧测量模式
typedef NS_ENUM(UInt8,WatchOxygenMsmType){
    //智能
    WatchOxygenMsm_Intelligent = 0x00,
    //定时
    WatchOxygenMsm_runTime = 0x01
};

///监察开关类型
typedef NS_ENUM(UInt8, WatchSwitchType) {
    ///关闭
    WatchSwitchType_Close    = 0x00,
    ///全天开启
    WatchSwitchType_AllDay   = 0x01,
    ///自定义时间
    WatchSwitchType_Customer = 0x02,
};

@interface WatchTimer : NSObject
/// 时
@property(nonatomic,assign,readonly)UInt8 hour;
/// 分
@property(nonatomic,assign,readonly)UInt8 min;

-(instancetype _Nonnull)initWithData:(NSData *_Nonnull)data;

-(instancetype _Nonnull)initWith:(uint8_t)h Min:(uint8_t)m;

@end

NS_ASSUME_NONNULL_BEGIN

@interface JLwSettingModel : NSObject
@property(nonatomic,assign)uint8_t length;
@property(nonatomic,assign)WatchSettingFunc type;
@property(nonatomic,strong)NSData *value;

/// 设备UUID
@property(nonatomic,strong)NSString *deviceID;


-(NSData *)beData;



@end

NS_ASSUME_NONNULL_END
