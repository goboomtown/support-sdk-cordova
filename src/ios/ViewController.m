//
//  ViewController.m
//  SupportSDK
//
//  Created by Larry Borsato on 2020-10-22.
//  Copyright © 2020 Boomtown. All rights reserved.
//

#import "ViewController.h"
// #import "SupportSDK.h"


// @interface ViewController ()
//
// @property   SupportSDK  *supportSDKPlugin;
//
// @end

@implementation ViewController

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
}


// - (void)registerPlugin:(CDVPlugin*)plugin withClassName:(NSString*)className
// {
//     [super registerPlugin:plugin withClassName:className];
//     if ( [plugin isKindOfClass:[SupportSDK class]] ) {
//         self.supportSDKPlugin = (SupportSDK *)plugin;
//     }
// }
//
// - (void)registerPlugin:(CDVPlugin*)plugin withPluginName:(NSString*)pluginName
// {
//     [super registerPlugin:plugin withPluginName:pluginName];
//     if ( [plugin isKindOfClass:[SupportSDK class]] ) {
//         self.supportSDKPlugin = (SupportSDK *)plugin;
//     }
// }

@end
