//
//  UIImage+RawImageData.h
//  ABParDemo
//
//  Created by Bluetrum on 2024/3/28.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (RawImageData)

/// 转换成原始图像数据，转换的格式为ARGB
@property (nonatomic, nullable, readonly) NSData *rawImageData;

@end

NS_ASSUME_NONNULL_END
