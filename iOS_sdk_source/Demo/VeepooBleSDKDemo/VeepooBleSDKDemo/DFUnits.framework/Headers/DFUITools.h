//
//  DFUITools.h
//  DFUnits
//
//  Created by DFung on 2016/12/9.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void (^TipsCompletion) (void);


@class DFTips;
@interface DFUITools : NSObject

#define kDF_SCR_W_0         (int)[DFUITools screen_W]
#define kDF_SCR_H_0         (int)[DFUITools screen_H]

#define kDF_SCR_W_1         (int)[DFUITools screen_1_W]
#define kDF_SCR_H_1         (int)[DFUITools screen_1_H]
#define kDF_RGBA(r,g,b,a)   [UIColor colorWithRed:((r)/255.0) green:((g)/255.0) blue:((b)/255.0) alpha:(a)]

#pragma mark 屏幕尺寸
/**
 *  设备屏幕的【宽】
 */
+(CGFloat)screen_W;

/**
 *  设备屏幕的【长】
 */
+(CGFloat)screen_H;

/**
 *  设备竖屏的【宽】
 */
+(float)screen_1_W;

/**
 *  设备竖屏的【长】
 */
+(float)screen_1_H;

/**
 *  iPhone竖屏的【宽】
 */
+(float)screen_2_W;

/**
 *  iPhone竖屏的【长】
 */
+(float)screen_2_H;

/**
 *  获取手机版本
 */
+(float)getVersion;

/**
 *  获取当前设备UUID
 */
+(NSString*)getUUID;

/**
 *  获取当前UIWindow
 */
+(UIWindow*)getWindow;

/**
 *  多语言化：当前系统语言
 */
+(NSString*)systemLanguage;

/**
 *  多语言化：选择
 */
+(void)languageSet:(NSString*)lan;

/**
 *  多语言化：翻译
 */
+(NSString*)languageText:(NSString*)key Table:(NSString*)table;

/**
 *  设置UIButton的图片
 */
+(void)setButton:(UIButton*)btn Image:(NSString*)image;
+(void)setButton:(UIButton*)btn Image_1:(UIImage*)image;

/**
 *  设置UIButton的文字
 */
+(void)setButton:(UIButton*)btn Text:(NSString*)text;

/**
 *  设置UIButton的字体颜色
 */
+(void)setButton:(UIButton*)btn Color:(UIColor*)color;

/**
 *  获取【定宽Label】的【高】。
 */
+ (CGFloat)labelHeightByWidth:(CGFloat)width Text:(NSString *)text Font:(UIFont *)font;

/**
 *  获取【定宽Label】的【宽】。
 */
+ (CGFloat)labelWidthByWidth:(CGFloat)width Text:(NSString *)text Font:(UIFont *)font;

/**
 *  加载Nib文件的UI。
 */
+(id)loadNib:(NSString*)name;


/**
 *  增加触摸事件。
 */
+(UITapGestureRecognizer*)addSingleTaps:(int)taps
                                   View:(UIView*)view
                                 Target:(id)target
                                 Action:(SEL)action;


/**
 *  弄个UIColor，【RGB值】和【透明度Alpha】
 */
+(UIColor*)colorR:(float)r G:(float)g B:(float)b AP:(float)ap;




#pragma mark >>> DFTips___APIs___
+ (DFTips *)showHUDWithLabel:(NSString *)labelText
                      onView:(UIView *)view;

+ (DFTips *)showHUDWithLabel_1:(NSString *)labelText
                        onView:(UIView *)view;

+ (DFTips *)showHUDWithDetailLabel:(NSString *)detailLabelText
                            onView:(UIView *)view;

+ (DFTips *)showHUDOnWindowWithLabel:(NSString *)labelText;

+ (DFTips *)showHUDWithLabel:(NSString *)labelText
                      onView:(UIView *)view
                            color:(UIColor *)color;

+ (DFTips *)showHUDWithLabel:(NSString *)labelText
                      onView:(UIView *)view
                       color:(UIColor *)color
              labelTextColor:(UIColor *)textColor
      activityIndicatorColor:(UIColor *)actIndicatorColor;

+ (DFTips *)showHUDOnWindowWithLabel:(NSString *)labelText
                               color:(UIColor *)color;

+ (DFTips *)showTransparentHUDWithLabel:(NSString *)labelText
                                 onView:(UIView *)view;

+ (DFTips *)showTransparentHUDOnWindowWithLabel:(NSString *)labelText
                                 labelTextColor:(UIColor *)textColor;

+ (DFTips *)showTransparentHUDOnWindowWithLabel:(NSString *)labelText;

+ (DFTips *)changeLabelText:(NSString *)labelText;

+ (DFTips *)changeDetailLabelText:(NSString *)labelText;

+ (void)removeHUD;

+ (void)removeHUDWithDelay:(float)time;

+ (void)removeHUDWithDelay:(float)time
                completion:(TipsCompletion)completion;

+ (void)showText:(NSString *)text
          onView:(UIView *)view
           delay:(float)time;

+ (void)showText:(NSString *)text
          onView:(UIView *)view
           delay:(float)time
      completion:(TipsCompletion)completion;

+ (void)showText_1:(NSString *)text
            onView:(UIView *)view
             delay:(float)time;

+ (void)showDetailText:(NSString *)text
                onView:(UIView *)view
                 delay:(float)time;

+ (void)showDetailText:(NSString *)text
                onView:(UIView *)view
                 delay:(float)time
            completion:(TipsCompletion)completion;

+(void)showClearLayer;
+(void)showClearLayerDelay:(NSTimeInterval)time;

+(void)openWaittting:(NSString*)text delay:(NSTimeInterval)time;
+(void)closeWaitting:(NSTimeInterval)time;


@end
