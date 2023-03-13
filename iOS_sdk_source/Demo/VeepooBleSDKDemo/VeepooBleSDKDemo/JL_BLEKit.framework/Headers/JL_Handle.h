//
//  JL_Handle.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/10.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FlashOperateManager.h>
#import "JL_BLEAction.h"
#import "JL_RCSP.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  收到设备返回的XM_PKG的回调。
 */
extern NSString *kJL_CMD_RECEIVE;       //XM_RCSP【接收】

@protocol JL_HandleDelegate <NSObject>
@optional
-(void)onHandleOutputPKG:(JL_PKG*)pkg;
@end

@interface JL_Handle : NSObject
@property(nonatomic,weak)id<JL_HandleDelegate>delegate;

/**
输入BLE数据
@param data  设备过来的数据
*/
-(void)inputHandleData:(NSData*)data;

/**[实例]
向设备发送JL_PKG数据包。
@param pkg JL_PKG数据模型
@param name 设备名字
*/
-(NSData*)sendPackage:(JL_PKG*)pkg WithName:(NSString*)name;

+(void)logPackage:(JL_PKG*)pkg WithName:(NSString *__nullable)name IsSend:(BOOL)isSend;

@end

NS_ASSUME_NONNULL_END
