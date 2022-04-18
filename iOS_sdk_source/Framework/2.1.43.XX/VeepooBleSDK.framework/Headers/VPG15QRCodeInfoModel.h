//
//  VPG15QRCodeInfoModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2022/2/14.
//  Copyright © 2022 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, VPG15QRCodeType) {
    VPG15QRCodeTypePatient, // 患者二维码
    VPG15QRCodeTypePayment, // 收款二维码
};

@interface VPG15QRCodeInfoModel : NSObject

/// 二维码类型
@property (nonatomic, assign) VPG15QRCodeType qrcodeType;

/// 二维码内容，不超过 50 个字节(byte)
@property (nonatomic, strong) NSString *content;

/// 姓名，不超过 30 个字节(byte)
@property (nonatomic, strong) NSString *name;

/// 组别，不超过 30 个字节(byte)
@property (nonatomic, strong) NSString *groupId;

/// 编号，不超过 30 个字节(byte)
@property (nonatomic, strong) NSString *number;


// 传输内容 内部调用
- (nullable NSData *)getSerializationData;

@end

NS_ASSUME_NONNULL_END

