#!/bin/bash
set -euo pipefail

GCC_ARM_EMBEDDED_TOOLCHAIN_URL="https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q2-update/+download/gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2"
GCC_ARM_EMBEDDED_TOOLCHAIN_TAR="gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2"

if [ ! -f "${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}" ]; then
	echo "=== Downloading ${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}"
	curl --retry 10 --retry-max-time 120 -L ${GCC_ARM_EMBEDDED_TOOLCHAIN_URL}
fi

if [ ! -d "gcc-arm-none-eabi-5_4-2016q2" ]; then
	echo "=== Extracting ${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}"
	tar -xf ${GCC_ARM_EMBEDDED_TOOLCHAIN_TAR}
fi

export PATH="${PWD}/gcc-arm-none-eabi-5_4-2016q2/bin:${PATH}"
arm-none-eabi-gcc --version
make
