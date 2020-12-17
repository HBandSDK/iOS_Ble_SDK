//
//  VPSyncPersonalInfo.h
//  VeepooBleSDK
//
//  Created by zhangchong on 2020/3/3.
//  Copyright © 2020 zc.All rights reserved.
//

#import <Foundation/Foundation.h>


@interface VPSyncPersonalInfo : NSObject

//身高， 单位cm
@property(nonatomic, assign) int status;

//体重， 单位kg
@property(nonatomic, assign) int weight;

//年龄 (current yeart - birth year） 当前年 - 用户出生年
@property(nonatomic, assign) int age;

//性别 0代表 female， 1代表male
@property(nonatomic, assign) int sex;

//目标步数 单位步（step）
@property(nonatomic, assign) int targetStep;

//目标睡眠时长 单位分钟（minute）要确认项目中是否有这个功能，如果没有也可以设置
@property(nonatomic, assign) int targetSleepDuration;

@end

