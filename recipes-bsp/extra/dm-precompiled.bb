SUMMARY = "Pre-compiled for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "^(dreamone|dreamtwo)$"

inherit preserve_binary

SRC_URI = "file://others.zip"

S = "${WORKDIR}"

do_compile[noexec] = "1"

do_install() {
	install -d ${D}${sysconfdir}/u-boot.scr.d
	install -m 0644 ${S}${sysconfdir}/u-boot.scr.d/* ${D}${sysconfdir}/u-boot.scr.d
	install -m 0644 ${S}${sysconfdir}/machine-id ${D}${sysconfdir}/
}

FILES:${PN} += "/"
