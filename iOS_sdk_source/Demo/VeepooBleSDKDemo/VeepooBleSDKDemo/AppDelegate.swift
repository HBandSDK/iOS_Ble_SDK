//
//  AppDelegate.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/14.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    static let hud = MBProgressHUD()
    static let hud1 = MBProgressHUD()
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        window = UIWindow.init(frame: UIScreen.main.bounds)
        
        let mainNavi = VPBaseNavigationController(rootViewController: VPRootViewController())
        window?.rootViewController = mainNavi;
        
        window?.makeKeyAndVisible()
        //先初始化VPBleCentralManage，也可以在主控制器中初始化，总之就是在使用蓝牙功能前初始化
//        let veepooBleManager: VPBleCentralManage = VPBleCentralManage.sharedBleManager()
        
        let centralManagerIdentifiers = launchOptions?[UIApplicationLaunchOptionsKey.bluetoothCentrals]
        print(centralManagerIdentifiers ?? [])
        
//        VPDFUOperation().veepooSDKStartDfu(withFilePath: VPPath.filePath(documentSubPath: "VeepooBleSDKframework.zip")) { (progress, state) in
//            
//        }
        
        return true
    }

    class func shareDelegate() -> AppDelegate {
        return UIApplication.shared.delegate as! AppDelegate
    }
    
    class func showHUD(message: String, hudModel: MBProgressHUDMode, showView: UIView) -> MBProgressHUD {
        
        hud.labelText = message
        hud.mode = hudModel
        
        hud.hide(true, afterDelay: 1.0)
        hud.show(true)
        showView.addSubview(hud)
        return hud
    }
    
    class func showHUDNoHide(message: String, hudModel: MBProgressHUDMode, showView: UIView) -> MBProgressHUD {
        hud1.labelText = message
        hud1.mode = hudModel
        
        showView.addSubview(hud1)
        return hud1
    }
    
    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}

