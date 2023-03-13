//
//  JL_BatchManger.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/21.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_BatchType) {
    ///开始
    BatchType_Begin =  0x00,
    ///结束
    BatchType_Finish = 0x80,
    ///取消
    BatchType_Cancel = 0x81,
};

typedef NS_ENUM(NSUInteger, JL_BatchOptionType) {
    /// 格式化操作
    BatchOption_Format = 0x00,
    ///  未知操作
    BatchOption_unKnow = 0xFF,
};

@interface JL_BatchManger : JL_FunctionBaseManager

#pragma mark ---> 批操作命令
typedef void(^JL_BATCH_BK)(uint8_t flag);
/**
 @param type      0x00:开始 0x80:结束 0x81:结束
 @param array    @[@(JL_BatchOptionType)]，0x00代表格式化操作。
 @param result  操作回调 0x00:成功 0x01:失败
 */
-(void)cmdBatchType:(JL_BatchType)type
         Operations:(NSArray<NSNumber *>*)array
             Result:(JL_BATCH_BK __nullable)result;

@end

NS_ASSUME_NONNULL_END
