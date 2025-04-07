import SwiftUI

struct ConfigurationView: View {
    @EnvironmentObject var viewModel: WebAuthnViewModel
    @Environment(\.presentationMode) var presentationMode // Allows navigation back

    var body: some View {
        Form {
            Section(header: Text("WebAuthn Configuration")) {
                TextField("Host URL", text: $viewModel.hostUrl)
                    .keyboardType(.URL)
                    .autocapitalization(.none)
                    .disableAutocorrection(true)

                TextField("Application ID", text: $viewModel.applicationId)
                    .autocapitalization(.none)
                    .disableAutocorrection(true)

                TextField("Consumer ID", text: $viewModel.consumerId)
                    .autocapitalization(.none)
                    .disableAutocorrection(true)

                Button("Save Settings") {
                    viewModel.saveConfig()
                    presentationMode.wrappedValue.dismiss() // Dismiss view after saving
                }
                .buttonStyle(.bordered)
                .tint(.blue)
                .padding()
            }
        }
        .navigationTitle("Configuration")
    }
}

struct ConfigurationView_Previews: PreviewProvider {
    static var previews: some View {
        ConfigurationView()
            .environmentObject(WebAuthnViewModel()) // Ensure environmentObject is provided
    }
}
