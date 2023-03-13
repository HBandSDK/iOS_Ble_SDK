//
//  DFSort.h
//  DFUnits
//
//  Created by DFung on 16/1/29.
//  Copyright © 2016年 DFung. All rights reserved.
//


#import <Foundation/Foundation.h>
#include <stdio.h>





@interface DFSort : NSObject

void DescendingSort(int* arr,int left, int right);
void AscendingSort(int* arr,int left, int right);


/**
 *  打乱数组顺序。
 *  @param   array
 */
+(NSArray*)arrayRandom:(NSArray*)array;


@end


