AM_CFLAGS = -Wall

bin_PROGRAMS = sam7

sam7_SOURCES = main.c io.c samba.c cmd.c

if HAVE_IOKIT
sam7_SOURCES += io_iokit.c
endif
if HAVE_WIN32
sam7_SOURCES += io_win32.c
endif
if HAVE_POSIX
sam7_SOURCES += io_posix.c
endif
if HAVE_LIBUSB
sam7_SOURCES += io_libusb.c
endif

noinst_HEADERS = io.h samba.h cmd.h loader128_data.h loader256_data.h 

EXTRA_DIST = driver/Makefile driver/at91.c \
	loader/Makefile loader/at91.h loader/bin2c.c loader/crt0.S \
	loader/loader.c loader/loader.lds
