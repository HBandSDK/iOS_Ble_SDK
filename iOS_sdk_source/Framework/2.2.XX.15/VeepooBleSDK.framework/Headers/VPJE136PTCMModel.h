//
//  VPJE136PTCMModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/4/22.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"
NS_ASSUME_NONNULL_BEGIN

@interface VPJE136PTCMModel : NSObject

@property (nonatomic, assign) uint32_t timestamp;

@property (nonatomic, assign) uint16_t bloodStasis;      // 血瘀
@property (nonatomic, assign) uint16_t dampHeat;         // 湿热
@property (nonatomic, assign) uint16_t specialAllergy;   // 特禀
@property (nonatomic, assign) uint16_t yangDeficiency;   // 阳虚
@property (nonatomic, assign) uint16_t yinDeficiency;    // 阴虚
@property (nonatomic, assign) uint16_t phlegmDampness;   // 痰湿
@property (nonatomic, assign) uint16_t balanced;         // 平和
@property (nonatomic, assign) uint16_t qiStagnation;     // 气郁
@property (nonatomic, assign) uint16_t qiDeficiency;     // 气虚
@property (nonatomic, assign) uint16_t largeIntestine;   // 大肠
@property (nonatomic, assign) uint16_t gallbladder;      // 胆
@property (nonatomic, assign) uint16_t liver;            // 肝
@property (nonatomic, assign) uint16_t spleen;           // 脾
@property (nonatomic, assign) uint16_t lung;             // 肺
@property (nonatomic, assign) uint16_t smallIntestine;   // 小肠
@property (nonatomic, assign) uint16_t sanjiaoBladder;   // 三焦膀胱
@property (nonatomic, assign) uint16_t kidney;           // 肾
@property (nonatomic, assign) uint16_t stomach;          // 胃
@property (nonatomic, assign) uint16_t heart;            // 心脏

@property (nonatomic, assign) uint32_t option;

@end

NS_ASSUME_NONNULL_END
