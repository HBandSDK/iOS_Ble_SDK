//
//  VPContactCell.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/9/22.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPContactCell: UITableViewCell {
    
    var output: ((Bool) -> Void)?
    
    @IBOutlet weak var nickNameLabel: UILabel!
    @IBOutlet weak var phoneNumberLabel: UILabel!
    @IBOutlet weak var sosSwitch: UISwitch!
    @IBOutlet weak var sosLabel: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    @IBAction func valueDidChange(_ sender: UISwitch) {
        output?(sender.isOn)
    }
}
