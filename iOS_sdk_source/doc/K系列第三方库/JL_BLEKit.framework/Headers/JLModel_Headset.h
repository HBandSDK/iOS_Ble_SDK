//
//  JLModel_Headset.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModel_Headset : NSObject
@property(assign,nonatomic)BOOL             mCharging_L;
@property(assign,nonatomic)BOOL             mCharging_R;
@property(assign,nonatomic)BOOL             mCharging_C;
@property(assign,nonatomic)uint8_t          mPower;
@property(assign,nonatomic)uint8_t          mPower_L;
@property(assign,nonatomic)uint8_t          mPower_R;
@property(assign,nonatomic)uint8_t          mPower_C;
@property(assign,nonatomic)uint8_t          mLedScene;
@property(assign,nonatomic)uint8_t          mLedEffect;
@property(assign,nonatomic)uint8_t          mKeyLR;
@property(assign,nonatomic)uint8_t          mKeyAction;
@property(assign,nonatomic)uint8_t          mKeyFunction;
@property(assign,nonatomic)uint8_t          mMicMode;
@property(assign,nonatomic)uint8_t          mWorkMode;
@property(strong,nonatomic)NSString         *mEdr;
@end

NS_ASSUME_NONNULL_END
