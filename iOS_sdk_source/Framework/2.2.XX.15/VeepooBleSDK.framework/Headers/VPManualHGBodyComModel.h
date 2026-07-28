//
//  VPManualHGBodyComModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/7/7.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPManualHGBodyComModel : NSObject


/// BMI
@property (nonatomic, assign) double bmi;
/// 体脂率 百分比
@property (nonatomic, assign) double bodyFatPercentage;
/// 脂肪量 单位kg
@property (nonatomic, assign) double fatMass;
/// 去脂体重 单位kg
@property (nonatomic, assign) double leanBodyMass;
/// 肌肉率 百分比
@property (nonatomic, assign) double muscleRate;
/// 肌肉量 单位kg
@property (nonatomic, assign) double muscleMass;
/// 皮下脂肪 百分比
@property (nonatomic, assign) double subcutaneousFat;
/// 体内水分 百分比
@property (nonatomic, assign) double bodyMoisture;
/// 含水量 单位kg
@property (nonatomic, assign) double waterContent;
/// 骨骼肌率 百分比
@property (nonatomic, assign) double skeletalMuscleRate;
/// 骨量 单位kg
@property (nonatomic, assign) double boneMass;
/// 蛋白质占比 百分比
@property (nonatomic, assign) double proportionOfProtein;
/// 蛋白质量 单位kg
@property (nonatomic, assign) double proteinAmount;
/// 基础代谢率 kcal
@property (nonatomic, assign) double basalMetabolicRate;

@end

NS_ASSUME_NONNULL_END
