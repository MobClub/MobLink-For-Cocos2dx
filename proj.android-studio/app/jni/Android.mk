LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../../Classes/AppDelegate.cpp \
					../../../Classes/HelloWorldScene.cpp \
					../../../Classes/C2DXMobLink/C2DXMobLink.cpp \
					../../../Classes/C2DXMobLink/C2DXMobLinkScene.cpp \
					../../../Classes/C2DXMobLink/C2DXMobLinkCallBack.cpp \
					../../../Classes/C2DXMobLink/Android/C2DXAndroidMobLink.cpp \
					../../../Classes/C2DXMobLink/Android/C2DXAndroidActionListener.cpp \
					../../../Classes/C2DXMobLink/Android/com_mob_moblink_cocos2dx_ActionListener.cpp \
					../../../Classes/C2DXMobLink/Android/JSON/CCJSONConverter.cpp \
					../../../Classes/C2DXMobLink/Android/JSON/cJSON/cJSON.c




LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON \
                    $(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON/cJSON

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
