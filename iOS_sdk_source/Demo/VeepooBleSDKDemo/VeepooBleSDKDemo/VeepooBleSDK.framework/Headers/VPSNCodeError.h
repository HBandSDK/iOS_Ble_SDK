//
//  VPSNCodeError.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/9/23.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// JH76SN码操作错误码
/// 约定：
///  - 0 表示成功，非 0 表示失败。
///  - 后续新增错误码只需在下方 NS_ENUM 中追加一项，并同步在 VPSNCodeErrorDescription 中补充文案，
///    不要复用 / 修改已有值，以保证历史调用方能稳定解析。
///  - 预留区间：本地校验类 1xxx，设备返回类 2xxx，便于以后按来源归类扩展。
typedef NS_ENUM(NSInteger, VPJH76SNCodeErrorCode) {
    VPJH76SNCodeErrorCodeSuccess        = 0,    // 成功
    VPJH76SNCodeErrorCodeDeviceFailed   = 1000, // 失败
    VPJH76SNCodeErrorCodeInvalidFormat  = 1001, // 格式错误：SN码只能为数字
    VPJH76SNCodeErrorCodeInvalidLength  = 1002, // 长度错误：SN码固定 10 位
    VPJH76SNCodeErrorCodeAllZero        = 1003, // SN码不能全为0
};

/// 错误码 -> 说明文案
/// @param code 错误码
/// @return 对应中文说明；未知错误码返回通用提示（含原始 code，便于排查）
NSString *VPJH76SNCodeErrorDescription(VPJH76SNCodeErrorCode code);

NS_ASSUME_NONNULL_END
