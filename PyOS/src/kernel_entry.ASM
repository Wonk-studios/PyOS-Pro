BITS 64
section .text
global kernel_entry

kernel_entry:
    cli                     ; Clear interrupts
    mov ax, 0x10            ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, stack_top      ; Set up stack

    extern kernel_main
    call kernel_main        ; Call the C kernel main function

hang:
    hlt                     ; Halt the CPU
    jmp hang

section .bss
resb 8192                  ; 8 KB stack space
stack_top: