//
//  TCSLicenseController.h
//  Winclone
//
//  Created by Tim Perfitt on 2/10/17.
//  Copyright © 2017 Twocanoes Software Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "TCSSelectEditionWincloneWindowController.h"
//#import "TCSActivateLicenseWindowController.h"

//#import "TCSLicenseProviderProtocol.h"

@interface TCSLicenseController  : NSObject
+(TCSLicenseController * _Nonnull)sharedLicenseController;
@property (nonatomic,assign) BOOL isTrial;
@property (assign) BOOL isActivating;
@property (strong,nullable) NSString *activateLicenseText;
@property (nonatomic,strong, nullable) NSString *licenseFileExtension;
@property (assign) NSInteger majorVersion;

NS_ASSUME_NONNULL_BEGIN


-(NSString * _Nonnull)activatedProduct;
-(BOOL)isActivated;
-(void)purchaseLicense:(NSString *)inProduct withCompletionBlock:(void (^)(NSDictionary *activatedProductInfo, NSError *err))purchaseCompletionBlock;

-(void)activateLicenseWithFile:(NSString *)filePath majorVersion:(NSInteger)majorVersion completitionBlock:(void (^)(NSError *err))completitionBlock;

-(void)activateLicenseWithKey:(NSString * _Nonnull)inKey email:(NSString * _Nonnull)inEmail withCompletionBlock:(nonnull void (^)(NSString *activatedProduct, NSError *err))completionBlock ;

-(NSString * _Nonnull)licenseEmail;
-(NSString * _Nonnull)licenseKey;
//-(NSString * _Nonnull)editionNameForVersionNumber:(NSString * _Nonnull)version;

-(void)deactivateLicenseWithCompletionBlock:(nonnull void (^)(NSError *err))completionBlock;
-(void)showRegistrationFeedback:(NSError *)err forEdition:(NSString *)editionName;
-(NSNumber *)daysRemainingOnTrialForProduct:(NSString *)inProduct;
-(BOOL)isTimeTrialForProduct:(NSString *)inProduct;
NS_ASSUME_NONNULL_END
@end
