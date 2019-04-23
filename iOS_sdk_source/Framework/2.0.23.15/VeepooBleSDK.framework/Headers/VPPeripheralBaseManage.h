//
//  VPPeripheralBaseManage.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/9/20.
//  Copyright © 2017年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPeripheralModel.h"
#import "VPPublicDefine.h"
#import "VPDeviceAlarmModel.h"
#import "VPDeviceLongSeatModel.h"
#import "VPDeviceHeartAlarmModel.h"
#import "VPDeviceRaiseHandModel.h"
#import "VPDeviceBrightModel.h"
#import "VPDeviceFemaleModel.h"
#import "VPDeviceCountDownModel.h"
#import "VPDeviceNewAlarmModel.h"
#import "VPDevicePrivateBloodModel.h"
#import "VPScreenDurationModel.h"
#import "VPOxygenApneaRemindModel.h"
#import "VPECGTestDataModel.h"

@interface VPPeripheralBaseManage : NSObject<CBPeripheralDelegate>

//连接的设备模型
@property (nonatomic, strong) VPPeripheralModel *peripheralModel;

//接收手环查找手机的回调，可以设置这个属性进行监听，设备查找手机过程中每4秒回调一次，使用者在接收回调后可以播放一个3秒钟的音频
@property (nonatomic, copy) void(^ReceiveDeviceSearchIphoneCommand)(void);

//当手环被敲击后主动接收，type暂时不用管，只要有回调就证明设备被敲击了，type为01代表单击，02代表双击。
@property (nonatomic, copy) void(^ReceiveTapDeviceAlarm)(int type);

//接收SOS求救信息后回调，接收到求救信息如何操作，App内部可根据自定义场景设置
@property (nonatomic, copy) void(^ReceiveDeviceSOSCommand)(void);

+ (instancetype)shareVPPeripheralManager;

//发送固件升级命令，SDK内部使用
- (void)veepooSDKSendUpdateFirmCommand;

/**
 GSensor，特定开发使用
 注意：调试GSensor的时候要把正常的计步测试关闭掉，不然GSensor不会有返回值
 @param start 开始还是结束
 @param gSensorTestResult 测试的结果回调，key：totalSteps总的记步数，x y z分别代表轴上的当前参数
 */
- (void)veepooSDKTestGSensorStart:(BOOL)start testResult:(void(^)(NSDictionary *gSensorParameter))gSensorTestResult;

- (void)veepooSDKTestGSensorADCStart:(BOOL)start testResult:(void(^)(NSData *gSensorADC))gSensorADCTestResult;

#pragma mark -- 以下是基本功能的设置 要确保蓝牙正常连接
/**
 设置或者读取信息提醒的状态
 
 @param messageType 要设置和读取的信息类型
 @param settingState 设置还是读取
 @param settingCompleteBlock 设置和读取完成的回调
 */
- (void)veepooSDKSettingMessageType:(VPSettingMessageSwitchType)messageType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;

/**
 设置或者读取基本开关功能的状态包括：夜间抬手亮屏幕(只对22：00-08：00夜间进行设置，其余的时间抬手都是亮屏幕的)、设备防丢失、佩戴检测、公英制转换开代表是公制、时间制式设置开代表24小时制、心率自动检测、血压自动检测、运动量过量提醒（耳机项目）、心率血氧血压语音播报（耳机项目）、手机查找页面是否显示、秒表界面是否显示、血氧过低通知、LED灯档位1为偏白人2为偏黑人（档位为黑人的时候，佩戴检测设置无效）、HRV夜间自动检测、来电自动接听（当耳机取出手环时，来电自动接听）、蓝牙断链提醒、SOS页面显示、血氧夜间自动检测(枚举值1000)（要设置此功能baseFunctionType必须传入对应的枚举值，或者1000）
 
 @param baseFunctionType 要设置和读取的信息类型
 @param settingState 设置还是读取
 @param settingCompleteBlock 设置和读取完成的回调
 */
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;


/**
 读取设备的电池电量
 
 @param deviceBatteryPowerBlock 读取电量的回调返回值为0-4 0代表即将没电，1-4代表1-4格电量
 */
- (void)veepooSDKReadDeviceBatteryPower:(void(^)(NSUInteger batteryPower))deviceBatteryPowerBlock;

/**
 同步个人信息，不能读取，建议每次连接手环或者变更个人信息后都要调用，从手环获取的距离和卡路里，都要通过手环的步数和设置的身高去转换，手环默认身高175
 
 @param stature 用户的身高单位cm
 @param weight 用户的体重单位kg
 @param birth 用户的出生年如1995
 @param sex 用户的性别0代表女 1代表男
 @param targetStep 用户自定义的目标步数 目标值的范围为0-60000步 一定要在范围区间内
 @param synchronousPersonalInformationBlock 同步后的回调0代表失败 1代表成功
 */
- (void)veepooSDKSynchronousPersonalInformationWithStature:(NSUInteger)stature weight:(NSUInteger)weight birth:(NSUInteger)birth sex:(NSUInteger)sex targetStep:(NSUInteger)targetStep result:(void(^)(NSUInteger settingResult))synchronousPersonalInformationBlock;

/**
 注释：SDK1.7之后修改了此接口
 设置私人血压模式，设置的时候确保高压大于低压 如果设置模式为读取收缩压和舒张压都传0
 
 @param privateBloodModel 设置或者读取的model，不能为空
 @param settingMode  设置的方式为读取 关闭 或者开启私人模式，SDK1.7之后新增取消动态校准
 @param personalBloodModeResutBlock 设置成功的回调
 @param personalBloodModeFailureBlock 设置失败的回调
 */
- (void)veepooSDKSettingPersonalBloodWithModel:(VPDevicePrivateBloodModel *)privateBloodModel settingMode:(VPSettingFunctionState)settingMode successResult:(void(^)(VPDevicePrivateBloodModel *devicePrivateBloodModel))personalBloodModeResutBlock failureResult:(void(^)(void))personalBloodModeFailureBlock;


/**
 闹钟设置 如果是读取三个闹钟模型给默认初始化就可以 但是不可以为nil
 备注:设置闹钟的时候 每当改变一个闹钟的时候其他的2个闹钟值也要跟着一起设置,也就是每次设置闹钟都是对三个闹钟进行重新设置
 
 @param alarmModel1 第一个闹钟
 @param alarmModel2 第二个闹钟
 @param alarmModel3 第三个闹钟
 @param settingMode 设置还是读取
 @param settingAlarmResultBlock 设置成功结果的回调
 @param settingAlarmFailureBlock 设置失败的回调
 */
- (void)veepooSDKSettingDeviceAlarmWithAlarmModel1:(VPDeviceAlarmModel *)alarmModel1 alarmModel2:(VPDeviceAlarmModel *)alarmModel2 alarmModel3:(VPDeviceAlarmModel *)alarmModel3 settingMode:(VPOperationAlarmMode)settingMode successResult:(void(^)(VPDeviceAlarmModel *alarmModel1,VPDeviceAlarmModel *alarmModel2,VPDeviceAlarmModel *alarmModel3))settingAlarmResultBlock failureResult:(void(^)(void))settingAlarmFailureBlock;


/**
 设置和读取久坐数据
 
 @param longSeatModel 久坐的模型
 @param settingMode 设置久坐的模式0代表关闭久坐提醒 1代表开启久坐提醒 2代表读设备久坐信息
 @param settingLongSeatResultBlock 读取和设置成功后的回调
 @param settingLongSeatFailureBlock 读取和设置失败的回调
 */
- (void)veepooSDKSettingDeviceLongSeatWithLongSeatModel:(VPDeviceLongSeatModel *)longSeatModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceLongSeatModel *longSeatModel))settingLongSeatResultBlock failureResult:(void(^)(void))settingLongSeatFailureBlock;


/**
 设置和读取心率报警数据
 
 @param heartAlarmModel 心率报警模型
 @param settingMode 设置心率报警的模式0代表关闭 1代表开启 2代表读设备心率报警信息
 @param settingHeartAlarmResultBlock 读取和设置成功后的回调
 @param settingHeartAlarmFailureBlock 读取和设置失败的回调
 */
- (void)veepooSDKSettingDeviceHeartAlarmWithHeartAlarmModel:(VPDeviceHeartAlarmModel *)heartAlarmModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceHeartAlarmModel *heartAlarmModel))settingHeartAlarmResultBlock failureResult:(void(^)(void))settingHeartAlarmFailureBlock;


/**
 设置和读取翻腕亮屏功能
 
 @param raiseHandModel 翻腕亮屏模型
 @param settingMode 设置翻腕亮屏的模式0代表关闭 1代表开启 2代表读设备翻腕亮屏信息
 @param settingRaiseHandResultBlock 读取和设置成功后的回调
 @param settingRaiseHandFailureBlock 读取和设置失败的回调
 */
- (void)veepooSDKSettingRaiseHandWithRaiseHandModel:(VPDeviceRaiseHandModel *)raiseHandModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceRaiseHandModel *raiseHandModel))settingRaiseHandResultBlock failureResult:(void(^)(void))settingRaiseHandFailureBlock;

/**
 设置屏幕亮度调节功能
 
 @param brightModel 亮度调节的模型
 @param settingMode 1代表设置 2代表读取，这里没有0 哈哈
 @param settingBrightResultBlock 设置成功，带有设置成功后的回调
 @param settingBrightFailureBlock 设置失败的回调
 */
- (void)veepooSDKSettingBrightWithBrightModel:(VPDeviceBrightModel *)brightModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceBrightModel *brightModel))settingBrightResultBlock failureResult:(void(^)(void))settingBrightFailureBlock;

#pragma mark -- 用户开始关闭的操作
/**
 设置和监听拍照，进入拍照模式后通过回调可以监听用户拍照动作，当监听到用户VPCameraTypePhoto开始拍照的回调后，可以调用系统相机进行拍照并保存
 
 @param settingType 进入还是退出拍照
 @param cameraBlock 设置和监听拍照的回调
 */
- (void)veepooSDKSettingCameraType:(VPCameraType)settingType settingAndMonitorResult:(void(^)(VPCameraType cameraType))cameraBlock;


/**
 开启或者关闭心率测试，在测试过程中发现异常结束状态都代表此次测试已经结束，心率测试是一个动态测试过程，测试过程中会有多个结果回调，用户测试完毕后要主动调用此方法结束测试
 
 @param start YES代表开始测试 NO代表结束测试
 @param testHeartResultBlock 测试结果的回调
 */
- (void)veepooSDKTestHeartStart:(BOOL)start testResult:(void(^)(VPTestHeartState testHeartState, NSUInteger heartValue))testHeartResultBlock;

/**
 开启或者关闭血氧测试，测试的原理与心率相同，即一次测试会有多组值
 
 @param start YES代表开始测试 NO代表结束测试
 @param testOxygenResultBlock 测试结果的回调，当测试为校准状态时，value为校准进度，其他时候为血氧测试值
 */
- (void)veepooSDKTestOxygenStart:(BOOL)start testResult:(void(^)(VPTestOxygenState testOxygenState, NSUInteger oxygenValue))testOxygenResultBlock;


/**
 测试呼吸率
 
 @param start YES代表开始测试 NO代表结束测试
 @param testBreathingRateBlock 测试呼吸率的回调
 */
- (void)veepooSDKTestBreathingRateStart:(BOOL)start testResult:(void(^)(VPTestBreathingRateState testBreathingRateState, NSUInteger breathingRateProgress, NSUInteger breathingRateValue))testBreathingRateBlock;

/**
 开启或者关闭血压测试 血压测试与心率测试不同，血压测试一次大概需要50-55秒时间，开发者可以根据这个时间自定义测试进度，每次测试结束才会有结果，即一次测试只能有一组值
 
 @param start YES代表开始测试 NO代表结束测试
 @param testMode 测试的模式0代表 通用模式，1代表私人模式，默认传0
 @param testBloodResultBlock 测试结果的回调 包括测试状态、测试进度、高低压值
 */
- (void)veepooSDKTestBloodStart:(BOOL)start testMode:(NSUInteger)testMode testResult:(void(^)(VPTestBloodState testBloodState, NSUInteger testBloodProgress, NSUInteger highBlood, NSUInteger lowBlood))testBloodResultBlock;


/**
 开启和关闭疲劳度测试，疲劳度的测试和血压测试原理相同，即没测试一次最后只有一组值，不同的是设备给出了疲劳度测试的进度
 
 @param start YES代表开始测试 NO代表结束测试
 @param testFatigueResultBlock 测试结果的回调，测试返回结果包含测试状态、测试进度、和测试结果，测试结果等级为1-4分别对应的等级为 不疲劳、轻度疲劳、一般疲劳、重度疲劳
 */
- (void)veepooSDKTestFatigueStart:(BOOL)start testResult:(void(^)(VPTestFatigueState testFatigueState,NSUInteger testProgress, NSUInteger fatigueValue))testFatigueResultBlock;

/**
 开启或者关闭ECG测试，在测试过程中发现异常结束状态都代表此次测试已经结束，ECG测试是一个动态测试过程，测试过程中会有多个结果回调，用户测试完毕后要主动调用此方法结束测试
 
 @param start YES代表开始测试 NO代表结束测试
 @param testECGResultBlock 测试结果的回调
 */
- (void)veepooSDKTestECGStart:(BOOL)start testResult:(void(^)(VPTestECGState testECGState, NSUInteger testProgress, VPECGTestDataModel *testModel))testECGResultBlock;

/**
 发送与手机配对指令，当设备连接成功后，系统会有一个弹窗让用户选择设备是否与手机配对，如果用户选择了取消，如果在连接过程中想与手机配对，则发送这个命令就可以了，此命令没有回调，当发送成功后系统会有弹窗给用户
 注意：如果设备和手机已经配对此命令无效
 */
- (void)veepooSDKSendPairedWithIphoneCommand;

#pragma mark --- SDK1.7开始新增功能
/**
 设置女性项目 接口不可用，无此功能
 
 @param femaleModel 女性项目的model
 @param settingMode 设置模式0代表关闭 1代表开启 2代表读设备女性信息
 @param settingFemaleResultBlock 设置或者读取成功
 @param settingFemaleFailureBlock 设置或者读取失败
 */
- (void)veepooSDKSettingDeviceFemaleWithFemaleModel:(VPDeviceFemaleModel *)femaleModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceFemaleModel *deviceFemaleModel))settingFemaleResultBlock failureResult:(void(^)(void))settingFemaleFailureBlock;

/**
 设置倒计时
 
 @param countDownModel 倒计时Model，任何时候不能nil，读取的时候给你初始化的就可以
 @param settingMode 设置模式0代表取消当前正在进行的倒计时、1代表设置、2代表读取
 @param settingCountDownResultBlock 设置成功的回调
 @param settingCountDownFailureBlock 设置失败的回调
 */
- (void)veepooSDKSettingDeviceCountDownWithCountDownModel:(VPDeviceCountDownModel *)countDownModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceCountDownModel *countDownModel))settingCountDownResultBlock failureResult:(void(^)(void))settingCountDownFailureBlock;

/**
 设置或者读取新闹钟
 
 @param alarmModel 新闹钟的Model，不能为空，读取的时候传默认
 @param settingMode 0代表删除这组闹钟，1代表设置（增加或者修改）2代表读取
 @param settingNewAlarmResultBlock 设置或者读取成功，返回当前所有的闹钟数
 @param settingNewAlarmFailureBlock 设置或者读取闹钟失败
 */
- (void)veepooSDKSettingDeviceNewAlarmWithNewAlarmModel:(VPDeviceNewAlarmModel *)alarmModel settingMode:(NSUInteger)settingMode successResult:(void(^)(NSArray *alarmArray))settingNewAlarmResultBlock failureResult:(void(^)(void))settingNewAlarmFailureBlock;


#pragma mark --- SDK1.9开始新增功能

/**
 屏幕风格设置，先根据VPPeripheralModel中的screenTypes获取屏幕风格设置的区间，如果为3代表可以设置1-3，如果为0代表没有此功能

 @param screenStyle 设置的样式，区间为【1 screenTypes】，读取的时候传0
 @param settingMode 1代表设置，2代表读取
 @param settingScreenStyleResultBlock 设置后的回调，包括设置成功或者失败及设置后手环端的样式
 */
- (void)veepooSDKSettingDeviceScreenStyle:(int)screenStyle settingMode:(NSUInteger)settingMode result:(void(^)(int screenStyle, BOOL settingSuccess))settingScreenStyleResultBlock;

/**
 设置亮屏时长
 
 @param durationModel 设置屏幕时长模型，读取的时候不为nil就可以
 @param settingMode 1代表设置，2代表读取
 @param settingResult 设置后成功的回调
 @param failureResult 失败的回调
 */
- (void)veepooSDKSettingScreenDuration:(VPScreenDurationModel *)durationModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPScreenDurationModel *DurationModel))settingResult failureResult:(void(^)(void))failureResult;

/**
 设置呼吸暂停提醒，这个是血氧类型为4的时候取代呼吸暂停只有一个开关的提醒
 
 @param remindModel 设置呼吸暂停提醒模型
 @param settingMode 1代表设置，2代表读取
 @param successResult 设置后成功的回调
 @param failureResult 设置后失败的回调
 */
- (void)veepooSDKSettingOxygenApneaRemind:(VPOxygenApneaRemindModel *)remindModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPOxygenApneaRemindModel *oxygenApneaRemindModel))successResult failureResult:(void(^)(void))failureResult;

#pragma mark --- SDK2.3开始新增功能
/**
 设置和读取运动模式 2.3开始新增
 此接口正常的使用方式是，每次设置开启或者关闭的时候要确保当前的状态在做操作

 @param settingType 0是关闭运动模式，1是开启运动模式，2是读取当前设备运动模式
 @param runningResultBlock 设置和读取结果，
    runningType为0代表不在运动模式下，1代表运动模式中，2代表其他忙碌状态,3代表运动模式结束连接状态下主动告知App,此参数只有在读取或者设置失败的时候做参考，或者在运动结束主动上报的时候用
    settingSuccess 设置或读取是否成功，如果失败，可以参考runningType类型来看一下原因，如运动模式已经开启，再次开启，就会失败，或者设备在做其他操作
 */
- (void)veepooSDKSettingDeviceRunning:(int)settingType result:(void(^)(int runningType, BOOL settingSuccess))runningResultBlock;

#pragma mark --- SDK2.4开始新增功能
//清除数据，清除数据后手环会自动关机，不能监听是否清除成功，关机会会与App断开连接 （据 2.4增加）
- (void)veepooSDKClearDeviceData;

#pragma mark --- 简易的读取方式，适用于单机版本，读取完成之后可直接从SDK的数据库中提取数据，由子类VPPeripheralManage实现
//开始读取所有数据
- (void)veepooSdkStartReadDeviceAllDataWithReadStateChangeBlock:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;

//读取计步数据 调用每次获取当前手环的步数，SDK内部使用
- (void)veepooSdkSendStepCommand;

/**
 开始读取运动数据
 
 @param readDeviceRunningBlock 读取运动数据成功或者失败的回调
 */
- (void)veepooSDKStartReadDeviceRunningData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalTimes, NSUInteger currentReadTimes, NSUInteger readCurrentTimesProgress))readDeviceRunningBlock;

//开始读取血氧数据,不可用
- (void)veepooSdkStartReadDeviceOxygenData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;

//开始读取Hrv数据,不可用
- (void)veepooSdkStartReadDeviceHrvData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;

#pragma mark --- 适用于自己存储数据，开发过程中比较灵活，数据自己存储，适用于数据上传服务器和多账号多手环开发，由子类VPPeripheralAddManage实现，暂时为没有实现
//特别说明：VPPeripheralAddManage此代理中设计到字典里边的key最好在自己程序中先写成全局常量，因不涉及到数据库等所以后边可能会根据具体情况改变，自己代码也最好不要获取数据后直接保存，最好自己转一下符合自己公司的key在保存，这样后边SDK改变，对应自己的程序只需要改变全局常量即可了
/**
 读取某一天的计步数据

 @param dayNumber 代表哪一天0代表今天，1代表昨天，2代表前天，不能大于VPPeripheralModel中属性saveDays的值
 @param readStepBlock 读取计步的回调，是一个字典，包含计步、距离和卡路里
 */
- (void)veepooSDK_readStepDataWithDayNumber:(NSInteger)dayNumber result:(void(^)(NSDictionary *stepDict))readStepBlock;

/**
 读取某一天的睡眠数据,因数据量比较少，所以没有进度

 @param dayNumber 同上 但是睡眠今天应该显示昨天的数据，所以读取睡眠的dayNumber区间应该是【1 saveDays】
 @param readSleepBlock 返回一天的睡眠数据，一天可能有多段睡眠所以是数组，目前结构和数据库中类VPDataBaseOperation的结构一致，可以去参考下
 */
- (void)veepooSDK_readSleepDataWithDayNumber:(NSInteger)dayNumber result:(void(^)(NSArray *sleepOneDayArray))readSleepBlock;

/**
 读取基本数据，一天的详细的计步、心率、血压数据，如每5分钟一次数据

 @param dayNumber 代表哪一天0代表今天，1代表昨天，2代表前天，不能大于
 @param maxPackage 一天的数据比较多，每次读取可以从选择的包数读取，如从上一次读取结束的最大包数 + 1 读取，如逻辑简单也可以每次从1开始读取，处理起来简单，增加了手环传输数据量
 @param readBasicDataBlock 返回一天的基本数据，一天多个5分钟或者10分钟所以是数组，目前结构和数据库中类VPDataBaseOperation的结构一致，可以去参考下,因数据比较多所以返回一个一共有多少包，当前读取到多少包了,当前包大于等于总包数，数据读取完成
 */
- (void)veepooSDK_readBasicDataWithDayNumber:(NSInteger)dayNumber maxPackage:(NSInteger)maxPackage result:(void(^)(NSArray *oneDayBasicArray,NSInteger totalPackage, NSInteger currentReadPackage))readBasicDataBlock;

/**
 读取一天的血氧数据 此接口无效

 @param dayNumber 代表哪一天0代表今天，1代表昨天，2代表前天，不能大于saveDays
 @param maxPackage 一天的数据比较多，每次读取可以从选择的包数读取，如从上一次读取结束的最大包数 + 1 读取，如逻辑简单也可以每次从1开始读取，处理起来简单，增加了手环传输数据量
 @param readOxygenDataBlock 返回一天的血氧数据，目前结构和数据库中类VPDataBaseOperation的结构一致，可以去参考下,因数据比较多所以返回一个一共有多少包，当前读取到多少包了,当前包大于等于总包数，数据读取完成
 */
- (void)veepooSDK_readOxygenDataWithDayNumber:(NSInteger)dayNumber maxPackage:(NSInteger)maxPackage result:(void(^)(NSArray *oneDayOxygenArray,NSInteger totalPackage, NSInteger currentReadPackage))readOxygenDataBlock;

//读取一天hrv数据，逻辑同血氧读取方式,不可用
- (void)veepooSDK_readHrvDataWithDayNumber:(NSInteger)dayNumber maxPackage:(NSInteger)maxPackage result:(void(^)(NSArray *oneDayHrvArray,NSInteger totalPackage, NSInteger currentReadPackage))readHrvDataBlock;

/**
 获取手环运动数据的CRC
 读取运动模式数据的时候为了重复读取数据，先获取手环运动数据的CRC，获取的array长度是多少就代表手环最多能够存储几组运动数据，如数据内为@[@(128),@(0),@(153698)],数组内的数据为NSNumber类型，数组长度为3，手环上最多存储3组数据，读取第几组就用数组的下标读取，如0 1 2 ，数据为0的位置如@(0)，这块里没有数据，要直接跳过，每次获取完crc数据后要和本地的运动模式数据对比，如果返回的crc在本地存在就不用读取直接跳过，第一组和第二组不用读取，那直接用数据的最后下标2去读取就可以了,比如第一组和第三组都要读取，那就调用两次获取运动数据的接口，要读取完一组后在去读取，（切记不要一组没有读取完毕，就直接读取下一组）

 @param readDeviceRunningCrcBlock 获取CRC数据后的回调
 */
- (void)veepooSDK_readDeviceRunningCrcResult:(void(^)(NSArray *crcValues))readDeviceRunningCrcBlock;


- (void)veepooSDK_readDeviceRunningDataWithBlockNumber:(NSInteger)blockNumber result:(void(^)(NSDictionary *runningDataDict,NSInteger totalPackage, NSInteger currentReadPackage))readDeviceRunningDataBlock;

@end







