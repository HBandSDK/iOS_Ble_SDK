//
//  VPBleCentralManage.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/7.
//  Copyright © 2017年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPeripheralManage.h"

////SDK版本号
//FOUNDATION_EXPORT NSString * const VeepooBleSDKVersion;

@interface VPBleCentralManage : NSObject<CBPeripheralDelegate,CBCentralManagerDelegate>

//是否输出log日志，默认打开
@property (nonatomic, assign) BOOL isLogEnable;

//中心设备管理者
@property (nonatomic, strong) CBCentralManager *centralManager;

//已经连接的设备模型
@property (nonatomic, strong) VPPeripheralModel *peripheralModel;

//密码验证成功后设备的指令发送和数据接收管理
@property (nonatomic, strong) VPPeripheralBaseManage *peripheralManage;

//设备是否处于DFULang模式，如果在DFULang模式验证密码后不能读取数据
@property (nonatomic, assign) BOOL isDFULangMode;

//系统蓝牙状态改变的回调
@property (nonatomic, copy) void(^VPBleCentralManageChangeBlock)(VPCentralManagerState BleState);

//设备连接状态改变的回调
@property (nonatomic, copy) void(^VPBleConnectStateChangeBlock)(VPDeviceConnectState deviceConnectState);

//设备连接状态改变的回调
@property (nonatomic, copy) void(^VPBleDFUConnectStateChangeBlock)(VPDeviceConnectState deviceConnectState);

//连接状态,发送指令前确保连接
@property (nonatomic, assign) BOOL isConnected;


/**
 是否自动连接，默认是YES
 */
@property (nonatomic, assign) BOOL automaticConnection;

//创建实例
+ (instancetype)sharedBleManager;

//开始扫描设备
- (void)veepooSDKStartScanDeviceAndReceiveScanningDevice:(ReceiveScanningDevice)scanningDevice;

//停止扫描
- (void)veepooSDKStopScanDevice;

//开始连接设备
- (void)veepooSDKConnectDevice:(VPPeripheralModel *)peripheralModel deviceConnectBlock:(DeviceConnectBlock)connectBlock;

//断开连接，不再自动连接，人为断开连接SDK不再负责帮助自动重连
- (void)veepooSDKDisconnectDevice;

/**
 设置或验证密码，每次寻找到服务之后都会自动的去发送一次密码，默认密码是0000
 每次发送密码都会同步一下手机本地的时间给手环
 
 @param type 同步密码的类型是验证还是设置
 @param password 4位0-9的字符串，如果是设置则传nil
 @param result 0是失败 1是成功
 */
- (void)veepooSDKSynchronousPasswordWithType:(SynchronousPasswordType)type password:(NSString *)password SynchronizationResult:(SynchronizationResultBlock)result;

@end




