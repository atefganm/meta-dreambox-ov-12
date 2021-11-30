OPENDREAMBOX_PROJECT ?= "${BPN}"

SRC_URI += "git://git.opendreambox.org/git/${OPENDREAMBOX_PROJECT}.git;protocol=git"

inherit git-project

COMPATIBLE_MACHINE = "^(dm500hdv2|dm800sev2|dm7020hd|dm8000|dm900|dm920|dm520|dm820|dm7080|dreamone|dreamtwo)$"
