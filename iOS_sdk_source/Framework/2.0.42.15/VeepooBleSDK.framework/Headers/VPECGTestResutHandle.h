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

@interface VPECGTestResutHandle : NSObject

+ (NSArray <VPECGTestResultModle *>*)resultWithModel:(VPECGTestDataModel *)ecgTestDataModel;


+ (NSArray <VPECGTestResultModle *>*)resultWithPTTResultData:(NSData *)resultData;

//+ (NSArray <VPECGTestResultModle *>*)resultWithPTTModel:(VPECGPTTTestDataModel *)pttTestDataModel;

@end

NS_ASSUME_NONNULL_END
