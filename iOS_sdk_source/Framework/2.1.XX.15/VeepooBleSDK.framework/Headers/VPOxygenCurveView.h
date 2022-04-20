//
//  VPOxygenCurveView.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/12/20.
//  Copyright © 2018 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    VPOxygenCurveTypeOxygen = 0,//血氧呼吸暂停曲线
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


/**
 修改下边点的颜色, 在设置frame之前调用,如果为nil就是SDK默认值

 @param pointColors 点的颜色
 @param titleColors 文字的颜色
 @param titles 文本
 */
- (void)describePointColors:(NSArray <UIColor *>*)pointColors titleColors:(NSArray <UIColor *>*)titleColors titles:(NSArray <NSString *>*)titles;


/**
 修改曲线的颜色, 在设置frame之前调用
 传nil就是SDK默认值, 此处数组的长度必须是,血氧界面1, 睡眠活动3, 低氧时间2, 心脏负荷3, 呼吸率2
 如果不符合设置无效

 @param pointColors 颜色值数组从下到上
 */
- (void)lineColors:(NSArray <UIColor *>*)pointColors;

@end
