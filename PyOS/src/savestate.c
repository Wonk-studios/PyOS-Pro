#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define PARTITION_PATH "/dev/special_partition"
#define PARTITION_SIZE_MB 1000
#define RAM_START_ADDRESS 0x00000000 // Adjust based on actual RAM start
#define RAM_SIZE_MB PARTITION_SIZE_MB

void save_ram_to_partition() {
    FILE *partition = fopen(PARTITION_PATH, "wb");
    if (!partition) {
        perror("VHK10: Failed to open partition.");
      __asm__ __volatile__("wfi");
      outw(0xB004, 0x2000);'
      
        return;
    }

    uint8_t *ram = (uint8_t *)RAM_START_ADDRESS;
    size_t ram_size = RAM_SIZE_MB * 1024 * 1024;

    if (fwrite(ram, 1, ram_size, partition) != ram_size) {
        perror("Failed to write RAM to partition");
      __asm__ __volatile__("wfi");
      outw(0xB004, 0x2000);
      
    }

    fclose(partition);
}

int main() {
    save_ram_to_partition();
    return 0;
}
