#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

int main (void)
{
  struct udev *udev;
  struct udev_enumerate *enumerate;
  struct udev_list_entry *devices, *dev_list_entry;
  struct udev_device *dev;
  struct udev_monitor	*mon;
  int		fd;

  /* Create the udev object */
  udev = udev_new();
  if (!udev) {
    printf("Can't create udev\n");
    exit(1);
  }
  /* Set up a monitor to monitor hidraw devices */
  mon = udev_monitor_new_from_netlink(udev, "udev");
  udev_monitor_filter_add_match_subsystem_devtype(mon, "hidraw", NULL);
  udev_monitor_enable_receiving(mon);
  /* Get the file descriptor (fd) for the monitor.
     This fd will get passed to select() */
  fd = udev_monitor_get_fd(mon);

  /* This section will run continuously, calling usleep() at
        the end of each pass. This is to demonstrate how to use
	a udev_monitor in a non-blocking way. */
  while (1) {
    /* Set up the call to select(). In this case, select() will
          only operate on a single file descriptor, the one
	     associated with our udev_monitor. Note that the timeval
	        object is set to 0, which will cause select() to not
		block. */
    fd_set fds;
    struct timeval tv;
    int ret;

    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    ret = select(fd+1, &fds, NULL, NULL, NULL);

    /* Check if our file descriptor has received data. */
    if (ret > 0 && FD_ISSET(fd, &fds)) {
      printf("\nselect() says there should be data\n");

      /* Make the call to receive the device.
	 select() ensured that this will not block. */
      dev = udev_monitor_receive_device(mon);
      if (dev) {
	printf("Got Device\n");
	printf("   Node: %s\n", udev_device_get_devnode(dev));
	printf("   Subsystem: %s\n", udev_device_get_subsystem(dev));
	printf("   Devtype: %s\n", udev_device_get_devtype(dev));

	printf("   Action: %s\n",udev_device_get_action(dev));
	udev_device_unref(dev);
      }
      else {
	printf("No Device from receive_device(). An error occured.\n");
      }
    }
    usleep(250*1000);
    printf(".");
    fflush(stdout);
  }

  udev_unref(udev);

  return 0;
}
