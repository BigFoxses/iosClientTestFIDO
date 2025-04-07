#import <Foundation/Foundation.h>

//! Project version number for ZSM framework.
FOUNDATION_EXPORT double ZSMVersionNumber;

//! Project version string for ZSM framework.
FOUNDATION_EXPORT const unsigned char ZSMVersionString[];

#import <Foundation/Foundation.h>
#import <ZSM/ZSMError.h>
#import <ZSM/ZSMConfig.h>

NS_ASSUME_NONNULL_BEGIN

@class ZSM;

typedef void (^ZSMInitializationCompletion)(ZSM * _Nullable zsm, ZSMError * _Nullable error);

/**
 * This block is called when a success/failure result is ready.
 * @param success A boolean indicating whether the operation was successful.
 * @param error The error that occurred during the operation, if any.
 */
typedef void (^ZSMSuccessCompletion)(BOOL success, NSDictionary<NSString *, NSString *> * _Nullable metadata, ZSMError * _Nullable error);

/**
 * This block is called when a data operation is complete.
 * @param data The data resulting from the operation, if successful.
 * @param error The error that occurred during the operation, if any.
 */
typedef void (^ZSMJSONCompletion)(NSDictionary<NSString *, id> * _Nullable data, NSDictionary<NSString *, NSString *> * _Nullable metadata, ZSMError * _Nullable error);

/**
 * This block is called when a data operation is complete.
 * @param signature Signature result from signing
 * @param publicKey public key from signing operation
 * @param error The error that occurred during the operation, if any.
 */
typedef void (^ZSMSignCompletion)(NSData * _Nullable signature, NSData * _Nullable publicKey, NSDictionary<NSString *, NSString *> * _Nullable metadata, ZSMError * _Nullable error);

/**
 * `ZSM` manages security tasks such as activation, checking status, managing keys, and handling signatures.
 */
@interface ZSM : NSObject

#pragma mark - Registration and initialization

/**
 * Instantiates a ZSM instance with the specified configuration
 * @param config The configuration ZSM
 * @param completion Callback to be invoked upon completion containing a ZSM instance, if no error has been encountered.
 */
+ (void)createInstanceWithConfig:(ZSMConfig*)config completion:(ZSMInitializationCompletion)completion
NS_SWIFT_NAME(createInstance(config:completion:));

- (instancetype)init NS_UNAVAILABLE;
/**
 Version information about api
 */
@property (readonly, nonatomic) NSString *versionString;
    
/**
 Configuration of this instance
 */
@property (readonly, nonatomic) ZSMConfig *config;

/**
 * Indicates whether a cryptographic key has been generated.
 */
@property (readonly, nonatomic) BOOL hasCryptographicKey;

#pragma mark - Key management

/**
 * Generates a cryptographic key.
 * @param completion Callback to be invoked upon key generation completion.
 */
- (void)generateKeyWithCompletion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(generateKey(completion:));

/**
 * Generates a new cryptographic key.
 * @param headers Optional headers which will be merged with any headers specified in the initializer.
 * @param metadata Optional meta data for server.
 * @param completion Callback to be invoked upon key generation completion.
 */
- (void)generateKeyWithHeaders:(nullable NSDictionary<NSString *, NSString *> *)headers
                        metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata
                      completion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(generateKey(headers:metadata:completion:));

/**
 * Refreshes the cryptographic key.
 * @param completion Callback to be invoked upon key refresh completion.
 */
- (void)refreshKeyWithCompletion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(refreshKey(completion:));

/**
 * Refreshes the current cryptographic key.
 * @param headers Optional headers which will be merged with any headers specified in the initializer and sent to the server.
 * @param metadata Optional meta which will be merged with any headers specified in the initializer and sent to the server.
 * @param completion Callback to be invoked upon key refresh completion.
 */
- (void)refreshKeyWithHeaders:(nullable NSDictionary<NSString *, NSString *> *)headers
                     metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata
                   completion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(refreshKey(headers:metadata:completion:));

/**
 * Imports a cryptographic key from a PEM-encoded string.
 * @param pem PEM-encoded key data.
 * @param completion Callback to be invoked upon key import completion.
 */
- (void)importKey:(nonnull NSData *)pem
       completion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(importKey(from:completion:));

/**
 * Imports a cryptographic key from a PEM-encoded string.
 * @param pem PEM-encoded key data.
 * @param headers Optional headers which will be merged with any headers specified in the initializer and sent to the server.
 * @param metadata Optional meta which will be merged with any headers specified in the initializer and sent to the server.
 * @param completion Callback to be invoked upon key import completion.
 */
- (void)importKey:(nonnull NSData *)pem
          headers:(nullable NSDictionary<NSString *, NSString *> *)headers
         metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata
       completion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(importKey(from:headers:metadata:completion:));

/**
 * Deletes a cryptographic key.
 * @param completion Callback to be invoked upon key deletion completion.
 */
- (void)deleteKeyWithCompletion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(deleteKey(completion:));

/**
 * Deletes a cryptographic key.
 * @param headers Optional headers which will be merged with any headers specified in the initializer and sent to the server.
 * @param metadata Optional meta which will be merged with any headers specified in the initializer and sent to the server.
 * @param completion Callback to be invoked upon key deletion completion.
 */
- (void)deleteKeyWithHeaders:(nullable NSDictionary<NSString *, NSString *> *)headers
                    metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata
                  completion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(deleteKey(headers:metadata:completion:));

/**
 * Deletes all storage associated with this device including the cryptographic key.
 */
- (void)reset;

#pragma mark - Encryption and signing

/**
 * Generates a signature for the specified message using the current cryptographic key using the algorithm specified in configuration
 * @param message Message to sign.
 * @param completion Callback to be invoked upon signature generation completion.
 */
- (void)generateSignatureForMessage:(nonnull NSData*)message
                         completion:(ZSMSignCompletion)completion
NS_SWIFT_NAME(generateSignature(_:completion:));

/**
 * Generates a signature for the specified message using the current cryptographic key.
 * @param message Message to sign.
 * @param headers Optional headers which will be merged with any headers specified in the initializer and sent to the server.
 * @param metadata Optional meta which will be merged with any headers specified in the initializer and sent to the server.
 * @param refresh Refresh keys if true.
 * @param completion Callback to be invoked upon signature generation completion.
 */
- (void)generateSignatureForMessage:(nonnull NSData*)message
                            headers:(nullable NSDictionary<NSString *, NSString *> *)headers
                           metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata
                            refresh:(BOOL)refresh
                         completion:(ZSMSignCompletion)completion
NS_SWIFT_NAME(generateSignature(_:headers:metadata:refresh:completion:));

/**
 * Verifies the specified signature for the specified message using the current cryptographic key.
 * @param signature Signature data to verify.
 * @param message Original message for verification.
 * @param publicKey Optional public key for verification. Defaults to client keyset
 * @param completion Callback to be invoked upon signature verification completion.
 */
- (void)verifySignature:(nonnull NSData *)signature
                message:(nonnull NSData*)message
              publicKey:(nullable NSData*)publicKey
             completion:(ZSMSuccessCompletion)completion
NS_SWIFT_NAME(verifySignature(_:message:publicKey:completion:));


/**
 * Performs WebAuthn creation (attestation).
 * @param options JSON dictionary of WebAuthn creation options.
 * @param completion Callback to be invoked upon completion with result data or error.
 */
- (void)webauthnCreateWithOptions:(NSDictionary<NSString *, id> *)options completion:(ZSMJSONCompletion)completion
NS_SWIFT_NAME(webauthnCreate(options:completion:));

/**
 * Performs WebAuthn get (assertion).
 * @param options JSON dictionary of WebAuthn get options.
 * @param completion Callback to be invoked upon completion with result data or error.
 */
- (void)webauthnGetWithOptions:(NSDictionary<NSString *, id> *)options completion:(ZSMJSONCompletion)completion
NS_SWIFT_NAME(webauthnGet(options:completion:));

/**
 * Retrieves the attestation from create
 * @param completion Callback to be invoked upon completion with result data.
 */
- (void)webauthnRetrieveWithCompletion:(ZSMJSONCompletion)completion
NS_SWIFT_NAME(webauthnRetrieve(completion:));

@end

NS_ASSUME_NONNULL_END
