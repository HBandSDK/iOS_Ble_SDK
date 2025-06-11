//
//  VPWorldClockModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2025/2/14.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPWorldClockModel : NSObject

//城市/地区名  下发时使用UTF-8编码
@property (nonatomic, copy) NSString *cityName;

/**ID 从1开始，最大为10（世界时钟最多添加10个）**/
@property (nonatomic, assign) uint8_t dataID;

//时区的值(相较GMT时区有多少个15分钟，使用时转为int8_t类型，有正负
@property (nonatomic, strong) NSNumber *standardTimeZoneDiffer;

@end

NS_ASSUME_NONNULL_END
