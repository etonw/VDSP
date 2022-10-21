//FIR code implemented using shift register

#include "ADDS_21489_EzKit.h"
const float pm B[] = //placing the coefficients in the program memory.(pm)
{
    #include "fir_coef.txt" //coefficients from the matlab file.
};
#define coefficients (sizeof(B)/sizeof(float)) // defines the size of the vector
float dm inputx[coefficients]={0}; // stores the input values in the data memory(dm)

int N = coefficients-1;
float out=0;
int i = 0;

void process_AD1939_samples( int sig_int)
{
 /* Perform AD1939 Audio Processing Here Using 32-bit Floating-point Math
 (Note: The ADC/DAC variables below are used to "double-buffer" the audio
 samples with temporary variables, allowing active DMA completion of
 rx1a_buf[] and tx0a_buf[]) */

 Receive_ADC_Samples();

for(i=N; i>0; i--) // for i bigger than 0, the register will shift the position one to the left.
{
  inputx[i] = inputx[i-1];
}
inputx[0] = Left_Channel_In1; //register input of DSP
  
out = B[0] * inputx[0]; //computing coefficients and input at position 0.

for(i = 1; i <= N; i++)
{
//summing the products of inputs and corresponding coefficients.
out += B[i] * inputx[i];
}
  
Left_Channel_Out3 = out; //send y[n] to output of DSP
  Transmit_DAC_Samples();
}
