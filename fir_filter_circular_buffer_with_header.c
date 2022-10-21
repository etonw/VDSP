#include "ADDS_21489_EzKit.h"
#include <processor_include.h> //includes for using circindex function

float pm h[]=
{
  #include "fir_coef6.txt"
};

#define NN (sizeof(h)/sizeof(float)) //Number of coeficients

float dm regB[NN]={0};
    const int N=NN-1;//Filter order
    int i=0;
    int regHead = NN-1;
    
void process_AD1939_samples( int sig_int)
{
    Receive_ADC_Samples();
    int j;
    j=regHead;
    regB[regHead]=Left_Channel_In1;
    float sum=0;

//
 
     for(i=0;i<(N+1);i++)
     {
         sum+=h[i]*regB[j];
         j=circindex(j,1,N);
     }
     regHead--;
     if(regHead<0)
     regHead=N-1;
     
//// Filter code stops here ////

Left_Channel_Out1 = sum;
Right_Channel_Out1 = Right_Channel_In2;
      Transmit_DAC_Samples();
} 
