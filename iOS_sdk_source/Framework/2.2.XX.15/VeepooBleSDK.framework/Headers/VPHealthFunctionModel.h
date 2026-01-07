//
//  VPHealthFunctionModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2025/8/5.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

// 健康辅助评估支持的功能
typedef NS_OPTIONS(NSUInteger, VPFuncAssessmentType) {
    VPFuncAssessmentTypeNone         = 0,        // 不支持
    VPFuncAssessmentTypeBloodGlucose = 1 << 7,   // 支持血糖
    VPFuncAssessmentTypeBloodComp    = 1 << 6,   // 支持血液成分
    VPFuncAssessmentTypeBodyComp     = 1 << 5    // 支持身体成分
};

/// 所有支持控制的功能
typedef NS_ENUM(NSInteger, VPHealthFunctionType) {
    VPHealthFunctionTypeNone = -1,               //无
    VPHealthFunctionTypeBloodGlucose = 0,        //血糖
    VPHealthFunctionTypeBloodPressure,           //血压
    VPHealthFunctionTypeBloodOxygen,             //血氧
    VPHealthFunctionTypeBodyTemp,                //体温
    VPHealthFunctionTypeHrv,                     //HRV
    VPHealthFunctionTypeStress,                  //压力
    VPHealthFunctionTypeMetabolites,             //梅脱
    VPHealthFunctionTypeBloodComp,               //血液成分
    VPHealthFunctionTypeBodyComp,                //身体成分
    VPHealthFunctionTypeMicrobodyCheck,          //微体检
    VPHealthFunctionTypeEmotions,                //情绪
    VPHealthFunctionTypeFatigueLevel,            //疲劳度
    VPHealthFunctionTypeNuclearRadiation,        //核辐射
    VPHealthFunctionTypeFallDetection,           //跌倒提醒
    VPHealthFunctionTypeAIChat,                  //AI问答
    VPHealthFunctionTypeAIDial,                  //AI表盘
    VPHealthFunctionTypePicoelectric,            //皮电
};

NS_ASSUME_NONNULL_BEGIN

@interface VPHealthFunctionModel : NSObject

/// 功能类型
@property (nonatomic, assign) VPHealthFunctionType type;

/// 是否支持该功能
@property (nonatomic, assign) BOOL support;

/// 如果支持，该功能是否开启
@property (nonatomic, assign) BOOL open;

- (instancetype)initWithType:(VPHealthFunctionType)type support:(BOOL)support open:(BOOL)open;

@end

NS_ASSUME_NONNULL_END
