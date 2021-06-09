# Boomtown Cordova Plugin for Support SDK

## Description

This plugin allows to implement the Boomtown Support SDK in your Cordova application.

## Minimum Requirements

#### iOS

- Xcode 10.2
- iOS 11.0

#### Android

- Android 4.4 (API Level 19)
- Android Studio, v2.3.0 or higher recommended
- Gradle 3 or higher recommended


## Installation
```
cordova plugin add https://github.com/goboomtown/support-sdk-cordova.git
```
No manual configuration required.

## How it works

This plugin comes bundled with a SupportActivity that extends AppCompatActivity and adds CordovaFragment using FragmentTransactions.

AndroidManifest.xml is automatically updated to use the new SupportActivity.

## Initialization Methods

There are three basic methods available to initiate the Support SDK:

```
supportsdk.initiateBoomtown(boomtownConfigJSON, null, success, failure);

supportsdk.initiateBoomtownWithAppearance(boomtownConfigJSON, uiConfigJSON, null, success, failure);

supportsdk.initiateBoomtownWithCustomerAndAppearance(boomtownConfigJSON, customerJSON, uiConfigJSON, null, success, failure);

```

where:

boomtownConfigJSON is a JSON string containing the server configuration
customerJSON is a JSON string containing keys which identify the customer
uiConfigJSON is a JSON string containing the appearance configuration


## Sample Cordova implementation

```js
document.addEventListener('deviceready', onDeviceReady, false);

function onDeviceReady() {
    // Cordova is now initialized. Have fun!

    console.log('Running cordova-' + cordova.platformId + '@' + cordova.version);
    document.getElementById('deviceready').classList.add('ready');

    startBoomtown();

    window.resolveLocalFileSystemURL(cordova.file.applicationDirectory + "www/config.json", gotFile, fail);
}


function startBoomtown() {
  supportsdk.startBoomtownWithCustomerAndAppearance(
    JSON.stringify(boomtownConfig),
    null,
    JSON.stringify(uiConfig),
    null,
    function(response) {
    },
    function(err) {
    }
  );
}
```

## Events and Requests

The Support SDK sends events to provide status updates to the calling application. It also supports external requests made by the calling application.


### Events

An event will have the following properties (data is optional):

```
SupportSDKEventName: "event.name",
SupportSDKEventType: "event.type",
SupportSDKEventData: "event.data",

```

and will be identified by the event name:

```
SupportSDKEvent: "com.goboomtown.supportsdk.event",

```


This example code may be used to handle Support SDK events:

```
document.addEventListener(supportsdk.SupportSDKEvent, handleSDKEvent, false);

function handleSDKEvent(event) {
    if ( !event.detail.hasOwnProperty(supportsdk.SupportSDKEventType) ) {
        return false;
    }
    console.log(event.detail[supportsdk.SupportSDKEventType]);
}
```


The following event types are currently supported:

```
  EventChatStarted:         "com.goboomtown.event.chat.started",
  EventChatIssueCreated:    "com.goboomtown.event.chat.issue_created",
  EventChatIssueContinued:  "com.goboomtown.event.chat.issue_continued",
  EventChatIssueResolved:   "com.goboomtown.event.chat.issue_resolved",
  EventChatEnded:           "com.goboomtown.event.chat.ended",

  EventHistoryStarted:      "com.goboomtown.event.history.started",
  EventHistoryEnded:        "com.goboomtown.event.history.ended",

  EventKnowledgeStarted:    "com.goboomtown.event.knowledge.started",
  EventKnowledgeEnded:      "com.goboomtown.event.knowledge.ended",

  EventFormStarted:         "com.goboomtown.event.form.started",
  EventFormSubmitted:       "com.goboomtown.event.form.submitted",
  EventFormEnded:           "com.goboomtown.event.form.ended",

  EventAlertPresented:            "com.goboomtown.event.alert.presented",
  EventAlertDismissed:            "com.goboomtown.event.alert.dismissed",
  EventAlertDefaultClicked:       "com.goboomtown.event.alert.default",
  EventAlertPositiveClicked:      "com.goboomtown.event.alert.positive",
  EventAlertNegativeClicked:      "com.goboomtown.event.alert.negative",
```

### Requests

Requests may be sent to the Support SDK to take an action.

This is an example of a typical request, in this case to send an alert:

```js
userInfo = new Object();
userInfo[supportsdk.RequestAlertTitle] = "This is a test alert.";
userInfo[supportsdk.RequestAlertPositiveButtonTitle] = "OK";
userInfo[supportsdk.RequestAlertNegativeButtonTitle] = "Cancel";
supportsdk.sendRequest(
  supportsdk.RequestAlert,
  userInfo,
  function(msg) {
  },
  function(err) {
  }
);
```

The following requests are supported:
```
  RequestSupportSDKExit:    "com.goboomtown.request.supportsdk.exit",
  RequestToast:             "com.goboomtown.request.toast",
  RequestAlert:             "com.goboomtown.request.alert",
  RequestChatExit:          "com.goboomtown.request.chat.exit",
  RequestChatExitResolveIssue:  "com.goboomtown.event.chat.exit_resolve_issue",
```

The following additional information may be provided for toasts or alerts"
```
RequestAlertTitle:             "alert.title",
RequestAlertMessage:            "alert.message",
RequestAlertPositiveButtonTitle: "alert.positive",
RequestAlertNegativeButtonTitle: "alert.negative",
```


## Server Configuration

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

## Menu Types

The menu style is configured in the menuAppearance section of the appearance JSON like this:

```
"menuAppearance":
{
  "style": "iconlist"
...
}

```
The style value may be one of the following:

```
"nomenu"
"menu"
"button"
"iconlist"
"iconlistexit"
```

## Customer Configuration

If desired, the customer may be identified by providing values for any of the following keys"

```
CustomerId : "members_id",
CustomerExternalId: "members_external_id",
CustomerLocationId: "members_locations_id",
CustomerLocationExternalId: "members_locations_external_id",
CustomerLocationMid: "members_locations_mid",
UserId: "members_users_id",
UserExternalId: "members_users_external_id",
UserEmail: "members_users_email",
UserPhone: "members_users_phone",
```

like this:

```
var customerJSON = {
  "members_users_email": "email@example.com"
};
```

## Appearance Configuration

Much of the application (menus, icons, and colors currently) can be configured using a JSON file as follows:

This is the default JSON.

```
{
  "navigationBarAppearance":
  {
    "backgroundColor": "#ffffff",
    "backgroundColorDark": "#121212",
    "textColor": "#000000",
    "textColorDark": "#ffffff",
    "iconColor": "#000000",
    "iconColorDark": "#ffffff"
  },
  "menuAppearance":
  {
    "style": "iconlist",
    "heading": "Support",
    "textSize": "20",
    "textStyle": "bold",
    "borderWidth": "1",
    "padding": "10",
    "spacing": "50",
    "textColor": "#000000",
    "textColorDark": "#ffffff",
    "iconColor": "#EF5E0D",
    "iconColorDark": "#EF5E0D",
    "borderColor": "#E0E0E0",
    "borderColorDark": "#E0E0E0",
    "backgroundColor":  "#FAFAFA",
    "backgroundColorDark": "#121212"
  },
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
    "textColorDark": "#ffffff",
    "homeIconColor": "#EF5E0D",
    "homeLineColor": "#E0E0E0",
    "homeTextColor": "#007AFF",
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
  },
  "formAppearance":
  {
    "cancelButtonText": "Cancel",
    "saveButtonText": "Save",
    "label":
    {
      "textStyle": "bold",
      "textSize": "20",
      "textColor": "#000000",
      "textColorDark": "#ffffff",
      "requiredTextColor": "#000000",
      "requiredTextColorDark": "#ffffff",
      "requiredIndicatorColor": "#cc0000",
      "requiredIndicatorColorDark": "#cc0000"
    },
    "entry":
    {
      "textStyle": "bold",
      "textSize": "20",
      "textColor": "#000000",
      "textColorDark": "#ffffff",
      "borderColor": "#000000",
      "borderColorDark": "#ffffff",
      "borderWidth": "1"
    }
  }
}
```

If you only want to configure a general color scheme you need only set the following colors:

```
iconColor
buttonColor
lineColor
textColor
textColorDark
```
