#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Enum representing various types of errors that can occur in the ZSM system.
 */
typedef NS_ENUM(NSInteger, ZSMErrorCode) {
    ZSMErrorCode_Error = 0,                             /**< General error. */
    ZSMErrorCode_NetworkFailure = 1,                    /**< Network failure occurred. */
    ZSMErrorCode_InvalidLogin = 2,                      /**< Invalid login attempt. */
    ZSMErrorCode_UnauthorizedUser = 3,                  /**< Unauthorized user access attempt. */
    ZSMErrorCode_BadCryptograpicValue = 100,            /**< Bad cryptographic value encountered. */
    ZSMErrorCode_CryptographicFailure = 101,            /**< Cryptographic operation failed. */
    ZSMErrorCode_CryptographicKey = 102,                /**< Problem with cryptographic key. */
    ZSMErrorCode_SecureStorageUnavailable = 103,        /**< Secure storage is unavailable. */
    ZSMErrorCode_SecureStorageFailure = 104,            /**< Secure storage failure. */
    ZSMErrorCode_SecureStorageUnauthenticated = 105,    /**< Secure storage unauthenticated access attempt. */
    ZSMErrorCode_RegistrationFailure = 200,             /**< User registration failed. */
    ZSMErrorCode_RegistrationIncomplete = 201,          /**< User registration incomplete. */
    ZSMErrorCode_DeviceSuspended = 300,                 /**< Device is suspended. */
    ZSMErrorCode_DeviceDeactivated = 301,               /**< Device is deactivated. */
    ZSMErrorCode_AccountSuspended = 302,                /**< User account is suspended. */
    ZSMErrorCode_AccountDeactivated = 303,              /**< User account is deactivated. */
    ZSMErrorCode_InvalidKeychainSetup = 400,            /**< Invalid keychain information was specified. */
    ZSMErrorCode_DuplicateKeychainItem = 401,           /**< Duplicated keychain item. */
    ZSMErrorCode_InvalidKeychainGroup = 402             /**< Invalid keychain information was specified. */
};

/**
 * `ZSMError` is a class representing errors in the ZSM system.
 * It extends NSError to provide more specific error codes (see `ZSMErrorCode`).
 */
NS_SWIFT_SENDABLE // Immutable, and NSError must be Sendable because it conforms to Error in Swift
@interface ZSMError : NSError

/**
 * Initialize a `ZSMError` with a specific error code.
 * @param code The `ZSMErrorCode` for the error.
 */
- (instancetype)initWithCode:(ZSMErrorCode)code NS_SWIFT_NAME(init(code:));

/**
 * Initialize a `ZSMError` with a specific error code and message.
 * @param code The `ZSMErrorCode` for the error.
 * @param traceId The `trace ID` for the error which matches the server, if applicable.
 * @param message A custom error message.
 */
- (instancetype)initWithCode:(ZSMErrorCode)code traceId:(nullable NSString*)traceId message:(nullable NSString*)message NS_SWIFT_NAME(init(code:traceId:message:));

/**
 * Convenient method to create a `ZSMError` with a specific error code.
 * @param code The `ZSMErrorCode` for the error.
 */
+ (instancetype)errorWithCode:(ZSMErrorCode)code NS_SWIFT_NAME(error(code:));

/**
 * Convenient method to create a `ZSMError` with a specific error code and message.
 * @param code The `ZSMErrorCode` for the error.
 * @param traceId The `trace ID` for the error which matches the server, if applicable.
 * @param message A custom error message.
 */
+ (instancetype)errorWithCode:(ZSMErrorCode)code traceId:(nullable NSString*)traceId message:(nullable NSString*)message NS_SWIFT_NAME(error(code:traceId:message:));

/**
 * Provides the `ZSMErrorCode` for the current error.
 */
@property (readonly, nonatomic) ZSMErrorCode skError;
@property (readonly, nonatomic) NSString *traceId;

@end

NS_ASSUME_NONNULL_END
