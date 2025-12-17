//
//  LicenseDetails.h
//  ProductLicense
//
//  Created by Josh Wisenbaker on 1/20/18.
//  Copyright © 2018 Twocanoes Software, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "TCSLicense.h"

@interface TCSLicenseDetails : NSWindowController
@property (weak) IBOutlet NSButton *locateButton;
@property (weak) IBOutlet NSButton *licenseButton;
@property (strong) NSString *extension;
- (void)licenseDetails;
- (IBAction)buttonClick:(id)sender;
@end
