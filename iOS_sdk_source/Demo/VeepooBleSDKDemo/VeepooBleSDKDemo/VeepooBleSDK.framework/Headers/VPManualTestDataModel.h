//
//  VPManualTestDataModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2024/10/19.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class VPManualBloodPressureModel,VPManualBloodSugarModel,VPManualBloodOxygenModel,VPManualHeartRateModel,VPManualBodyTempModel,VPManualBloodCompModel;


@interface VPManualTestDataModel : NSObject

@property (nonatomic, copy) NSString *mac;

@property (nonatomic, strong) NSArray<VPManualBloodPressureModel *> *bloodPressureArr;

@property (nonatomic, strong) NSArray<VPManualBodyTempModel *> *bodyTempArr;

@property (nonatomic, strong) NSArray<VPManualBloodCompModel *> *bloodCompArr;

@property (nonatomic, strong) NSArray<VPManualHeartRateModel *> *heartRateArr;

@property (nonatomic, strong) NSArray<VPManualBloodOxygenModel *> *bloodOxygenArr;

@property (nonatomic, strong) NSArray<VPManualBloodSugarModel *> *bloodSugarArr;

- (instancetype)initWithData:(NSData *)sourceData;

@end

NS_ASSUME_NONNULL_END
