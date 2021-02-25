//
//  VPOxygenAnalysisSectionTwoView.h
//  WYPHealthyThird
//
//  Created by 张冲 on 17/7/21.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol VPOxygenAnalysisSectionTwoViewDelegate <NSObject>

- (void)oxygenAnalysisSectionSectionTwoViewBtnActionWithTag:(NSInteger)tag;

@end

@interface VPOxygenAnalysisSectionTwoView : UIView

- (void)setOxygenAnalysisSectionTwoViewUI;

@property (weak, nonatomic) IBOutlet UIView *sectionTwoBackView;


@property (weak, nonatomic) IBOutlet UILabel *nameLabel;//名称
@property (weak, nonatomic) IBOutlet UILabel *averageLabel;//平均值
@property (weak, nonatomic) IBOutlet UILabel *maxLabel;//最高(最低)
@property (weak, nonatomic) IBOutlet UILabel *referenceValueLabel;//参考值
@property (weak, nonatomic) IBOutlet UIButton *oxygenNameBtn;//血氧浓度
@property (weak, nonatomic) IBOutlet UILabel *oxygenAverageLabel;
@property (weak, nonatomic) IBOutlet UILabel *oxygenAbnormalLabel;
@property (weak, nonatomic) IBOutlet UILabel *oxygenReferenceLabel;
@property (weak, nonatomic) IBOutlet UIButton *respirationRateBtn;//呼吸率
@property (weak, nonatomic) IBOutlet UILabel *respirationRateAverageLabel;
@property (weak, nonatomic) IBOutlet UILabel *respirationRateAbnormalLabel;
@property (weak, nonatomic) IBOutlet UILabel *respirationRateReferenceLabel;
@property (weak, nonatomic) IBOutlet UIButton *hypoxiaTimeBtn;//低氧时间
@property (weak, nonatomic) IBOutlet UILabel *hypoxiaTimeAverageLabel;
@property (weak, nonatomic) IBOutlet UILabel *hypoxiaTimeAbnormalLabel;
@property (weak, nonatomic) IBOutlet UILabel *hypoxiaTimeReferenceLabel;
@property (weak, nonatomic) IBOutlet UIButton *cardiacLoadBtn;//心脏负荷
@property (weak, nonatomic) IBOutlet UILabel *cardiacLoadAverageLabel;
@property (weak, nonatomic) IBOutlet UILabel *cardiacLoadAbnormalLabel;
@property (weak, nonatomic) IBOutlet UILabel *cardiacLoadReferenceLabel;
@property (weak, nonatomic) IBOutlet UIButton *HRVBtn;//脉率变异性
@property (weak, nonatomic) IBOutlet UILabel *HRVAverageLabel;
@property (weak, nonatomic) IBOutlet UILabel *HRVAbnormalLabel;
@property (weak, nonatomic) IBOutlet UILabel *HRVReferenceLabel;
@property (weak, nonatomic) IBOutlet UIButton *sleepActivityBtn;//睡眠活动幅度
@property (weak, nonatomic) IBOutlet UILabel *sleepActivityAverageLabel;
@property (weak, nonatomic) IBOutlet UILabel *sleepActivityAbnormalLabel;
@property (weak, nonatomic) IBOutlet UILabel *sleepActivityReferenceLabel;

//把一天的血氧数据用VPOxygenAnalysisModel初始化得到的属性parseOneDayDict传入进来
@property (nonatomic, strong) NSDictionary *oneDayParseDict;
@property (nonatomic, weak) id<VPOxygenAnalysisSectionTwoViewDelegate>delegate;
@end




