//
//  VPECGMultiLeadChartReportView.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/11/4.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

let ECGPerCell:CGFloat = 3.2

let xOnePointWidth:CGFloat = 25 * ECGPerCell / 250

class VPECGMultiLeadChartReportBgGridView: UIView {
    
    private var gridLayers:[CAShapeLayer] = []
    
    public override init(frame: CGRect) {
        super.init(frame: frame)
        backgroundColor = .black
        self.setupGridLayers()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupGridLayers() {
        let height = frame.size.height
        let width = frame.size.width
        
        let centerY = height / 2.0
        
        let cellHeightCountHalf:Int = Int(height / ECGPerCell / 2)
        let cellWidthCount:Int = Int(width / ECGPerCell)
        
        for i in -cellHeightCountHalf..<cellHeightCountHalf {
            let y:CGFloat = ECGPerCell * CGFloat(i) + centerY
            if y > height {
                break
            }
            
            let start:CGPoint = .init(x: 0, y: y)
            let end:CGPoint = .init(x: width, y: y)
            
            let lineLayer:CAShapeLayer = CAShapeLayerWithStartPoint(start, end, i % 5 == 0)
            gridLayers.append(lineLayer)
            layer.addSublayer(lineLayer)
        }
        
        for i in 0..<cellWidthCount {
            let x:CGFloat = ECGPerCell * CGFloat(i)
            if x > width {
                break
            }
            
            let start:CGPoint = .init(x: x, y: 0)
            let end:CGPoint = .init(x: x, y: height)
            
            let lineLayer:CAShapeLayer = CAShapeLayerWithStartPoint(start, end, i % 5 == 0)
            gridLayers.append(lineLayer)
            layer.addSublayer(lineLayer)
        }
    }
    
    private func CAShapeLayerWithStartPoint(_ start:CGPoint, _ end:CGPoint, _ isBoldLine:Bool) -> CAShapeLayer {
        let path:UIBezierPath = .init()
        path.move(to: start)
        path.addLine(to: end)
        let lineLayer:CAShapeLayer = .init()
        lineLayer.path = path.cgPath
        if isBoldLine {
            lineLayer.strokeColor = UIColor.init(red: 1, green: 1, blue: 1, alpha: 0.2).cgColor
            lineLayer.lineWidth = 0.7
        } else {
            lineLayer.strokeColor = UIColor.init(red: 0x55/255.0, green: 0xbf/255.0, blue: 0x70/255.0, alpha: 0.2).cgColor
            lineLayer.lineWidth = 0.5
        }
        return lineLayer
    }
}

class VPECGMultiLeadChartReportLineView: UIView {
    
    private var bezierPath:UIBezierPath!
    
    public var dataArr:[NSNumber] = [] {
        didSet {
            self.setNeedsDisplay()
        }
    }
    
    public override init(frame: CGRect) {
        super.init(frame: frame)
        backgroundColor = UIColor.clear
    }
    
    override func draw(_ rect: CGRect) {
        bezierPath = .init()
        let oneMillivoltHeight:CGFloat = ECGPerCell * 10
        let startYPoint:CGFloat = frame.size.height * 1/2
        for i in 0..<dataArr.count {
            let yValue:CGFloat = startYPoint - dataArr[i].doubleValue * oneMillivoltHeight
            if i == 0 {
                bezierPath.move(to: CGPointMake(0, yValue))
            } else {
                bezierPath.addLine(to: CGPointMake(CGFloat(i) * xOnePointWidth, yValue))
            }
        }
        UIColor.green.setStroke()
        bezierPath.lineWidth = 1.5
        bezierPath.lineJoinStyle = .round
        bezierPath.lineCapStyle = .butt
        bezierPath.stroke()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class VPECGMultiLeadChartReportView: UIView {
    
    private var gridView:VPECGMultiLeadChartReportBgGridView!
    private var lineView:VPECGMultiLeadChartReportLineView!
    
    private var scrollView:UIScrollView!
    
    public var dataArr:[NSNumber] = [] {
        didSet {
            let width:CGFloat = CGFloat(dataArr.count) * xOnePointWidth + 20
            let size:CGSize = CGSizeMake(width, frame.height)
            scrollView.contentSize = size
            
            gridView = .init(frame: CGRect(origin: CGPoint.zero, size: size))
            scrollView.addSubview(gridView)
            
            lineView = .init(frame: CGRect(origin: CGPoint.zero, size: size))
            lineView.dataArr = dataArr
            scrollView.addSubview(lineView)
        }
    }
    
    public override init(frame: CGRect) {
        super.init(frame: frame)
        backgroundColor = .black
        setupSubviews()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    public func reset() {
        
    }
}

extension VPECGMultiLeadChartReportView {
    private func setupSubviews() {
        scrollView = .init(frame: CGRectMake(0, 0, frame.width, frame.height))
        addSubview(scrollView)
    }
}
