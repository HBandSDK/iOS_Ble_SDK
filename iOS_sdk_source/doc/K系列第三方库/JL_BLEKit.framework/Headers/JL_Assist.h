//
//  JL_Assist.h
//  QCY_Demo
//
//  Created by 杰理科技 on 2021/8/12.
//  Copyright © 2021 杰理科技. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN
typedef void(^JL_Assist_BK)(BOOL isPaired);

@class JL_ManagerM;

@interface JL_Assist : NSObject
@property(strong,nonatomic)JL_ManagerM        *mCmdManager;   //命令中心
@property(strong,nonatomic)NSString           *mService;      //服务号
@property(strong,nonatomic)NSString           *mRcsp_W;       //特征：RCSP写
@property(strong,nonatomic)NSString           *mRcsp_R;       //特征：RCSP读
@property(strong,nonatomic)NSData *__nullable mPairKey;       //握手(配对)秘钥
@property(assign,nonatomic)BOOL               mNeedPaired;    //是否需要配对

/// Execute in a method 「- (void)centralManagerDidUpdateState:」
/// @param state CBManagerState
-(void)assistUpdateState:(CBManagerState)state;

/// Execute in a method 「- (void)peripheral:didDiscoverServices:」
/// @param service CBService
/// @param peripheral CBPeripheral
-(void)assistDiscoverCharacteristicsForService:(CBService*)service
                                    Peripheral:(CBPeripheral*)peripheral;

/// Execute in a method 「- (void)peripheral:didUpdateNotificationStateForCharacteristic:error:」
/// @param characteristic CBCharacteristic
/// @param peripheral CBPeripheral
/// @param result JL_Assist_BK （YES:配对成功   NO:配对失败）
-(void)assistUpdateCharacteristic:(nonnull CBCharacteristic *)characteristic
                       Peripheral:(CBPeripheral*)peripheral
                           Result:(JL_Assist_BK)result;

/// Execute in a method 「- (void)peripheral:didUpdateValueForCharacteristic:error:」
/// @param characteristic CBCharacteristic
-(void)assistUpdateValueForCharacteristic:(CBCharacteristic *)characteristic;

/// Execute in a method 「- (void)centralManager:didDisconnectPeripheral:error:」
/// @param peripheral CBPeripheral
-(void)assistDisconnectPeripheral:(CBPeripheral *)peripheral;

@end

NS_ASSUME_NONNULL_END
