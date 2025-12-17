//
//  TCSLicenseCheck.h
//  ProductLicense
//
//  Created by Josh Wisenbaker on 1/21/18.
//  Copyright © 2018 Twocanoes Software, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TCSLicense.h"

typedef NS_ENUM(NSUInteger, TCSLicenseStatus) {
    valid,
    invalid,
    expired,
    trial,
    invalidID,
    unset
};

@interface TCSLicenseCheck: NSObject
@property TCSLicense * _Nonnull license;
- (TCSLicenseStatus)checkLicenseStatus:(NSString *_Nonnull)bundleID withExtension:(NSString *_Nonnull)inExtension;
- (nullable TCSLicense *)getLicenseFor:(NSString *_Nonnull)bundleID withExtension:(NSString *_Nonnull)inExtension;
- (nullable NSURL *)findAppSupport:(NSString *_Nonnull)bundleID ;
@end
