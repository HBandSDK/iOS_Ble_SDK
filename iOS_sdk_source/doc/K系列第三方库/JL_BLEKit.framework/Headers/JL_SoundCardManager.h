//
//  JL_SoundCardManager.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(uint8_t, JL_KalaoIndex) {
    JL_KalaoIndexReverberation  = 0,    //卡拉OK 混响
    JL_KalaoIndexDelayed        = 1,    //卡拉OK 延时
    JL_KalaoIndexVolume         = 2,    //卡拉OK 音量
};

@interface JL_SoundCardManager : JL_FunctionBaseManager

extern NSString *kJL_MANAGER_KALAOK_Data;
#pragma mark ---> 设置卡拉OK【index、value】
/**
 *  @param index 参数类型 JL_KalaoIndex 目前支持混响、延时、音量的设置。（具体可以看固件的json文件不遗憾）
 *  @param value 数值         0-100
 */
-(void)cmdSetKalaokIndex:(JL_KalaoIndex)index Value:(uint16_t)value;

#pragma mark ---> 设置卡拉OK【MIC EQ增益】
/**
 *  @param array @[@(0),@(0),@(0),@(0),@(0)]  单个取值范围 [-8.0 , +8.0]。
 */
-(void)cmdSetKaraokeMicEQ:(NSArray*)array;

@end

NS_ASSUME_NONNULL_END
