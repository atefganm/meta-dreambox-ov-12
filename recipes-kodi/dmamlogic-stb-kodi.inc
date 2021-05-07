require recipes-mediacenter/kodi/stb-kodi_19.bb

PROVIDES += "virtual/kodi"
RPROVIDES_${PN} += "virtual/kodi"
PROVIDES += "kodi"
RPROVIDES_${PN} += "kodi"

DEPENDS_append = " amlogic-libamadec amlogic-libamcodec amlogic-libamavutils"

EXTRA_OECONF += " \
    --with-platform=aml-aarch64 \
    --with-ffmpeg=stb \
"
