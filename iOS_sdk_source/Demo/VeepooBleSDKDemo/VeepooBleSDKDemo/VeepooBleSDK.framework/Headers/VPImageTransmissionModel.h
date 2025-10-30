//
//  VPImageTransmissionModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2025/10/23.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>
NS_ASSUME_NONNULL_BEGIN

@interface VPImageTransmissionModel : NSObject
//暂时没用
@property (nonatomic, assign) NSInteger address;
//最大可传输长度
@property (nonatomic, assign) NSInteger dataLength;
//设备支持图片的宽度
@property (nonatomic, assign) NSInteger width;
//设备支持图片的宽度
@property (nonatomic, assign) NSInteger height;
//传输的图片
@property (nonatomic, strong) UIImage *transformImage;

- (instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
