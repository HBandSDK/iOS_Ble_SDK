//
//  JLModel_SPEEX.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_SpeakType) {
    JL_SpeakTypeDo                  = 0,    //开始录音
    JL_SpeakTypeDone                = 1,    //结束录音
    JL_SpeakTypeDoing               = 2,    //正在录音
    JL_SpeakTypeDoneFail            = 0x0f, //结束失败
};
typedef NS_ENUM(UInt8, JL_SpeakDataType) {
    JL_SpeakDataTypePCM             = 0,    //PCM数据
    JL_SpeakDataTypeSPEEX           = 1,    //SPEEX数据
    JL_SpeakDataTypeOPUS            = 2,    //OPUS数据
};

@interface JLModel_SPEEX : NSObject
@property(assign,nonatomic)JL_SpeakType     mSpeakType;
@property(assign,nonatomic)JL_SpeakDataType mDataType;
@property(assign,nonatomic)uint8_t          mSampleRate;            //0x08=8k，0x10=16k
@property(assign,nonatomic)uint8_t          mVad;                   //断句方: 0:固件 1:APP
@end

NS_ASSUME_NONNULL_END
