//
//  DFImage.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface DFImage : NSObject



/**
 *  用途:压缩图片。
 *  @param   srcImage   待压缩的图片
 *  @param   scale      压缩比
 */
+(NSData*)compressImage:(UIImage *)srcImage Scale:(double)scale;


/**
 *  用途:从Project资源里寻找图片文件。
 *  @param   image     图片名     -->> @"test@2x.png" <<--
 */
+(UIImage*)loadImage:(NSString*)image;


/**
 *  @use 图片模糊处理
 *  @param image 图片数据
 *  @param blur  模糊值，取值[0,1]
 *  @return 模糊后的图片
 */
+(UIImage*)blurImage:(UIImage*)image Blur:(CGFloat)blur;

/**
 *  @use 图片模糊处理
 *  @param image 图片数据
 *  @param blur  模糊值，取值[0,1]
 *  @param color 背景色调
 *  @return 模糊后的图片
 */
+(UIImage*)blurImage:(UIImage*)image Blur:(CGFloat)blur TintColor:(UIColor*)color;

/**
 *  @use 屏幕截图
 *  @param size     大小
 *  @param view     截取视图
 *  @return 截取后的图片
 */
+(UIImage*)screenshotSize:(CGSize)size OnView:(UIView*)view;


@end
