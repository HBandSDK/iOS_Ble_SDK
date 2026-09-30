//
//  VPQH15SecurityProtectionConst.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/1/7.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

/**------------------------------------状态枚举------------------------------------**/



// QH15 安全守护
typedef NS_ENUM(uint8_t, VPQH15SecurityProtectionState){
    
    VPQH15SecurityProtectionStateNone = 0x00,   // 无指令
    VPQH15SecurityProtectionStateEffectiveLocation = 0x01,       // 有效定位
    VPQH15SecurityProtectionStateInvalidLocation = 0x02,       // 无效定位
    VPQH15SecurityProtectionStatePoorSignal = 0x03,       // 信号差
    VPQH15SecurityProtectionStateNoPermission = 0x04,       // 无权限
};

// QH15 设置安全守护返回ACK类型
typedef NS_ENUM(uint8_t, VPQH15SetProtectionFuncAckState){
    
    VPQH15SetProtectionFuncAckStateSuccess = 0x01,   // 成功
    VPQH15SetProtectionFuncAckStateLowBattery = 0x02,       // 手表电量过低无法开启
    VPQH15SetProtectionFuncAckStateLocationMalfunction = 0x03,       // 定位模块异常

};

// QH15 安全守护位置交互类型
typedef NS_ENUM(uint8_t, VPQH15SPType){
   
    VPQH15SPTypeReq = 0x01,  // 请求获取实时位置
    VPQH15SPTypePush = 0x02,// 推送实时位置数据
};
