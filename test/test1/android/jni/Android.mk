LOCAL_PATH := $(call my-dir)
MY_PATH := $(call my-dir)
GUIEX_Root := $(LOCAL_PATH)/../../../..

#librarys
include $(CLEAR_VARS)
include $(GUIEX_Root)/Android.mk

#this project
LOCAL_PATH := $(MY_PATH)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(GUIEX_INCLUDES)
LOCAL_STATIC_LIBRARIES := $(GUIEX_STATIC_LIBRARIES)

LOCAL_MODULE := test1
LOCAL_SRC_FILES := ../../test1.cpp

LOCAL_LDLIBS := $(GUIEX_LDLIBS)

include $(BUILD_SHARED_LIBRARY)
