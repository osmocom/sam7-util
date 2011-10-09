/*
 * io.c
 *
 * Copyright (C) 2005 Erik Gilling, all rights reserved
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, version 2.
 *
 */

#include "config.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>


#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#include "io.h"
#include "samba.h"

static int io_fd;

#define SAM7_TTY "/dev/at91_0"

#undef DEBUG_IO

int io_init( char *dev )
{
  if( dev == NULL ) {
    dev = SAM7_TTY;
  }
  //  char buff[16];

  if( (io_fd = open( dev, O_RDWR )) < 0 ) {
    printf( "can't open \"%s\": %s\n", dev, strerror( errno ) );
    return -1;
  }



  return samba_init();
}

int io_cleanup( void )
{
  close( io_fd );
  
  return 0;
}
int io_write( void *buff, int len ) 
{
  int write_len = 0;
  int ret;

#ifdef DEBUG_IO
  write( STDOUT_FILENO, ">", 1 );
  write( STDOUT_FILENO, buff, len );
  write( STDOUT_FILENO, "\n", 1 );
  
#endif
  while( write_len < len ) {
    if( (ret = write( io_fd, buff + write_len, len - write_len )) < 0 ) {
      return -1;
    }
    write_len += ret;
  }

  return write_len;
}

int io_read( void *buff, int len ) 
{
#ifdef DEBUG_IO
  int i;
  char outbuff[16];
  len = read( io_fd, buff, len );
  write( STDOUT_FILENO, "<", 1 );
  for( i=0 ; i<len ; i++ ) {
    snprintf( outbuff, 16, " %02X", ((char*)buff)[i] & 0xff );
    write( STDOUT_FILENO, outbuff, strlen(outbuff) );
  }
  write( STDOUT_FILENO, "\n", 1 );

  return len;
#else
  return read( io_fd, buff, len );
#endif
}

