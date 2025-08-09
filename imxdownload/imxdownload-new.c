#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define IMX6ULL_IVT_HEADER_TAG 0xD1
#define IMX6ULL_DCD_HEADER_TAG 0xD2
#define IMX6ULL_IMAGE_HEADER_TAG 0xD3

typedef struct {
    unsigned char tag;
    unsigned char length[2];
    unsigned char version[2];
    unsigned char reserved[4];
    unsigned char dcd_ptr[4];
    unsigned char boot_data_ptr[4];
    unsigned char self_ptr[4];
    unsigned char csf_ptr[4];
    unsigned char reserved2[4];
} imx6ull_ivt_header_t;

typedef struct {
    unsigned char tag;
    unsigned char length[2];
    unsigned char version[2];
    unsigned char reserved[4];
    unsigned char start[4];
    unsigned char boot_length[4];
    unsigned char plugin[4];
} imx6ull_boot_data_t;

void usage(const char *progname) {
    printf("Usage: %s <bin_file> <device>\n", progname);
    printf("Example: %s led.bin /dev/sda\n", progname);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return 1;
    }

    const char *bin_file = argv[1];
    const char *device = argv[2];

    // Open binary file
    FILE *fp = fopen(bin_file, "rb");
    if (!fp) {
        perror("Failed to open binary file");
        return 1;
    }

    // Get file size
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (file_size <= 0) {
        printf("Invalid file size\n");
        fclose(fp);
        return 1;
    }

    // Allocate buffer for the entire file
    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        printf("Failed to allocate memory\n");
        fclose(fp);
        return 1;
    }

    // Read the entire file
    if (fread(buffer, 1, file_size, fp) != file_size) {
        printf("Failed to read binary file\n");
        free(buffer);
        fclose(fp);
        return 1;
    }
    fclose(fp);

    // Open device file
    int fd = open(device, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        free(buffer);
        return 1;
    }

    // Seek to offset 1KB (0x400)
    if (lseek(fd, 0x400, SEEK_SET) != 0x400) {
        perror("Failed to seek to offset");
        close(fd);
        free(buffer);
        return 1;
    }

    // Write the binary data
    ssize_t written = write(fd, buffer, file_size);
    if (written != file_size) {
        perror("Failed to write to device");
        close(fd);
        free(buffer);
        return 1;
    }

    // Sync to ensure data is written
    if (fsync(fd) < 0) {
        perror("Failed to sync device");
    }

    close(fd);
    free(buffer);

    printf("Successfully downloaded %s to %s\n", bin_file, device);
    printf("File size: %ld bytes\n", file_size);
    printf("Written to offset: 0x400 (1KB)\n");

    return 0;
} 