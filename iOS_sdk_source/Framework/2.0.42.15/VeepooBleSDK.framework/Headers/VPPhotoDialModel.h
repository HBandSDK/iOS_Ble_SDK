//
//  VPPhotoDial.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/1/23.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>

typedef NS_ENUM(NSUInteger, VPDialChannelModel) {
    VPDialChannelModelSetup = 1,        // 设置模式 内部用
    VPDialChannelModelRead,             // 读取模式
    VPDialChannelModelSetupPhotoDial,   // 照片表盘设置元素模式
};

typedef NS_ENUM(NSUInteger, VPDeviceDialType) {
    VPDeviceDialTypeDefault = 0,        // 默认烧录表盘
    VPDeviceDialTypeMarket,             // 市场表盘
    VPDeviceDialTypePhoto,              // 照片表盘
};

typedef NS_ENUM(NSUInteger, VPDeviceScreenType) {
    VPDeviceScreenTypeCircle240_240 = 1,   // 圆屏 240*240
    VPDeviceScreenTypeSquare240_240,       // 方屏 240*240
    VPDeviceScreenTypeSquare240_280,       // 方屏 240*280
};

typedef NS_ENUM(NSUInteger, VPPhotoDialTimePosition) {
    // 圆屏
    VPPhotoDialTimePositionTop = 1,         // top
    VPPhotoDialTimePositionMiddle,          // middle
    VPPhotoDialTimePositionBottom,          // bottom
    // 方屏
    VPPhotoDialTimePositionLeftTop,         // left top
    VPPhotoDialTimePositionRightTop,        // right top
    VPPhotoDialTimePositionLeftBottom,      // left bottom
    VPPhotoDialTimePositionRightBottom,     // right bottom
};

typedef NS_ENUM(NSUInteger, VPPhotoDialTimeTopAndBottomElement) {
    VPPhotoDialTimeTopAndBottomElementHidden = 0,
    VPPhotoDialTimeTopAndBottomElementDateStyle1,
    // special: 圆屏：day+week 方屏：yyyyMMdd+week
    VPPhotoDialTimeTopAndBottomElementDateStyle2,
    VPPhotoDialTimeTopAndBottomElementStep,
    VPPhotoDialTimeTopAndBottomElementSleep,
    VPPhotoDialTimeTopAndBottomElementHeart,
    VPPhotoDialTimeTopAndBottomElementCalories,
    VPPhotoDialTimeTopAndBottomElementDistance,
    VPPhotoDialTimeTopAndBottomElementBatteryAndBLE,
};


NS_ASSUME_NONNULL_BEGIN

@interface VPPhotoDialModel : NSObject

@property (nonatomic, assign, readonly) NSUInteger index;
/// 屏幕的类型
@property (nonatomic, assign, readonly) VPDeviceScreenType screenType;
/// 是否是默认背景
@property (nonatomic, assign) BOOL isDefaultBG;

/*
 时间位置 根据 VPDeviceScreenType 决定设置范围
 VPDeviceScreenTypeCircle240_240:
    -VPPhotoDialTimePositionTop
    -VPPhotoDialTimePositionMiddle
    -VPPhotoDialTimePositionBottom
 
 VPDeviceScreenTypeSquare240_240:
 VPDeviceScreenTypeSquare240_280:
    -VPPhotoDialTimePositionLeftTop
    -VPPhotoDialTimePositionRightTop
    -VPPhotoDialTimePositionLeftBottom
    -VPPhotoDialTimePositionRightBottom
 SDK会做相应容错处理，请自行限制值的范围，否则SDK无法保证正常运行
 */
@property (nonatomic, assign) VPPhotoDialTimePosition timePosition;
/// 时间上方元素
@property (nonatomic, assign) VPPhotoDialTimeTopAndBottomElement timeTopPosition;
/// 时间下方元素
@property (nonatomic, assign) VPPhotoDialTimeTopAndBottomElement timeBottomPosition;
/// 设备读取上来的RGB 888
@property (nonatomic, strong, readonly) NSString *deviceColor;

@property (nonatomic, strong, readonly) NSString *crc16;

// 默认为deviceColor的值，0xFFFFF if deviceColor is nil;
// 可以用来进行颜色校准 格式 RGB-888 如 AABBCC：AA表示Red, 以此类推
@property (nonatomic, strong) NSString *setColor;

/*
 请根据屏幕类型裁剪传入的image
 如果要显示成照片表盘的默认背景，请传nil 否则将进入传输UI逻辑
 VPPhotoDialTypeCircle240_240 width:240 height:240
 VPPhotoDialTypeSquare240_240 width:240 height:240
 VPPhotoDialTypeSquare240_280 width:240 height:280
 */
@property (nonatomic, strong, nullable) UIImage *transformImage;

- (instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
