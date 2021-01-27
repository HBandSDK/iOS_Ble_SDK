//
//  ZCUIView+setRect.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/22.
//  Copyright © 2017年 zc.All rights reserved.
//

import Foundation

let Width = UIScreen.main.bounds.size.width
let Height = UIScreen.main.bounds.size.height

extension UIView {
    
    var zc_width: CGFloat {
        get {
            return self.frame.size.width
        }
        set {
            var viewFrame = self.frame
            viewFrame.size.width = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_height: CGFloat {
        get {
            return self.frame.size.height
        }
        set {
            var viewFrame = self.frame
            viewFrame.size.height = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_x: CGFloat {
        get {
            return self.frame.origin.x
        }
        set {
            var viewFrame = self.frame
            viewFrame.origin.x = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_y: CGFloat {
        get {
            return self.frame.origin.y
        }
        set {
            var viewFrame = self.frame
            viewFrame.origin.y = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_origin: CGPoint {
        get {
            return self.frame.origin
        }
        set {
            var viewFrame = self.frame
            viewFrame.origin = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_size: CGSize {
        get {
            return self.frame.size
        }
        set {
            var viewFrame = self.frame
            viewFrame.size = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_left: CGFloat {
        get {
            return self.frame.origin.x
        }
        set {
            var viewFrame = self.frame
            viewFrame.origin.x = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_right: CGFloat {
        get {
            return self.frame.origin.x + self.frame.size.width
        }
        set {
            var viewFrame = self.frame
            viewFrame.origin.x = newValue - self.frame.size.width
            self.frame = viewFrame
        }
    }
    
    var zc_top: CGFloat {
        get {
            return self.frame.origin.y
        }
        set {
            var viewFrame = self.frame
            viewFrame.origin.y = newValue
            self.frame = viewFrame
        }
    }
    
    var zc_bottom: CGFloat {
        get {
            return self.frame.origin.y + self.frame.size.height
        }
        set {
            var viewFrame = self.frame
            viewFrame.origin.y = newValue - self.frame.size.height
            self.frame = viewFrame
        }
    }
    
    var zc_centerX: CGFloat {
        get {
            return self.center.x
        }
        set {
            self.center = CGPoint(x:newValue,y:self.center.y)
        }
    }
    
    var zc_centerY: CGFloat {
        get {
            return self.center.y
        }
        set {
            self.center = CGPoint(x:self.center.x,y:newValue)
        }
    }
    
}
