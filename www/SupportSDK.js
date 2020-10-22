var exec = require('cordova/exec');

exports.loadConfigurationFromJSON = function(arg0, success, error) {
  exec(success, error, "SupportSDK", "loadConfigurationFromJSON", [arg0]);
};

exports.initiateBoomtown = function(arg0, success, error) {
  exec(success, error, "SupportSDK", "initiateBoomtown", [arg0]);
};
