package com.mob.moblink.cocos2dx;

import android.util.Log;

import com.mob.moblink.Scene;

public class RestoreSceneListener extends Object implements com.mob.moblink.SceneRestorable {
	private static final String TAG = "RestoreSceneListener";
	private int cxxObject;

	public RestoreSceneListener() {
		super();
		cxxObject = nativeOnCreateCxxObject();
		Log.d(TAG, "create cxxObject. cxxObject: " + cxxObject);
	}

	@Override
	public void onReturnSceneData(Scene result) {
		Log.d(TAG, "onReturnSceneData(). scene: {path: " + result.getPath() +
				", params: " + LogUtil.convertMaptoString(result.getParams()) + "}");
//		nativeOnReturnSceneData(activity, result);
		nativeOnReturnSceneData(result);
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		nativeOnDestoryCxxObject();
	}

	private native int nativeOnCreateCxxObject();
//	private native int nativeOnReturnSceneData(Activity activity, Scene string);
	private native int nativeOnReturnSceneData(Scene string);
	private native int nativeOnDestoryCxxObject();

	public int getCxxObject() {
		Log.d(TAG, "get cxxObject. cxxObject: " + cxxObject);
		return cxxObject;
	}

	public static RestoreSceneListener newInstance() {
		return new RestoreSceneListener();
	}
}
