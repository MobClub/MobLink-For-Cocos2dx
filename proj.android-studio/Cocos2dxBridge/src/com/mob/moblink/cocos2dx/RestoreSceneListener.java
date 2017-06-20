package com.mob.moblink.cocos2dx;

import android.app.Activity;

import org.json.JSONObject;

import java.util.HashMap;

public class RestoreSceneListener extends com.mob.moblink.AbstractRestoreSceneListener {

	private int cxxObject;

	public RestoreSceneListener() {
		super();
		cxxObject = nativeOnCreateCxxObject();
	}

	@Override
	public void onReturnSceneData(Activity activity, HashMap<String, Object> result) {
		JSONObject jsonObject = new JSONObject(result);
		String value = jsonObject.toString();
		nativeOnReturnSceneData(activity, value);
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		nativeOnDestoryCxxObject();
	}

	private native int nativeOnCreateCxxObject();
	private native int nativeOnReturnSceneData(Activity activity, String string);
	private native int nativeOnDestoryCxxObject();

	public int getCxxObject() {
		return cxxObject;
	}

	public static RestoreSceneListener newInstance() {
		return new RestoreSceneListener();
	}
}
