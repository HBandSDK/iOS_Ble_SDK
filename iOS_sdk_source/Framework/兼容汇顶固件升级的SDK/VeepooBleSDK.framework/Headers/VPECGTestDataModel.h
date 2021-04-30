//
//  VPECGTestDataModel.h
//  WYPHealthyThird
//
//  Created by 张冲 on 2018/11/8.
//  Copyright © 2018 zc.All rights reserved.
//  数据库暂时无用

#import <Foundation/Foundation.h>

typedef enum : int {
    ECGDataTypeAll = 1, //所有类型的数据
    ECGDataTypeDeviceManual = 2, //手环手动测试数据
    ECGDataTypeDeviceAuto = 3, //手环自动测试数据
    ECGDataTypeAppManual = 4, //App手动测试数据
} ECGDataType;

@interface VPECGTestDataModel : NSObject

//数据类型2代表手环手动测试，3代表手环自动测试，4代表App手动测试
@property (nonatomic, strong) NSString *type;
//2为E系列 3为G系列
@property (nonatomic, strong) NSString *ecgType;
//测试日期
@property (nonatomic, strong) NSString *date;
//测试时间
@property (nonatomic, strong) NSString *testTime;
//持续时间
@property (nonatomic, strong) NSString *duration;
//设备地址
@property (nonatomic, strong) NSString *mac;
//数据状态0代表数据被删除，1代表数据正常
@property (nonatomic, strong) NSString *state;
//最终的结果心率, 测试结束后界面显示
@property (nonatomic, strong) NSString *aveHeart;
//最终的结果HRV,测试结束后界面显示
@property (nonatomic, strong) NSString *aveHrv;
//最终的结果呼吸率,测试结束后界面显示,此参数暂时无效
@property (nonatomic, strong) NSString *aveResRate;
//最终的结果QT,测试结束后界面显示
@property (nonatomic, strong) NSString *aveQT;
//ADC数据流
@property (nonatomic, strong) NSArray *originalSignals;

//界面上画波形使用此数组,如果此数组没有值,则代表还没有合理的波形数据, 测试过程中此波形数组长度会一直拼接, 画波形的时候可以开启个定时器,每100毫秒取25个点
// ecgType不同，画图的方式不同 1为旧的方式，2为新的方式
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


- (instancetype)initWithDataType:(ECGDataType)dataType andMac:(NSString *)mac;

-(void)startReceiveData;
- (void)endReceiveData;
//接收App手动测试的数据
- (void)receiveAppTestValueBytes:(const uint8_t *)tbyte;
//接收App手动测试的波形数据
- (void)receiveAppTestAdcBytes:(const uint8_t *)tbyte;
//接收App手动测试的波形数据大包
- (void)receiveAppTestAdcBigBlock:(NSData *)data;

//根据读取的数据创建模型，如果返回nil代表数据解析失败
- (BOOL)parseWithContentData:(NSData *)contentData;

//保存到数据库要忽略的属性
+ (NSArray<NSString *> *)ignoreProperties;



@end
