//
//  GCXHexReader.h
//  libcomx
//
//  Created by dingjian on 2019/12/22.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface GCXHexReader : NSObject

+(instancetype)readerForData:(NSData*)data;
+(instancetype)readerForBytes:(const void*)data size:(NSUInteger)size;

-(uint32_t)getValueWithSize:(uint32_t)size;
-(uint32_t)getValueWithSize:(uint32_t)size isBigEndian:(BOOL)bigEndian;
-(NSData*)getDataWithSize:(uint32_t)size;

-(const void*)getBuffer;
-(NSUInteger)getRemainingSize;
-(NSUInteger)getBufferSize;

// Return current read position of raw byte array.
-(NSUInteger)getAbsolutePos;

// Set a sub range in raw byte array. The pos supports negative index.
-(instancetype)limitTo:(NSInteger)pos size:(NSUInteger)size;

// Set relative read position in the range set by limitTo:size:
-(instancetype)seekTo:(NSUInteger)pos;

@end

NS_ASSUME_NONNULL_END
