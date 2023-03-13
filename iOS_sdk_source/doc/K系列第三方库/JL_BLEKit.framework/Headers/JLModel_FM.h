//
//  JLModel_FM.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModel_FM : NSObject<NSCoding>
@property (assign,nonatomic) uint8_t        fmChannel;
@property (assign,nonatomic) uint16_t       fmFrequency;
@end

NS_ASSUME_NONNULL_END
