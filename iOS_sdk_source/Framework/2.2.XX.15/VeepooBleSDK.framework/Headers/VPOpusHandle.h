//
//  VPOpusHandle.h
//  WYPHealthyThird
//
//  Created by fengye on 2024/12/4.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define DocumentDirPath [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]

extern NSString *const kRecordedAudioFileName;



typedef void(^VPOpusDecodeResultBlock)(BOOL success, NSString *filePath, NSData *data);

@interface VPOpusHandle : NSObject

+ (instancetype)shareInstance;

/**
 将opus数据解码成PCM数据
 
 @param opusData 已编码opus格式数据
 */
- (void)decodeOpusDataToPcmData:(NSData *)opusData andSaveFile:(BOOL)save resultBlock:(VPOpusDecodeResultBlock)resultBlock;

@end

NS_ASSUME_NONNULL_END
