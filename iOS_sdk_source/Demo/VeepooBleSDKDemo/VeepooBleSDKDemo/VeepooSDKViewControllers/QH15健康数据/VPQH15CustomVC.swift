//
//  VPQX15CustomVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/5/28.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

// MARK: - 配置项模型
struct ConfigItem {
    let name: String
    let key: String
    let type: ItemType
    let minValue: UInt8?
    let maxValue: UInt8?
    let segmentTitles: [String]?
    
    enum ItemType {
        case slider
        case segment
    }
}

// MARK: - 主视图控制器
class VPQH15CustomVC: UIViewController {
    
    // MARK: - Properties
    private let tableView = UITableView(frame: .zero, style: .insetGrouped)
    private let healthData = VPQH15HealthDataModel()
    private var sections: [(title: String, items: [ConfigItem])] = []
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        setupSections()
        setupNavigationBar()
        setupSDKDelegate()
    }
    
    // MARK: - Setup
    private func setupUI() {
        title = "健康数据配置"
        view.backgroundColor = .systemBackground
        
        tableView.delegate = self
        tableView.dataSource = self
        tableView.register(SliderCell.self, forCellReuseIdentifier: "SliderCell")
        tableView.register(SegmentCell.self, forCellReuseIdentifier: "SegmentCell")
        
        view.addSubview(tableView)
        tableView.translatesAutoresizingMaskIntoConstraints = false
        
        NSLayoutConstraint.activate([
            tableView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            tableView.bottomAnchor.constraint(equalTo: view.bottomAnchor)
        ])
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15GetHealthDataTimestamp { time in
            print("时间戳\(time)")
        }
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15ReadStepData { step in
            guard let stepM = step else { return }
            print(stepM.readId, stepM.step, stepM.timestamp)
        }
    }
    
    private func setupSections() {
        sections = [
            (title: "年龄类参数 (0-120)", items: [
                ConfigItem(name: "BIOS年龄", key: "biosAge", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil),
                ConfigItem(name: "心脏年龄", key: "heartAge", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil),
                ConfigItem(name: "健身年龄", key: "fitnessAge", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil)
            ]),
            
            (title: "年龄状态 (1:↑ 2:→ 3:↓)", items: [
                ConfigItem(name: "BIOS年龄状态", key: "biosAgeStatus", type: .segment,
                          minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                ConfigItem(name: "心脏年龄状态", key: "heartAgeStatus", type: .segment,
                          minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                ConfigItem(name: "健身年龄状态", key: "fitnessAgeStatus", type: .segment,
                          minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"])
            ]),
            
            (title: "年龄变化值 (0-99)", items: [
                ConfigItem(name: "BIOS年龄变化", key: "biosAgeChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "心脏年龄变化", key: "heartAgeChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "健身年龄变化", key: "fitnessAgeChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil)
            ]),
            
            (title: "上月/去年单点数据(0-120)", items: [
                ConfigItem(name: "BIOS 年龄上月数据", key: "biosAgeLastMonth", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil),
                ConfigItem(name: "心脏年龄上月数据", key: "heartAgeLastMonth", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil),
                ConfigItem(name: "健身年龄上月数据", key: "fitnessAgeLastMonth", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil),
                ConfigItem(name: "BIOS 年龄去年数据", key: "biosAgeLastYear", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil),
                ConfigItem(name: "心脏年龄去年数据", key: "heartAgeLastYear", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil),
                ConfigItem(name: "健身年龄去年数据", key: "fitnessAgeLastYear", type: .slider,
                          minValue: 0, maxValue: 120, segmentTitles: nil)
            ]),
            (title: "上月/去年状态", items: [
                ConfigItem(name: "BIOS 年龄上月状态", key: "biosAgeLastMonthStatus", type: .segment,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "心脏年龄上月状态", key: "heartAgeLastMonthStatus", type: .segment,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "健身年龄上月状态", key: "fitnessAgeLastMonthStatus", type: .segment,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "BIOS 年龄去年状态", key: "biosAgeLastYearStatus", type: .segment,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "心脏年龄去年状态", key: "heartAgeLastYearStatus", type: .segment,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "健身年龄去年状态", key: "fitnessAgeLastYearStatus", type: .segment,
                          minValue: 0, maxValue: 99, segmentTitles: nil)
            ]),
            (title: "上月/去年变化值（0~99）", items: [
                ConfigItem(name: "BIOS 年龄上月变化值", key: "biosAgeLastMonthChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "心脏年龄上月变化值", key: "heartAgeLastMonthChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "健身年龄上月变化值", key: "fitnessAgeLastMonthChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "BIOS 年龄去年变化值", key: "biosAgeLastYearChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "心脏年龄去年变化值", key: "heartAgeLastYearChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil),
                ConfigItem(name: "健身年龄去年变化值", key: "fitnessAgeLastYearChange", type: .slider,
                          minValue: 0, maxValue: 99, segmentTitles: nil)
            ]),
            (title: "三大慢病风险 (0-100%)", items: [
                ConfigItem(name: "心血管风险", key: "cardiovascularRisk", type: .slider,
                          minValue: 0, maxValue: 100, segmentTitles: nil),
                ConfigItem(name: "痴呆风险", key: "dementiaRisk", type: .slider,
                          minValue: 0, maxValue: 100, segmentTitles: nil),
                ConfigItem(name: "糖尿病风险", key: "diabetesRisk", type: .slider,
                          minValue: 0, maxValue: 100, segmentTitles: nil)
            ]),
            
    
                    (title: "三大慢病风险状态 (1:↑ 2:→ 3:↓)", items: [
                        ConfigItem(name: "心血管风险状态", key: "cardiovascularRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "痴呆风险状态", key: "dementiaRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "糖尿病风险状态", key: "diabetesRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"])
                    ]),
                    

                    (title: "三大慢病风险变化值 (0-100)", items: [
                        ConfigItem(name: "心血管风险变化", key: "cardiovascularRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "痴呆风险变化", key: "dementiaRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "糖尿病风险变化", key: "diabetesRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    

                    (title: "心血管细化风险 (0-100%)", items: [
                        ConfigItem(name: "心脏病发作风险", key: "heartAttackRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "中风风险", key: "strokeRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "心力衰竭风险", key: "heartFailureRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    
                    (title: "心血管细化风险状态 (1:↑ 2:→ 3:↓)", items: [
                        ConfigItem(name: "心脏病发作风险状态", key: "heartAttackRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "中风风险状态", key: "strokeRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "心力衰竭风险状态", key: "heartFailureRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"])
                    ]),
                    
                    (title: "心血管细化风险变化值 (0-100)", items: [
                        ConfigItem(name: "心脏病发作风险变化", key: "heartAttackRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "中风风险变化", key: "strokeRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "心力衰竭风险变化", key: "heartFailureRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    
                    (title: "生活质量风险 (0-100%)", items: [
                        ConfigItem(name: "记忆力衰退风险", key: "memoryDeclineRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "跌倒与受伤风险", key: "fallInjuryRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "失去独立生活能力风险", key: "independentLivingRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    
                    (title: "生活质量风险状态 (1:↑ 2:→ 3:↓)", items: [
                        ConfigItem(name: "记忆力衰退风险状态", key: "memoryDeclineRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "跌倒与受伤风险状态", key: "fallInjuryRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "失去独立生活能力风险状态", key: "independentLivingRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"])
                    ]),
                    
                    (title: "生活质量风险变化值 (0-100)", items: [
                        ConfigItem(name: "记忆力衰退风险变化", key: "memoryDeclineRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "跌倒与受伤风险变化", key: "fallInjuryRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "失去独立生活能力风险变化", key: "independentLivingRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    
                    (title: "糖尿病并发症风险 (0-100%)", items: [
                        ConfigItem(name: "肾脏疾病风险", key: "kidneyDiseaseRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "神经损伤风险", key: "nerveDamageRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "视力丧失风险", key: "visionLossRisk", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    
                    (title: "糖尿病并发症风险状态 (1:↑ 2:→ 3:↓)", items: [
                        ConfigItem(name: "肾脏疾病风险状态", key: "kidneyDiseaseRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "神经损伤风险状态", key: "nerveDamageRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"]),
                        ConfigItem(name: "视力丧失风险状态", key: "visionLossRiskStatus", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: ["↑ 增加", "→ 稳定", "↓ 减少"])
                    ]),
                    
                    (title: "糖尿病并发症风险变化值 (0-100)", items: [
                        ConfigItem(name: "肾脏疾病风险变化", key: "kidneyDiseaseRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "神经损伤风险变化", key: "nerveDamageRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "视力丧失风险变化", key: "visionLossRiskChange", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    

                    (title: "健康指数 (0-100%)", items: [
                        ConfigItem(name: "营养状态", key: "nutritionStatus", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil),
                        ConfigItem(name: "目标状态", key: "goalStatus", type: .slider,
                                  minValue: 0, maxValue: 100, segmentTitles: nil)
                    ]),
                    
                    (title: "达标类型", items: [
                        ConfigItem(name: "达标类型", key: "achievementType", type: .segment,
                                  minValue: nil, maxValue: nil, segmentTitles: [
                                    "BIOS Age event",
                                    "Heart Age event",
                                    "Fitness Age event",
                                    "Steps goal event",
                                    "Nutrition goal event",
                                    "All goals achieved event",
                                    "New fitness goals event"
                                  ])
                    ])
        ]
    }
    
    private func setupNavigationBar() {
        let randomBtn = UIBarButtonItem(title: "随机", style: .plain, target: self, action: #selector(randomData))
        let sendBtn = UIBarButtonItem(title: "下发", style: .done, target: self, action: #selector(sendData))
        
        navigationItem.rightBarButtonItems = [sendBtn, randomBtn]
    }
    
    private func setupSDKDelegate() {
//        HealthDataSDK.shared().delegate = self
    }
    
    // MARK: - Actions
    @objc private func randomData() {
        healthData.generateRandomData()
        tableView.reloadData()
    }
    
    @objc private func clearData() {
        healthData.clearAllData()
        healthData.resetAllHasFlags()
        tableView.reloadData()
    }
    
    @objc private func sendData() {
        healthData.timestamp = UInt32(Date().timeIntervalSince1970)
        healthData.hasTimestamp = true
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SetHealthData(healthData) { success in
            print(success ? "发送成功" : "发送失败")
        }
    }
    
    // MARK: - Helper Methods
    private func getValue(forKey key: String) -> UInt8 {
        switch key {
        case "biosAge": return healthData.biosAge
        case "heartAge": return healthData.heartAge
        case "fitnessAge": return healthData.fitnessAge
        case "biosAgeStatus": return healthData.biosAgeStatus.rawValue
        case "heartAgeStatus": return healthData.heartAgeStatus.rawValue
        case "fitnessAgeStatus": return healthData.fitnessAgeStatus.rawValue
        case "biosAgeChange": return healthData.biosAgeChange
        case "heartAgeChange": return healthData.heartAgeChange
        case "fitnessAgeChange": return healthData.fitnessAgeChange
        case "cardiovascularRisk": return healthData.cardiovascularRisk
        case "dementiaRisk": return healthData.dementiaRisk
        case "diabetesRisk": return healthData.diabetesRisk
        case "nutritionStatus": return healthData.nutritionStatus
        case "goalStatus": return healthData.goalStatus
            
        case "biosAgeLastMonth": return healthData.biosAgeLastMonth
        case "heartAgeLastMonth": return healthData.heartAgeLastMonth
        case "fitnessAgeLastMonth": return healthData.fitnessAgeLastMonth
        case "biosAgeLastYear": return healthData.biosAgeLastYear
        case "heartAgeLastYear": return healthData.heartAgeLastYear
        case "fitnessAgeLastYear": return healthData.fitnessAgeLastYear
            
        case "biosAgeLastMonthStatus": return healthData.biosAgeLastMonthStatus.rawValue
        case "heartAgeLastMonthStatus": return healthData.heartAgeLastMonthStatus.rawValue
        case "fitnessAgeLastMonthStatus": return healthData.fitnessAgeLastMonthStatus.rawValue
        case "biosAgeLastYearStatus": return healthData.biosAgeLastYearStatus.rawValue
        case "heartAgeLastYearStatus": return healthData.heartAgeLastYearStatus.rawValue
        case "fitnessAgeLastYearStatus": return healthData.fitnessAgeLastYearStatus.rawValue
            
        case "biosAgeLastMonthChange": return healthData.biosAgeLastMonthChange
        case "heartAgeLastMonthChange": return healthData.heartAgeLastMonthChange
        case "fitnessAgeLastMonthChange": return healthData.fitnessAgeLastMonthChange
        case "biosAgeLastYearChange": return healthData.biosAgeLastYearChange
        case "heartAgeLastYearChange": return healthData.heartAgeLastYearChange
        case "fitnessAgeLastYearChange": return healthData.fitnessAgeLastYearChange
            
        // 三大慢病风险变化值
       case "cardiovascularRiskChange": return healthData.cardiovascularRiskChange
       case "dementiaRiskChange": return healthData.dementiaRiskChange
       case "diabetesRiskChange": return healthData.diabetesRiskChange
       
       // 心血管细化风险
       case "heartAttackRisk": return healthData.heartAttackRisk
       case "strokeRisk": return healthData.strokeRisk
       case "heartFailureRisk": return healthData.heartFailureRisk
       
       // 心血管细化风险状态
       case "heartAttackRiskStatus": return healthData.heartAttackRiskStatus.rawValue
       case "strokeRiskStatus": return healthData.strokeRiskStatus.rawValue
       case "heartFailureRiskStatus": return healthData.heartFailureRiskStatus.rawValue
       
       // 心血管细化风险变化值
       case "heartAttackRiskChange": return healthData.heartAttackRiskChange
       case "strokeRiskChange": return healthData.strokeRiskChange
       case "heartFailureRiskChange": return healthData.heartFailureRiskChange
       
       // 生活质量风险
       case "memoryDeclineRisk": return healthData.memoryDeclineRisk
       case "fallInjuryRisk": return healthData.fallInjuryRisk
       case "independentLivingRisk": return healthData.independentLivingRisk
       
       // 生活质量风险状态
       case "memoryDeclineRiskStatus": return healthData.memoryDeclineRiskStatus.rawValue
       case "fallInjuryRiskStatus": return healthData.fallInjuryRiskStatus.rawValue
       case "independentLivingRiskStatus": return healthData.independentLivingRiskStatus.rawValue
       
       // 生活质量风险变化值
       case "memoryDeclineRiskChange": return healthData.memoryDeclineRiskChange
       case "fallInjuryRiskChange": return healthData.fallInjuryRiskChange
       case "independentLivingRiskChange": return healthData.independentLivingRiskChange
       
       // 糖尿病并发症风险
       case "kidneyDiseaseRisk": return healthData.kidneyDiseaseRisk
       case "nerveDamageRisk": return healthData.nerveDamageRisk
       case "visionLossRisk": return healthData.visionLossRisk
       
       // 糖尿病并发症风险状态
       case "kidneyDiseaseRiskStatus": return healthData.kidneyDiseaseRiskStatus.rawValue
       case "nerveDamageRiskStatus": return healthData.nerveDamageRiskStatus.rawValue
       case "visionLossRiskStatus": return healthData.visionLossRiskStatus.rawValue
       
       // 糖尿病并发症风险变化值
       case "kidneyDiseaseRiskChange": return healthData.kidneyDiseaseRiskChange
       case "nerveDamageRiskChange": return healthData.nerveDamageRiskChange
       case "visionLossRiskChange": return healthData.visionLossRiskChange
            
        default: return 0
        }
    }
    
    private func setValue(_ value: UInt8, forKey key: String) {
        switch key {
        case "biosAge":
            healthData.biosAge = value
            healthData.hasBiosAge = true
        case "heartAge":
            healthData.heartAge = value
            healthData.hasHeartAge = true
        case "fitnessAge":
            healthData.fitnessAge = value
            healthData.hasFitnessAge = true
        case "biosAgeStatus":
            healthData.biosAgeStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasBiosAgeStatus = true
        case "heartAgeStatus":
            healthData.heartAgeStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasHeartAgeStatus = true
        case "fitnessAgeStatus":
            healthData.fitnessAgeStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasFitnessAgeStatus = true
        case "biosAgeChange":
            healthData.biosAgeChange = value
            healthData.hasBiosAgeChange = true
        case "heartAgeChange":
            healthData.heartAgeChange = value
            healthData.hasHeartAgeChange = true
        case "fitnessAgeChange":
            healthData.fitnessAgeChange = value
            healthData.hasFitnessAgeChange = true
        case "cardiovascularRisk":
            healthData.cardiovascularRisk = value
            healthData.hasCardiovascularRisk = true
        case "dementiaRisk":
            healthData.dementiaRisk = value
            healthData.hasDementiaRisk = true
        case "diabetesRisk":
            healthData.diabetesRisk = value
            healthData.hasDiabetesRisk = true
        case "nutritionStatus":
            healthData.nutritionStatus = value
            healthData.hasNutritionStatus = true
        case "goalStatus":
            healthData.goalStatus = value
            healthData.hasGoalStatus = true
        case "biosAgeLastMonth":
            healthData.hasBiosAgeLastMonth = true
            healthData.biosAgeLastMonth = value
        case "heartAgeLastMonth":
            healthData.hasHeartAgeLastMonth = true
            healthData.heartAgeLastMonth = value
        case "fitnessAgeLastMonth":
            healthData.hasFitnessAgeLastMonth = true
            healthData.fitnessAgeLastMonth = value
        case "biosAgeLastYear":
            healthData.hasBiosAgeLastYear = true
            healthData.biosAgeLastYear = value
        case "heartAgeLastYear":
            healthData.hasHeartAgeLastYear = true
            healthData.heartAgeLastYear = value
        case "fitnessAgeLastYear":
            healthData.hasFitnessAgeLastYear = true
            healthData.fitnessAgeLastYear = value
        case "biosAgeLastMonthStatus":
            healthData.hasBiosAgeLastMonthStatus = true
            healthData.biosAgeLastMonthStatus = AgeStatusType(rawValue: value) ?? .stable
        case "heartAgeLastMonthStatus":
            healthData.hasHeartAgeLastMonthStatus = true
            healthData.heartAgeLastMonthStatus = AgeStatusType(rawValue: value) ?? .stable
        case "fitnessAgeLastMonthStatus":
            healthData.hasFitnessAgeLastMonthStatus = true
            healthData.fitnessAgeLastMonthStatus = AgeStatusType(rawValue: value) ?? .stable
        case "biosAgeLastYearStatus":
            healthData.hasBiosAgeLastYearStatus = true
            healthData.biosAgeLastYearStatus = AgeStatusType(rawValue: value) ?? .stable
        case "heartAgeLastYearStatus":
            healthData.hasHeartAgeLastYearStatus = true
            healthData.heartAgeLastYearStatus = AgeStatusType(rawValue: value) ?? .stable
        case "fitnessAgeLastYearStatus":
            healthData.hasFitnessAgeLastYearStatus = true
            healthData.fitnessAgeLastYearStatus = AgeStatusType(rawValue: value) ?? .stable
        case "biosAgeLastMonthChange":
            healthData.hasBiosAgeLastMonthChange = true
            healthData.biosAgeLastMonthChange = value
        case "heartAgeLastMonthChange":
            healthData.hasHeartAgeLastMonthChange = true
            healthData.heartAgeLastMonthChange = value
        case "fitnessAgeLastMonthChange":
            healthData.hasFitnessAgeLastMonthChange = true
            healthData.fitnessAgeLastMonthChange = value
        case "biosAgeLastYearChange":
            healthData.hasBiosAgeLastYearChange = true
            healthData.biosAgeLastYearChange = value
        case "heartAgeLastYearChange":
            healthData.hasHeartAgeLastYearChange = true
            healthData.heartAgeLastYearChange = value
        case "fitnessAgeLastYearChange":
            healthData.hasFitnessAgeLastYearChange = true
            healthData.fitnessAgeLastYearChange = value
            // 三大慢病风险状态
        case "cardiovascularRiskStatus":
            healthData.cardiovascularRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasCardiovascularRiskStatus = true
        case "dementiaRiskStatus":
            healthData.dementiaRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasDementiaRiskStatus = true
        case "diabetesRiskStatus":
            healthData.diabetesRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasDiabetesRiskStatus = true
        
        // 三大慢病风险变化值
        case "cardiovascularRiskChange":
            healthData.cardiovascularRiskChange = value
            healthData.hasCardiovascularRiskChange = true
        case "dementiaRiskChange":
            healthData.dementiaRiskChange = value
            healthData.hasDementiaRiskChange = true
        case "diabetesRiskChange":
            healthData.diabetesRiskChange = value
            healthData.hasDiabetesRiskChange = true
        
        // 心血管细化风险
        case "heartAttackRisk":
            healthData.heartAttackRisk = value
            healthData.hasHeartAttackRisk = true
        case "strokeRisk":
            healthData.strokeRisk = value
            healthData.hasStrokeRisk = true
        case "heartFailureRisk":
            healthData.heartFailureRisk = value
            healthData.hasHeartFailureRisk = true
        
        // 心血管细化风险状态
        case "heartAttackRiskStatus":
            healthData.heartAttackRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasHeartAttackRiskStatus = true
        case "strokeRiskStatus":
            healthData.strokeRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasStrokeRiskStatus = true
        case "heartFailureRiskStatus":
            healthData.heartFailureRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasHeartFailureRiskStatus = true
        
        // 心血管细化风险变化值
        case "heartAttackRiskChange":
            healthData.heartAttackRiskChange = value
            healthData.hasHeartAttackRiskChange = true
        case "strokeRiskChange":
            healthData.strokeRiskChange = value
            healthData.hasStrokeRiskChange = true
        case "heartFailureRiskChange":
            healthData.heartFailureRiskChange = value
            healthData.hasHeartFailureRiskChange = true
        
        // 生活质量风险
        case "memoryDeclineRisk":
            healthData.memoryDeclineRisk = value
            healthData.hasMemoryDeclineRisk = true
        case "fallInjuryRisk":
            healthData.fallInjuryRisk = value
            healthData.hasFallInjuryRisk = true
        case "independentLivingRisk":
            healthData.independentLivingRisk = value
            healthData.hasIndependentLivingRisk = true
        
        // 生活质量风险状态
        case "memoryDeclineRiskStatus":
            healthData.memoryDeclineRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasMemoryDeclineRiskStatus = true
        case "fallInjuryRiskStatus":
            healthData.fallInjuryRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasFallInjuryRiskStatus = true
        case "independentLivingRiskStatus":
            healthData.independentLivingRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasIndependentLivingRiskStatus = true
        
        // 生活质量风险变化值
        case "memoryDeclineRiskChange":
            healthData.memoryDeclineRiskChange = value
            healthData.hasMemoryDeclineRiskChange = true
        case "fallInjuryRiskChange":
            healthData.fallInjuryRiskChange = value
            healthData.hasFallInjuryRiskChange = true
        case "independentLivingRiskChange":
            healthData.independentLivingRiskChange = value
            healthData.hasIndependentLivingRiskChange = true
        
        // 糖尿病并发症风险
        case "kidneyDiseaseRisk":
            healthData.kidneyDiseaseRisk = value
            healthData.hasKidneyDiseaseRisk = true
        case "nerveDamageRisk":
            healthData.nerveDamageRisk = value
            healthData.hasNerveDamageRisk = true
        case "visionLossRisk":
            healthData.visionLossRisk = value
            healthData.hasVisionLossRisk = true
        
        // 糖尿病并发症风险状态
        case "kidneyDiseaseRiskStatus":
            healthData.kidneyDiseaseRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasKidneyDiseaseRiskStatus = true
        case "nerveDamageRiskStatus":
            healthData.nerveDamageRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasNerveDamageRiskStatus = true
        case "visionLossRiskStatus":
            healthData.visionLossRiskStatus = AgeStatusType(rawValue: value) ?? .stable
            healthData.hasVisionLossRiskStatus = true
        
        // 糖尿病并发症风险变化值
        case "kidneyDiseaseRiskChange":
            healthData.kidneyDiseaseRiskChange = value
            healthData.hasKidneyDiseaseRiskChange = true
        case "nerveDamageRiskChange":
            healthData.nerveDamageRiskChange = value
            healthData.hasNerveDamageRiskChange = true
        case "visionLossRiskChange":
            healthData.visionLossRiskChange = value
            healthData.hasVisionLossRiskChange = true
        case "achievementType":
            let achievementType = AchievementType(rawValue: value - 1) ?? .biosAgeEvent
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SetComplianceEvent(achievementType) { success in
                print(success ? "发送成功" : "发送失败")
            }
        default: break
        }
    }
}

// MARK: - UITableViewDelegate & DataSource
extension VPQH15CustomVC: UITableViewDelegate, UITableViewDataSource {
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return sections.count
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return sections[section].title
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return sections[section].items.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let item = sections[indexPath.section].items[indexPath.row]
        let value = getValue(forKey: item.key)
        
        switch item.type {
        case .slider:
            let cell = tableView.dequeueReusableCell(withIdentifier: "SliderCell", for: indexPath) as! SliderCell
            cell.configure(
                title: item.name,
                value: value,
                minValue: item.minValue ?? 0,
                maxValue: item.maxValue ?? 100
            ) { [weak self] newValue in
                self?.setValue(newValue, forKey: item.key)
            }
            return cell
            
        case .segment:
            let cell = tableView.dequeueReusableCell(withIdentifier: "SegmentCell", for: indexPath) as! SegmentCell
            cell.configure(
                title: item.name,
                value: value,
                titles: item.segmentTitles ?? ["↑", "→", "↓"]
            ) { [weak self] newValue in
                self?.setValue(newValue, forKey: item.key)
            }
            return cell
        }
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 50
    }
}

// MARK: - Slider Cell
class SliderCell: UITableViewCell {
    
    private let titleLabel = UILabel()
    private let slider = UISlider()
    private let valueLabel = UILabel()
    private var valueChangeBlock: ((UInt8) -> Void)?
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        setupUI()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupUI() {
        selectionStyle = .none
        
        titleLabel.font = .systemFont(ofSize: 16)
        
        valueLabel.font = .monospacedSystemFont(ofSize: 14, weight: .medium)
        valueLabel.textColor = .systemBlue
        valueLabel.textAlignment = .right
        
        slider.addTarget(self, action: #selector(sliderValueChanged), for: .valueChanged)
        
        let stackView = UIStackView(arrangedSubviews: [titleLabel, slider, valueLabel])
        stackView.axis = .horizontal
        stackView.spacing = 12
        stackView.alignment = .center
        stackView.translatesAutoresizingMaskIntoConstraints = false
        
        contentView.addSubview(stackView)
        
        NSLayoutConstraint.activate([
            stackView.topAnchor.constraint(equalTo: contentView.topAnchor, constant: 8),
            stackView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            stackView.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -16),
            stackView.bottomAnchor.constraint(equalTo: contentView.bottomAnchor, constant: -8),
            slider.widthAnchor.constraint(equalToConstant: 160)
        ])
    }
    
    func configure(title: String, value: UInt8, minValue: UInt8, maxValue: UInt8, onChange: @escaping (UInt8) -> Void) {
        titleLabel.text = title
        slider.minimumValue = Float(minValue)
        slider.maximumValue = Float(maxValue)
        slider.value = Float(value)
        valueLabel.text = "\(value)"
        valueChangeBlock = onChange
    }
    
    @objc private func sliderValueChanged() {
        let value = UInt8(slider.value)
        valueLabel.text = "\(value)"
        valueChangeBlock?(value)
    }
}

// MARK: - Segment Cell
class SegmentCell: UITableViewCell {
    
    private let titleLabel = UILabel()
    private let segmentedControl = UISegmentedControl()
    private var valueChangeBlock: ((UInt8) -> Void)?
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        setupUI()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupUI() {
        selectionStyle = .none
        
        titleLabel.font = .systemFont(ofSize: 16)
        
        segmentedControl.addTarget(self, action: #selector(segmentChanged), for: .valueChanged)
        
        let stackView = UIStackView(arrangedSubviews: [titleLabel, segmentedControl])
        stackView.axis = .horizontal
        stackView.spacing = 12
        stackView.alignment = .center
        stackView.translatesAutoresizingMaskIntoConstraints = false
        
        contentView.addSubview(stackView)
        
        NSLayoutConstraint.activate([
            stackView.topAnchor.constraint(equalTo: contentView.topAnchor, constant: 8),
            stackView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            stackView.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -16),
            stackView.bottomAnchor.constraint(equalTo: contentView.bottomAnchor, constant: -8)
        ])
    }
    
    func configure(title: String, value: UInt8, titles: [String], onChange: @escaping (UInt8) -> Void) {
        titleLabel.text = title
        
        segmentedControl.removeAllSegments()
        for (index, title) in titles.enumerated() {
            segmentedControl.insertSegment(withTitle: title, at: index, animated: false)
        }
        segmentedControl.selectedSegmentIndex = Int(value) - 1
        valueChangeBlock = onChange
    }
    
    @objc private func segmentChanged() {
        let value = UInt8(segmentedControl.selectedSegmentIndex + 1)
        valueChangeBlock?(value)
    }
}
