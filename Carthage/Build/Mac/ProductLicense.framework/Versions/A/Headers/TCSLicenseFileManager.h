#import <Foundation/Foundation.h>
@class TCSLicense;

NS_ASSUME_NONNULL_BEGIN

/**
 Protocol defined to support test cases that don't depend on NSFileManager.
 All these methods are implemented by NSFileManager.
 */
@protocol TCSFileManagerProtocol

- (nullable NSArray<NSString *> *)contentsOfDirectoryAtPath:(NSString *)path
                                                      error:(NSError **)error;

- (nullable NSData *)contentsAtPath:(NSString *)path;
- (BOOL)fileExistsAtPath:(NSString *)path;
- (BOOL)createFileAtPath:(NSString *)path
                contents:(nullable NSData *)data
              attributes:(nullable NSDictionary<NSFileAttributeKey, id> *)attr;
- (BOOL)createDirectoryAtURL:(NSURL *)url
 withIntermediateDirectories:(BOOL)createIntermediates
                  attributes:(nullable NSDictionary<NSFileAttributeKey, id> *)attributes
                       error:(NSError **)error;
@end

@interface TCSLicenseFileManager : NSObject
@property NSString *fileExtension;
/**

 */
- (instancetype)initWithSearchPath:(NSURL *)searchPath
                     fileExtension:(NSString *)fileExtension
                       fileManager:(id<TCSFileManagerProtocol>)fileManager NS_DESIGNATED_INITIALIZER;

- (NSData * _Nullable)discoverLicense;
- (NSArray<NSString *> *_Nullable)licenseFileNames;
- (NSData * _Nullable)validLicenseFromFilesNamed:(NSArray<NSString *> * _Nonnull)paths;

- (TCSLicense * _Nullable)discoverValidLicense;
- (NSArray<NSURL *> * _Nullable)licenseFilesInSearchPath;

/**
 Saves PList license in the search directory, using the fileName.
 */
- (void)saveLicense:(TCSLicense *)license withName:(NSString *)fileName;

/**
 Saves license based on search directory, license key, and license extension.
 */
- (void)saveLicense:(TCSLicense *)license;

/**
 Makes sure directory exists, and creates it if it doesn't.
 */
- (void)ensureDirectory:(NSURL *)directory error:(NSError **)error;
-(BOOL)isLicenseValidFromFile:(NSString *)inPath;

@end

NS_ASSUME_NONNULL_END
