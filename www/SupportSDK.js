var exec = require('cordova/exec');

var supportsdk = {
  NoMenu: 0,
  Menu: 1,
  Button: 2,
  IconList: 3,
  IconListExit: 4,

  CustomerId : "members_id",
  CustomerExternalId: "members_external_id",
  CustomerLocationId: "members_locations_id",
  CustomerLocationExternalId: "members_locations_external_id",
  CustomerLocationMid: "members_locations_mid",
  UserId: "members_users_id",
  UserExternalId: "members_users_external_id",
  UserEmail: "members_users_email",
  UserPhone: "members_users_phone",

  initiateBoomtown: function(supportJSON, desiredMenuType, success, error) {
    exec(success, error, "SupportSDK", "initiateBoomtown", [supportJSON, desiredMenuType]);
  },

  initiateBoomtownWithAppearance: function(supportJSON, uiJSON, desiredMenuType, success, error) {
    exec(success, error, "SupportSDK", "initiateBoomtownWithAppearance", [supportJSON, uiJSON, desiredMenuType]);
  },

  initiateBoomtownWithCustomerAndAppearance: function(supportJSON, customerJSON, uiJSON, desiredMenuType, success, error) {
    exec(success, error, "SupportSDK", "initiateBoomtownWithCustomerAndAppearance", [supportJSON, customerJSON, uiJSON, desiredMenuType]);
  },

  displayMenu: function(arg0, success, error) {
    exec(success, error, "SupportSDK", "displayMenu", [arg0]);
  },

  configureAppearance: function(arg0, success, error) {
    exec(success, error, "SupportSDK", "configureAppearance", [arg0]);
  }
};

module.exports = supportsdk;
