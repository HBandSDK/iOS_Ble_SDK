//
//  VPOxygenCurveView.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/12/20.
//  Copyright © 2018 veepoo. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    VPOxygenCurveTypeOxygen,//血氧呼吸暂停曲线
    VPOxygenCurveTypeCardiacLoad,//心脏负荷
    VPOxygenCurveTypeSleepActivity,//睡眠活动
    VPOxygenCurveTypeRespirationRate,//呼吸率
    VPOxygenCurveTypeHypoxiaTime,//低氧时间
}VPOxygenCurveType;

@protocol VPOxygenCurveViewDelegate <NSObject>

//点击视图右边的按钮, 进入详情界面, 详情界面要自己写
- (void)clickListBtnWithOxygenCurveType:(VPOxygenCurveType)curveType;

@end

@interface VPOxygenCurveView : UIView

//初始化视图,根据type类型返回, 必须使用这个构造方法创建类
- (instancetype)initWithVPOxygenCurveType:(VPOxygenCurveType)type;

@property (nonatomic, weak) id<VPOxygenCurveViewDelegate>delegate;

//这里传入从数据库中取出一天血氧的数据即可
@property (nonatomic, strong) NSArray *oneDayOxygens;

//视图左上角标题
@property (nonatomic, strong) NSString *title;

//下方提示颜色对应的提示文本, 如偏低、偏高、正常, 依次从左到右, 数据的count必须与对应模块的提示数量保持一致
@property (nonatomic, strong) NSArray *describeTitles;

//这里设置listBtn是否隐藏
@property (nonatomic, assign) BOOL listBtnHide;

@end
