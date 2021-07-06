//
//  VPPeripheralModel.h
//  VPBleSdk
//
//  Created by 张冲 on 17/1/11.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "VPLowPowerModel.h"
#import "VPDialModel.h"

@interface VPPeripheralModel : NSObject

#pragma mark - Attribute value obtained at scan time 扫描时候获取的属性值

//Bluetooth device, developers don't need
//蓝牙设备，开发者不用
@property (strong, nonatomic, readonly) CBPeripheral *peripheral;

//The name of the device, displayed in the scanned list
//设备的名字，扫描的列表中显示

@property (nonatomic, strong, readonly) NSString *deviceName;

//Device address, password verification may change after successful verification, displayed in the scanned list
//设备地址，密码验证成功之后可能会改变，扫描的列表中显示
@property (nonatomic, strong, readonly) NSString *deviceAddress;

//The signal of the device can be sorted in the list by this signal. The larger the rssi value, the better the signal, generally the negative number.
//设备的信号，可以通过此信号，在列表中排序，rssi值越大信号越好，一般是负数
@property (nonatomic, strong) NSNumber *RSSI;

//过滤规则
@property (nonatomic, assign, readonly) BOOL deviceFilter;

#pragma mark - Attribute value obtained after connection and password verification succeeded 连接并密码验证成功后获取的属性值

//Device number, developers don't need
//设备编号，开发者不用
@property (nonatomic, assign, readonly) NSUInteger deviceNumber;

//The display version of the device, telling the user that the current version is less
//设备的显示版本，告知用户当前的版本是多少
@property (nonatomic, strong, readonly) NSString *deviceVersion;

//The device test version, which is used when the developer calls it, notifies the specific version of the current test, and does not display it to the client.
//设备测试版本，开发者调用的时候要使用，告知当前测试的具体版本，不给客户显示
@property (nonatomic, strong, readonly) NSString *deviceTestVersion;

//设备功能的数据包含的功能数据结构如A702010202000102020000000000000000000000共计20个字节的Data，从第二个字节，即下标为1开始，依次代表血压、饮酒、久坐、无用（无用但是占位了）、微信运动、拍照、疲劳度、血氧、安卓信息提醒包数、心率报警、翻腕亮屏、女性项目、屏幕调节亮度、C3指令（安卓用）、手环精度标志、高端血压（动态校准血压模式）、新的闹钟功能（没有就用老的闹钟,0xFE表示手环彻底没有闹钟功能）、心率功能（因后加1带表没有、0代表有）每个位置0代表没有此功能，1代表有此功能（特殊除外）
@property (nonatomic, strong) NSData *deviceFuctionData;

//SDK1.7开始新增属性-----设备功能的数据包含的功能数据结构如A702010202000102020000000000000000000000共计20个字节的Data，从第二个字节，即下标为1开始，依次代表倒计时功能、日常数据读取天数（开发者不用）、信息推送备注包数（） 数后边预留每个位置0代表没有此功能，1代表有此功能（特殊除外）
@property (nonatomic, strong) NSData *deviceFuctionDataTwo;

@property (nonatomic, strong) NSData *deviceFuctionDataThird;

//Judge the device to save a total of several days of data
//设备一共保存几天的数据
@property (nonatomic, assign) UInt8 saveDays;

//Whether the device has a sport mode, store it a few times
//设备是否有运动模式,存储几次
@property (nonatomic, assign) NSInteger runningSaveTimes;

//This field represents the type of motion mode, 0 for single motion, 1 for 10 multiple motions, to determine if there is a sport mode with runningSaveTimes field, if nonzero for motion mode
//此字段代表运动模式的类型, 0代表是单运动, 1代表有10种多运动, 判断是否有运动模式用runningSaveTimes这个字段, 如果非0代表有运动模式
@property (nonatomic, assign) NSInteger runningType;

//判断是否是新协议读取方式
@property (nonatomic, assign) BOOL stepChangeNewMode;

//The device can set several screen styles, mainly color screen items, and 0 means no screen style setting function.
//设备可以设置几种屏幕风格，主要是彩屏项目，0代表没有屏幕风格设置功能
@property (nonatomic, assign) NSUInteger screenTypes;

//Height in equipment data
//设备资料中的身高
@property (nonatomic, assign) NSUInteger deviceStature;

//Bright screen duration type 0 means no, 1 means there is this function
//亮屏时长类型0代表没有，1代表有此功能
@property (nonatomic, assign) NSUInteger screenDurationType;

//设备ANCS信息提醒包含的功能数据结构如AD02010202000102020000000000000000000000共计20个字节的Data，前两个字节是头和设置及读取，从第三个字节，即下标为2开始，依次代表来电、短信、wechat、QQ、Sina、Facebook、Twitter、Flickr、LinkedIn、whatsApp、Line、Instagram、Snapchat、Skype、钉钉、企业微信，后边的带开发，每个位置0代表没有此功能，1代表开启此提醒，2代表关闭此提醒，最后一位是其他应用（除了上述之外的其他有通知的App），图标显示默认公共图标，0代表没有此功能，1代表开启此提醒，2代表关闭此提醒
// 下标19的高4位表示包号（第一包为0x00） 低4位表示 其它， 如果打开其它，则下标19应为0x01(高4位:0b0000,低4位:0b0001)
@property (nonatomic, strong) NSData *deviceAncsData;

// AD02010202000102020000000000000000000010
// ANCS第二包 前两个字节是头和设置及读取 从第三个字节，即下标为2开始，依次代表 tiktok、telegram、connected2、、、 下标19的高4位表示包号（0x10表示第二包）
@property (nonatomic, strong) NSData *deviceAncsDataTwo;

//设备开关的提醒状态包含的功能数据结构如B802010202010102020000000000000000000000前两个字节是头和设置及读取，从第三个字节，即下标为2开始，依次代表公英制、24小时制式、心率自动检测、血压自动检测、运动量过量提醒、心率血压血氧语音播报、手机查找、秒表功能、血氧过低通知、LED灯档位（1代表正常肤色档位、2代表黑色皮肤档位），HRV夜间自动检测，来电免接听，蓝牙断链提醒，SOS页面显示, PPG自动测量, 科学睡眠自动检测(这个暂时无用, 关闭科学睡眠用的是PPG自动测量)，每个位置0代表没有此功能，1代表开启此提醒，2代表关闭此提醒
@property (nonatomic, strong) NSData *deviceSwitchData;

//设备开关(第二个数据包)的提醒状态包含的功能数据结构如B802010202010102020000000000000000000001前两个字节是头和设置及读取，从第三个字节，即下标为2开始，依次代表公长按解锁、消息亮屏, 每个位置0代表没有此功能，1代表开启此提醒，2代表关闭此提醒
@property (nonatomic, strong) NSData *deviceSwitchTwoData;

//Drinking status and whether there is drinking data 0 means no drinking, other representatives have several drinking
//饮酒状态及是否有饮酒数据 0代表没有饮酒，其他的代表有几次饮酒
@property (nonatomic, assign) NSUInteger drinkState;

//The following states are all 0 means no, 1 means open, 2 means closed.
//下边的几个状态都是0代表没有，1代表开启，2代表关闭
@property (nonatomic, assign) NSUInteger raiseHandState;//抬手亮屏幕（夜间转腕）
@property (nonatomic, assign) NSUInteger lostRemindState;//设备防丢失
@property (nonatomic, assign) NSUInteger wearMonitoringState;//佩戴检测

//Device password
//设备的密码
@property (nonatomic, strong) NSString *devicePassword;

//Non-zero means blood oxygenation
//非0代表有血氧功能呢
@property (nonatomic, assign) NSInteger oxygenType;

//Blood oxygen automatic detection switch status
//血氧自动检测开关状态
@property (nonatomic, assign) NSInteger oxygenAutoDetectType;

//Non-zero means that there is hrv function
//非0代表有hrv功能
@property (nonatomic, assign) NSInteger hrvType;

//0 stands for normal sleep and 1 stands for precise sleep
//0代表普通睡眠,1代表精准睡眠
@property (nonatomic, assign) NSInteger sleepType;

//0 generation does not have this function, 1 means E series, 2 means G series
//0代没有此功能,1代表E系列,2代表G系列
@property (nonatomic, assign) NSInteger ecgType;

//0 means the device is not in PTT mode, 1 means the device is in PTT mode
//0代表设备未处于PTT模式下, 1代表设备正处于PTT模式下
@property (nonatomic, assign) NSInteger pttState;

//主动上报数据, 内部使用
@property (nonatomic, assign) NSData *reportData;

//Basic data type
//基本数据类型
@property (nonatomic, assign) NSInteger fiveProtocolType;

//Respiratory rate test function 0 generation is not, 1 means there is
//呼吸率测试功能 0代没有,1代表有
@property (nonatomic, assign) NSInteger resRateType;

//Low power type 0 generation is not, 1 means there is
//低功耗类型 0代没有,1代表有
@property (nonatomic, assign) NSInteger lowPowerType;

//Whether there is weather data, if 1 means there is, if not 1 means no
//是否有天气数据，如果1代表有，如果非1代表没有
@property (nonatomic, assign) NSInteger weatherType;

//普通表盘个数
@property (nonatomic, assign) NSUInteger dialCount;

//市场表盘个数
@property (nonatomic, assign) NSUInteger marketDialCount;

//照片表盘个数
@property (nonatomic, assign) NSUInteger photoDialCount;

// AGPS功能 1代表有 0表示没有
@property (nonatomic, assign) NSInteger agpsFunction;

@property (nonatomic, strong) VPDialModel *dialModel;

//手机查找手环功能 0代表没有，1代表有
@property (nonatomic, assign) NSUInteger searchDeviceFunction;

//体温功能 0表示没有 1有体温但无自动测量 2有体温且有自动测量
@property (nonatomic, assign) NSUInteger temperatureType;

#pragma mark - Property value obtained when new firmware is found 发现新固件的时候获得的属性值
//Device network upgrade version, when the user receives a new firmware version, tell the user what version of the upgrade is
//设备网络升级版本，当用户收到有新固件版本的时候，告知用户升级的版本是多少
@property (nonatomic, strong) NSString *deviceNetVersion;

//Device upgrade update version description, multiple descriptions are separated by $, and multiple descriptions can be split by $
//设备升级更新版本描述，多个描述以$这个符号分隔，可以通过$进行拆分多个描述
@property (nonatomic, strong) NSString *deviceNetVersionDes;

//Low power model
//低功耗模型
@property (nonatomic, strong) VPLowPowerModel *lowPowerModel;

//Initialize the model through the broadcast package, sdk internal use
//通过广播包初始化模型，sdk内部使用
- (instancetype)initWithPeripher:(CBPeripheral*)peripher advertisementData:(NSDictionary*)advertisementData RSSI:(NSNumber *)RSSI;

//Initialize the model by getting the connected device, sdk internal use
//通过获取已连接的设备初始化模型，sdk内部使用
- (instancetype)initWithPeripher:(CBPeripheral*)peripher;

//Change the attribute value after successful password verification, sdk internal use
//密码验证成功后改变属性值 ，sdk内部使用
- (void)setPropertyValueWithPasswordData:(NSData *)passData;


@end







