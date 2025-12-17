//
//  TCSLicense.h
//  Boot Runner
//
//  Created by Tim Perfitt on 10/18/17.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString * const TCSLicenseDateIssuedKey;
extern NSString * const TCSDateExpiredKey;
extern NSString * const TCSEditionKey;
extern NSString * const TCSEmailKey;
extern NSString * const TCSLicenseKeyKey;
extern NSString * const TCSMajorVersionKey;
extern NSString * const TCSNameKey;
extern NSString * const TCSNumberOfClientsKey;
extern NSString * const TCSProductKey;
extern NSString * const TCSSignatureKey;
extern NSString * const TCSMACAddressKey;

/**
 An object interface to a signed license in property list format. Based on AquaticPrime
 code. TCSLicense provided properties to access elements. It also provided methods
 to validate the signature based on the contained data.
 */

@interface TCSLicense : NSObject <NSCoding>

@property (readonly, nullable) NSString *dateIssued;
@property (readonly, nullable) NSString *dateExpired;
@property (readonly, nullable) NSString *edition;
@property (readonly, nullable) NSString *email;
@property (readonly, nullable) NSString *licenseKey;
@property (readonly) NSInteger majorVersion;
@property (readonly, nullable) NSString *name;
@property (readonly) NSInteger numberOfClients;
@property (readonly, nullable) NSString *product;
@property (readonly, nullable) NSData *signature;
@property (readonly, nullable) NSString *macAddress;

// Computed properties
/** Uses the publicKey to validate the signature. All properties that are part
 of the signature must be set. */
@property (readonly) BOOL isSignatureValid;

/// All properties assembled into a dictionary.
@property (readonly) NSDictionary *propertyListObject;

/// The propertyListObject serialized into an XML Plist object
@property (readonly) NSData *propertyListData;

/** Represents the data that was presented for the signature stored in the
signature property. */
@property (readonly) NSData *signedData;

/** Designated initializer These properties map to the keys defined in the dictionary
 retrieved from the plist.

 Note that the dates are expressed as a string and not an NSDate. This is
 also reflected in the plist.
 */
- (instancetype)initWithDateIssued:(NSString * _Nullable)dateIssued
                       dateExpired:(NSString * _Nullable)dateExpired
                           edition:(NSString * _Nullable)edition
                             email:(NSString * _Nullable)email
                        licenseKey:(NSString * _Nullable)licenseKey
                      majorVersion:(NSInteger)majorVersion
                              name:(NSString * _Nullable)name
                   numberOfClients:(NSInteger)numberOfClients
                           product:(NSString * _Nullable)product
                         signature:(NSData * _Nullable)signature
                        macAddress:(NSString * _Nullable)macAddress NS_DESIGNATED_INITIALIZER;

/**
 Convenience initializer.

 This initializer unarchived the data into an NSDictionary using NSPropertyListSerialization.
 Then it sets the object properties from the values in the dictionary.

 @param data Data that is ready to be unarchived using NSPropertyListSerialization.
 */
- (instancetype _Nullable)initWithPropertyListData:(NSData *)data;

/*
The methods below are in need up refractor and rethinking. Their current state
 requires an TCSLicense object with a publicKey set. The functions then act on
 data passed in and ignore all other values in the TCSLicense object.
*/
- (BOOL)verifyLicenseFile:(NSString *)path;
- (BOOL)verifyLicenseData:(NSData *)data ;
- (NSDictionary *)dictionaryForLicenseData:(NSData *)data;
- (NSDictionary *)dictionaryForLicenseFile:(NSString *)path;

@end

NS_ASSUME_NONNULL_END
