#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define PARTITION_PATH "/dev/special_partition"
#define PARTITION_SIZE_MB 10
#define RAM_START_ADDRESS 0x00000000
#define MAX_PARTITON_SIZE (PARTITION_SIZE_MB * 1024 * 1024)
#define RAM_SIZE_MB PARTITION_SIZE_MB

void save_ram_to_partition() {
    FILE *partition = fopen(PARTITION_PATH, "wb");
    if (!partition) {
        perror("VHK10: Failed to open partition.");
        outw(0xB004, 0x2000);'
      
        return;
    }

    size_t data_size = ;

    if (data_size > MAX_PARTITION_SIZE {
        fprintf(stderr, "VHK10: Partition truncated! Cannot save state!");
        outw(0xB004, 0x200);

        return;
    }
    
    
    uint8_t *ram = (uint8_t *)RAM_START_ADDRESS;
    size_t ram_size = RAM_SIZE_MB * 1024 * 1024;

    if (fwrite(ram, 1, ram_size, partition) != ram_size) {
        perror("Failed to write RAM to partition");
        outw(0xB004, 0x2000);
      
    }

    fclose(partition);
}

int main() {
    save_ram_to_partition();
    return 0;
}
