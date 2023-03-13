//
//  DFAction.h
//  DFUnits
//
//  Created by DFung on 16/1/25.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>



typedef void(^Action)();

@interface DFAction : NSObject

/**
 *  @how:Execution block on Asynchronous thread.
 */
+(void)subTask:(Action)block;

/**
 *  @how:Execution block on Synchronization thread.
 */
+(void)mainTask:(Action)block;

/**
 *  @how:Execution some blocks asynchronousily and make a summary.
 *  @tasks  block Array
 *  @block  final block
 */
+(void)subTasks:(NSArray*)tasks Final:(Action)block;

/**
 *  @how:Execution block after a few seconds.
 *  @param   sec     Delay time
 *  @param   block   Code block
 */
+(void)delay:(double)sec Task:(Action)block;

/**
 *  @how:Execution block only once.
 *  @param   block   Code block
 */
+(void)taskOnce:(Action)block;

/**
 *  @how:Execution block N times.
 *  @param   block   Code block
 *  @param   times   N
 */
+(void)task:(Action)block Times:(int)times;

/**
 *  设置执行代码的最小时间间隔gap。
 *  返回 YES：大于gap，建议继续执行。
 *  返回 NO： 小于gap，建议代码return。
 */
+(BOOL)setMinExecutionGap:(NSTimeInterval)gap;

/**
 *  @how:定时处理.
 *  @return   NSTimer
 */
+(NSTimer*)timingStart:(SEL)sel target:(id)objc Time:(NSTimeInterval)sec;

/**
 *  @how:暂停定时处理.
 *  @return   NSTimer
 */
+(void)timingPause:(__weak NSTimer*)timer;
/**
 *  @how:继续定时处理.
 *  @return   NSTimer
 */
+(void)timingContinue:(__weak NSTimer*)timer;
/**
 *  @how:摧毁定时处理功能.
 */
+(void)timingStop:(__weak NSTimer*)timer;

@end
