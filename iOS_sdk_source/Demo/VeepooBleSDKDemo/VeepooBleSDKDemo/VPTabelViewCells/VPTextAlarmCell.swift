//
//  VPTextAlarmCell.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/9/18.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPTextAlarmCell: UITableViewCell {

    var alarmModel:VPDeviceTextAlarmModel? {
        willSet {
            timeLabel.text = (newValue?.alarmHour)! + ":" + (newValue?.alarmMinute)! + " id:" + (newValue?.alarmID)!
            alarmText.text = newValue?.alarmText
            alarmSwitch.isOn = UInt((newValue?.alarmState)!) == 1
            
            if UInt((newValue?.repeatState)!) == 0 {//单次提醒
                alarmSwitch.isHidden = true
                repeatLabel.text = newValue?.alarmDate
            }else {
                alarmSwitch.isHidden = false
                repeatLabel.text = newValue?.getRepeatWeek()
            }
        }
    }
    
    @IBOutlet weak var timeLabel: UILabel!
    @IBOutlet weak var repeatLabel: UILabel!
    @IBOutlet weak var alarmSwitch: UISwitch!
    @IBOutlet weak var alarmText: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
}
