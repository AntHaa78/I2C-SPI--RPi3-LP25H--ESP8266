#include <stdio.h>
#include <fcntl.h> // for open function
#include <unistd.h> // for close function, usleep function
#include <stdlib.h> // for exit(1)
#include <sys/ioctl.h> // fpr ioctl func
#include <linux/i2c-dev.h> // for I2C_SLAVE
#include <i2c/smbus.h> //for all i2c_smbus functions? avoid implicit declaration of function error
#include <stdint.h> // for 8 bit and 16 bit
#include <string.h> // compare strings
#include <linux/spi/spidev.h>


#define DEVPATH_I2C "/dev/i2c-1" // find it with i2cdetect -l
#define DEV_ID 0x5c // address of lps25h sensor

#define DEVPATH_SPI "/dev/spidev0.0" //check /dev folder, two choices 0.0 or 0.1
#define SPI_MODE SPI_MODE_0
#define SPI_SPEED 1000000 // 1 MHz
#define SPI_BIT_PER_WORD 8

// Refer to st.com/resource/en/datasheet/lps25h.pdf page 20 for registers address map
#define WHO_AM_I 0x0F // ID register of sensor
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define TEMP_OUT_L 0x2B
#define TEMP_OUT_H 0x2C
#define PRESS_OUT_XL 0x28
#define PRESS_OUT_L 0x29
#define PRESS_OUT_H 0x2A

void i2c_com()
{
	// Open i2c comms
	int i2c_fd = 0;
	i2c_fd = open(DEVPATH_I2C, O_RDWR);
	if (i2c_fd == -1) {
		//use perror? perror("Cannot open the i2c bus");
		printf("Cannot open the i2c bus");
		exit(1);
	}

	
	//Configure i2c slave
	if (ioctl(i2c_fd, I2C_SLAVE, DEV_ID) == -1){
		printf("Cannot access slave");
		close(i2c_fd);
		exit(1);
	}
	//printf("%d", ioctl(i2c_fd, I2C_SLAVE, DEV_ID));
	//printf("\n%d", sizeof(I2C_SLAVE));
	
	
	// ID check of sensor. The expected value of the byte of data from the who am I register should be 10111101 (documentation) or 0xBD in hex.

	if (i2c_smbus_read_byte_data(i2c_fd, WHO_AM_I) != 0xBD){
		printf("Fail identification");
		close(i2c_fd);
		exit(1);
	}
	printf("Sensor loaded and ready!\n");
	

	
	// Power down/Clean start
	i2c_smbus_write_byte_data(i2c_fd, CTRL_REG1, 0x00);
	
    //Turn on the pressure sensor, one shot configuration. 
    //BDU(block data update) on or off?  10000100 or 10000000? 0x84 or 0x80?
    // From https://www.pololu.com/file/0J762/LPS25H-AN4450-Hardware-and-software-guidelines.pdf, we use 0x84
    i2c_smbus_write_byte_data(i2c_fd, CTRL_REG1, 0x84);

    //Run one-shot measurement (temperature and pressure), the set bit will be reset by the
    // sensor itself after execution (self-clearing bit) 00000001

    i2c_smbus_write_byte_data(i2c_fd, CTRL_REG2, 0x01);	
    
    // Wait until measurement is complete
    
    while (i2c_smbus_read_byte_data(i2c_fd, CTRL_REG2) !=0){
		usleep(1000 * 100);
		}
    
	
	// Temperature data
	// From the doc (page33) we get 2 bytes, TEMP_OUT_H and TEMP_OUT_L, which form a binary signed 2's complement (16 digits), which we will call TEMP_OUT.
	// To build a 16-bit value from two 8-bit inputs, we use: 16bit = (8bit_a << 8) | 8bit_b
	// (We then need to convert it to a float/double, or not, can directly use %f in print, need to cast (float) though), and finally use the formula given in doc: T = 42.5 +(TEMP_OUT/480)
	
	//unsigned char temp_out_h = 0;
	//unsigned char temp_out_l = 0;
	uint8_t temp_out_h = 0;
	uint8_t temp_out_l = 0;	
	int16_t TEMP_OUT = 0;
	
	
	temp_out_h = i2c_smbus_read_byte_data(i2c_fd, TEMP_OUT_H);
	temp_out_l = i2c_smbus_read_byte_data(i2c_fd, TEMP_OUT_L);
	TEMP_OUT = (temp_out_h << 8) | temp_out_l;
	printf("\nThe measure of TEMP_OUT IS: %d", TEMP_OUT);
	printf("\nTemperature is : %.2f degrees C\n", 42.5+((float)TEMP_OUT/480.0));
	
	
	// Pressure data
	// For pressure we get 3 bytes, to build a 24-bit value: 24_bit = (8bit_a << 16) | (8bit_b << 8 ) | 8bit_c
	// Then use formula given: P(hPa) = P_OUT / 4096
	
	uint8_t press_out_h = 0;
	uint8_t press_out_l = 0;
	uint8_t press_out_xl = 0;
	uint32_t P_OUT = 0;
	
	press_out_h = i2c_smbus_read_byte_data(i2c_fd, PRESS_OUT_H);
	press_out_l = i2c_smbus_read_byte_data(i2c_fd, PRESS_OUT_L);
	press_out_xl = i2c_smbus_read_byte_data(i2c_fd, PRESS_OUT_XL);
	P_OUT = (press_out_h << 16) | (press_out_l << 8) | press_out_xl;
	printf("\nThe measure of P_OUT is: %d", P_OUT);
	printf("\nPressure is : %.2f hPa\n", ((float)P_OUT/4096.0));	
	printf("Average atmospheric pressure is 1013 hPa");
	
	close(i2c_fd);
	printf("\n\nEnd of I2C");
}

void spi_com()
{
	//Open spi communication
	int spi_fd = 0;
	spi_fd = open(DEVPATH_SPI, O_RDWR);
	if (spi_fd == -1) {
		//use perror? perror("Cannot open the spi bus");
		printf("Cannot open the spi bus");
		exit(1);
	}
	
	// Need to initialize clock speed, data format, chip select pins(no need?)
	
	//Read SPI mode
	uint8_t mode;
	//uint32_t mode2;
	//printf("\n%d", ioctl(spi_fd, SPI_IOC_RD_MODE, &mode)); 	
	//printf("\n%d", ioctl(spi_fd, SPI_IOC_RD_MODE32, &mode2)); 
	if (ioctl(spi_fd, SPI_IOC_RD_MODE, &mode) == -1){
		printf("Cannot read SPI mode");
		close(spi_fd);
		exit(1);
	}
	mode = SPI_MODE; // or mode |= SPI_MODE?
	
	// Write SPI mode
	if (ioctl(spi_fd, SPI_IOC_WR_MODE, &mode) == -1){
		printf("Cannot write SPI mode");
		close(spi_fd);
		exit(1);
	}	
	
	// Read max SPI speed
	uint32_t speed;
	//printf("%d", ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed));
	if (ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1){
		printf("Cannot read SPI max speed");
		close(spi_fd);
		exit(1);
	}
	speed = SPI_SPEED;
	
	//	Write max SPI speed
	if (ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1){
		printf("Cannot write SPI max speed");
		close(spi_fd);
		exit(1);
	}
	
	// Write word length (bits per word)
	uint8_t bits = SPI_BIT_PER_WORD;
	if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1){
		printf("Cannot set SPI bits per word");
		close(spi_fd);
		exit(1);
		}
	
	
	// To send the command to take a measurement and read data we use struct spi_ioc_transfer (spidev.h)
	// Need to find what is the command to take measurement (tried 0x84 / 0x01->0x09)
	// need delay? Manual CS change HIGH/LOW?
	
	uint8_t tx_buffer[2] = {???, ???};
	uint8_t rx_buffer[2];
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx_buffer,
		.rx_buf = (unsigned long)rx_buffer,
		.len = 2
		};
	
	
	//~ uint8_t tx_buffer[2];
	//~ uint8_t rx_buffer[2];
	//~ struct spi_ioc_transfer tr;
	//~ tr.tx_buf = (unsigned long)tx_buffer;
	//~ tr.tx_buf = (unsigned long)tx_buffer;
	//~ tr.len = 2;
	
	//~ tx_buffer[0]=0xB0;
	//~ tx_buffer[1]=0x00;


	int status;
	status = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
	if(status<1){
		printf("SPI transfer returned %d...\r\n", status);
		printf("error during SPI transfer");
		close(spi_fd);
		exit(1);	
		}
	printf("SPI transfer returned %d...\r\n", status);	
	printf("\nReceived SPI buffer...:\r\n");
	printf("\n%#02X", rx_buffer[0]);
	printf("\n%#02X", rx_buffer[1]);
	

	
	//uint16_t temp = (rx_buffer[1] << 8) | rx_buffer[0];
	//float temp_celsius = 42.5 + ((float)temp/480.0);
	//printf("\nThe measure of temp is: %d", temp);
	//printf("\nTemperature is : %.2f degrees C\n", temp_celsius);
	
	
	
	printf("\nWorking fine");
	close(spi_fd);
}

int main()
{
	printf("Choose I2C or SPI: ");
	char answer[]="";
	scanf("%s", answer);
	
	if (strcmp(answer,"i2c") == 0){
		i2c_com();
	}	
	
	if (strcmp(answer,"spi") == 0){
		spi_com();
	}	
	

	return 0;	
}
	

// compile with -li2c at the end
