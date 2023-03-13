#ifndef __BMP_CONVERT_H__
#define __BMP_CONVERT_H__

typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

#define LWORD(buf,pos)   *((u16*)&buf[pos])
#define LDWORD(buf,pos)  *((u32*)&buf[pos])
#define NULL ((void *)0)
#define __INT_MAX 2147483647
#define RGB565(r,g,b)   ((u16)(((u16)(r)<<8)&0xF800) | (((u16)(g)<<3) & 0x07E0) | ((u16)(b)>>3))
#define REPEAT_THRESHOLD 3

/*
 *输入：
 *    inbuf    : bmp图像raw数据(像素排列顺序 BGRA...BGRA, inbuf大小为inWidth*inHeight*4)
 *    inWidth  : bmp图像的宽度
 *    inHeight : bmp图像的高度
 *输出：
 *    outbuf   : 存放转换后的数据缓存，为NULL时计算需要的缓存大小
 *    outsize  : 数据缓存大小
 *返回值   ：
 *    转换后的数据大小
 */
int br23_bmp_to_res(u8 *inbuf, u32 inWidth, u32 inHeight, u8 *outbuf, u32 outsize);

/*
 * 输入：
 *     infile : bmp图像raw数据的文件路径(像素排列顺序 BGRA...BGRA, 文件大小为width*height*4)
 *     width  : bmp图像宽度
 *     height : bmp图像高度
 * 输出：
 *     outfile : 输出文件路径(转换后的文件)
 * 返回值：
 *     0 : 转换失败(输入的width, height与infile文件的大小不匹配)
 *     1 : 转换成功
 */
int br23_btm_to_res_path(char *infile, int width, int height, char *outfile);

/*
 *输入：
 *    inbuf    : bmp图像raw数据(像素排列顺序 BGRA...BGRA, inbuf大小为inWidth*inHeight*4)
 *    inWidth  : bmp图像的宽度
 *    inHeight : bmp图像的高度
 *输出：
 *    outbuf   : 存放转换后的数据缓存，为NULL时计算需要的缓存大小
 *    outsize  : 数据缓存大小
 *返回值   ：
 *    转换后的数据大小
 */
int br28_bmp_to_res(u8 *inbuf, u32 inWidth, u32 inHeight, u8 *outbuf, u32 outsize);

/*
 * 输入：
 *     infile : bmp图像raw数据的文件路径(像素排列顺序 BGRA...BGRA, 文件大小为width*height*4)
 *     width  : bmp图像宽度
 *     height : bmp图像高度
 * 输出：
 *     outfile : 输出文件路径(转换后的文件)
 * 返回值：
 *     0 : 转换失败(输入的width, height与infile文件的大小不匹配)
 *     1 : 转换成功
 */
int br28_btm_to_res_path(char *infile, int width, int height, char *outfile);

#endif
