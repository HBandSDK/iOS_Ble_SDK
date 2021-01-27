//
//  VPOxygenAnalysisModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2019/1/11.
//  Copyright © 2019 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPOxygenAnalysisModel : NSObject

//一天的血氧数据
@property (nonatomic, strong) NSArray *oneDayOxygens;

//根据一天血氧数据解析出的一些结果
@property (nonatomic, strong) NSDictionary *parseOneDayDict;

//呼吸暂停频现时间
@property (nonatomic, strong) NSArray *frequentOccurrenceTimes;
//呼吸暂停频现时间对应的次数
@property (nonatomic, strong) NSArray *frequentOccurrenceValues;


//呼吸暂停结果-1代表没有结果 0代表正常 1代表轻度 2代表中度 3代表重度
@property (nonatomic, assign) int osahsResult;

//呼吸暂停结果的本地化描述, 对应osahsResult,如果osahsResult为-1时为“--”
@property (nonatomic, strong) NSString *osahsResultDes;

//血氧的平均值,如果为0代表没有数据
@property (nonatomic, assign) int aveOxygenValue;

//血氧的最低值,如果为0代表没有数据
@property (nonatomic, assign) int minOxygenValue;

//呼吸率的平均值
@property (nonatomic, assign) int aveRespirationRate;

//呼吸率的最低值
@property (nonatomic, assign) int minRespirationRate;

//呼吸率的最高值
@property (nonatomic, assign) int maxRespirationRate;

//低氧时间的平均值
@property (nonatomic, assign) int aveLowOxygenTime;

//低氧时间的最大值
@property (nonatomic, assign) int maxLowOxygenTime;

//心脏负荷的平均值
@property (nonatomic, assign) int aveCardiacLoad;

//心脏负荷的最大值
@property (nonatomic, assign) int maxCardiacLoad;

//心脏负荷的最小值
@property (nonatomic, assign) int minCardiacLoad;

//睡眠活动的平均值, 睡眠活动的最大最小值都显示--就可以
@property (nonatomic, assign) int aveSleepActivity;

- (instancetype)initWithOneDayOxygens:(NSArray *)oneDayOxygens;


@end
