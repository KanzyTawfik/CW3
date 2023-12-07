#include <util/delay.h>
#include "Lcd.h"
#include "Adc.h"
#include <stdlib.h>
#include "Uart.h"
#include "speed.h"
#include<EEPROM.h>
#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

int main() {
 Adc_Init();  // initializing ADC
 PWM_Init(); // initializing PWM
 Uart_Init(); // initializing uart
 int limit=20 ; //creating a variable templimit as the limit of 30
 
  
while(1){
  

 int  button = Adc_ReadChannel(0); // reads analogue input at channel 0 (button pressed on LCD keypad)
  float temp = Adc_ReadChannel(1); // reads analogue input at channel 1 
     
    float current = (temp/1024)*5*100; // converting the analogue reading to voltage and converting it to celcius
  
 if (button < 60){ 
      limit ++;
     
          //right button adds one to temperature min
        
        //print new min value (+1) in LCD and saves in Eeprom
      }
    else if (button  < 200) {
        //up  button adds one to temperature max
        limit --;
       
        
        
      } //creating a variable to store the input reading of pin B5
 int difference= current-limit;
 //int difference2= limit-current;
 unsigned char buffer[4]; //creating a variable buffer of type char
 unsigned char buffer2[4];//creating a variable buffer2 of type char
  itoa(current, buffer, 10); //calling the function that implememts itoa to convert the integer value into a string and store it in buffer
  itoa(limit, buffer2, 10);//calling the function that implememts itoa to convert the integer value into a string and store it in buffer2
  
 LCD_Init();// Initialize LCD 
 LCD_String_xy(0,0,"Current:");	//write string on 1st line of LCD
 LCD_String_xy(0,8, buffer);     // printing the temperature value stored in buffer
 LCD_String_xy(1,0,"limit:");	        // Write string on 2nd line
 LCD_String_xy(1,7,buffer2);  // printing the temperature value stored in buffer2
 
if (current>=limit){
  
  if(difference>=3)
  {
    Uart_SendString("Clockwise", 9);
    Uart_SendString("\n", 2);
   Set_DutyCycle(190,3);
  Set_DutyCycle(0,11);
  }
  
  else {

  Set_DutyCycle(255,3); 
    Set_DutyCycle(0,11);
  }

}
else {
  
 
 if(difference<=3){
  Uart_SendString("antiClockwise", 13);
  Uart_SendString("\n", 2);
    Set_DutyCycle(0,3);
    Set_DutyCycle(190,11); 
 
  }
  else {
     Set_DutyCycle(0,3);
  Set_DutyCycle(255,11); 
   
  }

}
  }


	return 0;
}
	
