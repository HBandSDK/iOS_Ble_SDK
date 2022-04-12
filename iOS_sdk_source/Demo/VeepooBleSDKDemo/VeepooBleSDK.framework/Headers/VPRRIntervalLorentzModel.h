//
//  VPRRIntervalLorentzModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2022/4/8.
//  Copyright © 2022 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIColor.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPRRIntervalLorentzModel : NSObject

/// x轴坐标
@property (nonatomic, assign) NSInteger xCoordinate;
/// y轴坐标
@property (nonatomic, assign) NSInteger yCoordinate;
/// 对应点{xCoordinate, yCoordinate} 的颜色
@property (nonatomic, strong) UIColor *color;

@end

NS_ASSUME_NONNULL_END
