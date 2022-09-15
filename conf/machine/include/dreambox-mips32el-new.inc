# dreambox-mips32el-new.inc

KERNELVERSION = "3.4"

BOX_BRAND = "dreambox"

PREFERRED_PROVIDER_virtual/egl ?= "libvc5dream"
PREFERRED_PROVIDER_virtual/libgles1 ?= "libvc5dream"
PREFERRED_PROVIDER_virtual/libgles2 ?= "libvc5dream"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa-gl"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa-gl"
PREFERRED_VERSION_linux-dreambox = "${KERNELVERSION}"
PREFERRED_PROVIDER_jpeg ?= "libjpeg-turbo"
PREFERRED_PROVIDER_jpeg-native ?= "libjpeg-turbo-native"

MACHINE_EXTRA_RDEPENDS += "libvc5dream"

DREAMBOX_IMAGE_SIZE ??= "1024"

IMAGE_FSTYPES =+ "tar.xz"

IMAGE_CMD:tar:prepend = "\
	mkdir -p ${IMAGE_ROOTFS}/tmp; \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	mkdir -p ${IMAGE_ROOTFS}${localstatedir}/lib/opkg/info; \
	echo "#!/bin/sh" > ${IMAGE_ROOTFS}${localstatedir}/lib/opkg/info/dreambox-secondstage.postinst; \
	echo "[ -n \"$D\" ] || flash-ssbl /usr/share/dreambox-secondstage/ssbl.bin" >> ${IMAGE_ROOTFS}${localstatedir}/lib/opkg/info/dreambox-secondstage.postinst; \
	chmod 777 ${IMAGE_ROOTFS}${localstatedir}/lib/opkg/info/dreambox-secondstage.postinst; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.tar.xz; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	"

CONVERSION_CMD:xz:append = ";\
	cd ${DEPLOY_DIR_IMAGE}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}_flash.tar.xz ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar.xz; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/donate.txt; \
	zip ${IMAGE_NAME}_webif.zip ${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar.xz imageversion donate.txt; \
	cd ${IMGDEPLOYDIR}; \
	"

STB_PLATFORM = "dm3gen"

MACHINE_FEATURES += "modem dvb-c blindscan-dvbc hdmicec recovery ci usbconsole HDMI"

RCNAME = "dmm2"

IMAGE_CLASSES += "tarxz-dreambox"

KODIEXTSETTINGS = ""

DVBMEDIASINK_CONFIG:dm7080 = "--with-pcm --with-wma --with-wmv --with-dtsdownmix --with-eac3 --with-dts --with-vb6 --with-vb8 --with-spark"
DVBMEDIASINK_CONFIG:dm820 = "--with-pcm --with-wma --with-wmv --with-dtsdownmix --with-eac3 --with-dts --with-vb6 --with-vb8 --with-spark"
DVBMEDIASINK_CONFIG:dm520 = "--with-pcm --with-wma --with-wmv --with-dtsdownmix --with-eac3 --with-dts --with-vb6 --with-vb8 --with-spark --with-h265"

CFLAGS:append:pn-titan = " -DDREAMBOX -DCONFIG_ION "
