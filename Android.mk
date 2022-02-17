
BT_PLATFORM=$(subst MTK_CONSYS_MT,,$(MTK_BT_CHIP))
$(info [BT_Drv] MTK_BT_CHIP=$(MTK_BT_CHIP))
$(info [BT_Drv] BT_PLATFORM=$(BT_PLATFORM))

ifeq ($(BT_PLATFORM), $(filter $(BT_PLATFORM), 6885 6893 6877))
  include $(call all-named-subdir-makefiles, btif)
else 
  include $(call all-named-subdir-makefiles, wmt)
endif
