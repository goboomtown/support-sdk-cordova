var exec = require('cordova/exec');

exports.initiateBoomtown = function(supportJSON, desiredMenuType, success, error) {
  exec(success, error, "SupportSDK", "initiateBoomtown", [supportJSON, desiredMenuType]);
};

exports.initiateBoomtownWithAppearance = function(supportJSON, uiJSON, desiredMenuType, success, error) {
  exec(success, error, "SupportSDK", "initiateBoomtownWithAppearance", [supportJSON, uiJSON, desiredMenuType]);
};

exports.displayMenu = function(arg0, success, error) {
  exec(success, error, "SupportSDK", "displayMenu", [arg0]);
};

exports.configureAppearance = function(arg0, success, error) {
  exec(success, error, "SupportSDK", "configureAppearance", [arg0]);
};
