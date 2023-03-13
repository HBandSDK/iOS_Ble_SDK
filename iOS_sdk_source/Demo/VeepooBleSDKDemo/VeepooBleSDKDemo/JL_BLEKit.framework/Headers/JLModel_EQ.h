//
//  JLModel_EQ.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_EQMode) {
    JL_EQModeNORMAL                 = 0,    //自然
    JL_EQModeROCK                   = 1,    //摇滚
    JL_EQModePOP                    = 2,    //流行
    JL_EQModeCLASSIC                = 3,    //经典
    JL_EQModeJAZZ                   = 4,    //爵士
    JL_EQModeCOUNTRY                = 5,    //乡村
    JL_EQModeCUSTOM                 = 6,    //用户自定义
    JL_EQModeLATIN                  = 7,    //拉丁
    JL_EQModeDANCE                  = 8,    //舞蹈
};

@interface JLModel_EQ : NSObject
@property(assign,nonatomic)JL_EQMode        mMode;
@property(strong,nonatomic)NSArray *__nullable mEqArray;
@end

NS_ASSUME_NONNULL_END
