package com.goboomtown.plugin.supportsdk;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;
import android.content.Context;
import android.widget.Toast;

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

import java.util.HashMap;
import java.util.Map;

public class SupportSDK extends CordovaPlugin {

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
  }


  @Override
  public boolean execute(String action, JSONArray args, CallbackContext callbackContext ) throws JSONException {
    callback = callbackContext;
    if ("loadConfigurationFromJSON".equals(action)) {
      loadConfigurationFromJSON(args.getString(0), callbackContext);
      return true;
    }
    return false;
  }

  private void loadConfigurationFromJSON(String json, CallbackContext callbackContext) {
    if (json == null || json.length() == 0) {
      callbackContext.error("No configuration provided.");
    } else {
      Intent intent = new Intent(cordovaActivity, SupportActivity.class);
      if ( intent != null ) {
        intent.putExtra("JSON", json);
        cordovaActivity.startActivityForResult(intent, 999);
      }
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


//  private void customLayout() {
//    cordova.getActivity().runOnUiThread(new Runnable() {
//      @Override
//      public void run() {
//        cordovaActivity.setContentView(mResources.getIdentifier("layout", "layout", mPackageName));
////        mFragmentContainer = cordovaActivity.getContentView().findViewById(R.id.fragment_container);
//        mFragmentContainerId = mResources.getIdentifier("fragment_container", "id", mPackageName);
//        mFragmentContainer = mView.findViewById(mFragmentContainerId);
//
//        int mSupportMenuContainerId = mResources.getIdentifier("supportMenuContainer", "id", mPackageName);
//        mSupportMenuContainer = mView.findViewById(mSupportMenuContainerId);
//
////        LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
////        mMainView = inflater.inflate(R.layout.layout, null);
////        mView.addView(mMainView);
////        cordovaActivity.setContentView(resources.getIdentifier("layout", "layout", packageName));
//      }
//    });
//  }

  private void toast(final String msg) {
    cordovaActivity.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        Toast.makeText(cordovaActivity, msg, Toast.LENGTH_SHORT).show();
      }
    });
  }

}
