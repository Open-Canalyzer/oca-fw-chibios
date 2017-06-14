# oca-fw-chibios

[![Build Status](https://travis-ci.org/Open-Canalyzer/oca-fw-chibios.svg?branch=master)](https://travis-ci.org/Open-Canalyzer/oca-fw-chibios)

Open-Canalyzer firmware based on ChibiOS RTOS

# OpenOCD & GDB

OpenOCD and GDB are used for development and debugging

```
$ ./scripts/openocd.sh &> /dev/null &
$ arm-none-eabi-gdb --command=scripts/openocd-oca-v1.cfg
```

# Instrumentation trace macrocell

Use [stlink-trace -c 72](https://github.com/Open-Canalyzer/stlink-trace)
