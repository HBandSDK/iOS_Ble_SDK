//
//  DFVideo.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DFVideo : NSObject

/**
 *  用途:获得AVI视频的PreViewImage。
 *  @param   path      文件路径
 *  @return @{@"IMG" : 图片Data,
 *            @"SIZE": 宽高,
 *            @"TIME": 时长}
 */
+(NSDictionary*)previewAVI:(NSString*)path;

/**
 *  用途:获得AVI视频的PreViewImage。
 *  @param   data      文件数据
 *  @return @{@"IMG" : 图片Data,
 *            @"SIZE": 宽高,
 *            @"TIME": 时长}
 */
+(NSDictionary *)previewData:(NSData*)data;

/**
 *  用途:秒数换算成时间字符串。
 *  @param  total 秒数（60s ==> 00:01:00）
 *  @return @"00:01:00"
 */
+(NSString *)timeTyping:(long)total;

@end
