//
//  DFCrc16.h
//  DFUnits
//
//  Created by DFung on 2017/3/6.
//  Copyright © 2017年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <unistd.h>
#include <_types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

@interface DFCrc16 : NSObject
/**
 *  单独Crc16值.
 */
+(uint16_t)didCrc16:(uint8_t*)pt
             Length:(uint16_t)len;
/**
 *  累加Crc16值.
 */
+(uint16_t)didCrc16All:(uint8_t*)pt
                Length:(uint16_t)len
              CrcValue:(uint16_t)value;
/**
 *  清除Crc值.
 */
+(void)didResetCrc;

@end
