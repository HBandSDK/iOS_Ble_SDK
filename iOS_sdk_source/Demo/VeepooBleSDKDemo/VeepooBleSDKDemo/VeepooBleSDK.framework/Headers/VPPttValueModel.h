//
//  VPPttValueModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2019/10/16.
//  Copyright © 2019 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, PTTTestState){
    PTTTestStateNormal = 0,//正常测试
    PTTTestStateLeadFail = 1,//导联脱落
    PTTTestStateBusy = 2,//设备正忙
};

@interface VPPttValueModel : NSObject

@property (nonatomic, assign) int frequency;

@property (nonatomic, assign) int uploadFrequency;

@property (nonatomic, assign) int heart;
//@property (nonatomic, assign) int rr;
@property (nonatomic, assign) int hrv;
@property (nonatomic, assign) int qt;

@property (nonatomic, assign) PTTTestState testState;

@property (nonatomic, strong) NSData *resultData;

+ (instancetype)modelWithData:(NSData *)ecgPTTData;

@end

