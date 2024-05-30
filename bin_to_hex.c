#include <stdint.h> 
#include <stdio.h>

void binary_to_hex(unsigned long int binaryval)
	{
		uint8_t hexval =0;
		int remainder =0;
		int i=1;
		while (binaryval!=0){
			remainder = binaryval%10;
			hexval = hexval + remainder*i;
			i=i*2;
			binaryval = binaryval/10;}
		printf("The corresponding hex value is: %#02X\n", hexval);
	}

int main(){
	unsigned long int binaryval = 0;
	printf("Enter a binary: ");
	scanf("%lu", &binaryval);
	binary_to_hex(binaryval);		
}
