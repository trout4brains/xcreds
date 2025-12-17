//
//  TCSLicenseWindowController.h
//  TCSCertRequest
//
//  Created by Timothy Perfitt on 8/2/21.
//  Copyright © 2021 Twocanoes Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "TCSLicense.h"

@interface TCSLicenseWindowController : NSWindowController
+ (instancetype _Nonnull )sharedWindowController;
-(void)showLicense:(TCSLicense *_Nonnull)license;
@end
