//
//  VPAnalysisViewFactory.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2019/1/15.
//  Copyright © 2019 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPOxygenAnalysisSectionResultView.h"
#import "VPOxygenAnalysisSectionOneView.h"
#import "VPOxygenAnalysisSectionTwoView.h"
#import "VPOxygenAnalysisSectionThreeView.h"
#import "VPOxygenAnalysisSectionFourView.h"

@interface VPAnalysisViewFactory : NSObject

+ (VPOxygenAnalysisSectionResultView *)createResultView;

+ (VPOxygenAnalysisSectionOneView *)createSectionOneView;

+ (VPOxygenAnalysisSectionTwoView *)createSectionTwoView;

+ (VPOxygenAnalysisSectionThreeView *)createSectionThreeView;

+ (VPOxygenAnalysisSectionFourView *)createSectionFourView;

@end
