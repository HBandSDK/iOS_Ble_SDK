//
//  JLModel_BT.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModel_BT : NSObject
@property(assign,nonatomic)uint32_t         mBtType;
@property(strong,nonatomic)NSData *__nullable mBtAddress;
@property(assign,nonatomic)uint8_t          mBtRssi;
@property(strong,nonatomic)NSString *__nullable mBtName;
@end

NS_ASSUME_NONNULL_END
