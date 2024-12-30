//
//  VPBodyCompositionValueModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/10/10.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 身高、体重、性别 SDK 内部无数据，需应用层自行处理
@interface VPBodyCompositionValueModel : NSObject

/// 测量日期 yyyy-MM-dd
@property (nonatomic, strong) NSString *date;

/// 测量时间(结束时间) HH:mm:ss
@property (nonatomic, strong) NSString *testTime;

/// 是否为设备端测量
@property (nonatomic, assign) BOOL isDeviceTest;

/// 身高 cm 需先调用设置个人信息接口
@property (nonatomic, assign) NSUInteger stature;

/// 体重 kg
@property (nonatomic, assign) NSUInteger weight;

/// 性别 0表示女性 1表示男性
@property (nonatomic, assign) NSUInteger gender;

/// BMI
@property (nonatomic, strong) NSString *bmi;

/// 体脂率 百分比
@property (nonatomic, strong) NSString *bodyFatPercentage;

/// 脂肪量 单位kg
@property (nonatomic, strong) NSString *fatMass;

/// 去脂体重 单位kg
@property (nonatomic, strong) NSString *leanBodyMass;

/// 肌肉率 百分比
@property (nonatomic, strong) NSString *muscleRate;

/// 肌肉量 单位kg
@property (nonatomic, strong) NSString *muscleMass;

/// 皮下脂肪 百分比
@property (nonatomic, strong) NSString *subcutaneousFat;

/// 体内水分 百分比
@property (nonatomic, strong) NSString *bodyMoisture;

/// 含水量 单位kg
@property (nonatomic, strong) NSString *waterContent;

/// 骨骼肌率 百分比
@property (nonatomic, strong) NSString *skeletalMuscleRate;

/// 骨量 单位kg
@property (nonatomic, strong) NSString *boneMass;

/// 蛋白质占比 百分比
@property (nonatomic, strong) NSString *proportionOfProtein;

/// 蛋白质量 单位kg
@property (nonatomic, strong) NSString *proteinAmount;

/// 基础代谢率 kcal
@property (nonatomic, strong) NSString *basalMetabolicRate;

/// 蓝牙数据解析方法
/// - Parameter data: 设备回传的蓝牙数据
- (void)parseAppTestWithData:(NSData *)data;

+ (NSArray<NSString *> *)ignoreProperties;

@end

NS_ASSUME_NONNULL_END

