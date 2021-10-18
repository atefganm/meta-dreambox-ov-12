DESCRIPTION = "Dreambox box-specific configuration files"
SECTION = "base"
PRIORITY = "required"
MAINTAINER = "PLi team"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "^(dm7020hd|dm8000)$"

SRC_URI = "file://skin_box.xml"

PACKAGES = "${PN}"

FILES:${PN} = "${datadir}/enigma2"

S = "${WORKDIR}"

do_install() {
	install -d ${D}${datadir}/enigma2
	install -m 644 ${S}/skin_box.xml ${D}${datadir}/enigma2/
}
