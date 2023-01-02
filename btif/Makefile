$(info [bt_drv] btif/Makefile start M=$(M))

define build_kernel_modules
$(MAKE) -C $(KERNEL_SRC) M=$(M)/../$(1) modules $(KBUILD_OPTIONS) BT_PLATFORM=$(1) LOG_TAG=$(PRIVATE_LOG_TAG) KBUILD_EXTRA_SYMBOLS="$(EXTRA_SYMBOLS)"
endef

define install_kernel_modules
$(MAKE) M=$(M)/../$(1) -C $(KERNEL_SRC) modules_install
endef

define clean_kernel_modules
$(MAKE) -C $(KERNEL_SRC) M=$(M)/../$(1) clean
endef

LOG_TAG := [BT_Drv][btif]

ifneq ($(wildcard $(KERNEL_SRC)/$(DEVICE_MODULES_REL_DIR)/Makefile.include),)
include $(KERNEL_SRC)/$(DEVICE_MODULES_REL_DIR)/Makefile.include
extra_symbols := $(abspath $(OUT_DIR)/../vendor/mediatek/kernel_modules/connectivity/conninfra/Module.symvers)
extra_symbols += $(abspath $(OUT_DIR)/../vendor/mediatek/kernel_modules/connectivity/connfem/Module.symvers)
else
extra_symbols := $(abspath $(O)/../vendor/mediatek/kernel_modules/connectivity/conninfra/Module.symvers)
extra_symbols += $(abspath $(O)/../vendor/mediatek/kernel_modules/connectivity/connfem/Module.symvers)
endif

all: PRIVATE_LOG_TAG := $(LOG_TAG)
all: EXTRA_SYMBOLS  += $(extra_symbols)
all:
	$(call build_kernel_modules,6885)
	$(call build_kernel_modules,6893)
	$(call build_kernel_modules,6877)
	$(call build_kernel_modules,6983)
	$(call build_kernel_modules,6879)
	$(call build_kernel_modules,6895)
	$(call build_kernel_modules,6886)

modules_install:
	$(call install_kernel_modules,6885)
	$(call install_kernel_modules,6893)
	$(call install_kernel_modules,6877)
	$(call install_kernel_modules,6983)
	$(call install_kernel_modules,6879)
	$(call install_kernel_modules,6895)
	$(call install_kernel_modules,6886)

clean:
	$(call clean_kernel_modules,6885)
	$(call clean_kernel_modules,6893)
	$(call clean_kernel_modules,6877)
	$(call clean_kernel_modules,6983)
	$(call clean_kernel_modules,6879)
	$(call clean_kernel_modules,6895)
	$(call clean_kernel_modules,6886)


$(info [bt_drv] btif/Makefile end)

