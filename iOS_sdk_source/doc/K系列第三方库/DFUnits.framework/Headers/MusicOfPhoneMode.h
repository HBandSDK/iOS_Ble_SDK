//
//  MusicOfPhoneMode.h
//  AiRuiSheng
//
//  Created by DFung on 2017/2/22.
//  Copyright © 2017年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>

@interface MusicOfPhoneMode : NSObject

@property(nonatomic,assign) BOOL         isPlaying;
@property(nonatomic,assign) NSInteger    mIndex;
@property(nonatomic,strong) MPMediaItem  *mItem;
@property(nonatomic,strong) NSString     *mPath;
@property(nonatomic,strong) NSString     *mUrl;
@property(nonatomic,strong) NSString     *mImgUrl;
@property(nonatomic,strong) NSString     *mTitle;
@property(nonatomic,strong) NSString     *mArtist;
@property(nonatomic,strong) UIImage      *mImage;
@property(nonatomic,assign) uint32_t     mTime;
@property(nonatomic,strong) id           mMediaItem;

/**
 *  用途获取自定义大小的歌曲图片。（适用于iPod内的歌曲）
 *
 */
-(UIImage*)getImage:(CGSize)size;

@end
