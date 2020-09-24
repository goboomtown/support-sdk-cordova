# Boomtown Cordova Plugin for Support SDK

## 1. Description

This plugin allows to implement the Boomtown Support SDK in your Cordova application.

## 2. Minimum Requirements

#### iOS

- Xcode 10.2
- iOS 9.0

#### Android

- Android 4.4 (API Level 19)
- Android Studio, v2.3.0 or higher recommended
- Gradle 3 or higher recommended


## 3. Installation
```
cordova plugin add cordova-plugin-boomtown-supportsdk --save
```
No manual configuration required.

## 4. How it works
This plugin comes bundled with a SupportActivity that extends AppCompatActivity and adds CordovaFragment using FragmentTransactions.

AndroidManifest.xml is automatically updated to use the new SupportActivity.

## 5. Sample Cordova implementation

```
document.addEventListener('deviceready', onDeviceReady, false);

function onDeviceReady() {
    // Cordova is now initialized. Have fun!

    console.log('Running cordova-' + cordova.platformId + '@' + cordova.version);
    document.getElementById('deviceready').classList.add('ready');

    window.resolveLocalFileSystemURL(cordova.file.applicationDirectory + "www/config.json", gotFile, fail);
}

function fail(e) {
  console.log("FileSystem Error");
  console.dir(e);
}

function gotFile(fileEntry) {
  fileEntry.file(function(file) {
    var reader = new FileReader();

    reader.onloadend = function(e) {
      console.log(this.result);
      supportsdk.loadConfigurationFromJSON(
        this.result,
        function(msg) {
          document
          .getElementById('deviceready')
          .querySelector('.received')
          .innerHTML = msg;
        },
        function(err) {
          document
          .getElementById('deviceready')
          .innerHTML = '<p class="event received">' + err + '</p>';
        }
      );

    }

    reader.readAsText(file);


  });
}
```

## 6. Configuration

The plugin depends on a JSON file (www/config.json here) that you must obtain from your provider. The file looks like this:

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
