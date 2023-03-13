//
//  JLModel_File.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_BrowseType) {
    JL_BrowseTypeFolder             = 0,    //文件夹
    JL_BrowseTypeFile               = 1,    //文件
};
typedef NS_ENUM(UInt8, JL_CardType) {
    JL_CardTypeUSB                  = 0,    //USB
    JL_CardTypeSD_0                 = 1,    //SD_0
    JL_CardTypeSD_1                 = 2,    //SD_1
    JL_CardTypeFLASH                = 3,    //FLASH
    JL_CardTypeLineIn               = 4,    //LineIn
    JL_CardTypeFLASH2               = 5,    //FLASH2
};

@interface JLModel_File : NSObject<NSCopying>
@property (assign,nonatomic) JL_BrowseType  fileType;
@property (assign,nonatomic) JL_CardType    cardType;
@property (assign,nonatomic) uint32_t       fileClus;
@property (assign,nonatomic) uint16_t       fileIndex;
@property (copy,  nonatomic) NSString       *fileHandle;
@property (copy,  nonatomic) NSString       *fileName;
@property (copy,  nonatomic) NSString       *folderName;
@property (copy,  nonatomic) NSData *__nullable pathData;
@end

NS_ASSUME_NONNULL_END
