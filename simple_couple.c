#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

int main()
{
	int i, j;
	char devname[]="/dev/pty--";
	char s1[]="pqrstuvwxyzabcde";
	char s2[]="0123456789abcdef";
	int fds, fdm = -1;

	for (i=0; fdm<0 && i<16; i++) {
		for (j=0; fdm<0 && j<16; j++) {
			devname[8] = s1[i];
			devname[9] = s2[j];
			if ((fdm = open(devname, O_RDWR)) < 0) {
				if (errno == EIO) continue;
				exit(1);
			}
		}
	}
	devname[5]='t';        //   /dev/ttyXY
	if ((fds = open(devname, O_RDWR)) < 0)
		exit(2);
	exit(0);
}
