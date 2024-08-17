#include <sys/mman.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define JPEG_HEADER 0xd8ff
#define JPEG_END_TAG 0xd9ff
#define JPEG_MIN_SIZE (1 * 1024 * 1024)
#define JPEG_MAX_SIZE (64 * 1024 * 1024)

// TODO: Implement proper way to get jpeg size.
static uint64_t get_jpeg_size(const char *img)
{
    uint64_t pos = 0;

    for(pos = JPEG_MIN_SIZE; pos < JPEG_MAX_SIZE; pos++)
    {
        uint16_t end_tag = 0;

        end_tag = *((uint16_t *)(img + pos));
        if (end_tag == JPEG_END_TAG)
        {
            return pos + 2;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    struct stat img_stat;
    char *img_file = NULL;
    void *img_data = NULL;
    uint64_t src_size = 0;
    int img_fd = 0;

    if (argc < 3)
    {
        fprintf(stderr, "Usage nikon-jpeg-recovery <img_file> <dest_dir>\n");
        return EXIT_FAILURE;
    }

    setbuf(stdout, NULL); // disable buffering on stdout

    img_file = argv[1];

    // mmap file.
    img_fd = open(argv[1], O_RDONLY);
    if (img_fd == -1)
    {
        fprintf(stderr, "Error opening image file(%s). Error: %m\n", img_file);
        return EXIT_FAILURE;
    }

    if (fstat(img_fd, &img_stat) != 0)
    {
        fprintf(stderr, "Error stating image file(%s). Error: %m\n", img_file);
        return EXIT_FAILURE;
    }

    img_data = mmap(NULL, img_stat.st_size, PROT_READ, MAP_PRIVATE, img_fd, 0);
    if (img_data == MAP_FAILED)
    {
        fprintf(stderr, "Error maping image file(%s). Error: %m\n", img_file);
        return EXIT_FAILURE;
    }

    src_size = img_stat.st_size;

    // search for jpeg header on every sector start(512b)
    for(uint64_t c = 0; c < (src_size - 512); c += 512)
    {
        void *ptr = NULL;
        uint16_t hdr = 0;

        ptr = (char *)img_data + c;
        hdr = *((uint16_t *)ptr);

        if (hdr == JPEG_HEADER)
        {
            const char *producer = (char *)ptr + 0xa0;

            if (strcmp(producer, "NIKON CORPORATION") == 0)
            {
                const char *date_str = NULL;
                uint64_t img_size = 0;

                date_str = (char *)ptr + 0xdc;

                printf("Found jpeg at address 0x%"PRIx64" - Date image created: %s\n", c, date_str);

                img_size = get_jpeg_size(ptr);

                if (img_size > 0)
                {
                    ssize_t written = 0;
                    int out_fd = 0;

                    int str_size = snprintf(NULL, 0, "%s/IMG_%s.jpg", argv[2], date_str);
                    char dest_img_name[str_size + 1];

                    snprintf(dest_img_name, sizeof dest_img_name, "%s/IMG_%s.jpg", argv[2], date_str);

                    out_fd = open(dest_img_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                    if (out_fd == -1)
                    {
                        fprintf(stderr, "Error creating img file(%s). Error: %m\n", dest_img_name);
                        break;
                    }

                    written = write(out_fd, ptr, img_size);
                    if (written < 0)
                    {
                        fprintf(stderr, "Error writing img file(%s). Error: %m\n", dest_img_name);
                    }
                    else if (written != img_size)
                    {
                        fprintf(stderr, "Partial write to img file(%s). Error: %m\n", dest_img_name);
                    }

                    close(out_fd);
                }
            }
        }
    }

    munmap(img_data, src_size);

    close(img_fd);

    return EXIT_SUCCESS;
}
