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

//public class SupportActivity extends AppCompatActivity

public class SupportView extends FrameLayout
        implements SupportButton.SupportButtonListener {

    public static final String TAG = "SupportView";

    private FrameLayout mFragmentContainer;
    private LinearLayout mSupportMenuContainer;
    private View mView;
    private SupportButton mSupportButton;
    private Resources     mResources;
    private String        mPackageName;
    private int           mFragmentContainerId;
    private View          mMenuView = null;
    private SupportButton.MenuStyle     desiredMenuType = SupportButton.MenuStyle.ICON_LIST_EXIT;

    public SupportView(Context context, Resources resources, String packageName) {
        super(context);
        mContext = context;
        mResources = resources;
        mPackageName = packageName;
        setup();
    }

    private void setup() {
        View view = inflate(mContext, R.layout.support_menu_item, this);

        int mSupportMenuContainerId = mResources.getIdentifier("supportMenuContainer", "id", mPackageName);
        mSupportMenuContainer = findViewById(mSupportMenuContainerId);

        mFragmentContainerId = mResources.getIdentifier("fragment_container", "id", mPackageName);

        // mFragmentContainer = findViewById(R.id.fragment_container);
        mFragmentContainer = findViewById(mFragmentContainerId);

        int sb_id = mResources.getIdentifier("supportButton", "id", mPackageName);
        // mSupportButton = findViewById(R.id.supportButton);
        mSupportButton = findViewById(sb_id);
        mSupportButton.setVisibility(View.GONE);
        mSupportButton.setListener(this);

        mSupportButton.appearance.setIconColor(Color.RED);
        mSupportButton.appearance.setTextColor(Color.BLACK);

        String json = getIntent().getStringExtra("JSON");
        String desiredMenuString = getIntent().getStringExtra("desiredMenuString");
        // if ( desiredMenuString != null ) {
        //   desiredMenuType = menuType(Integer.parseInt(desiredMenuString));
        // } else {
        //   desiredMenuType = menuType(-1);
        // }
        try {
          desiredMenuType = menuType(Integer.parseInt(desiredMenuString));
        } catch (Exception e) {
          desiredMenuType = menuType(-1);
        }

        // int configResource = R.raw.support_sdk_preprod; // R.raw.support_sdk;
        // mSupportButton.loadConfiguration(configResource, null);
        mSupportButton.loadConfiguration(json, null);

        Map<String, String> myPubData = new HashMap<>();
        myPubData.put("public", "fooData");
        Map<String, String> myPrivData = new HashMap<>();
        myPrivData.put("private", "someEncryptedData");

        mSupportButton.advertiseServiceWithPublicData(myPubData, myPrivData);
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
            // setTitle(getString(R.string.app_name));
        }
        count = getSupportFragmentManager().getBackStackEntryCount();
    } else {
//            mFragmentContainer.setVisibility(View.GONE);
        hideActionBar();
        mFragmentContainer.setVisibility(View.GONE);
        // setTitle(getString(R.string.app_name));
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
//        mSupportButton.menuStyle = SupportButton.MenuStyle.BUTTON;
        mSupportButton.menuStyle = desiredMenuType;
        mSupportButton.click();
    }

    @Override
    public void supportButtonDidFailToGetSettings() {
      toast("Unable to retrieve settings");
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
        // runOnUiThread(new Runnable() {
        //     @Override
        //     public void run() {
        //         PopupWindow popupWindow = new PopupWindow();
        //         popupWindow.setWindowLayoutMode(
        //                 WindowManager.LayoutParams.WRAP_CONTENT,
        //                 WindowManager.LayoutParams.WRAP_CONTENT);
        //         popupWindow.setHeight(250);
        //         popupWindow.setWidth(350);
        //         popupWindow.setContentView(view);
        //
        //         //set content and background
        //
        //         popupWindow.setTouchable(true);
        //         popupWindow.setFocusable(true);
        //
        //         mSupportMenuContainer.setVisibility(View.VISIBLE);
        //         mFragmentContainer.setVisibility(View.GONE);
        //         popupWindow.showAtLocation(mFragmentContainer, Gravity.CENTER, 0, 0);
        //     }
        // });
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
                // mSupportMenuContainer.setVisibility(View.GONE);
                mFragmentContainer.setVisibility(View.VISIBLE);
            }
        });
//        startService(new Intent(this, SupportOverlayService.class));
    }

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
                // mSupportMenuContainer.setVisibility(View.VISIBLE);
                // setTitle(getString(R.string.app_name));
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
}
