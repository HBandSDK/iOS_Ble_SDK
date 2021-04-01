//
//  VPEditNewAlarmController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/16.
//  Copyright © 2017年 zc.All rights reserved.
//

//写的有点啰嗦了,具体页面就不要看了，主要看功能实现的逻辑，星期一到星期日的weekBtn.tag一次为2^0至2^6，把所有选择的星期异或如选择了周一和周三就 2^0 | 2^2取得的值就是alarmModel.repeatState的值了，如果都没有选alarmModel.repeatState = 0，如果单次设置失败，可能是选择的日期比当前的日期早，场景图标demo中有两套，根据你们手环上的图标去对应选择，场景为0默认闹钟（这个是通用的），其他的依次顺序为1-20，不要混掉，手环端是根据这个一一对应的

import UIKit

class VPEditNewAlarmController: UIViewController,UIPickerViewDelegate,UIPickerViewDataSource,UITableViewDelegate,UITableViewDataSource {

    var callBackBlock: (() -> Void)?

    var isAdd: Bool = false //是添加闹钟还是边界

    var alarmModel: VPDeviceNewAlarmModel? {
        willSet {
            hour = Int((newValue?.alarmHour)!)!
            minute = Int((newValue?.alarmMinute)!)!
        }
    }

    @IBOutlet weak var timePickerView: UIPickerView!
    
    @IBOutlet weak var editTableView: UITableView!
    
    
    var hour = 0, minute = 0
    
    var showScene: Bool = true //是否显示或者隐藏场景
    
    let indexPathOneRow:CGFloat = 45.0, indexPathTwoRow:CGFloat = 80.0, IndexPathThreeTopHeight:CGFloat = 10.0
    
    let repeatWeekArray = ["周日","周六","周五","周四","周三","周二","周一"]
    let alarmLabelCount = 20 //闹钟场景标签除了默认其他的总数
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = isAdd ? "添加闹钟" : "编辑闹钟"
        timePickerView.selectRow(hour, inComponent: 0, animated: false)
        timePickerView.selectRow(minute, inComponent: 1, animated: false)
        self.setEditAlarmControllerUI()
    }
    
    let delectView = UIView()
    let alarmRepeatView = UIView(frame: CGRect(x: 0, y: 0, width: UIScreen.main.bounds.width, height: 150))
    let repeatTitleLabel:UILabel = UILabel(frame: CGRect(x: 20, y: 0, width: 150, height: 45))
    let repeatDetailLabel:UILabel = UILabel()
    let arrowImageView1 = UIImageView()
    
    let weekBtnView = UIView()
    var repeatWeekBtns = Array<UIButton>()
    let sceneTitleLabel: UILabel = UILabel()
    let sceneImageView: UIImageView = UIImageView()
    let arrowImageView2: UIImageView = UIImageView()
    
    
    let sceneView = UIView()
    var sceneBtns = Array<UIButton>()
    
    func setEditAlarmControllerUI() {
        editTableView.tableFooterView = UIView()
        
        delectView.frame = CGRect(x: 0, y: 0, width:Width, height: indexPathOneRow)
        let saveLabel: UILabel = UILabel(frame: delectView.bounds)
        saveLabel.font = UIFont.systemFont(ofSize: 17)
        saveLabel.textColor = #colorLiteral(red: 0.4666666687, green: 0.7647058964, blue: 0.2666666806, alpha: 1)
        saveLabel.textAlignment = .center
        saveLabel.text = "开始设置"
        delectView.addSubview(saveLabel)
        
        //indexPath.row == 0 的视图
        repeatTitleLabel.text = "重复"
        repeatTitleLabel.font = UIFont.boldSystemFont(ofSize: 18)
        repeatTitleLabel.textAlignment = .left
        repeatTitleLabel.textColor = #colorLiteral(red: 0.6, green: 0.6, blue: 0.6, alpha: 1)
        
        repeatDetailLabel.frame = CGRect(x: repeatTitleLabel.zc_right, y: 0, width: Width - repeatTitleLabel.zc_right - 30, height: repeatTitleLabel.zc_height)
        repeatDetailLabel.text = "周一"
        repeatDetailLabel.textColor = repeatTitleLabel.textColor
        repeatDetailLabel.font = UIFont.boldSystemFont(ofSize: 15)
        repeatDetailLabel.adjustsFontSizeToFitWidth = true
        repeatDetailLabel.textAlignment = .right
        
        arrowImageView1.frame = CGRect(x: self.repeatDetailLabel.zc_right + 5, y: self.repeatDetailLabel.center.y - 6, width: 8, height: 12)
        arrowImageView1.image = UIImage(named: "arrow")
        
        //indexPath.row == 1 的视图
        weekBtnView.frame = CGRect(x: 0, y: 0, width: Width, height: indexPathTwoRow)
        let weekString = alarmModel?.weekBinaryString()
        
        for i in (1...7).reversed() {
            let btnCount = 7
            let leftBorder:CGFloat = 10
            let btnWidth:CGFloat = (UIScreen.main.bounds.size.width - CGFloat(leftBorder*2))/CGFloat(btnCount) - CGFloat(10)
            let btnFrame = CGRect(x: leftBorder + (Width - leftBorder * CGFloat(2))/CGFloat(btnCount)*CGFloat((btnCount-i)) + CGFloat(5), y: (self.weekBtnView.zc_height - btnWidth)/CGFloat(2), width: btnWidth, height: btnWidth)
            let weekBtn = UIButton(type: .custom)
            weekBtn.frame = btnFrame
            weekBtn.setBackgroundImage(UIImage(named: "alarm_week_unclick"), for: .normal)
            weekBtn.setBackgroundImage(UIImage(named: "alarm_week"), for: .selected)
            weekBtn.addTarget(self, action: #selector(selectRepeatWeekAction(sender:)), for: .touchUpInside)
            weekBtn.layer.cornerRadius = btnWidth/2.0
            weekBtn.titleLabel?.font = UIFont.systemFont(ofSize: 13)
            weekBtn.setTitle(repeatWeekArray[i - 1], for: .normal)
            weekBtn.setTitleColor(UIColor.gray, for: .normal)
            weekBtn.setTitleColor(UIColor.white, for: .selected)
            weekBtn.tag = Int(pow(2.0, Double(btnCount - i)))
            weekBtnView.addSubview(weekBtn)
            repeatWeekBtns.append(weekBtn)
            
            let subIndex: String.Index = weekString!.index(weekString!.startIndex, offsetBy:i)
            let endIndex: String.Index = weekString!.index(after: subIndex)
            let subWeekString = weekString?.substring(with:subIndex..<endIndex)//截取某一个范围内的字符
            if subWeekString == "1" {
                weekBtn.isSelected = true
            }
            self.getAlarmRemindWeekOrDate()
        }
    
        //indexPath.row == 2 的视图
        sceneTitleLabel.frame = repeatTitleLabel.frame
        sceneTitleLabel.textColor = repeatTitleLabel.textColor
        sceneTitleLabel.text = "闹钟标签"
        sceneTitleLabel.font = UIFont.systemFont(ofSize: 18)
        sceneImageView.frame = CGRect(x: Width - 30 - 25, y: sceneTitleLabel.center.y - 12.5, width: 25, height: 25)
        sceneImageView.image = UIImage(named: "clockP-select")
        arrowImageView2.frame = CGRect(x: sceneImageView.zc_right + 5, y: sceneTitleLabel.center.y - 6, width: 8, height: 12)
        arrowImageView2.image = UIImage(named: "arrow")
        arrowImageView2.transform = CGAffineTransform(rotationAngle: 3.14 * 0.5)
        
        //indexPath.row == 3 的视图
        sceneView.frame = CGRect(x: 0, y: 0, width: Width, height: self.getAlarmSceneHeigth())
        
        for i in (0..<alarmLabelCount) {
            let btnCount = 9
            let j = i % btnCount
            let leftBorder:CGFloat = 10
            let btnWidth = (Width - leftBorder*CGFloat(2))/CGFloat(btnCount) - CGFloat(10)
            let topY:CGFloat = CGFloat(10) + (btnWidth + CGFloat(10))*CGFloat((i/btnCount))
            let btnFrame = CGRect(x: leftBorder + (Width - leftBorder * CGFloat(2))/CGFloat(btnCount)*CGFloat(j) + CGFloat(5), y: topY, width: btnWidth, height: btnWidth)
            let imageName: String = String(format: "alarmLabelJ%d", i + 1)
            let imageSelectName: String = imageName + "_select"
            let sceneBtn = UIButton(type: .custom)
            sceneBtn.frame = btnFrame
            sceneBtn.setImage(UIImage(named:imageName), for: .normal)
            sceneBtn.setImage(UIImage(named:imageSelectName), for: .selected)
            sceneBtn.addTarget(self, action: #selector(selectSceneAction(sender:)), for: .touchUpInside)
            sceneBtn.tag = i + 1
            if Int((alarmModel?.alarmScene)!) == sceneBtn.tag {
                sceneImageView.image = UIImage(named: imageSelectName)
                sceneBtn.isSelected = true
            }
            sceneBtns.append(sceneBtn)
            sceneView.addSubview(sceneBtn)
        }
    }
    
    @objc func selectRepeatWeekAction(sender: UIButton)  {//选择星期
        sender.isSelected = !sender.isSelected;
        print(sender.tag)
        var k = 0
        for  btn: UIButton in repeatWeekBtns {
            if btn.isSelected == true {
                k = k | btn.tag
            }
        }
        alarmModel?.repeatState = String(format: "%02d", k)
        self.getAlarmRemindWeekOrDate()
        let indexPath: IndexPath = IndexPath(row: 0, section: 0)
        editTableView.reloadRows(at: [indexPath], with: .none)
    }
    
    func getAlarmSceneHeigth() -> CGFloat {//得到场景模块的高度
        let leftBorder:CGFloat = 10;
        let btnWidth:CGFloat = (view.frame.size.width - leftBorder*2)/9 - 10
        let topY:CGFloat = (btnWidth + 10)*((CGFloat(alarmLabelCount))/9+1) + 10
        return topY
    }
    
    @objc func selectSceneAction(sender: UIButton) {//场景选择
        for sceneBtn:UIButton in sceneBtns {
            if sceneBtn.tag != sender.tag {
                sceneBtn.isSelected = false
            }
        }
        if sender.isSelected == true {
            alarmModel?.alarmScene = "0"
            sceneImageView.image = UIImage(named: "clockP-select")
        }else {
            alarmModel?.alarmScene = String(format:"%d", sender.tag)
            sceneImageView.image = UIImage(named: String(format:"alarmLabelJ%d_select", sender.tag))
        }
        sender.isSelected = !sender.isSelected;
    }
    
    // MARK: - pickerView DataSorce和delegate
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 2
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        if component == 0 {//（2001-2019）
            return 24
        }else{
            return 60
        }
    }
    
    func getAlarmRemindWeekOrDate()  {
        if  Int((alarmModel?.repeatState)!) != 0 {
            repeatDetailLabel.text = alarmModel?.getRepeatWeek()
            repeatTitleLabel.text = "重复"
            return ;
        }
        repeatTitleLabel.text = "提醒日期"
        if alarmModel?.alarmDate == "0000-00-00" || Int((alarmModel?.alarmState)!) == 0 {//如果没有日期或者已经提醒过
            repeatDetailLabel.text = alarmModel?.alarmDate
        }
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
        label.text = String(row)
        return label
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if component == 0 {
            hour = row
        }else {
            minute = row
        }
    }

    

    //MARK: tableView的代理
    func numberOfSections(in tableView: UITableView) -> Int {
        return 3
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section == 0 {
            return 2
        }else if section == 1 {
            if showScene == true {
                return 2
            }
            return 1
        }
        return 1
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = UITableViewCell()
        cell.selectionStyle = .none
        if indexPath.row == 0 && indexPath.section == 0 {//重复提醒
            cell.contentView.addSubview(repeatTitleLabel)
            cell.contentView.addSubview(repeatDetailLabel)
            
            if Int((alarmModel?.repeatState)!) == 0 {
                cell.contentView.addSubview(self.arrowImageView1)
                cell.selectionStyle = .default;
            }
        }else if indexPath.row == 1 && indexPath.section == 0 {
            cell.contentView.addSubview(weekBtnView)
        }else if indexPath.row == 0 && indexPath.section == 1 {
            cell.selectionStyle = .default;
            cell.contentView.addSubview(arrowImageView2)
            cell.contentView.addSubview(sceneTitleLabel)
            cell.contentView.addSubview(sceneImageView)
        }else if indexPath.row == 1 && indexPath.section == 1 {
            cell.contentView.addSubview(sceneView)
        }else if indexPath.row == 0 && indexPath.section == 2 {
            cell.contentView.addSubview(delectView)
            cell.selectionStyle = .default;
        }
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        if indexPath.row == 0 && indexPath.section == 0 {//选择日期,先给你写个随机的，大概意思就是这意思
            repeatDetailLabel.text = String(format: "%04d-%02d-%02d",2021,arc4random()%12 + 1 ,arc4random() % 31)
            alarmModel?.alarmDate = repeatDetailLabel.text
        }else if (indexPath.row == 0 && indexPath.section == 1) {
            showScene = !showScene
            unowned let weakSelf = self
            UIView.animate(withDuration: 0.3, animations: { 
                if weakSelf.showScene == true {
                    weakSelf.arrowImageView2.transform = CGAffineTransform(rotationAngle: 3.14 * 0.5)
                }else {
                    weakSelf.arrowImageView2.transform = CGAffineTransform(rotationAngle: 0)
                }
            }, completion: { (finished) in
                tableView.reloadData()
            })
        }else if (indexPath.row == 0 && indexPath.section == 2) {//修改闹钟
            guard let callBackBlock = callBackBlock else {
                return
            }
            
            alarmModel?.alarmHour = String(hour)
            alarmModel?.alarmMinute = String(minute)
            callBackBlock()
        }
    }
 
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if indexPath.section == 0 {
            if indexPath.row == 0 {
                return indexPathOneRow
            }else if indexPath.row == 1 {
                return indexPathTwoRow
            }
        }else if indexPath.section == 1 {
            if indexPath.row == 0 {
                return indexPathOneRow
            }else if indexPath.row == 1 {
                return self.getAlarmSceneHeigth()
            }
        }
        return indexPathOneRow;
    }

}
