### Features
Recover photos from sdcard(or sdcard image file) taken with Nikon DSLR(Tested on D3200).

### How to build
```shell
$ meson setup builddir
$ ninja -C builddir
```

### Run
```shell
$ ./nikon_jpeg_recovery ../sdcard.img .
Found jpeg at address 0x820000 - Date image created: 2015:11:21 12:24:55
Found jpeg at address 0xf08000 - Date image created: 2015:11:21 12:40:36
Found jpeg at address 0x1580000 - Date image created: 2015:11:21 12:41:01
Found jpeg at address 0x1bc0000 - Date image created: 2015:11:21 12:41:13
Found jpeg at address 0x2218000 - Date image created: 2015:11:21 12:42:28
Found jpeg at address 0x2888000 - Date image created: 2015:11:21 12:45:33
Found jpeg at address 0x2ed0000 - Date image created: 2015:11:21 12:46:38
Found jpeg at address 0x3510000 - Date image created: 2015:11:21 12:46:47
Found jpeg at address 0x3bd8000 - Date image created: 2015:11:21 12:46:56
Found jpeg at address 0x42f0000 - Date image created: 2015:11:21 12:47:07
Found jpeg at address 0x4938000 - Date image created: 2015:11:21 12:49:06
Found jpeg at address 0x4f88000 - Date image created: 2015:11:21 12:50:07
Found jpeg at address 0x56b8000 - Date image created: 2015:11:21 12:50:20
Found jpeg at address 0x5cf8000 - Date image created: 2015:11:21 12:50:27
Found jpeg at address 0x6368000 - Date image created: 2015:11:21 12:54:45
Found jpeg at address 0x69f8000 - Date image created: 2015:11:21 12:54:53
Found jpeg at address 0x7078000 - Date image created: 2015:11:21 12:55:00
Found jpeg at address 0x7770000 - Date image created: 2015:11:21 12:55:39
Found jpeg at address 0x7e48000 - Date image created: 2015:11:21 12:55:41
Found jpeg at address 0x84e0000 - Date image created: 2015:11:21 12:56:33
Found jpeg at address 0x8bb0000 - Date image created: 2015:11:21 12:56:46
Found jpeg at address 0x92e0000 - Date image created: 2015:11:21 12:56:49
Found jpeg at address 0x9a18000 - Date image created: 2015:11:21 12:56:52
Found jpeg at address 0xa158000 - Date image created: 2015:11:21 12:56:58
Found jpeg at address 0xa7c0000 - Date image created: 2015:11:21 12:57:00
Found jpeg at address 0xaee8000 - Date image created: 2015:11:21 12:57:49
Found jpeg at address 0xb5c8000 - Date image created: 2015:11:21 12:58:49
Found jpeg at address 0xbc70000 - Date image created: 2015:11:21 12:58:55
Found jpeg at address 0xc2f8000 - Date image created: 2015:11:21 12:59:00
...
```
