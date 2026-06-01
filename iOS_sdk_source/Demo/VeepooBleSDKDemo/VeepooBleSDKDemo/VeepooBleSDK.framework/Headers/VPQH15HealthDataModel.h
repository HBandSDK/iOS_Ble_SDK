//
//  VPQH15HealthDataModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/6/1.
//  Copyright © 2026 veepoo. All rights reserved.
//

// VPQH15HealthDataModel.h
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 状态枚举 (1:↑ 2:→ 3:↓)
typedef NS_ENUM(UInt8, AgeStatusType) {
    AgeStatusIncrease = 1,
    AgeStatusStable = 2,
    AgeStatusDecrease = 3
};

/// 达标类型枚举
typedef NS_ENUM(UInt8, AchievementType) {
    AchievementTypeBiosAgeEvent = 0,
    AchievementTypeHeartAgeEvent = 1,
    AchievementTypeFitnessAgeEvent = 2,
    AchievementTypeStepsGoalEvent = 3,
    AchievementTypeNutritionGoalEvent = 4,
    AchievementTypeAllGoalsAchievedEvent = 5,
    AchievementTypeNewFitnessGoalsEvent = 6
};

@interface VPQH15HealthDataModel : NSObject

#pragma mark - 1. 年龄类参数 (TAG 0x10-0x12)
@property (nonatomic, assign) UInt8 biosAge;
@property (nonatomic, assign) UInt8 heartAge;
@property (nonatomic, assign) UInt8 fitnessAge;
@property (nonatomic, assign) BOOL hasBiosAge;
@property (nonatomic, assign) BOOL hasHeartAge;
@property (nonatomic, assign) BOOL hasFitnessAge;

#pragma mark - 2. 年龄状态 (TAG 0x13-0x15)
@property (nonatomic, assign) AgeStatusType biosAgeStatus;
@property (nonatomic, assign) AgeStatusType heartAgeStatus;
@property (nonatomic, assign) AgeStatusType fitnessAgeStatus;
@property (nonatomic, assign) BOOL hasBiosAgeStatus;
@property (nonatomic, assign) BOOL hasHeartAgeStatus;
@property (nonatomic, assign) BOOL hasFitnessAgeStatus;

#pragma mark - 3. 年龄变化值 (TAG 0x16-0x18)
@property (nonatomic, assign) UInt8 biosAgeChange;
@property (nonatomic, assign) UInt8 heartAgeChange;
@property (nonatomic, assign) UInt8 fitnessAgeChange;
@property (nonatomic, assign) BOOL hasBiosAgeChange;
@property (nonatomic, assign) BOOL hasHeartAgeChange;
@property (nonatomic, assign) BOOL hasFitnessAgeChange;

#pragma mark - 4. 90天趋势数据 (TAG 0x19-0x1B)
@property (nonatomic, strong) NSArray<NSNumber *> *biosAge90Days;
@property (nonatomic, strong) NSArray<NSNumber *> *heartAge90Days;
@property (nonatomic, strong) NSArray<NSNumber *> *fitnessAge90Days;
@property (nonatomic, assign) BOOL hasBiosAge90Days;
@property (nonatomic, assign) BOOL hasHeartAge90Days;
@property (nonatomic, assign) BOOL hasFitnessAge90Days;

#pragma mark - 5. 上月/去年单点数据 (TAG 0x1C-0x21)
@property (nonatomic, assign) UInt8 biosAgeLastMonth;
@property (nonatomic, assign) UInt8 heartAgeLastMonth;
@property (nonatomic, assign) UInt8 fitnessAgeLastMonth;
@property (nonatomic, assign) UInt8 biosAgeLastYear;
@property (nonatomic, assign) UInt8 heartAgeLastYear;
@property (nonatomic, assign) UInt8 fitnessAgeLastYear;
@property (nonatomic, assign) BOOL hasBiosAgeLastMonth;
@property (nonatomic, assign) BOOL hasHeartAgeLastMonth;
@property (nonatomic, assign) BOOL hasFitnessAgeLastMonth;
@property (nonatomic, assign) BOOL hasBiosAgeLastYear;
@property (nonatomic, assign) BOOL hasHeartAgeLastYear;
@property (nonatomic, assign) BOOL hasFitnessAgeLastYear;

#pragma mark - 6. 上月/去年状态 (TAG 0x22-0x27)
@property (nonatomic, assign) AgeStatusType biosAgeLastMonthStatus;
@property (nonatomic, assign) AgeStatusType heartAgeLastMonthStatus;
@property (nonatomic, assign) AgeStatusType fitnessAgeLastMonthStatus;
@property (nonatomic, assign) AgeStatusType biosAgeLastYearStatus;
@property (nonatomic, assign) AgeStatusType heartAgeLastYearStatus;
@property (nonatomic, assign) AgeStatusType fitnessAgeLastYearStatus;
@property (nonatomic, assign) BOOL hasBiosAgeLastMonthStatus;
@property (nonatomic, assign) BOOL hasHeartAgeLastMonthStatus;
@property (nonatomic, assign) BOOL hasFitnessAgeLastMonthStatus;
@property (nonatomic, assign) BOOL hasBiosAgeLastYearStatus;
@property (nonatomic, assign) BOOL hasHeartAgeLastYearStatus;
@property (nonatomic, assign) BOOL hasFitnessAgeLastYearStatus;

#pragma mark - 7. 上月/去年变化值 (TAG 0x28-0x2D)
@property (nonatomic, assign) UInt8 biosAgeLastMonthChange;
@property (nonatomic, assign) UInt8 heartAgeLastMonthChange;
@property (nonatomic, assign) UInt8 fitnessAgeLastMonthChange;
@property (nonatomic, assign) UInt8 biosAgeLastYearChange;
@property (nonatomic, assign) UInt8 heartAgeLastYearChange;
@property (nonatomic, assign) UInt8 fitnessAgeLastYearChange;
@property (nonatomic, assign) BOOL hasBiosAgeLastMonthChange;
@property (nonatomic, assign) BOOL hasHeartAgeLastMonthChange;
@property (nonatomic, assign) BOOL hasFitnessAgeLastMonthChange;
@property (nonatomic, assign) BOOL hasBiosAgeLastYearChange;
@property (nonatomic, assign) BOOL hasHeartAgeLastYearChange;
@property (nonatomic, assign) BOOL hasFitnessAgeLastYearChange;

#pragma mark - 8. 三大慢病风险 (TAG 0x30-0x32)
@property (nonatomic, assign) UInt8 cardiovascularRisk;
@property (nonatomic, assign) UInt8 dementiaRisk;
@property (nonatomic, assign) UInt8 diabetesRisk;
@property (nonatomic, assign) BOOL hasCardiovascularRisk;
@property (nonatomic, assign) BOOL hasDementiaRisk;
@property (nonatomic, assign) BOOL hasDiabetesRisk;

#pragma mark - 9. 三大慢病风险状态 (TAG 0x33-0x35)
@property (nonatomic, assign) AgeStatusType cardiovascularRiskStatus;
@property (nonatomic, assign) AgeStatusType dementiaRiskStatus;
@property (nonatomic, assign) AgeStatusType diabetesRiskStatus;
@property (nonatomic, assign) BOOL hasCardiovascularRiskStatus;
@property (nonatomic, assign) BOOL hasDementiaRiskStatus;
@property (nonatomic, assign) BOOL hasDiabetesRiskStatus;

#pragma mark - 10. 三大慢病风险变化值 (TAG 0x36-0x38)
@property (nonatomic, assign) UInt8 cardiovascularRiskChange;
@property (nonatomic, assign) UInt8 dementiaRiskChange;
@property (nonatomic, assign) UInt8 diabetesRiskChange;
@property (nonatomic, assign) BOOL hasCardiovascularRiskChange;
@property (nonatomic, assign) BOOL hasDementiaRiskChange;
@property (nonatomic, assign) BOOL hasDiabetesRiskChange;

#pragma mark - 11. 心血管细化风险 (TAG 0x39-0x3B)
@property (nonatomic, assign) UInt8 heartAttackRisk;
@property (nonatomic, assign) UInt8 strokeRisk;
@property (nonatomic, assign) UInt8 heartFailureRisk;
@property (nonatomic, assign) BOOL hasHeartAttackRisk;
@property (nonatomic, assign) BOOL hasStrokeRisk;
@property (nonatomic, assign) BOOL hasHeartFailureRisk;

#pragma mark - 12. 心血管细化风险状态 (TAG 0x3C-0x3E)
@property (nonatomic, assign) AgeStatusType heartAttackRiskStatus;
@property (nonatomic, assign) AgeStatusType strokeRiskStatus;
@property (nonatomic, assign) AgeStatusType heartFailureRiskStatus;
@property (nonatomic, assign) BOOL hasHeartAttackRiskStatus;
@property (nonatomic, assign) BOOL hasStrokeRiskStatus;
@property (nonatomic, assign) BOOL hasHeartFailureRiskStatus;

#pragma mark - 13. 心血管细化风险变化值 (TAG 0x3F-0x41)
@property (nonatomic, assign) UInt8 heartAttackRiskChange;
@property (nonatomic, assign) UInt8 strokeRiskChange;
@property (nonatomic, assign) UInt8 heartFailureRiskChange;
@property (nonatomic, assign) BOOL hasHeartAttackRiskChange;
@property (nonatomic, assign) BOOL hasStrokeRiskChange;
@property (nonatomic, assign) BOOL hasHeartFailureRiskChange;

#pragma mark - 14. 生活质量风险 (TAG 0x42-0x44)
@property (nonatomic, assign) UInt8 memoryDeclineRisk;
@property (nonatomic, assign) UInt8 fallInjuryRisk;
@property (nonatomic, assign) UInt8 independentLivingRisk;
@property (nonatomic, assign) BOOL hasMemoryDeclineRisk;
@property (nonatomic, assign) BOOL hasFallInjuryRisk;
@property (nonatomic, assign) BOOL hasIndependentLivingRisk;

#pragma mark - 15. 生活质量风险状态 (TAG 0x45-0x47)
@property (nonatomic, assign) AgeStatusType memoryDeclineRiskStatus;
@property (nonatomic, assign) AgeStatusType fallInjuryRiskStatus;
@property (nonatomic, assign) AgeStatusType independentLivingRiskStatus;
@property (nonatomic, assign) BOOL hasMemoryDeclineRiskStatus;
@property (nonatomic, assign) BOOL hasFallInjuryRiskStatus;
@property (nonatomic, assign) BOOL hasIndependentLivingRiskStatus;

#pragma mark - 16. 生活质量风险变化值 (TAG 0x48-0x4A)
@property (nonatomic, assign) UInt8 memoryDeclineRiskChange;
@property (nonatomic, assign) UInt8 fallInjuryRiskChange;
@property (nonatomic, assign) UInt8 independentLivingRiskChange;
@property (nonatomic, assign) BOOL hasMemoryDeclineRiskChange;
@property (nonatomic, assign) BOOL hasFallInjuryRiskChange;
@property (nonatomic, assign) BOOL hasIndependentLivingRiskChange;

#pragma mark - 17. 糖尿病并发症风险 (TAG 0x4B-0x4D)
@property (nonatomic, assign) UInt8 kidneyDiseaseRisk;
@property (nonatomic, assign) UInt8 nerveDamageRisk;
@property (nonatomic, assign) UInt8 visionLossRisk;
@property (nonatomic, assign) BOOL hasKidneyDiseaseRisk;
@property (nonatomic, assign) BOOL hasNerveDamageRisk;
@property (nonatomic, assign) BOOL hasVisionLossRisk;

#pragma mark - 18. 糖尿病并发症风险状态 (TAG 0x4E-0x50)
@property (nonatomic, assign) AgeStatusType kidneyDiseaseRiskStatus;
@property (nonatomic, assign) AgeStatusType nerveDamageRiskStatus;
@property (nonatomic, assign) AgeStatusType visionLossRiskStatus;
@property (nonatomic, assign) BOOL hasKidneyDiseaseRiskStatus;
@property (nonatomic, assign) BOOL hasNerveDamageRiskStatus;
@property (nonatomic, assign) BOOL hasVisionLossRiskStatus;

#pragma mark - 19. 糖尿病并发症风险变化值 (TAG 0x51-0x53)
@property (nonatomic, assign) UInt8 kidneyDiseaseRiskChange;
@property (nonatomic, assign) UInt8 nerveDamageRiskChange;
@property (nonatomic, assign) UInt8 visionLossRiskChange;
@property (nonatomic, assign) BOOL hasKidneyDiseaseRiskChange;
@property (nonatomic, assign) BOOL hasNerveDamageRiskChange;
@property (nonatomic, assign) BOOL hasVisionLossRiskChange;

#pragma mark - 20. 健康指数 (TAG 0x54-0x55)
@property (nonatomic, assign) UInt8 nutritionStatus;
@property (nonatomic, assign) UInt8 goalStatus;
@property (nonatomic, assign) BOOL hasNutritionStatus;
@property (nonatomic, assign) BOOL hasGoalStatus;

#pragma mark - 21. 时间戳 (TAG 0xA1)
@property (nonatomic, assign) UInt32 timestamp;
@property (nonatomic, assign) BOOL hasTimestamp;

#pragma mark - 达标类型 (TAG 0x56)
@property (nonatomic, assign) AchievementType achievementType;

/// 打包成下发数据
- (NSData *)packToData;

/// 重置所有has标志
- (void)resetAllHasFlags;

/// 清空所有数据
- (void)clearAllData;

/// 随机生成测试数据
- (void)generateRandomData;

@end

NS_ASSUME_NONNULL_END
