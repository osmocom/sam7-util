/*
 * io.c
 *
 * Copyright (C) 2011 Holger Freyther, all rights reserved
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 */

#include "io.h"

#include <stdio.h>

static struct io_driver *g_driver = NULL;

static struct io_driver *drivers[5] = { NULL, };
static int last_driver = 0;

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

int io_driver_register(struct io_driver *driver)
{
	if (last_driver > ARRAY_SIZE(drivers)) {
		fprintf(stderr, "Registered more than %zu devices.\n",
			ARRAY_SIZE(drivers));
		return -1;
	}

	drivers[last_driver++] = driver;
	return 0;
}

static void io_driver_activate(struct io_driver *driver)
{
	printf("Activating driver: %s\n", driver->name);
	g_driver = driver;
}

int io_init(char *dev)
{
	return g_driver->io_init(dev);
}

int io_cleanup(void)
{
	return g_driver->io_cleanup();
}

int io_write(void *buff, int len)
{
	return g_driver->io_write(buff, len);
}

int io_read(void *buff, int len)
{
	return g_driver->io_read(buff, len);
}

void io_driver_select_backend(const char *name)
{
  int i;
  struct io_driver *driver = drivers[0];

  for ( i = 0; ;++i) {
    if (!drivers[i])
      break;

    if (name && strcmp("posix", drivers[i]->name) == 0) {
      driver = drivers[i];
      break;
    } else if (!name && strcmp("libusb", drivers[i]->name) == 0) {
      driver = drivers[i];
      break;
    }
  }

  io_driver_activate(driver);
}
