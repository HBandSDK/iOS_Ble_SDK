//
//  JL_MusicControlManager.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_Tools.h"

typedef NS_ENUM(UInt8, JL_FCmdMusic) {
    JL_FCmdMusicPP                  = 0x01, //PP按钮
    JL_FCmdMusicPREV                = 0x02, //上一曲
    JL_FCmdMusicNEXT                = 0x03, //下一曲
    JL_FCmdMusicMODE                = 0x04, //切换播放模式
    JL_FCmdMusicEQ                  = 0x05, //EQ
    JL_FCmdMusicFastBack            = 0x06, //快退
    JL_FCmdMusicFastPlay            = 0x07, //快进
};


NS_ASSUME_NONNULL_BEGIN

@interface JL_MusicControlManager : JL_FunctionBaseManager

#pragma mark ---> 设置播放模式
/**
 @param mode 模式
 0x01:全部循环; 0x02:设备循环; 0x03:单曲循环; 0x04:随机播放; 0x05:文件夹循环
 */
-(void)cmdSetSystemPlayMode:(JL_MusicMode)mode;

#pragma mark ---> 快进快退
/**
 @param cmd 快进或者快退枚举
 @param sec 时间
 @param result 返回结果
 */
-(void)cmdFastPlay:(JL_FCmdMusic)cmd
            Second:(uint16_t)sec
            Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END
