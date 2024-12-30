//
//  VPPhotoDialConfigModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/11/17.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPhotoDialModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 照片表盘的配置表
@interface VPPhotoDialConfigModel : NSObject

/// 屏幕宽高，为sdk内部根据screenType做的映射值
@property (nonatomic, assign, readonly) CGSize screenSize;
/// 长按设备主界面，带边框缩略图的大小
@property (nonatomic, assign, readonly) CGSize previewBorderSize;
/// 长按设备主界面，缩略图的大小(不带边框)
@property (nonatomic, assign, readonly) CGSize previewSize;
/// 是否为圆屏
@property (nonatomic, assign, readonly) BOOL isCircle;
/// 预览图的外边框图片名称，在SDKResours.bundle资源中，如果发生异常，请检查资源中是否存在该图片
@property (nonatomic, strong, readonly) NSString *previewBorderImageName;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithScreenSize:(CGSize)screenSize
                 previewBorderSize:(CGSize)previewBorderSize
                       previewSize:(CGSize)previewSize
                          isCircle:(BOOL)isCircle
            previewBorderImageName:(NSString *)previewBorderImageName;

@end

NS_ASSUME_NONNULL_END

