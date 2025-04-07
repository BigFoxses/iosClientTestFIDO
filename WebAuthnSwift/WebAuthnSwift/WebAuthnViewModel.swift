import SwiftUI
import ZSM
import Foundation

class WebAuthnViewModel: ObservableObject {
    @Published var zsm: ZSM?
    @Published var inputText: String = ""
    @Published var outputText: String = ""
    @Published var errorMessage: String?
    @Published var credentialId: String? // Stores rawId from Create()

    @Published var hostUrl: String = UserDefaults.standard.string(forKey: "hostUrl") ?? "https://mobilesoasit.citi.com/tbslab/"
    @Published var applicationId: String = UserDefaults.standard.string(forKey: "appId") ?? "6dcb42e7-5dfb-4263-b21f-34c014a55ecc"
    @Published var consumerId: String = "cititest1-ios"
    
//let headers: [String:String] = [ "client_id" : "E0F58A01-CF8B-4ADB-B6EA-A095275F8D90", "client_secret"  : "uy80l7g40j189q80b20wm94w3x53si4ehobpmw9h58526mkf4da"]

    
    let applicationEnvironment : String = "NA"
    
    init() {
        initializeZSM()
    }

    func initializeZSM() {
        
        let json : [String: Any] = [
            "host_url": hostUrl,
            "application_id": applicationId,
            "consumer_id": consumerId,
            "application_environment": applicationEnvironment
  //          "headers" :  [ "client_id" : "E0F58A01-CF8B-4ADB-B6EA-A095275F8D90", "client_secret"  : "uy80l7g40j189q80b20wm94w3x53si4ehobpmw9h58526mkf4da"]
            
        ]
        /*
        let config = ZSMConfig(json: [
            "host_url": hostUrl,
            "application_id": applicationId,
            "consumer_id": consumerId,
            "application_environment": applicationEnvironment,
            "headers" :  [ "client_id" : "E0F58A01-CF8B-4ADB-B6EA-A095275F8D90", "client_secret"  : "uy80l7g40j189q80b20wm94w3x53si4ehobpmw9h58526mkf4da"]
            
        ])
        */
        let config = ZSMConfig(json: json)
        
        ZSM.createInstance(config: config) { instance, error in
            DispatchQueue.main.async {
                if let instance = instance {
                    self.zsm = instance
                } else if let error = error {
                    self.errorMessage = "Error initializing ZSM: \(error.localizedDescription)"
                }
            }
        }
    }

    func saveConfig() {
        //UserDefaults.standard.set(hostUrl, forKey: "hostUrl")
        //UserDefaults.standard.set(applicationId, forKey: "appId")
        initializeZSM() // Reinitialize with new settings
    }

    func create() {
        guard let data = inputText.data(using: .utf8) else {
            print("invalid Json string")
            return
        }
        
        let object = try JSONSerialization.jsonObject(with: data)
        let prettyPrintedData = try JSONSerialization.data(
            withJSONObject: object,
            options: [.prettyPrinted, .sortedKeys]
        )
        let prettyPrintedString = String(data: prettyPrintedData, encoding: .utf8)!
        print(prettyPrintedString)
        
       // let jObject = try? JSONSerialization.jsonObject(with: js, options: [])
     
       // let formattedData = try? JSONSerialization.data(withJSONObject: jObject, options: [.prettyPrinted])
        
       // if let formattedString = String(data: formattedData, encoding: .utf8) {
       //     print(formattedString)
       // }
        
        
                
        guard let zsm = zsm, let jsonData = inputText.data(using: .utf8),
              let options = try? JSONSerialization.jsonObject(with: jsonData) as? [String: Any] else {
            errorMessage = "Invalid JSON input"
            return
        }

        zsm.webauthnCreate(options: options) { json, _, error in
            DispatchQueue.main.async {
                if let json = json, let rawId = json["rawId"] as? String {
                    self.credentialId = rawId // Store credential ID
                    self.outputText = self.formatJSON(json)
                } else {
                    self.outputText = "Error: \(error?.localizedDescription ?? "Unknown")"
                }
            }
        }
    }

    func get() {
        guard let zsm = zsm, let jsonData = inputText.data(using: .utf8),
              let options = try? JSONSerialization.jsonObject(with: jsonData) as? [String: Any] else {
            errorMessage = "Invalid JSON input or no credential available."
            return
        }

        zsm.webauthnGet(options: options) { json, _, error in
            DispatchQueue.main.async {
                self.outputText = json.map { self.formatJSON($0) } ?? "Error: \(error?.localizedDescription ?? "Unknown")"
            }
        }
    }

    func retrieve() {
        guard let zsm = zsm else {
            errorMessage = "ZSM is not initialized"
            return
        }

        zsm.webauthnRetrieve { json, _, error in
            DispatchQueue.main.async {
                self.outputText = json.map { self.formatJSON($0) } ?? "Error: \(error?.localizedDescription ?? "Unknown")"
            }
        }
    }
    
    func clearInput() {
        inputText = ""
        outputText = ""
    }

    func clearOutput() {
        outputText = ""
        errorMessage = nil
    }

    // Loads a valid WebAuthn Create() example. You will need to use your own relying party data
    func loadExampleCreate() {
        inputText = formatJSON([
            "rp": ["name": "zsm.app", "id": "zsm.app"],
            "user": ["id": "wdrGRM8-QVGObt2fluIsnw", "name": "user123", "displayName": "user123"],
            "challenge": "dae5Moljx_7gqaB2482nJ9Sytls_04mdAxbrApwgGcQ",
            "pubKeyCredParams": [["type": "public-key", "alg": -7], ["type": "public-key", "alg": -257]],
            "timeout": 300000,
            "authenticatorSelection": ["residentKey": "discouraged", "requireResidentKey": false, "userVerification": "required"],
            "attestation": "none",
            "extensions": ["credentialProtectionPolicy": "userVerificationRequired", "enforceCredentialProtectionPolicy": false, "uvm": true, "credProps": true]
        ])
    }

    // Loads a valid WebAuthn Get() example. You will need to use your own relying party data
    func loadExampleGet() {
        guard let credentialId = credentialId else {
            errorMessage = "No credential available. Run Create first."
            return
        }
        
        inputText = formatJSON([
            "challenge": "EeLxRgy2MyLAFsrrv0AH_qf5YQZEtC6ZkTtY4sCtNn8",
            "timeout": 300000,
            "rpId": "zsm.app",
            "allowCredentials": [["id": credentialId, "type": "public-key"]],
            "userVerification": "required"
        ])
    }

    private func formatJSON(_ json: [String: Any]) -> String {
        guard let data = try? JSONSerialization.data(withJSONObject: json, options: .prettyPrinted),
              let formattedString = String(data: data, encoding: .utf8) else {
            return "Error formatting JSON"
        }
        return formattedString
    }
}
