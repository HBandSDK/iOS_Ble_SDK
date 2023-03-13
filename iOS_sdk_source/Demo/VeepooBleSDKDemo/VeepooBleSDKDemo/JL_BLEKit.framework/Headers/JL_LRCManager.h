//
//  JL_LRCManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/17.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_LRCType) {
    JL_LRCTypeDone                  = 1,    //LRC已传输完
    JL_LRCTypeBusy                  = 2,    //设备忙碌
    JL_LRCTypeDoneFail              = 0x0e, //传输失败
};
typedef void(^JL_LRC_BK)(NSString* __nullable lrc, JL_LRCType type);
typedef void(^JL_LRC_BK_1)(NSData* __nullable lrc, JL_LRCType type);

@interface JL_LRCManager : JL_FunctionBaseManager

#pragma mark ---> 获取LRC歌词
/**
 @param result 返回LRC数据
 */
-(void)cmdLrcMonitorResult:(JL_LRC_BK __nullable)result;
-(void)cmdLrcMonitorResult_1:(JL_LRC_BK_1 __nullable)result;

@end

NS_ASSUME_NONNULL_END
