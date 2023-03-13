//
//  JLModel_Flash.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_FlashSystemType) {
    JL_FlashSystemType_FATFS        = 0,
    JL_FlashSystemType_RCSP         = 1,
};

@interface JLModel_Flash : NSObject
@property(assign,nonatomic)uint32_t         mFlashSize;             //flash大小
@property(assign,nonatomic)uint32_t         mFatfsSize;             //FAT系统大小

@property(assign,nonatomic)JL_FlashSystemType mFlashType;            //系统类型 0:FATFS，1:RCSP
@property(assign,nonatomic)uint8_t          mFlashStatus;           //系统当前状态,0x00正常，0x01异常
@property(assign,nonatomic)uint16_t         mFlashVersion;          //Flash版本

@property(assign,nonatomic)uint16_t         mFlashReadMtu;          //读数MTU
@property(assign,nonatomic)uint16_t         mFlashCluster;          //扇区大小

@property(strong,nonatomic)NSString         *mFlashMatchVersion;    //手表兼容列表"W001,W002,W003"
@property(assign,nonatomic)uint16_t         mFlashWriteMtu;         //写数MTU
@property(assign,nonatomic)uint16_t         mScreenWidth;           //屏幕宽度
@property(assign,nonatomic)uint16_t         mScreenHeight;          //屏幕高度
@end

NS_ASSUME_NONNULL_END
