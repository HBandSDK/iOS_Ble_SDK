//
//  VPQH15SecurityProtectionConst.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/1/7.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

/**------------------------------------状态枚举------------------------------------**/

// QH15 指令类型
typedef NS_ENUM(uint8_t, VPQH15SPCmd){
   
    VPQH15SPCmdGNSSLocation = 0x08, // GNSS实时位置数据交互
    VPQH15SPCmdProtectionFunc = 0x09,  // 守护功能状态控制
};



// QH15 安全守护功能类型
typedef NS_ENUM(uint8_t, VPQH15SPFunctionType){
   
    VPQH15SPFunctionTypeGNSS = 0x01,  // GNSS运动
    VPQH15SPFunctionTypeFamily = 0x02,// 亲情安全守护
    VPQH15SPFunctionTypeSOS = 0x03,   // SOS紧急求助
};

// QH15 安全守护类型
typedef NS_ENUM(uint8_t, VPQH15SPType){
   
    VPQH15SPTypeReq = 0x01,  // 请求获取实时位置
    VPQH15SPTypePush = 0x02,// 推送实时位置数据

};

// QH15 安全守护GNSS类型
typedef NS_ENUM(uint8_t, VPQH15SPGNSSState){
    
    VPQH15SPGNSSStateNone = 0x00,   // 无指令
    VPQH15SPGNSSStateEffectiveLocation = 0x01,       // 有效定位
    VPQH15SPGNSSStateInvalidLocation = 0x02,       // 无效定位
    VPQH15SPGNSSStatePoorSignal = 0x03,       // 信号差
    VPQH15SPGNSSStateNoPermission = 0x04,       // 无权限
};

// QH15 设置安全守护返回ACK类型
typedef NS_ENUM(uint8_t, VPQH15SetProtectionFuncAckState){
    
    VPQH15SetProtectionFuncAckStateSuccess = 0x01,   // 成功
    VPQH15SetProtectionFuncAckStateLowBattery = 0x02,       // 手表电量过低无法开启
    VPQH15SetProtectionFuncAckStateLocationMalfunction = 0x03,       // 定位模块异常

};

