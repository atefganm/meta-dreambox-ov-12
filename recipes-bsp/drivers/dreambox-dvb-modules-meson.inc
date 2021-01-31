SUMMARY = "Hardware drivers for Dreambox"
SECTION = "base"
LICENSE = "CLOSED"
DEPENDS += "virtual/kernel dreambox-dvb-modules-systemd"
PRIORITY = "required"

PACKAGE_ARCH = "${MACHINE_ARCH}"

PRECOMPILED_NAME = "dreambox-dvb-modules"

PRECOMPILED_ARCH = "${MACHINE}"

PACKAGES =+ "${PN}-firmware ${PN}-fp ${PN}-lcd ${PN}-stb-core"

RDEPENDS_${PN} = "${PN}-fp ${PN}-lcd ${PN}-stb-core"
RDEPENDS_${PN}-firmware = "${PN}-firmware"
RDEPENDS_${PN}-fp = "${PN}-stb-core"
RDEPENDS_${PN}-lcd = "${PN}-fp ${PN}-stb-core"
RRECOMMENDS_${PN} = "${PN}-firmware dreambox-dvb-modules-systemd"

FILES_${PN} = "${sysconfdir}/modules-load.d/*-dreambox-dvb-modules.conf \
               ${nonarch_base_libdir}/modules/${DM_LOCALVERSION}/extra/"

FILES_${PN}-firmware = "${nonarch_base_libdir}/firmware"

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
DM_LOCALVERSION = "${@d.getVar('PV', True).rsplit('-', 1)[0]}"

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

inherit opendreambox-precompiled-binary-new

RREPLACES_${PN} += "dreamframeinject"
RPROVIDES_${PN} += "dreamframeinject"
RCONFLICTS_${PN} += "dreamframeinject"
