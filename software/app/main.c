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
    //Calibrate the accelerometer
    //Calibrate the accelerometer
    int x_0g = 0, y_0g = 0, z_1g = 0;
    int num_samples = 10; // number of samples to take for calibration
    int i;
    for(i = 0; i < num_samples; i++){
        x_0g += lecture_i2c(DXL) | lecture_i2c(DXM) << 8;
        y_0g += lecture_i2c(DYL) | lecture_i2c(DYM) << 8;
        z_1g += lecture_i2c(DZL) | lecture_i2c(DZM) << 8;
    }
    x_0g /= num_samples;
    y_0g /= num_samples;
    z_1g /= num_samples;
    int SZ = 256; // sensitivity of the ADXL345 in LSB/g
    int x_offset = -round((x_0g / num_samples - 15.6) / 4);
    int y_offset = -round((y_0g  / num_samples - 15.6) / 4);
    int z_offset = -round((z_1g / num_samples - 15.6) / 4);
    printf("Offsets: X=%d, Y=%d, Z=%d\n", x_offset, y_offset, z_offset);

    //Write the offset values to the offset registers
    I2C_start(OPENCORES_I2C_0_BASE, ADD, 0);
	I2C_write(OPENCORES_I2C_0_BASE, OFSX, x_offset & 0xff);
    //I2C_write(OPENCORES_I2C_0_BASE, OFSX, 0);
    I2C_write(OPENCORES_I2C_0_BASE, x_offset, 0);
    I2C_start(OPENCORES_I2C_0_BASE, ADD, 0);
	I2C_write(OPENCORES_I2C_0_BASE, OFSX, y_offset & 0xff);
    //I2C_write(OPENCORES_I2C_0_BASE, OFSY, 0);
    I2C_write(OPENCORES_I2C_0_BASE, y_offset, 0);
    I2C_start(OPENCORES_I2C_0_BASE, ADD, 0);
	I2C_write(OPENCORES_I2C_0_BASE, OFSX, z_offset & 0xff);
    //I2C_write(OPENCORES_I2C_0_BASE, OFSZ, 0);
    I2C_write(OPENCORES_I2C_0_BASE, z_offset, 0);
	while(1){
	usleep(70000);

	datax0 =  lecture_i2c(DXL); 
	datax1 =  lecture_i2c(DXM);
	datay0 = lecture_i2c(DYL);
	datay1=  lecture_i2c(DYM);
	dataz0 =  lecture_i2c(DZL);
	dataz1 = lecture_i2c(DZM);
	
	int x_actual = ((datax1 <<8)| datax0) - x_offset;
    int y_actual = ((datay1 <<8)| datay0) - y_offset;
    int z_actual = (((dataz1 <<8)| dataz0) - z_offset) ;//+ SZ;
	


	//printf("----------------------------\n Axis X: %d\n Axis Y: %d\n Axis Z: %d\n ----------------------------\n",((datax1 <<8)| datax0),((datay1 <<8)| datay0),((dataz1 <<8)| dataz0)) ;
	printf("----------------------------\n Axis X: %d\n Axis Y: %d\n Axis Z: %d\n ----------------------------\n",x_actual,y_actual,z_actual );
		
		
	}

    return 0;
}