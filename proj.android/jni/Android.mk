LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/plugin/publish)
$(call import-add-path,$(LOCAL_PATH))

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/AchiScene.cpp \
../../Classes/MainScene.cpp \
../../Classes/ShopScene.cpp \
../../Classes/AdmobHelper.cpp


LOCAL_LDLIBS := -landroid -llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/plugin/publish/protocols/android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/plugin/publish/protocols/include

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic PluginGoogleAnalytics sdkbox

include $(BUILD_SHARED_LIBRARY)

$(call import-module,plugin/protocols/proj.android/jni)
$(call import-module,cocos)
$(call import-module, ./sdkbox)
$(call import-module, ./plugingoogleanalytics)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END


