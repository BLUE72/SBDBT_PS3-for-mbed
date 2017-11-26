#include "mbed.h"

Serial pc(USBTX, USBRX);
Serial sbdbt(tx, rx);    //使用するボードに合わせて変更
uint8_t DAT[8] = {0};

void sbdbt_rx (){
    DAT[0] = sbdbt.getc();
    if(DAT[0] == 0x80){
        for (int i=1;i<8;i++){
            DAT[i] = sbdbt.getc();
        }
    }
}

int main(){
    sbdbt.baud(2400);
    pc.baud(9600);
    sbdbt.format(8, Serial::None, 1);
    sbdbt.attach(sbdbt_rx, Serial::RxIrq);

    while(1){
        pc.printf("\r");

        pc.printf("LX:%3d ",(int)64-(int)(DAT[3]));
        pc.printf("LY:%3d ",(int)64-(int)(DAT[4]));
        pc.printf("RX:%3d ",(int)64-(int)(DAT[5]));
        pc.printf("RY:%3d ",(int)64-(int)(DAT[6]));
        
        if((DAT[2]>>0)&1 == 1){
            pc.printf("Up ");
        }
        if((DAT[2]>>1)&1 == 1){
            pc.printf("Down ");
        }
        if((DAT[2]>>2)&1 == 1){
            pc.printf("Right ");
        }
        if((DAT[2]>>3)&1 == 1){
            pc.printf("Left ");
        }
        if((DAT[2]>>4)&1 == 1){
            pc.printf("Triangle ");
        }
        if((DAT[2]>>5)&1 == 1){
            pc.printf("Cross ");
        }
        if((DAT[2]>>6)&1 == 1){
            pc.printf("Circle ");
        }
                
        if((DAT[1]>>0)&1 == 1){
            pc.printf("Square ");
        }           
        if((DAT[1]>>1)&1 == 1){
            pc.printf("L1 ");
        }
        if((DAT[1]>>2)&1 == 1){
            pc.printf("L2 ");
        }
        if((DAT[1]>>3)&1 == 1){
            pc.printf("R1 ");
        }
        if((DAT[1]>>4)&1 == 1){
            pc.printf("R2 ");
        }
        
        if(((DAT[2]>>0)&1 == 1) && ((DAT[2]>>1)&1 == 1)){
            pc.printf("Start ");
        }
        
        pc.printf("\n");
        wait(0.05);
    }
}
