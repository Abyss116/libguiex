LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:=guiex_sample
LOCAL_SRC_FILES := ../../../common_android/common_android.cpp \
	../../testparticle2d.cpp



include ../../android_library.mk

include $(BUILD_SHARED_LIBRARY)

include ../../android_import_module.mk
