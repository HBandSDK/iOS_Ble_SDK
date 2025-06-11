//
//  VPManualTestDataModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2024/10/19.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class VPManualBloodPressureModel;
@interface VPManualTestDataModel : NSObject

@property (nonatomic, copy) NSString *mac;

@property (nonatomic, strong) NSArray<VPManualBloodPressureModel *> *bloodPressureArr;

- (instancetype)initWithData:(NSData *)sourceData;

@end

NS_ASSUME_NONNULL_END
