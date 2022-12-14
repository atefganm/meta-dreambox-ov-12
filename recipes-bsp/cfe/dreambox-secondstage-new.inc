SUMMARY = "Dreambox second stage bootloader"
SECTION = "base"
LICENSE = "CLOSED"
PROVIDES += "virtual/bootloader"
PRIORITY = "required"

PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "http://dreamboxupdate.com/download/opendreambox/2.2.0/dreambox-secondstage/${PV}/${MACHINE}/${MD5SUM}/dreambox-secondstage_${PV}_${MACHINE}.tar.xz;name=${MACHINE}"

PACKAGES = "${PN}"

inherit preserve_binary

S = "${WORKDIR}/dreambox-secondstage_${PV}_${MACHINE}"

do_install() {
	install -d ${D}${datadir}/dreambox-secondstage
	install -m 0644 ${S}${datadir}/dreambox-secondstage/ssbl.bin ${D}${datadir}/dreambox-secondstage/ssbl.bin
}

RDEPENDS:${PN} = "flash-scripts"

FILES:${PN} = "${datadir}"

do_compile[noexec] = "1"
