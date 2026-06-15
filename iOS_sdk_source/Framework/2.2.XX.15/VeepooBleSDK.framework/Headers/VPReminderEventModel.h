//
//  VPReminderEventModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/6/12.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"
NS_ASSUME_NONNULL_BEGIN

@interface VPReminderEventModel : NSObject

@property (nonatomic, assign) VPReminderEventType type;

@property (nonatomic, assign) int64_t timestamp;

@end

NS_ASSUME_NONNULL_END
