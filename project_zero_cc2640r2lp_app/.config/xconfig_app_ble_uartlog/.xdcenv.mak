#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/tirtos/packages;D:/ti/ccsv8/ccs_base;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source/ti/blestack;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/packages;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;D:/HandsFree/project_zero_cc2640r2lp_app/.config
override XDCROOT = D:/ti/xdctools_3_50_03_33_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/tirtos/packages;D:/ti/ccsv8/ccs_base;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source/ti/blestack;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/packages;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;D:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;D:/HandsFree/project_zero_cc2640r2lp_app/.config;D:/ti/xdctools_3_50_03_33_core/packages;..
HOSTOS = Windows
endif
