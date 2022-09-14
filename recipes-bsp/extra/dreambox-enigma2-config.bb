SUMMARY = "Dreambox box-specific configuration files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "^(dm7020hd|dm8000)$"

SRC_URI = "file://skin_box.xml"

PACKAGES = "${PN}"

FILES:${PN} = "${enigma_skins}"

S = "${WORKDIR}"

do_install() {
	install -d ${D}${enigma_skins}
	install -m 644 ${S}/skin_box.xml ${D}${enigma_skins}/
}

do_compile[noexec] = "1"
