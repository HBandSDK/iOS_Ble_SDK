//
//  StringExtension.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/18.
//  Copyright © 2017年 zc.All rights reserved.
//

import Foundation

let zv = UIScreen.main.bounds.size.width

extension Int {
    func getOneDayDateString() -> String {//通过数值得到于今天差距的日期字符串
        let todayDate = Date(timeIntervalSinceNow: 0)
        
        let currentCalendar = Calendar.current
        
        let date = currentCalendar.date(byAdding: .day, value: self, to: todayDate)
        
        let year = currentCalendar.component(.year, from: date!)
        
        let month = currentCalendar.component(.month, from: date!)
        
        let day = currentCalendar.component(.day, from: date!)
        
        return String(year) + "-" + String(format: "%02d", month) + "-" + String(format: "%02d", day)
    }
}
