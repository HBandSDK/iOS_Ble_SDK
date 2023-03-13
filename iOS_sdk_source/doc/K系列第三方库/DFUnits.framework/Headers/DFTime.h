//
//  DFTime.h
//  
//
//  Created by Mac on 15/12/10.
//
//

#import <Foundation/Foundation.h>

@interface DFTime : NSObject
/**
 返回时间戳（单位：秒）
*/
+(long)dateCurrent;

/**
 *  获取iPhone时间（数组形式）。
 *  @return @"2016" @"2" @"18" @"11" @"26" @"00"
 */
+(NSArray*)dateMembers;

/**
 *  获取iPhone时间（字符串形式）。
 *  @return @"20160218112600"
 */
+ (NSString*)dateString;

/**
 *  编辑日期时间
 */
+(NSDate*)makeDateYear:(int)y
                 Month:(int)mo
                   Day:(int)d
                  Hour:(int)h
                   Min:(int)m
                   Sec:(int)s;

/**
 *  将字符串日期分解时间成员，@"20160218112600" => @"2016" @"2" @"18" @"11" @"26" @"00"
 *  @param time     @"20160218112600"
 *  @return @"2016" @"2" @"18" @"11" @"26" @"00"
 */
+ (NSArray*)divideDateMembers:(NSString*)time;

/**
 *  时间值加“秒”值。
 *  @param   sec     秒数
 *  @param   date    @"20160218112600"
 */
+ (NSString*)addSec:(NSTimeInterval)sec OnDate:(NSString *)date;

/**
 *  求两个时间点差值。(timeA-timeB)
 *  @param   timeA    @"20160218112601"
 *  @param   timeB    @"20160218112600"
 */
+(NSTimeInterval)differenceOfDateA:(NSString*)timeA AndDateB:(NSString*)timeB;

/**
 *  求两个时间点差值。(dateA-dateB)
 *  @param   dateA
 *  @param   dateB
 */
+(NSTimeInterval)gapOfDateA:(NSDate*)dateA DateB:(NSDate*)dateB;


/**
 *  当前【天】
 */
+ (NSInteger)day:(NSDate *)date;

/**
 *  当前【月】
 */
+ (NSInteger)month:(NSDate *)date;

/**
 *  当前【年】
 */
+ (NSInteger)year:(NSDate *)date;

/**
 *  当前【星期】
 */
+ (NSInteger)weekday:(NSDate *)date;

/**
 *  这周是这个月的第几周？
 */
+ (NSInteger)firstWeekdayInThisMonth:(NSDate *)date;

/**
 *  获取当前月天数
 */
+ (NSInteger)totaldaysInMonth:(NSDate *)date;

/**
 *  上/下m个月后的时间。
 */
+ (NSDate *)changeMonth:(int)m onDate:(NSDate *)date;

/**
 *  上/下d个天后的时间。
 */
+ (NSDate *)changeDay:(int)d onDate:(NSDate *)date;

/**
 *  秒数换算
 *  输入 ：60秒      (uint32_t)
 *  返回 ：00:01:00 （NSString*）
 */
+(NSString*)stringFromSec:(uint32_t)sec;

@end
