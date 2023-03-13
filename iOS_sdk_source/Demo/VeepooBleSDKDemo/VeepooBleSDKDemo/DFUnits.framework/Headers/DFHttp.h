//
//  DFHttp.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>


@class DFHttp;

@protocol DFHttpDelegate <NSObject>
@optional

-(void)http:(DFHttp*)http didFail:(NSError*)error;
-(void)http:(DFHttp*)http didSuccess:(NSString*)path;
-(void)http:(DFHttp*)http progress:(float)rate;

@end


@interface DFHttp : NSObject
@property(assign,nonatomic)int tag;
@property(assign,nonatomic)id <DFHttpDelegate>delegate;


/*
 *  Set info[@"URL"];
 *      info[@"PATH"];
 */
-(void)down:(NSDictionary*)info;


/*
        Returns a new string made from the receiver by replacing
    all characters not in the allowedCharacters set with percent
    encoded characters. UTF-8 encoding is used to determine the
    correct percent encoded characters. Entire URL strings cannot
    be percent-encoded. This method is intended to percent-encode
    an URL component or subcomponent string, NOT the entire URL
    string. Any characters in allowedCharacters outside of the
    7-bit ASCII range are ignored.
 */
+(NSString*)encodeURL:(NSString*)url;

/*
        Returns a new string made from the receiver by replacing
    all percent encoded sequences with the matching UTF-8 characters.
 */
+(NSString*)decodeURL:(NSString*)url;

/**
 *  异步请求（GET）
 */
+(void)getWithUrl:(NSString*)url
           Result:(void(^)(id ret, NSURLResponse *rps))block;

/**
 *  异步请求（POST）
 */
+(void)postWithUrl:(NSString*)url
              Body:(NSString*)body
             Result:(void(^)(id ret, NSURLResponse *rps))block;




@end
