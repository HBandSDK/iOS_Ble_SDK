//
//  VPCountDownSelectView.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/15.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPCountDownSelectView: UIView, UIPickerViewDelegate,UIPickerViewDataSource {

    var callBackBlock: ((Bool) -> Void)?
    
    var countDownModel: VPDeviceCountDownModel?
    
    let titleLabel: UILabel = UILabel()
    
    let selectPickerView:UIPickerView = UIPickerView()
    
    var a = 0
    
    var selectViewTitle: String? {
        willSet
        {
            
        }
        didSet {
            titleLabel.text = selectViewTitle
            //            selectPickerView.reloadAllComponents()
        }
    }
    
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
        titleLabel.text = "倒计时时长"
        seletctTopView.addSubview(titleLabel)
        
        selectPickerView.frame = CGRect(x: 0, y: seletctTopView.frame.size.height, width: selectMainView.frame.size.width, height: selectMainView.frame.size.height - seletctTopView.frame.size.height)
        selectPickerView.delegate = self
        selectPickerView.dataSource = self
        selectMainView.addSubview(selectPickerView)
    }
    
    @objc func cancelOrConfirmAction(sender: UIButton) {//取消或者确认操作
        if sender.tag == 1 {
            if selectViewTitle == "常驻倒计时时长" {
                countDownModel?.repeatTime = UInt(a)
                countDownModel?.settingOperation = 1
            }else {
                countDownModel?.repeatTime = UInt(a)
                countDownModel?.settingOperation = 2
            }
        }
        callBackBlock!(sender.tag == 1)
    }
    
    // MARK: - pickerView DataSorce和delegate
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return 3600
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
        label.text = String(row + 1)
        return label
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        a = row + 1
    }

}






