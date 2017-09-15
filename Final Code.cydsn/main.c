#include "project.h"
#include "stdio.h"
#include "math.h" 
#include "stdlib.h"

float count_l, count_r, distance;
// For displaying the colours of the LED's
int i=0;
uint32 room;
uint32 red;
uint32 blue;
uint32 green;
uint16 countUS = 0;
float dm_USFL;
float dm_USFR;
float dm_USL;
float dm_USR;
int flag=0;
int flag_task = 0;
int count = 0;
char count_str[30];
char colour[50];
char initial[50];
char PD_Current[50];
char string2[300];
const int max_speed = 65535;
const int LeftDelta = 300;
void Left_Motor(float speed, int direction, int state);
void Right_Motor(float speed, int direction, int state);
//void Go_Straight(int speed, int direction, float destination);
void MoveStraight(float LeftSpeed, float RightSpeed, float Distance, int Direction, int LeftDelta);
void Stop_Rover(void);
void Turn_Left(int degrees);
void Turn_Right(int degrees);
void Colour();
//void Task1();
//int Task2(void);
//int Task3(void);
//int Task4(void);
float Ultrasonic_Sensor(int usonic);
float R_PWM_s = 50;				// Right PWM --> moving straight
float L_PWM_s = 50;			// Left PWM --> moving straight
//void Reset_Tasks();
//void OnOff();
int robot_angle; 
//void Front_Block_Detection (void);
//void Side_Block_Detection (void);
int Correction();



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start components
    Clock_1_Start();
    QuadDec_L_Start();
    QuadDec_R_Start();
    UART_Start();
    TIA_Start();
    IDAC8_Start();
    
//    IDAC8_SetValue(1);
    ADC_Start();
    count_l = 0, count_r = 0;
    QuadDec_L_SetCounter(0);
    QuadDec_R_SetCounter(0);
    
    IDAC8_Wakeup();
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    room = abs(ADC_GetResult32());
    IDAC8_Sleep();
    
    sprintf(initial, "I got a small dick = %lu\n", room);
    UART_PutString(initial);
    CyDelay(1000);
            
    for(;;)
        {
            //OnOff();
            //Reset_Tasks();
            CyDelay(1000);
            //Buzzer_Write(1);
            //CyDelay(200);
            //Buzzer_Write(0);
            
             QuadDec_L_SetCounter(0);
             QuadDec_R_SetCounter(0);
            MoveStraight(50,50,50,0,300);
//            Correction();
//            Turn_Left(90);
//            Correction();
//            CyDelay(5000);
           /*
            if (flag_task == 1)
            {
                switch(i) 
        		{
        			case 1: Task1(); break;
//        			case 2: Task2(); break;
  //      			case 3: Task3(); break;
        			//case 4: Task4(); break;
    //                case 4: Task4(); break;
        			default : break;
        		}
            }
        }
           */
        
//        Colour();

    }
//}

//void Task1() {
        //Go_Straight(30, 0, 50);
      //  MoveStraight(L_PWM_s,R_PWM_s,50,0,LeftDelta);
        //Stop_Rover();
      //  CyDelay(500);
}
//        Go_Straight(50, 1, 50);
//        Stop_Rover();
//        CyDelay(500);

//void Task2(int flag2) {
//    if (flag2) {
//        Go_Straight(50, 0, 50);
//        Stop_Rover();
//        CyDelay(500);
//        Turn_Left(180);
//        Stop_Rover();
//        CyDelay(500);
//        Go_Straight(50, 0, 50);
//        Stop_Rover();
//        CyDelay(500);
//    }
//    return;
//}
//
//void Task3(int flag3) {
//    if (flag3) {
//        Go_Straight(50, 0, 15);
//        CyDelay(500);
//        Turn_Left(90);
//        CyDelay(500);
//        Go_Straight(50, 0, 35);
//        CyDelay(500);
//        Turn_Right(90);
//        CyDelay(500);
//        Go_Straight(50, 0, 50);
//        CyDelay(500);
//        Turn_Right(90);
//        CyDelay(500);
//        Go_Straight(50, 0, 63);
//        CyDelay(500);
//        Turn_Right(90);
//        Go_Straight(50, 0, 50);
//        CyDelay(500);
//        Turn_Right(90);
//        CyDelay(500);
//        Go_Straight(50, 0, 35);
//        CyDelay(500);
//        Turn_Left(90);
//        CyDelay(500);
//        Go_Straight(50, 0, 15);
//        CyDelay(500);
//    }
//    return;
//}

/*  
    Function: Left_Motor (type void)
    Inputs: speed (as a %),
            direction (0 = fwd, 1 = bwd),
            state (1 = run, 0 = stop)
    Role: Controls the left motor, allows for turns and variable speed.
*/
/*
void OnOff()
{
    if (Flag_Read() == 1) // Flag_Read() it is the push_buttonn  
    {
        CyDelay(20);
        if (Flag_Read() == 1)
        {
            flag_task = 1;
            i++;
            if(i == 5)
            {
                i=4;
            }
        }
    }
}
*/
void Left_Motor(float speed, int direction, int state) {
    if (state == 1 ) {
        speed = (max_speed*speed)/100;
        Direction_L_Write(direction);
        PWM_L_WriteCompare(speed);
        PWM_L_Start();
    }
    else {
        PWM_L_Stop();
    }
}

void Right_Motor(float speed, int direction, int state) {
    if (state == 1 ) {
        speed = (max_speed*speed)/100;
        Direction_R_Write(direction);
        PWM_R_WriteCompare(speed);
        PWM_R_Start();
    }
    else {
        PWM_R_Stop();
    }
}

//void Go_Straight(int speed, int direction, float destination) {
//    
//    QuadDec_L_SetCounter(0);
//    QuadDec_R_SetCounter(0);
//    distance = 0;
//    
//    while(distance < destination) {
//        count_l = (float)QuadDec_L_GetCounter();
//        count_r = (float)QuadDec_R_GetCounter();
//        distance = fabs(count_l/300);
////        sprintf(count_str, "Count = %d\n", count_l);
////        UART_PutString(count_str);
//        
//        Left_Motor(speed, direction, 1);
//        Right_Motor(speed, direction, 1);
//    }
//    Stop_Rover();
//}

void MoveStraight(float LeftSpeed, float RightSpeed, float Distance, int Direction, int LeftDelta)
{
     QuadDec_L_SetCounter(0);
     QuadDec_R_SetCounter(0);
     int32 count_left = abs(QuadDec_L_GetCounter()); //Referencing to left quad decoder, updating right speed from left speed
     float temp = 30; // Initial speed at 30 and then accelerates to left and right speed 
    
    while(abs(count_left) < 5 * LeftDelta)   
    {
        // going at 30 and then accelerates to 50
    Left_Motor(temp,Direction,1);
    Right_Motor(temp+0.52,Direction,1); // Right is slower than left, assign offset of 0.51-0.53
    count_left = QuadDec_L_GetCounter();
    int32 diff = abs(QuadDec_L_GetCounter())-abs(QuadDec_R_GetCounter());
     sprintf(string2, "Count left: %d Count right: %d, diff = %ld \n ", abs(QuadDec_L_GetCounter()), abs(QuadDec_R_GetCounter()), diff);
             UART_PutString(string2);
            CyDelay(100);
    }
    
    for(;;)
    {
        RightSpeed = LeftSpeed * fabs((float)QuadDec_L_GetCounter()/(float)QuadDec_R_GetCounter());
    	Right_Motor(RightSpeed,Direction,1);
    	Left_Motor(LeftSpeed,Direction,1);
        int tempCount = fabs((float)QuadDec_L_GetCounter() / LeftDelta);
        int32 diff2 = QuadDec_L_GetCounter()-QuadDec_R_GetCounter();
            sprintf(string2, "Count left: %hd Count right: %hd, diff = %ld \n ", QuadDec_L_GetCounter(), QuadDec_R_GetCounter(), diff2);
             UART_PutString(string2);
            
    	if ( tempCount >= Distance)
    	{
    		Right_Motor(0,Direction,0);
    		Left_Motor(0,Direction,0);
            break;
    	}
        
    }
   
}	

void Stop_Rover(void) {
    Left_Motor(0, 0, 0);
    Right_Motor(0, 0, 0);
}

void Turn_Left(int degrees) {
    QuadDec_L_SetCounter(0);
    QuadDec_R_SetCounter(0);
    double turned = 0;
    while (fabs(turned) < (double) degrees) {
        
        count_l = QuadDec_L_GetCounter();
        turned = count_l / 53; // Obtained thru trial n error
        Left_Motor(20, 1, 1);
        Right_Motor(20, 0, 1);
    }
    Stop_Rover();
}

void Turn_Right(int degrees) {
    QuadDec_L_SetCounter(0);
    QuadDec_R_SetCounter(0);
    double turned = 0;
    while (fabs(turned) < (double) degrees) {
        
        count_l = QuadDec_R_GetCounter();
        turned = count_l / 53; // Obtained thru trial n error
        Left_Motor(20, 0, 1);
        Right_Motor(20, 1, 1);
    }
    Stop_Rover();
}

float Ultrasonic_Sensor(int usonic)
{
    USelect_Write(usonic);
    //UART_PutString("Trigger\n");
    while (Echo_Read() == 0)
    {
        Trigger_Write(1);       // Trigger for 10 us
        CyDelayUs(10);
        Trigger_Write(0);        // Turn Trigger Off and Reset from timer
	}
	//UART_PutString("Echo\n");
    while (Echo_Read() == 1){}
    //UART_PutString("Receives Measurement\n");
    
    int counter = UTimer_ReadCounter();
    int temp = 65535 - counter;
    double distance = temp/58;
        

    //sprintf(string, "Ultrasonic: %d \n %f \n", usonic, distance);
    //sprintf(string2, "Distance: %0.2f \n ", distance);
    sprintf(string2, "Distance: %f \n ", distance);
    UART_PutString(string2);
    return distance;
}

int Correction() {
      int IsStraight = 0;

while(IsStraight == 0){
  // Trigger F1 Ultrasonic Sensor
     dm_USFL = Ultrasonic_Sensor(0);
     CyDelay(10);
     dm_USFR = Ultrasonic_Sensor(1);
     CyDelay(10);

  CyDelay(100);

    if(dm_USFL < dm_USFR * 0.99){
        Turn_Left(1);
    }
    else if(dm_USFL> dm_USFR * 1.01){
        Turn_Right(1);
    }
    else{
        Stop_Rover();
         IsStraight =1;
    }
} 
          return 0;
}

//Ultrasonic's plan;
//Only using for block detection and wall (NOT for correcting the robot)
//Which ultrasonics would you use to detect the block? ONLY the front two AND the ultrasonic on the side you rotate to (security measure --> knows when it is safe to pass the block)! 

//When the robot DOES NOT detect anything in-front of it, so we hard-code to turn LEFT from home base 
//Detects potential case where block is on left-side
//void Front_Block_Detection (void)
//{
//    UART_PutString("What is in front of me?");
//    // Store the distance of Ultrasonics
//    dm_USFL = Ultrasonic_Sensor(0);
//    CyDelay(100);
//    dm_USFR = Ultrasonic_Sensor(1);
//    CyDelay(100);
//    //Assume block is closer than 65cm from back wall
//    int Back_wall = 65;
//    int q = 0;
//    int w = 0;
//    if(dm_USFL<Back_wall || dm_USFR<Back_wall)
//    {
//       //Now, either FL or FR ultrasonics have detected the block
//        // Assuming block is closer than 25cm (arbitrary value)
//        while(fabs(dm_USFL-dm_USFR) < 0.25)
//        {   
//            //Have to account for situations where one side is detected and the other is not
//            //The right side is closer, assuming block is infront of you
//            // Rotate the robot to the right because WE KNOW we are on the right wall, until both sides have a similar length
//            Turn_Right(q);
//            q = q+1; //Rotating by 1 degree each time
//    }
//        // Robot will know if the block is infront of it. 
//        robot_angle = q; 
//        Turn_Left(robot_angle); //Bring back to original position
//        // Straighten function goes here
//        Turn_Right(90);
//        // Straighten function goes here
//    }      
//}
//
//void Side_Block_Detection (void)
//{
//    UART_PutString("What is in front of me?");
//    // Store the distance of Ultrasonics
//    dm_USL = Ultrasonic_Sensor(2);
//    CyDelay(100);
//    int q = 0;
//    int w = 0;
//    // Need to determine where the block is infront of it
//    if(dm_USFL<30)
//    {
//        while(fabs((dm_USFR-dm_USFL)) > 2)
//        {   
//          //The right side is closer, assuming block is infront of you
//            Turn_Right(q);
//            q = q+5; //Rotating by 2 degrees each time
//    }
//    }
//}

//void Colour(){
//
//    Red_Pin_Write(0);   
//    Green_Pin_Write(0);  
//    Blue_Pin_Write(0);  
//    
//    CyDelay(100);
//    
//    IDAC8_Wakeup();
//    Red_Pin_Write(1);
//    CyDelay(20);
//    ADC_StartConvert();
//    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
//    red = abs(ADC_GetResult32());
//    Red_Pin_Write(0);
//    IDAC8_Sleep();
//    
//    CyDelay(100); 
//    
//    IDAC8_Wakeup();
//    Green_Pin_Write(1);
//    CyDelay(20);
//    ADC_StartConvert();
//    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
//    green = abs(ADC_GetResult32());
//    Green_Pin_Write(0);
//    IDAC8_Sleep();
//    
//    CyDelay(100);
//    
//    IDAC8_Wakeup();
//    Blue_Pin_Write(1);
//    CyDelay(20);
//    ADC_StartConvert();
//    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
//    blue = abs(ADC_GetResult32());
//    Blue_Pin_Write(0);
//    IDAC8_Sleep();
//    
//    
//    CyDelay(100);
//
//    sprintf(PD_Current, "Red = %ld\nGreen = %ld\nBlue = %ld\n",red, green, blue);
//    UART_PutString(PD_Current);
////
////    CyDelay(500);
////    
////    if ((((red - green)>4000) && ((red - blue)>4000))){// Red
////        Red_Pin_Write(1);
////        CyDelay(1000);
////        Red_Pin_Write(0);
////
////    }
////    else if ((((green - red)>4000) && ((green - blue)>4000))){// Red
////        Green_Pin_Write(1);
////        CyDelay(1000);
////        Green_Pin_Write(0);
////
////    }
////    else if ((((blue - green)>4000) && ((blue - red)>4000))){// Red
////        Blue_Pin_Write(1);
////        CyDelay(1000);
////        Blue_Pin_Write(0);
////
////    }
////    else{
////        Red_Pin_Write(0);   
////        Green_Pin_Write(0);
////        Blue_Pin_Write(0);
////        CyDelay(1000);
////    } 
//    
//    if (((red < green) && (red < blue))){// Red
//        Red_Pin_Write(1);
//        CyDelay(1000);
//        Red_Pin_Write(0);
//
//    }
//    else if (((green < red) && (green < blue))){// Red
//        Green_Pin_Write(1);
//        CyDelay(1000);
//        Green_Pin_Write(0);
//
//    }
//    else if (((blue < red) && (blue < green)) && (blue > (room + 100000))){// Red
//        Blue_Pin_Write(1);
//        CyDelay(1000);
//        Blue_Pin_Write(0);
//
//    }
//    else{
//        Red_Pin_Write(0);   
//        Green_Pin_Write(0);
//        Blue_Pin_Write(0);
//        CyDelay(1000);
//    }
//}     


/* [] END OF FILE */