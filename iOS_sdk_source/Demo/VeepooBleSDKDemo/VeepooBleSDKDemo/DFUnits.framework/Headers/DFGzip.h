//
//  DFGzip.h
//  DFUnits
//
//  Created by DFung on 2016/12/13.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DFGzip : NSObject


/**
 *  Gzip 解压(Need Include => libz.1.2.8.tbd)
 */
+(NSData *)uncompressZippedData:(NSData *)compressedData;

/**
 *  Gzip 压缩(Need Include => libz.1.2.8.tbd)
 */
+(NSData *)gzipData:(NSData *)pUncompressedData;


@end
