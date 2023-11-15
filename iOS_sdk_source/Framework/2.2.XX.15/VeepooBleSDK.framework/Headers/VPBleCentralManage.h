//
//  VPBleCentralManage.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/7.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPeripheralManage.h"

//SDK版本号
//FOUNDATION_EXPORT NSString * const VeepooBleSDKVersion;

@interface VPBleCentralManage : NSObject<CBPeripheralDelegate,CBCentralManagerDelegate>

///Whether to output log log, open by default
///是否输出log日志，默认打开
@property (nonatomic, assign) BOOL isLogEnable;

///连接后是否弹系统配对窗口，默认Yes
@property (nonatomic, assign) BOOL isAutoShowPair;

///连接过程的小时制式控制，默认Yes
@property (nonatomic, assign) BOOL is24HourFormat;

///是否默认连接K系列的BT，仅在 isAutoShowPair为YES且系统版本>=iOS13才有效，默认Yes
///如果系统版本低于13，无法自动连接BT，需要提示用户前往手机系统蓝牙自行连接
@property (nonatomic, assign) BOOL isAutoConnectBT NS_AVAILABLE_IOS(13_0);

///是否按照厂商ID进行扫描过滤，默认No。如果开启，将扫描不到非我司厂商ID的设备
///Whether to scan and filter based on manufacturer ID, default No.
@property (nonatomic, assign) BOOL manufacturerIDFilter;

///The timeout period after the connection is initiated. If the connection is not successful or fails within connectionTimeout seconds after the connection is initiated.
///the connection timeout state is triggered. The default is 30 seconds.
///连接发起后的超时时长，连接发起后connectionTimeout秒内未连接成功或失败，则触发连接超时状态，默认为30秒
@property (nonatomic, assign) NSUInteger connectionTimeout;

///Bluetooth Center Device Manager
///中心设备管理者
@property (nonatomic, strong) CBCentralManager *centralManager;

///Connected device model
///已经连接的设备模型
@property (nonatomic, strong) VPPeripheralModel *peripheralModel;

///Command transmission and data reception management of the device after successful password verification
///密码验证成功后设备的指令发送和数据接收管理
@property (nonatomic, strong) VPPeripheralBaseManage *peripheralManage;

///Whether the device is in DFULang mode, if the password cannot be read after verifying the password in DFULang mode
///设备是否处于DFULang模式，如果在DFULang模式验证密码后不能读取数据，内部会将其它非OTA指令全部屏蔽，表现为无响应
@property (nonatomic, assign, readonly) BOOL isDFULangMode;

///System Bluetooth status change callback
///系统蓝牙状态改变的回调
@property (nonatomic, copy) void(^VPBleCentralManageChangeBlock)(VPCentralManagerState BleState);

///Callback of device connection status change
///设备连接状态改变的回调
@property (nonatomic, copy) void(^VPBleConnectStateChangeBlock)(VPDeviceConnectState deviceConnectState);

///The device enters the callback of the DFU connection status change
///设备进入DFU连接状态改变的回调
@property (nonatomic, copy) void(^VPBleDFUConnectStateChangeBlock)(VPDeviceConnectState deviceConnectState);

///Connection status, ensure connection before sending instructions
///连接状态,发送指令前确保连接
@property (nonatomic, assign) BOOL isConnected;

///Whether to connect automatically, the default is YES
///是否自动连接，默认是YES
@property (nonatomic, assign) BOOL automaticConnection;

///Watch language settings follow the mobile phone system, the default is yes
///手表语言设置跟随手机系统，默认是YES
@property (nonatomic, assign) BOOL systemLanguage;

///Singleton object
///单例对象
+ (instancetype)sharedBleManager;

- (instancetype)init NS_UNAVAILABLE;

///Start scanning device
///开始扫描设备
- (void)veepooSDKStartScanDeviceAndReceiveScanningDevice:(ReceiveScanningDevice)scanningDevice;

///Start connecting devices
///开始连接设备
- (void)veepooSDKConnectDevice:(VPPeripheralModel *)peripheralModel
            deviceConnectBlock:(DeviceConnectBlock)connectBlock;

///自行实现扫描连接设备时使用，适合集成多家SDK场景，连接状态使用：VPBleConnectStateChangeBlock
///不可与 {@link veepooSDKConnectDevice:deviceConnectBlock:} 混用
- (void)veepooSDKSelfScanConnectDevice:(CBPeripheral *)peripheral
                    deviceConnectBlock:(DeviceConnectBlock)connectBlock;

///Stop scanning
///停止扫描
- (void)veepooSDKStopScanDevice;

///Disconnected, no longer automatically connected, artificially disconnected SDK is no longer responsible for helping to automatically reconnect
///断开连接，不再自动连接，人为断开连接SDK不再负责帮助自动重连
- (void)veepooSDKDisconnectDevice;

/**
 Set or verify the password, and each time you find the service, it will automatically send the password once. The default password is 0000.
 Every time you send a password, it will synchronize the local time of the phone to the bracelet.
 设置或验证密码，每次寻找到服务之后都会自动的去发送一次密码，默认密码是0000
 每次发送密码都会同步一下手机本地的时间给手环
 
 @param type Is the type of sync password verified or set? 同步密码的类型是验证还是设置
 @param password 4 digits 0-9 string, if it is set, pass nil 4位0-9的字符串，如果是设置则传nil
 @param result 0 is a failure 1 is a success 0是失败 1是成功
 */
- (void)veepooSDKSynchronousPasswordWithType:(SynchronousPasswordType)type
                                    password:(NSString *)password
                       SynchronizationResult:(SynchronizationResultBlock)result;

@end




