//
//  JL_FmManager.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"


typedef NS_ENUM(UInt8, JL_FCmdFM) {
    JL_FCmdFMPP                     = 0x01, //FM 暂停/播放
    JL_FCmdFMPonitBefore            = 0x02, //上一个频点
    JL_FCmdFMPonitNext              = 0x03, //下一个频点
    JL_FCmdFMChannelBefore          = 0x04, //上一个频道
    JL_FCmdFMChannelNext            = 0x05, //下一个频道
    JL_FCmdFMSearch                 = 0x06, //扫描
    JL_FCmdFMChannelSelect          = 0x07, //选择频道
    JL_FCmdFMChannelDelete          = 0x08, //删除频道
    JL_FCmdFMFrequencySelect        = 0x09, //选择频点
    JL_FCmdFMFrequencyDelete        = 0x0a, //删除频点
};

typedef NS_ENUM(UInt8, JL_FMSearch) {
    JL_FMSearchALL                  = 0x00, //FM 暂停/播放
    JL_FMSearchForward              = 0x01, //向前搜索
    JL_FMSearchBackward             = 0x02, //向后搜索
    JL_FMSearchStop                 = 0x03, //停止搜索
};

NS_ASSUME_NONNULL_BEGIN

@interface JL_FmManager : JL_FunctionBaseManager

#pragma mark ---> FM相关操作
/**
 @param cmd FM功能
 @param search FM搜索
 @param channel FM频道
 @param frequency FM频点
 @param result 返回结果
 */
-(void)cmdFm:(JL_FCmdFM)cmd
      Saerch:(JL_FMSearch)search
     Channel:(uint8_t)channel
   Frequency:(uint16_t)frequency
      Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END

