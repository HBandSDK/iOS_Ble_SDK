//
//  AbsCmd.h
//  GRDFU
//
//  Created by dingjian on 2019/12/21.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ErrorCode.h"
#import "GRDFULog.h"


NS_ASSUME_NONNULL_BEGIN

@interface AbsCmd : NSObject
{
}
-(void)start;
-(BOOL)isRunning;
-(BOOL)isFinished;
-(void)abort;

// 需要子类覆盖的方法
// 子类在调用 [super onAction] 后，应该使用 [self isFinished] 判断是否还需要继续执行。
-(void)onAction;
-(void)onTimeout;
-(void)onCleanUp; // 命令结束了，需要清理资源，可能是正常结束，也可能是异常或中止
-(void)resetObserver; //复位回调，用于解除cmd对外部(如task)的强依赖。

// 给子类调用的方法
-(void)setTimeout:(double)second; // 设置命令的超时时间，这句代码必须在onAction里面调用。
-(void)publishProgress:(int)progress;
-(void)publishFinishWith:(int)code andError:(nullable NSException*)err;

-(void)observeProgress:(void(^)(AbsCmd* src, int percent))observer;
-(void)observeFinish:(void(^)(AbsCmd* src, int errCode, NSException* err))observer;
@end

NS_ASSUME_NONNULL_END
