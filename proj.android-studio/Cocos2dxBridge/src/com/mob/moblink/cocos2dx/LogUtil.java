package com.mob.moblink.cocos2dx;

import java.util.Iterator;
import java.util.Map;

public class LogUtil {
	/**
	 * Convert map to string.
	 * <p>
	 * This method will call the toString() method of K and V.
	 *
	 * @param map the map to be output.
	 * @return the string result.
	 */
	public static String convertMaptoString(Map map) {
		if (map == null) {
			return "";
		}
		String str = "[";
		Iterator it = map.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry pair = (Map.Entry) it.next();
			str += " " + pair.getKey() + ":" + (pair.getValue() == null ? "" : pair.getValue());
		}
		return str + " ]";
	}
}
