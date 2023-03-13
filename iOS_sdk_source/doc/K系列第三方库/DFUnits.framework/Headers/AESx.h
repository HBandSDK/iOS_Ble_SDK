//
//  AES_DF.h
//  WifiAudio
//
//  Created by zhjl on 15-5-29.
//  Copyright (c) 2015年 ZH-jl. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AESx : NSObject

+(id)shared;

-(unsigned int)Dcs_EnCodeSrc:(char *)src
                         Des:(char *)des
                     Lenghts:(unsigned int)lengths
                         Key:(char *)key;

-(void)Dcs_DeCodeSrc:(char *)src
                 Des:(char *)des
             Lengths:(unsigned int)lengths
                 Key:(char *)key;

-(unsigned int)ns_crc32Buffer:(const unsigned char *)buffer
                       Lenght:(unsigned int)len;

@end
