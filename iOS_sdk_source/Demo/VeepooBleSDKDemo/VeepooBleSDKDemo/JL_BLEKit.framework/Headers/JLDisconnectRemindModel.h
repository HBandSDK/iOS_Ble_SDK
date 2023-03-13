//
//  JLDisconnectRemindModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 手表蓝牙断开提醒设置
@interface JLDisconnectRemindModel : JLwSettingModel
//开关
@property(nonatomic,assign)BOOL status;
/// 提醒模式
@property(nonatomic,assign)WatchRemindType rType;

-(instancetype)initWithData:(NSData *)data;

- (instancetype)initWithModel:(WatchRemindType)type Status:(BOOL)status;

@end

NS_ASSUME_NONNULL_END
