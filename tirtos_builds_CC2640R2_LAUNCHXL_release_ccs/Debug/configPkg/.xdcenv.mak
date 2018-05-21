#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/simplelink_cc2640r2_sdk_1_50_00_58/source;D:/ti/simplelink_cc2640r2_sdk_1_50_00_58/kernel/tirtos/packages
override XDCROOT = D:/ti/xdctools_3_50_03_33_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/simplelink_cc2640r2_sdk_1_50_00_58/source;D:/ti/simplelink_cc2640r2_sdk_1_50_00_58/kernel/tirtos/packages;D:/ti/xdctools_3_50_03_33_core/packages;..
HOSTOS = Windows
endif
