#!/bin/sh
#openocd -f interface/stlink-v2.cfg -f target/stm32f3x.cfg -o '$_TARGETNAME configure -rtos auto'
openocd -f scripts/openocd-oca-v1.cfg
