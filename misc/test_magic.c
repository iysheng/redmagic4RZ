#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <linux/gpio.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * SWDIO GPIO_4_1  = 33
 * SWCLK GPIO_40_2 = 322
 * */
int main(int argc, char **argv)
{
	struct gpiohandle_request req[2];
	struct gpiohandle_data data;
	struct gpiohandle_data data_swdio;
    struct gpiohandle_config swdio_config;
	char chrdev_name[20];
	int fd, ret;

	strcpy(chrdev_name, "/dev/gpiochip0");

	/*  Open device: gpiochip0 for GPIO bank A */
	fd = open(chrdev_name, 0);
	if (fd == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to open %s\n", chrdev_name);

		return ret;
	}

	req[0].lineoffsets[0] = 33;
	req[0].flags = GPIOHANDLE_REQUEST_OUTPUT;
	req[0].lines = 1;
	memcpy(req[0].default_values, &data, sizeof(req[0].default_values));
	strcpy(req[0].consumer_label, "swdio");

	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req[0]);
	if (ret == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to issue GET LINEHANDLE IOCTL (%d)\n",
			ret);
	}

	req[1].lineoffsets[0] = 322;
	req[1].flags = GPIOHANDLE_REQUEST_OUTPUT;
	req[1].lines = 1;
	memcpy(req[1].default_values, &data, sizeof(req[1].default_values));
	strcpy(req[1].consumer_label, "swclk");
	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req[1]);
	if (ret == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to issue GET LINEHANDLE IOCTL (%d)\n",
			ret);
	}

	if (close(fd) == -1)
		perror("Failed to close GPIO character device file");

	int test_here = 0;
	bool read = false;
	/*  Start led blinking */
	while(1) {
    	data.values[0] = !data.values[0];
		ret = ioctl(req[1].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (ret == -1) {
			ret = -errno;
			fprintf(stderr, "Failed to issue %s (%d)\n",
					"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
		}

		if (test_here++ > 100)
		{
    		usleep(10000);
            swdio_config.flags = GPIOHANDLE_REQUEST_INPUT;
    		ret = ioctl(req[0].fd, GPIOHANDLE_SET_CONFIG_IOCTL, &swdio_config);
    		if (ret == -1) {
    			ret = -errno;
    			fprintf(stderr, "Failed to issue %s (%d)\n",
    					"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
    		}

			read = true;
		}
		/* else if (test_here++ % 100 == 0) */
		/* { */
            /* usleep(10000); */
            /* swdio_config.flags = GPIOHANDLE_REQUEST_OUTPUT; */
            /* ret = ioctl(req[0].fd, GPIOHANDLE_SET_CONFIG_IOCTL, &swdio_config); */
            /* if (ret == -1) { */
                /* ret = -errno; */
                /* fprintf(stderr, "Failed to issue %s (%d)\n", */
                        /* "GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret); */
            /* } */
			/* read = false; */
		/* } */

		if (read == true)
		{
    		ret = ioctl(req[0].fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data_swdio);
    		if (ret == -1) {
    			ret = -errno;
    			fprintf(stderr, "Failed to issue %s (%d)\n",
    					"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
    		}
			else
			{
				printf("catch swdio=%u\n", data_swdio.values[0]);
			}
		}
		else
		{
    		ret = ioctl(req[0].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    		if (ret == -1) {
    			ret = -errno;
    			fprintf(stderr, "Failed to issue %s (%d)\n",
    					"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
    		}
		}
    	usleep(10000);
	}

	/*  release line */
	ret = close(req[0].fd);
	if (ret == -1) {
		perror("Failed to close GPIO LINEHANDLE device file");
		ret = -errno;
	}
	ret = close(req[1].fd);
	if (ret == -1) {
		perror("Failed to close GPIO LINEHANDLE device file");
		ret = -errno;
	}
	return ret;
}

