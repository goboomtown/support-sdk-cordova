# Boomtown Product Support Platform SDK for ios

### Getting Started

After cloning the project you will need to retrieve dependencies. This is done with Carthage (https://github.com/Carthage/Carthage). Once you have installed Carthage you should run the following command:

```
carthage build --platform ios --use-xcframeworks
```

Go get a coffee. It will take a while.

**Note:** If you experience an issue building XMPPFramework, you may need to go to open `Carthage/Checkouts/XMPPFramework/XMPPFramework.xcodeproj` in Xcode and change the XMPPFrameworkSwift scheme to use a minimum target of iOS 11.0, then build again.

Once you have done that you can build the SDK or the Test app by selecting the appropriate build scheme.

The  `make_supportsdk_xcframework` script will build the framework using the `(R) SupportSDK` scheme and copy it to the Distribution/support-sdk-ios subdirectory. In that directory you should change the SupportSDK.podspec file to reflect the new SupportSDK version number and then push the new Pod using the command:

```
pod trunk push SupportSDK.podspec
```
