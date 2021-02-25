//
//  VPOxygenDisconnectTestModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2019/10/15.
//  Copyright © 2019 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPOxygenDisconnectTestModel : NSObject

@property (nonatomic, assign) int year;
@property (nonatomic, assign) int month;
@property (nonatomic, assign) int day;
@property (nonatomic, assign) int hour;
@property (nonatomic, assign) int minute;
@property (nonatomic, assign) int second;

@property (nonatomic, assign) int oxygen;
@property (nonatomic, assign) int heart;

+ (NSArray <VPOxygenDisconnectTestModel *>*)modelWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
