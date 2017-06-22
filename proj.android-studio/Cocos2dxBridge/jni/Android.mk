LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

COCOS2D_ROOT := ../../../cocos2d

LOCAL_MODULE := moblink_bridge
LOCAL_MODULE_FILENAME := libmoblinbridge

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := 	../../../Classes/C2DXMobLink/C2DXMobLink.cpp \
					../../../Classes/C2DXMobLink/C2DXMobLinkScene.cpp \
					../../../Classes/C2DXMobLink/C2DXMobLinkCallBack.cpp \
					../../../Classes/C2DXMobLink/Android/C2DXAndroidMobLink.cpp \
					../../../Classes/C2DXMobLink/Android/C2DXAndroidActionListener.cpp \
					../../../Classes/C2DXMobLink/Android/com_mob_moblink_cocos2dx_ActionListener.cpp \
					../../../Classes/C2DXMobLink/Android/C2DXAndroidRestoreSceneListener.cpp \
					../../../Classes/C2DXMobLink/Android/com_mob_moblink_cocos2dx_RestoreSceneListener.cpp \
					../../../Classes/C2DXMobLink/Android/JSON/CCJSONConverter.cpp \
					../../../Classes/C2DXMobLink/Android/JSON/cJSON/cJSON.c

					
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(COCOS2D_ROOT)/cocos \
					$(LOCAL_PATH)/$(COCOS2D_ROOT)/cocos/platform/android \
					$(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON \
                    $(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON/cJSON
					
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../Classes/C2DXMobLink \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android \
					$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON \
                    $(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON/cJSON
					

include $(BUILD_STATIC_LIBRARY)

