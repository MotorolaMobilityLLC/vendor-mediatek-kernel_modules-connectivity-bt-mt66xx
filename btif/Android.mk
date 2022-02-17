LOCAL_PATH := $(call my-dir)

ifneq (true,$(strip $(TARGET_NO_KERNEL)))
$(info [BT_Drv][btif] build connac20 btif)

include $(CLEAR_VARS)
LOCAL_MODULE := bt_drv.ko
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_INIT_RC := init.bt_drv.rc
LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%,%,$(shell find $(LOCAL_PATH) -type f -name '*.[cho]')) Makefile
LOCAL_REQUIRED_MODULES := conninfra.ko
include $(MTK_KERNEL_MODULE)

BT_OPTS += BT_PLATFORM=$(BT_PLATFORM)
$(info [BT_Drv][btif] BT_OPTS = $(BT_OPTS))
$(linked_module): OPTS += $(BT_OPTS)

endif

