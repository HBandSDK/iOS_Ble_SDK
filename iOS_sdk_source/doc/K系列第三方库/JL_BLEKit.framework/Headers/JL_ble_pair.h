//
//  JL_ble_pair.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/10.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#ifndef JL_ble_pair_h
#define JL_ble_pair_h

#include <stdio.h>

void function_jieli(uint8_t *address,uint8_t *RAND,uint8_t *K,uint8_t *result);

#pragma mark CRC校验
unsigned short JL_CRC16(unsigned char *ptr, int len, uint16_t lastCrc);

#endif /* JL_ble_pair_h */
