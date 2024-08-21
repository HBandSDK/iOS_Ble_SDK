# VeepooSDK iOS API 文档

| 版本  | 修改内容                                                     | 修改日期   |
| ----- | ------------------------------------------------------------ | ---------- |
| 1.0.0 | SDK初版                                                      | 2023.05.15 |
| 1.0.1 | 添加语言设置文档                                             | 2023.06.06 |
| 1.0.2 | 添加公英制单位切换、12/24小时切换、以及其他个性化设置文档    | 2023.06.26 |
| 1.0.3 | 添加部分功能状态监听接口、新增127种运动枚举、体温支持获取原始温度(体表温度)、支持自扫描连接、添加设备时间设置接口等 | 2023.08.24 |
| 1.0.4 | 添加获取设备充电状态和电量接口                               | 2023.09.07 |
| 1.0.5 | 表盘传输和OTA添加电池电量限制等相关描述                      | 2023.09.11 |
| 1.0.6 | 添加身体成分、血液成分、血糖多校准、联系人SOS设置、ECG离线存储等相关文档 | 2023.10.31 |
| 1.0.7 | 添加血糖风险等级、体温整合到日常数据接口中相关文档           | 2024.04.15 |

# SDK初始化

## [VPBleCentralManager sharedBleManager]

* VPBleCentralManager: SDK主入口
* sharedBleManager: 获取单例对象，SDK接口以单例形式存在

* 先初始化VPBleCentralManage，也可以在主控制器中初始化，总之在使用蓝牙功能前初始化

**注意⚠️，SDK内部数据接口不支持并发操作，例如读取日常数据的过程中，不支持操作设备的开关状态。出现并发情况，无法保证指令操作的正常响应。应用层需自行考虑并发场景下的交互逻辑处理。**

**注意⚠️，iOS因为系统原因，允许多个应用同时连接同一个外围设备，如果您的手机中存在H Band或SDK DEMO，请勿同时连接同一个设备，可能回触发读取数据的死循环，引起异常。**

设备端自动测量产生的数据，可以通过SDK的相关接口将这些数据读取到APP端。读取这些自动测量产生的数据，SDK提供了两套方式，一种是SDK内部的DB持久化，用户调用 **【日常数据读取接口】等** 完成之后，从DB中获取持久化的数据对象。另一种是直接通过接口读取数据，由SDK外部自行进行持久化操作。

建议使用SDK持久化的方式，集成难度较低，大多数客户都选择该种方式。

SDK持久化方式：

```swift
// VPPeripheralManage
VPBleCentralManage.sharedBleManager().peripheralManage = VPPeripheralManage.shareVPPeripheralManager()
```

应用层自行持久化方式：

```swift
// VPPeripheralAddManage
VPBleCentralManage.sharedBleManager().peripheralManage = VPPeripheralAddManage.shareVPPeripheralManager()
```



## SDK版本号获取

`VPPublicDefine.h -> VeepooBleSDKVersion`



# 扫描设备

### 前提

当确保手机系统蓝牙开启的状态下，如果进入扫描设备扫描界面调用如下代码，扫描到设备后会有设备模型的回调，一个设备可能会被扫描到多次，所以展示的时候要根据模型VPPeripheralModel的设备地址属性deviceAddress进行重复性过滤，可以根据模型的属性值进行用户展示

 ### 类名

  `VPBleCentralManager`

### 接口

```objective-c
- (void)veepooSDKStartScanDeviceAndReceiveScanningDevice:(ReceiveScanningDevice)scanningDevice;
```

### 参数解释

| 参数           | 参数类型                                     | 备注     |
| -------------- | -------------------------------------------- | -------- |
| scanningDevice | void(^）(VPPeripheralModel *peripheralModel) | 设备模型 |

### 自定义扫描

当需要集成多家SDK场景时，无法使用内部扫描情况下使用。

参数`CBPeripheral` 由外界的 `CBCentralManager` 实现扫描委托方法中得到，相关代码可以参考Demo中的`VPCustomScanManage` 类

内部会重新执行扫描，扫到相同UUID的 `CBPeripheral` 才发起连接

```objective-c
///自行实现扫描连接设备时使用，适合集成多家SDK场景，连接状态使用：VPBleConnectStateChangeBlock
///不可与 {@link veepooSDKConnectDevice:deviceConnectBlock:} 混用
- (void)veepooSDKSelfScanConnectDevice:(CBPeripheral *)peripheral
                    deviceConnectBlock:(DeviceConnectBlock)connectBlock;
```



# 停止扫描

### 前提

* 当确保手机系统蓝牙开启的状态下，如果离开扫描界面、准备连接设备以及其他需要停止扫描的情况下，务必调用此接口

 ### 类名

  `VPBleCentralManager`

### 接口

```objective-c
- (void)veepooSDKStopScanDevice;
```

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().veepooSDKStopScanDevice()
```



# 连接设备

### 前提

当确保手机系统蓝牙开启的状态下

### 类名

`VPBleCentralManager`

### 接口

```objective-c
- (void)veepooSDKConnectDevice:(VPPeripheralModel *)peripheralModel deviceConnectBlock:(DeviceConnectBlock)connectBlock;
```

### 参数解释

| 参数            | 参数类型                                 | 备注         |
| --------------- | ---------------------------------------- | ------------ |
| peripheralModel | VPPeripheralModel                        | 外设模型     |
| connectBlock    | void(^)(DeviceConnectState connectState) | 回调连接状态 |

```objc
typedef NS_ENUM(NSInteger, DeviceConnectState) {
    BlePoweredOff = 0,//蓝牙没有打开
    BleConnecting = 1,//蓝牙连接中
    BleConnectSuccess = 2, //蓝牙连接成功
    BleConnectFailed = 3, //蓝牙连接失败
    BleVerifyPasswordSuccess = 4,//验证密码成功
    BleVerifyPasswordFailure = 5,//验证密码失败
};
```

# 断开连接

### 前提

* 断开连接，不再自动连接，人为断开连接SDK不再负责帮助自动重连

 ### 类名

  `VPBleCentralManager`

### 接口

```objective-c
- (void)veepooSDKDisconnectDevice;
```

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().veepooSDKDisconnectDevice()
```



# 读取设备电池电量

特别注意⚠️：表盘传输和OTA过程会有较大功耗，需要增加电量限制。手表电量很低时，如果发起表盘传输，在传输过程中手表可能会因低电关机，重新充电后，表盘会变黑。 建议每次传输前，先读取一遍手表当前电量，如果电量状态为低电，则禁止传输。

OTA过程较长，建议电池电量在30%以上，才允许升级。

### 前提

设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**`

### 接口

```objc
// 读取设备的电池电量
- (void)veepooSDKReadDeviceBatteryInfo:(void(^)(BOOL isPercent, BOOL percenTypeIsLowBat, NSUInteger battery))deviceBatteryInfoBlock;

// 带充电状态的接口
- (void)veepooSDKReadDeviceBatteryAndChargeInfo:(void(^)(BOOL isPercent, VPDeviceChargeState chargeState, BOOL percenTypeIsLowBat, NSUInteger battery))deviceBatteryInfoBlock
```

### 参数解释

| 参数               | 参数类型   | 备注                                                         |
| ------------------ | ---------- | ------------------------------------------------------------ |
| isPercent          | BOOL       | 表示电量是否为百分比                                         |
| percenTypeIsLowBat | BOOL       | 表示isPercent为真的情况下，设备是否为低电状态；              |
| battery            | NSUInteger | 电池电量，如果为百分比电量，则范围为[0, 100] 否则表示电池的格数，[0, 4] |

| 参数        | 参数类型            | 备注                           |
| ----------- | ------------------- | ------------------------------ |
| chargeState | VPDeviceChargeState | 设备充电状态，枚举类型详见下方 |

```objective-c
// 设备的充电状态
typedef NS_ENUM(NSUInteger, VPDeviceChargeState) {
    VPDeviceChargeStateNormal = 0,      // 设备在正常使用，没有充电
    VPDeviceChargeStateCharging,        // 充电中
    VPDeviceChargeStateLowPressure,     // 低压状态，已被废弃
    VPDeviceChargeStateFull             // 充满状态，不可靠
};
```

### 示例代码

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKReadDeviceBatteryInfo { isPercent, percenTypeIsLowBat, battery in
            let str = isPercent ? "电量" : "电压"
            let percentSign = isPercent ? "%" : ""
            weakSelf.vpDeviceBatteryLevelLabel.text = "电池" + str + ":" + String(battery) + percentSign
        }
```

带充电状态的示例

```swift
veepooBleManager.peripheralManage.veepooSDKReadDeviceBatteryAndChargeInfo { [weak self]isPercent, chargeState, percenTypeIsLowBat, battery in
            let str = isPercent ? "电量" : "电压"
            var state = "正常使用"
            if chargeState == .charging {
                state = "充电中"
            }
            if chargeState == .full {
                state = "已充满"
            }
            print("充电状态：\(state)")
            let percentSign = isPercent ? "%" : ""
            self?.vpDeviceBatteryLevelLabel.text = "电池" + str + ":" + String(battery) + percentSign
        }
```

# 同步个人信息到设备

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

###  接口

身高体重的设置，会影响卡路里的计算结果

```objective-c
- (void)veepooSDKSynchronousPersonalInformation:(VPSyncPersonalInfo *)personalInfo result:(void(^)(NSUInteger settingResult))synchronousPersonalInformationBlock;
```

### 参数解释

|     参数     |             参数类型              |                             备注                             |
| :----------: | :-------------------------------: | :----------------------------------------------------------: |
| personalInfo |        VPSyncPersonalInfo         | 需要同步的个人信息Model，具体释义如下， 建议本地存储一份用户数据，每次信息变更或者设备连接时同步给设备 |
|    result    | void(^)(NSUInteger settingResult) |   settingResult = 1时 代表设置成功，其余情况则代表设置失败   |

```objective-c
@interface VPSyncPersonalInfo : NSObject

//身高， 单位cm
@property(nonatomic, assign) int status;

//体重， 单位kg
@property(nonatomic, assign) int weight;

//年龄 (current yeart - birth year） 当前年 - 用户出生年
@property(nonatomic, assign) int age;

//性别 0代表 female， 1代表male
@property(nonatomic, assign) int sex;

//目标步数 单位步（step）
@property(nonatomic, assign) int targetStep;

//目标睡眠时长 单位分钟（minute）要确认项目中是否有这个功能，如果没有也可以设置
@property(nonatomic, assign) int targetSleepDuration;

@end
```

### 示例代码

```swift
public func synchoronusPersonlInfo(personalInfo: UserModel, result: ((Bool) -> Void)?) {
    guard bleCentralM.isConnected else {
        return
    }
    vpPeripheralManager.veepooSDKSynchronousPersonalInformation(personalInfo.vpSyncPersonalInfo) { settingResult in

        result?(settingResult == 1 ? true : false)
    }
}
```



# 设置设备语言

设置语言，如果设备上没有的语言，则默认显示英语。

建议使用自动SDK跟随手机语言设置。

如果使用此接口务必将 `VPBleCentralManage`中的`systemLanguage`此值设为 **NO**

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
- (void)veepooSDKSettingLanguage:(UInt8)languageType result:(void(^)(BOOL success))settingLangueResult;
```

### 参数解释

|        参数         |       参数类型        |                             备注                             |
| :-----------------: | :-------------------: | :----------------------------------------------------------: |
|    languageType     |         UInt8         | 中文(1) 英文(2) 日语(3) 韩语(4) 德语(5) 俄语(6) 西班牙(7) 意大利(8) 法语(9) 越南语(10) 葡萄牙语(11) 中文繁体(12) 泰语(13) 波兰(14) 瑞典(15) 土耳其(16) 荷兰语(17) 捷克语(18) 阿拉伯(19) 匈牙利(20) 希腊(21) 罗马尼亚(22) 斯洛伐克(23) 印尼语(24) 巴西葡萄牙语(25) 克罗地亚(26) 立陶宛亚(27) 乌克兰(28) 印地语(29) 希伯来语(30) 丹麦语(31) 波斯语(32) 芬兰语(33) 马来语(34) |
| settingLangueResult | void(^)(BOOL success) |                        设置的回调结果                        |



#  设备公英制单位切换与读取

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 参数解释

|         参数         |            参数类型             |                             备注                             |
| :------------------: | :-----------------------------: | :----------------------------------------------------------: |
|   baseFunctionType   | VPSettingBaseFunctionSwitchType |                     传入VPSettingMetric                      |
|     settingState     |     VPSettingFunctionState      | 公制：传入VPSettingFunctionOpen   英制：传入VPSettingFunctionClose                           读取：传入VPReadFunctionState |
| settingCompleteBlock | VPSettingFunctionCompleteState  |              设置或者读取某个功能完成之后的状态              |

```objective-c
typedef NS_ENUM(NSInteger, VPSettingFunctionCompleteState) {//设置某个功能完成之后的状态
    VPFunctionCompleteUnknown = 0, //设备没有此功能
    VPFunctionCompleteOpen = 1,//（公制）
    VPFunctionCompleteClose = 2,//（英制）
    VPFunctionCompleteFailure = 3,//设置或者读取失败
    VPFunctionCompleteComplete = 4,//设置完成，针对Data设置的回复
};
```

### 使用举例

```swift
   peripheralM.baseFunctionType(type: .metric, settingState: .init(rawValue: (preferenceM.preference.metricImperialUnit.rawValue + 1)) ?? .settingFunctionOpen, completeBlock: nil)
```





# 设备12/24小时切换与读取

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 参数解释

|         参数         |            参数类型             |                             备注                             |
| :------------------: | :-----------------------------: | :----------------------------------------------------------: |
|   baseFunctionType   | VPSettingBaseFunctionSwitchType |                   传入VPSettingTimeFormat                    |
|     settingState     |     VPSettingFunctionState      | 24小时：传入VPSettingFunctionOpen   12小时：传入VPSettingFunctionClose                           读取：传入VPReadFunctionState |
| settingCompleteBlock | VPSettingFunctionCompleteState  |                  设置某个功能完成之后的状态                  |

```objective-c
typedef NS_ENUM(NSInteger, VPSettingFunctionCompleteState) {//设置某个功能完成之后的状态
    VPFunctionCompleteUnknown = 0, //设备没有此功能
    VPFunctionCompleteOpen = 1,//（24小时）
    VPFunctionCompleteClose = 2,//（12小时）
    VPFunctionCompleteFailure = 3,//设置或者读取失败
    VPFunctionCompleteComplete = 4,//设置完成，针对Data设置的回复
};
```

### 使用举例

```swift
 peripheralM.baseFunctionType(type: .timeFormat, settingState: .init(rawValue: sysHourFormat.rawValue) ?? .settingFunctionOpen, completeBlock: nil)
```

# 设备时间设置

### 前提

* 设备已经连接

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
/// 同步时间，特殊情况使用，默认连接的时候会自动同步时间
/// @param year 年份
/// @param month 月份 1-12
/// @param day 日 1-31
/// @param hour 小时 0-23
/// @param min 分钟 0-59
/// @param sec 秒 0-59
/// @param system 0不设置 1是12小时 2是24小时 如果无用则需要通过开关设置中的制式再设置一遍
/// @param result 失败/成功结果回调，内部会置空
- (void)veepooSDKSettingTimeWithYear:(int)year
                               month:(int)month
                                 day:(int)day
                                hour:(int)hour
                              minute:(int)min
                              second:(int)sec
                          timeSystem:(int)system
                              result:(void(^)(BOOL success))result;
```

```objective-c
/// 同步手机当前时间给设备，时间参数由SDK内部自行获取手机当前数据
/// 本接口不可与 {@link veepooSDKSettingTimeWithYear:month:day:hour:minute:second:timeSystem:result:} 共用
/// 本接口时间制式设置无效，设置时间制式请调用 {@link veepooSDKSettingBaseFunctionType:settingState:completeBlock:}
/// @param result 失败/成功结果回调，内部会置空
- (void)veepooSDKSettingTimeWithResult:(void(^)(BOOL success))result;
```

### 参数解释

无

### 使用举例

```swift
veepooBleManager.peripheralManage.veepooSDKSettingTime(withYear: 2023, month: 08, day: 15, hour: 18, minute: 00, second: 00, timeSystem: 0) { success in
            print(success)
        }
```

```swift
veepooBleManager.peripheralManage.veepooSDKSettingTime { success in
            print(success)
        }
```

# 设备其他个性化设置与读取

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

设备端状态变更监听

```objective-c
/// 设备端开关状态变更主动上报回调
@property (nonatomic, copy) void(^deviceFunctionSwitchDidChangeBlock)(void);
```

### 参数解释

|         参数         |            参数类型             |                  备注                  |
| :------------------: | :-----------------------------: | :------------------------------------: |
|   baseFunctionType   | VPSettingBaseFunctionSwitchType |       各项个性化设置，枚举值如下       |
|     settingState     |     VPSettingFunctionState      |    设置或者读取某个功能，枚举值如下    |
| settingCompleteBlock | VPSettingFunctionCompleteState  | 设置某个功能完成之后的状态，枚举值如下 |

#### VPSettingBaseFunctionSwitchType

备注栏里标 "/" 的，settingState传VPSettingFunctionOpen 为 打开此功能，传VPSettingFunctionClose为关闭此工功能，其他特殊情况见非"/" 备注

|                参数                |                        释义                         |                             备注                             |
| :--------------------------------: | :-------------------------------------------------: | :----------------------------------------------------------: |
|         VPSettingRaiseHand         |                   设置抬手亮屏幕                    |                              /                               |
|        VPSettingDeviceLose         |                     设备防丢失                      |                              /                               |
|       VPSettingWearDetection       |                      佩戴检测                       |                              /                               |
|      VPSettingAutomaticHRTest      |                  设置自动心率检测                   |                              /                               |
|      VPSettingAutomaticBPTest      |                  设置自动血压检测                   |                              /                               |
|         VPSettingExercise          |       设置运动量过量提醒，主要用在耳机项目上        |                              /                               |
|    VPSettingVoiceAnnouncements     |   心率、血压、血氧等语音播报，主要用在耳机项目上    |                              /                               |
|   VPSettingSearchPhoneInterFace    |          设置搜索手机界面是否在手环上显示           |                              /                               |
|    VPSettingStopwatchInterFace     |            设置秒表界面是否在手环上显示             |                              /                               |
|     VPSettingOxygenLowerRemind     |                 设置血氧过低后警告                  |                              /                               |
|         VPSettingLedGrade          | 设置Led灯的等级，关闭是黑人档位，开启是正常肤色档位 |                              /                               |
|     VPSettingAutomaticHRVTest      |           设置HRV夜间自动检测开关是否开启           |                              /                               |
|        VPSettingAutoAnswer         |           设置来电自动接听开关，耳机有效            |                              /                               |
|     VPSettingDisconnectRemind      |                    设置断链提醒                     |                              /                               |
|         VPSettingSOSRemind         |                SOS，类似查找手机功能                |                              /                               |
|     VPSettingAutomaticPPGTest      |         脉率自动检测开关,主要是ECG手环使用          |                              /                               |
|       VPSettingAccurateSleep       |                    精准睡眠开关                     | 暂时无效, 目前使用VPSettingAutomaticPPGTest这个控制, 关闭的同时精准睡眠也会被关闭 |
|       VPSettingMusicControl        |                      音乐控制                       |                              /                               |
|      VPSettingLongpressUnlock      |                      长按解锁                       |                              /                               |
|    VPSettingMessageScreenLight     |                      消息亮屏                       |                              /                               |
| VPSettingAutomaticTemperatureTest  |                  体温自动检测开关                   |                              /                               |
|      VPSettingTemperatureUnit      |                    体温单位设置                     |                   1表示摄氏度 2表示华氏度                    |
|      VPSettingECGNormallyOpen      |                    ECG 常开功能                     |                              /                               |
| VPSettingAutomaticBloodGlucoseTest |                  血糖自动检测开关                   |                              /                               |
|            VPSettingMet            |                    梅脱功能开关                     |                              /                               |
|          VPSettingStress           |                    压力功能开关                     |                              /                               |
|     VPSettingBloodGlucoseUnit      |                    血糖单位设置                     |                    1表示mmol/L 2表示mg/dl                    |
|    VPSettingAutomaticOxygenTest    |                  血氧夜间自动检测                   |                              /                               |

#### VPSettingFunctionState

```objective-c
typedef NS_ENUM(NSInteger, VPSettingFunctionState) {//设置获取读取某个功能
    VPReadFunctionState = 0, //读取某个功能的开关和有无
    VPSettingFunctionOpen = 1,//打开某个功能
    VPSettingFunctionClose = 2,//关闭某个功能
    VPSettingFunctionCancel = 3,//现在仅动态血压校准有效
    VPSettingFunction = 4,//设置某个功能
};

```

#### VPSettingFunctionCompleteState

```objective-c
typedef NS_ENUM(NSInteger, VPSettingFunctionCompleteState) {//设置某个功能完成之后的状态
    VPFunctionCompleteUnknown = 0, //设备没有此功能
    VPFunctionCompleteOpen = 1,//此功能已经打开 
    VPFunctionCompleteClose = 2,//此功能已经关闭
    VPFunctionCompleteFailure = 3,//设置或者读取失败
    VPFunctionCompleteComplete = 4,//设置完成，针对Data设置的回复
};
```

### 使用举例

```swift
 @objc func baseFunctionOpenOrCloseRemindAction(sender: UISwitch)  {//开始设置信息提醒的开关功能
        if VPBleCentralManage.sharedBleManager().isConnected == false {
            print();
            _ = AppDelegate.showHUD(message: "设备未连接,设置失败", hudModel: MBProgressHUDModeText, showView: view)
            self.perform(#selector(settingBaseFunctionRemindFarilure(sender:)), with: sender, afterDelay: 0.5)
            return
        }
         VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingBaseFunctionType(VPSettingBaseFunctionSwitchType(rawValue: sender.tag)!, settingState: VPSettingFunctionState(rawValue: sender.isOn ? 1 : 2)!) {[weak self] (settingFunctionCompleteState) in
            if self == nil {
                return
            }
            switch settingFunctionCompleteState {
            case .functionCompleteUnknown:
                _ = AppDelegate.showHUD(message: "没有此功能", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
                fallthrough
            case .functionCompleteFailure:
                self?.perform(#selector(self?.settingBaseFunctionRemindFarilure(sender:)), with: sender, afterDelay: 0.5)
                _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            case .functionCompleteOpen:
                _ = AppDelegate.showHUD(message: "设置成功，已经开启", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            case .functionCompleteClose:
                _ = AppDelegate.showHUD(message: "设置成功，已经关闭", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            case .functionCompleteComplete:
                _ = AppDelegate.showHUD(message: "设置完成闭", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            }
        }
    }
```





# 计步数据获取

指的是设备的计步、距离和卡路里，本接口返回的数据是实时的，与日常数据中的步数有差别，日常数据中的步数是每5分钟的汇总体现，存在滞后性。如果应用层需要同步获取设备端的步数，需要固定频率调用本接口获取数据。

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

SDK持久化方式：

```objective-c
// 
+ (void)veepooSDKGetStepDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID changeUserStature:(NSUInteger)userStature result:(void(^)(NSDictionary *stepDict))resultBlock;
```

应用层自行持久化方式：

```objc
// 如果是当天的数据，设备一直在产生数据，需要应用层自行控制读取的时机。非当天的数据是幂等的，每次读取都是一样的结果，应用层可以自行持久化，已持久化数据避免重复获取。
// dayNumber代表哪一天0代表今天，1代表昨天，2代表前天，不能大于VPPeripheralModel中属性saveDays的值
- (void)veepooSDK_readStepDataWithDayNumber:(NSInteger)dayNumber result:(void(^)(NSDictionary *stepDict))readStepBlock;
```

### 回调参数解释

|    参数     |   参数类型   |                             备注                             |
| :---------: | :----------: | :----------------------------------------------------------: |
|  queryDate  |   NSString   |                要查询的日期，格式为yyyy-MM-dd                |
|   tableID   |   NSString   |           查询数据的ID 传想要获取数据设备的MAC地址           |
| userStature |  NSUInteger  | 用户的身高，通过此参数把步数转换为距离和卡路里，身高要和传给设备的个人信息一致，设备默认身高为175 |
| resultBlock | NSDictionary |    返回的格式以具体的名称为key 具体的数值为value 格式如下    |

```objective-c
{
 Step = 5000;//一天总的步数
 Dis = 80.00;//转换后的距离单位为km
 Cal = 1600.0;//转换后的卡路里单位为kcal（千卡）
}
```

### 示例代码

```swift
 /// 获取手环当前的计步数据，与设备的显示的计步数据同步
    @objc func startRealTimeStep() {
        if veepooBleManager.isConnected == false {
            return
        }
        if stepTimer == nil {
            stepTimer = Timer.scheduledTimer(timeInterval: 5.0, target: self, selector: #selector(self.startRealTimeStep), userInfo: nil, repeats: true)
        }
        unowned let weakSelf = self
        VPDataBaseOperation .veepooSDKGetStepData(withDate: 0.getOneDayDateString(), andTableID: veepooBleManager.peripheralModel.deviceAddress, changeUserStature: veepooBleManager.peripheralModel.deviceStature) { (stepDict) in
            
            guard  let deviceStepDict = stepDict  else {
                return
            }
            if deviceStepDict["Step"] != nil && deviceStepDict["Dis"] != nil && deviceStepDict["Cal"] != nil {
                weakSelf.vpDeviceCurrentStepLabel.text = "实时步数:" + (deviceStepDict["Step"] as! String) + "  " + (deviceStepDict["Dis"] as! String) + "km  " + (deviceStepDict["Cal"] as! String) + "kcal  "
            }
        }
    }
```



# 日常数据读取功能

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

简易的读取方式，适用于单机版本，读取完成之后可直接从SDK的数据库中提取数据

```objective-c
- (void)veepooSdkStartReadDeviceAllDataWithReadStateChangeBlock:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock;
```

### 回调参数解释

|          参数          |         参数类型          |                    备注                    |
| :--------------------: | :-----------------------: | :----------------------------------------: |
|       readState        | VPReadDeviceBaseDataState | 读取设备基本数据的状态变化，所有枚举值如下 |
|        totalDay        |        NSUInteger         |            设备保存了数据的天数            |
|  currentReadDayNumber  |        NSUInteger         |             当前读取的天数下标             |
| readCurrentDayProgress |        NSUInteger         |             当前天数的读取进度             |

```objective-c
typedef NS_ENUM(NSInteger, VPReadDeviceBaseDataState) {//读取设备基本数据的状态变化
    VPReadDeviceBaseDataIdle = 0, // 未开始读取状态
    VPReadDeviceBaseDataStart = 1, //开始读取数据
    VPReadDeviceBaseDataReading = 2, //读取中
    VPReadDeviceBaseDataComplete,//读取全部完成
    VPReadDeviceBaseDataInvalid,//SDK不提供使用
};
```

### 示例代码

```swift
//验证密码成功后开始读取手环的数据（睡眠、计步、心率、血压、血氧值、血糖、血液成分等基本数据）
//体温类型为5时，也在本接口中触发读取
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSdkStartReadDeviceAllData {[weak self] (readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress) in
    switch readDeviceBaseDataState {
    case .start: //开始读取数据
        hud.show(true)
        hud.labelText = "开始读取"
    case .reading://正在读取数据
        let progressString: String = String(currentReadDayNumber) + "/" + String(totalDay) + "  " + String(readCurrentDayProgress) + "%"
        hud.labelText = progressString
    case .complete://读取数据完成
        hud.labelText = "读取完成"
        hud.hide(true, afterDelay: 1.0)
        self?.readOxygenData()
    default:
        break
    }
}
```



# 心率功能

## 判断设备是否有心率功能

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

```objective-c
@property (nonatomic, strong) NSData *deviceFuctionData;
```

### 示例代码

```swift
  if let data = model?.deviceFuctionData {

      if data[18] != 1 {

        result.append(.heartRate)

  }
```





## 心率测量 

### 前提

* 设备已连接且支持该功能
* 全部日常数据读取完毕后进行测量否则设备会报设备正忙的错误回调
* 开启或者关闭心率测试，在测试过程中发现异常结束状态都代表此次测试已经结束，心率测试是一个动态测试过程，测试过程中会有多个结果回调，用户测试完毕后要主动调用此方法结束测试

### 类名

`VPPeripheralBaseManage` 

获取途径：**[VPBleCentralManage sharedBleManager].peripheralManage**

### 接口

```objective-c
- (void)veepooSDKTestHeartStart:(BOOL)start testResult:(void(^)(VPTestHeartState testHeartState, NSUInteger heartValue))testHeartResultBlock;
```

### 参数解释

| 参数                 | 参数类型                                                     | 备注                                                         |
| -------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| start                | BOOL                                                         | 开启或者关闭心率测试，在测试过程中发现异常结束状态都代表此次测试已经结束，心率测试是一个动态测试过程，测试过程中会有多个结果回调，用户测试完毕后要主动调用此方法结束测试 |
| testHeartResultBlock | void(^)(VPTestHeartState testHeartState, NSUInteger heartValue) | VPTestHeartState: 测试心率过程中的状态变化，heartValue: 测量到的瞬时心率值 |

```objective-c
typedef NS_ENUM(NSInteger,VPTestHeartState) {//测试心率过程中的状态变化
    VPTestHeartStateStart = 0,//开始检测心率，还没有测出结果
    VPTestHeartStateTesting = 1,//正在检测心率，已经测出心率值
    VPTestHeartStateNotWear = 2,//佩戴检测没有通过，测试已经结束
    VPTestHeartStateDeviceBusy = 3,//设备正忙不能测试了，测试已经结束
    VPTestHeartStateOver = 4,//测试正常结束，人为结束
};
```



## 获取心率原始数据

### 前提

*  设备已连接且支持该功能
* 调用日常数据读取完成之后，从SDK数据库中获取心率数据

### 类名

 `VPDataBaseOperation`

### 接口

```objective-c
+ (NSDictionary *)veepooSDKGetOriginalDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

获取某一天原始数据 一般是每隔5分钟或者10分钟的 如果间隔时间长就是在设备中没有读取到数据，原始数据主要作为数据分析，保存到自己的服务器，一般不给用户展示

### 参数解释

| 参数      | 参数类型 | 备注                                     |
| --------- | -------- | ---------------------------------------- |
| queryDate | NSString | 要查询的日期 格式为2017-02-09            |
| tableID   | NSString | 查询数据的ID 传想要获取数据设备的MAC地址 |

### 返回数据

```objc
{
 "10:40" = {
 diastolic = 0;//高压值
 systolic = 0;//低压值
 heartValue = 0;//心率值
 sportValue = 17;//运动量
 stepValue = 0;//步数
 calValue = 0;//卡路里
 disValue = 0;//距离
 ppgs = [数组]; //使用的时, 如果有heartValue用heartValue,如果没有则优先使用ecgs,如果heartValue和ecgs都没有就用ppgs, ppgs和ecgs是这个时间段的心率数组
 ecgs = [数组];
 };
 "10:45" = {
 diastolic = 0;
 systolic = 0;
 heartValue = 0;
 sportValue = 25;
 stepValue = 0;
 calValue = 0;
 disValue = 0;
 ppgs = [数组]; 
 ecgs = [数组];
 };
 }
```



## 获取半小时心率平均值数据

### 前提

* 设备已连接且支持该功能

* 调用日常数据读取完成之后，从SDK数据库中获取心率数据

### 类名

`VPDataBaseOperation`

### 接口

> 半小时心率获取，注意不同的设备自动测量心率的频率不一样，频率最高的情况为一分钟一次，本接口返回的是所有心率数据处理成每半小时心率平均值的字典数组。

```objective-c
+ (NSDictionary *)veepooSDKGetOriginalChangeHalfHourDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```



### 参数解释

| 参数      | 参数类型 | 备注                                     |
| --------- | -------- | ---------------------------------------- |
| queryDate | NSString | 要查询的日期 格式为2017-02-09            |
| tableID   | NSString | 查询数据的ID 传想要获取数据设备的MAC地址 |

### 返回数据

> 特别说明: 心率平均值：10：30 就是10：30-11：00的平均值 11：00就是11：00-11：30的平均值，运动量和步数是半小时内所有值累加的

```objc
{
 "10:30" = {
 heartValue = 0;//半小时心率平均值
 sportValue = 108;//半小时运动量累加值
 stepValue = 0;//半小时计步数累加值
 calValue = 0;//半小时卡路里累加值
 disValue = 0;//半小时距离累加值
 };
 "11:00" = {
 heartValue = 0;
 sportValue = 33;
 stepValue = 0;
 calValue = 0;//半小时卡路里累加值
 disValue = 0;//半小时距离累加值
 };
 }
```

### 使用举例



## 心率自动监测开关设置

### 前提

设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 参数解释

| 参数                 | 参数类型                                              | 备注                       |
| -------------------- | ----------------------------------------------------- | -------------------------- |
| baseFunctionType     | VPSettingBaseFunctionSwitchType                       | 要设置和读取的信息类型     |
| settingState         | VPSettingFunctionState                                | 设置还是读取               |
| settingCompleteBlock | void(^)(VPSettingFunctionCompleteState completeState) | 设置某个功能完成之后的状态 |

### 示例代码

```swift
 VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingBaseFunctionType(.automaticHRTest, settingState: .readFunctionState) { [weak self] state in
        if state == .functionCompleteUnknown || state == .functionCompleteFailure {
            monitorHeight = 0
        } else {
            self?.monitorSW.isOn = state == .functionCompleteOpen
        }

    }
```



##  设置和读取心率报警数据

### 前提

设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingDeviceHeartAlarmWithHeartAlarmModel:(VPDeviceHeartAlarmModel *)heartAlarmModel settingMode:(NSUInteger)settingMode successResult:(void(^)(VPDeviceHeartAlarmModel *heartAlarmModel))settingHeartAlarmResultBlock failureResult:(void(^)(void))settingHeartAlarmFailureBlock;
```

### 参数解释

| 参数                          | 参数类型                                          | 备注                                                         |
| ----------------------------- | ------------------------------------------------- | ------------------------------------------------------------ |
| heartAlarmModel               | VPDeviceHeartAlarmModel                           | 心率报警模型 (ps: 当settingMode为2 时 传入VPDeviceHeartAlarmModel()) |
| settingMode                   | NSUInteger                                        | 设置心率报警的模式0代表**关闭** 1代表**开启** 2代表**读取**设备心率报警信息 |
| settingHeartAlarmResultBlock  | void(^)(VPDeviceHeartAlarmModel *heartAlarmModel) | 读取和设置成功后的回调                                       |
| settingHeartAlarmFailureBlock | void(^)(void)                                     | 读取和设置失败的回调                                         |

### 示例代码

```swift
    
    // MARK: - 心率提醒
    /// 读取设备心率提醒数据
    public func getHeartRate(successResult: @escaping ((VPDeviceHeartAlarmModel?) -> Void), failureResult: @escaping (() -> Void)) {
        vpPeripheralManager.veepooSDKSettingDeviceHeartAlarm(with: VPDeviceHeartAlarmModel(), settingMode: 2, successResult: successResult, failureResult: failureResult)
    }
    
    /// 设置设备心率提醒数据
    /// - Parameters:
    ///   - model: 心率提醒model
    public func setHearRate(model: VPDeviceHeartAlarmModel, successResult: @escaping ((VPDeviceHeartAlarmModel?) -> Void), failureResult: @escaping (() -> Void)) {
        vpPeripheralManager.veepooSDKSettingDeviceHeartAlarm(with: model, settingMode: model.isOpen ? 1 : 0, successResult: successResult, failureResult: failureResult)
    }
    
```



# 体温功能
## 判断设备是否有体温功能

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

> 体温功能  0: 表示没有  1: 有体温但无自动测量  2/4/5: 有体温且有自动测量
>
> 体温类型5的自动测量数据读取被整合到日常数据读取中了，不需要调用单独的接口去触发读。

```objective-c
@property (nonatomic, assign) NSUInteger temperatureType;
```





## 手动体温测量功能

### 前提

* 设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDK_temperatureTestStart:(BOOL)start result:(void (^)(VPTemperatureTestState state, BOOL enable, NSInteger progress, NSInteger tempValue, NSInteger originalTempValue))result;
```

### 参数解释

| 参数   | 参数类型                                                     | 备注              |
| ------ | ------------------------------------------------------------ | ----------------- |
| start  | Bool                                                         | YES 开启/ NO 关闭 |
| result | void (^)(VPTemperatureTestState state, BOOL enable, NSInteger progress, NSInteger tempValue, NSInteger originalTempValue) | 结果回调          |

### 回调参数解释

| 参数              | 参数类型               | 备注                                                     |
| ----------------- | ---------------------- | -------------------------------------------------------- |
| state             | VPTemperatureTestState | YES 开启/ NO 关闭                                        |
| enable            | BOOL                   | 参数表示设备是否正忙                                     |
| progress          | NSInteger              | 表示测量进度（0~100）                                    |
| tempValue         | NSInteger              | 表示体温值的10倍(单位摄氏度)                             |
| originalTempValue | NSInteger              | 表示原始温度值的10倍(单位摄氏度)，对应H Band中的体表温度 |

```objective-c
// 体温手动测试/自动监测开关状态
typedef NS_ENUM(NSUInteger, VPTemperatureTestState) {
    VPTemperatureTestStateUnsupported, // 不支持体温监测功能
    VPTemperatureTestStateOpen, // 体温监测打开
    VPTemperatureTestStateClose, // 体温监测关闭
};
```



## 读取设备体温数据

### 前提

* 读取数据完成后存储在数据库中，直接从数据库中拿数据
* 注意⚠️不要与hrv/血氧/日常数据等并发读取
* 体温类型(temperatureType)为5时，不支持本接口

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSdkStartReadDeviceTemperatureData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalDay, NSUInteger currentReadDayNumber, NSUInteger readCurrentDayProgress))readStateChangeBlock{}
```

### 回调参数解释

| 参数                   | 参数类型                  | 备注                  |
| ---------------------- | ------------------------- | --------------------- |
| readState              | VPReadDeviceBaseDataState | 枚举定义如下代码      |
| totalDay               | NSUInteger                | 设备保存体温的天数    |
| currentReadDayNumber   | NSUInteger                | 当前读取的天数        |
| readCurrentDayProgress | NSUInteger                | 当天读取进度（0~100） |

```objective-c
typedef NS_ENUM(NSInteger, VPReadDeviceBaseDataState) {//读取设备基本数据的状态变化
    VPReadDeviceBaseDataIdle = 0, // 未开始读取状态
    VPReadDeviceBaseDataStart = 1, //开始读取数据
    VPReadDeviceBaseDataReading = 2, //读取中
    VPReadDeviceBaseDataComplete,//读取全部完成
    VPReadDeviceBaseDataInvalid,//SDK不提供使用
};
```



##   获取设备某一天的体温自动测量数据

### 前提

* 设备已连接且支持体温功能

* 体温读取数据完成后存储在数据库中，直接从数据库中拿数据

### 类名

`VPDataBaseOperation`

### 接口

```objective-c
+ (NSArray *)veepooSDKGetDeviceTemperatureDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

### 参数解释

| 参数      | 参数类型 | 备注                              |
| --------- | -------- | --------------------------------- |
| queryDate | NSString | 要查询的日期格式为2021-06-07      |
| tableID   | NSString | 设备的mac地址，获取哪个设备的数据 |

### 返回数据

```objective-c
 /* 获取一天体温自动测量数据的数组，数组内是每5分钟的字典，格式如下
 NSDictionary *dataDic =  {
 VPDeviceTemperatrueDataMonthKey: month, 月份
 VPDeviceTemperatrueDataDayKey: day, 日
 VPDeviceTemperatrueDataHourKey: hour, 小时
 VPDeviceTemperatrueDataMinuteKey: minute, 分钟
 VPDeviceTemperatrueDataValueKey: value, 温度值（摄氏度）
 VPDeviceTemperatrueDataOriginalValueKey: riginalValue, 体表温度值（摄氏度）皮肤温度
 }
 */
```





## 体温单位切换

### 前提

* 设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 参数解释

| 参数                 | 参数类型                                              | 备注                                            |
| -------------------- | ----------------------------------------------------- | ----------------------------------------------- |
| baseFunctionType     | VPSettingBaseFunctionSwitchType                       | 功能类型， 传入此枚举值VPSettingTemperatureUnit |
| settingState         | VPSettingFunctionState                                | 设置或者读取某个功能，所有枚举值如下            |
| settingCompleteBlock | void(^)(VPSettingFunctionCompleteState completeState) | 回调中的状态枚举值如下                          |

```objective-c
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
```



## 体温自动监测开关

### 前提

* 设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 参数解释

| 参数                 | 参数类型                                              | 备注                                                     |
| -------------------- | ----------------------------------------------------- | -------------------------------------------------------- |
| baseFunctionType     | VPSettingBaseFunctionSwitchType                       | 功能类型， 传入此枚举值VPSettingAutomaticTemperatureTest |
| settingState         | VPSettingFunctionState                                | 设置获取读取某个功能，所有枚举值如下                     |
| settingCompleteBlock | void(^)(VPSettingFunctionCompleteState completeState) | 回调中的状态枚举值如下                                   |

```objective-c
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
```





# ECG功能

## 判断设备是否支持ECG

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

 `0`：代没有此功能

 `1`：代表**E**系列

 `2`：代表**G**系列

```objective-c
@property (nonatomic, assign) NSInteger ecgType;
```





## ECG PTT(胸口模式)功能

### PTT状态改变监听

#### 前提

* 设备已连接且支持该功能

#### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

#### 接口

```objective-c
- (void)veepooSDKAddPTTStateListener:(void(^)(NSInteger pttState))pttListener;
```

#### 回调参数解释

| 参数     | 参数类型  | 备注                                               |
| -------- | --------- | -------------------------------------------------- |
| pttState | NSInteger | 0代表设备未处于PTT模式下, 1代表设备正处于PTT模式下 |

#### 示例代码

```swift
 //监听设备是否处于PTT模式下
  VPBleCentralManage.sharedBleManager()?
      .peripheralManage.veepooSDKAddPTTStateListener({[weak self] (state) in
      self?.pttStateLabel.text = state == 1 ? "设备已进入PTT模式" : "设备未进入PTT模式"
  })
```



###  PTT数据监听

#### 前提

* 设备已连接且支持该功能

#### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

#### 接口

```objective-c
- (void)veepooSDKPTTTest:(BOOL)start valueBlock:(void(^)(VPPttValueModel *valueModel))valueBlock signalBlock:(void(^)(NSArray <NSNumber *>*signals))signalBlock;
```

#### 参数解释

| 参数  | 参数类型 | 备注                |
| ----- | -------- | ------------------- |
| start | BOOL     | 开启或者关闭PTT测试 |

#### 返回数据

| 参数       | 参数类型        | 备注        |
| ---------- | --------------- | ----------- |
| valueModel | VPPttValueModel | PPT数据     |
| signals    | <NSNumber *>    | PPT信号变化 |

#### 示例代码

```swift
VPBleCentralManage.sharedBleManager()?
    .peripheralManage.veepooSDKPTTTest(sender.isSelected, valueBlock: {[weak self] (valueModel) in
        self?.handleValue(valueModel)
    }, signal: {[weak self] (signals) in
        self?.handleSignals(signals)
    })

 func handleValue(_ model: VPPttValueModel?) {
        switch model!.testState {
        case .normal:
            valueLabel.text = "心率:\(model!.heart)    HRV:\(model!.hrv)    QT:\(model!.qt)"
        case .busy:
            valueLabel.text = "设备在处理其他事情"
        case .leadFail:
            valueLabel.text = "设备导联脱落"
        default:
            valueLabel.text = ""
        }
    }
    
    func handleSignals(_ signals: [NSNumber]?) {
        guard let deviceSignals = signals else {
            return;
        }
        signalLabel.text = ""
        for signal in deviceSignals {
            signalLabel.text = (signalLabel.text)! + "    " +  "\(signal)"
        }
    }
```





## ECG测量


### 前提

* 设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

 开启或者关闭ECG测试，在测试过程中发现异常结束状态都代表此次测试已经结束，ECG测试是一个动态测试过程，测试过程中会有多个结果回调，用户测试完毕后要主动调用此方法结束测试

```objective-c
- (void)veepooSDKTestECGStart:(BOOL)start testResult:(void(^)(VPTestECGState testECGState, NSUInteger testProgress, VPECGTestDataModel *testModel))testECGResultBlock;
```

### 参数解释

| 参数                 | 参数类型                                                     | 备注                                 |
| -------------------- | ------------------------------------------------------------ | ------------------------------------ |
| start                | Bool                                                         | 开启或者关闭ECG测试                  |
| testECGResultBlock   | VPSettingFunctionState                                       | 设置获取读取某个功能，所有枚举值如下 |
| settingCompleteBlock | void(^)(VPTestECGState testECGState, NSUInteger testProgress, VPECGTestDataModel *testModel) | 回调中的参数解释如下                 |

### 回调参数解释

| 参数         | 参数类型           | 备注                                   |
| ------------ | ------------------ | -------------------------------------- |
| testECGState | VPTestECGState     | 测试过程中的状态变化，枚举值如下       |
| testProgress | NSUInteger         | 测试进度（0-100）                      |
| testModel    | VPECGTestDataModel | 测试中的数据返回，注意返回的是全量数据 |

```objective-c
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
```

## ECG设备端离线存储数据获取

设备端离线存储数据读取被穿插带日常数据读取接口中

已连接状态下，SDK有监听设备离线测量完成的接口，可以订阅该接口，在触发回调的同时，去触发日常数据读取接口

### 前提

设备支持ECG离线存储功能

### 类名

`VPDataBaseOperation` && `VPPeripheralBaseManage`

### 接口

```objective-c
/// 获取设备某一天的所有设备端离线存储的ECG数据
/// @param queryDate 要查询的日期格式为2021-06-07
/// @param tableID 设备的mac地址，获取哪个设备的数据
+ (NSArray<VPECGTestDataModel *> *)veepooSDKGetDeviceOffStoreECGWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

设备测量离线存储完成回调接口

```objective-c
/// 设备端测量离线存储ECG功能完成回调
@property (nonatomic, copy) void(^deviceTestOffStoreECGDidFinishBlock)(void);
```

### 参数解释



### 示例代码

```swift
private func subscribe() {
        // 订阅设备端ECG离线测量完成事件
        VPBleCentralManage.sharedBleManager().peripheralManage.deviceTestOffStoreECGDidFinishBlock = {[weak self] in
            // 这里调用读取全部日常数据即可
            self?.reReadAllData()
        }
    }
    
private func reReadAllData() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSdkStartReadDeviceAllData {
            [weak self] (readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress) in
            if readDeviceBaseDataState == .complete {
                print("读取成功")
            }
        }
    }
```



# HRV功能

## 判断设备是否有HRV功能

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

> 非0代表有hrv功能

```objective-c
@property (nonatomic, assign) NSInteger hrvType;
```





## 获取某天的HRV数据

### 前提

* 设备有HRV功能

### 类名

`VPDataBaseOperation`

### 接口

 ```objective-c
 + (NSArray *)veepooSDKGetDeviceHrvDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
 ```

### 参数解释

| 参数      | 参数类型 | 备注                                     |
| --------- | -------- | ---------------------------------------- |
| queryDate | NSString | 要查询的日期 格式为2017-02-09            |
| tableID   | NSString | 查询数据的ID 传想要获取数据设备的MAC地址 |

### 返回数据

```objective-c
// 获取一天hrv数据的数组，数组内是每一分钟的字典，格式如下
NSDictionary *riginalDic = @{
 VPHRVTimeKey:hrvTime, 时间
 VPHRVValueKey:hrvValue, hrv值
 VPHRVTempKey:hrvTemp1, 预留参数
 VPHRVHeartsKey:@[这里是字符串数组，代表一分钟内所有的rr间期值，每一个数乘以10代表一个rr间期值，洛伦兹散点图就是根据这个画的，要把所有分钟的rr间期值组合到一起]
 };
```

### 示例代码

```swift
public func getHRVDataFromDB(date: Date) -> [[String : Any]] {
        guard record.deviceAddress.isNotEmpty else {
            return []
        }
        
        guard let dicArray = VPDataBaseOperation.veepooSDKGetDeviceHrvData(withDate: date.hf.toString(formatter: .yyyy_MM_dd_v), andTableID: record.deviceAddress) as? [[String : Any]] else {
            return []
        }
        return dicArray
    }
```





# 睡眠功能

## 判断设备支持的睡眠功能类型

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

`0`代表普通睡眠  

`1/3`代表精准睡眠

```objective-c
@property (nonatomic, assign) NSInteger sleepType;
```



## 获取某一天的普通睡眠数据

### 前提

* 设备支持普通
* 睡眠功能

### 类名

`VPDataBaseOperation`

### 接口

 获取某一天睡眠的数据 一天可能有多段睡眠如 晚上睡一觉 白天睡一觉 而每一段睡眠又可能有多次的起夜

```objective-c
+ (NSArray *)veepooSDKGetSleepDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

### 参数解释

| 参数      | 参数类型 | 备注                                     |
| --------- | -------- | ---------------------------------------- |
| queryDate | NSString | 要查询的日期 格式为2017-02-09            |
| tableID   | NSString | 查询数据的ID 传想要获取数据设备的MAC地址 |

### 返回数据

```objective-c
 (
 {
 "DEEP_HOUR" = "2.833";//深睡的时间，单位小时
 HeartBasic = 1;//暂时无用
 "LIGHT_HOUR" = "3.667";//浅睡的时间，单位小时
 "SLEEP_LEVEL" = 3;//睡眠等级区间1-5个等级为:差 一般 好 很好 完美,也可以自定义语言
 "SLEEP_TIME" = "2017/02/09 01:15";//睡眠开始时间
 "SLE_HOUR" = 6;//睡眠总的小时，单位小时
 "SLE_MINUTE" = 30;//睡眠总的分钟，单位分钟 SLE_HOUR + SLE_MINUTE 或者 DEEP_HOUR + LIGHT_HOUR 为总的睡眠时间  或者用WAKE_TIME - SLEEP_TIME 选择用哪个计算总的睡眠时间都可以
 "SLE_LINE" = 010000011111111011111111000001110020000001100200000000000001111111111100001100;//深浅睡眠曲线，0代表浅睡 1代表深睡 2代表苏醒起夜  每个值代表5分钟睡眠时间，如第一个0 就是睡眠的头5分钟 第二个1就是头5-10分钟的睡眠 第三个0就是10-15分钟的睡眠 以此类推 根据此字符串 自定义深浅睡眠曲线或者图形
 "WAKE_TIME" = "2017/02/09 03:45";//睡眠结束时间
 WakeUpTime = 0;//每段睡眠的苏醒次数
 }
 {
 "DEEP_HOUR" = "2.833";
 HeartBasic = 1;
 "LIGHT_HOUR" = "3.667";
 "SLEEP_LEVEL" = 3;
 "SLEEP_TIME" = "2017/02/09 04:15";
 "SLE_HOUR" = 6;
 "SLE_MINUTE" = 30;
 "SLE_LINE" = 000000011111111011111111000001110000000001100000000000000001111111111100001100;
 "WAKE_TIME" = "2017/02/09 07:45";
 WakeUpTime = 0;
 }
 )
```





## 获取某一天的精准睡眠数据

### 前提

* 设备支持精准睡眠功能

### 类名

`VPDataBaseOperation`

### 接口

获取某一天睡眠的数据 一天可能有多段睡眠如 晚上睡一觉 白天睡一觉 而每一段睡眠又可能有多次的起夜

```
+ (NSArray <VPAccurateSleepModel *>*)veepooSDKGetAccurateSleepDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID
```

### 参数解释

| 参数      | 参数类型 | 备注                                     |
| --------- | -------- | ---------------------------------------- |
| queryDate | NSString | 要查询的日期 格式为2017-02-09            |
| tableID   | NSString | 查询数据的ID 传想要获取数据设备的MAC地址 |

### 返回数据

```objective-c
@interface VPAccurateSleepModel : NSObject
//Type of sleep, upload A7 command sleep flag(睡眠的类型，上传A7指令睡眠标记位)
@property (nonatomic, strong) NSString *sleepType;
//Sleep time 入睡时间
@property (nonatomic, strong) NSString *sleepTime;
//Wake up time 起床时间
@property (nonatomic, strong) NSString *wakeTime;
//Sleep sign 睡眠标志
@property (nonatomic, strong) NSString *sleepTag;
//get up score 起夜得分
@property (nonatomic, strong) NSString *getUpScore;
//Deep sleep score 深睡得分
@property (nonatomic, strong) NSString *deepScore;
//Sleep efficiency score, efficiency score from night to deep sleep 睡眠效率得分，起夜到深睡的效率得分
@property (nonatomic, strong) NSString *sleepEfficiencyScore;
//Sleeping efficiency score, from the start of sleep to the first time into the deep sleep 入睡效率得分，从开始睡眠到第一次进入深睡的效率
@property (nonatomic, strong) NSString *fallAsleepScore;

//睡眠时长得分
@property (nonatomic, strong) NSString *sleepTimeScore;
//退出睡眠的模式
@property (nonatomic, strong) NSString *exitSleepMode;
//睡眠质量0到4, 依次代表1到5颗星
@property (nonatomic, strong) NSString *sleepQuality;
//起夜次数
@property (nonatomic, strong) NSString *getUpTimes;
//深浅睡眠模式
@property (nonatomic, strong) NSString *deepAndLightMode;
//睡眠总时长，单位分钟
@property (nonatomic, strong) NSString *sleepDuration;
//深睡时间，单位分钟
@property (nonatomic, strong) NSString *deepDuration;
//浅睡时间，单位分钟
@property (nonatomic, strong) NSString *lightDuration;
//起夜时间，单位分钟, 苏醒时长
@property (nonatomic, strong) NSString *getUpDuration;
//其他睡眠时间，单位分钟, 快速眼动期
@property (nonatomic, strong) NSString *otherDuration;
//第一次进入深睡时间，入睡效率
@property (nonatomic, strong) NSString *firstDeepDuration;
//起夜到深睡时间的平均值，睡眠效率
@property (nonatomic, strong) NSString *getUpToDeepAve;
//曲线上一个点代表的时间，单位秒，现在是60s
@property (nonatomic, strong) NSString *onePointDuration;
//精准睡眠类型, 1是精准睡眠, 0是普通睡眠
@property (nonatomic, strong) NSString *accurateType;
//失眠标志
@property (nonatomic, strong) NSString *insomniaTag;
//失眠得分
@property (nonatomic, strong) NSString *insomniaScore;
//失眠次数
@property (nonatomic, strong) NSString *insomniaTimes;
//beginTime开始时间,具体开始入睡多少分钟,endTime结束时间,具体开始入睡多少分钟
@property (nonatomic, strong) NSArray *insomniaRecord;
//睡眠曲线，16进制的字符串，客户端解析的时候在转换成数据流，每两个字节代表一个点(一分钟), 高位在前,低位在后, 其中高3个比特代表睡眠的状态,深睡(0)、浅睡(1)、快速眼动(2)、失眠(3)、苏醒(4) 如0x1000这个数, 取高三位0x1000>>13, 得到的值看是0到4中的哪个。
@property (nonatomic, strong) NSString *sleepLine;

//根据曲线转换的失眠时长
@property (nonatomic, strong) NSString *insomniaDuration;

//这两个字段, 如果lastType == 1 就代表要和上一段睡眠拼接, 如果nextType==1就代表要和下一段睡眠也拼接, 拼接后除了入睡、起床要修改, 曲线要拼接, 其他都用最后一段的
@property (nonatomic, strong) NSString *lastType;
@property (nonatomic, strong) NSString *nextType;
@property (nonatomic, strong) NSString *mac;
@end
```

睡眠曲线解析方法:

`VPAccurateSleepModel`

```objective-c
/* 
 sleepLine 睡眠曲线的解析方法，处理成字典对象，数据结构为
 @{
    @"index": 0, //NSNumber类型 下标，对应第几分钟的数据
    @"type": 0   //NSNumber类型 当前下标的睡眠状态，深睡(0)、浅睡(1)、快速眼动(2)、失眠(3)、苏醒(4)
 }
 注：KH系列没有【快速眼动(2)、失眠(3)】两种状态
 */
- (NSArray<NSDictionary *> *)parseSleepLine;
```




# 表盘功能

## 获取设备各种类型表盘个数

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

```objective-c
// 普通表盘个数
@property (nonatomic, assign) NSUInteger dialCount;

// 市场表盘个数
@property (nonatomic, assign) NSUInteger marketDialCount;

// 照片表盘个数
@property (nonatomic, assign) NSUInteger photoDialCount;
```

>值为0 则代表不支持此功能
>
>比如 marketDialCount =0. 则意味着设备无表盘市场功能





## 表盘设置和读取接口

### 前提

* 设备已连接
* 设备不处于同步日常数据状态

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDK_dialChannelWithChannelModel:(VPDialChannelModel)model
                                     dialType:(VPDeviceDialType)dialType
                               photoDialModel:(VPPhotoDialModel *)photoDialModel
                                       result:(void (^)(VPPhotoDialModel *photoDialModel, VPDeviceMarketDialModel *deviceMarketDialModel, NSError *error))result
                            transformProgress:(void (^)(double progress))transformProgress;
```



### 参数解释

| 参数              | 参数类型                                                     | 备注                                                         |
| ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| model             | VPDialChannelModel                                           | 模式，枚举定义如下                                           |
| dialType          | VPDeviceDialType                                             | 表盘类型,枚举定义如下                                        |
| photoDialModel    | VPPhotoDialModel                                             | 照片表盘的模型 仅在 VPDialChannelModelSetupPhotoDial 模式下需要 |
| result            | void (^)(VPPhotoDialModel *photoDialModel, VPDeviceMarketDialModel *deviceMarketDialModel, NSError *error) | 回调函数，在VPDialChannelModelSetupPhotoDial 模式下无效 不同的模式使用不同的模型 |
| transformProgress | void (^)(double progress)                                    | 传输进度回调函数，仅在VPDialChannelModelSetupPhotoDial时有效 |

```objective-c
typedef NS_ENUM(NSUInteger, VPDialChannelModel) {
    VPDialChannelModelSetup = 1,        // 设置模式 内部用
    VPDialChannelModelRead,             // 读取模式
    VPDialChannelModelSetupPhotoDial,   // 照片表盘设置元素模式
};

typedef NS_ENUM(NSUInteger, VPDeviceDialType) {
    VPDeviceDialTypeDefault = 0,        // 默认烧录表盘
    VPDeviceDialTypeMarket,             // 市场表盘
    VPDeviceDialTypePhoto,              // 照片表盘
};
```

### 回调参数解释

| 参数                  | 参数类型                | 备注             |
| --------------------- | ----------------------- | ---------------- |
| photoDialModel        | VPPhotoDialModel        | 设备照片表盘数据 |
| deviceMarketDialModel | VPDeviceMarketDialModel | 设备市场表盘数据 |
| progress              | double                  | 照片表盘设置进度 |
| error                 | NSError                 | 失败结果回调     |

### 示例代码

```swift
  @IBAction func readPhotoDialDetailInfo(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_dialChannel(with: .read, dialType: .photo, photoDialModel: nil, result: { [weak self](photoDialModel, deviceMarketDialModel, error) in
            self?.photoDialModel = photoDialModel! as VPPhotoDialModel
        }, transformProgress: nil);
    }
```





## 获取 Veepoo 服务器中的市场表盘

### 前提

* 需要提前获取到设备市场表盘数据 VPDeviceMarketDialModel

### 类名

`VPMarketDialManager`

### 接口

```objective-c
- (void)getVeepooServerAllMarketDialsWithDeviceInfo:(VPDeviceMarketDialModel *)model
                                            success:(void(^)(NSArray<VPServerMarketDialModel *> * _Nullable response))success
                                            failure:(void(^)(NSError * _Nullable error, NSInteger errorcode))fairlure
```

### 参数解释

| 参数     | 参数类型                                                     | 备注             |
| -------- | ------------------------------------------------------------ | ---------------- |
| model    | VPDeviceMarketDialModel                                      | 设备市场表盘数据 |
| success  | void(^)(NSArray<VPServerMarketDialModel *> * _Nullable response) | 成功回调         |
| fairlure | void(^)(NSError * _Nullable error, NSInteger errorcode)      | 失败回调         |

### 示例代码

```swift
VPMarketDialManager.share().marketDialManager.getVeepooServerAllMarketDials(withDeviceInfo: deviceMarketDialModel) { [weak self](marketDialArray) in
    guard  let marketDialArray = marketDialArray  else {
        return
    }
    self?.marketDialArray = marketDialArray
    if marketDialArray.count > 0 {
        var str = ""
        for item in marketDialArray {
            str = str.appending("\(item.fileUrl) \n")
        }
        self?.textView.text = str
    }
} failure: { (error, code) in      
```



## 下载市场表盘的bin文件

### 前提

* 需要提前获取指定的`市场表盘模型`以及`设备的读取上来的市场表盘信息`

### 类名

`VPMarketDialManager`

### 接口

```objective-c
- (void)downloadMarketDialBinFileWithModel:(VPServerMarketDialModel *)model
                     deviceMarketDialModel:(VPDeviceMarketDialModel *)deviceMarketDialModel
                                   success:(void(^)(NSURL * _Nullable filePath))success
                                   failure:(void(^)(NSError * _Nullable error, NSInteger errorcode))fairlure;
```



### 参数解释

| 参数                  | 参数类型                                                | 备注                          |
| --------------------- | ------------------------------------------------------- | ----------------------------- |
| model                 | VPServerMarketDialModel                                 | 指定的市场表盘模型            |
| deviceMarketDialModel | VPDeviceMarketDialModel                                 | 设备的读取上来的信息 用来校验 |
| success               | void(^)(NSURL * _Nullable filePath)                     | 成功回调，返回 filePath       |
| fairlure              | void(^)(NSError * _Nullable error, NSInteger errorcode) | 失败回调                      |

### 示例代码

```swift
 VPMarketDialManager.share().downloadMarketDialBinFile(with: marketDialArray.first!, deviceMarketDialModel: deviceMarketDialModel) { [weak self](filePath) in
            self?.filePath = filePath!
            print("下载成功!")
        } failure: { (error, code) in
            
      }
```





## 开始传输市场表盘的bin文件到设备

### 前提

* 需提前获取到 bin 文件的路径
* bin 文件路径 从 downloadMarketDialBinFileWithModel:success:failure:（下载市场表盘bin文件） 中的success回调获取
* 注意⚠️表盘文件的文件名不允许修改，手表底层会进行校验
* 手表电量充足。注意⚠️ 表盘传输需要增加一个异常保护场景：手表电量很低时，如果发起表盘传输，在传输过程中手表可能会因低电关机，重新充电后，表盘会变黑。 我们建议每次传输前，先读取一遍手表当前电量，如果电量状态为低电，则禁止传输。

### 类名

`VPMarketDialManager`

### 接口

```objective-c
- (void)startTransferWithFilePath:(NSURL *)filePath transformProgress:(void(^)(double progress))transformProgress failure:(void(^)(NSError * _Nullable error))fairlure;
```

### 参数解释

| 参数              | 参数类型                           | 备注                                                         |
| ----------------- | ---------------------------------- | ------------------------------------------------------------ |
| filePath          | NSURL                              | bin 文件的路径  从 downloadMarketDialBinFileWithModel:success:failure: 中的success回调获取 |
| transformProgress | void(^)(double progress)           | 传输进度回调                                                 |
| fairlure          | void(^)(NSError * _Nullable error) | 错误回调                                                     |

### 示例代码

```swift
   VPMarketDialManager.share().startTransfer(withFilePath: filePath) { (progress) in
        print("进度: \(progress * 100) %")
    } failure: { (error) in
        if error != nil{
            print(error! as NSError)
        }
    }
```



## 屏幕风格设置与读取

### 前提

* 先根据VPPeripheralModel中的screenTypes获取屏幕风格设置的区间，如果为3代表可以设置1-3，如果为0代表没有此功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```
- (void)veepooSDKSettingDeviceScreenStyle:(int)screenStyle
                              settingMode:(NSUInteger)settingMode
                                 dialType:(VPDeviceDialType)dialType
                                   result:(void(^)(VPDeviceDialType dialType,int screenStyle, BOOL settingSuccess))settingScreenStyleWithDialTypeBlock;
```



### 参数解释

| 参数                                | 参数类型                                                     | 备注                                                       |
| ----------------------------------- | ------------------------------------------------------------ | ---------------------------------------------------------- |
| screenStyle                         | int                                                          | 市场表盘/照片表盘从1开始，默认表盘的从0开始; 读取的时候传0 |
| settingMode                         | NSUInteger                                                   | 1代表设置，2代表读取                                       |
| dialType                            | VPDeviceDialType                                             | 表盘类型：0 默认表盘 1 市场表盘 2 照片表盘                 |
| settingScreenStyleWithDialTypeBlock | void(^)(VPDeviceDialType dialType,int screenStyle, BOOL settingSuccess) | 设置后的回调，包括设置成功或者失败及设置后手环端的样式     |

### 示例代码

```swift
 VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingDeviceScreenStyle(0, settingMode: 2, dialType: .market, result: { [weak self](dialType, screenStyle, settingSuccess) in
//            print("读取>> screenStyle: \(screenStyle), settingSuccess:\(settingSuccess)")
            self?.dialTypeLabel.text = "\(dialType.rawValue) - \(screenStyle)"
        })
```



## 开启杰理的文件系统

### 前提

* K(杰理)系列设备使用，开启杰理的文件系统，外设模型中CPUType==1表示K(杰理)系列

### 类名

`VPMarketDialManager`

### 接口

```objective-c
- (void)openJLDialFileSystemWithAction:(void(^)(BOOL success))action;
```

### 参数解释

| 参数   | 参数类型              | 备注       |
| ------ | --------------------- | ---------- |
| action | void(^)(BOOL success) | 成功或失败 |

### 示例代码

```swift
  func openJLDialFileSystem(result: @escaping ((Bool) -> Void)) {
        VPMarketDialManager.share().openJLDialFileSystem { isOpen in
            result(isOpen)
        }
    }
```



## 获取杰里文件系统中的文件列表

### 前提

* K(杰理)系列设备使用，外设模型中CPUType==1表示K(杰理)系列
* 注意⚠️请先调用{@link openJLDialFileSystemWithAction:}开启文件系统

### 类名

`VPMarketDialManager`

### 接口

```objective-c
- (void)getJLWatchNamesWithAction:(void(^)(NSArray<NSString *> * _Nullable array))action
```

### 参数解释

| 参数   | 参数类型                                       | 备注         |
| ------ | ---------------------------------------------- | ------------ |
| action | void(^)(NSArray<NSString *> * _Nullable array) | 文件名字列表 |



## 获取杰里芯片设备当前照片表盘和市场表盘名称

### 前提

* K(杰理)系列设备使用，外设模型中CPUType==1表示K(杰理)系列

### 类名

`VPMarketDialManager`

### 接口

```objective-c
- (void)getJLCurrentPhotoAndMarketWatchNameWithArray:(NSArray<NSString *> *)array
                                              result:(void(^)(NSString *_Nullable photoWatchName, NSString * _Nullable marketWatchName))result;
```

### 参数解释

| 参数   | 参数类型                                                     | 备注                                                         |
| ------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| array  | NSArray<NSString *> *                                        | 文件列表，请确保传输的数组不为空且包含WATCH的元素            |
| result | void(^)(NSString *_Nullable photoWatchName, NSString * _Nullable marketWatchName) | 照片表盘和市场表盘的结果回调，照片表盘为空表示该项目无照片表盘，市场表盘为空表示设备当前未传输过照片表盘 |





# 联系人功能

## 判断设备是否支持添加联系人

### 前提

* 设备已连接
* 支持BT功能

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

```objective-c
// 通讯录类型 1代表有 0表示没有
@property (nonatomic, assign) NSUInteger contactType;
```



## 操作设备联系人

### 前提

* 设备已连接
* BT已连接
* 设备支持联系人功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingDeviceContactsWithOpCode:(VPDeviceContactsOpCode)opCode
                                         opModel:(VPDeviceContactsModel *)opModel
                                            toID:(int)toID
                                     resultBlock:(void(^)(VPDeviceContactsOpState state, NSArray<VPDeviceContactsModel *> *contactModels))resultBlock;
```

### 参数解释

| 参数        | 参数类型                                                     | 备注                     |
| ----------- | ------------------------------------------------------------ | ------------------------ |
| opCode      | VPDeviceContactsOpCode                                       | 操作类型，所有枚举值如下 |
| opModel     | VPDeviceContactsModel                                        | opCode为读取时无效       |
| toID        | Int                                                          | 目标id 仅移动操作时有效  |
| resultBlock | void(^)(VPDeviceContactsOpState state, NSArray<VPDeviceContactsModel *> *contactModels) | 结果回调                 |

```objective-c
// 设备通讯录操作类型
typedef NS_ENUM(NSUInteger, VPDeviceContactsOpCode) {
    VPDeviceContactsOpCodeRead = 0,    // 读取
    VPDeviceContactsOpCodeAdd,         // 添加
    VPDeviceContactsOpCodeDelete,      // 删除
    VPDeviceContactsOpCodeMove         // 移动
};
```



### 结果回调参数解释

| 参数          | 参数类型                         | 备注                             |
| ------------- | -------------------------------- | -------------------------------- |
| state         | VPDeviceContactsOpState          | 通讯录操作状态                   |
| contactModels | NSArray<VPDeviceContactsModel *> | 设备返回的操作后的联系人模型数组 |

```objective-c
// 通讯录操作状态
typedef NS_ENUM(NSUInteger, VPDeviceContactsOpState) {
    VPDeviceContactsOpStateNoFunction = 0,  // 不支持该功能
    VPDeviceContactsOpStateReading,         // 读取中
    VPDeviceContactsOpStateComplete,        // 操作成功
    VPDeviceContactsOpStateFailure          // 操作失败
};
```

## SOS联系人功能

本功能依附于联系人，将联系人设置为SOS联系人，可在设备上触发SOS拨打

### 前提

有联系人功能且支持SOS功能，可通过 `VPBleCentralManage.sharedBleManager().peripheralModel.contactType == 2` 判断

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
/// 通讯录的SOS电话拨打次数 Number of SOS calls made in the address book
/// @param opCode 操作类型  读取/设置
/// @param times 次数，请自行限制在 resultBlock 读取返回的[timesMin, timesMax]内，仅设置时有效
/// @param resultBlock 结果回调，设置操作时 返回的timesMin和timesMax为0
- (void)veepooSDKSettingDeviceContactsSOSInfoWithOpCode:(VPSOSOperationType)opCode
                                                  times:(int)times
                                            resultBlock:(void(^)(VPDeviceContactsOpState state, int times, int timesMin, int timesMax))resultBlock;
```

### 参数解释

| 参数        | 参数类型           | 备注               |
| ----------- | ------------------ | ------------------ |
| opCode      | VPSOSOperationType | 操作类型           |
| times       | int                | 次数，仅设置时有效 |
| resultBlock | Block              | 结果回调           |

```objective-c
// SOS的操作类型
typedef NS_ENUM(NSUInteger, VPSOSOperationType) {
    VPSOSOperationTypeSetting,     // 设置
    VPSOSOperationTypeRead         // 读取
};
```

### 使用举例

读取

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceContactsSOSInfo(withOpCode: .read, times: 0) { (state, curTime, timesMin, timesMax) in
            if state == .complete {
                print("curTime:\(curTime), timesMin:\(timesMin), timesMax:\(timesMax)")
            }
        }
```

设置

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceContactsSOSInfo(withOpCode: .setting, times: 2) { (state, curTime, timesMin, timesMax) in
            if state == .complete {
                print("curTime:\(curTime), timesMin:\(timesMin), timesMax:\(timesMax)")
            }
        }
```



# 手环查找手机功能

### 前提

设备已连接且支持该功能，设备点击查找手机按钮后，下方接口会触发事件，应用层播放一段音频。

事件触发的频率为4秒一次，播放的音频每次不宜超过3秒钟。**部分设备会每秒触发一次**。

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
//接收手环查找手机的回调，可以设置这个属性进行监听，设备查找手机过程中每4秒回调一次，使用者在接收回调后可以播放一个3秒钟的音频
@property (nonatomic, copy) void(^ReceiveDeviceSearchIphoneCommand)(void);
```

### 参数解释

无

### 返回数据

无

### 使用举例

```swift
// swift
VPBleCentralManage.sharedBleManager().peripheralManage.receiveDeviceSearchIphoneCommand = {
   print("播放一段3秒的音乐")
}
```



# 手机查找设备功能

## 判断设备是否支持手机查找设备功能

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

手机查找手环功能  `0`代表没有，`1`代表有

```objective-c
@property (nonatomic, assign) NSUInteger searchDeviceFunction;
```



## 手机查找设备功能

### 前提

* 设备已连接
* 设备支持手机查找手环功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDK_searchDeviceFuntionWithState:(BOOL)open result:(void (^)(BOOL open, VPSearchDeviceFunctionState state))result;
```

### 参数解释

| 参数   | 参数类型                                               | 备注                                                     |
| ------ | ------------------------------------------------------ | -------------------------------------------------------- |
| open   | BOOL                                                   | 开启或者关闭手机查找设备功能                             |
| result | void (^)(BOOL open, VPSearchDeviceFunctionState state) | open: 是否开启   state: 手机查找手环状态, 枚举值列表如下 |

```objective-c
// 手机查找手环状态
typedef NS_ENUM(NSUInteger, VPSearchDeviceFunctionState) {
    VPSearchDeviceFunctionStateUnsupported,   // 功能不支持
    VPSearchDeviceFunctionStateEnter,         // 设备进入了查找状态
    VPSearchDeviceFunctionStateExit,          // 设备退出了查找状态
    VPSearchDeviceFunctionStateTimeout,       // 设备查找超时
};
```

### 示例代码

 ```swift
  VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_searchDeviceFuntion(withState: !sender.isSelected, result: { [weak self](start, state) in
             print("state: \(state.rawValue)")
             if state.rawValue == 2 || state.rawValue == 3 {//设备主动退出或查找超时
                 self?.searchDeviceBtn.isSelected = false
             }
         })
 
 ```





# 消息通知功能

### 前提

* 设备已连接

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
- (void)veepooSDKSettingMessageType:(VPSettingMessageSwitchType)messageType settingState:(VPSettingFunctionState)settingState completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 批处理接口

```objective-c
/// 消息推送(信息提醒) 批处理接口，内部会自动忽略设备不支持的推送类型
/// @param models 需要处理的推送类型数组
/// @param settingCompleteBlock 设置状态Block 内部会置空
- (void)veepooSDKBatchSettingWithMessageTypeModels:(NSArray<VPDeviceMessageTypeModel *> *)models
                                     completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 参数解释

| 参数                 | 参数类型                                              | 备注                                                       |
| -------------------- | ----------------------------------------------------- | ---------------------------------------------------------- |
| messageType          | VPSettingMessageSwitchType                            | 要设置和读取的信息类型.所有值如下                          |
| settingState         | VPSettingFunctionState                                | 设置还是读取                                               |
| settingCompleteBlock | void(^)(VPSettingFunctionCompleteState completeState) | 设置和读取完成的回调，VPSettingFunctionCompleteState值如下 |

```objc
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
    VPSettingKakaoTalk = 23,
    VPSettingJingYou = 24, // 警右 APP
    VPSettingMessenger = 25,
    VPSettingAll = 100,//设置所有, 读取的使用不能使用这个
}

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
```

### 示例代码

```swift
unowned let weakSelf = self
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingMessageType(VPSettingMessageSwitchType.settingAll, settingState: VPSettingFunctionState(rawValue: sender.tag)!) { (settingFunctionCompleteState) in
    switch settingFunctionCompleteState {
    case .functionCompleteUnknown:
        _ = AppDelegate.showHUD(message: "没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
    case .functionCompleteFailure:
        _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
    case .functionCompleteOpen:
        _ = AppDelegate.showHUD(message: "设置成功，已经开启", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        weakSelf.messageRemindTableView?.reloadData()
    case .functionCompleteClose:
        _ = AppDelegate.showHUD(message: "设置成功，已经关闭", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        weakSelf.messageRemindTableView?.reloadData()
    case .functionCompleteComplete:
        _ = AppDelegate.showHUD(message: "设置完成", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        weakSelf.messageRemindTableView?.reloadData()
    }
}
```





# 蓝牙通话功能

## 判断设备是否支持蓝牙通话

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel**

### 接口

> 设备的芯片类型 从杰理系列开始有 1表示杰理系列
>
> CPUType =`1` 代表支持蓝牙通, 其余情况则代表不支持

```objective-c
@property (nonatomic, assign) NSUInteger CPUType;
```





## 打开设备BT开关

### 前提

* 设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

 打开设备的BT开关，如果设备与手机系统未配对，会触发配对请求。

 BT的连接状态统一使用 {@link VPBTConnectStateChangeBlock} 进行判断

```objective-c
- (void)veepooSDK_openDeviceBTSwitch;
```



## 设备BT连接状态改变的回调

### 前提

* 设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

设备BT连接状态改变的回调

```objective-c
@property (nonatomic, copy) void(^VPBTConnectStateChangeBlock)(VPDeviceBTState btState, BOOL btSwitchOpen, BOOL mediaSwitchOpen);
```

### 回调参数解释

| 参数            | 参数类型        | 备注                         |
| --------------- | --------------- | ---------------------------- |
| btState         | VPDeviceBTState | BT连接状态                   |
| btSwitchOpen | BOOL            | 设备的BT开关是否开启 |
| mediaSwitchOpen | BOOL            | 是否通过设备播放手机媒体音频 |

```objective-c
typedef NS_ENUM(NSInteger, VPDeviceBTState) {
    VPDeviceBTStateDisConnect = 0, //未连接
    VPDeviceBTStateConnected,      //已连接
    VPDeviceBTStateAdvertising,    //广播中
};
```





# OTA升级

注意⚠️：

* SDK使用用户需自行集成产品所属的厂商DFU库

* OTA过程较长，如果电池电量不足，传输过程可能会因低电关机，建议电池电量在30%以上，才允许升级；

## 获取当前固件版本号

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralModel**

### 接口

```objective-c
//设备的显示版本，告知用户当前的版本是多少
@property (nonatomic, strong, readonly) NSString *deviceVersion;
```

### 示例代码

```swift
currentVersionLabel.text = "当前版本: " + VPBleCentralManage.sharedBleManager().peripheralModel.deviceVersion
```



## 获取新固件版本号以及升级描述

### 前提

* 设备已连接

### 类名

`VPPeripheralModel`

获取途径：**VPBleCentralManage.sharedBleManager().peripheralModel**

### 接口

```objective-c
//设备网络升级版本，当用户收到有新固件版本的时候，告知用户升级的版本是多少
@property (nonatomic, strong, readonly) NSString *deviceNetVersion;

//设备升级更新版本描述，多个描述以$这个符号分隔，可以通过$进行拆分多个描述
@property (nonatomic, strong) NSString *deviceNetVersionDes;
```



### 示例代码

```swift
if VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion == nil {
    updateVersionLabel.text = "升级版本: " + "没有新版本"
}else {
    // 升级版本和升级新固件描述
    updateVersionLabel.text = "升级版本: " + VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion
    updateDesTextView.text = VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersionDes.replacingOccurrences(of: "$", with: "\n")
}
```



## 远程固件OTA升级

### 前提

* 设备已连接
* 有新固件可供升级

### 类名

`VPDFUOperation`

### 接口

```objective-c
/// 检查当前设备是否有新固件版本，生产环境请使用本接口，测试可以使用{@link checkDeviceOTAInfoWithDebug:downloadProgress:completionHandler:}
/// @param downloadProgressBlock 固件下载进度
/// @param completionHandler 请求完成处理器，newVersion不为空表示有新固件
- (void)checkDeviceOTAInfoWithDownloadProgress:(void (^)(NSProgress *downloadProgress))downloadProgressBlock
                             completionHandler:(void (^)(NSString *newVersion, NSString *des, NSError *error))completionHandler;

/// 检查当前设备是否有新固件版本
/// @param debug 是否为测试环境，⚠️注意生产环境不能使用yes
/// @param downloadProgressBlock 固件下载进度
/// @param completionHandler 请求完成处理器，newVersion不为空表示有新固件
- (void)checkDeviceOTAInfoWithDebug:(BOOL)debug
                   downloadProgress:(void (^)(NSProgress *downloadProgress))downloadProgressBlock
                  completionHandler:(void (^)(NSString *newVersion, NSString *des, NSError *error))completionHandler;
```



```objective-c
/**
 升级调用的接口，SDK从我司服务器自动获取固件直接升级就可以

 @param dfuBlock 返回的状态和进度的block
 */
- (void)veepooSDKStartDfu:(DeviceDFUBlock)dfuBlock;
```

### 回调block参数解释

```objective-c
typedef void(^DeviceDFUBlock)(double progress, DeviceDFUState deviceDFUState);
```

| 参数           | 参数类型       | 备注                     |
| -------------- | -------------- | ------------------------ |
| progress       | double         | 升级进度                 |
| deviceDFUState | DeviceDFUState | 升级状态，所有枚举值如下 |

```objective-c
typedef NS_ENUM(NSInteger, DeviceDFUState) {
    DeviceDFUFileNotExist = 0,  //升级文件不存在
    DeviceDFUStart,             //开始升级
    DeviceDFUUpdating,          //升级中
    DeviceDFUSuccess,           //升级成功
    DeviceDFUFailure,           //升级失败
    DeviceDFUPrepared,          //K系列设备的数据校验完成
    DeviceDFUReboot             //K系列设备重启
};
```



### 示例代码

```swift
VPDFUOperation.dfuOperationShare().veepooSDKStartDfu { (dfuProgress, deviceDFUState) in
          switch deviceDFUState {
          case .fileNotExist:
              sender.isSelected = false
              _ = AppDelegate.showHUD(message: "升级文件不存在，不能升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
          case .start:
              _ = AppDelegate.showHUD(message: "开始升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
          case .updating:
              weakSelf.dfuProgressLabel.text = "升级进度: " + String(dfuProgress) + "%"
          case .success:
              sender.isSelected = false
              _ = AppDelegate.showHUD(message: "升级成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
          case .failure:
              sender.isSelected = false
              _ = AppDelegate.showHUD(message: "升级失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
          }
      }
```





## 本地固件OTA

### 前提

* 设备已连接

### 类名

`VPDFUOperation`

### 接口

```objective-c
/// 开发者自己传入升级文件路径升级
/// @param dfuBlock 升级回调,文件路径不存在或者文件格式不对都返回文件路径不存在
- (void)veepooSDKStartDfuWithFilePath:(NSString *)filePath result:(DeviceDFUBlock)dfuBlock;
```

### 参数解释

| 参数     | 参数类型                                                     | 备注                                  |
| -------- | ------------------------------------------------------------ | ------------------------------------- |
| filePath | NSString                                                     | 升级文件路径                          |
| dfuBlock | void(^DeviceDFUBlock)(double progress, DeviceDFUState deviceDFUState) | 具体释义同远程OTA接口中的回调参数解释 |

### 示例代码

```swift
VPDFUOperation.dfuOperationShare().veepooSDKStartDfu(withFilePath: filePath) { (dfuProgress, deviceDFUState) in
    switch deviceDFUState {
    case .fileNotExist:
        sender.isSelected = false
        _ = AppDelegate.showHUD(message: "升级文件不存在，不能升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
    case .start:
        _ = AppDelegate.showHUD(message: "开始升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
    case .updating:
        weakSelf.dfuProgressLabel.text = "升级进度: " + String(dfuProgress) + "%"
    case .success:
        sender.isSelected = false
        _ = AppDelegate.showHUD(message: "升级成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
    case .failure:
        sender.isSelected = false
        _ = AppDelegate.showHUD(message: "升级失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
    }
}
```



# 久坐功能

### 前提

设备已连接且支持该功能。

注意本接口无标志位判断设备是否支持久坐，要判断设备是否支持久坐，可以使用接口读取一遍信息，如果触发失败的回调，则表示设备不支持本接口

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
- (void)veepooSDKSettingDeviceLongSeatWithLongSeatModel:(VPDeviceLongSeatModel *)longSeatModel
                                            settingMode:(NSUInteger)settingMode
                                          successResult:(void(^)(VPDeviceLongSeatModel *longSeatModel))settingLongSeatResultBlock
                                          failureResult:(void(^)(void))settingLongSeatFailureBlock;
```

### 参数解释

| 参数名                      | 类型                  | 备注                          |
| --------------------------- | --------------------- | ----------------------------- |
| longSeatModel               | VPDeviceLongSeatModel | 久坐的模型实例，见下表        |
| settingMode                 | NSUInteger            | 设置模式，0关闭、1开启、2读取 |
| settingLongSeatResultBlock  | Block                 | 成功结果回调                  |
| settingLongSeatFailureBlock | Block                 | 失败回调                      |

`VPDeviceLongSeatModel`

| 参数名              | 类型       | 备注                                       |
| ------------------- | ---------- | ------------------------------------------ |
| longSeatStartHour   | NSUInteger | 久坐提醒开始的小时 区间为0-23              |
| longSeatStartMinute | NSUInteger | 久坐提醒开始的分钟 区间为0-59              |
| longSeatEndHour     | NSUInteger | 久坐提醒结束的小时 区间为0-23              |
| longSeatEndMinute   | NSUInteger | 久坐提醒结束的分钟 区间为0-59              |
| longSeatGateValue   | NSUInteger | 久坐提醒的闸值 为多少分钟 区间为【30 240】 |
| longSeatState       | NSUInteger | 此为久坐提醒的状态，0代表关闭 1代表开启    |

### 返回数据

成功会触发`settingLongSeatResultBlock`

失败会触发`settingLongSeatFailureBlock`

### 使用举例

```swift
// swift
//初始化久坐模型
let longSeatModel = VPDeviceLongSeatModel(longSeatStartHour: 2, longSeatStartMinute: 30, longSeatEndHour: 18, longSeatEndMinute: 50, longSeatGateValue: 30, longSeatState: 1)

//设置
unowned let weakSelf = self;
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceLongSeat(with: longSeatModel, settingMode: 1, successResult: { (longSeatModel) in
    _ = AppDelegate.showHUD(message: "久坐设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
}) {
    _ = AppDelegate.showHUD(message: "久坐设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
}
```



# 闹钟功能

注意设备的闹钟功能存在多种版本，不同版本的闹钟不会同时存在，例如设备支持场景闹钟则不支持文字闹钟

## 文字闹钟

文字闹钟允许在设备端进行操作开关、时间设置等，但无法输入文字。

### 前提

设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`，可以参考SDK DEMO的 `VPTextAlarmClockSettingController` 类实现

### 接口

设备最多支持10组闹钟，应用层因增加限制添加闹钟个数的逻辑处理，否则设备可能会出现异常。

settingTextAlarmResultBlock不为空的情况下，在设备端操作闹钟状态，会触发回调，将数据同步到应用层

```objective-c
- (void)veepooSDKSettingDeviceTextAlarmWithTextAlarmModel:(VPDeviceTextAlarmModel *)alarmModel
                                              settingMode:(VPDeviceTextAlarmSettingModel)settingMode
                                            successResult:(void(^)(NSArray *alarmArray))settingTextAlarmResultBlock
                                            failureResult:(void(^)(void))settingTextAlarmFailureBlock;
```

### 参数解释

| 参数名                       | 类型                          | 备注                                                  |
| ---------------------------- | ----------------------------- | ----------------------------------------------------- |
| alarmModel                   | VPDeviceTextAlarmModel        | 文字闹钟对象，不能为空，读取的时候传初始化的默认对象  |
| settingMode                  | VPDeviceTextAlarmSettingModel | 1代表删除这组闹钟，2代表设置（增加或者修改）3代表读取 |
| settingTextAlarmResultBlock  | Block                         | 设置或者读取成功，返回当前所有的闹钟数                |
| settingTextAlarmFailureBlock | Block                         | 设置或者读取闹钟失败                                  |

```objective-c
// 文字闹钟的设置模式
typedef NS_ENUM(NSUInteger, VPDeviceTextAlarmSettingModel) {
    VPDeviceTextAlarmSettingModelDelete = 1,
    VPDeviceTextAlarmSettingModelAddOrChange,
    VPDeviceTextAlarmSettingModelRead
};
```

### 返回数据

文字闹钟对象数组

| 参数名      | 类型     | 备注                             |
| ----------- | -------- | -------------------------------- |
| alarmHour   | NSString | 闹钟小时                         |
| alarmMinute | NSString | 闹钟分钟                         |
| alarmState  | NSString | 闹钟状态，0代表关闭 1代表开启    |
| alarmID     | NSString | 闹钟ID，增删改查都需要用到这个   |
| repeatState | NSString | 闹钟重复状态，详情见表格下方释义 |
| alarmText   | NSString | 闹钟提醒的文字，最长支持60字节   |
| alarmDate   | NSString | 闹钟提醒的日期，无效字段         |

> 闹钟重复状态，0代表不重复要设置一个闹钟提醒的日期，其他情况是由8位2进制转换成10进制的字符串如：00000011，代表重复星期是周一和周二，repeatState就是3；二进制从后边往前推，开头的第一位一直为0，其他的一次代表周一至周日，第2位是周日，最后一位是周一，1代表重复，0代表这个星期不重复

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceTextAlarm(with: VPDeviceTextAlarmModel(), settingMode: .read) { arr in
    // 成功返回
} failureResult: {
    // 失败
}
```

## 场景闹钟(新闹钟)

新闹钟是相对旧的闹钟设计而言，并非是最新版本闹钟的意思。等同于场景闹钟、标签闹钟

### 类名

`VPPeripheralBaseManage` 参考 SDK Demo `VPEditNewAlarmController` 的实现

### 接口

```objective-c
- (void)veepooSDKSettingDeviceNewAlarmWithNewAlarmModel:(VPDeviceNewAlarmModel *)alarmModel
                                            settingMode:(NSUInteger)settingMode
                                          successResult:(void(^)(NSArray *alarmArray))settingNewAlarmResultBlock
                                          failureResult:(void(^)(void))settingNewAlarmFailureBlock;
```

### 参数解释

| 参数名                      | 类型                  | 备注                                                  |
| --------------------------- | --------------------- | ----------------------------------------------------- |
| alarmModel                  | VPDeviceNewAlarmModel | 新闹钟的Model，不能为空，读取的时候传默认             |
| settingMode                 | NSUInteger            | 0代表删除这组闹钟，1代表设置（增加或者修改）2代表读取 |
| settingNewAlarmResultBlock  | Block                 | 设置或者读取成功，返回当前所有的闹钟数                |
| settingNewAlarmFailureBlock | Block                 | 设置或者读取闹钟失败                                  |

### 返回数据

场景闹钟对象数组

| 参数名      | 类型     | 备注                                                         |
| ----------- | -------- | ------------------------------------------------------------ |
| alarmHour   | NSString | 闹钟小时                                                     |
| alarmMinute | NSString | 闹钟分钟                                                     |
| alarmState  | NSString | 闹钟状态，0代表关闭 1代表开启                                |
| alarmID     | NSString | 闹钟ID，增删改查都需要用到这个                               |
| repeatState | NSString | 闹钟重复状态，详情见表格下方释义                             |
| alarmScene  | NSString | 闹钟提醒的场景，1-20，场景闹钟的icon从Demo中获取，不要混用，手环端是根据这个一一对应的 |
| alarmDate   | NSString | 闹钟提醒的日期，对单次提醒有效，重复星期提醒的默认给0000-00-00，所有格式都是这样的 |

> 闹钟重复状态，0代表不重复要设置一个闹钟提醒的日期，其他情况是由8位2进制转换成10进制的字符串如：00000011，代表重复星期是周一和周二，repeatState就是3；二进制从后边往前推，开头的第一位一直为0，其他的一次代表周一至周日，第2位是周日，最后一位是周一，1代表重复，0代表这个星期不重复

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceNewAlarm(with: VPDeviceNewAlarmModel(), settingMode: 1) { arr in
    // 成功返回
} failureResult: {
    // 失败
}
```



# 女性功能

### 前提

设备已连接且支持该功能，女性功能为SDK的限制功能，需要先与我司商务联系，进行商务对接。

在权限未开启情况下，相应接口的职能无法生效。

### 类名

`VPPeripheralBaseManage`，参考SDK Demo `VPSettingFemaleRelatedController` 类实现

### 接口

```objective-c
- (void)veepooSDKSettingDeviceFemaleWithFemaleModel:(VPDeviceFemaleModel *)femaleModel
                                        settingMode:(NSUInteger)settingMode
                                      successResult:(void(^)(VPDeviceFemaleModel *deviceFemaleModel))settingFemaleResultBlock
                                      failureResult:(void(^)(void))settingFemaleFailureBlock;
```

### 参数解释

| 参数名                    | 类型                | 备注                                            |
| ------------------------- | ------------------- | ----------------------------------------------- |
| femaleModel               | VPDeviceFemaleModel | 女性功能对象实例化，见下表                      |
| settingMode               | NSUInteger          | 设置模式0代表关闭 1代表开启 2代表读设备女性信息 |
| settingFemaleResultBlock  | Block               | 设置或者读取成功                                |
| settingFemaleFailureBlock | Block               | 设置或者读取失败                                |

`VPDeviceFemaleModel`

| 参数名                   | 类型                | 备注                                                         |
| ------------------------ | ------------------- | ------------------------------------------------------------ |
| femaleState              | VPDeviceFemaleState | 处于哪个生理期                                               |
| lastMenstrualDate        | NSString            | 最后经期日期格式yyyy-MM-dd                                   |
| menstrualCircle          | NSInteger           | 经期周期                                                     |
| menstrualDays            | NSInteger           | 经期天数                                                     |
| currentMenstrualDays     | NSInteger           | 当前经期的时间天数，menstrualDays是一个人常规的经期天数，比如5天，但是这个月可能少一天也可能多一天，所以都了个此属性，此属性在彩屏项目上有效 |
| expectedDateOfChildbirth | NSString            | 预产期                                                       |
| babyBirthday             | NSString            | 宝宝的生日格式yyyy-MM-dd                                     |
| isGirl                   | BOOL                | 宝宝是否为女                                                 |

```objective-c
typedef NS_ENUM(NSInteger,VPDeviceFemaleState) {//女性项目属于哪个生理期
    VPDeviceFemaleStateNone = 0,//没有设置生理期
    VPDeviceFemaleStateMenstrual,//月经期
    VPDeviceFemaleStatePregnancy,//备孕期
    VPDeviceFemaleStateGestation,//怀孕期
    VPDeviceFemaleStateBaoma,//辣妈期
};
```

### 返回数据

成功触发`settingFemaleResultBlock`回调，失败触发`settingFemaleFailureBlock`回调

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceFemale(with: femaleModel, settingMode: 2, successResult: { (deviceFemaleModel) in
    guard let deviceFemaleModel = deviceFemaleModel else {
        return
    }
    weakSelf.femaleModel = deviceFemaleModel
    weakSelf.femaleRelatedTableView?.reloadData()
    _ = AppDelegate.showHUD(message: "读取成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
}) {
    _ = AppDelegate.showHUD(message: "读取失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
}
```



# 拍照功能

### 前提

设备已连接且支持该功能，本功能需要客户自行设计并实现应用内拍照功能。手环的主要作用是控制拍照时刻，进入拍照后，点击手环端的拍照按钮或摇一摇，SDK端会收到一个拍照触发事件，应用层触发拍照即可。

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
- (void)veepooSDKSettingCameraType:(VPCameraType)settingType settingAndMonitorResult:(void(^)(VPCameraType cameraType))cameraBlock;
```

### 参数解释

| 参数名      | 类型         | 备注             |
| ----------- | ------------ | ---------------- |
| settingType | VPCameraType | VPCameraType枚举 |
| cameraBlock | Block        | 结果回调         |

```objective-c
typedef NS_ENUM(NSInteger,VPCameraType) {
    VPCameraTypeExit = 0,//退出拍照
    VPCameraTypeEnter = 1,//进入拍照
    VPCameraTypePhoto = 2//开始拍照
};
```

### 返回数据

设备如果支持拍照，则会触发cameraBlock回调

### 使用举例

```swift
// swift
VPPeripheralManage.shareVPPeripheralManager().veepooSDKSettingCameraType(.enter) { type in
	  print(type.rawValue)
}
```





# 手环运动功能

## 手环运动历史数据获取

### 前提

设备已连接且支持该功能

### 类名

`VPDataBaseOperation` 、`VPPeripheralBaseManage`

### 接口

```objc
// 先调用这个接口将数据从设备同步到SDK
- (void)veepooSDKStartReadDeviceRunningData:(void(^)(VPReadDeviceBaseDataState readState, NSUInteger totalTimes, NSUInteger currentReadTimes, NSUInteger readCurrentTimesProgress))readDeviceRunningBlock;
// 从SDK数据库中读取数据
+ (NSArray *)veepooSDKGetDeviceRunningDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

### 参数解释

| 参数名    | 类型     | 备注                            |
| --------- | -------- | ------------------------------- |
| queryDate | NSString | 要查询的日期，格式为:yyyy-MM-dd |
| tableID   | NSString | 设备的mac地址                   |

### 返回数据

```objc
[{
    aerobTime = 1260;
    averHeart = 81;
    averPace = 0;
    beginTime = "2023-05-17 20:16:25";
    crcValue = 47136;
    endTime = "2023-05-17 20:37:33";
    isHide = 0;
    oneMinuteData =     (
                {
            calValue = 0;
            disValue = 0;
            heartValue = 86;
            isPause = 0;
            packageCount = 00001;
            sportValue = 5;
            stepValue = 0;
        }
    );
    pauseCount = 0;
    pauseTotalTime = 0;
    recordCount = 5376;
    totalCal = 0;
    totalDis = 0;
    totalSport = 124;
    totalStep = 0;
    totalTime = 1268;
    type = 1;
}]
```

| 参数名         | 类型               | 备注                     |
| -------------- | ------------------ | ------------------------ |
| beginTime      | NSString           | 开始时间                 |
| endTime        | NSString           | 结束时间                 |
| averHeart      | NSString           | 平均心率                 |
| averPace       | NSString           | 平均配速                 |
| pauseCount     | NSString           | 暂停次数                 |
| pauseTotalTime | NSString           | 暂停时长                 |
| recordCount    | NSString           | 记录                     |
| totalCal       | NSString           | 总卡路里数，单位cal      |
| totalDis       | NSString           | 总路程，单位m            |
| totalSport     | NSString           | 总的运动量               |
| totalStep      | NSString           | 总的步数                 |
| totalTime      | NSString           | 运动总的时间             |
| type           | VPDeviceRuningMode | 运动类型                 |
| oneMinuteData  | NSArray            | 数组，每一分钟的数据结构 |
| crcValue       | NSString           | 运动的crc值              |

每一分钟的数据结构

| 参数名       | 类型     | 备注               |
| ------------ | -------- | ------------------ |
| heartValue   | NSString | 心率               |
| disValue     | NSString | 里程               |
| calValue     | NSString | 卡路里             |
| isPause      | NSString | 是否暂停           |
| packageCount | NSString | 当前包号，无需处理 |
| sportValue   | NSString | 运动量             |
| stepValue    | NSString | 步数               |

### 使用举例

```swift
// 读取运动数据
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readDeviceRunningData(withBlockNumber: 0) { (deviceRunningDict, totalPackage, currentPackage) in
            if currentPackage >= totalPackage {
                print(deviceRunningDict ?? "没有运动数据")
            }else {
                print("totalPackage:\(totalPackage) currentPackage:\(currentPackage)")
            }
        }
```

```objc
// 从数据库拿单天的运动数据
let arr = VPDataBaseOperation.veepooSDKGetDeviceRunningData(withDate: 0.getOneDayDateString(), andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
```

## 手环运动模式开启与读取

### 前提

设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

### 接口

注意，设备中存在的运动类型并不是全部，不同的项目存在不同的运动类型。并且运动模式需一一对应。

```objc
- (void)veepooSDKSettingDeviceRunning:(int)settingType
                              runMode:(VPDeviceRuningMode)runningMode
                               result:(void(^)(int runningType, BOOL settingSuccess))runningResultBlock;
```

监听设备端手环运动结束事件，block触发回调，可以调用读取数据接口

```objective-c
/// 设备端结束一组运动并产生有效数据时回调
@property (nonatomic, copy) void(^deviceSportDidFinishBlock)(BOOL success);
```

### 参数解释

| 参数名             | 类型               | 备注                                                         |
| ------------------ | ------------------ | ------------------------------------------------------------ |
| settingType        | int                | 0是关闭运动模式，1是开启运动模式，2是读取当前设备运动模式    |
| runningMode        | VPDeviceRuningMode | 具体参考枚举, 如果不是多运动给0, 判断多运动的方式见VPPeripheralModel下的runningType属性说明 |
| runningResultBlock | Block              | 设置和读取结果                                               |

```objc
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
    VPDeviceRuningModeStrongWalk,               //健走
    VPDeviceRuningModeTreadmill,                //跑步机
    VPDeviceRuningModeTrailRunning,             //越野跑
    VPDeviceRuningModeRaceWalking,              //竞走
    VPDeviceRuningModeMountainBiking,           //山地骑行
    VPDeviceRuningModeBmx,                      //小轮车
    VPDeviceRuningModeOrienteering,             //定向越野
    VPDeviceRuningModeFishing,                  //钓鱼
    VPDeviceRuningModeHunt,                     //打猎
    VPDeviceRuningModeSkateboard,               //滑板
    VPDeviceRuningModeRollerSkating,            //轮滑
    VPDeviceRuningModeParkour,                  //跑酷
    VPDeviceRuningModeAtv,                      //沙滩车
    VPDeviceRuningModeMotocross,                //越野摩托
    VPDeviceRuningModeClimbingMachine,          //爬楼机
    VPDeviceRuningModeSpinningBike,             //动感单车
    VPDeviceRuningModeIndoorFitness,            //室内健身
    VPDeviceRuningModeMixedAerobic,             //混合有氧
    VPDeviceRuningModeCrossTraining,            //交叉训练
    VPDeviceRuningModeBodybuildingExercise,     //健身操
    VPDeviceRuningModeGroupGymnastics,          //团体操
    VPDeviceRuningModeKickboxing,               //搏击操
    VPDeviceRuningModeStrengthTraining,         //力量训练
    VPDeviceRuningModeSteppingTraining,         //踏步训练
    VPDeviceRuningModeCoreTraining,             //核心训练
    VPDeviceRuningModeFlexibilityTraining,      //柔韧训练
    VPDeviceRuningModeFreeTraining,             //自由训练
    VPDeviceRuningModePilates,                  //普拉提
    VPDeviceRuningModeBattleRope,               //战绳
    VPDeviceRuningModeStretch,                  //拉伸
    VPDeviceRuningModeSquareDance,              //广场舞
    VPDeviceRuningModeBallroomDancing,          //交际舞
    VPDeviceRuningModeBellyDance,               //肚皮舞
    VPDeviceRuningModeBallet,                   //芭蕾舞
    VPDeviceRuningModeHipHop,                   //街舞
    VPDeviceRuningModeZumba,                    //尊巴
    VPDeviceRuningModeLatinDance,               //拉丁舞
    VPDeviceRuningModeJazz,                     //爵士舞
    VPDeviceRuningModeHipHopDance,              //嘻哈舞
    VPDeviceRuningModePoleDancing,              //钢管舞
    VPDeviceRuningModeBreakDance,               //霹雳舞
    VPDeviceRuningModeNationalDance,            //民族舞
    VPDeviceRuningModeModernDance,              //现代舞
    VPDeviceRuningModeDisco,                    //迪斯科
    VPDeviceRuningModeTapDance,                 //踢踏舞
    VPDeviceRuningModeWrestling,                //摔跤
    VPDeviceRuningModeMartialArts,              //武术
    VPDeviceRuningModeTaiChi,                   //太极
    VPDeviceRuningModeMuayThai,                 //泰拳
    VPDeviceRuningModeJudo,                     //柔道
    VPDeviceRuningModeTaekwondo,                //跆拳道
    VPDeviceRuningModeKarate,                   //空手道
    VPDeviceRuningModeFreeSparring,             //自由搏击
    VPDeviceRuningModeSwordsmanship,            //剑术
    VPDeviceRuningModeJujitsu,                  //柔术
    VPDeviceRuningModeFencing,                  //击剑
    VPDeviceRuningModeBeachSoccer,              //沙滩足球
    VPDeviceRuningModeBeachVolleyball,          //沙滩排球
    VPDeviceRuningModeSoftball,                 //垒球
    VPDeviceRuningModeSquash,                   //壁球
    VPDeviceRuningModeCroquet,                  //门球
    VPDeviceRuningModeCricket,                  //板球
    VPDeviceRuningModePolo,                     //马球
    VPDeviceRuningModeWallball,                 //墙球
    VPDeviceRuningModeTakrawBall,               //藤球
    VPDeviceRuningModeDodgeball,                //躲避球
    VPDeviceRuningModeWaterPolo,                //水球
    VPDeviceRuningModeShuttlecock,              //毽球
    VPDeviceRuningModeIndoorSoccer,             //室内足球
    VPDeviceRuningModeSandbagBall,              //沙包球
    VPDeviceRuningModeBocceBall,                //地掷球
    VPDeviceRuningModeJaileyball,               //回力球
    VPDeviceRuningModeFloorball,                //地板球
    VPDeviceRuningModeOutdoorBoating,           //户外划船
    VPDeviceRuningModeKayak,                    //皮划艇
    VPDeviceRuningModeDragonBoat,               //龙舟
    VPDeviceRuningModePaddleBoard,              //桨板冲浪
    VPDeviceRuningModeIndoorFillingWaves,       //室内充浪
    VPDeviceRuningModeDrifting,                 //漂流
    VPDeviceRuningModeWaterSkiing,              //滑水
    VPDeviceRuningModeSnowboarding,             //双板滑雪
    VPDeviceRuningModeSnowboard,                //单板滑雪
    VPDeviceRuningModeAlpineSkiing,             //高山滑雪
    VPDeviceRuningModeCrossCountrySkiing,       //越野滑雪
    VPDeviceRuningModeOrienteeringSki,          //定向滑雪
    VPDeviceRuningModeBathlon,                  //冬季两项
    VPDeviceRuningModeOutdoorSkating,           //户外滑冰
    VPDeviceRuningModeIndoorSkating,            //室内滑冰
    VPDeviceRuningModeSnowCar,                  //雪车
    VPDeviceRuningModeSnowmobile,               //雪地摩托
    VPDeviceRuningModeSnowshoeing,              //雪鞋健行
    VPDeviceRuningModeHulaHoop,                 //呼啦圈
    VPDeviceRuningModeFrisbee,                  //飞盘
    VPDeviceRuningModeDart,                     //飞镖
    VPDeviceRuningModeFlyAKite,                 //放风筝
    VPDeviceRuningModeTugOfWar,                 //拔河
    VPDeviceRuningModeShuttlecockKicking,       //踢毽子
    VPDeviceRuningModeESports,                  //电子竞技
    VPDeviceRuningModeWanderingMachine,         //漫步机
    VPDeviceRuningModeSwing,                    //秋千
    VPDeviceRuningModeShuffleboard,             //沙狐球
    VPDeviceRuningModeTableSoccer,              //桌上足球
    VPDeviceRuningModeSomatosensoryGame,        //体感游戏
    VPDeviceRuningModeInternationalChess,       //国际象棋
    VPDeviceRuningModeDraughts,                 //国际跳棋
    VPDeviceRuningModeGo,                       //围棋
    VPDeviceRuningModeBridge,                   //桥牌
    VPDeviceRuningModeBoardGame,                //桌游
    VPDeviceRuningModeArchery,                  //射箭
    VPDeviceRuningModeEquestrianSports,         //马术运动
    VPDeviceRuningModeClimbingTheStairs,        //爬楼
    VPDeviceRuningModeDrive,                    //驾车
    VPDeviceRuningModeSeatedPush,               //坐姿推举
    VPDeviceRuningModeSeatedChestPress,         //坐姿胸部推举
    VPDeviceRuningModeBarbell,                  //杠铃
    VPDeviceRuningModeLongDistanceRunning,      //长跑
    VPDeviceRuningModeFullSpeedRun,             //全速跑
    VPDeviceRuningModeVariableSpeedRun,         //变速跑
    VPDeviceRuningModeRaceRiding,               //赛场骑行
    VPDeviceRuningModeMilitaryChess,            //军棋
    VPDeviceRuningModeMahjong,                  //麻将
    VPDeviceRuningModePoker,                    //扑克
    VPDeviceRuningModeGobang,                   //五子棋
    VPDeviceRuningModeChineseChess,             //中国象棋
    VPDeviceRuningModeHighJump,                 //跳高
    VPDeviceRuningModeLongJump,                 //跳远
    VPDeviceRuningModeSpinningTop,              //打陀螺
};
```

### 返回数据

`runningResultBlock`

| 参数名         | 类型 | 备注                                                         |
| -------------- | ---- | ------------------------------------------------------------ |
| runningType    | int  | runningType为0代表不在运动模式下，1代表运动模式中，2代表其他忙碌状态,3代表运动模式结束连接状态下主动告知App,此参数只有在读取或者设置失败的时候做参考，或者在运动结束主动上报的时候用 |
| settingSuccess | BOOL | 设置或读取是否成功，如果失败，可以参考runningType类型来看一下原因，如运动模式已经开启，再次开启，就会失败，或者设备在做其他操作 |

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceRunning(1, run: VPDeviceRuningMode.outdoorRun ) { type, success in
            // to do ...
        }
```

# 天气功能

### 前提

设备已连接且支持该功能，应用层需自行接入第三方天气数据源，SDK内部仅负责进行数据传输。

我司使用的第三方天气数据源为和风天气 https://www.qweather.com/

### 类名

`VPWeatherHandle`

### 接口

应用层先读取设备的天气开关等信息，然后请求第三方天气数据源

```objective-c
typedef void(^VPSyncWeatherResult)(VPWeatherSettingState state);
typedef void(^VPSettingWeatherResult)(VPWeatherSettingState state);
typedef void(^VPReadWeatherResult)(VPWeatherSettingState state, VPWeatherConfigModel * _Nullable cofigModel);

//SDK使用人，主要调用以下3个方法即可，Model自己配置好下发
//同步App的天气数据给设备
- (void)syncWeatherDataToDeviceWithWeatherServerModel:(VPWeatherServerModel *)serverModel result:(VPSyncWeatherResult)result;
//读取天气开关和单位
- (void)readWeatherInfo:(VPReadWeatherResult)result;
//设置天气开关和单位
- (void)settingWeatherInfo:(VPWeatherConfigModel *)settingModel result:(VPSettingWeatherResult)result;
```

### 参数解释

| 参数名       | 类型                 | 备注                             |
| ------------ | -------------------- | -------------------------------- |
| serverModel  | VPWeatherServerModel | 要传输给设备的天气数据实例化对象 |
| result       | VPSyncWeatherResult  | 天气同步结果                     |
| settingModel | VPWeatherConfigModel | 天气相关配置的实例化对象         |

* VPWeatherServerModel

| 参数名   | 类型                                    | 备注                            |
| -------- | --------------------------------------- | ------------------------------- |
| lon      | double                                  | 经度                            |
| lat      | double                                  | 纬度                            |
| city     | NSString                                | 温度的城市或区域                |
| update   | NSString                                | 最后更新时间2020-05-09 09:08:34 |
| hourly   | NSArray<VPWeatherServerHourlyModel *>   | 逐3小时天气数组                 |
| forecast | NSArray<VPWeatherServerForecastModel *> | 未来逐天的天气数组              |

* VPWeatherServerHourlyModel

| 参数名  | 类型     | 备注                                      |
| ------- | -------- | ----------------------------------------- |
| time    | NSString | 时间，格式2020-02-28 05:00                |
| temp    | double   | 温度华氏度                                |
| uvi     | NSNumber | 紫外线强度指数                            |
| code    | Int      | 天气状态码 下方注释有详细对应天气状态关系 |
| wind_sc | NSString | 风向等级1-2                               |
| vis     | NSNumber | 能见度                                    |

* VPWeatherServerForecastModel

| 参数名    | 类型     | 备注                 |
| --------- | -------- | -------------------- |
| date      | NSString | 日期，格式2020-02-28 |
| maxTemp   | double   | 最高温度华氏度       |
| minTemp   | double   | 最低温度华氏度       |
| uvi       | NSNumber | 紫外线强度指数       |
| dayCode   | NSNumber | 白天天气状态码       |
| nightCode | NSNumber | 夜间天气状态码       |
| wind_sc   | NSString | 风向等级1-2          |
| vis       | NSNumber | 能见度               |

```objc
/** VPWeatherServerHourlyModel
 天气状态码对应天气状态关系 逐小时的状态与此关系一致
 “()” 表示不包含
 "[]" 表示包含
 
 [0,   4]          表示 - 晴天
 (4, 12]          表示 - 晴转多云
 (12, 16]        表示 - 阴天
 (16, 20]        表示 - 阵雨
 (20, 24]        表示 - 雷阵雨
 (24, 32]        表示 - 冰雹
 (32, 40]        表示 - 小雨
 (40, 48]        表示 - 中雨
 (48, 56]        表示 - 大雨
 (56, 72]        表示 - 暴雨
 (72, 84]        表示 - 小雪
 (84, 100]      表示 - 大雪
 (100, 155]    表示 - 多云
 其它 - 未知
 */
```

### 返回数据

* VPWeatherConfigModel

| 参数名      | 类型     | 备注                                                    |
| ----------- | -------- | ------------------------------------------------------- |
| switchState | int      | 0是关，1是开                                            |
| weatherUnit | int      | 0是摄氏度，1华氏度                                      |
| crc         | uint16_t | 设备当前天气的CRC，做来比对应用层存储的天气数据是否过期 |

```objc
typedef NS_ENUM(NSInteger, VPWeatherSettingState) {
    VPWeatherSettingStateNone = 0, //没有此功能
    VPWeatherSettingStateSuccess,  //成功
    VPWeatherSettingStateFailure,  //失败
};
```

### 使用举例

```objc
[[VPWeatherHandle share] readWeatherInfo:^(VPWeatherSettingState state, VPWeatherConfigModel * _Nullable cofigModel) {
        if (state == 1) {//读取成功
            // todo...
        }
    }];
```



# 血糖功能

## 血糖自动测量历史数据获取

血糖值值域为：**[3.00, 15.00]**

血糖风险等级需要设备的血糖类型值为5才支持；`bloodGlucoseType == 5`

### 前提

设备已连接且支持该功能，调用日常数据读取完成之后，从SDK数据库中获取血糖历史数据

###  类名

`VPDataBaseOperation`

### 接口

本接口返回到是每5分钟到血糖历史数据，应用层要怎么显示可以自行对返回的数据进行加工处理。

对于当天来说，数据是持续产生的，每次读取返回的数据数量不定。

```objective-c
+ (NSArray *)veepooSDKGetDeviceBloodGlucoseDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

### 参数解释

| 参数名    | 类型     | 备注                            |
| --------- | -------- | ------------------------------- |
| queryDate | NSString | 要查询的日期，格式为:yyyy-MM-dd |
| tableID   | NSString | 设备的mac地址                   |

### 返回数据

字典数组

```objective-c
NSDictionary *dataDic = {
    "time" = "16:30";
    "bloodGlucoses" =  [@"0.00"]; // 每5分钟的血糖值数组，数组中元素最少1个，至多5个。
    "bloodGlucoseLevels" = [@"0"];//血糖值对应的风险等级，1-3分别为低、中、高，设备的血糖类型(bloodGlucoseType)为5才支持，如果有则与血糖值是一一对应的。注意这个Key使用前需要做非空判断
}
```

| 参数名             | 类型     | 备注                               |
| ------------------ | -------- | ---------------------------------- |
| time               | NSString | 时间，格式：HH:mm                  |
| bloodGlucoses      | NSArray  | 血糖值数组                         |
| bloodGlucoseLevels | NSArray  | 血糖风险等级数组，与血糖值一一对应 |

### 使用举例

```swift
@IBAction func readDataBtnAction(_ sender: UIButton) {
    let tableID = VPBleCentralManage.sharedBleManager()?.peripheralModel.deviceAddress;
    let dateFormatter = DateFormatter.init()
    dateFormatter.dateFormat = "yyyy-MM-dd"
    dateFormatter.timeZone = TimeZone.init(identifier: "Asia/Shanghai")
    let dateStr = dateFormatter.string(from: Date.init())
    
    let arr = VPDataBaseOperation.veepooSDKGetDeviceBloodGlucoseData(withDate: dateStr, andTableID: tableID)
    print(arr as Any)
}
```

## 单项测量

### 类名

`VPPeripheralBaseManage`

### 接口

返回的血糖值结构为: 0.00，上报的value为100倍，显示的时候自行处理， 血糖值单位转换如下：`mmol/L => mg/dL`

公式：`floor((X mmol/L ) * 18 +0.5f) = Y mg/dL`

**血糖类型(bloodGlucoseType)为5情况下，level风险等级才有效**

```objective-c
- (void)veepooSDKTestBloodGlucoseStart:(BOOL)start testResult:(void(^)(VPDeviceBloodGlucoseTestState testState, NSUInteger testProgress, NSUInteger value, NSUInteger level))testResult;
```

### 参数解释

| 参数名     | 类型  | 备注           |
| ---------- | ----- | -------------- |
| start      | BOOL  | 开始或结束测量 |
| testResult | Block | 测量结果回调   |

```objective-c
// 血糖功能指令测试状态
typedef NS_ENUM(NSUInteger, VPDeviceBloodGlucoseTestState) {
    VPDeviceBloodGlucoseTestStateUnsupported,      // 设备不支持
    VPDeviceBloodGlucoseTestStateOpen,             // 开启测量
    VPDeviceBloodGlucoseTestStateClose,            // 关闭测量
    VPDeviceBloodGlucoseTestStateLowPower,         // 设备低电
    VPDeviceBloodGlucoseTestStateDeviceBusy,       // 设备正忙
    VPDeviceBloodGlucoseTestStateNotWear           // 设备佩戴检测未通过
};
```

### 使用举例

```swift
@IBAction func manualTestDataBtnAction(_ sender: UIButton) {
    sender.isSelected = !sender.isSelected
    VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKTestBloodGlucoseStart(sender.isSelected, testResult: { [weak self](state, progress, value, level) in
        var txt = ""
        if state == .unsupported{
            txt = "设备不支持该功能"
        }
        if state == .close {
            txt = "测量结束"
        }
        if state == .lowPower {
            txt = "设备低电"
        }
        if state == .deviceBusy {
            txt = "设备正忙"
        }
        if state == .notWear {
            txt = "设备佩戴检测失败"
        }
        if state == .open {
            txt = "进度：\(progress) % 值：\(value) 等级：\(level)"
        }        
        _ = AppDelegate.showHUD(message: txt, hudModel: MBProgressHUDModeText, showView: self!.view)
    });
}
```

## 血糖私人模式

### 前提

设备已连接且支持该功能

血糖私人模式需要用户先设置一个基准血糖值，涉及读取和设置血糖基准值

血糖私人模式打开之后，血糖自动测量的数据则以私人模式进行测量

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
- (void)veepooSDKBloodGlucosePersonalWithOpCode:(NSInteger)opCode
                                          value:(CGFloat)value
                                           open:(BOOL)open
                                         result:(void(^)(BOOL success, CGFloat privateValue, NSInteger model))result;
```

### 参数解释

| 参数名 | 类型      | 备注                                                         |
| ------ | --------- | ------------------------------------------------------------ |
| opCode | NSInteger | 1为设置 2为读取                                              |
| value  | CGFloat   | 血糖值范围[3.00, 15.00]，不在该范围内会被强制修改为4.00 （读取时无效） |
| open   | BOOL      | 是否开启校准模式 0关闭 1开启（读取时无效）                   |
| result | Block     | 回调                                                         |

### 返回数据

| 参数名       | 类型      | 备注                     |
| ------------ | --------- | ------------------------ |
| success      | BOOL      | 成功/失败                |
| privateValue | CGFloat   | 血糖基准值               |
| model        | NSInteger | 是否开启，0未开启，1开启 |

### 使用举例

```swift
VPBleCentralManage.sharedBleManager()?.peripheralManage
            .veepooSDKBloodGlucosePersonal(withOpCode: 2, value: 0, open: true, result: {  [weak self](success, value, isOpen) in
        _ = AppDelegate.showHUD(message: "读取 \(success), \(value), \(isOpen)", hudModel: MBProgressHUDModeText, showView: self!.view)
        })
```

## 血糖多校准功能

单校准和多校准互斥，同一项目不会出现都有的情况

### 前提

血糖功能的类型为4/5/7(后期可能添加不同的类型，根据具体项目包含的功能判断)

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
/// 血糖多校准的设置/读取，与 {@link: veepooSDKBloodGlucosePersonalWithOpCode:value:open:result:} 互斥
/// 通过 bloodGlucoseType 判断是否支持多校准，多校准有6个时间段的血糖参考值
/// @param opCode 1为设置 2为读取
/// @param model 血糖多校准的模型
/// @param result 回调函数
- (void)veepooSDKBloodGlucoseMultiPersonalWithOpCode:(NSInteger)opCode
                                               model:(VPMultiBloodGlucoseModel *)model
                                              result:(void(^)(BOOL success, VPMultiBloodGlucoseModel * model))result;
```

### 参数解释

| 参数名 | 类型                     | 备注                             |
| ------ | ------------------------ | -------------------------------- |
| opCode | NSInteger                | 1为设置 2为读取                  |
| model  | VPMultiBloodGlucoseModel | 多校准的参数模型，读取时可以不传 |
| result | Block                    | 回调                             |

VPMultiBloodGlucoseModel

| 参数名          | 类型                         | 备注                                      |
| --------------- | ---------------------------- | ----------------------------------------- |
| open            | BOOL                         | 是否已开启私人模式                        |
| beforeBreakfast | VPMultiBloodGlucoseItemModel | 早餐前，只能设置在凌晨2:00点到12:00点之间 |
| afterBreakfast  | VPMultiBloodGlucoseItemModel | 早餐后                                    |
| beforeLunch     | VPMultiBloodGlucoseItemModel | 午餐前                                    |
| afterLunch      | VPMultiBloodGlucoseItemModel | 午餐后                                    |
| beforeDinner    | VPMultiBloodGlucoseItemModel | 晚餐前                                    |
| afterDinner     | VPMultiBloodGlucoseItemModel | 晚餐后                                    |

VPMultiBloodGlucoseItemModel

| 参数名 | 类型     | 备注                                                 |
| ------ | -------- | ---------------------------------------------------- |
| hour   | uint8_t  | 小时，24制式，[0, 23]                                |
| minute | uint8_t  | 分钟，[0, 59]                                        |
| value  | uint16_t | 对应的血糖值，值域[300, 1500]，实际值域为[3.0, 15.0] |

### 使用举例

```swift
// setting 设置
        let model:VPMultiBloodGlucoseModel = .init()
        model.open = true
        model.beforeBreakfast = VPMultiBloodGlucoseItemModel(hour: 8, minute: 0, value: 8)
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKBloodGlucoseMultiPersonal(withOpCode: 1, model: model) { success, model in
            if success {
                guard let model = model else { return }
                print(model)
            }
        }
```



## 血糖单位切换

### 前提

设备已连接且支持该功能，可以参考`VPBaseFunctionRemindController`类中的实现

### 类名

`VPPeripheralBaseManage`

### 接口

```objective-c
- (void)veepooSDKSettingBaseFunctionType:(VPSettingBaseFunctionSwitchType)baseFunctionType
                            settingState:(VPSettingFunctionState)settingState
                           completeBlock:(void(^)(VPSettingFunctionCompleteState completeState))settingCompleteBlock;
```

### 参数解释

| 参数名               | 类型                            | 备注                                              |
| -------------------- | ------------------------------- | ------------------------------------------------- |
| baseFunctionType     | VPSettingBaseFunctionSwitchType | 要设置或读取的类型，使用VPSettingBloodGlucoseUnit |
| settingState         | VPSettingFunctionState          | 设置/读取                                         |
| settingCompleteBlock | Block                           | 回调                                              |

```objective-c
typedef NS_ENUM(NSInteger, VPSettingFunctionState) {//设置获取读取某个功能
    VPReadFunctionState = 0, //读取某个功能的开关和有无
    VPSettingFunctionOpen = 1,//打开某个功能
    VPSettingFunctionClose = 2,//关闭某个功能
    VPSettingFunctionCancel = 3,//现在仅动态血压校准有效
    VPSettingFunction = 4,//设置某个功能
};
```

### 返回数据

```objective-c
typedef NS_ENUM(NSInteger, VPSettingFunctionCompleteState) {//设置某个功能完成之后的状态
    VPFunctionCompleteUnknown = 0, //设备没有此功能
    VPFunctionCompleteOpen = 1,//此功能已经打开
    VPFunctionCompleteClose = 2,//此功能已经关闭
    VPFunctionCompleteFailure = 3,//设置或者读取失败
    VPFunctionCompleteComplete = 4,//设置完成，针对Data设置的回复
};
```

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingBaseFunctionType(.bloodGlucoseUnit, settingState: .readFunctionState) { state in
		// todo...
}
```



# 血压功能

## 血压历史数据获取

### 前提

设备已连接且支持该功能，调用日常数据读取完成之后，从SDK数据库中获取血压数据

### 类名

`VPDataBaseOperation` , 参考SDK Demo `VPTestBloodController` 类实现

### 接口

获取某一天的血压历史数据，默认每10分钟一条血压数据。如果为10分钟一条，则一天至多有144条数据。

不同系列的设备，测量的频率不一致。

```objective-c
+ (NSArray *)veepooSDKGetBloodDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

### 参数解释

| 参数名    | 类型     | 备注                       |
| --------- | -------- | -------------------------- |
| queryDate | NSString | 查询日期，格式为yyyy-MM-dd |
| tableID   | NSString | 数据ID，传设备的MAC地址    |

### 返回数据

```objective-c
[
 {
    Time = "07:05";
    diastolic = "106";
    isManual = "N";
    systolic = "71";
    vein = "0";
 },
 {
    Time = "08:05";
    diastolic = "101";
    isManual = "N";
    systolic = "65";
    vein = "0";
 }
]
```

| 参数名    | 类型     | 备注                      |
| --------- | -------- | ------------------------- |
| Time      | NSString | 测量时间                  |
| diastolic | NSString | 舒张压(低压)              |
| isManual  | NSString | 是不是手动测量，固定为“N” |
| systolic  | NSString | 收缩压(高压)              |
| vein      | NSString | 无效字段                  |

### 使用举例

```swift
func obtainOneDayBloodData() {
        self.bloodDateLabel.text = bloodDayIndex.getOneDayDateString()
        let bloodDataBaseArray = VPDataBaseOperation.veepooSDKGetBloodData(withDate: self.bloodDateLabel.text, andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        
        guard let bloodDataArray = bloodDataBaseArray else {
            self.bloodArray = [[String: String]]()
            testBloodTableView.reloadData()
            return
        }
        
        self.bloodArray = bloodDataArray as! Array<[String : String]>
        
        testBloodTableView.reloadData()
    }
```

## 血压单项测试

### 类名

`VPPeripheralBaseManage`, 参考SDK Demo `VPTestBloodController` 类实现

### 接口

开启或者关闭血压测试 血压测试与心率测试不同，血压测试一次大概需要50-55秒时间，开发者可以根据这个时间自定义测试进度，每次测试结束才会有结果，即一次测试只能有一组值

```objective-c
- (void)veepooSDKTestBloodStart:(BOOL)start
                       testMode:(NSUInteger)testMode
                     testResult:(void(^)(VPTestBloodState testBloodState, NSUInteger testBloodProgress, NSUInteger highBlood, NSUInteger lowBlood))testBloodResultBlock;
```

### 参数解释

| 参数名               | 类型       | 备注                                         |
| -------------------- | ---------- | -------------------------------------------- |
| start                | BOOL       | 开始/结束测量                                |
| testMode             | NSUInteger | 测量模式，0通用模式，1私人模式，默认通用模式 |
| testBloodResultBlock | Block      | 测试结果的回调                               |

### 返回数据

**testBloodResultBlock**

```objc
typedef NS_ENUM(NSInteger,VPTestBloodState) {//测试血压过程中的状态变化
    VPTestBloodStateTesting = 0,//开始检测血压，还没有测出结果
    VPTestBloodStateDeviceBusy = 1,//设备忙，测试结束
    VPTestBloodStateTestFail = 2,//测试无效，即为测试失败
    VPTestBloodStateTestInterrupt = 3,//测试被人为结束
    VPTestBloodStateComplete = 4,//测试已经完成
    VPTestBloodStateNoFunction = 5,//设备没有血压功能
};
```

| 参数名            | 类型             | 备注            |
| ----------------- | ---------------- | --------------- |
| testBloodState    | VPTestBloodState | 测量状态        |
| testBloodProgress | NSUInteger       | 测量进度，0-100 |
| highBlood         | NSUInteger       | 高压值          |
| lowBlood          | NSUInteger       | 低压值          |

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBloodStart(sender.isSelected, testMode: 0) { (testBloodState, progress, systolic, diastolic) in
            if sender.isSelected {
                weakSelf.testProgressLabel.text = "测试进度:" + String(progress) + "%"
                weakSelf.systolicLabel.text = "高压:" + String(systolic)
                weakSelf.diastolicLabel.text = "低压:" + String(diastolic)
                switch testBloodState {
                case .testing://正在测试中
                    print("正在测试中")
                case .deviceBusy:
                    _ = AppDelegate.showHUD(message: "设备正忙，结束测试", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .testFail:
                    _ = AppDelegate.showHUD(message: "测试失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .testInterrupt:
                    _ = AppDelegate.showHUD(message: "人为结束测试", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .complete:
                    _ = AppDelegate.showHUD(message: "测试已经完成", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .noFunction:
                    _ = AppDelegate.showHUD(message: "设备暂时没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                }
            }
        }
```

## 血压私人模式

血压私人模式需要用户先设置一个基准高低血压值，涉及读取和设置血压高低基准值

血压私人模式打开之后，血压自动测量的数据则以私人模式进行测量

### 类名

`VPPeripheralBaseManage`

### 接口

设置私人血压模式，设置的时候确保高压大于低压 如果设置模式为读取收缩压和舒张压都传0

```objective-c
- (void)veepooSDKSettingPersonalBloodWithModel:(VPDevicePrivateBloodModel *)privateBloodModel
                                   settingMode:(VPSettingFunctionState)settingMode
                                 successResult:(void(^)(VPDevicePrivateBloodModel *devicePrivateBloodModel))personalBloodModeResutBlock
                                 failureResult:(void(^)(void))personalBloodModeFailureBlock;
```

### 参数解释

| 参数名                        | 类型                      | 备注               |
| ----------------------------- | ------------------------- | ------------------ |
| privateBloodModel             | VPDevicePrivateBloodModel | 私人血压实例化对象 |
| settingMode                   | VPSettingFunctionState    | 设置模式           |
| personalBloodModeResutBlock   | Block                     |                    |
| personalBloodModeFailureBlock | Block                     |                    |

**VPDevicePrivateBloodModel**

| 参数名              | 类型       | 备注                                                         |
| ------------------- | ---------- | ------------------------------------------------------------ |
| systolicPressure    | NSUInteger | 收缩压即为高压                                               |
| diastolicPressure   | NSUInteger | 舒张压即为低压                                               |
| privateMode         | NSUInteger | 私人模式状态, 0为关闭 1为开启                                |
| dynamicCalibration  | BOOL       | 是否是需要动态校准的私人模式                                 |
| settingState        | NSUInteger | 0 是设置失败，1是设置成功，6是动态校准中，7是校准失败，8是校准成功，9是设备在被使用也属于校准失败的一种 |
| calibrationProgress | NSUInteger | 校准进度，仅带有动态校准功能的设备有用                       |

**VPSettingFunctionState**

```objc
typedef NS_ENUM(NSInteger, VPSettingFunctionState) {//设置获取读取某个功能
    VPReadFunctionState = 0, //读取某个功能的开关和有无
    VPSettingFunctionOpen = 1,//打开某个功能
    VPSettingFunctionClose = 2,//关闭某个功能
    VPSettingFunctionCancel = 3,//现在仅动态血压校准有效
    VPSettingFunction = 4,//设置某个功能
};
```

### 返回数据

设置/读取成功会触发`personalBloodModeResutBlock`回调，失败触发`personalBloodModeFailureBlock`

### 使用举例

```swift
//要先读取一下手环的数据，这个App显示一般以手环为主
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingPersonalBlood(with: VPDevicePrivateBloodModel(), settingMode: .readFunctionState, successResult: { (devicePrivateModel) in
            weakSelf.privateBloodModel = devicePrivateModel
            if devicePrivateModel?.systolicPressure == 0 && devicePrivateModel?.diastolicPressure == 0 {
                _ = AppDelegate.showHUD(message: "手环还没有设置此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }else {//展示给用户当前手环的值
                _ = AppDelegate.showHUD(message: "读取血压私人模式成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                weakSelf.systolicSlider.value = Float((devicePrivateModel?.systolicPressure)!)
                weakSelf.diastolicSlider.value = Float((devicePrivateModel?.diastolicPressure)!)
                weakSelf.bloodModeSegControl.selectedSegmentIndex = Int((devicePrivateModel?.privateMode)!)
                weakSelf.systolicLabel.text = "高压:" + String((devicePrivateModel?.systolicPressure)!)
                weakSelf.diastolicLabel.text = "低压:" + String((devicePrivateModel?.diastolicPressure)!)
                weakSelf.modeLabel.text = devicePrivateModel?.privateMode == 0 ? "模式:通用" : "模式:私人"
            }
        }) { 
            _ = AppDelegate.showHUD(message: "读取血压私人模式失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
```





# 血氧功能

## 血氧自动测量历史数据获取

### 前提

设备已连接且支持该功能，调用日常数据读取完成之后，从SDK数据库中获取血氧历史数据

注意，血氧功能为SDK的限制功能，需要先与我司商务联系，进行商务对接。在被限制情况下，仅返回血氧值

### 类名

`VPDataBaseOperation` , 参考SDK Demo `VPTestOxygenController` 类实现

### 接口

注意，接口返回的数据是全天血氧的，但是设备的血氧数据只在**0-7点有效**，此为算法与产品及测量条件综合评估做的限制。

```objective-c
+ (NSArray *)veepooSDKGetDeviceOxygenDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;
```

### 参数解释

| 参数名    | 类型     | 备注                            |
| --------- | -------- | ------------------------------- |
| queryDate | NSString | 要查询的日期，格式为:yyyy-MM-dd |
| tableID   | NSString | 设备的mac地址                   |

### 返回数据

字典数组

```objective-c
 NSDictionary *riginalDic = @{
        ApneaResult = 0;
        CardiacLoad = 0;
        HRV = 0;
        HeartValue = 65;
        Hypopnea = 0;
        HypoxiaTime = 0;
        IsHypoxia = 0;
        OxygenValue = 0;
        RespirationRate = 255;
        SportValue = 0;
        StepValue = 0;
        Temp1 = 75;
        Time = "00:00";
        protocolType = 2;
    };
```

| 参数名          | 类型     | 备注                                 |
| --------------- | -------- | ------------------------------------ |
| Time            | NSString | 时间                                 |
| OxygenValue     | NSString | 血氧值，限制模式下，仅返回本字段的值 |
| ApneaResult     | NSString | 呼吸暂停次数                         |
| CardiacLoad     | NSString | 心脏负荷                             |
| HRV             | NSString | HRV心率变异性                        |
| HeartValue      | NSString | 心率                                 |
| Hypopnea        | NSString | 低通气                               |
| HypoxiaTime     | NSString | 缺氧时间                             |
| IsHypoxia       | NSString | 是否缺氧                             |
| RespirationRate | NSString | 呼吸率                               |
| SportValue      | NSString | 运动量                               |
| StepValue       | NSString | 步数                                 |
| Temp1           | NSString | 调试参数                             |
| protocolTyp     | NSString | 协议版本                             |

### 使用举例

```objc
VPDataBaseOperation.veepooSDKGetDeviceOxygenData(withDate: "2020-05-27", andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
```

## 单项测量

### 前提

设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`

### 接口

开启或者关闭血氧测试，测试的原理与心率相同，即一次测试会有多组值

```objective-c
- (void)veepooSDKTestOxygenStart:(BOOL)start
                      testResult:(void(^)(VPTestOxygenState testOxygenState, NSUInteger oxygenValue))testOxygenResultBlock;
```

### 参数解释

| 参数名                | 类型  | 备注          |
| --------------------- | ----- | ------------- |
| start                 | BOOL  | 开启/关闭测量 |
| testOxygenResultBlock | Block | 测量结果回调  |

### 返回数据

测试结果的回调，当测试为校准状态时，value为校准进度，其他时候为血氧测试值

```objc
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
```

### 使用举例

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestOxygenStart(sender.isSelected) { (testOxygenState, oxygenValue) in
            if  sender.isSelected {
                switch testOxygenState {
                case .start:
                    _ = AppDelegate.showHUD(message: "正在做测试准备，请保持正确姿势", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                case .testing: //正在检测血氧，已经测出血氧值
                    weakSelf.currentOxygenValueLabel.text = "当前血氧值:" + String(oxygenValue) + "%"
                case .notWear: //佩戴检测没有通过，测试已经结束
                    _ = AppDelegate.showHUD(message: "佩戴检测未通过", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .deviceBusy: //设备正忙不能测试了，测试已经结束
                    _ = AppDelegate.showHUD(message: "设备端正在操作", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .over: //测试正常结束，人为结束
                    _ = AppDelegate.showHUD(message: "测试结束", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .noFunction: //设备没有此功能
                    _ = AppDelegate.showHUD(message: "设备没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .calibration: //校准中
                    weakSelf.currentOxygenValueLabel.text = "校准进度:" + String(oxygenValue) + "%"
                case .calibrationComplete: //校准完成
                    weakSelf.currentOxygenValueLabel.text = "校准进度:" + String(oxygenValue) + "%"
                default:
                    break
                }
            }else {
                if testOxygenState == .over {
                    _ = AppDelegate.showHUD(message: "测试结束", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                }
            }
        }
```



# 翻(转)腕亮屏功能

### 前提

设备已连接且支持该功能

```
var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[11] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有翻腕亮屏功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
```

### 类名

`VPPeripheralBaseManage`，参考SDK `VPRaiseHandSettingController` 类实现

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objc
- (void)veepooSDKSettingRaiseHandWithRaiseHandModel:(VPDeviceRaiseHandModel *)raiseHandModel
                                        settingMode:(NSUInteger)settingMode
                                      successResult:(void(^)(VPDeviceRaiseHandModel *raiseHandModel))settingRaiseHandResultBlock
                                      failureResult:(void(^)(void))settingRaiseHandFailureBlock;
```

### 参数解释

| 参数                         | 参数类型               | 备注                                                         |
| ---------------------------- | ---------------------- | ------------------------------------------------------------ |
| raiseHandModel               | VPDeviceRaiseHandModel | 翻腕亮屏模型                                                 |
| settingMode                  | NSUInteger             | 设置翻腕亮屏的模式0代表关闭 1代表开启 2代表读设备翻腕亮屏信息 |
| settingRaiseHandResultBlock  | Block                  | 成功回调                                                     |
| settingRaiseHandFailureBlock | Block                  | 失败回调                                                     |

* VPDeviceRaiseHandModel

| 参数                 | 参数类型   | 备注                                                         |
| -------------------- | ---------- | ------------------------------------------------------------ |
| raiseHandStartHour   | NSUInteger | 翻腕亮屏开始的小时 区间为0-23                                |
| raiseHandStartMinute | NSUInteger | 翻腕亮屏开始的分钟 区间为0-59                                |
| raiseHandEndHour     | NSUInteger | 翻腕亮屏结束的小时 区间为0-23                                |
| raiseHandEndMinute   | NSUInteger | 翻腕亮屏结束的分钟 区间为0-59                                |
| raiseHandState       | NSUInteger | 此为翻腕亮屏的状态，0代表关闭 1代表开启，开启的时候在设置时间内有效 |
| sensitive            | NSUInteger | 手环当前灵敏度                                               |
| defaultSensitive     | NSUInteger | 手环默认灵敏度，如果没有则代表没有灵敏度设置功能             |

### 示例代码

```swift
@IBAction func startSettingLongseatAction(_ sender: UIButton) {
        //建立模型
        let raiseHandModel = VPDeviceRaiseHandModel(raiseHandStartHour: UInt(startHourSlider.value), raiseHandStartMinute: UInt(startMinuteSlider.value), raiseHandEndHour: UInt(endHourSlider.value), raiseHandEndMinute: UInt(endMinuteSlider.value), raiseHandState: UInt(stateSegControl.selectedSegmentIndex), raiseHandSensitive: UInt(sensitiveSlider.value))
        
        //开始设置
        unowned let weakSelf = self;
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingRaiseHand(with: raiseHandModel, settingMode: UInt(stateSegControl.selectedSegmentIndex), successResult: { (raiseHandModel) in
            _ = AppDelegate.showHUD(message: "翻腕亮屏设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }) { 
            _ = AppDelegate.showHUD(message: "翻腕亮屏设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }
```



# 屏幕亮度调节功能

### 前提

设备已连接且支持该功能

```
var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage
            .sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[13] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有亮度调节功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
```

### 类名

`VPPeripheralBaseManage`，参考SDK `VPSettingBrightController` 类实现

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

> 比如你设置一个作用时间段为22:00-8:00 档位为firstBrightValue 其他时间段的亮度档位为otherBrightValue，那手环在22:00-8:00这个时间段按照firstBrightValue的档位显示亮度，其他时间显示otherBrightValue这个档位的亮度
>
>  如果设置为自动，会根据不同设备在不同时间段显示不同的档位，这个具体由手环决定
>
>  每个设备的最大档位也是不同的

```objc
- (void)veepooSDKSettingBrightWithBrightModel:(VPDeviceBrightModel *)brightModel
                                  settingMode:(NSUInteger)settingMode
                                successResult:(void(^)(VPDeviceBrightModel *brightModel))settingBrightResultBlock
                                failureResult:(void(^)(void))settingBrightFailureBlock;
```

### 参数解释

| 参数                      | 参数类型            | 备注                |
| ------------------------- | ------------------- | ------------------- |
| brightModel               | VPDeviceBrightModel | 亮度调节的模型      |
| settingMode               | NSUInteger          | 1代表设置 2代表读取 |
| settingBrightResultBlock  | Block               | 成功回调            |
| settingBrightFailureBlock | Block               | 失败回调            |

* VPDeviceBrightModel

| 参数                   | 参数类型  | 备注                                       |
| ---------------------- | --------- | ------------------------------------------ |
| firstBrightStartHour   | NSInteger | 第一个档位作用开始小时                     |
| firstBrightStartMinute | NSInteger | 第一个档位作用开始分钟                     |
| firstBrightEndHour     | NSInteger | 第一个档位作用结束小时                     |
| firstBrightEndMinute   | NSInteger | 第一个档位作用结束分钟                     |
| firstBrightValue       | NSInteger | 设置时间段的第一个档位                     |
| otherBrightValue       | NSInteger | 其他时间段亮度档位                         |
| isAutomatic            | BOOL      | 是否自动调节                               |
| maxBrightValue         | NSInteger | 最大的亮度调节档位                         |
| lastManualBrightValue  | NSInteger | 每次连接手动设置的otherBrightValue最后档位 |

### 示例代码

```swift
@IBAction func startSettingLongseatAction(_ sender: UIButton) {
        //建立亮度调节模型
        let brightModel = VPDeviceBrightModel(startHour: Int(brightStartHourSlider.value), startMinute: Int(brightStartMinuteSlider.value), endHour: Int(brightEndHourSlider.value), endMinute: Int(brightEndMinuteSlider.value), firstBrightValue: Int(firstBrightValueSlider.value), otherBrightValue: Int(otherBrightValueSlider.value))
        
        //开始设置
        unowned let weakSelf = self;
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingBright(with: brightModel, settingMode: 1, successResult: { (deviceBrightModel) in
            _ = AppDelegate.showHUD(message: "亮度调节设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }) { 
            _ = AppDelegate.showHUD(message: "亮度调节设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }
```



# 亮屏时长调节功能

### 前提

设备已连接且支持该功能

```swift
//1.先判断有没有此功能
let type = VPBleCentralManage.sharedBleManager().peripheralModel.screenDurationType
if type == 0 {
    _ = AppDelegate.showHUD(message: "该设备没有亮屏时长设置功能", hudModel: MBProgressHUDModeText, showView: view)
    return
}
```

### 类名

`VPPeripheralBaseManage`，参考SDK `VPSettingScreenDurationController` 类实现

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objc
- (void)veepooSDKSettingScreenDuration:(VPScreenDurationModel *)durationModel
                           settingMode:(NSUInteger)settingMode
                         successResult:(void(^)(VPScreenDurationModel *DurationModel))settingResult
                         failureResult:(void(^)(void))failureResult;
```

### 参数解释

| 参数          | 参数类型              | 备注                                      |
| ------------- | --------------------- | ----------------------------------------- |
| durationModel | VPScreenDurationModel | 设置屏幕时长模型，读取的时候不为nil就可以 |
| settingMode   | NSUInteger            | 1代表设置 2代表读取                       |
| settingResult | Block                 | 成功回调                                  |
| failureResult | Block                 | 失败回调                                  |

* VPScreenDurationModel

| 参数            | 参数类型  | 备注                     |
| --------------- | --------- | ------------------------ |
| currentDuration | NSInteger | 当前的亮屏时长           |
| defaultDuration | NSInteger | 设备默认的亮屏时长       |
| minDuration     | NSInteger | 设备可设置最小的亮屏时长 |
| maxDuration     | NSInteger | 设备可设置最大的亮屏时长 |

### 示例代码

```swift
//2.读取当前设备亮屏时长的信息
        VPBleCentralManage.sharedBleManager()
            .peripheralManage.veepooSDKSettingScreenDuration(VPScreenDurationModel(), settingMode: 2, successResult: {[weak self] (durationModel) in
                _ = AppDelegate.showHUD(message: "读取信息成功", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
                self?.durationModel = durationModel!
                self?.updateUI()
        }) {[weak self] in
                _ = AppDelegate.showHUD(message: "读取信息失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
        }
```



# 健康提醒功能

### 前提

设备已连接且支持该功能

### 类名

`VPPeripheralBaseManage`，参考SDK `VPDeviceHealthRemindViewController` 类实现

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objc
- (void)veepooSDKSettingHealthRemindWithRemindType:(VPDeviceHealthRemindType)remindType
                                            opCode:(NSInteger)opCode
                                       remindModel:(VPDeviceHealthRemindModel *)remindModel
                                       resultBlock:(void(^)(BOOL success, VPDeviceHealthRemindModel *successModel))resultBlock
                          deviceInfoDidChangeBlock:(void(^)(VPDeviceHealthRemindModel *changeModel))deviceInfoDidChangeBlock;
```

### 参数解释

| 参数                     | 参数类型                  | 备注                                           |
| ------------------------ | ------------------------- | ---------------------------------------------- |
| remindType               | VPDeviceHealthRemindType  | 提醒类型                                       |
| opCode                   | NSInteger                 | 1表示设置 2表示读取，读取时remindModel可以传空 |
| remindModel              | VPDeviceHealthRemindModel | 设置模型，仅在设置时有效                       |
| resultBlock              | Block                     | 结果回调                                       |
| deviceInfoDidChangeBlock | Block                     | 设备端信息存在变更时触发回调                   |

```objc
// 健康提醒功能类型
typedef NS_ENUM(NSUInteger, VPDeviceHealthRemindType) {
    VPDeviceHealthRemindTypeAll,             // 所有
    VPDeviceHealthRemindTypeLongSeat,        // 久坐
    VPDeviceHealthRemindTypeDrinkWater,      // 喝水
    VPDeviceHealthRemindTypeLookFarAway,     // 远眺
    VPDeviceHealthRemindTypeSport,           // 运动
    VPDeviceHealthRemindTypeTakeMedicine,    // 吃药
    VPDeviceHealthRemindTypeRead,            // 看书
    VPDeviceHealthRemindTypeTrip,            // 出行
    VPDeviceHealthRemindTypeWashHands,       // 洗手
};
```

* VPDeviceHealthRemindModel

| 参数           | 参数类型                 | 备注                                     |
| -------------- | ------------------------ | ---------------------------------------- |
| type           | VPDeviceHealthRemindType | 提醒类型                                 |
| startHour      | NSInteger                | 开始时间-小时，请自行限制范围在[0,23]内  |
| startMinute    | NSInteger                | 开始时间-分钟，请自行限制范围在[0, 59]内 |
| endHour        | NSInteger                | 结束时间-小时，请自行限制范围在[0,23]内  |
| endMinute      | NSInteger                | 结束时间-分钟，请自行限制范围在[0, 59]内 |
| remindInterval | NSInteger                | 提醒间隔时长                             |
| open           | BOOL                     | 提醒是否开启                             |

### 示例代码

```swift
// 读取
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingHealthRemind(with: .all, opCode: 2, remindModel: nil) { [weak self]success, model in
            if (success) {
                if let model = model {
                    let index = Int(model.type.rawValue)
                    let start = String(format: "%02d:%02d", model.startHour, model.startMinute)
                    let end = String(format: "%02d:%02d", model.endHour, model.endMinute)
                    print("type:\(NameStrArr[index]), 起始:\(start), 结束- \(end), 间隔- \(model.remindInterval), 开启:\(model.open)")
                    _ = AppDelegate.showHUD(message: "读取成功", hudModel: MBProgressHUDModeText, showView: self!.view)
                    self!.mArr.append(model)
                    self!.tableView.reloadData()
                }
            }
        } deviceInfoDidChange: { [weak self] model in
            self!.deviceDidChange(model: model)
        }
```



# 身体成分功能

身体成分功能依赖于ECG，与ECG测量姿态一致，在手表正常佩戴情况下，无法自动测量。故该功能只有手动测量，分为指令开启测量和设备端离线测量。

离线测量指该次测量结果存储在手表端中，具有持久化的效果，连接状态下，可以将该数据通过[日常数据读取接口](#日常数据读取功能)读取到SDK中.

### 前提

支持该功能，可通过 `VPBleCentralManage.sharedBleManager().peripheralModel.bodyCompositionType` 判断

### 类名

`VPPeripheralBaseManage`，参考SDK `VPBodyCompositionViewController` 类实现

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

```objective-c
/// 身体成分单次测量开启或关闭
/// - Parameters:
///   - start: 开始或关闭
///   - progress: 进度回调，lead 0表示导联过了(表示手在电极片上)，1表示导联没过
///   - testResult: 结果回调
- (void)veepooSDKTestBodyCompositionStart:(BOOL)start
                                 progress:(void(^)(NSInteger lead, NSProgress *progress))progress
                               testResult:(void(^)(VPDeviceBodyCompositionState state, VPBodyCompositionValueModel *model))testResult;
```

```objective-c
/// 设备端测量身体成分完成回调
@property (nonatomic, copy) void(^deviceTestBodyCompositionDidFinishBlock)(void);
```

### 参数解释

| 参数       | 参数类型 | 备注               |
| ---------- | -------- | ------------------ |
| start      | BOOL     | 开始或关闭         |
| progress   | Block    | 进度和导联状态回调 |
| testResult | Block    | 结果回调           |

```objective-c
// 设备身体成分测量状态
typedef NS_ENUM(NSUInteger, VPDeviceBodyCompositionState) {
    VPDeviceBodyCompositionStateNoFunction,    // 设备没有此功能
    VPDeviceBodyCompositionStateDeviceBusy,    // 设备正忙不能开始测试
    VPDeviceBodyCompositionStateOver,          // 测试正常结束，人为结束
    VPDeviceBodyCompositionStateLowPower,      // 设备低电
    VPDeviceBodyCompositionStateFailure,       // 测试失败
    VPDeviceBodyCompositionStateComplete,      // 测试已经完成
};
```

VPBodyCompositionValueModel 的参数解释及值域范围 

身高、体重、性别 SDK 内部没有持久化数据，需应用层自行处理

| 参数 | 参数类型 | -               | -                                | -                                  | -                                  | -                                  |
| ---- | -------- | ---- | ---- | ---- | ---- | ---- |
|date| 测量日期 yyyy-MM-dd | - | - | - | - | - |
|testTime| 测量时间(结束时间) HH:mm:ss | **有效范围** | **偏低范围** | **正常范围** | **偏高范围** | **过高范围** |
|bmi| BMI | [4,1114] kg/m2 | [4,18.5)偏低 | [18.5,24.0)正常 | [24.0,28.0)超重 | [28.0,1114]肥胖 |
|bodyFatPercentage| 体脂率 | [2,48]% | 男 [2,17], 女 [2,25], 偏低 | 男 [18,22], 女 [26,31], 正常 | 男 [23,29], 女 [32,39], 超重 | 男 [30,48], 女 [40,48], 肥胖 |
|fatMass| 脂肪量 | [10,248] kg |  |  |  |  |
|leanBodyMass| 去脂体重 | [1,132] kg | [1,45.8)偏低 | [45.8,55.9], 标准 | (55.9,132], 优秀 |  |
|muscleRate| 肌肉率 | [39,90]% | [39,68.1), 偏低 | [68.1,84.8], 标准 | (84.8,90], 优秀 |  |
|muscleMass| 肌肉量 | [9,248] kg | [9,40.8), 偏低 | [40.8,50.8], 标准 | (50.8,248], 优秀 |  |
|subcutaneousFat| 皮下脂肪 | [1,47]% | [1,8.6), 偏低 | [8.6,16.7], 正常 | (16.7,47], 偏高 |  |
|bodyMoisture| 体内水分 | [28,79]% | [28,53.4), 偏低 | [53.4,66.6], 标准 | (66.6,79], 优秀 |  |
|waterContent| 含水量 | [7,217] kg |                                  |                                    |                                    |  |
|skeletalMuscleRate| 骨骼肌率 | [13,69]% | [13,25), 偏低 | [25,35], 标准 | (35,69], 优秀 |  |
|boneMass| 骨量 | [2.3,4.8] kg | [2.3,2.9), 偏低 | [2.9,3.7], 标准 | (3.7,4.8], 优秀 |  |
|proportionOfProtein| 蛋白质占比 | [4,26]% | [4,14.1), 偏低 | [14.1,17.7], 标准 | (17.7,26], 优秀 |  |
|proteinAmount| 蛋白质量 | [1,71] kg |  |  |  |  |
|basalMetabolicRate| 基础代谢率 | [25,14995] kcal | [25,1619), 偏低 | [1619,14995], 优秀 |  |  |



### 示例代码

测量

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBodyCompositionStart(true) { lead, progress in
            if let progress = progress {
                print("lead = \(lead), progress = \(progress)")
            }
        } testResult: { [weak self]state, model in
            if state == .complete {
                if let model = model {
                    print(model)
                }
            }
            if state == .failure {
                print("测量失败")
            }
            if state == .over {
                print("手动结束")
            }
            self?.opButton.isSelected = false
        }
```

离线存储数据获取

```swift
let tableID = VPBleCentralManage.sharedBleManager()?.peripheralModel.deviceAddress;
        var date = "2023-09-22"
        let arr = VPDataBaseOperation.veepooSDKGetDeviceOffStoreBodyComposition(withDate: date, andTableID: tableID)
        
        guard let arr = arr else {
            print("没有数据")
            return
        }
        if arr.isEmpty {
            print("没有数据")
            return
        }
        print(arr)
```



# 血液成分功能

血液成分功能支持校准逻辑，同血压校准类似

有日常数据

### 前提

支持该功能，可通过 `VPBleCentralManage.sharedBleManager().peripheralModel.bloodAnalysisType` 判断

### 类名

`VPPeripheralBaseManage`，参考SDK `VPBloodAnalysisViewController` 类实现

获取途径：**VPBleCentralManage.sharedBleManager().peripheralManage**

### 接口

单次测量

```objective-c
/// 血液成分单次测量开启或关闭
/// @param start 开启/关闭
/// @param isPersonalModel 是否为私人模式
/// @param progress 进度回调
/// @param testResult 结果回调
- (void)veepooSDKTestBloodAnalysisStart:(BOOL)start
                        isPersonalModel:(BOOL)isPersonalModel
                               progress:(void(^)(NSProgress *progress))progress
                             testResult:(void(^)(VPDeviceBloodAnalysisState state, VPBloodAnalysisResultModel *model))testResult;
```

私人模式

```objective-c
/// 血液成分私人模式操作
/// @param opCode  1为设置 2为读取
/// @param open 是否开启，开启后，则设备端自动测量的血液成分依据设置的私人模式值进行测量
/// @param model 要设置的私人模式值，读取时可为空
/// @param result 结果回调
- (void)veepooSDKBloodAnalysisPersonalWithOpCode:(NSInteger)opCode
                                            open:(BOOL)open
                                           model:(VPBloodAnalysisResultModel *)model
                                          result:(void(^)(BOOL success, BOOL open, VPBloodAnalysisResultModel *model))result;
```

日常数据

```objective-c
/// 获取设备某一天的血液成分自动测量数据
/// @param queryDate 要查询的日期格式为2021-06-07
/// @param tableID 设备的mac地址，获取哪个设备的数据
+ (NSArray<VPDailyBloodAnalysisModel *> *)veepooSDKGetDeviceBloodAnalysisDataWithDate:(NSString *)queryDate
                                                                           andTableID:(NSString *)tableID;
```

### 参数解释

| 参数            | 参数类型 | 备注           |
| --------------- | -------- | -------------- |
| start           | BOOL     | 开始或关闭     |
| isPersonalModel | BOOL     | 是否为私人模式 |
| progress        | Block    | 进度回调       |
| testResult      | Block    | 结果回调       |

```objective-c
// 血液成分测量状态
typedef NS_ENUM(NSUInteger, VPDeviceBloodAnalysisState) {
    VPDeviceBloodAnalysisStateNoFunction,    // 设备没有此功能
    VPDeviceBloodAnalysisStateDeviceBusy,    // 设备正忙不能开始测试
    VPDeviceBloodAnalysisStateOver,          // 测试正常结束，人为结束
    VPDeviceBloodAnalysisStateLowPower,      // 设备低电
    VPDeviceBloodAnalysisStateFailure,       // 测试失败
    VPDeviceBloodAnalysisStateNotWear,       // 设备佩戴检测未通过
    VPDeviceBloodAnalysisStateComplete,      // 测试已经完成
};
```

VPBloodAnalysisResultModel

| 参数                        | 参数类型 | 备注                                 | 有效范围      | 正常范围                                       |
| --------------------------- | -------- | ------------------------------------ | ------------- | ---------------------------------------------- |
| uricAcidValue               | double   | 尿酸 ，一位小数点，单位μmol/L        | [90.0,1000.0] | 男[150.0,420.0]μmol/L<br/>女[90.0,360.0]μmol/L |
| totalCholesterolValue       | double   | 总胆固醇，二位小数点，单位mmol/L     | [0.01,20.00]  | [2.8,5.17]mmol/L                               |
| triglycerideValue           | double   | 甘油三酸酯，二位小数点，单位mmol/L   | [0.01,20.00]  | [2.8,5.17]mmol/L                               |
| highDensityLipoproteinValue | double   | 高密度脂蛋白，二位小数点，单位mmol/L | [0.01,20.00]  | [2.8,5.17]mmol/L                               |
| lowDensityLipoproteinValue  | double   | 低密度脂蛋白，二位小数点，单位mmol/L | [0.01,20.00]  | [2.8,5.17]mmol/L                               |

单位转换公式:

| 参数                        | 参数名称     | 单位切换        | 转换公式               |
| --------------------------- | ------------ | --------------- | ---------------------- |
| uricAcidValue               | 尿酸         | μmol/L => mg/dL | 1μmol/L = 59.5 mg/dL   |
| totalCholesterolValue       | 总胆固醇     | mmol/L => mg/dL | 38.67mmol/L = 1 mg/dL  |
| triglycerideValue           | 甘油三酸酯   | mmol/L => mg/dL | 88.545mmol/L = 1 mg/dL |
| highDensityLipoproteinValue | 高密度脂蛋白 | mmol/L => mg/dL | 38.67mmol/L = 1 mg/dL  |
| lowDensityLipoproteinValue  | 低密度脂蛋白 | mmol/L => mg/dL | 38.67mmol/L = 1 mg/dL  |

### 示例代码

测量

```swift
VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBloodAnalysisStart(ture, isPersonalModel: false, progress: { progress in
            if let progress = progress {
                print("progress = \(progress)")
            }
        }, testResult: { [weak self]state, model in
            if state == .complete {
                if let model = model {
                    print(model)
                }
            }
            if state == .failure {
                print("测量失败")
            }
            if state == .over {
                print("手动结束")
            }
            self?.opButton.isSelected = false
        })
```

校准

```swift
let setModel:VPBloodAnalysisResultModel = .init()
        setModel.uricAcidValue = 9.4
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKBloodAnalysisPersonal(withOpCode: 1, open: false, model: nil) { success, openState, model in
            if let model = model {
                print(model)
            }
        }
```

日常数据

```swift
let tableID = VPBleCentralManage.sharedBleManager()?.peripheralModel.deviceAddress;
        let arr = VPDataBaseOperation.veepooSDKGetDeviceBloodAnalysisData(withDate: "2023-10-18", andTableID: tableID)
        
        guard let arr = arr else {
            print("当日没有血液成分数据")
            return
        }
```

