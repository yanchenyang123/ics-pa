cmd_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/nemu-main.o := unused

source_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/nemu-main.o := src/nemu-main.c

deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/nemu-main.o := \
    $(wildcard include/config/target/am.h) \
  /home/ycy/ics2022/nemu/include/common.h \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
    $(wildcard include/config/isa64.h) \
  /home/ycy/ics2022/nemu/include/macro.h \
  /home/ycy/ics2022/nemu/include/debug.h \
  /home/ycy/ics2022/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \
  /home/ycy/ics2022/nemu/include/isa.h \
  /home/ycy/ics2022/nemu/src/isa/riscv32/include/isa-def.h \

/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/nemu-main.o: $(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/nemu-main.o)

$(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/nemu-main.o):