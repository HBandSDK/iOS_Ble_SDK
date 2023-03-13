//
//  JL_MSG_Weather.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/5/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

 
typedef NS_ENUM(UInt8, JLWeatherType) {
    ///晴
    JLWeatherTypeSunny = 0x00,
    ///少云
    JLWeatherTypeCloudLess,
    ///晴间多云
    JLWeatherTypePartlyCloudy,
    ///多云
    JLWeatherTypeCloudiness,
    ///阴
    JLWeatherTypeOvercastSky,
    ///有风/和风/清风/微风
    JLWeatherTypeBreeze,
    ///平静
    JLWeatherTypeCalmWind,
    ///大风/强风/劲风/疾风
    JLWeatherTypeHighWind,
    ///飓风/狂爆风
    JLWeatherTypeHurricane,
    ///热带风暴/风暴
    JLWeatherTypeTropicalStorm,
    ///霾/中度霾/重度霾/严重霾
    JLWeatherTypeHaze,
    ///阵雨
    JLWeatherTypeShower,
    ///雷阵雨
    JLWeatherTypeThunderShower,
    ///雷阵雨并伴有冰雹
    JLWeatherTypeHallThunderShower,
    ///雨/小雨/毛毛雨/细雨/小雨-中雨
    JLWeatherTypeLightRain,
    ///中雨/中雨-大雨
    JLWeatherTypeModerateRain,
    ///大雨/大雨-暴雨
    JLWeatherTypeHeavyRain,
    ///暴雨/暴雨-大暴雨
    JLWeatherTypeDownpour,
    ///大暴雨/大暴雨-特大暴雨
    JLWeatherTypeExtraordinaryRainstorm,
    ///特大暴雨
    JLWeatherTypeHeavyDownpour,
    ///强阵雨
    JLWeatherTypeStrongRainShower,
    ///强雷阵雨
    JLWeatherTypeStrongThunderShower,
    ///极端降雨
    JLWeatherTypeExtremeRainfall,
    ///雨夹雪/阵雨夹雪/冻雨/雨雪天气
    JLWeatherTypeRainySnowy,
    ///雪
    JLWeatherTypeSnowy,
    ///阵雪
    JLWeatherTypeSnowShower,
    ///小雪/小雪-中雪
    JLWeatherTypeLightSnow,
    ///中雪/中雪-大雪
    JLWeatherTypeModerateSnow,
    ///大雪/大雪-暴雪
    JLWeatherTypeHeavySnow,
    ///暴雪
    JLWeatherTypeSnowstorm,
    ///浮尘
    JLWeatherTypeDust,
    ///扬沙
    JLWeatherTypeblowingSand,
    ///沙尘暴
    JLWeatherTypedustStorm,
    ///强沙尘暴
    JLWeatherTypeSevereSandstorm,
    ///龙卷风
    JLWeatherTypeTornado,
    ///雾/轻雾/浓雾/强浓雾/特强浓雾
    JLWeatherTypeFog,
    ///未知
    JLWeatherTypeUnknow,
    ///冷
    JLWeatherTypeCold,
    ///未知2
    JLWeatherTypeUnknown1,
    
};

typedef NS_ENUM(UInt8, JLWindDirectionType) {
    ///无风向
    JLWindDirectionTypeNone = 0x00,
    ///东
    JLWindDirectionTypeEast,
    ///南
    JLWindDirectionTypeSouth,
    ///西
    JLWindDirectionTypeWest,
    ///北
    JLWindDirectionTypeNorth,
    ///东南
    JLWindDirectionTypeEastSouth,
    ///东北
    JLWindDirectionTypeEastNorth,
    ///西北
    JLWindDirectionTypeWestNorth,
    ///西南
    JLWindDirectionTypeWestSouth,
    ///旋转不定
    JLWindDirectionTypeUnknow
};

@interface JL_MSG_Weather : NSObject

/// 省份
@property(nonatomic,strong)NSString *province;
///城市
@property(nonatomic,strong)NSString *city;
///天气编码
@property(nonatomic,assign)JLWeatherType code;
///温度
@property(nonatomic,assign)NSInteger temperature;
///湿度
@property(nonatomic,assign)NSInteger humidity;
///风向编码
@property(nonatomic,assign)JLWindDirectionType direction;
///风力
@property(nonatomic,assign)NSInteger wind;
/// 时间
@property(nonatomic,strong)NSDate *date;


-(NSData *)beData;

@end

NS_ASSUME_NONNULL_END
