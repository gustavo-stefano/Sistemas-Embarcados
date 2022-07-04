#include "mbed.h"
#include "Servo.h"

Servo leg1(p21);
Servo shoulder1(p22);
Servo leg3(p23);
Servo shoulder3(p24);
Servo leg5(p25);
Servo shoulder5(p26);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);


CAN can(p30, p29);//setting CAN interface
CANMessage msg;

int clock_freq = 100000000;  //used by peripherals to adjust frequency

//--------CAN messages dictionary-----
int fwd = 1300; //instruction to move foward
int bwd = 1301;// ... backward
//==================================
//---------Commands-----------------
int direction = 2; //0-> foward; 1 -> backward ; 2->standby

//-----Functions--------
void Init_Timer_us();
void us(int t);//timer peripheral set
void standBy();
void foward();
void backward();
void EINT0_IRQHandler();//interrupt request handler for external trigger
void recv_CAN(); //function to recieve intructions from linux terminal 

int main() { 
    Init_Timer_us();  
    
    //stand up
    leg1 = 0.5f;
    leg3 = 0.5f;
    leg5 = 0.5f;
    //--x--
    LPC_GPIOINT->IO0IntEnR |= (1 << 1); //set p10 for interrupt
    NVIC_EnableIRQ(EINT0_IRQn); //turn on external interrupt 3
    
    can.frequency(500000);
    //energize sholders
    shoulder1 = 1.0f;
    shoulder3 = 1.0f;
    shoulder5 = 1.0f;
    //--x--
    
    while(1){
        recv_CAN();//recieve instructions for CAN bus
        EINT0_IRQHandler();//Interrupt request for movements routines
    }
    
}

void standBy(){
    //stand up
    leg1 = 0.5f;
    leg5 = 0.5f;
    leg3 = 0.5f;
    //--x--
    
    //energize sholders
    shoulder1 = 0.5f;
    shoulder3 = 0.5f;
    shoulder5 = 0.5f;
}


void foward(){
        //rising leg1
        for(float i = 0.5f; i < 1.0f; i += 0.01f){
            leg1 = i;
            us(9999);//step 
        }
        leg1 = 1.0f;
        //--x--
        //sholder 1 moving foward
        for(float i = 0.7f; i > 0.4f; i-= 0.01f){
            shoulder1 = i;
            us(9999);//step
        }
        shoulder1 = 0.4f;
        //--x--
        //falling leg1
        for(float i = 1.0f; i > 0.4f; i-= 0.01f){
            leg1 = i;
            us(9999);//step
        }
        leg1 = 0.4f;
        //--x--
        
        //rising leg3
        for(float i = 0.4f; i < 1.0f; i += 0.01f){
            leg3 = i;
            us(9999);//step
        }
        leg3 = 1.0f;
        //--x--
        //sholder 3 moving foward
        for(float i = 0.7f; i > 0.4f; i-= 0.01f){
            shoulder3 = i;
            us(9999);//step
        }
        shoulder3 = 0.4f;
        //--x--
        //falling leg3
        for(float i = 1.0f; i > 0.4f; i-= 0.01f){
            leg3 = i;
            us(9999);//step
        }
        leg3 = 0.4f;
        //--x--
        
        //rising leg5
        for(float i = 0.4f; i < 1.0f; i += 0.01f){
            leg5 = i;
            us(9999);//step
        }
        leg5 = 1.0f;
        //--x--
        //sholder 5 moving foward
        for(float i = 0.7f; i > 0.4f; i-= 0.01f){
            shoulder5 = i;
            us(9999);//step
        }
        shoulder5 = 0.4f;
        //--x--
        //falling leg5
        for(float i = 1.0f; i > 0.4f; i-= 0.01f){
            leg5 = i;
            us(9999);//step
        }
        leg5 = 0.4f;
        
        //all the shoulders moving backward
        for(float i = 0.7f; i > 0.4f ; i-= 0.01f){
            shoulder1 = i;
            shoulder3 = i;
            shoulder5 = i;
            us(9999);//step
        }
}

void backward(){
    //rising leg1
        for(float i = 0.6f; i < 1.0f; i+= 0.01f){
            leg1 = i;
            us(9999);//step
        }
        leg1 = 1.0f;
        //--x--
        //sholder 1 moving backward
        for(float i = 1.0f; i > 0.5f; i-= 0.01f){
            shoulder1 = i;
            us(9999);//step
        }
        shoulder1 = 0.5f;
        //--x--
        //falling leg1
        for(float i = 1.0f; i > 0.6f; i -= 0.01f){
            leg1 = i;
            us(9999);//step
        }
        leg1 = 0.6f;
        
        //--x--
        
        //rising leg3
        for(float i = 0.6f; i < 1.0f; i+= 0.01f){
            leg3 = i;
            us(9999);//step
        }
        leg3 = 1.0f;
        //--x--
        //sholder 3 moving backward
        for(float i = 0.9f; i > 0.6f; i-= 0.01f){
            shoulder3 = i;
            us(9999);//step
        }
        shoulder3 = 0.6f;
        //--x--
        //falling leg3
        for(float i = 1.0f; i > 0.6f; i -= 0.01f){
            leg3 = i;
            us(9999);//step
        }
        leg3 = 0.6f;
        //--x--
        
        //rising leg5
        for(float i = 0.5f; i < 0.7f; i+= 0.01f){
            leg5 = i;
            us(9999);//step
        }
        leg5 = 0.7f;
        //--x--
        //sholder 5 moving backward
        for(float i = 1.0f; i > 0.6f; i -= 0.01f){
            shoulder5 = i;
            us(9999);//step
        }
        shoulder5 = 0.6f;
        //--x--
        //falling leg5
        for(float i = 0.7f; i > 0.5f; i -= 0.01f){
            leg5 = i;
            us(9999);//step
        }
        leg5 = 0.5f;
        
        //all the shoulders moving foward
        for(float i = 0.6f; i < 1.0f ; i+= 0.01f){
            shoulder1 = i;
            shoulder3 = i;
            shoulder5 = i;
            us(9999);//step
        }
        
}

void recv_CAN(){
    CANMessage msg;
    if(can.read(msg)){
        if(msg.id == fwd){
            direction = 0;
        }
        if(msg.id == bwd){
            direction = 1;
        }
    }
}
void Init_Timer_us(){
    LPC_SC->PCONP |=1<<22;//Enable Timer2
    LPC_TIM2->CTCR = 0;//TImer mode
    LPC_SC->PCLKSEL1 = 2<<14; //clk/4
    LPC_TIM2->PR = clock_freq/4/1000000-1;//1us
}


void us(int t){
    t = t - 15;//intrinsic delay of 15 us
    LPC_TIM2->TCR = 1<<1; //reset timer
    LPC_TIM2->TCR = 1; //enable timer
    while(LPC_TIM2->TC < t);
}

void EINT0_IRQHandler() {
    // If the rising edge interrupt was triggered
    if((LPC_GPIOINT->IO0IntStatR >> 1) & 1){
        LPC_GPIOINT->IO0IntClr |= (1 << 1); //clear
        if(direction == 1){
            foward();//
            
            //foward pattern for leds 
            led1 = 1;
            us(100000);
            led1 = 0;
            led2 = 1;
            us(100000);
            led2 = 0;
            led3 = 1;
            us(100000);
            led3 = 0;
            led4 = 1;
            us(100000);
            led4 = 0;
            direction = 2;//standBy after the step
        }
        else if(direction == 0){
            backward();
            
            //backward pattern for leds
            led4 = 1;
            us(100000);
            led4 = 0;
            led3 = 1;
            us(100000);
            led3 = 0;
            led2 = 1;
            us(100000);
            led2 = 0;
            led1 = 1;
            us(100000);
            led1 = 0;
            
            direction = 2;//standBy after the step
        }
        else if(direction == 2){
            
            //stand by led indicator
            led1 = 1;
            led2 = 1;
            led3 = 1;
            led4 = 1;
        }
    }
}
