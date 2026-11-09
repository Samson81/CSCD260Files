# Commands

## Part A

### Compile the Assembly

```bash
aarch64-linux-gnu-gcc -g -c base.S -o base.o
aarch64-linux-gnu-ld --no-warn-rwx-segments -T link.ld base.o -o base.elf
```

### Start QEMU

```bash
qemu-system-aarch64 -M virt -cpu cortex-a72 -m 512M -display none -kernel base.elf -monitor stdio -s -S
```

### Start GDB

```bash
gdb-multiarch base.elf -ex "target remote :1234" -ex "break web_nommu" -ex "break game_nommu" -ex "break web_mmu" -ex "break game_mmu"
```

Alternatively:

```bash
gdb-multiarch

target remote :1234
b web_nommu
b game_nommu
b web_mmu
b game_mmu
```

## Part B

### Compile the Assembly

```bash
aarch64-linux-gnu-gcc -g -c protect.S -o protect.o
aarch64-linux-gnu-ld --no-warn-rwx-segments -T link.ld protect.o -o protect.elf
```

### Start QEMU

```bash
qemu-system-aarch64 -M virt -cpu cortex-a72 -m 512M -display none -kernel protect.elf -monitor stdio -s -S
```

### Start GDB

```bash
gdb-multiarch protect.elf -ex "target remote :1234" -ex "break web_nommu" -ex "break game_nommu" -ex "break web_mmu" -ex "break game_mmu"
```

Alternatively:

```bash
gdb-multiarch

target remote :1234
b web_nommu
b game_nommu
b web_mmu
b game_mmu
```

