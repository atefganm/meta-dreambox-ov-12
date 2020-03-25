DEPENDS = "libgcc"
PROVIDES = "linux-dreambox"
PE = "1"

PACKAGE_ARCH = "${MACHINE_ARCH}"

require recipes-bsp/linux/linux-dreambox-one.inc

SRC_URI = "https://dreamboxupdate.com/download/opendreambox/linux-meson64/linux-meson64-v${PV}.tar.xz \
    file://${OPENVISION_BASE}/meta-openvision/recipes-linux/kernel-patches/kernel-add-support-for-gcc9.patch \
    "

SRC_URI[md5sum] = "d5770c1cf86b093cb17fa6dafce03ff9"
SRC_URI[sha256sum] = "258e542be44bef8a36fe63fc963e1c8e14a6e549bafd4e1cb44817aedea9a7d8"

KERNEL_CC += "${TOOLCHAIN_OPTIONS}"
KERNEL_LD += "${TOOLCHAIN_OPTIONS}"

S = "${WORKDIR}/linux-meson64-v${PV}"

CMDLINE = "${@kernel_console(d)} root=/dev/mmcblk0p7 rootwait rootfstype=ext4 no_console_suspend"

COMPATIBLE_MACHINE = "^(dreamone)$"

DEFCONFIG = "meson64"

LINUX_VERSION = "4.9"
KERNEL_DEVICETREE = "dreamone.dtb"
KERNEL_IMAGETYPES = "Image.gz"

export KCFLAGS = "-Wno-error=misleading-indentation \
                  -Wno-error=parentheses \
                  -Wno-error=shift-overflow \
                  -Wno-error=unused-const-variable \
                  -Wno-error=array-bounds \
                  -Wno-error=address-of-packed-member \
                  -Wno-error=maybe-uninitialized \
                  -Wno-error=missing-attributes \
                  -Wno-error=unused-variable \
                  -Wno-error=stringop-overflow \
                  "

do_configure_append(){
    sed -i "s/(none)/${MACHINE}/" "${WORKDIR}/defconfig"
}

do_compile_append() {
    if test -n "${KERNEL_DEVICETREE}"; then
    	for DTB in ${KERNEL_DEVICETREE}; do
    		if echo ${DTB} | grep -q '/dts/'; then
    			bbwarn "${DTB} contains the full path to the the dts file, but only the dtb name should be used."
    			DTB=`basename ${DTB} | sed 's,\.dts$,.dtb,g'`
    		fi
    		oe_runmake ${DTB}
    	done
    	# Create directory, this is needed for out of tree builds
    	mkdir -p ${B}/arch/arm64/boot/dts/amlogic/
    	cp ${B}/arch/arm64/boot/dts/amlogic/${KERNEL_DEVICETREE} ${B}/arch/arm64/boot/
    fi
}

KERNEL_FLASH_ARGS = "-c '${CMDLINE}'"
