#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <kernel/mem.h>
#include <kernel/atag.h>
#include <kernel/kerio.h>
#include <kernel/gpu.h>
#include <kernel/interrupts.h>
#include <kernel/timer.h>
#include <kernel/process.h>
#include <kernel/mutex.h>
#include <common/stdlib.h>

#define _VERSION "0.0.18"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) atags;

    mem_init((atag_t *)atags);
    gpu_init();
    printf("GPU INITIALIZED\n");
    printf("INITIALIZING INTERRUPTS...");
    interrupts_init();
    printf("DONE\n");
    printf("INITIALIZING TIMER...");
    timer_init();
    printf("DONE\n");
    printf("INITIALIZING SCHEDULER...");
    process_init();
    printf("DONE\n");
    printf("INITIALIZING FINISHED\n");

    gpu_cls();

    printf("Genetic Lifeform and Disk Operating System [%s]\n",_VERSION);
    printf("(c) 2020 Aperture Science, Inc. ALl rights reserved\n\n");

    char input[256];
    printf("GlaDOS>");

    while (1) {
        char c = getc();

        if(c == 13){
            newline();
            newline();

            if(strcomp("cls",input) == 0){
                gpu_cls();
            }else{
                putc('\'');
                puts(input);
                putc('\'');
                puts(" is not recognized as an internal or external command.");
                newline();
                newline();
            }
            
            memset(&input[0], 0, sizeof(input));
            puts("GlaDOS>");
        }else{
            append(input, c);
            write(c);
        }
    }
}