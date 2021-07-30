package com.goboomtown.plugin.supportsdk;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.apache.cordova.CordovaResourceApi;
import org.apache.cordova.file.FileUtils;
import org.apache.cordova.file.LocalFilesystemURL;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;
import android.content.Context;
import android.widget.Toast;
import android.net.Uri;

import android.app.Activity;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import android.view.View;
import android.util.Log;
import android.view.Gravity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.view.LayoutInflater;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.Resources;

import com.goboomtown.plugin.supportsdk.SupportActivity;
import com.goboomtown.supportsdk.api.EventManager;

import java.util.HashMap;
import java.util.Map;

import com.goboomtown.supportsdk.view.SupportButton;


public class SupportSDK extends CordovaPlugin
  implements SupportButton.SupportButtonListener {

  private CallbackContext callback            = null;
  private Activity        cordovaActivity     = null;
  private CordovaWebView  mWebView            = null;
  private Context         mContext            = null;
  private View            mView               = null;
  private View            mMainView           = null;
  private Resources       mResources          = null;
  private String          mPackageName        = null;
  private FrameLayout     mFrameLayout        = null;
  private LinearLayout    mSupportMenuContainer  = null;
  private FrameLayout     mFragmentContainer  = null;
  private int             mFragmentContainerId  = 0;
  private SupportButton   mSupportButton = null;
  private View            mMenuView = null;
  private View            displayView = null;
  private Integer         desiredMenuType = -1;
  private String          mJSON = null;
  private String          mDesiredMenuString = "";
  private String          mCustomerJSON = "";
  private String          mAppearanceJSON = "";


  public void initialize(CordovaInterface cordova, CordovaWebView webView) {
    super.initialize(cordova, webView);

    cordovaActivity = cordova.getActivity();
    mWebView = webView;
    mContext = mWebView.getContext();
    mView = mWebView.getView();
    mContext = cordovaActivity.getApplicationContext();
    mResources = cordovaActivity.getResources();
    mPackageName = cordovaActivity.getPackageName();
    mFrameLayout = (FrameLayout) mView.getParent();
    EventManager.setContext(mContext);
  }


  private String getContentsOfFile(String file) {
   String contents = null;
   String baseURLstr = "cdvfile://localhost/assets/www/" + file;
   CordovaResourceApi.OpenForReadResult result = null;
   try {
     FileUtils fileUtils = FileUtils.getFilePlugin();
     String fname = fileUtils.filesystemPathForURL(baseURLstr);
     String fileUrl = "file://" + fname;
     LocalFilesystemURL newUrl = LocalFilesystemURL.parse(fileUrl);
     Uri uri = Uri.parse(fileUrl);
     CordovaResourceApi resourceApi = mWebView.getResourceApi();
     result = resourceApi.openForRead(uri, true);
     long length = result.length;
     if (length > 0) {
       int ch;
       StringBuilder sb = new StringBuilder();
       while ((ch = result.inputStream.read()) != -1) {
         sb.append((char) ch);
       }
       contents = sb.toString();
     }
   } catch (Exception e) {
   }
   result = null;

   return contents;
 }



  @Override
  public boolean execute(String action, JSONArray args, CallbackContext callbackContext ) throws JSONException {
    callback = callbackContext;
    if ("configureAppearance".equals(action)) {
      configureAppearance(args.getString(0), callbackContext);
      return true;
    }
    if ("initiateBoomtown".equals(action)) {
      initiateBoomtown(args.getString(0), args.getString(1), callbackContext);
      return true;
    }
    else if ("initiateBoomtownWithAppearance".equals(action)) {
      initiateBoomtownWithAppearance(args.getString(0), args.getString(1), args.getString(2), callbackContext);
      return true;
    }
    else if ("initiateBoomtownWithCustomerAndAppearance".equals(action)) {
      initiateBoomtownWithCustomerAndAppearance(args.getString(0), args.getString(1), args.getString(2), args.getString(3), callbackContext);
      return true;
    }
    else if ("sendRequest".equals(action)) {
      String type = args.getString(0);
      JSONObject userInfo = args.getJSONObject(1);
      sendRequest(type, userInfo, callbackContext);
      return true;
    }
    else if ("displayMenu".equals(action)) {
      displayMenu(args.getString(0), callbackContext);
      return true;
    }
    else if ("settings".equals(action)) {
        settings(args.getString(0), callbackContext);
        return true;
    }

      return false;
  }


  private void loadConfigurationFromJSON(String json, String desiredMenuString, CallbackContext callbackContext) {
    if (json == null || json.length() == 0) {
      PluginResult result = new PluginResult(PluginResult.Status.ERROR, "No configuration provided." );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);
    } else {
      mJSON = json;
      mDesiredMenuString = desiredMenuString;
      Intent intent = new Intent(cordovaActivity, SupportActivity.class);
      if ( intent != null ) {
        intent.putExtra("JSON", json);
        if ( desiredMenuString != null ) {
          intent.putExtra("desiredMenuString", desiredMenuString);
        }
        cordovaActivity.startActivityForResult(intent, 999);
      }
    }
  }


  private void initiateBoomtown(String json, String desiredMenuString, CallbackContext callbackContext) {
    loadConfigurationFromJSON(json, desiredMenuString, callbackContext);
  }


  private void loadConfigurationWithAppearance(String json, String uiJSON, String desiredMenuString, CallbackContext callbackContext) {
    if ( mJSON == null && (json == null || json.length() == 0)  ) {
        // callbackContext.error("No configuration provided.");
      PluginResult result = new PluginResult(PluginResult.Status.ERROR, "No configuration provided." );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);
    } else {
      mJSON = json;
      mAppearanceJSON = uiJSON;

      mDesiredMenuString = desiredMenuString;
      Intent intent = new Intent(cordovaActivity, SupportActivity.class);
      if ( intent != null ) {
        intent.putExtra("JSON", mJSON);
        if ( mAppearanceJSON != null ) {
          intent.putExtra("appearanceJSON", mAppearanceJSON);
        }

        if ( desiredMenuString != null ) {
          intent.putExtra("desiredMenuString", desiredMenuString);
        }
        cordovaActivity.startActivityForResult(intent, 999);
      }
    }
  }

  private void loadConfigurationWithCustomerAndAppearance(String json, String customerJSON, String uiJSON, String desiredMenuString, CallbackContext callbackContext) {
    if ( mJSON == null && (json == null || json.length() == 0)  ) {
        // callbackContext.error("No configuration provided.");
      PluginResult result = new PluginResult(PluginResult.Status.ERROR, "No configuration provided." );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);
    } else {
      mJSON = json;
      mCustomerJSON = customerJSON;
      mAppearanceJSON = uiJSON;

      mDesiredMenuString = desiredMenuString;
      Intent intent = new Intent(cordovaActivity, SupportActivity.class);
      if ( intent != null ) {
        intent.putExtra("JSON", mJSON);
        if ( mCustomerJSON != null ) {
          intent.putExtra("customerJSON", mCustomerJSON);
        }
        if ( mAppearanceJSON != null ) {
          intent.putExtra("appearanceJSON", mAppearanceJSON);
        }

        if ( desiredMenuString != null ) {
          intent.putExtra("desiredMenuString", desiredMenuString);
        }
        cordovaActivity.startActivityForResult(intent, 999);
      }
    }
  }

  private void initiateBoomtownWithAppearance(String json,  String uiJSON, String desiredMenuString, CallbackContext callbackContext) {
    loadConfigurationWithAppearance(json, uiJSON, desiredMenuString, callbackContext);
  }

  private void initiateBoomtownWithCustomerAndAppearance(String json,  String customerJSON, String uiJSON, String desiredMenuString, CallbackContext callbackContext) {
    loadConfigurationWithCustomerAndAppearance(json, customerJSON, uiJSON, desiredMenuString, callbackContext);
  }

  private void configureAppearance(String appearanceJSON, CallbackContext callbackContext) {
    if ( appearanceJSON != null ) {
      mAppearanceJSON = appearanceJSON;
      PluginResult result = new PluginResult(PluginResult.Status.OK, "OK" );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);
    } else {
      PluginResult result = new PluginResult(PluginResult.Status.ERROR, "ERROR" );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);
    }
  }


  private void sendRequest(String request, JSONObject userInfo, CallbackContext callbackContext) {
  if ( request != null ) {
      EventManager.notify(request, userInfo);
      PluginResult result = new PluginResult(PluginResult.Status.OK, "OK" );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);
    } else {
      PluginResult result = new PluginResult(PluginResult.Status.ERROR, "ERROR" );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);

    }
  }


  private void displayMenu(String menuTypeString, CallbackContext callbackContext) {
    if ( mJSON != null ) {
      loadConfigurationFromJSON(mJSON, menuTypeString, callbackContext);
    } else {
      PluginResult result = new PluginResult(PluginResult.Status.ERROR, "ERROR" );
      result.setKeepCallback(true);
      callbackContext.sendPluginResult(result);

    }
  }


    private void settings(String arg, CallbackContext callbackContext) {
        if ( mJSON != null ) {
            loadConfigurationFromJSON(mJSON, null, callbackContext);
        } else {
            PluginResult result = new PluginResult(PluginResult.Status.ERROR, "ERROR" );
            result.setKeepCallback(true);
            callbackContext.sendPluginResult(result);

        }
    }



    @Override
  public void onActivityResult(int requestCode, int resultCode, Intent data)
  {
    if( requestCode == 999 )
    {
      if( resultCode == Activity.RESULT_OK )
      {
        PluginResult result = new PluginResult(PluginResult.Status.OK, "all done");
        result.setKeepCallback(true);
        callback.sendPluginResult(result);
      }
      else
      {
        PluginResult result = new PluginResult(PluginResult.Status.ERROR, "NO_RESULT_ERROR" );
        result.setKeepCallback(true);
        callback.sendPluginResult(result);
      }
    }
  }


  private void toast(final String msg) {
    cordovaActivity.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        Toast.makeText(cordovaActivity, msg, Toast.LENGTH_SHORT).show();
      }
    });
  }

  @Override
  public void supportButtonDidFailWithError(final String description, final String reason) {
  }

  @Override
  public void supportButtonDidGetSettings() {
    PluginResult result = new PluginResult(PluginResult.Status.OK, "didGetSettings");
    result.setKeepCallback(false);
    callback.sendPluginResult(result);
  }

  @Override
  public void supportButtonDidFailToGetSettings() {
    PluginResult result = new PluginResult(PluginResult.Status.ERROR, "didFailToGetSettings" );
    result.setKeepCallback(false);
    callback.sendPluginResult(result);
  }

  @Override
  public void supportButtonDidRetrieveAccount(HashMap<String, String> accountInfo) {

  }

  @Override
  public void supportButtonDidFailToRetrieveAccount(String message) {
  }


  @Override
  public void supportButtonDidCompleteTask() {
  }


  @Override
  public void supportButtonDidRequestExit() {
     if ( displayView != null ) {
         mSupportMenuContainer.removeView(displayView);
         displayView = null;
     }
   }


  @Override
  public void supportButtonDisplayView(final View view) {
      mMenuView = view;
      int i = 1;
  }


  @Override
  public void supportButtonDisplayFragment(final Fragment fragment, String title) {
    int i = 1;
  }

  @Override
  public void supportButtonSetTitle(String title) {
  }


  @Override
  public void supportButtonRemoveFragment(Fragment fragment) {
  }

  @Override
  public void supportButtonDidAdvertiseService() {
  }

  @Override
  public void supportButtonDidFailToAdvertiseService() {
  }


}
