package com.mob.moblink.cocos2dx;

import android.app.Activity;
import android.util.Log;

import com.mob.MobApplication;
import com.mob.moblink.MobLink;
import com.mob.moblink.Scene;

public class MobLinkCocosApplication extends MobApplication {
	private static final String TAG = "MobLinkCocosApplication";

	@Override
	public void onCreate() {
		super.onCreate();

		// 指定Cocos的Activity，否则无法跳转
		Log.d(TAG, "Set RestoreSceneListener to specify AppActivity to be target activity");
		MobLink.setRestoreSceneListener(new com.mob.moblink.RestoreSceneListener() {
			@Override
			public Class<? extends Activity> willRestoreScene(Scene scene) {
				Class cocosClazz = null;
				try {
					cocosClazz = Class.forName("org.cocos2dx.cpp.AppActivity");
				} catch (ClassNotFoundException e) {
					Log.e(TAG, "Can not initialize AppActivity", e);
				}
				return cocosClazz;
			}

			@Override
			public void completeRestore(Scene scene) {
				Log.d(TAG, "Restore scene completed.");
			}

			@Override
			public void notFoundScene(Scene scene) {

			}
		});
	}
}
