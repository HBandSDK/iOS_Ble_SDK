//
//  JLModel_AlarmSetting.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModel_AlarmSetting : NSObject
@property(assign,nonatomic)uint8_t index;       //闹钟索引
@property(assign,nonatomic)uint8_t isCount;     //是否可以设置【闹铃次数】
@property(assign,nonatomic)uint8_t count;       //闹铃次数
@property(assign,nonatomic)uint8_t isInterval;  //是否可以设置【时间间隔】
@property(assign,nonatomic)uint8_t interval;    //时间间隔
@property(assign,nonatomic)uint8_t isTime;      //是否可以设置【时间长度】
@property(assign,nonatomic)uint8_t time;        //时间长度
-(NSData*)dataModel;
@end

NS_ASSUME_NONNULL_END
