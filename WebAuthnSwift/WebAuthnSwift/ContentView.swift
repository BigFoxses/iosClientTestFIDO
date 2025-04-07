import SwiftUI

struct ContentView: View {
    @StateObject private var viewModel = WebAuthnViewModel()

    var body: some View {
        NavigationView {
            VStack(alignment: .leading, spacing: 16) {
                // iOS 14 compatible navigation
                Text("WebAuthn Demo")
                    .font(.title)
                    .bold()

                NavigationLink("Configure WebAuthn Settings", destination: ConfigurationView())
                    .buttonStyle(BorderedButtonStyle())

                Text("Input JSON")
                TextEditor(text: $viewModel.inputText)
                    .frame(height: 150)
                    .border(Color.gray, width: 1)
                    .padding(.bottom, 10)

                HStack {
                    Button("Example Create") {
                        viewModel.loadExampleCreate()
                    }
                    .buttonStyle(BorderedButtonStyle())

                    Button("Example Get") {
                        viewModel.loadExampleGet()
                    }
                    .buttonStyle(BorderedButtonStyle())
                }

                HStack {
                    Button("Create") {
                        viewModel.create()
                    }
                    .buttonStyle(BlueBorderedButtonStyle())

                    Button("Get") {
                        viewModel.get()
                    }
                    .buttonStyle(.bordered)
                    .tint(.blue)

                    Button("Retrieve") {
                        viewModel.retrieve()
                    }
                    .buttonStyle(.bordered)
                    .tint(.blue)
                    
                    Button("Clear") {
                        viewModel.clearInput()
                    }
                    .buttonStyle(.bordered)
                    .tint(.blue)
                }
                .padding(.bottom, 10)

                Text("Output JSON")
                TextEditor(text: $viewModel.outputText)
                    .frame(height: 200)
                    .border(Color.gray, width: 1)

                if let errorMessage = viewModel.errorMessage {
                    Text(errorMessage)
                        .foregroundColor(.red)
                        .padding()
                }
            }
            .padding()
        }
        .navigationViewStyle(.stack) // Required for iOS 14 stack behavior
    }
}

struct BorderedButtonStyle: ButtonStyle {
    func makeBody(configuration: Configuration) -> some View {
        configuration.label
            .padding(.horizontal, 12)
            .padding(.vertical, 8)
            .foregroundColor(.blue)
            .overlay(
                RoundedRectangle(cornerRadius: 8)
                    .stroke(Color.blue, lineWidth: 1)
            )
    }
}

struct BlueBorderedButtonStyle: ButtonStyle {
    func makeBody(configuration: Configuration) -> some View {
        configuration.label
            .padding(.horizontal, 12)
            .padding(.vertical, 8)
            .background(Color.blue)
            .foregroundColor(.white)
            .cornerRadius(8)
            .overlay(
                RoundedRectangle(cornerRadius: 8)
                    .stroke(Color.blue, lineWidth: 1)
            )
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ConfigurationView()
            .environmentObject(WebAuthnViewModel())
    }
}
