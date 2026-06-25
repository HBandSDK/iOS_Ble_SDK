//
//  VPManualTestDataModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2024/10/19.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class VPManualBloodPressureModel,VPManualBloodSugarModel,VPManualBloodOxygenModel,VPManualHeartRateModel,VPManualBodyTempModel,VPManualBloodCompModel, VPManualHealthGlanceModel,VPManualHRVModel,VPManualMetModel,VPManualStressModel,VPManualFatigueLevelModel,VPManualEmotionModel,VPManualGSRModel;


@interface VPManualTestDataModel : NSObject

@property (nonatomic, copy) NSString *mac;

@property (nonatomic, strong) NSArray<VPManualBloodPressureModel *> *bloodPressureArr;

@property (nonatomic, strong) NSArray<VPManualBodyTempModel *> *bodyTempArr;

@property (nonatomic, strong) NSArray<VPManualBloodCompModel *> *bloodCompArr;

@property (nonatomic, strong) NSArray<VPManualHeartRateModel *> *heartRateArr;

@property (nonatomic, strong) NSArray<VPManualBloodOxygenModel *> *bloodOxygenArr;

@property (nonatomic, strong) NSArray<VPManualBloodSugarModel *> *bloodSugarArr;

@property (nonatomic, strong) NSArray<VPManualHealthGlanceModel *> *healthGlanceArr;

@property (nonatomic, strong) NSArray<VPManualHRVModel *> *hrvArr;

@property (nonatomic, strong) NSArray<VPManualGSRModel *> *gsrArr;

@property (nonatomic, strong) NSArray<VPManualEmotionModel *> *emotionArr;

@property (nonatomic, strong) NSArray<VPManualFatigueLevelModel *> *fatigueLevelArr;

@property (nonatomic, strong) NSArray<VPManualStressModel *> *stressArr;

@property (nonatomic, strong) NSArray<VPManualMetModel *> *metArr;

- (instancetype)initWithData:(NSData *)sourceData;

@end

NS_ASSUME_NONNULL_END
