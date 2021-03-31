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

//Whether to output log log, open by default 是否输出log日志，默认打开
@property (nonatomic, assign) BOOL isLogEnable;

//连接后是否弹系统配对窗口，默认Yes
@property (nonatomic, assign) BOOL isAutoShowPair;

//Bluetooth Center Device Manager 中心设备管理者
@property (nonatomic, strong) CBCentralManager *centralManager;

//Connected device model 已经连接的设备模型
@property (nonatomic, strong) VPPeripheralModel *peripheralModel;

//Command transmission and data reception management of the device after successful password verification 密码验证成功后设备的指令发送和数据接收管理
@property (nonatomic, strong) VPPeripheralBaseManage *peripheralManage;

//Whether the device is in DFULang mode, if the password cannot be read after verifying the password in DFULang mode 设备是否处于DFULang模式，如果在DFULang模式验证密码后不能读取数据
@property (nonatomic, assign) BOOL isDFULangMode;

//System Bluetooth status change callback 系统蓝牙状态改变的回调
@property (nonatomic, copy) void(^VPBleCentralManageChangeBlock)(VPCentralManagerState BleState);

//Callback of device connection status change 设备连接状态改变的回调
@property (nonatomic, copy) void(^VPBleConnectStateChangeBlock)(VPDeviceConnectState deviceConnectState);

//The device enters the callback of the DFU connection status change 设备进入DFU连接状态改变的回调
@property (nonatomic, copy) void(^VPBleDFUConnectStateChangeBlock)(VPDeviceConnectState deviceConnectState);

//Connection status, ensure connection before sending instructions 连接状态,发送指令前确保连接
@property (nonatomic, assign) BOOL isConnected;

//Whether to connect automatically, the default is YES 是否自动连接，默认是YES
@property (nonatomic, assign) BOOL automaticConnection;

//Watch language settings follow the mobile phone system, the default is yes 手表语言设置跟随手机系统，默认是YES
@property (nonatomic, assign) BOOL systemLanguage;

//Create an instance 创建实例
+ (instancetype)sharedBleManager;

//Start scanning device 开始扫描设备
- (void)veepooSDKStartScanDeviceAndReceiveScanningDevice:(ReceiveScanningDevice)scanningDevice;

//Stop scanning 停止扫描
- (void)veepooSDKStopScanDevice;

//Start connecting devices 开始连接设备
- (void)veepooSDKConnectDevice:(VPPeripheralModel *)peripheralModel deviceConnectBlock:(DeviceConnectBlock)connectBlock;

//Disconnected, no longer automatically connected, artificially disconnected SDK is no longer responsible for helping to automatically reconnect 断开连接，不再自动连接，人为断开连接SDK不再负责帮助自动重连
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
- (void)veepooSDKSynchronousPasswordWithType:(SynchronousPasswordType)type password:(NSString *)password SynchronizationResult:(SynchronizationResultBlock)result;


/// 读取已连接设备的RSSI值  ⚠️设备未连接时无效
/// @param block 回调函数
- (void)veepooSDKReadConnectedPeripheralRSSIValue:(VPReadRSSIBlock)block;

@end




