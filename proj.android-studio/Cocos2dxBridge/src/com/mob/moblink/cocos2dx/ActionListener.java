package com.mob.moblink.cocos2dx;

/**
 * ActionListener for cocos2dx.<br/>
 * 使用demo, step by step:
 * <ul>
 *     <li>cxx代码, 创建本类的实例, 通过jni提示的方式</li>
 *     <li>通过getCxxObject获取cxx对象, 并对cxx对象进行配置</li>
 *     <li>传递此对象引用到MobLink中, 等待回调</li>
 *     <li>回调的方法通过native调用cxx对象对应的函数</li>
 *     <li>在cxx对象对应的函数中实现不同的需要</li>
 * </ul>
 *
 */
public class ActionListener extends Object implements com.mob.moblink.ActionListener<String> {
	private int cxxObject;

	public ActionListener() {
		super();
		cxxObject = nativeOnCreateCxxObject();
	}

	@Override
	public void onResult(String mid) {
		nativeOnResult(mid);
	}

	@Override
	public void onError(Throwable t) {
		String value = t.toString();
		nativeOnError(value);
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		nativeOnDestoryCxxObject();
	}

	private native int nativeOnCreateCxxObject();
	private native int nativeOnResult(String string);
	private native int nativeOnError(String string);
	private native int nativeOnDestoryCxxObject();

	public int getCxxObject() {
		return cxxObject;
	}

	public static ActionListener newInstance() {
		return new ActionListener();
	}
}
