LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libmoblinkbridge
LOCAL_SRC_FILES := libmoblinkbridge.a
LOCAL_EXPORT_C_INCLUDES  := $(LOCAL_PATH)/C2DXMobLinkH

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../../Classes/AppDelegate.cpp \
					../../../Classes/HelloWorldScene.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES := libmoblinkbridge

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

