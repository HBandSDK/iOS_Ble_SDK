//
//  VPDeviceFemaleModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/6/13.
//  Copyright © 2017年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"
@interface VPDeviceFemaleModel : NSObject
//处于哪个生理期
@property (nonatomic, assign) VPDeviceFemaleState femaleState;
//最后经期日期格式yyyy-MM-dd
@property (nonatomic, strong) NSString *lastMenstrualDate;
//经期周期
@property (nonatomic, assign) NSInteger menstrualCircle;
//经期天数
@property (nonatomic, assign) NSInteger menstrualDays;

//当前经期的时间天数，menstrualDays是一个人常规的经期天数，比如5天，但是这个月可能少一天也可能多一天，所以都了个此属性，此属性在彩屏项目上有效
@property (nonatomic, assign) NSInteger currentMenstrualDays;
//预产期expectedDateOfChildbirth
@property (nonatomic, strong) NSString *expectedDateOfChildbirth;

//宝宝的生日格式yyyy-MM-dd
@property (nonatomic, strong) NSString *babyBirthday;
//宝宝是否为女
@property (nonatomic, assign) BOOL isGirl;

- (instancetype)initWithTbyte:(const uint8_t *)tbyte;

- (NSData *)changeSelfToSettingData;

@end
