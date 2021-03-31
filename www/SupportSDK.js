  var exec = require('cordova/exec');

  var supportsdk = {
    /*  Menu options */
    NoMenu:       0,
    Menu:         1,
    Button:       2,
    IconList:     3,
    IconListExit: 4,

    /* Customer selectors */
    CustomerId:                 "members_id",
    CustomerExternalId:         "members_external_id",
    CustomerLocationId:         "members_locations_id",
    CustomerLocationExternalId: "members_locations_external_id",
    CustomerLocationMid:        "members_locations_mid",
    UserId:                     "members_users_id",
    UserExternalId:             "members_users_external_id",
    UserEmail:                  "members_users_email",
    UserPhone:                  "members_users_phone",

    /*  Event Types */
    SupportSDKEvent: "com.goboomtown.supportsdk.event",
    SupportSDKEventName: "event.name",
    SupportSDKEventType: "event.type",
    SupportSDKEventData: "event.data",

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

    RequestSupportSDKExit:    "com.goboomtown.request.supportsdk.exit",
    RequestToast:             "com.goboomtown.request.toast",
    RequestAlert:             "com.goboomtown.request.alert",
    RequestAlertTitle:             "alert.title",
    RequestAlertMessage:            "alert.message",
    RequestAlertPositiveButtonTitle: "alert.positive",
    RequestAlertNegativeButtonTitle: "alert.negative",

    RequestChatExit:          "com.goboomtown.request.chat.exit",
    RequestChatExitResolveIssue:  "com.goboomtown.request.chat.exit_resolve_issue",

    successCallback: function(arg){},

    initiateBoomtown: function(supportJSON, desiredMenuType, success, error) {
      supportsdk.sdkExec(success, error, "SupportSDK", "initiateBoomtown", [supportJSON, desiredMenuType]);
    },

    initiateBoomtownWithAppearance: function(supportJSON, uiJSON, desiredMenuType, success, error) {
      supportsdk.sdkExec(success, error, "SupportSDK", "initiateBoomtownWithAppearance", [supportJSON, uiJSON, desiredMenuType]);
    },

    initiateBoomtownWithCustomerAndAppearance: function(supportJSON, customerJSON, uiJSON, desiredMenuType, success, error) {
      supportsdk.sdkExec(success, error, "SupportSDK", "initiateBoomtownWithCustomerAndAppearance", [supportJSON, customerJSON, uiJSON, desiredMenuType]);
    },

    handleEvent: function(event) {
      if ( supportsdk.isSupportSDKEvent(event)) {
        console.log(event[supportsdk.SupportSDKEventType]);
        const myEvent = new CustomEvent(supportsdk.SupportSDKEvent, {
          detail: event,
          bubbles: true,
          cancelable: true,
          composed: false
        });
        document.dispatchEvent(myEvent);
      }
      if ( supportsdk.successCallback ) {
        supportsdk.successCallback(event);
      }
    },

    sdkExec: function(success, error, sdk, method, args) {
      supportsdk.successCallback = success;
      exec(this.handleEvent, error, sdk, method, args)
    },

    sendRequest: function(eventType, userInfo, success, error) {
      supportsdk.sdkExec(success, error, "SupportSDK", "sendRequest", [eventType, userInfo]);
    },


    displayMenu: function(arg0, success, error) {
      supportsdk.sdkExec(success, error, "SupportSDK", "displayMenu", [arg0]);
    },

    configureAppearance: function(arg0, success, error) {
      supportsdk.sdkExec(success, error, "SupportSDK", "configureAppearance", [arg0]);
    },

    isSupportSDKEvent: function(event) {
      if ( !event.hasOwnProperty(this.SupportSDKEventName) ) {
        return false;
      }
      if ( event[this.SupportSDKEventName] != this.SupportSDKEvent ) {
        return false;
      }
      return true;
    }

  };

  module.exports = supportsdk;
