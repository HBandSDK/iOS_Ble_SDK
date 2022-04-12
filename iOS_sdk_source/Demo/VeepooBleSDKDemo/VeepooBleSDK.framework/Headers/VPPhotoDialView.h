//
//  VPPhotoDialView.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/1/26.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class VPPhotoDialModel;

@interface VPPhotoDialView : UIView

- (instancetype)initWithPhotoDialModel:(VPPhotoDialModel *)model;

- (void)setBgImage:(UIImage *)image;

- (void)showDefaultBgImage;

@end

NS_ASSUME_NONNULL_END
