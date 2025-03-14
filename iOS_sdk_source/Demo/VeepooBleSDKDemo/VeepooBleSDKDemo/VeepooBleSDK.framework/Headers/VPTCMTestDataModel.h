//
//  VPTCMTestDataModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2025/3/14.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPTCMTestDataModel : NSObject

//测试日期
@property (nonatomic, strong) NSString *date;
//测试时间
@property (nonatomic, strong) NSString *testTime;
//持续时间
@property (nonatomic, strong) NSString *duration;
//设备地址
@property (nonatomic, strong) NSString *mac;
//最终的结果心率, 测试结束后界面显示
@property (nonatomic, strong) NSString *aveHeart;
//最终的结果HRV,测试结束后界面显示
@property (nonatomic, strong) NSString *aveHrv;
//最终的结果呼吸率,测试结束后界面显示,此参数暂时无效
@property (nonatomic, strong) NSString *aveResRate;
//最终的结果QT,测试结束后界面显示
@property (nonatomic, strong) NSString *aveQT;
//最终的结果PWV,测试结束后界面显示
@property (nonatomic, strong) NSString *avePWV;
//最终的结果PAT
@property (nonatomic, strong) NSString *avePAT;
//ADC数据流
@property (nonatomic, strong) NSArray *originalSignals;

//界面上画波形使用此数组,如果此数组没有值,则代表还没有合理的波形数据, 测试过程中此波形数组长度会一直拼接, 画波形的时候可以开启个定时器,从数组中取点数绘制
@property (nonatomic, strong) NSArray *filterSignals;

//心率数组，App手动测试每秒的心率值
@property (nonatomic, strong) NSArray *hearts;
//hrv数组，App手动测试每秒的hrv值
@property (nonatomic, strong) NSArray *hrvs;
//hrv数组，App手动测试每秒的rr值
@property (nonatomic, strong) NSArray *rrs;
//呼吸率数组，App手动测试每秒的呼吸率值
@property (nonatomic, strong) NSArray *resRates;
//QT数组，App手动测试每秒的QT值
@property (nonatomic, strong) NSArray *qts;
//PWV数组，APP手动测量每秒的PWV值
@property (nonatomic, strong) NSArray *pwvs;
//PAT数组，APP手动测量每秒的PAT值
@property (nonatomic, strong) NSArray *pats;

//导联信号
@property (nonatomic, strong) NSString *lead;

//使用VPECGTestResutHandle下这个方法可获取诊断结果, 付费客户可用
//测试结果, 根据每个结果得出诊断结果
@property (nonatomic, strong) NSString *result1;
@property (nonatomic, strong) NSString *result2;
@property (nonatomic, strong) NSString *result3;
@property (nonatomic, strong) NSString *result4;
@property (nonatomic, strong) NSString *result5;
@property (nonatomic, strong) NSString *result6;
@property (nonatomic, strong) NSString *result7;
@property (nonatomic, strong) NSString *result8;
@property (nonatomic, strong) NSString *multipleDiagnosisTempStr;

//测试频率,采样频率
@property (nonatomic, strong) NSString *frequency;
//设备上传给App的频率,界面显示用此频率值
@property (nonatomic, strong) NSString *uploadFrequency;

//测试过程中使用,每个数组的最后一个值就是当前界面应该显示的值, 测试完成后会拷贝到hearts中,测试完成后界面显示平均值
@property (nonatomic, strong) NSMutableArray *muHearts;
@property (nonatomic, strong) NSMutableArray *muHrvs;
@property (nonatomic, strong) NSMutableArray *muRrs;
@property (nonatomic, strong) NSMutableArray *muResRates;
@property (nonatomic, strong) NSMutableArray *muQTs;
@property (nonatomic, strong) NSMutableArray *muPwvs;
@property (nonatomic, strong) NSMutableArray *muPats;

#pragma mark - 私有方法

- (instancetype)initWithMac:(NSString *)mac;

- (void)startReceiveData;

- (void)endReceiveData;

/// 接收App手动测试的数据
- (void)receiveAppTestValueWithData:(NSData *)data;

/// 接收App手动测试的波形数据大包
- (void)receiveAppTestAdcBigBlock:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
