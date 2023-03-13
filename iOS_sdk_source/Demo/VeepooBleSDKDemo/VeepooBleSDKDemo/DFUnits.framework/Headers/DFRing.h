//
//  DFRing.h
//  libDVRunning
//
//  Created by DFung on 2017/7/13.
//  Copyright © 2017年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DFRing : NSObject
@property(assign,nonatomic)int32_t len_total;


/**
 *  用途:【Ring Buffer】剩余容量
 *  @return  uint32_t   容量大小
 */
-(uint32_t)ringUsable;

/**
 *  用途:创建【Ring Buffer】
 *  @param   size   循环buffer的大小
 *  @return  BOOL   创建是否成功
 */
-(BOOL)ringMakeSize:(int32_t)size;

/**
 *  用途:存入数据。
 *  @param   buf    数据地址
 *  @param   size   数据大小
 */
-(uint32_t)ringPut:(void*)buf Size:(uint32_t)size;

/**
 *  用途:获取数据。
 *  @param   buf    数据地址
 *  @param   size   数据大小
 */
-(uint32_t)ringGet:(void*)buf Size:(uint32_t)size;

/**
 *  用途:擦除【Ring Buffer】的数据。
 */
-(void)ringClean;

/**
 *  用途:完全释放【Ring Buffer】
 */
-(void)ringRelease;

@end
