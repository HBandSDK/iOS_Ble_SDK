//
//  NfcModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/3.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface NfcModel : NSObject

/// NFC标签
@property(nonatomic,assign)UInt16 idCard;

/// 保留位
@property(nonatomic,strong)NSData *reserver;

/// 设备索引
@property(nonatomic,strong)NSData *devHandler;

/// 更新时间戳，用于排序
@property(nonatomic,strong)NSDate *updateTime;

/// nfc数据文件名，格式如下：XX.nfc，XX是0~9
@property(nonatomic,strong)NSString *nfcFileName;

/// 别名,最大字符长度为26, 不足部分补‘\0’ 编码格式:UTF-8(以后可以保留位决定) 例如:公司门禁卡，家里门禁等等
@property(nonatomic,strong)NSString *nickName;

/// 可变字段长度，包含crc + nfc_id
@property(nonatomic,assign)UInt16 variableLength;

/// NFC 数据的CRC
@property(nonatomic,strong)NSData   *crc;

/// nfc数据的唯一值
@property(nonatomic,strong)NSData   *nfc_id;


+(NfcModel *)initMsgModel:(NSData *)data;

/// 解析NFC头部数据
/// @param basicData 裸数据
+(NSArray<NfcModel *> *)initMSGModels:(NSData *)basicData;

@end

NS_ASSUME_NONNULL_END





@interface NfcFileModel : NfcModel

/// NFC 数据
@property(nonatomic,strong)NSData * _Nonnull nfcData;
@property(nonatomic,assign,readonly)UInt32  length;
+(NfcFileModel *_Nonnull)initFileModel:(NSData *_Nonnull)data;

@end




