target extended-remote :3333
monitor arm semihosting enable
monitor reset halt
file build/oca.elf
load build/oca.elf
monitor reset init
