# dreambox-mips32el.inc

BOX_BRAND = "dreambox"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

MTD_KERNEL = "mtd2"

require conf/machine/include/dreambox.inc
require conf/machine/include/mips/tune-mips32.inc

DVBMEDIASINK_CONFIG = "--with-pcm --with-wma --with-wmv --with-dtsdownmix --with-eac3 --with-dts"
DVBMEDIASINK_CONFIG:dm8000 = "--with-pcm --with-wma --with-wmv --with-dtsdownmix --with-eac3 --with-dts --with-limited-mpeg4v2 --with-amr"

CFLAGS:append:pn-titan = " -DDREAMBOX "

KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

MACHINE_FEATURES += "dreamboxlib"
