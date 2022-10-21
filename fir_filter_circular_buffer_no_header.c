#include "ADDS_21489_EzKit.h"
#include "processor_include.h"

float pm h[]=
{
#include "fir_coef6.txt"
};


#define NN (sizeof(h)/sizeof(float)) //Number of coeficients
float dm regB[NN]={0};

const unsigned short N=NN-1;//Filter order
unsigned short pm i = 0;
unsigned short pm j = 0;

void process_AD1939_samples( int sig_int)
{
Receive_ADC_Samples();


float sum=0;
regB[j]=Left_Channel_In1; //register input of DSP in position j

for(i=0;i<(N+1);i++) //compute the products
{
sum+=h[i]*regB[j];
j=circindex(j,1,N); //change j in the circular buffer
}

Left_Channel_Out1 = sum;
Right_Channel_Out1 = Right_Channel_In2;
Transmit_DAC_Samples();
}
