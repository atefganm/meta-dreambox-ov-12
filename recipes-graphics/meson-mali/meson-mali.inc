SUMMARY = "Amlogic mali opengl provider"
LICENSE = "CLOSED"
PROVIDES = "virtual/egl virtual/libgles2"

RRECOMMENDS:${PN} = "${PN}-module-bifrost-r12p0"

RPROVIDES:${PN} = "libegl libegl1 libgles2 libglesv2-2"
RPROVIDES:${PN}-dev = "libegl-dev libgles2-dev"

RCONFLICTS:${PN} = "libegl libegl1 libgles2 libglesv2-2"
RCONFLICTS:${PN}-dev = "libegl-dev libgles2-dev"

RREPLACES:${PN} = "libegl libegl1 libgles2 libglesv2-2"
RREPLACES:${PN}-dev = "libegl-dev libgles2-dev"

FILES:${PN} += "${libdir}/lib*${SOLIBSDEV}"
FILES_SOLIBSDEV = ""

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit opendreambox-precompiled-binary-new

PRECOMPILED_ARCH = "aarch64"

do_compile[noexec] = "1"
