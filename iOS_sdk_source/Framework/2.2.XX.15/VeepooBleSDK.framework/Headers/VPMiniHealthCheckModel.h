//
//  VPMiniHealthCheckModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2025/10/29.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPMiniHealthCheckModel : NSObject

// 心率
@property (nonatomic,assign)int heartRate;

// 血氧
@property (nonatomic,assign)int bloodOxygen;

//压力
@property (nonatomic,assign)int pressure;

//情绪[-10,10]
@property (nonatomic,assign)int emotion;

//疲劳度
@property (nonatomic,assign)int fatigueLevel;

//血糖
@property (nonatomic,assign)CGFloat bloodSugar;

//体温
@property (nonatomic,assign)CGFloat bodyTemperature;

//血压(收缩压)
@property (nonatomic,assign)int systolicBloodPressure;

//血压(舒缩压)
@property (nonatomic,assign)int diastolicBloodPressure;

//HRV
@property (nonatomic,assign)int hrv;

- (instancetype)initWithData:(NSData *)data;
@end

NS_ASSUME_NONNULL_END
