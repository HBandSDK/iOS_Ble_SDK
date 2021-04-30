//
//  Header.h
//  GRDFU
//
//  Created by dingjian on 2019/12/21.
//  Copyright © 2019 Goodix. All rights reserved.
//

#ifndef Error_Code_h
#define Error_Code_h

#define CMD_DONE (0)
#define CMD_TIMEOUT (-1)
#define CMD_ABORT (-2)
#define CMD_ERROR (-3)
#define CMD_ERROR_ON_FINISH (-4)

#define CMD_ERR_BLE_POWEROFF (1001)
#define CMD_ERR_DEVICE_NOT_FOUND (1002)

#define CMD_ERR_DEVICE_IS_NULL (2001)
#define CMD_ERR_DEVICE_NOT_CONNECTED (2002)
#define CMD_ERR_FAILED_TO_DISCOVERY_SERVICE (2003)
#define CMD_ERR_FAILED_TO_CFG_CHARACTERISTIC (2004)
#define CMD_ERR_DEVICE_DISCONNECTED (2005)

#define CMD_ERR_ABSENT_CHARACTERISTIC (3001)
#define CMD_ERR_CAN_NOT_WRITE_WITHOUT_RESPONSE (3002)


// for GRDGetImgInfoList
#define CMD_ERR_OP_FAILED (4001)

#define CMD_ERR_NO_FW (5001)
#define CMD_ERR_INVALID_FW (5002)
#define CMD_ERR_MEMORY_OVERLAID (5003)
#define CMD_ERR_START_PROGRAM (5004)
#define CMD_ERR_PROGRAM_FLASH (5005)
#define CMD_ERR_PROGRAM_END (5006)

// for GRDBuilder
#define CMD_ERR_FW_OVERLAID (6001)
#define CMD_ERR_SELECT_NONE_IN_FW_LIST (6002)
#define CMD_ERR_ABORT_BY_USER (6003)
#define CMD_ERR_FW_Encrypted_Dismatch (6004)
#define CMD_ERR_FW_OverLay_BootInfo (6005)


// for GRDSetImgInfoList
#define CMD_ERR_INVALID_LIST (7001)

// for GRDSetCtrlData
#define CMD_ERR_INVALID_CTRL_DATA (8001)
#define CMD_ERR_UNABLE_TO_SEND_CTRL_DATA (8002)

// for GRDInitExtFlashCmd
#define CMD_ERR_CFG_SPI_FAILED (9001)
#define CMD_ERR_READ_FLASH_INFO_FAILED (9002)

// for misc
#define CMD_ERR_RESET_FAILED (11001)
#endif /* Error_Code_h */
