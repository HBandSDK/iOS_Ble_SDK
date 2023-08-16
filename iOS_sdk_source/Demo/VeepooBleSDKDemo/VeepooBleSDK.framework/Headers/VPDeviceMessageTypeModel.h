//
//  VPDeviceMessageTypeModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/8/15.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"

NS_ASSUME_NONNULL_BEGIN

/// 消息推送开关批处理工具对象
@interface VPDeviceMessageTypeModel : NSObject

@property (nonatomic, assign) VPSettingMessageSwitchType messageType;

@property (nonatomic, assign) BOOL open;

@end

NS_ASSUME_NONNULL_END

