//
//  JLFallDetectionModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 跌到监测设置
@interface JLFallDetectionModel : JLwSettingModel
///开关
@property(nonatomic,assign)BOOL status;
/// 提醒模式
@property(nonatomic,assign)WatchRemindType rType;
/// 电话号码
@property(nonatomic,strong,readonly)NSString *phoneNumber;

-(instancetype)initWithData:(NSData *)data;

/// 构建一个跌倒监测的设置对象
/// @param type 提醒类型
/// @param status 开关
/// @param pn 电话号码
- (instancetype)initWithModel:(WatchRemindType)type Status:(BOOL)status phoneNumber:(NSString * _Nullable)pn;

@end

NS_ASSUME_NONNULL_END
