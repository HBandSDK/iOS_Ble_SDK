//
//  DFNotice.h
//  IPCamera
//
//  Created by DFung on 16/5/27.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>



@interface DFNotice : NSObject

/**
 *  发送通知
 *
 *  @param name  :通知名字
 *  @param object:传递的对象
 */
+(void)post:(NSString*)name Object:(id)object;

/**
 *  监听通知
 *
 *  @param name  :通知名字
 *  @param action:实现方法
 *  @param own   :监听者
 */
+(void)add:(NSString*)name Action:(SEL)action Own:(id)own;

/**
 *  监听取消
 *
 *  @param name:通知名字
 *  @param own :监听者
 */
+(void)remove:(NSString*)name Own:(id)own;

/** (iOS 10.0 以上有效。)
 *  定时通知
 *
 *  @param date:yyyyMMddHHmmss
 *  @param repeat:0 -->不重复
 */
+(void)pushLocalNoticeDate:(NSString*)date
                        ID:(NSString*)noteId
                     Txt_0:(NSString*)txt_0
                     Txt_1:(NSString*)txt_1
                     Txt_2:(NSString*)txt_2
                     Badge:(NSNumber*)badge
                    Repeat:(BOOL)repeat;

@end
