AC_INIT([sam7utils], [0.2.1], [konkers@konkers.net])

AC_CANONICAL_HOST

AM_INIT_AUTOMAKE(foreign)
AM_CONFIG_HEADER(config.h)

AC_PROG_CC 
AC_PROG_INSTALL
AC_PROG_MAKE_SET

case "${host}" in
     *-*-darwin* )
       LIBS="$LIBS -framework IOKIT -framework CoreFoundation"
       have_iokit="true"
     ;;	    
     *-*-cygwin* )
       LIBS="$LIBS -lsetupapi"
       have_win32="true"
     ;;	    
     * )
       have_posix="true"
       AC_CHECK_LIB(usb,usb_init,have_libusb="true";LIBS="$LIBS -lusb")
       
     ;;
esac


AC_HEADER_STDC

AC_CHECK_LIB(readline, readline,,AC_MSG_ERROR(readline not found))
AC_CHECK_LIB(curses, tgoto,,AC_MSG_ERROR(curses not found))
AC_CHECK_HEADERS(stdint.h,,AC_MSG_WARN(can't find stdint.h))
AC_CHECK_HEADERS(ctype.h,,)
AC_CHECK_HEADERS(endian.h,,)


AM_CONDITIONAL([HAVE_IOKIT], [test x$have_iokit = xtrue])
AM_CONDITIONAL([HAVE_WIN32], [test x$have_win32 = xtrue])
AM_CONDITIONAL([HAVE_POSIX], [test x$have_posix = xtrue])
AM_CONDITIONAL([HAVE_LIBUSB],[test x$have_libusb = xtrue])

AC_OUTPUT(Makefile)
