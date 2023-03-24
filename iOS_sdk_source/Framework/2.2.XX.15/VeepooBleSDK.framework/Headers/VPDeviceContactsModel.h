//
//  VPDeviceContactsModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/3/21.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceContactsModel : NSObject

@property(nonatomic, assign) int contactID;

// 只支持20个字节，超过20个字节，会转成能转换成string的长度
@property(nonatomic, strong) NSString *nickName;

@property(nonatomic, strong) NSString *phoneNumber;

@end

NS_ASSUME_NONNULL_END

