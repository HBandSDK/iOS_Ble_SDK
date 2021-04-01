//
//  VPPath.swift
//  VPH-3Production
//
//  Created by zhangchong on 2020/8/18.
//  Copyright © 2020 veepoo. All rights reserved.
//

import UIKit

class VPPath: NSObject {
    static let document = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true).first
    
    static func filePath(documentSubPath path: String) -> String {
        return document! + "/" + path
    }
    
    static func isDirectory(_ filePath: String) -> Bool {
        var directory = ObjCBool.init(false)
        FileManager.default.fileExists(atPath: filePath, isDirectory: &directory)
        return directory.boolValue
    }
    
}
