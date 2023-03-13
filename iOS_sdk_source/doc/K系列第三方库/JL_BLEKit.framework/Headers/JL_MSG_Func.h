//
//  JL_MSG_Func.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/5/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef enum : uint8_t {
    Func_Location,
    Func_Weather,
    Func_Notify,
} FuncMsgType;

@interface JL_MSG_Func : NSObject

@end

NS_ASSUME_NONNULL_END
