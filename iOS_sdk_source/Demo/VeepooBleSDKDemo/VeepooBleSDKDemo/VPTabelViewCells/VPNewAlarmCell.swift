//
//  VPNewAlarmCell.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/16.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPNewAlarmCell: UITableViewCell {
    
    var alarmModel:VPDeviceNewAlarmModel? {
        willSet {
            timeLabel.text = (newValue?.alarmHour)! + ":" + (newValue?.alarmMinute)!
            alarmSwitch.isOn = UInt((newValue?.alarmState)!) == 1
            
            if UInt((newValue?.repeatState)!) == 0 {//单次提醒
                alarmSwitch.isHidden = true
                repeatLabel.text = newValue?.alarmDate
            }else {
                alarmSwitch.isHidden = false
                repeatLabel.text = newValue?.getRepeatWeek()
            }
            if Int((newValue?.alarmScene)!)! == 0 {
                alarmImageView.image = UIImage(named: "clockP-select")
                return
            }
            //下边的代码自己优化吧，我主要是实现一个方式，手环上的场景标签和App端是一一对应的，根据这里边的切图，你们可以自己重新设计尺寸和颜色等
            var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
            VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
            if (tbyte[17] == 1) {//对应不同的UI，现在只有两种
                let imageName = String(format: "alarmLabelJ%d_select", Int((newValue?.alarmScene)!)!)
                alarmImageView.image = UIImage(named: imageName)
            }else if (tbyte[17] == 2) {
                let imageName = String(format: "alarmLabelP%d_select", Int((newValue?.alarmScene)!)!)
                alarmImageView.image = UIImage(named: imageName)
            }else {
                let imageName = String(format: "alarmLabelP%d_select", Int((newValue?.alarmScene)!)!)
                alarmImageView.image = UIImage(named: imageName)
            }
        }
    }

    @IBOutlet weak var timeLabel: UILabel!
    
    @IBOutlet weak var repeatLabel: UILabel!

    @IBOutlet weak var alarmSwitch: UISwitch!

    @IBOutlet weak var alarmImageView: UIImageView!

    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
}
