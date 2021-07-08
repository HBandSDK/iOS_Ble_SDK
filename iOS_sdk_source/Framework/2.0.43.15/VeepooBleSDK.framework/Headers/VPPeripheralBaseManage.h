//
//  VPPeripheralBaseManage.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/9/20.
//  Copyright © 2017年 zc.All rights reserved.
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
#import "VPLowPowerModel.h"
#import "VPOxygenDisconnectTestModel.h"
#import "VPPttValueModel.h"
#import "VPSyncPersonalInfo.h"
#import "VPDialModel.h"
#import "VPPhotoDialModel.h"
#import "VPDeviceMarketDialModel.h"
#import "VPDeviceGPSModel.h"
#import "VPDeviceKAABAGPSModel.h"
#import "VPDeviceHadjCountModel.h"

@interface VPPeripheralBaseManage : NSObject<CBPeripheralDelegate>

//Connected device model 连接的设备模型
@property (nonatomic, strong) VPPeripheralModel *peripheralModel;

//Receiving the bracelet to find the callback of the mobile phone, you can set this property to monitor. The device will call back every 4 seconds during the device search. The user can play a 3-second audio after receiving the callback.
//接收手环查找手机的回调，可以设置这个属性进行监听，设备查找手机过程中每4秒回调一次，使用者在接收回调后可以播放一个3秒钟的音频
@property (nonatomic, copy) void(^ReceiveDeviceSearchIphoneCommand)(void);

//When the bracelet is actively received after being tapped, the type is temporarily ignored. As long as there is a callback, the device is struck. Type 01 means click and 02 means double click.
//当手环被敲击后主动接收，type暂时不用管，只要有回调就证明设备被敲击了，type为01代表单击，02代表双击。
@property (nonatomic, copy) void(^ReceiveTapDeviceAlarm)(int type);

//After receiving the SOS help information, the callback is sent, and the help information is received, and the App can be set according to the customized scene.
//接收SOS求救信息后回调，接收到求救信息如何操作，App内部可根据自定义场景设置
@property (nonatomic, copy) void(^ReceiveDeviceSOSCommand)(void);

//Receive 50Hz green light data
//接收50Hz绿光数据
@property (nonatomic, copy) void(^ReceiveGreenLightData)(NSArray <NSNumber *>*values);

//Create an instance
+ (instancetype)shareVPPeripheralManager;

//Send firmware upgrade command, used internally by SDK
//发送固件升级命令，SDK内部使用
- (void)veepooSDKSendUpdateFirmCommand;

/**
 GSensor, specific development use
   Note: When debugging GSensor, you should turn off the normal step test, otherwise GSensor will not have a return value.
 GSensor，特定开发使用
 注意：调试GSensor的时候要把正常的计步测试关闭掉，不然GSensor不会有返回值
 @param start Start or end 开始还是结束
 @param gSensorTestResult The result of the test callback, key: totalSteps total number of steps, x y z represent the current parameters on the axis 测试的结果回调，key：totalSteps总的记步数，x y z分别代表轴上的当前参数
 */
- (void)veepooSDKTestGSensorStart:(BOOL)start testResult:(void(^)(NSDictionary *gSensorParameter))gSensorTestResult;

- (void)veepooSDKTestGSensorADCStart:(BOOL)start testResult:(void(^)(NSData *gSensorADC))gSensorADCTestResult;

//Invalid interface 无效接口
- (void)veepooSDKSendData:(NSData *)commandData adcResult:(void(^)(NSData *gSensorADC))adcTestResult valueResult:(void(^)(NSData *gSensorADC))valueTestResult;

//同步时间，特殊情况使用，默认连接的时候会自动同步时间 system 1是12小时 2是24小时，如果无用则需要通过开关设置中的制式在设置一遍
- (void)veepooSDKSettingTimeWithYear:(int)year month:(int)month day:(int)day hour:(int)hour minute:(int)min second:(int)sec timeSystem:(int)system;


/// 定制功能
/// 24-hour oxygen test switch, Special project functions
/// @param settingType Set type
/// @param settingResult Result after setting
- (void)veepooSDKSettingAllDayOxygenTest:(VPSettingFunctionState)settingType result:(void(^)(VPSettingFunctionCompleteState state))settingResult;

/// 定制功能 断开连接后测试的心率和血氧数据
/// Read the blood oxygen and heart rate data tested after disconnection
/// @param lastReadTime Read the data tested after this time format @"19-10-11 08:00:00"
/// @param readResult Returns the data for the test 0 reading, 1 read complete
- (void)veepooSDKReadDisconnectOxygenDataWithLastReadTime:(NSString *)lastReadTime result:(void(^)(VPOxygenDisconnectTestModel *testModel, NSInteger state))readResult;

//设置语言，如果设备上没有的语言，则默认显示英语, 建议使用自动SDK跟随手机语言设置，如使用此接口systemLanguage此值设为NO
//languageType 中文(1) 英文(2) 日语(3) 韩语(4) 德语(5) 俄语(6) 西班牙(7) 意大利(8) 法语(9) 越南语(10) 葡萄牙语(11) 泰语(13) 波兰(14) 瑞典(15) 土耳其(16) 荷兰语(17) 捷克语(18)
- (void)veepooSDKSettingLanguage:(UInt8)languageType result:(void(^)(BOOL success))settingLangueResult;

#pragma mark - 单兵SOS定制功能，App和设备只做简单指令交互，其他功能客户自己解决

//接受士兵的反馈,设置这个回调就可以，设备长按3秒侧按键，启动SOS功能，手环发送一条SOS指令到APP，APP收到后，反馈指令给手环，手环显示“SOS发送成功”
//Accept the soldier's feedback and set this callback
@property(nonatomic, strong) void(^receiveSoldierFeedback)(void);

//App发送一条指令给设备，紧急情况下，指挥员信息通知单兵（手机到手环）
//In an emergency, the commander informs the individual soldier (mobile phone to bracelet)
- (void)veepooSDKSendToSoldierCommand:(void(^)(BOOL sendSuccess))result;

/// 服务器可以主动推送一些文字消息，透过APP转发给手环，并在手环上显示消息并振动提醒。比如“全员撤退”之类的命令。
/// @param type 用来定义任务类型
/// @param taskMessage 用来显示服务器要推送的内容,内容长度不能超过100个字节
- (void)veepooSDKSendToSoldierSpecialTask:(int)type taskMessage:(NSString *)taskMessage andResult:(void(^)(BOOL success))sendResult;


#pragma mark - ECG PTT FUNCTION

/// 是否处于PTT模式下的监听
/// Monitor PTT status changes, Destroy the listener nil
/// @param pttListener 1 is in ptt mode
- (void)veepooSDKAddPTTStateListener:(void(^)(NSInteger pttState))pttListener;

/// PTT数据监听
/// <#Description#>
/// @param start <#start description#>
/// @param valueBlock <#valueBlock description#>
/// @param signalBlock <#signalBlock description#>
- (void)veepooSDKPTTTest:(BOOL)start valueBlock:(void(^)(VPPttValueModel *valueModel))valueBlock signalBlock:(void(^)(NSArray <NSNumber *>*signals))signalBlock;


#pragma mark - The following are the basic function settings to ensure that Bluetooth is properly connected. 以下是基本功能的设置 要确保蓝牙正常连接
/**
 Set or read the status of the message reminder
 设置或者读取信息提醒的状态
 
 @param messageType Type of information to set and read 要设置和读取的信息类型
 @param settingState Set or read 设置还是读取
 @param settingCompleteBlock Set and read completed callbacks 设置和读取完成的回调
 */
- (void)veepooSDKSettingMessageType:(VPSettingMessageSwitchType)messageType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;

- (void)veepooSDKSettingMessageWithData:(NSData *)settingData completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;

/**
 The status of setting or reading the basic switch function includes: raising the screen at night to brighten the screen (only setting for 22:00-08:00 night, the rest of the time is to brighten the screen)
 设置或者读取基本开关功能的状态包括：夜间抬手亮屏幕(只对22：00-08：00夜间进行设置，其余的时间抬手都是亮屏幕的)、设备防丢失、佩戴检测、公英制转换开代表是公制、时间制式设置开代表24小时制、心率自动检测、血压自动检测、运动量过量提醒（耳机项目）、心率血氧血压语音播报（耳机项目）、手机查找页面是否显示、秒表界面是否显示、血氧过低通知、LED灯档位1为偏白人2为偏黑人（档位为黑人的时候，佩戴检测设置无效）、HRV夜间自动检测、来电自动接听（当耳机取出手环时，来电自动接听）、蓝牙断链提醒、SOS页面显示、血氧夜间自动检测(枚举值1000)（要设置此功能baseFunctionType必须传入对应的枚举值，或者1000）
 
 @param baseFunctionType Type of information to set and read 要设置和读取的信息类型
 @param settingState Set or read 设置还是读取
 @param settingCompleteBlock Set and read completed callbacks 设置和读取完成的回调
 */
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;


/**
 Read the battery level of your device
 读取设备的电池电量
 
 @param deviceBatteryPowerBlock The callback return value for reading power is 0-4, 0 means no power, 1-4 means 1-4 grid
 读取电量的回调返回值为0-4 0代表即将没电，1-4代表1-4格电量
 */
- (void)veepooSDKReadDeviceBatteryPower:(void(^)(NSUInteger batteryPower))deviceBatteryPowerBlock;

/**
 Synchronize personal information, can not be read, it is recommended to call each time you connect the bracelet or change personal information, the distance and calorie obtained from the bracelet must be converted by the number of steps and the height of the set, the bracelet default Height 175
 同步个人信息，不能读取，建议每次连接手环或者变更个人信息后都要调用，从手环获取的距离和卡路里，都要通过手环的步数和设置的身高去转换，手环默认身高175
 
 @param stature User's height unit cm 用户的身高单位cm
 @param weight User's weight unit kg 用户的体重单位kg
 @param birth The user's birth year is 1995 用户的出生年如1995
 @param sex User's gender 0 stands for female 1 stands for male 用户的性别0代表女 1代表男
 @param targetStep User-defined target step number Target value range is 0-60000 steps 用户自定义的目标步数 目标值的范围为0-60000步 一定要在范围区间内
 @param synchronousPersonalInformationBlock Callback 0 after synchronization represents failure 1 represents success 同步后的回调0代表失败 1代表成功
 */
- (void)veepooSDKSynchronousPersonalInformationWithStature:(NSUInteger)stature weight:(NSUInteger)weight birth:(NSUInteger)birth sex:(NSUInteger)sex targetStep:(NSUInteger)targetStep result:(void(^)(NSUInteger settingResult))synchronousPersonalInformationBlock;

//可以使用下边的设置个人信息，使用personalInfo设置，需自己初始化
- (void)veepooSDKSynchronousPersonalInformation:(VPSyncPersonalInfo *)personalInfo result:(void(^)(NSUInteger settingResult))synchronousPersonalInformationBlock;

/**
 Set the private blood pressure mode, ensure that the high pressure is greater than the low pressure when setting. If the setting mode is read systolic pressure and diastolic pressure are transmitted 0
 设置私人血压模式，设置的时候确保高压大于低压 如果设置模式为读取收缩压和舒张压都传0
 
 @param privateBloodModel Model set or read, cannot be empty 设置或者读取的model，不能为空
 @param settingMode Set the way to read off 设置的方式为读取 关闭 或者开启私人模式
 @param personalBloodModeResutBlock Set a successful callback 设置成功的回调
 @param personalBloodModeFailureBlock Set failed callbacks 设置失败的回调
 */
- (void)veepooSDKSettingPersonalBloodWithModel:(VPDevicePrivateBloodModel *)privateBloodModel settingMode:(VPSettingFunctionState)settingMode successResult:(void(^)(VPDevicePrivateBloodModel *devicePrivateBloodModel))personalBloodModeResutBlock failureResult:(void(^)(void))personalBloodModeFailureBlock;


/**
 This interface has expired for the company's new product.
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
 Set up and read sedentary data
 设置和读取久坐数据
 
 @param longSeatModel Sedentary model 久坐的模型
 @param settingMode Set sedentary mode 0 means turn off sedentary reminder 1 means turn on sedentary reminder 2 stand for reading equipment sedentary information 设置久坐的模式0代表关闭久坐提醒 1代表开启久坐提醒 2代表读设备久坐信息
 @param settingLongSeatResultBlock Callback after reading and setting success 读取和设置成功后的回调
 @param settingLongSeatFailureBlock Read and set failed callbacks 读取和设置失败的回调
 */
- (void)veepooSDKSettingDeviceLongSeatWithLongSeatModel:(VPDeviceLongSeatModel *)longSeatModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceLongSeatModel *longSeatModel))settingLongSeatResultBlock failureResult:(void(^)(void))settingLongSeatFailureBlock;


/**
 Set and read heart rate alarm data
 设置和读取心率报警数据
 
 @param heartAlarmModel Heart rate alarm model 心率报警模型
 @param settingMode Set the heart rate alarm mode 0 to turn off 1 to turn on 2 to read the device heart rate alarm information 设置心率报警的模式0代表关闭 1代表开启 2代表读设备心率报警信息
 @param settingHeartAlarmResultBlock Callback after reading and setting success 读取和设置成功后的回调
 @param settingHeartAlarmFailureBlock Read and set failed callbacks 读取和设置失败的回调
 */
- (void)veepooSDKSettingDeviceHeartAlarmWithHeartAlarmModel:(VPDeviceHeartAlarmModel *)heartAlarmModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceHeartAlarmModel *heartAlarmModel))settingHeartAlarmResultBlock failureResult:(void(^)(void))settingHeartAlarmFailureBlock;


/**
 Set and read the scrolling function
 设置和读取翻腕亮屏功能
 
 @param raiseHandModel Wrist wristscreen model 翻腕亮屏模型
 @param settingMode Set the mode of turning the wrist bright screen to 0 to turn off 1 to turn on 2 to read the device to turn the wrist bright information 设置翻腕亮屏的模式0代表关闭 1代表开启 2代表读设备翻腕亮屏信息
 @param settingRaiseHandResultBlock Callback after reading and setting success
 @param settingRaiseHandFailureBlock Read and set failed callbacks
 */
- (void)veepooSDKSettingRaiseHandWithRaiseHandModel:(VPDeviceRaiseHandModel *)raiseHandModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceRaiseHandModel *raiseHandModel))settingRaiseHandResultBlock failureResult:(void(^)(void))settingRaiseHandFailureBlock;

/**
 Set screen brightness adjustment
 设置屏幕亮度调节功能
 
 @param brightModel Brightness adjustment model 亮度调节的模型
 @param settingMode 1 stands for setting 2 stands for reading 1代表设置 2代表读取
 @param settingBrightResultBlock Successful setup with callback after successful setup
 @param settingBrightFailureBlock Set failed callbacks
 */
- (void)veepooSDKSettingBrightWithBrightModel:(VPDeviceBrightModel *)brightModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceBrightModel *brightModel))settingBrightResultBlock failureResult:(void(^)(void))settingBrightFailureBlock;

#pragma mark - User turn off the operation 用户开启关闭的操作
/**
 Set and monitor the camera, after entering the camera mode, you can listen to the user's camera action through the callback. After listening to the callback of the user VPCameraTypePhoto to start taking photos, you can call the system camera to take photos and save.
 设置和监听拍照，进入拍照模式后通过回调可以监听用户拍照动作，当监听到用户VPCameraTypePhoto开始拍照的回调后，可以调用系统相机进行拍照并保存
 
 @param settingType Enter or exit photo 进入还是退出拍照
 @param cameraBlock Set and listen for photo callbacks
 */
- (void)veepooSDKSettingCameraType:(VPCameraType)settingType settingAndMonitorResult:(void(^)(VPCameraType cameraType))cameraBlock;


/**
 Turning the heart rate test on or off, and finding the abnormal end state during the test means that the test has ended. The heart rate test is a dynamic test process. There are multiple result callbacks during the test. After the user finishes testing, you should call this method to end. test
 开启或者关闭心率测试，在测试过程中发现异常结束状态都代表此次测试已经结束，心率测试是一个动态测试过程，测试过程中会有多个结果回调，用户测试完毕后要主动调用此方法结束测试
 
 @param start Start or end
 @param testHeartResultBlock Callback of test results
 */
- (void)veepooSDKTestHeartStart:(BOOL)start testResult:(void(^)(VPTestHeartState testHeartState, NSUInteger heartValue))testHeartResultBlock;

/**
 Turn the blood oxygen test on or off. The principle of the test is the same as the heart rate, that is, there will be multiple sets of values in one test.
 开启或者关闭血氧测试，测试的原理与心率相同，即一次测试会有多组值
 
 @param start Start or end
 @param testOxygenResultBlock The callback of the test result, when the test is in the calibration state, the value is the calibration progress, and the other is the blood oxygen test value.  测试结果的回调，当测试为校准状态时，value为校准进度，其他时候为血氧测试值
 */
- (void)veepooSDKTestOxygenStart:(BOOL)start testResult:(void(^)(VPTestOxygenState testOxygenState, NSUInteger oxygenValue))testOxygenResultBlock;

//Blood Oxygen Test For special customization projects, use Fang FA above if not for special customization customers,  Method of Monitoring 50Hz Raw Data(ReceiveGreenLightData)
//开始测试血氧(特殊定制客户使用, 如非特殊定制客户请使用上面的方法),如需监测绿光请使用ReceiveGreenLightData此回调属性
- (void)veepooSDKTestOxygenAndHeartStart:(BOOL)start testResult:(void(^)(VPTestOxygenState testOxygenState, NSUInteger oxygenValue, NSUInteger heartValue))testOxygenResultBlock;

/**
 Test respiration rate
 测试呼吸率
 
 @param start Start or end
 @param testBreathingRateBlock Test the rate of breath rate 测试呼吸率的回调
 */
- (void)veepooSDKTestBreathingRateStart:(BOOL)start testResult:(void(^)(VPTestBreathingRateState testBreathingRateState, NSUInteger breathingRateProgress, NSUInteger breathingRateValue))testBreathingRateBlock;

/**
 Turning the blood pressure test on or off is different from the heart rate test. The blood pressure test takes about 50-55 seconds. The developer can customize the test progress according to this time. The result will be available at the end of each test. value
 开启或者关闭血压测试 血压测试与心率测试不同，血压测试一次大概需要50-55秒时间，开发者可以根据这个时间自定义测试进度，每次测试结束才会有结果，即一次测试只能有一组值
 
 @param start Start and End
 @param testMode The tested mode 0 represents the general mode, 1 represents the private mode, and the default is 0. 测试的模式0代表 通用模式，1代表私人模式，默认传0
 @param testBloodResultBlock Callback of test results including test status, test progress, high and low voltage values 测试结果的回调 包括测试状态、测试进度、高低压值
 */
- (void)veepooSDKTestBloodStart:(BOOL)start testMode:(NSUInteger)testMode testResult:(void(^)(VPTestBloodState testBloodState, NSUInteger testBloodProgress, NSUInteger highBlood, NSUInteger lowBlood))testBloodResultBlock;


/**
 The fatigue test is turned on and off. The fatigue test is the same as the blood pressure test. That is, there is only one set of values when not tested. The difference is that the device gives the progress of the fatigue test.
 开启和关闭疲劳度测试，疲劳度的测试和血压测试原理相同，即没测试一次最后只有一组值，不同的是设备给出了疲劳度测试的进度
 
 @param start Start and End
 @param testFatigueResultBlock
 The callback of the test results, the test return results include the test status, test progress, and test results. The test results are rated at 1-4. The corresponding levels are non-fatigue, mild fatigue, general fatigue, severe fatigue.
 测试结果的回调，测试返回结果包含测试状态、测试进度、和测试结果，测试结果等级为1-4分别对应的等级为 不疲劳、轻度疲劳、一般疲劳、重度疲劳
 */
- (void)veepooSDKTestFatigueStart:(BOOL)start testResult:(void(^)(VPTestFatigueState testFatigueState,NSUInteger testProgress, NSUInteger fatigueValue))testFatigueResultBlock;

/**
 Turning the ECG test on or off, and finding the abnormal end state during the test means that the test has ended. The ECG test is a dynamic test process. There are multiple result callbacks during the test. After the user finishes testing, you must call this method to end. test
 开启或者关闭ECG测试，在测试过程中发现异常结束状态都代表此次测试已经结束，ECG测试是一个动态测试过程，测试过程中会有多个结果回调，用户测试完毕后要主动调用此方法结束测试
 
 @param start Start and End
 @param testECGResultBlock Callback of test results
 */
- (void)veepooSDKTestECGStart:(BOOL)start testResult:(void(^)(VPTestECGState testECGState, NSUInteger testProgress, VPECGTestDataModel *testModel))testECGResultBlock;

//Send the mobile phone pairing command. When the device is successfully connected, the system will have a pop-up window for the user to select whether the device is paired with the mobile phone. If the user chooses to cancel, if you want to pair with the mobile phone during the connection process, you can send this command. There is no callback for this command. When the transmission is successful, the system will pop up the window to the user. Note: If the device and phone are already configured with this command, it is invalid.
//发送与手机配对指令，当设备连接成功后，系统会有一个弹窗让用户选择设备是否与手机配对，如果用户选择了取消，如果在连接过程中想与手机配对，则发送这个命令就可以了，此命令没有回调，当发送成功后系统会有弹窗给用户, 注意：如果设备和手机已经配对此命令无效

- (void)veepooSDKSendPairedWithIphoneCommand;


/**
 Set female features
 设置女性功能
 
 @param femaleModel Female project model 女性项目的model
 @param settingMode Setting mode 0 means off 1 means on 2 representative reading device female information 设置模式0代表关闭 1代表开启 2代表读设备女性信息
 @param settingFemaleResultBlock Set or read successfully 设置或者读取成功
 @param settingFemaleFailureBlock Set or read failed 设置或者读取失败
 */
- (void)veepooSDKSettingDeviceFemaleWithFemaleModel:(VPDeviceFemaleModel *)femaleModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceFemaleModel *deviceFemaleModel))settingFemaleResultBlock failureResult:(void(^)(void))settingFemaleFailureBlock;

/**
 Set countdown
 设置倒计时
 
 @param countDownModel
 Countdown Model, you can't nil at any time, you can initialize it when you read it.
 倒计时Model，任何时候不能nil，读取的时候给你初始化的就可以
 @param settingMode
 Setting mode 0 means canceling the countdown currently in progress, 1 means setting, 2 means reading
 设置模式0代表取消当前正在进行的倒计时、1代表设置、2代表读取
 @param settingCountDownResultBlock Set a successful callback 设置成功的回调
 @param settingCountDownFailureBlock Set failed callbacks 设置失败的回调
 */
- (void)veepooSDKSettingDeviceCountDownWithCountDownModel:(VPDeviceCountDownModel *)countDownModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceCountDownModel *countDownModel))settingCountDownResultBlock failureResult:(void(^)(void))settingCountDownFailureBlock;

/**
 Set or read a new alarm
 设置或者读取新闹钟
 
 @param alarmModel The model of the new alarm clock, can not be empty, the default when reading 新闹钟的Model，不能为空，读取的时候传默认
 @param settingMode 0 means delete this group of alarms, 1 means set (increase or modify) 2 means read 0代表删除这组闹钟，1代表设置（增加或者修改）2代表读取
 @param settingNewAlarmResultBlock Set or read successfully, return all current alarms 设置或者读取成功，返回当前所有的闹钟数
 @param settingNewAlarmFailureBlock Setting or reading an alarm failed 设置或者读取闹钟失败
 */
- (void)veepooSDKSettingDeviceNewAlarmWithNewAlarmModel:(VPDeviceNewAlarmModel *)alarmModel settingMode:(NSUInteger)settingMode successResult:(void(^)(NSArray *alarmArray))settingNewAlarmResultBlock failureResult:(void(^)(void))settingNewAlarmFailureBlock;


/**
 Screen style setting, first get the range of screen style settings according to screenTypes in VPPeripheralModel. If it is 3, you can set 1-3. If it is 0, it does not have this function.
 屏幕风格设置，先根据VPPeripheralModel中的screenTypes获取屏幕风格设置的区间，如果为3代表可以设置1-3，如果为0代表没有此功能

 @param screenStyle Set the style, the interval is [1 screenTypes], when the reading is 0 设置的样式，区间为【1 screenTypes】，读取的时候传0
 @param settingMode 1 stands for setting, 2 stands for reading 1代表设置，2代表读取
 @param settingScreenStyleResultBlock
 Callback after setting, including setting success or failure and setting the style of the bracelet end
 设置后的回调，包括设置成功或者失败及设置后手环端的样式
 */
- (void)veepooSDKSettingDeviceScreenStyle:(int)screenStyle
                              settingMode:(NSUInteger)settingMode
                                   result:(void(^)(int screenStyle, BOOL settingSuccess))settingScreenStyleResultBlock DEPRECATED_MSG_ATTRIBUTE("Please use veepooSDKSettingDeviceScreenStyle:settingMode:dialType:result:");

/**
 Screen style setting, first get the range of screen style settings according to screenTypes in VPPeripheralModel. If it is 3, you can set 1-3. If it is 0, it does not have this function.
 屏幕风格设置，先根据VPPeripheralModel中的screenTypes获取屏幕风格设置的区间，如果为3代表可以设置1-3，如果为0代表没有此功能

 @param screenStyle Set the style, the interval is [1 screenTypes], when the reading is 0 设置的样式，区间为【1 screenTypes】，读取的时候传0
 @param settingMode 1 stands for setting, 2 stands for reading 1代表设置，2代表读取
 @param dialType 表盘类型
 @param settingScreenStyleWithDialTypeBlock
 Callback after setting, including setting success or failure and setting the style of the bracelet end
 设置后的回调，包括设置成功或者失败及设置后手环端的样式
 */
- (void)veepooSDKSettingDeviceScreenStyle:(int)screenStyle
                              settingMode:(NSUInteger)settingMode
                                 dialType:(VPDeviceDialType)dialType
                                   result:(void(^)(VPDeviceDialType dialType,int screenStyle, BOOL settingSuccess))settingScreenStyleWithDialTypeBlock;

/**
 Set the duration of the bright screen
 设置亮屏时长
 
 @param durationModel Set the screen duration model, you can read it without nil 设置屏幕时长模型，读取的时候不为nil就可以
 @param settingMode 1 stands for setting, 2 stands for reading 1代表设置，2代表读取
 @param settingResult Successful callback after setting 设置后成功的回调
 @param failureResult Failed callback 失败的回调
 */
- (void)veepooSDKSettingScreenDuration:(VPScreenDurationModel *)durationModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPScreenDurationModel *DurationModel))settingResult failureResult:(void(^)(void))failureResult;

/**
 Set the apnea reminder, this is a reminder that there is only one switch to replace the apnea when the blood oxygen type is 4.
 设置呼吸暂停提醒，这个是血氧类型为4的时候取代呼吸暂停只有一个开关的提醒
 
 @param remindModel Set the apnea reminder model 设置呼吸暂停提醒模型
 @param settingMode 1 stands for setting, 2 stands for reading 1代表设置，2代表读取
 @param successResult success
 @param failureResult failure
 */
- (void)veepooSDKSettingOxygenApneaRemind:(VPOxygenApneaRemindModel *)remindModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPOxygenApneaRemindModel *oxygenApneaRemindModel))successResult failureResult:(void(^)(void))failureResult;


/**
 Set and read the sport mode
   The normal use of this interface is to ensure that the current state is being operated each time the setting is turned on or off.
 设置和读取运动模式
 此接口正常的使用方式是，每次设置开启或者关闭的时候要确保当前的状态在做操作

 @param settingType
 0 is to turn off the sport mode, 1 is to turn on the sport mode, 2 is to read the current device sport mode
 0是关闭运动模式，1是开启运动模式，2是读取当前设备运动模式
 @param runningMode
 For specific reference enumeration, if not multi-motion is given to 0, the way to judge multi-motion is described in the runningType attribute of VPPeripheralModel.
 具体参考枚举, 如果不是多运动给0, 判断多运动的方式见VPPeripheralModel下的runningType属性说明
 @param runningResultBlock
 Set and read the results, The runningType is 0 for not in the sport mode, 1 for the sport mode, 2 for the other busy state, and 3 for the active mode to notify the App when the sport mode ends the connection state. This parameter is only used for reference when reading or setting fails, or in motion. When ending the active report
      settingSuccess Set or read successfully. If it fails, you can refer to the runningType type to see the reason. If the sport mode is already on, turn it back on, it will fail, or the device is doing other operations.
  设置和读取结果， runningType为0代表不在运动模式下，1代表运动模式中，2代表其他忙碌状态,3代表运动模式结束连接状态下主动告知App,此参数只有在读取或者设置失败的时候做参考，或者在运动结束主动上报的时候用
    settingSuccess 设置或读取是否成功，如果失败，可以参考runningType类型来看一下原因，如运动模式已经开启，再次开启，就会失败，或者设备在做其他操作
 */
- (void)veepooSDKSettingDeviceRunning:(int)settingType runMode:(VPDeviceRuningMode)runningMode result:(void(^)(int runningType, BOOL settingSuccess))runningResultBlock;


/**
 Set or read low power
 设置或读取低功耗

 @param settingMode
 Set the type, first read first, if you do not read the direct setting on or off may fail
 设置类型, 第一次要先读取, 如果不读直接设置开或关可能会失败
 @param lowPowerResultBlock Return result
 */
- (void)veepooSDKSettingLowPowerSettingMode:(VPSettingFunctionState)settingMode result:(void(^)(VPSettingFunctionCompleteState settingState))lowPowerResultBlock;

//Clear the data, the bracelet will automatically shut down after clearing the data, can not monitor whether the clear is successful, the shutdown will disconnect from the App
//清除数据，清除数据后手环会自动关机，不能监听是否清除成功，关机后会与App断开连接
- (void)veepooSDKClearDeviceData;

#pragma mark - 设置功能的有无, 特殊开发者使用
- (void)veepooSDKSettingFunction:(VPOperationFuctionType)fuctionType settingType:(VPOperationType)settingType result:(void(^)(VPSettingFunctionCompleteState settingState))settingResult;


#pragma mark - Simple reading method, suitable for stand-alone version, data can be directly extracted from the SDK database after reading, by subclass VPPeripheralManage
#pragma mark 简易的读取方式，适用于单机版本，读取完成之后可直接从SDK的数据库中提取数据，由子类VPPeripheralManage实现

//Start reading all data
//开始读取所有数据
- (void)veepooSdkStartReadDeviceAllDataWithReadStateChangeBlock:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;

//Read the step data. Call each time to get the number of steps in the current bracelet, used internally by the SDK.
//读取计步数据 调用每次获取当前手环的步数，SDK内部使用
- (void)veepooSdkSendStepCommand;

/**
 Start reading motion data
 开始读取运动数据
 
 @param readDeviceRunningBlock Read callbacks for successful or failed motion data 读取运动数据成功或者失败的回调
 */
- (void)veepooSDKStartReadDeviceRunningData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalTimes, NSUInteger currentReadTimes, NSUInteger readCurrentTimesProgress))readDeviceRunningBlock;

//Start reading blood oxygen data
//开始读取血氧数据
- (void)veepooSdkStartReadDeviceOxygenData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;

//Start reading Hrv data
//开始读取Hrv数据
- (void)veepooSdkStartReadDeviceHrvData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;

//Start reading Temperature data
//开始读取体温数据
- (void)veepooSdkStartReadDeviceTemperatureData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;

#pragma mark - It is suitable for storing data by itself. It is more flexible in the development process, and the data is stored by itself. It is suitable for data uploading server and multi-account multi-handle development. It is implemented by subclass VPPeripheralAddManage, temporarily not implemented.
#pragma mark 适用于自己存储数据，开发过程中比较灵活，数据自己存储，适用于数据上传服务器和多账号多手环开发，由子类VPPeripheralAddManage实现
//特别说明：VPPeripheralAddManage此代理中设计到字典里边的key最好在自己程序中先写成全局常量，因不涉及到数据库等所以后边可能会根据具体情况改变，自己代码也最好不要获取数据后直接保存，最好自己转一下符合自己公司的key在保存，这样后边SDK改变，对应自己的程序只需要改变全局常量即可了
/**
 Read the count data for a certain day
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


/// 读取自动测量的体温数据
/// @param dayNumber 代表哪一天0代表今天，1代表昨天，2代表前天，不能大于saveDays
/// @param maxPackage 一天的数据比较多，每次读取可以从选择的包数读取，仅当天有效
/// @param readDeviceTemperatureDataBlock 回调函数
- (void)veepooSDK_readDeviceAutoTestTemperatureDataWithDayNumber:(NSInteger)dayNumber maxPackage:(NSInteger)maxPackage result:(void (^)(NSArray *oneDayTempDataArray ,NSInteger totalPackage, NSInteger currentReadPackage))readDeviceTemperatureDataBlock;

#pragma mark - Dial Channel
// SDK 内部使用
- (void)veepooSDK_peripheralIsReadyToSendWriteWithoutResponseBlock:(void(^)(CBPeripheral *peripheral))block;

/// 表盘设置和读取接口
/// @param model 模式
/// @param dialType 类型
/// @param photoDialModel 照片表盘的模型 仅在 VPDialChannelModelSetupPhotoDial 模式下需要
/// @param result 回调函数，VPDialChannelModelSetupPhotoDial 模式下无效 不同的模式使用不同的模型
/// @param transformProgress 传输进度回调函数
- (void)veepooSDK_dialChannelWithChannelModel:(VPDialChannelModel)model
                                     dialType:(VPDeviceDialType)dialType
                               photoDialModel:(VPPhotoDialModel *)photoDialModel
                                       result:(void (^)(VPPhotoDialModel *photoDialModel, VPDeviceMarketDialModel *deviceMarketDialModel, NSError *error))result
                            transformProgress:(void (^)(double progress))transformProgress;

#pragma mark - search device function

/// 手机查找手环功能
/// @param open 开启or关闭
/// @param result 设备状态回调
- (void)veepooSDK_searchDeviceFuntionWithState:(BOOL)open result:(void (^)(BOOL open, VPSearchDeviceFunctionState state))result;

#pragma mark - gps 和 诵经

/// GPS和时区设置
/// @param model 传入的模型
/// @param result 结果，state 为0表示不支持，1成功 2失败
- (void)veepooSDK_setDeviceGPSAndTimezoneWithModel:(VPDeviceGPSModel *)model result:(void (^)(NSInteger state))result;


/// 诵经计数数据读取
/// @param timestamp 时间戳 读取哪个时间戳之后的数据
/// @param result 诵经结果 单包或多包
- (void)veepooSDK_readHadjCountWithTimestamp:(long)timestamp result:(void (^)(VPDeviceHadjCountModel *model))result;



/// 克尔白经纬度设置
/// @param model 传入的模型
/// @param result 结果 0表示不支持 1表示成功 2代表失败
- (void)veepooSDK_setKAABAGPSWithModel:(VPDeviceKAABAGPSModel *)model result:(void (^)(NSInteger state))result;


/// 设备克尔白经纬度实际上报
/// @param open 开启/关闭 上报
/// @param result 回调
- (void)veepooSDK_readDeviceRTGPSDataWithState:(BOOL)open result:(void (^)(BOOL start, VPDeviceKAABAGPSModel *model))result;


/// AGPS数据传输 先通过 peripheralModel.agpsFunction 判定是否支持AGPS功能
/// @param fileUrl 星历文件（rtcm 格式）
/// @param timestamp 星历文件生成时间戳（网站获取）
/// @param result 结果，使用UI传输的方式所以 photoDialModel和deviceMarketDialModel无效，仅error有用
/// @param transformProgress 数据传输进度
- (void)veepooSDK_AGPSTransformWithFileUrl:(NSURL *)fileUrl
                                 timestamp:(long)timestamp
                                    result:(void(^)(VPPhotoDialModel *photoDialModel, VPDeviceMarketDialModel *deviceMarketDialModel, NSError *error))result
                         transformProgress:(void (^)(double progress))transformProgress;

/// 设备主动要求APP(SDK)下发GPS数据  调用示例可参考SDK配套的Demo
/// @param block  回调函数，自身包含一个block参数，下发时使用这个参数进行下发
/// state 0x01 表示设备要求App 开始 下发GPS数据
///     0x02 表示设备要求App 结束 下发GPS数据
///
/// 嵌套的block
/// ackState 同 state 状态一致
/// GPSState  0x01 表示App GPS状态正常，model 的数据有效，可定时下发GPS数据
///         0x02 表示App GPS信号弱， model的数据有效
///         0x03 表示App GPS权限未开启， model的数据无效，SDK不会触发下发数据操作
/// model 海拔高度(altitude) 属性无效，其它属性有效
- (void)veepooSDK_sendGPSDataToDeviceWithBlock:(void(^)(NSInteger state, void(^sendTask)(NSInteger ackState, NSInteger GPSState, VPDeviceGPSModel *model)))block;

#pragma mark - 体温功能

/// 手动测量体温
/// @param start 开启/关闭
/// @param result 回调函数
///   state 表示状态
///   enable 参数表示设备是否正忙
///   progress表示测量进度
///   tempValue表示体温值的10倍(单位摄氏度)
- (void)veepooSDK_temperatureTestStart:(BOOL)start result:(void (^)(VPTemperatureTestState state, BOOL enable, NSInteger progress, NSInteger tempValue))result;


@end







