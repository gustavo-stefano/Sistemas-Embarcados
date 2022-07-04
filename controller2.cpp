#include "mbed.h"
#include "Servo.h"

Servo leg2(p21);
Servo shoulder2(p22);
Servo leg4(p23);
Servo shoulder4(p24);
Servo leg6(p25);
Servo shoulder6(p26);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);


CAN can(p30, p29);//setting CAN interface
CANMessage msg;

int clock_freq = 100000000;  //used by peripherals to adjust frequency

//--------CAN messages dictionary-----
int fwd = 1302; //instruction to move foward
int bwd = 1303;// ... backward
int stnd = 1304; //... standBy
//==================================
//---------Commands-----------------
int direction = 2; //0-> foward; 1 -> backward ; 2->standby

//-----Functions--------
void Init_Timer_us();
void us(int t);//timer peripheral set
void standBy();
void foward();
void backward();
void recv_CAN(); //function to recieve intructions from linux terminal 

int main() { 
    Init_Timer_us();  
    
    LPC_GPIO0->FIODIR |= (1 << 9); // Setting P5 as output for triggering the second board 
    
    //stand up
    leg2 = 0.5f;
    leg4 = 0.5f;
    leg6 = 0.5f;
    //--x--
    can.frequency(500000);
    //energize sholders
    shoulder2 = 1.0f;
    shoulder4 = 1.0f;
    shoulder6 = 1.0f;
    //--x--
    
    while(1){
        recv_CAN();//recieve instructions for CAN bus
    }
    
}

void standBy(){
    //stand up
    leg2 = 0.5f;
    leg4 = 0.5f;
    leg6 = 0.5f;
    //--x--
    
    //energize sholders
    shoulder2 = 0.5f;
    shoulder4 = 0.5f;
    shoulder6 = 0.5f;
    
     //stand by led indicator
    led1 = 1;
    led2 = 1;
    led3 = 1;
    led4 = 1;
}


void foward(){
        //rising leg2
        for(float i = 0.5f; i < 1.0f; i += 0.01f){
            leg2 = i;
            us(9999);//step 
        }
        leg2 = 1.0f;
        //--x--
        //sholder 2 moving foward
        for(float i = 0.7f; i > 0.4f; i-= 0.01f){
            shoulder2 = i;
            us(9999);//step
        }
        shoulder2 = 0.4f;
        //--x--
        //falling leg2
        for(float i = 1.0f; i > 0.4f; i-= 0.01f){
            leg2 = i;
            us(9999);//step
        }
        leg2 = 0.4f;
        
        //--x--
        
        //rising leg4
        for(float i = 0.4f; i < 1.0f; i += 0.01f){
            leg4 = i;
            us(9999);//step
        }
        leg4 = 1.0f;
        //--x--
        //sholder 4 moving foward
        for(float i = 0.7f; i > 0.4f; i-= 0.01f){
            shoulder4 = i;
            us(9999);//step
        }
        shoulder4 = 0.4f;
        //--x--
        //falling leg4
        for(float i = 1.0f; i > 0.4f; i-= 0.01f){
            leg4 = i;
            us(9999);//step
        }
        leg4 = 0.4f;
        //--x--
        
        //rising leg6
        for(float i = 0.4f; i < 1.0f; i += 0.01f){
            leg6 = i;
            us(9999);//step
        }
        leg6 = 1.0f;
        //--x--
        //sholder 6 moving foward
        for(float i = 0.7f; i > 0.4f; i-= 0.01f){
            shoulder6 = i;
            us(9999);//step
        }
        shoulder6 = 0.4f;
        //--x--
        //falling leg6
        for(float i = 1.0f; i > 0.4f; i-= 0.01f){
            leg6 = i;
            us(9999);//step
        }
        leg6 = 0.4f;
        //all the shoulders moving backward
        for(float i = 0.7f; i > 0.4f ; i-= 0.01f){
            shoulder2 = i;
            shoulder4 = i;
            shoulder6 = i;
            us(9999);//step
        }
}

void backward(){
    //rising leg2
        for(float i = 0.6f; i < 1.0f; i+= 0.01f){
            leg2 = i;
            us(9999);//step
        }
        leg2 = 1.0f;
        //--x--
        //sholder 2 moving backward
        for(float i = 1.0f; i > 0.5f; i-= 0.01f){
            shoulder2 = i;
            us(9999);//step
        }
        shoulder2 = 0.5f;
        //--x--
        //falling leg2
        for(float i = 1.0f; i > 0.6f; i -= 0.01f){
            leg2 = i;
            us(9999);//step
        }
        leg2 = 0.6f;
        
        //--x--
        
        //rising leg4
        for(float i = 0.6f; i < 1.0f; i+= 0.01f){
            leg4 = i;
            us(9999);//step
        }
        leg4 = 1.0f;
        //--x--
        //sholder 4 moving backward
        for(float i = 0.9f; i > 0.6f; i-= 0.01f){
            shoulder4 = i;
            us(9999);//step
        }
        shoulder4 = 0.6f;
        //--x--
        //falling leg4
        for(float i = 1.0f; i > 0.6f; i -= 0.01f){
            leg4 = i;
            us(9999);//step
        }
        leg4 = 0.6f;
        //--x--
        
        //rising leg6
        for(float i = 0.5f; i < 0.7f; i+= 0.01f){
            leg6 = i;
            us(9999);//step
        }
        leg6 = 0.7f;
        //--x--
        //sholder 6 moving backward
        for(float i = 1.0f; i > 0.6f; i -= 0.01f){
            shoulder6 = i;
            us(9999);//step
        }
        shoulder6 = 0.6f;
        //--x--
        //falling leg6
        for(float i = 0.7f; i > 0.5f; i -= 0.01f){
            leg6 = i;
            us(9999);//step
        }
        leg6 = 0.5f;
        
        //all the shoulders moving foward
        for(float i = 0.6f; i < 1.0f ; i+= 0.01f){
            shoulder2 = i;
            shoulder4 = i;
            shoulder6 = i;
            us(9999);//step
        }
        
}

void recv_CAN(){
    CANMessage msg;
    if(can.read(msg)){
        if(msg.id == fwd){
            LPC_GPIO0->FIOPIN |= (1 << 9); // Write p5 state as HIGH
            us(200000);//wait 200 ms     
            LPC_GPIO0->FIOPIN &= ~(1 << 9); // Write p5 state as LOW
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
            standBy();//standBy after the step
        }
        if(msg.id == bwd){
            LPC_GPIO0->FIOPIN |= (1 << 9); // Write p5 state as HIGH
            us(200000);//wait 200 ms     
            LPC_GPIO0->FIOPIN &= ~(1 << 9); // Write p5 state as LOW
            
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
            
            standBy(); //stand by after the step
        }
        if(msg.id == stnd){
            LPC_GPIO0->FIOPIN |= (1 << 9); // Write p5 state as HIGH
            us(200000);//wait 200 ms     
            LPC_GPIO0->FIOPIN &= ~(1 << 9); // Write p5 state as LOW
            
            standBy();
            
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
