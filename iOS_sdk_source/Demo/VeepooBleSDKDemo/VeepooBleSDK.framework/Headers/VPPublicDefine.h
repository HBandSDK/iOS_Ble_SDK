//
//  VPPublicDefine.h
//  VPBleSdk
//
//  Created by 张冲 on 17/1/12.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPeripheralModel.h"
#ifndef __OPTIMIZE__
# define NSLog(...) NSLog(__VA_ARGS__)
#else
# define NSLog(...)
#endif

//SDK版本号
FOUNDATION_EXPORT NSString * const VeepooBleSDKVersion;

//System Bluetooth status change
//系统蓝牙状态改变
typedef NS_ENUM (NSInteger, VPCentralManagerState) {
    VPCentralManagerStateUnknown = 0,
    VPCentralManagerStateResetting,
    VPCentralManagerStateUnsupported,
    VPCentralManagerStateUnauthorized,
    VPCentralManagerStatePoweredOff,//系统蓝牙关闭
    VPCentralManagerStatePoweredOn,//系统蓝牙开启
};

//Bluetooth connection status change
//蓝牙连接状态改变
typedef NS_ENUM (NSInteger, VPDeviceConnectState) {
    VPDeviceConnectStateDisConnect = 0,//断开连接
    VPDeviceConnectStateConnect,//已经连接
    VPDeviceConnectStateVerifyPasswordSuccess,//验证密码成功
    VPDeviceConnectStateVerifyPasswordFailure,//验证密码失败
    VPDeviceDiscoverNewUpdateFirm,//Discover new firmware that can be upgraded 发现可以升级的新固件
};

typedef NS_ENUM(NSInteger, DeviceConnectState) {
    BlePoweredOff = 0,//蓝牙没有打开
    BleConnecting = 1,//蓝牙连接中
    BleConnectSuccess = 2, //蓝牙连接成功
    BleConnectFailed = 3, //蓝牙连接失败
    BleVerifyPasswordSuccess = 4,//验证密码成功
    BleVerifyPasswordFailure = 5,//验证密码失败
};

typedef NS_ENUM(NSInteger, PasswordSynchronTpye) {
    PasswordValidationFailed = 0,//密码验证失败
    PasswordValidationSuccess = 1,//密码验证成功
    PasswordResetFailed = 2, //重置密码失败
    PasswordResetSuccess = 3, //重置密码成功
    PasswordReadFailed = 4,//密码读取失败
    PasswordReadSuccess = 5,//密码读取成功
    PasswordValidationAllSuccess = 6,//密码验证成功和时间同步都成功，一般会返回这个
};

typedef NS_ENUM(NSInteger, SynchronousPasswordType) {
    VerifyPasswordType = 0,//发送密码
    SettingPasswordType = 1,//设置密码
};

typedef NS_ENUM(NSInteger, DeviceDFUState) {
    DeviceDFUFileNotExist = 0, //升级文件不存在
    DeviceDFUStart,//开始升级
    DeviceDFUUpdating,//升级中
    DeviceDFUSuccess,//升级成功
    DeviceDFUFailure,//升级失败
};

//接收扫描到的设备
typedef void(^ReceiveScanningDevice)(VPPeripheralModel *peripheralModel);
//接收扫描到的设备
typedef void(^DeviceConnectBlock)(DeviceConnectState connectState);

typedef void(^SynchronizationResultBlock)(PasswordSynchronTpye result);

typedef void(^VPReadRSSIBlock)(NSInteger rssiValue);

typedef NS_ENUM(NSInteger, VPReadDeviceBaseDataState) {//读取设备基本数据的状态变化
    VPReadDeviceBaseDataStart = 0, //开始读取数据
    VPReadDeviceBaseDataReading = 1, //读取中
    VPReadDeviceBaseDataComplete,//读取全部完成
    VPReadDeviceBaseDataInvalid,//SDK不提供使用
};

#pragma mark - 基本功能设置的状态
typedef NS_ENUM(NSInteger, VPSettingMessageSwitchType) {//关于来电提醒的类型选择
    VPSettingUnkonw = 1, //未知类型
    VPSettingCall = 2, //来电设置
    VPSettingSMS,//短信设置
    VPSettingWechat,
    VPSettingQQ,
    VPSettingSina,
    VPSettingFaceBook,
    VPSettingTwitter,
    VPSettingFlickr,
    VPSettingLinkedln,
    VPSettingwhatsapp,
    VPSettingLine,
    VPSettingInstagram,
    VPSettingSnapchat,
    VPSettingSkype,
    VPSettingGMail,
    VPSettingDingTalk,
    VPSettingWeChatWork,
    VPSettingOtherPlatform = 19,
    // 第二包
    VPSettingOtherTikTok = 20,
    VPSettingOtherTelegram = 21,
    VPSettingOtherConnected2 = 22,
    VPSettingKakaoTalk,
    VPSettingJingYou, // 警右 APP
    VPSettingAll = 100,//设置所有, 读取的使用不能使用这个
};

typedef NS_ENUM(NSInteger, VPSettingBaseFunctionSwitchType) {//关于来电提醒的类型选择
    VPSettingRaiseHand = 0, //设置抬手亮屏幕
    VPSettingDeviceLose = 1, //设备防丢失
    VPSettingWearDetection = 2,//佩戴检测
    VPSettingMetric = 3,//设置公英制
    VPSettingTimeFormat,//设置时间制式
    VPSettingAutomaticHRTest,//设置自动心率检测
    VPSettingAutomaticBPTest,//设置自动血压检测
    VPSettingExercise,//设置运动量过量提醒，主要用在耳机项目上
    VPSettingVoiceAnnouncements,//心率、血压、血氧等语音播报，主要用在耳机项目上
    VPSettingSearchPhoneInterFace,//设置搜索手机界面是否在手环上显示
    VPSettingStopwatchInterFace,//设置秒表界面是否在手环上显示
    VPSettingOxygenLowerRemind,//设置血氧过低后警告
    VPSettingLedGrade,//设置Led灯的等级，关闭是黑人档位，开始是正常肤色档位
    VPSettingAutomaticHRVTest,//设置HRV夜间自动检测开关是否开启
    VPSettingAutoAnswer,//设置来电自动接听开关，耳机有效
    VPSettingDisconnectRemind,//设置断链提醒
    VPSettingSOSRemind,//SOS，类似查找手机功能
    VPSettingAutomaticPPGTest,//脉率自动检测开关,主要是ECG手环使用
    VPSettingAccurateSleep,//精准睡眠开关, 暂时无效, 目前使用VPSettingAutomaticPPGTest这个控制, 关闭的同时精准睡眠也会被关闭
    VPSettingMusicControl = 19,//音乐控制
    
    //下边是第二包
    VPSettingLongpressUnlock = 22, //长按解锁
    VPSettingMessageScreenLight = 23, //消息亮屏
    VPSettingAutomaticTemperatureTest = 24, //体温自动检测开关
    VPSettingTemperatureUnit = 25, //体温单位设置 1表示摄氏度 2表示华氏度
    VPSettingECGNormallyOpen = 26, //ECG 常开功能
    
    //其他指令
    VPSettingAutomaticOxygenTest = 1000,//血氧夜间自动检测
};

typedef NS_ENUM(NSInteger, VPSettingFunctionState) {//设置获取读取某个功能
    VPReadFunctionState = 0, //读取某个功能的开关和有无
    VPSettingFunctionOpen = 1,//打开某个功能
    VPSettingFunctionClose = 2,//关闭某个功能
    VPSettingFunctionCancel = 3,//现在仅动态血压校准有效
    VPSettingFunction = 4,//设置某个功能
};

typedef NS_ENUM(NSInteger, VPSettingFunctionCompleteState) {//设置某个功能完成之后的状态
    VPFunctionCompleteUnknown = 0, //设备没有此功能
    VPFunctionCompleteOpen = 1,//此功能已经打开
    VPFunctionCompleteClose = 2,//此功能已经关闭
    VPFunctionCompleteFailure = 3,//设置或者读取失败
    VPFunctionCompleteComplete = 4,//设置完成，针对Data设置的回复
};


typedef NS_ENUM(NSInteger,VPCameraType) {
    VPCameraTypeExit = 0,//退出拍照
    VPCameraTypeEnter = 1,//进入拍照
    VPCameraTypePhoto = 2//开始拍照
};

//可设置某个功能在设备上显示或隐藏
typedef NS_ENUM(NSInteger,VPOperationFuctionType) {
    VPOperationFuctionTypeBlood = 0,//血压
};

typedef NS_ENUM(NSInteger, VPOperationType) {//设置获取读取某个功能
    VPOperationTypeOpen = 1,//打开某个功能
    VPOperationTypeClose = 2,//关闭某个功能
    VPOperationTypeRead = 3, //读取某个功能的开关和有无
};

#pragma mark - 心率、血压、血氧、疲劳度的测试

typedef NS_ENUM(NSInteger,VPTestHeartState) {//测试心率过程中的状态变化
    VPTestHeartStateStart = 0,//开始检测心率，还没有测出结果
    VPTestHeartStateTesting = 1,//正在检测心率，已经测出心率值
    VPTestHeartStateNotWear = 2,//佩戴检测没有通过，测试已经结束
    VPTestHeartStateDeviceBusy = 3,//设备正忙不能测试了，测试已经结束
    VPTestHeartStateOver = 4,//测试正常结束，人为结束
};

typedef NS_ENUM(NSInteger,VPTestOxygenState) {//测试血氧过程中的状态变化
    VPTestOxygenStateStart = 0,//开始检测血氧，还没有测出结果
    VPTestOxygenStateTesting = 1,//正在检测血氧，已经测出血氧值
    VPTestOxygenStateNotWear = 2,//佩戴检测没有通过，测试已经结束
    VPTestOxygenStateDeviceBusy = 3,//设备正忙不能测试了，测试已经结束
    VPTestOxygenStateOver = 4,//测试正常结束，人为结束
    VPTestOxygenStateNoFunction = 5,//设备没有血氧功能
    VPTestOxygenStateCalibration = 6,//血氧校准中
    VPTestOxygenStateCalibrationComplete = 7,//血氧校准完成
    VPTestOxygenStateInvalid = 8,//血氧功能暂时不可用
};

typedef NS_ENUM(NSInteger,VPTestBreathingRateState) {//测试呼吸率过程中的状态变化
    VPTestBreathingRateStateStart = 0,//开始检测呼吸率，还没有测出结果
    VPTestBreathingRateStateTesting = 1,//正在检测呼吸率
    VPTestBreathingRateStateNotWear = 2,//佩戴检测没有通过，测试已经结束
    VPTestBreathingRateStateDeviceBusy = 3,//设备正忙不能测试了，测试已经结束
    VPTestBreathingRateStateOver = 4,//测试正常结束，人为结束
    VPTestBreathingRateStateComplete = 5,//测试完成
    VPTestBreathingRateStateFailure = 6,//测试无效，即为测试失败
    VPTestBreathingRateStateNoFunction = 7,//设备没有血氧功能
};

typedef NS_ENUM(NSInteger,VPTestBloodState) {//测试血压过程中的状态变化
    VPTestBloodStateTesting = 0,//开始检测血压，还没有测出结果
    VPTestBloodStateDeviceBusy = 1,//设备忙，测试结束
    VPTestBloodStateTestFail = 2,//测试无效，即为测试失败
    VPTestBloodStateTestInterrupt = 3,//测试被人为结束
    VPTestBloodStateComplete = 4,//测试已经完成
    VPTestBloodStateNoFunction = 5,//设备没有血压功能
};

typedef NS_ENUM(NSInteger,VPTestFatigueState) {//测试心率过程中的状态变化
    VPTestFatigueStateTesting = 0,//开始检测疲劳度，还没有测出结果
    VPTestFatigueStateDeviceBusy = 1,//设备忙，测试结束
    VPTestFatigueStateTestFail = 2,//测试无效，即为测试失败
    VPTestFatigueStateTestInterrupt = 3,//测试被人为结束
    VPTestFatigueStateComplete = 4,//测试已经完成
    VPTestFatigueStateNoFunction = 5,//设备没有疲劳度功能
};

typedef NS_ENUM(NSInteger,VPTestECGState) {//测试ECG过程中的状态变化
    VPTestECGStateStart = 0,//开始检测ECG，还没有测出结果
    VPTestECGStateTesting = 1,//正在检测ECG，已经测出心率值
    VPTestECGStateNotLead = 2,//导联脱落
    VPTestECGStateDeviceBusy = 3,//设备正忙不能测试了，测试已经结束
    VPTestECGStateOver = 4,//测试正常结束，人为结束
    VPTestECGStateFailure,//测试失败
    VPTestECGStateComplete,//测试已经完成
    VPTestECGStateNoFunction,//设备没有此功能
};

#pragma mark - SDK 1.7后新添加
typedef NS_ENUM(NSInteger,VPDeviceFemaleState) {//女性项目属于哪个生理期
    VPDeviceFemaleStateNone = 0,//没有设置生理期
    VPDeviceFemaleStateMenstrual,//月经期
    VPDeviceFemaleStatePregnancy,//备孕期
    VPDeviceFemaleStateGestation,//怀孕期
    VPDeviceFemaleStateBaoma,//辣妈期
};

typedef NS_ENUM(NSInteger,VPDeviceRuningMode) {//运动模式类型
    VPDeviceRuningModeCommon = 0,               //普通的单运动模式
    VPDeviceRuningModeOutdoorRun,               //户外跑步
    VPDeviceRuningModeOutdoorWalk,              //户外步行
    VPDeviceRuningModeIutdoorRun,               //室内跑步
    VPDeviceRuningModeIutdoorWalk,              //室内步行
    VPDeviceRuningModeHiking,                   //徒步
    VPDeviceRuningModeStairStepper,             //踏步机
    VPDeviceRuningModeOutdoorCycle,             //户外骑行
    VPDeviceRuningModeStationaryBike,           //室内骑行
    VPDeviceRuningModeElliptical,               //椭圆机
    VPDeviceRuningModeRowingMachine,            //划船机
    VPDeviceRuningModeMountaineering,           //登山
    VPDeviceRuningModeSwim,                     //游泳
    VPDeviceRuningModeSitUps,                   //仰卧起坐
    VPDeviceRuningModeSki,                      //滑雪
    VPDeviceRuningModeJumpRope,                 //跳绳
    VPDeviceRuningModeYoga,                     //瑜伽
    VPDeviceRuningModePingpong,                 //乒乓球
    VPDeviceRuningModeBasketball,               //篮球
    VPDeviceRuningModeVolleyball,               //排球
    VPDeviceRuningModeFootball,                 //足球
    VPDeviceRuningModeBadminton,                //羽毛球
    VPDeviceRuningModeTennis,                   //网球
    VPDeviceRuningModeClimbStairs,              //爬楼梯
    VPDeviceRuningModeFitness,                  //健身
    VPDeviceRuningModeWeightlifting,            //举重
    VPDeviceRuningModeDiving,                   //潜水
    VPDeviceRuningModeBoxing,                   //拳击
    VPDeviceRuningModeGymBall,                  //健身球
    VPDeviceRuningModeSquatTraining,            //深蹲训练
    VPDeviceRuningModeTriathlon,                //铁人三项
    VPDeviceRuningModeDance,                    //舞蹈
    VPDeviceRuningModeHIIT,                     //HIIT
    VPDeviceRuningModeRockClimbing,             //攀岩
    VPDeviceRuningModeSports,                   //竞技
    VPDeviceRuningModeBalls,                    //球类
    VPDeviceRuningModeFitnessGame,              //健身游戏
    VPDeviceRuningModeFreeTime,                 //自由活动
    VPDeviceRuningModeAerobics,                 //健美操
    VPDeviceRuningModeGymnastics,               //体操
    VPDeviceRuningModeFloorExercise,            //自由体操
    VPDeviceRuningModeHorizontalBar,            //单杠
    VPDeviceRuningModeParallelBars,             //双杠
    VPDeviceRuningModeTrampoline,               //蹦床
    VPDeviceRuningModeTrackAndField,            //田径
    VPDeviceRuningModeMarathon,                 //马拉松
    VPDeviceRuningModePushUps,                  //俯卧撑
    VPDeviceRuningModeDumbbel,                  //哑铃
    VPDeviceRuningModeRugbyFootball,            //橄榄球
    VPDeviceRuningModeHandball,                 //手球
    VPDeviceRuningModeBaseballSoftball,         //棒垒球
    VPDeviceRuningModeBaseball,                 //棒球
    VPDeviceRuningModeHockey,                   //曲棍球
    VPDeviceRuningModeGolf,                     //高尔夫球
    VPDeviceRuningModeBowling,                  //保龄球
    VPDeviceRuningModeBilliards,                //台球
    VPDeviceRuningModeRowing,                   //赛艇
    VPDeviceRuningModeSailboat,                 //帆船
    VPDeviceRuningModeSkate,                    //滑冰
    VPDeviceRuningModeCurling,                  //冰壶
    VPDeviceRuningModePuck,                     //冰球
    VPDeviceRuningModeSled,                     //雪橇
};


// 手机查找手环状态
typedef NS_ENUM(NSUInteger, VPSearchDeviceFunctionState) {
    VPSearchDeviceFunctionStateUnsupported,   // 功能不支持
    VPSearchDeviceFunctionStateEnter,         // 设备进入了查找状态
    VPSearchDeviceFunctionStateExit,          // 设备推出了查找状态
    VPSearchDeviceFunctionStateTimeout,       // 设备查找超时
};

// 体温手动测试/自动监测开关状态
typedef NS_ENUM(NSUInteger, VPTemperatureTestState) {
    VPTemperatureTestStateUnsupported,
    VPTemperatureTestStateOpen,
    VPTemperatureTestStateClose,
};

// 赛米加G15定制需求 界面的传输类型
typedef NS_ENUM(NSUInteger, VPG15DialViewTransformType) {
    VPG15DialViewTransformTypeAppQRCode = 0xA2,  //下载App二维码信息
    VPG15DialViewTransformTypePersonalProfile = 0xA3,   //个人信息
    VPG15DialViewTransformTypePictureTheme1 = 0xA4,     //图片主题1
    VPG15DialViewTransformTypePictureTheme2 = 0xA5,     //图片主题2
};

// 文字闹钟的设置模式
typedef NS_ENUM(NSUInteger, VPDeviceTextAlarmSettingModel) {
    VPDeviceTextAlarmSettingModelDelete = 1,
    VPDeviceTextAlarmSettingModelAddOrChange,
    VPDeviceTextAlarmSettingModelRead
};

// 血糖功能指令测试状态
typedef NS_ENUM(NSUInteger, VPDeviceBloodGlucoseTestState) {
    VPDeviceBloodGlucoseTestStateUnsupported,      // 设备不支持
    VPDeviceBloodGlucoseTestStateOpen,             // 开启测量
    VPDeviceBloodGlucoseTestStateClose,            // 关闭测量
    VPDeviceBloodGlucoseTestStateLowPower,         // 设备低电
    VPDeviceBloodGlucoseTestStateDeviceBusy,       // 设备正忙
    VPDeviceBloodGlucoseTestStateNotWear           // 设备佩戴检测未通过
};

