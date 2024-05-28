import os
import mmap
import struct
import sys

JPEG_HEADER = 0xd8ff
JPEG_END_TAG = 0xd9ff
JPEG_MIN_SIZE = 1 * 1024 * 1024
JPEG_MAX_SIZE = 64 * 1024 * 1024


def get_jpeg_size(img):
    pos = 0

    while pos < len(img):
        end_tag = struct.unpack_from('<H', img, pos)[0]

        if end_tag == JPEG_END_TAG:
            return pos + 2

        pos += 1

    return 0


def main():
    if len(sys.argv) < 3:
        print("Usage: python nikon-jpeg-recovery.py <img_file> <dest_dir>")
        sys.exit(1)

    img_file = sys.argv[1]
    dest_dir = sys.argv[2]

    # Open image file
    try:
        with open(img_file, 'rb') as f:
            img_data = mmap.mmap(f.fileno(), 0, prot=mmap.PROT_READ)
            src_size = os.fstat(f.fileno()).st_size

            # Search for JPEG headers
            c = 0
            while c < (src_size - 512):
                hdr = struct.unpack_from('<H', img_data, c)[0]

                if hdr == JPEG_HEADER:
                    producer = img_data[c + 0xa0:c + 0xa0 + len("NIKON CORPORATION")]
                    if producer.decode('ascii') == "NIKON CORPORATION":
                        date_str = img_data[c + 0xdc:c + 0xdc + 20].decode('ascii').rstrip('\x00')

                        print(f"Found JPEG at address 0x{c:x} - Date image created: {date_str}")

                        img_size = get_jpeg_size(img_data[c:])
                        if img_size > 0:
                            dest_img_name = os.path.join(dest_dir, f"IMG_{date_str}.jpg")

                            with open(dest_img_name, 'wb') as out_f:
                                out_f.write(img_data[c:c + img_size])

                c += 512

    except OSError as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
