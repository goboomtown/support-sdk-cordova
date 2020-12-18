# Boomtown Cordova Plugin for Support SDK

## 1. Description

This plugin allows to implement the Boomtown Support SDK in your Cordova application.

## 2. Minimum Requirements

#### iOS

- Xcode 10.2
- iOS 11.0

#### Android

- Android 4.4 (API Level 19)
- Android Studio, v2.3.0 or higher recommended
- Gradle 3 or higher recommended


## 3. Installation
```
cordova plugin add https://github.com/goboomtown/support-sdk-cordova.git
```
No manual configuration required.

## 4. How it works

This plugin comes bundled with a SupportActivity that extends AppCompatActivity and adds CordovaFragment using FragmentTransactions.

AndroidManifest.xml is automatically updated to use the new SupportActivity.

## 5. Initialization Methods

There are two basic methods available to initiate the Support SDK:

```
supportsdk.initiateBoomtown(boomtownConfigJSON, desiredMenuType, success, failure);

supportsdk.initiateBoomtownWithAppearance(boomtownConfigJSON, uiConfigJSON, desiredMenuType, success, failure);

```

where:

boomtownConfigJSON is a JSON string containing the server configuration
uiConfigJSON is a JSON string containing the appearance configuration


## 6. Sample Cordova implementation

```
document.addEventListener('deviceready', onDeviceReady, false);

function onDeviceReady() {
    // Cordova is now initialized. Have fun!

    console.log('Running cordova-' + cordova.platformId + '@' + cordova.version);
    document.getElementById('deviceready').classList.add('ready');

    startBoomtown();

    window.resolveLocalFileSystemURL(cordova.file.applicationDirectory + "www/config.json", gotFile, fail);
}

function startBoomtown() {
  supportsdk.initiateBoomtownWithAppearance(
    JSON.stringify(boomtownConfig),
    JSON.stringify(uiConfig),
    1,
    function(msg) {
    },
    function(err) {
    }
  );
}

```

## 7. Server Configuration

The plugin depends on a server JSON configuration file (www/config.json here) that you must obtain from your provider. The file looks like this:

```
{
  "apiHost": "https://api.goboomtown.com",
  "integrationId": "xxxxxx",
  "apiKey": "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
  "buttonURL":"https://api.goboomtown.com/resources/images/sdk_button.png",
  "partnerToken": "xxxxxxxx",
  "privateKey": "xxxxxxxxxxxxxxxxxxxxx"
}
```

This file enables communication with the server and configures the available features.

## 8. Menu Types

The second parameter of loadConfigurationFromJSON() is the desired menu type as per the following list:

```
typedef enum MenuStyle : NSInteger {
    NoMenu          = 0,
    Menu            = 1,
    Button          = 2,
    IconList        = 3,
    IconListExit    = 4
} MenuStyle;
```

## 9. Appearance Configuration

Much of the application (menus, icons, and colors currently) can be configured using a JSON file as follows:

This is the default JSON.

```
{
    "menu":
    {
        "chat": {
            "text": "Chat with Us",
            "icon": "a_chat"
        },
        "callme":
        {
            "text": "Call Me",
            "icon": "phone_call"
        },
        "knowledge":
        {
            "text": "Search Knowledge",
            "icon": "book_bookmark"
        },
        "web":
        {
            "text": "Web Support",
            "icon": "globe"
        },
        "email":
        {
            "text": "Email Support",
            "icon": "letter"
        },
        "phone":
        {
            "text": "Phone Support",
            "icon": "phone"
        },
        "forms":
        {
            "text": "Forms",
            "icon": "form"
        },
        "history":
        {
            "text": "History",
            "icon": "customer_alt"
        },
        "exit":
        {
            "text": "Exit"
        }
    },
    "icons":
    {
        "kbFolderIcon": "book-bookmark",
        "chatAttachmentButtonImage": "paperclip.png",
        "chatSendButtonImage": "send.png"
    },
    "colors":
    {
        "navigationBarColor": "#f2f2f2",
        "iconColor": "#EF5E0D",
        "buttonColor": "#EF5E0D",
        "lineColor": "#E0E0E0",
        "textColor": "#4F4F4F",
        "homeIconColor": "#EF5E0D",
        "homeLineColor": "#E0E0E0",
        "homeTextColor": "#4F4F4F",
        "homeSelectedColor": "#EBEBEB",
        "callMeHeaderTextColor": "#4F4F4F",
        "callMeLabelTextColor": "#626363",
        "callMeHintTextColor": "#ACACAC",
        "callMeButtonTextColor": "#ACACAC",
        "callMeButtonBackgroundColor": "#1AA8A8",
        "ratingHeaderTextColor": "#4F4F4F",
        "ratingLabelTextColor": "#626363",
        "ratingHintTextColor": "#ACACAC",
        "ratingButtonTextColor": "#ACACAC",
        "ratingButtonBackgroundColor": "#1AA8A8",
        "chatRefidTextColor": "#4f4f4f",
        "chatNavBarColor": "#f2f2f2",
        "chatSendButtonEnabledColor": "#626363",
        "chatSendButtonDisabledColor": "#ACACAC",
        "chatTimeStampColor": "#ACACAC",
        "chatActionButtonTextColor": "#838383",
        "chatActionButtonSelectedTextColor": "#ffffff",
        "chatActionButtonBorderColor": "#E0E0E0",
        "chatIconColor": "#838383",
        "kbFolderNameTextColor": "#303030",
        "kbFolderL0BackgroundColor": "#F3F8F8",
        "kbTextColor": "#303030",
        "menuBorderColor": "#E0E0E0"
    }
}
```

If you only want to configure a general color scheme you need only set the following colors:

```
iconColor
buttonColor
lineColor
textColor
```
