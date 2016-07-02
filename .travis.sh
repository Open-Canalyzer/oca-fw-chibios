#!/bin/bash
set -euo pipefail

GCC_ARM_EMBEDDED_TOOLCHAIN="gcc-arm-none-eabi-5_4-2016q2"
GCC_ARM_EMBEDDED_TOOLCHAIN_TAR="${GCC_ARM_EMBEDDED_TOOLCHAIN}-20160622-linux.tar.bz2"
GCC_ARM_EMBEDDED_TOOLCHAIN_URL="https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q2-update/+download/${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}"

if [ ! -f "${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}" ]; then
	echo "=== Downloading ${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}"
	wget ${GCC_ARM_EMBEDDED_TOOLCHAIN_URL}
fi

echo "=== Extracting ${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}"
tar -xf ${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}

export PATH="${PWD}/${GCC_ARM_EMBEDDED_TOOLCHAIN}/bin:${PATH}"
arm-none-eabi-gcc --version
make
