SUMMARY = "Broadcom VC5 driver"

FILES:${PN} = "${libdir}/lib*${SOLIBSDEV}"
FILES:${PN}-dev = "${includedir}"

EXCLUDE_FROM_WORLD = "1"

PACKAGE_ARCH = "${MACHINE_ARCH}"
