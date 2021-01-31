SUMMARY = "Hardware drivers for Dreambox"
SECTION = "base"
LICENSE = "CLOSED"
DEPENDS += "virtual/kernel"
PRIORITY = "required"

PACKAGE_ARCH = "${MACHINE_ARCH}"

BCMNUMBER = "bcm7435"
BCMNUMBER_dm520 = "bcm73625"
BCMNUMBER_dm900 = "bcm7439"
BCMNUMBER_dm920 = "bcm7439"

DREAMBOX_DVB_MODULES_MIRROR ?= "http://dreamboxupdate.com/download/opendreambox/2.5.0/dreambox-dvb-modules/${KV}-${MACHINE}-${DRIVERDATE}/${MACHINE}/${MD5SUM}"

SRC_URI = "${DREAMBOX_DVB_MODULES_MIRROR}/dreambox-dvb-modules_${KV}-${MACHINE}-${DRIVERDATE}_${MACHINE}.tar.xz;name=${MACHINE}"

S = "${WORKDIR}/dreambox-dvb-modules_${KV}-${MACHINE}-${DRIVERDATE}_${MACHINE}"

inherit module-base

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"


do_install() {
	find . -depth -not -path "./patches*" -not -path "./.pc*" -print0 | cpio --null -pdlu ${D}
	chown -hR root:root ${D}
}

do_install_append() {
	install -d ${D}${sysconfdir}/modules-load.d
	echo "stb-core" > ${D}${sysconfdir}/modules-load.d/01-dreambox-dvb-modules-stb-core.conf
	chmod 0644 ${D}${sysconfdir}/modules-load.d/01-dreambox-dvb-modules-stb-core.conf
	if [ -f ${D}${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/lcd.ko ]; then
		echo "lcd" > ${D}${sysconfdir}/modules-load.d/02-dreambox-dvb-modules-lcd.conf
		chmod 0644 ${D}${sysconfdir}/modules-load.d/02-dreambox-dvb-modules-lcd.conf
	fi
	for module in ${BCMNUMBER} dreambox_keyboard ble; do
		if [ -f ${D}${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/$module.ko ]; then
			echo $module >> ${D}${sysconfdir}/modules-load.d/10-dreambox-dvb-modules.conf
		fi
	done
	chmod 0644 ${D}${sysconfdir}/modules-load.d/10-dreambox-dvb-modules.conf
}

PACKAGES =+ "${PN}-fp ${PN}-lcd ${PN}-stb-core"

RDEPENDS_${PN} = "dreambox-secondstage-${MACHINE} ${PN}-fp kernel-${DM_LOCALVERSION} ${PN}-lcd ${PN}-stb-core"
RDEPENDS_${PN}_dm900 = "kernel-${KV}-${MACHINE} ${PN}-stb-core"
RDEPENDS_${PN}_dm920 = "kernel-${KV}-${MACHINE} ${PN}-stb-core"
RDEPENDS_${PN}-fp = "${PN}-stb-core"
RDEPENDS_${PN}-lcd = "${PN}-fp ${PN}-stb-core"

FILES_${PN} = "${sysconfdir}/modules-load.d/*-dreambox-dvb-modules.conf \
	${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/"

ALLOW_EMPTY_${PN}-fp = "1"
FILES_${PN}-fp = "${sysconfdir}/modules-load.d/*-dreambox-dvb-modules-fp.conf \
	${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/fp/fp-dev.ko"

ALLOW_EMPTY_${PN}-lcd = "1"
FILES_${PN}-lcd = "${sysconfdir}/modules-load.d/*-dreambox-dvb-modules-lcd.conf \
	${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/lcd.ko"

FILES_${PN}-stb-core = "${sysconfdir}/modules-load.d/*-dreambox-dvb-modules-stb-core.conf \
	${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/stb-core.ko \
	${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/core/boxsec.ko \
	${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/stb/stb-core.ko"

# We don't use KERNEL_VERSION in this recipe, because the
# precompiled modules depend on a specific version.
DM_LOCALVERSION = "${@'-'.join('${PV}'.split('-')[:-1])}-${MACHINE}"
DRIVERDATE = "${@'${PV}'.split('-')[-1]}"

pkg_postinst_${PN} () {
if [ -z "$D" ]; then
	depmod -a ${DM_LOCALVERSION}
fi
}
pkg_postinst_${PN}-lcd () {
if [ -z "$D" ]; then
	depmod -a ${DM_LOCALVERSION}
fi
}
pkg_postinst_${PN}-stb-core () {
if [ -z "$D" ]; then
	depmod -a ${DM_LOCALVERSION}
fi
}
