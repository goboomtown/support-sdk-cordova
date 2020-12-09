var exec = require('cordova/exec');

exports.loadConfigurationFromJSON = function(arg0, arg1, success, error) {
  exec(success, error, "SupportSDK", "loadConfigurationFromJSON", [arg0, arg1]);
};

exports.initiateBoomtown = function(arg0, arg1, success, error) {
  exec(success, error, "SupportSDK", "initiateBoomtown", [arg0, arg1]);
};

exports.displayMenu = function(arg0, success, error) {
  exec(success, error, "SupportSDK", "displayMenu", [arg0]);
};
