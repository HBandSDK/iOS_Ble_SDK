//
//  VPFemaleSelectView.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/14.
//  Copyright © 2017年 zc.All rights reserved.
//

/*
此部门逻辑不是十分严谨，写这个demo主要是告诉使用SDK的开发者，如何调用接口及大体的使用逻辑，
1.女性项目一般分为4个生理期：经期、备孕期、预产期、宝妈期
2.在经期、备孕期、宝妈期手环都需要知道用户最后一次来月经的时间
3.一般经期的周期，即两次月经时间的间隔，不同人的体质不同因人而异默认一般28天
4.经期长度，即从来月经到月经消失要多少天，一般人是5-6天
5.如果App需要做此功能，建议参考美柚和大姨妈，及网络搜索各种参数，我们仅是提供开发接口，详细的还要开发者及其产品经理去定义

最后说一句，我这写的不好的不要吐槽，本身能让开发者看懂大概意思就可以了，我也是抽时间写demo的，哈哈此功能到此结束，休息一会
 */

import UIKit

class VPFemaleSelectView: UIView, UIPickerViewDelegate, UIPickerViewDataSource {

    var callBackBlock: ((Bool) -> Void)?

    var selectViewTitle: String? {
        willSet
        {
            
        }
        didSet {
            titleLabel.text = selectViewTitle
//            selectPickerView.reloadAllComponents()
        }
    }
    
    var femaleModel: VPDeviceFemaleModel?

    let titleLabel: UILabel = UILabel()

    let selectPickerView:UIPickerView = UIPickerView()
    
    let physiologicalArray = ["取消","月经期","备孕期","预产期","宝妈期"]
    let sexArray = ["男","女"]
    
    var a = 0,b = 0,c = 0
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        backgroundColor = UIColor(white: 0.8, alpha: 0.8)
        self.setSelectViewUI()
        
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func setSelectViewUI() {
        let selectMainView = UIView(frame: CGRect(x: 30, y: (self.frame.size.height - 300)/2, width: self.frame.size.width - 60, height: 300))
        selectMainView.backgroundColor = UIColor(white: 0.7, alpha: 0.8)
        self.addSubview(selectMainView)
        
        let seletctTopView = UIView(frame: CGRect(x: 0, y: 0, width: selectMainView.frame.width, height: 44))
        seletctTopView.backgroundColor = UIColor.brown
        selectMainView.addSubview(seletctTopView)
        
        let cancelBtn = UIButton(type: .custom)
        cancelBtn.frame = CGRect(x: 10, y: 0, width: 40, height: seletctTopView.frame.height)
        cancelBtn.tag = 0
        cancelBtn.setTitle("取消", for: .normal)
        cancelBtn.addTarget(self, action: #selector(cancelOrConfirmAction(sender:)), for: .touchUpInside)
        seletctTopView.addSubview(cancelBtn)
        
        let confirmBtn = UIButton(type: .custom)
        confirmBtn.frame = CGRect(x: seletctTopView.frame.width - 50, y: 0, width: 40, height: seletctTopView.frame.height)
        confirmBtn.tag = 1
        confirmBtn.setTitle("确定", for: .normal)
        confirmBtn.addTarget(self, action: #selector(cancelOrConfirmAction(sender:)), for: .touchUpInside)
        seletctTopView.addSubview(confirmBtn)
        
        titleLabel.frame = CGRect(x: 60, y: 0, width: seletctTopView.frame.size.width - 120, height: seletctTopView.frame.size.height)
        titleLabel.textAlignment = .center
        titleLabel.textColor = UIColor.white
        seletctTopView.addSubview(titleLabel)
        
        selectPickerView.frame = CGRect(x: 0, y: seletctTopView.frame.size.height, width: selectMainView.frame.size.width, height: selectMainView.frame.size.height - seletctTopView.frame.size.height)
        selectPickerView.delegate = self
        selectPickerView.dataSource = self
        selectMainView.addSubview(selectPickerView)
    }
    
    @objc func cancelOrConfirmAction(sender: UIButton) {
        if sender.tag == 1 {
            if selectViewTitle == "生理期选择" {
                femaleModel?.femaleState = VPDeviceFemaleState(rawValue: a)!
            }else if selectViewTitle == "最后经期日期" {
                femaleModel?.lastMenstrualDate = String(format: "%04d", a + 2001) + "-" + String(format: "%02d", b + 1) + "-" + String(format: "%02d", c + 1)
            }else if selectViewTitle == "经期周期" {
                femaleModel?.menstrualCircle = a + 7
            }else if selectViewTitle == "经期正常持续天数" {
                femaleModel?.menstrualDays = a + 1
            }else if selectViewTitle == "宝宝生日" {
                femaleModel?.babyBirthday = String(format: "%04d", a + 2001) + "-" + String(format: "%02d", b + 1) + "-" + String(format: "%02d", c + 1)
            }else if selectViewTitle == "宝宝性别" {
                femaleModel?.isGirl = a == 1
            }else {//预产期
                femaleModel?.expectedDateOfChildbirth = String(format: "%04d", a + 2001) + "-" + String(format: "%02d", b + 1) + "-" + String(format: "%02d", c + 1)
            }
        }
        
        callBackBlock!(sender.tag == 1)
    }
    
    // MARK: - pickerView DataSorce和delegate
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        if selectViewTitle == "生理期选择" {
            return 1
        }else if selectViewTitle == "最后经期日期" {
            return 3
        }else if selectViewTitle == "经期周期" {
            return 1
        }else if selectViewTitle == "经期正常持续天数" {
            return 1
        }else if selectViewTitle == "宝宝生日" {
            return 3
        }else if selectViewTitle == "宝宝性别" {
            return 1
        }else if selectViewTitle == "预产期"{//预产期
            return 3
        }
        return 0
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        if selectViewTitle == "生理期选择" {//四种生理期
            return 5
        }else if selectViewTitle == "最后经期日期" || selectViewTitle == "宝宝生日" || selectViewTitle == "预产期" {//这里没有对日期进行逻辑处理，就是简单的功能实现，如出现9月份有31日的，你们自己设置的时候注意一下就好，我累了，不想写
            if component == 0 {//（2001-2019）
                return 19
            }else if component == 1 {
                return 12
            }else {
                return 31
            }
        }else if selectViewTitle == "经期周期" {//两次经期的正常间隔（7-46）
            return 40
        }else if selectViewTitle == "经期正常持续天数" {//从来月经到走（1-15）
            return 15
        }else if selectViewTitle == "宝宝性别" {//男或者女
            return 2
        }
        return 3
    }
    
    func pickerView(_ pickerView: UIPickerView, viewForRow row: Int, forComponent component: Int, reusing view: UIView?) -> UIView {
        for subView in pickerView.subviews {
            if subView.frame.size.height < 1 {
                subView.backgroundColor = UIColor.brown
            }
        }
        let label = UILabel(frame: CGRect(x: 0, y: 0, width: pickerView.frame.size.width/3, height: 44))
        label.textColor = UIColor.brown
        label.textAlignment = .center
        if selectViewTitle == "生理期选择" {//四种生理期
            label.text = physiologicalArray[row]
        }else if selectViewTitle == "最后经期日期" || selectViewTitle == "宝宝生日" || selectViewTitle == "预产期" {//这里没有对日期进行逻辑处理，就是简单的功能实现，如出现9月份有31日的，你们自己设置的时候注意一下就好，我累了，不想写
            if component == 0 {//（2001-2017）
                label.text =  String(row+2001)
            }else if component == 1 {
                label.text =  String(row+1)
            }else {
                label.text =  String(row+1)
            }
        }else if selectViewTitle == "经期周期" {//两次经期的正常间隔（7-46）
            label.text =  String(row + 7)
        }else if selectViewTitle == "经期正常持续天数" {//从来月经到走（1-15）
            label.text =  String(row + 1)
        }else if selectViewTitle == "宝宝性别" {//男或者女
            label.text =  sexArray[row]
        }
        return label
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if component == 0 {
            a = row
        }else if component == 1 {
            b = row
        }else {
            c = row
        }
    }
    
}













