/* Author : Chakin
 * e-mail : Sbe3
 */


#include <system.h>
#include <sys/alt_stdio.h>
#include "opencores_i2c.h"
#include <stdio.h>


#define ADD 0x1D
#define DXL 0x32
#define DXM 0x33
#define DYL 0x34
#define DYM 0x35
#define DZL 0x36
#define DZM 0x37
#define OFSX 0x1E
#define OFSY 0x1F
#define OFSZ 0x20

alt_8 I2c_data,datax0,datax1,datay0,datay1,dataz0,dataz1;
int x,y,z;



int lecture_i2c(alt_8 reg)
{
    int dex;
    I2C_start(OPENCORES_I2C_0_BASE, 0x1d, 0); 
    I2C_write(OPENCORES_I2C_0_BASE, reg, 0);  
    I2C_start(OPENCORES_I2C_0_BASE, 0x1d, 1); 
    dex = I2C_read(OPENCORES_I2C_0_BASE, 1);   

    return dex;
}




int main(int argc, char *argv[])
{
    I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_CPU_FREQ,100000);

    I2c_data = I2C_start(OPENCORES_I2C_0_BASE,ADD,0);

	if ( I2c_data == 0){
			printf("Gyro read : %x\n",ADD);
			
		}

    else {
			printf("Error adress\n");}
	
	while(1){
	usleep(40000);

	datax0 =  lecture_i2c(DXL); 
	datax1 =  lecture_i2c(DXM);
	datay0 = lecture_i2c(DYL);
	datay1=  lecture_i2c(DYM);
	dataz0 =  lecture_i2c(DZL);
	dataz1 = lecture_i2c(DZM);
	
	printf("----------------------------\n Axis X: %d\n Axis Y: %d\n Axis Z: %d\n ----------------------------\n",((datax1 <<8)| datax0)/OFSX,((datay1 <<8)| datay0)/OFSY,((dataz1 <<8)| dataz0))/OFSZ ;
		
		
	}

    return 0;
}

