//
//  JLModel_SmallFile.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/14.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(UInt8, JL_SmallFileType) {
    JL_SmallFileTypeContacts        = 0x01, //联系人
    JL_SmallFileTypeMotionRecord    = 0x02, //运动记录
    JL_SmallFileTypeHeartRate       = 0x03, //心率数据
    JL_SmallFileTypeSpoData         = 0x04, //血氧数据
    JL_SmallFileTypeSleepData       = 0x05, //睡眠数据
    JL_SmallFileTypeMassage         = 0x06, //消息数据
    JL_SmallFileTypeWeather         = 0x07, //天气数据
    JL_SmallFileTypeCallLog         = 0x08, //通话记录
    JL_SmallFileTypeStepCount       = 0x09, //步数数据
    JL_SmallFileTypeWeight          = 0xFF, //体重数据
};

@interface JLModel_SmallFile : NSObject
@property(nonatomic,assign)JL_SmallFileType  file_type;
@property(nonatomic,assign)uint8_t  file_ver;
@property(nonatomic,assign)uint16_t file_id;
@property(nonatomic,assign)uint16_t file_size;
@end

NS_ASSUME_NONNULL_END
