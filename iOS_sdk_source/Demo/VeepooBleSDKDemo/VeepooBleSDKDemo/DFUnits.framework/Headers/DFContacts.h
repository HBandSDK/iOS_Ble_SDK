//
//  DFContacts.h
//  DFUnits
//
//  Created by DFung on 2018/4/19.
//  Copyright © 2018年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
//#define JL_CONTACTS_ENABLE

#ifdef JL_CONTACTS_ENABLE
#import <Contacts/Contacts.h>

@interface DFContacts : NSObject
/**
 *  keys: @[CNContactPhoneNumbersKey,   手机号
 *          CNContactFamilyNameKey,     姓氏
 *          CNContactGivenNameKey       名字
 *          ...,nil ];  @see <Contacts/Contacts.h> 内有详情。
 *  选择需要的信息。
 *
 *  contacts：返回NSArray<CNContact>。
 *  flag：0=成功，-1=用户拒绝，-2=需在设置界面开启通讯录，-3=参数有误；
 */
+(void)scanContactsWithKeys:(NSArray*)keys
                     Result:(void(^)(NSArray*contacts,
                                     int flag))result;

/**
 *  简单解析 contacts
 *  {@"FamilyName":@"...",
 *   @"GivenName":@"...",
 *   @"Phones":@[@"iphone":@"110",@"home":@"456",...]}
 */
+(NSDictionary*)openContact:(CNContact*)contact;

@end
#endif
