//
//  DFHmacMD5.h
//  DFUnits
//
//  Created by DFung on 2016/12/13.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DFHmacMD5 : NSObject

/*
 *  MD5加密32位
 */
+ (NSString *)HmacMD5String:(NSString *)string;

/*
 *  HmacMD5加密
 */
+ (NSString *)HmacMD5String:(NSString *)string
                        Key:(NSString *)keyStr;

@end
