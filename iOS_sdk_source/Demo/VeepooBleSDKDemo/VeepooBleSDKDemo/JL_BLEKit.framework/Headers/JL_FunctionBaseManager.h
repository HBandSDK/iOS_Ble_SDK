//
//  JL_FunctionBaseManager.h
//  JL_BLEKit
//
//  Created by 凌煊峰 on 2021/12/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_Device.h>
#import <JL_BLEKit/JL_RCSP.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;
@interface JL_FunctionBaseManager : NSObject

@property (assign, nonatomic) uint8_t           mCmdSN;
@property (strong, nonatomic) NSString          *mBLE_UUID;
@property (strong, nonatomic) NSString          *mBLE_NAME;
@property (weak  , nonatomic) JLModel_Device    *deviceModel;
@property (weak  , nonatomic) JL_ManagerM       *centerManagerM;

- (void)inputPKG:(JL_PKG *)pkg;

@end

NS_ASSUME_NONNULL_END
