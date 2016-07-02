# oca-fw-chibios

Open-Canalyzer firmware based on ChibiOS RTOS

# OpenOCD & GDB

OpenOCD and GDB are used for development and debugging

```
$ ./scripts/openocd.sh &> /dev/null &
$ arm-none-eabi-gdb --command=scripts/openocd-oca-v1.cfg
```
