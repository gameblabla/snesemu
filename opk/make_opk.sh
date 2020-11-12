#!/bin/sh

cd $(dirname "$0")

OPK_NAME="${1:-snesemu.opk}"

echo Building "${OPK_NAME}"...

# create opk
FLIST="../snes9x default.gcw0.desktop sfc.png"

rm -f "${OPK_NAME}"
mksquashfs ${FLIST} "${OPK_NAME}" -all-root -no-xattrs -noappend -no-exports

cat default.gcw0.desktop
