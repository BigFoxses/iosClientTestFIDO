import SwiftUI

@main
struct WebAuthnSwiftApp: App {
    @StateObject private var viewModel = WebAuthnViewModel() // Ensure viewModel is here

    var body: some Scene {
        WindowGroup {
            ContentView()
                .environmentObject(viewModel) // Inject WebAuthnViewModel into environment
        }
    }
}
