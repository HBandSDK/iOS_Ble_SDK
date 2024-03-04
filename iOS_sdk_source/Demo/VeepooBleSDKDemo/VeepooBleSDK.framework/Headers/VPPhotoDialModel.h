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
    VPDeviceScreenTypeCircle240_240             = 0x01,        // 圆屏 240*240
    VPDeviceScreenTypeSquare240_240             = 0x02,        // 方屏 240*240
    VPDeviceScreenTypeSquare240_280             = 0x03,        // 方屏 240*280
    VPDeviceScreenTypeSquare240_280_QFN         = 0x04,        // 方屏 240*280 QFN版本
    VPDeviceScreenTypeCircle240_240_QFN         = 0x05,        // 圆屏 240*240 QFN版本
    VPDeviceScreenTypeSquare240_295             = 0x06,        // 方屏 240*295
    VPDeviceScreenTypeSquare240_295_QFN         = 0x07,        // 方屏 240*295 QFN版本
    VPDeviceScreenTypeCircle360_360_QFN         = 0x08,        // 圆屏 360*360 QFN版本
    VPDeviceScreenTypeSquare240_280_QFN_RIG     = 0x09,        // 方屏 240*280 QFN版本 RIG设备，与0x04区分默认背景
    VPDeviceScreenTypeSquare080_160_QFN         = 0x0A,        // 方屏  80*160 位置只有上中下
    VPDeviceScreenTypeSquare240_240_QFN         = 0x0B,        // 方屏 240*240 QFN版本
    VPDeviceScreenTypeSquare135_240_QFN         = 0x0C,        // 方屏 135*240 位置只有上中下
    VPDeviceScreenTypeSquare172_320_QFN         = 0x0D,        // 方屏 172*320 位置只有上中下
    VPDeviceScreenTypeSquare167_240_QFN         = 0x0E,        // 方屏 167*240 位置只有上中下
    VPDeviceScreenTypeSquare240_284_QFN         = 0x0F,        // 方屏 240*284 QFN版本 效果图用240x280的
    VPDeviceScreenTypeSquare240_286_QFN         = 0x10,        // 方屏 240*286 QFN版本 效果图用240x280的
    VPDeviceScreenTypeSquare320_380_QFN         = 0x11,        // 方屏 320*380 QFN版本
    VPDeviceScreenTypeSquare200_320_QFN         = 0x12,        // 方屏 200*320 位置只有上中下
    
    // K系列的
    VPDeviceScreenTypeCircle360_360_JL          = 0x30,        // 杰理 360*360
    VPDeviceScreenTypeSquare240_280_JL          = 0x31,        // 杰理 240*280
    VPDeviceScreenTypeSquare240_284_JL          = 0x32,        // 杰理 240*284
    VPDeviceScreenTypeSquare240_286_JL          = 0x33,        // 杰理 240*286
    VPDeviceScreenTypeSquare368_448_JL          = 0x34,        // 杰理 368*448
    VPDeviceScreenTypeCircle466_466_JL          = 0x35,        // 杰理 466*466
    VPDeviceScreenTypeCircle412_412_JL          = 0x36,        // 杰理 412*412
    VPDeviceScreenTypeSquare320_380_JL          = 0x37,        // 杰理 320*380
    VPDeviceScreenTypeSquare240_296_JL          = 0x38,        // 杰理 240*296
    VPDeviceScreenTypeSquare320_386_JL          = 0x39,        // 杰理 320*386
    VPDeviceScreenTypeSquare410_502_JL          = 0x3A,        // 杰理 410*502
    VPDeviceScreenTypeSquare240_292_JL          = 0x3B,        // 杰理 240*292
    VPDeviceScreenTypeCircle240_240_JL          = 0x3C,        // 杰理 240*240
    VPDeviceScreenTypeSquare200_320_JL          = 0x3D,        // 杰理 200*320
    VPDeviceScreenTypeSquare172_320_JL          = 0x3E,        // 杰理 172*320
    VPDeviceScreenTypeCircle390_390_JL          = 0x3F,        // 杰理 390*390
    VPDeviceScreenTypeSquare390_450_JL          = 0x40,        // 杰理 390*450
    VPDeviceScreenTypeCircle416_416_JL          = 0x41,        // 杰理 416*416
    VPDeviceScreenTypeSquare240_296_JL_Apple    = 0x42,        // 杰理 240*296 苹果款，用以区分自定义背景
    VPDeviceScreenTypeCircle320_320_JL          = 0x43,        // 杰理 320*320
    VPDeviceScreenTypeSquare240_280_JL_Apple    = 0x44,        // 杰理 240*280 苹果款，用以区分自定义背景
    VPDeviceScreenTypeSquare240_284_JL_Apple    = 0x45,        // 杰理 240*284 苹果款，用以区分自定义背景
    VPDeviceScreenTypeSquare240_286_JL_Apple    = 0x46,        // 杰理 240*286 苹果款，用以区分自定义背景
    VPDeviceScreenTypeSquare368_448_JL_Apple    = 0x47,        // 杰理 368*448 苹果款，用以区分自定义背景
    VPDeviceScreenTypeSquare320_380_JL_Apple    = 0x48,        // 杰理 320*380 苹果款，用以区分自定义背景
    VPDeviceScreenTypeSquare320_386_JL_Apple    = 0x49,        // 杰理 320*386 苹果款，用以区分自定义背景
    VPDeviceScreenTypeSquare410_502_JL_Apple    = 0x4A,        // 杰理 410*502 苹果款，用以区分自定义背景
    VPDeviceScreenTypeSquare240_292_JL_Apple    = 0x4B,        // 杰理 240*292 苹果款，用以区分自定义背景
    VPDeviceScreenTypeCircle240_240_JL_Apple    = 0x4C,        // 杰理 240*240 苹果款，用以区分自定义背景
    VPDeviceScreenTypeCircle360_360_JL_Apple    = 0x4D,        // 杰理 360*360 苹果款，用以区分自定义背景
    VPDeviceScreenTypeCircle412_412_JL_Apple    = 0x4E,        // 杰理 412*412 苹果款，用以区分自定义背景
    VPDeviceScreenTypeCircle466_466_JL_Apple    = 0x4F,        // 杰理 466*466 苹果款，用以区分自定义背景
    VPDeviceScreenTypeCircle480_480_JL          = 0x50,        // 杰理 480*480
    VPDeviceScreenTypeSquare240_240_JL          = 0x51,        // 杰理 240*240 方屏
};

typedef NS_ENUM(NSUInteger, VPPhotoDialTimePosition) {
    // 上中下 有些方屏比较窄，也设计成上中下三个位置
    VPPhotoDialTimePositionTop = 1,         // top
    VPPhotoDialTimePositionMiddle,          // middle
    VPPhotoDialTimePositionBottom,          // bottom
    // 四个角
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
    /* 如果是以下类型，需隐藏此项，因为电池存在百分比与固定格数的区分
     * VPDeviceScreenTypeSquare240_280_QFN
     * VPDeviceScreenTypeSquare240_280_QFN_RIG
     * VPDeviceScreenTypeSquare240_284_QFN
     * VPDeviceScreenTypeSquare240_286_QFN
     */
    VPPhotoDialTimeTopAndBottomElementBatteryAndBLE,
};


NS_ASSUME_NONNULL_BEGIN
@class VPPhotoDialConfigModel;
@interface VPPhotoDialModel : NSObject

@property (nonatomic, assign, readonly) NSUInteger index;
/// 屏幕的类型
@property (nonatomic, assign, readonly) VPDeviceScreenType screenType;
/// 设备表盘的基本配置信息，根据screenType做的映射配置
/// 如果获取到的为nil，可能是SDK未适配该屏型
@property (nonatomic, strong, readonly) VPPhotoDialConfigModel *configModel;
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

/*
 默认为deviceColor的值，0xFFFFF if deviceColor is nil;
 可以用来进行颜色校准 格式 RGB-888 如 AABBCC：AA表示Red, 以此类推
 注意⚠️：https://en.wikipedia.org/wiki/Color_depth or https://baike.baidu.com/item/%E8%89%B2%E5%BD%A9%E6%B7%B1%E5%BA%A6/1196418
   - 设备的屏幕颜色使用 High color (16-bit) RGB 565
   - 手机的屏幕颜色使用 True color (24-bit) RGB 888
   基于以上原因，会导致手机上显示的颜色与设备的颜色有差异
   如果要减少颜色的差异，可以对下发的颜色进行校准，如：
   APP显示 0xFF0000 红色，下发设备 0xF00000。映射关系：0xFF0000 -> 0xF00000
*/
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
