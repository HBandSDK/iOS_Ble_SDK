//
//  JLPersonInfoModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 个人信息设置
@interface JLPersonInfoModel : JLwSettingModel

/// 身高，cm
@property(nonatomic,assign)uint16_t height;
/// 体重，kg
@property(nonatomic,assign)uint16_t weight;
/// 生日
@property(nonatomic,strong)NSDate *birthDay;
/// 性别
/// 女性：0x00
/// 男性：0x01
@property(nonatomic,assign)uint8_t gender;

-(instancetype)initWith:(NSDate *)birthDay height:(uint16_t)h weight:(uint16_t)w gener:(uint8_t)gender;

-(instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
