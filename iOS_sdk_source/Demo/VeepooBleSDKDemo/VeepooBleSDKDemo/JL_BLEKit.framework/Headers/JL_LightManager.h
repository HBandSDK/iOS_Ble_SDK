//
//  JL_LightManager.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_LightManager : JL_FunctionBaseManager

#pragma mark ---> 设置灯光
/**
 *  设置灯光
 *  @param lightState 灯光状态
 *  @param lightMode 灯光模式
 *  @param red 红色色值
 *  @param green 绿色色值
 *  @param blue 蓝色色值
 *  @param flashIndex 闪烁模式index
 *  @param flashFreqIndex 闪烁频率
 *  @param sceneIndex 情景模式
 *  @param hue 色调，范围0-360
 *  @param saturation 饱和度，0-100
 *  @param lightness 亮度，0-100
 */
-(void)cmdSetState:(JL_LightState)lightState
              Mode:(JL_LightMode)lightMode
               Red:(uint8_t)red
             Green:(uint8_t)green
              Blue:(uint8_t)blue
         FlashInex:(JL_LightFlashModeIndex)flashIndex
         FlashFreq:(JL_LightFlashModeFrequency)flashFreqIndex
        SceneIndex:(JL_LightSceneMode)sceneIndex
               Hue:(uint16_t)hue
        Saturation:(uint8_t)saturation
         Lightness:(uint8_t)lightness;

@end

NS_ASSUME_NONNULL_END
