tar extended-remote :4242
file build/oca.elf
load build/oca.elf
monitor reset
monitor halt
kill
quit
