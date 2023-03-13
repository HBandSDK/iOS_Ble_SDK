//
//  JL_SystemEQ.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"


NS_ASSUME_NONNULL_BEGIN


@interface JL_SystemEQ : JL_FunctionBaseManager

#pragma mark ---> 设置系统EQ
/**
 @param eqMode EQ模式
 @param params EQ参数(10个参数,仅适用于JL_EQModeCUSTOM情况)
 */
-(void)cmdSetSystemEQ:(JL_EQMode)eqMode Params:(NSArray* __nullable)params;

@end

NS_ASSUME_NONNULL_END
