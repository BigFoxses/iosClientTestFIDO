//
//  ZSMConfig.h
//  ZSM
//
//  Created by Joel Teply on 8/9/23.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Enum representing the various loging levels.
 */
typedef NS_ENUM(NSInteger, LogLevel) {
    LogLevelTrace=-1, /**< Used for trace logging. */
    LogLevelDebug, /**< Used for debugging purposes. This level of logging provides the most granular information. */
    LogLevelInfo, /**< Used to record informational messages that highlight the progress of the application at a high level. */
    LogLevelWarn, /**< Indicates potentially harmful situations. */
    LogLevelError, /**< Used to record error events that might still allow the application to continue running.*/
    LogLevelFatal /**< Records very severe error events that will presumably lead the application to abort. */
};

/**
 * Enum representing the various encryption algorithms.
 */
typedef NS_ENUM(NSInteger, MPCAlgorithm) {
    MPCAlgorithmECDSAP256=0x10,
    MPCAlgorithmRSA2048=0x20,
    MPCAlgorithmRSA3072=0x21,
    MPCAlgorithmRSA4096=0x22,
    MPCAlgorithmAES128ECB=0x30,
    MPCAlgorithmAES128CTR=0x31,
};

/**
 * This block is called whenever a log message is created.
 * @param level The log level of the message.
 * @param message The log message.
 */
typedef void (^ZSMLoggingCallback)(LogLevel level, NSString * message);

@interface ZSMConfig : NSObject

    /**
     * Instantiates a ZSM config instance with the specified host URL and consumer ID.
     * @param json configuration json
     * @return A newly initialized ZSMConfig instance.
     */
    - (instancetype)initWithJSON:(NSDictionary *)json;

    /**
     * Host url for performing remote transactions
     */
    @property (strong, nonatomic, nonnull) NSURL *hostUrl;

    /**
     * Application ID for remote transactions
     */
    @property (strong, nonatomic, nonnull) NSUUID *applicationId;

    /**
     * Network timeout while performing remote transactions. Default's to 30 seconds or 30000 ms
     */
    @property (assign, nonatomic) NSUInteger requestTimeoutMS;

    /**
     * Network retry count while performing remote transactions. Default's to 0
     */
    @property (assign, nonatomic) NSUInteger retryCount;

    /**
     * Whether to perform a health check prior to instantiation to test for network health. Defaults to true.
     */
    @property (assign, nonatomic) BOOL performNetworkHealthCheck;

    /**
     * Environment name, defaults to "TEST"
     */
    @property (strong, nonatomic, nonnull) NSString *environment;

    /**
     * Headers used while performing remote transactions
     */
    @property (strong, nonatomic) NSDictionary *headers;

    /**
     * meta data used while performing remote transactions
     */
    @property (strong, nonatomic) NSDictionary *metadata;

    /**
     * consumer ID for remote transactions
     */
    @property (strong, nonatomic, nonnull) NSString *consumerId;

    /**
      Shared keychain group ID between multiple applications of the same vendor.
      The format is typically 'keychainGroup' or 'TEAMID.keychainGroup', where 'keychainGroup' is specified as an entry in your app's Target Settings -> Keychain Sharing -> Keychain Groups. 'TEAMID' is your iOS Development Team ID, found in your iOS provisioning portal or as the string 'DEVELOPMENT_TEAM' within the project file.
      The necessity of including 'TEAMID' in the format can vary based on your app's configuration and provisioning. For detailed guidelines on setting up and using keychain access groups, consult Apple's documentation on this subject: https://developer.apple.com/documentation/bundleresources/entitlements/keychain-access-groups
    */
    @property (strong, nonatomic, nullable) NSString *keychainGroup;

    
    /**
     * encryption algorithm for transactions. Defaults to MpcAlgorithmECDSAP256
     */
    @property (assign, nonatomic) MPCAlgorithm mpcAlgorithm;

    /**
     * abiity to bypass biometrics, which assumes it has been implemented outside of this api
     */
    @property (assign, nonatomic) BOOL requiresBiometrics;
    
    /**
     * level for api logging
     */
    @property (assign, nonatomic) LogLevel logLevel;
    
    /**
     * A block that will be called whenever a log message is created.
     */
    @property (copy, nonatomic) ZSMLoggingCallback logFunction;
@end

NS_ASSUME_NONNULL_END
