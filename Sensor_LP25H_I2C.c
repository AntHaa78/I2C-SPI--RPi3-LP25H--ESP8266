#include <stdio.h>
#include <fcntl.h> // for open function
#include <unistd.h> // for close function
#include <stdlib.h> // for exit(1)
#include <sys/ioctl.h> // fpr ioctl func
#include <linux/i2c-dev.h> // for I2C_SLAVE

#define DEVPATH_I2C "/dev/i2c-1" // find it with i2cdetect -l
#define DEV_ID 0x5c // address of lps25h sensor

int main()
{
	// Open i2c comms
	int i2c=0;
	i2c = open(DEVPATH_I2C, O_RDWR);
	if (i2c == -1) {
		//perror("Too bad");
		printf("Can not access device");
		exit(1);
	}
	//printf("Working");
	
	//Configure i2c slave
	if (ioctl(i2c, I2C_SLAVE, DEV_ID) == -1){
		printf("ERROR");
		close(i2c);
		exit(1);
	}
	printf("%d", ioctl(i2c, I2C_SLAVE, DEV_ID));
	//printf("\n%d", sizeof(I2C_SLAVE));
	
	
	close(i2c);
	return 0;
}

