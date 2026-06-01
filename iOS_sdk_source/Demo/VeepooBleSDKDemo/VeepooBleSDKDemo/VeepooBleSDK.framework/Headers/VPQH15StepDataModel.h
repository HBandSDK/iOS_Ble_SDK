//
//  VPQH15StepDataModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/6/1.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPQH15StepDataModel : NSObject

@property (nonatomic, assign) uint64_t timestamp;

@property (nonatomic, assign) uint64_t step;

@property (nonatomic, assign) uint16_t readId;

@end

NS_ASSUME_NONNULL_END
