//
//  VPECGTestResutHandle.h
//  WYPHealthyThird
//
//  Created by 张冲 on 2018/12/5.
//  Copyright © 2018 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPECGTestDataModel.h"
NS_ASSUME_NONNULL_BEGIN

@interface VPECGTestResultModle : NSObject

//根据状态从对照表中获取疾病诊断信息
@property (nonatomic, assign) int diseaseState;

//下面无效
//疾病名称
@property (nonatomic, strong) NSString *diseaseName;
//医学解释
@property (nonatomic, strong) NSString *explain;

@end

// 多诊断报告对象
@interface VPECGTestResultReportModle : NSObject

/// 疾病风险 [1,99] 心律失常
@property (nonatomic, strong) NSString *diseaseRisk;
/// 压力指数 [1,99]
@property (nonatomic, strong) NSString *pressureIndex;
/// 疲劳指数 [1,99]
@property (nonatomic, strong) NSString *fatigueIndex;
/// 心肌炎风险 [1,99]
@property (nonatomic, strong) NSString *myocarditisRisk;
/// 冠心病风险 [1,99]
@property (nonatomic, strong) NSString *chdRisk;
/// 血管硬化风险 [1,99]
@property (nonatomic, strong) NSString *angiosclerosisRisk;
/// 32种疾病风险等级
@property (nonatomic, strong) NSArray *riskParamArr;

/// QRS时长 ，单位ms
@property (nonatomic, strong) NSString *qrsTime;
/// QRS振幅 ，单位mv 【float 软件乘100取整】
@property (nonatomic, strong) NSString *qrsAmp;
/// pwv的实时均值，测量范围[6,20]m/s,动脉粥样硬化指标，异常范围 > 15m/s 【float 软件乘10取整】
@property (nonatomic, strong) NSString *pwvMeanVal;
/// 平均st段振幅 ，单位mv，[-0.05,0.1]mv为正常范围 【float 软件乘100取整】
@property (nonatomic, strong) NSString *stMeanAmp;
/// SDNN 窦性心搏间标准差,正常值为(141±39)ms
@property (nonatomic, strong) NSString *diseaseSdnn;
/// RMSSD 相邻正常心动周期差值的均方根，正常值范围为（27±12）ms
@property (nonatomic, strong) NSString *diseaseRmssd;


@end

@interface VPECGTestResutHandle : NSObject

+ (NSArray <VPECGTestResultModle *>*)resultWithModel:(VPECGTestDataModel *)ecgTestDataModel;

+ (NSArray <VPECGTestResultModle *>*)resultWithPTTResultData:(NSData *)resultData;

/// 获取多诊断的结果对象
/// - Parameter ecgTestDataModel: ecg测量结果对象
+ (VPECGTestResultReportModle *)resultReportWithModel:(VPECGTestDataModel *)ecgTestDataModel;

//+ (NSArray <VPECGTestResultModle *>*)resultWithPTTModel:(VPECGPTTTestDataModel *)pttTestDataModel;

@end

NS_ASSUME_NONNULL_END
