//
//  JL_NFC.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/2.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"
#import "JL_ManagerM.h"

@class JL_RCSP;
@class JL_EntityM;
@class NfcFileModel;
@class NfcModel;
NS_ASSUME_NONNULL_BEGIN

typedef void(^NfcSyncResult)(UInt8 result,NSArray<NfcModel *> * _Nullable models);

typedef void(^NfcIDResult)(UInt16 result);

typedef void(^NfcDefaultResult)(BOOL result);

typedef void(^NfcBeginAddResult)(JL_EntityM *entity);


@interface JL_NFC : NSObject

-(instancetype)initWith:(JL_EntityM *)entity FileHandler:(JL_FileHandleType)handler;


/// 同步NFC信息开始
-(void)w_syncNfcStart:(NfcSyncResult)result;


/// 修改NFC的信息
/// @param dict 修改的内容
/**
 dict 的内容
 {
 @"timestamp" : NSDate()
 @"nickname" : @"我的家"
 }
 如果key值找不到对应的value，那就说明该项值不参与被修改
 */
-(void)w_modifyNfc:(NSDictionary *)dict WithID:(UInt16)nfcID;


/// 删除NFC信息
/// @param model nfc头部model
-(void)w_deleteNfc:(NfcModel *)model;


/// 获取当前正在使用着的默认NFC卡ID
/// @param result NFC卡id
-(void)w_getNfcDefaultCard:(NfcIDResult)result;


/// 设置默认的NFC信息
/// @param model NFC头部model
-(void)w_setNfcDefalutCard:(NfcModel *)model result:(NfcDefaultResult)result;


/// 通知默认NFC改变
/// @param model NFC信息头部
-(void)w_NfcDefaultNotify:(NfcModel *)model;

/// 添加NFC文件
/// @param model NFC文件模型
/// @param result 开始传输操作
/** examp.
 NfcFileModel *fm = [[NfcFileModel alloc] init];
//    fm.idCard = ...
//    fm.nfcFileName = ...
 JL_NFC *mgr = [[JL_NFC alloc] init];
 [mgr w_NfcAddCard:fm BeginAdd:^(JL_EntityM * _Nonnull entity) {
    //大文件传输开始
     [entity.mCmdManager cmdBigFileData:#path WithFileName:#fileName Result:^(JL_BigFileResult result, float progress) {
         if (result == JL_BigFileTransferEnd) {
             //结束NFC文件添加
             [mgr w_NfcEndAdd:fm];
         }
         
     }];
 }];
 */
-(void)w_NfcAddCard:(NfcFileModel *)model BeginAdd:(NfcBeginAddResult)result;

/// 添加NFC文件结束
/// @param model NFC文件模型
-(void)w_NfcEndAdd:(NfcFileModel *)model;

@end

NS_ASSUME_NONNULL_END
