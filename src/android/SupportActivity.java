package com.goboomtown.plugin.supportsdk;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;

import android.widget.Toast;

import android.content.BroadcastReceiver;
import com.goboomtown.supportsdk.api.EventManager;

import com.goboomtown.supportsdk.view.SupportButton;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;
import androidx.appcompat.app.ActionBar;

import android.graphics.Color;

import android.provider.Settings;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.RelativeLayout;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.Resources;


import java.io.File;
import java.util.HashMap;
import java.util.Map;
import androidx.fragment.app.FragmentActivity;

import org.json.JSONException;
import org.json.JSONObject;
import androidx.lifecycle.Lifecycle;



//public class SupportActivity extends AppCompatActivity

public class SupportActivity extends AppCompatActivity
        implements SupportButton.SupportButtonListener {

    public static final String TAG = "SupportActivity";

    private FrameLayout mFragmentContainer;
    private LinearLayout mSupportMenuContainer;
    private View mView;
    private SupportButton mSupportButton;
    private Resources     mResources;
    private String        mPackageName;
    private int           mFragmentContainerId;
    private View          mMenuView = null;
    private SupportButton.MenuStyle     desiredMenuType = SupportButton.MenuStyle.ICON_LIST_EXIT;
    private String        mCustomerJSON = null;
    private String        mAppearanceJSON = null;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mResources = getResources();
        mPackageName = getPackageName();

        int as_id = mResources.getIdentifier("activity_support", "layout", mPackageName);
        setContentView(as_id);

        hideActionBar();

        int tb_id = mResources.getIdentifier("toolbar", "id", mPackageName);
        Toolbar toolbar = findViewById(tb_id);

        int mSupportMenuContainerId = mResources.getIdentifier("supportMenuContainer", "id", mPackageName);
        mSupportMenuContainer = findViewById(mSupportMenuContainerId);

        mFragmentContainerId = mResources.getIdentifier("fragment_container", "id", mPackageName);

        mFragmentContainer = findViewById(mFragmentContainerId);

        int logoViewId = mResources.getIdentifier("logoImageView", "id", mPackageName);
        int logoId = mResources.getIdentifier("custom_logo", "drawable", mPackageName);
        ImageView logoView = findViewById(logoViewId);
        if ( logoView != null ) {
            logoView.setImageDrawable(getResources().getDrawable(logoId));
        }

        int sb_id = mResources.getIdentifier("supportButton", "id", mPackageName);
        mSupportButton = findViewById(sb_id);
        mSupportButton.setVisibility(View.GONE);
        mSupportButton.setListener(this);

        mCustomerJSON = getIntent().getStringExtra("customerJSON");
        mAppearanceJSON = getIntent().getStringExtra("appearanceJSON");
        if ( mAppearanceJSON != null ) {
          mSupportButton.appearance.configureFromJSON(mAppearanceJSON);
        }

        String json = getIntent().getStringExtra("JSON");
        String desiredMenuString = getIntent().getStringExtra("desiredMenuString");
        try {
          desiredMenuType = menuType(Integer.parseInt(desiredMenuString));
        } catch (Exception e) {
        }

        mSupportButton.loadConfiguration(json, mCustomerJSON);

        Map<String, String> myPubData = new HashMap<>();
        myPubData.put("public", "fooData");
        Map<String, String> myPrivData = new HashMap<>();
        myPrivData.put("private", "someEncryptedData");

        mSupportButton.advertiseServiceWithPublicData(myPubData, myPrivData);

        EventManager.addObserver(mEventReceiver);
    }


  private SupportButton.MenuStyle menuType(int desiredMenuType) {
    SupportButton.MenuStyle style = SupportButton.MenuStyle.ICON_LIST_EXIT;
    switch(desiredMenuType) {
      case 0:
        style = SupportButton.MenuStyle.NO_MENU;
        break;
      case 1:
        style = SupportButton.MenuStyle.MENU;
        break;
      case 2:
        style = SupportButton.MenuStyle.BUTTON;
        break;
      case 3:
        style = SupportButton.MenuStyle.ICON_LIST;
        break;
      case 4:
        style = SupportButton.MenuStyle.ICON_LIST_EXIT;
        break;
      case 5:
        style = SupportButton.MenuStyle.ICON_GRID;
        break;
      default:
        style = SupportButton.MenuStyle.ICON_LIST_EXIT;
        break;
    }
    return style;
  }

  private void toast(final String msg) {
    final Activity activity = this;
    runOnUiThread(new Runnable() {
      @Override
      public void run() {
        Toast.makeText(activity, msg, Toast.LENGTH_SHORT).show();
      }
    });
  }

  private void alert(JSONObject userInfo) {
    if ( !getLifecycle().getCurrentState().isAtLeast(Lifecycle.State.STARTED) ) {
       return;
   }
     runOnUiThread(new Runnable() {
           @Override
           public void run() {
               String title = null;
               String message = null;
               String positiveButtonTitle = null;
               String negativeButtonTitle = null;
               try {
                   title = userInfo.getString(EventManager.kRequestAlertTitle);
                   message = userInfo.getString(EventManager.kRequestAlertMessage);
                   positiveButtonTitle = userInfo.getString(EventManager.kRequestAlertPositiveButtonTitle);
                   negativeButtonTitle = userInfo.getString(EventManager.kRequestAlertNegativeButtonTitle);
               } catch (JSONException e) {

               }
               AlertDialog.Builder builder = new AlertDialog.Builder(SupportActivity.this, AlertDialog.THEME_HOLO_LIGHT);
               builder.setTitle(title);
               builder.setMessage(message);

               String defaultButtonTitle = null;
               if ( positiveButtonTitle==null || negativeButtonTitle==null ) {
                   defaultButtonTitle = positiveButtonTitle!=null ? positiveButtonTitle : negativeButtonTitle;
                   if ( defaultButtonTitle == null ) {
                       defaultButtonTitle = "OK";
                   }
               }
               if ( defaultButtonTitle != null ) {
                   DialogInterface.OnClickListener defaultOnClickListener = new DialogInterface.OnClickListener() {
                       @Override
                       public void onClick(DialogInterface dialog, int which) {
                           EventManager.notify(EventManager.kEventAlertDefaultClicked, null);
                       }
                   };
                   builder.setPositiveButton(defaultButtonTitle, defaultOnClickListener);
                   builder.setCancelable(true);
               } else {
                   builder.setPositiveButton(positiveButtonTitle, new DialogInterface.OnClickListener() {
                       @Override
                       public void onClick(DialogInterface dialog, int which) {
                           EventManager.notify(EventManager.kEventAlertPositiveClicked, null);
                       }
                   });
                   builder.setNegativeButton(negativeButtonTitle, new DialogInterface.OnClickListener() {
                       @Override
                       public void onClick(DialogInterface dialog, int which) {
                           EventManager.notify(EventManager.kEventAlertNegativeClicked, null);
                       }
                   });
                   builder.setCancelable(false);
               }

               final AlertDialog dlg = builder.create();
               if (dlg != null) {
                   dlg.show();
                   EventManager.notify(EventManager.kEventAlertPresented, null);
               }
           }
       });

   }


    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        setResult(RESULT_OK, null);
    }


    @Override
    public void onBackPressed() {
        int count = getSupportFragmentManager().getBackStackEntryCount();

        if ( count > 0 ) {
            getSupportFragmentManager().popBackStack();
            if ( count == 1 ) {
                hideActionBar();
                mFragmentContainer.setVisibility(View.GONE);
                mSupportButton.click();
            }
            count = getSupportFragmentManager().getBackStackEntryCount();
        } else {
            hideActionBar();
            mFragmentContainer.setVisibility(View.GONE);
            super.onBackPressed();
        }
    }

    private void showActionBar() {
        ActionBar actionBar = getSupportActionBar();
        if ( actionBar != null ) {
            actionBar.show();
        }
    }

    private void hideActionBar() {
        ActionBar actionBar = getSupportActionBar();
        if ( actionBar != null ) {
            actionBar.hide();
        }
    }


    @Override
    public void supportButtonDidFailWithError(final String description, final String reason) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AlertDialog.Builder builder = new AlertDialog.Builder(SupportActivity.this, AlertDialog.THEME_HOLO_LIGHT);
                builder.setTitle(description);
                builder.setMessage(reason);
                builder.setCancelable(false);

                builder.setPositiveButton("OK", null);

                final AlertDialog dlg = builder.create();
                if (dlg != null) {
                    dlg.show();
                }
            }
        });
    }

    @Override
    public void supportButtonDidGetSettings() {
        Log.d(TAG, "#helpButtonDidGetSettings");
        mSupportButton.menuStyle = desiredMenuType;
        mSupportButton.click();
    }

    @Override
    public void supportButtonDidFailToGetSettings() {
      toast("Unable to retrieve settings");
    }

    @Override
    public void supportButtonDidRetrieveAccount(HashMap<String, String> accountInfo) {

    }

    @Override
    public void supportButtonDidFailToRetrieveAccount(String message) {
    }

    @Override
     public void supportButtonDidCompleteTask() {
         mSupportButton.click();
     }


    @Override
    public void supportButtonDidRequestExit() {
       if ( mMenuView != null ) {
           mSupportMenuContainer.removeView(mMenuView);
           mMenuView = null;
       }
       finish();
     }


    @Override
    public void supportButtonDisplayView(final View view) {
        if ( view == null ) {
          return;
        }
        mMenuView = view;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mSupportMenuContainer.addView(mMenuView);
            }
        });
    }


    @Override
    public void supportButtonDisplayFragment(final Fragment fragment, String title) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                getSupportFragmentManager().beginTransaction()
                        .add(mFragmentContainerId, fragment)
                        .addToBackStack(null)
                        .commit();
                showActionBar();
                if ( title != null ) {
                    setTitle(title);
                }
                mFragmentContainer.setVisibility(View.VISIBLE);
            }
        });
    }


//    private void kill() {
//        final Handler handler = new Handler(Looper.getMainLooper());
//        handler.postDelayed(new Runnable() {
//            @Override
//            public void run() {
//                //Do something after 100ms
//                EventManager.notify(EventManager.kRequestChatExitResolveIssue, null);
//            }
//        }, 10000);
//    }


    @Override
    public void supportButtonSetTitle(String title) {
        setTitle(title);
    }


    @Override
    public void supportButtonRemoveFragment(Fragment fragment) {
        getSupportFragmentManager().popBackStack();
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mFragmentContainer.setVisibility(View.GONE);
                hideActionBar();
                if ( mSupportButton.menuStyle == SupportButton.MenuStyle.MENU ) {
                  mSupportButton.showSupportDialog();
                }
            }
        });
    }

    @Override
    public void supportButtonDidAdvertiseService() {
        Log.i(TAG, "service advertised successfully");
    }

    @Override
    public void supportButtonDidFailToAdvertiseService() {
        Log.i(TAG, "error when advertising service");
    }

    private BroadcastReceiver mEventReceiver = new BroadcastReceiver() {
      @Override
      public void onReceive(Context context, final Intent intent) {
        String intentAction = null;
        if (intent != null) {
            intentAction = intent.getAction();
        }
        Log.d(TAG, "msg received with intent: " + intentAction);

        if (EventManager.kSupportSDKEvent.equals(intentAction)) {

            String type = intent.getStringExtra(EventManager.kSupportSDKEventType);
            Log.d(TAG, "msg received with type: " + type );
            String userInfoString = intent.getStringExtra(EventManager.kSupportSDKEventData);
            JSONObject userInfo = null;
            try {
                if (userInfoString != null) {
                    userInfo = new JSONObject(userInfoString);
                }
            } catch(JSONException e) {

            }
            if ( type.equals(EventManager.kRequestToast) ) {

            } else if ( type.equals(EventManager.kRequestAlert) ) {
                alert(userInfo);
            }

        }
      }
  };

}
