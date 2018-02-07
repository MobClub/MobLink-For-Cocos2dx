package com.mob.moblink.cocos2dx;

import android.app.Activity;
import android.content.Intent;

import com.mob.moblink.Scene;

public class RestoreSceneListener extends Object implements com.mob.moblink.RestoreSceneListener {

	private int cxxObject;

	public RestoreSceneListener() {
		super();
		cxxObject = nativeOnCreateCxxObject();
	}

	@Override
	public void onBeginCheckScene() {
		// do nothing
	}

	@Override
	public void onFinishCheckScene() {
		// do nothing
	}

	@Override
	public boolean onReturnSceneIntent(String var1, Intent var2) {
		return false;
	}

	@Override
	public void onReturnSceneData(Activity activity, Scene result) {
		nativeOnReturnSceneData(activity, result);
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		nativeOnDestoryCxxObject();
	}

	private native int nativeOnCreateCxxObject();
	private native int nativeOnReturnSceneData(Activity activity, Scene string);
	private native int nativeOnDestoryCxxObject();

	public int getCxxObject() {
		return cxxObject;
	}

	public static RestoreSceneListener newInstance() {
		return new RestoreSceneListener();
	}
}
