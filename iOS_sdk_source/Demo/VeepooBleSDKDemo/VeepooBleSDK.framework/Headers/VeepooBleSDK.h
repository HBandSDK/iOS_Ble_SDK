//
//  VeepooBleSDK.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/7.
//  Copyright © 2017年 zc.All rights reserved.

//  Developer qq: 2810503497, if there is a problem during the debugging process, you can contact qq, please add notes when using qq to use iOS Bluetooth SDK and company name

//  The reason why the -Objc is not supported in the SDK has been modified. The main reason is that the code writes repeatedly when the load is repeated.(已经修改SDK中不支持-Objc的原因，主要原因是代码写重复了加载的时候报重复错误)
// 在xcode11上因为代码@available的库编译 在11以下的xcode上跑不起来


#import <UIKit/UIKit.h>
#import "VPBleCentralManage.h"
#import "VPPeripheralManage.h"
#import "VPPeripheralAddManage.h"
#import "VPDataBaseOperation.h"
#import "VPPublicDefine.h"
#import "VPDFUOperation.h"
#import "VPPeripheralModel.h"
#import "VPDeviceAlarmModel.h"
#import "VPDeviceLongSeatModel.h"
#import "VPDeviceHeartAlarmModel.h"
#import "VPDeviceRaiseHandModel.h"
#import "VPDeviceBrightModel.h"
#import "VPDeviceFemaleModel.h"
#import "VPDeviceCountDownModel.h"
#import "VPHRVPublicTool.h"
#import "VPHRVLorentAnalysisModel.h"
#import "VPOxygenAnalysisModel.h"
#import "VPLowPowerModel.h"
#import "VPDialModel.h"
#import "VPPhotoDialModel.h"
#import "VPPhotoDialView.h"
#import "VPDeviceMarketDialModel.h"
#import "VPServerMarketDialModel.h"
#import "VPMarketDialManager.h"
#import "VPOxygenDisconnectTestModel.h"
#import "VPPttValueModel.h"
#import "VPECGTestResutHandle.h"

#import "VPSyncPersonalInfo.h"

//测试UI使用
#import "VPHRVLorentView.h"
#import "VPOxygenCurveView.h"
#import "VPDashView.h"
#import "VPDashHRVView.h"
#import "VPDashOxygenView.h"
#import "VPHRVCurveView.h"
#import "VPOxygenDetailController.h"

#import "VPAnalysisViewFactory.h"
#import "VPOxygenAnalysisSectionResultView.h"
#import "VPOxygenAnalysisSectionOneView.h"
#import "VPOxygenAnalysisSectionTwoView.h"
#import "VPOxygenAnalysisSectionThreeView.h"
#import "VPOxygenAnalysisSectionFourView.h"

#import "VPWeatherConfigModel.h"
#import "VPWeatherServerModel.h"
#import "VPWeatherHandle.h"
#import "VPWeatherServerHourlyModel.h"
#import "VPWeatherServerForecastModel.h"

#import "WLWeatherModel.h"
#import "WLWeatherManager.h"

#import "VPRRIntervalDataModel.h"
#import "VPRRIntervalDataHRVHandle.h"

//! Project version number for VeepooBleSDK.
FOUNDATION_EXPORT double VeepooBleSDKVersionNumber;

//! Project version string for VeepooBleSDK.
FOUNDATION_EXPORT const unsigned char VeepooBleSDKVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <VeepooBleSDK/PublicHeader.h>



