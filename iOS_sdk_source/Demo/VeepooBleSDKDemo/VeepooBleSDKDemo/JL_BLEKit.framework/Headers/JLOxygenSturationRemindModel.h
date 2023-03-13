//
//  JLOxygenSturationRemindModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/2/17.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLOxygenSturationRemindModel : JLwSettingModel
///开关
@property(nonatomic,assign)BOOL status;
/// 测量模式
@property(nonatomic,assign)WatchOxygenMsmType rType;


-(instancetype)initWithData:(NSData *)data;

/// 创建一个新的传感器设置对象
/// @param type 测量类型
/// @param status 开团状态
- (instancetype)initWithModel:(WatchOxygenMsmType)type Status:(BOOL)status;
@end

NS_ASSUME_NONNULL_END
