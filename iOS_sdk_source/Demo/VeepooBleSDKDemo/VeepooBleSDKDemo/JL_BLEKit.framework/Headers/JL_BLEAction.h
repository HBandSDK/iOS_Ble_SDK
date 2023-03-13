//
//  JL_BLEAction.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/10.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  BLE数据通知
 */
extern NSString *kJL_RCSP_RECEIVE;      //Rcsp数据【接收】
extern NSString *kJL_RCSP_SEND;         //Rcsp数据【发送】


typedef void(^ATC_Block)(BOOL ret);
@protocol JL_BLEActionDelegate <NSObject>
@optional
-(void)onPairOutputData:(NSData*)data;

@end

@interface JL_BLEAction : NSObject
@property(nonatomic,weak)id<JL_BLEActionDelegate>delegate;

+(id)sharedMe;

/**
 过滤其余蓝牙设备
 @param key 过滤码
 @param advertData 蓝牙广播字典
 @return YES：认证设备 NO：杂余设备
 */
+(NSDictionary*)bluetoothKey_1:(NSData*)key Filter:(NSDictionary*)advertData;

/**
 蓝牙设备配对
 @param pKey 配对码
 @param bk   配对回调YES：成功 NO：失败
 */
-(void)bluetoothPairingKey:(NSData *__nullable)pKey Result:(ATC_Block)bk;
-(void)inputPairData:(NSData*)rData;

#pragma mark - 蓝牙根据广播包回连

/**
 *  获取广播包kCBAdvDataManufacturerData里面 'JLOTA' 标识的蓝牙地址
 *  @param kCBAdvDataManufacturerData 广播包
 */
+ (NSString * _Nullable)otaBleMacAddressFromCBAdvDataManufacturerData:(NSData *)kCBAdvDataManufacturerData;

/**
 *  判断当前蓝牙地址是否等于广播包kCBAdvDataManufacturerData里面的蓝牙地址
 *  @param otaBleMacAddress ota升级中设备的蓝牙地址
 *  @param kCBAdvDataManufacturerData 广播包
 */
+ (Boolean)otaBleMacAddress:(NSString *)otaBleMacAddress isEqualToCBAdvDataManufacturerData:(NSData *)kCBAdvDataManufacturerData;

@end

NS_ASSUME_NONNULL_END
