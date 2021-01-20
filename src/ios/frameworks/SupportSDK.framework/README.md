# Boomtown Product Support Platform SDK for ios

### Getting Started

After cloning the project you will need to retrieve dependencies. This is done with Carthage (https://github.com/Carthage/Carthage). Once you have installed Carthage you should run the following command:

```
./carthage.sh update --platform iOS
```

Go get a coffee. It will take a while.

Once you have done that you can build the SDK or the Test app by selecting the appropriate build scheme.

The ios-build-framework-script.sh script will copy the new framework to the Distribution/support-sdk-ios subdirectory. In that directory you should change the SupportSDK.podspec file to reflect the new SupportSDK version number and then push the new Pod using the command:

```
pod trunk push SupportSDK.podspec
```
