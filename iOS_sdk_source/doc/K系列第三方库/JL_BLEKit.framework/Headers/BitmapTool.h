//
//  BitmapTool.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/29.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BitmapTool : NSObject

/*
 *输入：
 *    image    : UIimage图片
 *返回值：
 *    NSData   : B_G_R_A位图数据
 */
+(NSData*)convert_B_G_R_A_BytesFromImage:(UIImage*)image;

/*
 *输入：
 *    image    : UIimage图片
 *返回值：
 *    NSData   : R_G_B_A位图数据
 */
+(NSData*)convert_R_G_B_A_BytesFromImage:(UIImage*)image;

/*
 *输入：
 *    image    : UIimage图片
 *    newSize  : 新的图片尺寸
 *返回值：
 *    NSData   : 图片数据
 */
+(NSData *)resizeImage:(UIImage*)image andResizeTo:(CGSize)newSize;
@end

NS_ASSUME_NONNULL_END
