SUMMARY = "Dreambox EGL and GLES2 libraries"
LICENSE = "CLOSED"
DEPENDS = "${LIBEGLDEP}"
PROVIDES = "virtual/egl virtual/libgles1 virtual/libgles2"
RPROVIDES:${PN} = "virtual/egl virtual/libgles1 virtual/libgles2"

LIBEGLDEP = ""
LIBEGLDEP:dm520 = "libv3ddriver"
LIBEGLDEP:dm820 = "libv3ddriver"
LIBEGLDEP:dm7080 = "libv3ddriver"
LIBEGLDEP:dm900 = "libvc5driver"
LIBEGLDEP:dm920 = "libvc5driver"

LIBEGLRDEP = ""
LIBEGLRDEP_dm820 = "libv3ddriver"
LIBEGLRDEP_dm7080 = "libv3ddriver"
LIBEGLRDEP_dm900 = "libvc5driver"
LIBEGLRDEP_dm920 = "libvc5driver"

RDEPENDS:${PN} = "${LIBEGLRDEP}"

RPROVIDES:${PN} = "libegl libegl1 libgles1 libgles2 libglesv2-2"
RPROVIDES:${PN}-dev = "libegl-dev libgles1-dev libgles2-dev"

RCONFLICTS:${PN} = "libegl libegl1 libgles1 libgles2 libglesv2-2"
RCONFLICTS:${PN}-dev = "libegl-dev libgles1-dev libgles2-dev"

RREPLACES:${PN} = "libegl libegl1 libgles1 libgles2 libglesv2-2"
RREPLACES:${PN}-dev = "libegl-dev libgles1-dev libgles2-dev"

# As a workaround, keep .so symlinks in base package
# until all users were recompiled.
FILES:${PN} += "${libdir}/lib*${SOLIBSDEV}"
FILES_SOLIBSDEV = ""

#do_install:append() {
#	rm -rf ${D}${libdir}/pkgconfig
#}
