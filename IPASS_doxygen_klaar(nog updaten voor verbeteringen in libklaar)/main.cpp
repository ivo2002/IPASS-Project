#include "hwlib.hpp"
#include "DS3231.hpp"

int main( void ){	  
   namespace target = hwlib::target;
   
   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

   auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );
   auto font = hwlib::font_default_8x8();
   auto display = hwlib::terminal_from( oled, font );

   auto button1 = target::pin_in_out( target::pins::d22 ); // left button == adress - 1
   auto button2 = target::pin_in_out( target::pins::d23 ); // right button == adress + 1
   auto button3 = target::pin_in_out( target::pins::d24 ); // select button
   auto button4 = target::pin_in_out( target::pins::d25 ); // left button == state-1
   auto button5 = target::pin_in_out( target::pins::d26 ); // right button == state+1

   DS3231 ds3231(i2c_bus);

   int state = 1;
   ds3231.setAllRegisters(56,5,23,2,2,3,5); // set registers

   while(true){
      hwlib::cout << "Current State = " << state << '\n';

      if(!button5.read() ){
         //hwlib::cout << "Statebutton5 = " << state << '\n';
         state += 1;
         if(state > 7){
            state = 1;
         }
      }   
      else if(!button4.read()){
         state -= 1;
         if(state <= 0){
            state = 7;
         }
      }
      else if(!button3.read()){
      hwlib::cout << "NA else if button 3"  << '\n';

         if(state == 1){//seconds
            if(!button2.read()){
               ds3231.writeToRegister(0x00, ds3231.getRegisterSec() + 1);
               if(ds3231.getRegisterSec() >= 60){
                  ds3231.writeToRegister(0x00, ds3231.getRegisterSec() -59);
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() + 1);
               }
            }
            else if(!button1.read()){
               ds3231.writeToRegister(0x00, ds3231.getRegisterSec() - 1);
               if(ds3231.getRegisterSec() <= 0){
                  ds3231.writeToRegister(0x00, ds3231.getRegisterSec() + 59);
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() - 1);
               }
            }
         }
            
         else if(state == 2){//minutes
            if(!button2.read()){
               ds3231.writeToRegister(0x01, ds3231.getRegisterMin() + 1);
               if(ds3231.getRegisterMin() >= 60){
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() -59);
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() + 1);
               }
            }
            else if(!button1.read()){
               ds3231.writeToRegister(0x01, ds3231.getRegisterMin() - 1);
               if(ds3231.getRegisterMin() <= 0){
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() + 59);
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() - 1);
               }
            }          
         }

         else if(state == 3){//hours
            if(!button2.read()){
               ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() + 1);
               if(ds3231.getRegisterHrs() >= 24){
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() -24);
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() + 1);
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() + 1);
               }
            }
            else if(!button1.read()){
               ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() - 1);
               if(ds3231.getRegisterHrs() <= 0){
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() + 24); // bij 0 gaat die naar 15
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() - 1);
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() - 1);
               }
            }              
         }

         else if(state == 4){//day
            if(!button2.read()){
               ds3231.writeToRegister(0x03, ds3231.getRegisterDay() + 1);
               if(ds3231.getRegisterDay() >= 8){
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() -7);
               }
            }
            else if(!button1.read()){
               ds3231.writeToRegister(0x03, ds3231.getRegisterDay() - 1);
               if(ds3231.getRegisterDay() <= 0){
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() + 7);
               }
            }             
         }

         else if(state == 5){//date
            if(!button2.read()){
               ds3231.writeToRegister(0x04, ds3231.getRegisterDate() + 1);
               if(ds3231.getRegisterDate() >= 31){
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() -30);
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() + 1);
               }
            }
            else if(!button1.read()){
               ds3231.writeToRegister(0x04, ds3231.getRegisterDate() - 1);
               if(ds3231.getRegisterDate() <= 0){
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() + 30);
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() - 1);
               }
            }                
         }

         else if(state == 6){//month
            if(!button2.read()){
               ds3231.writeToRegister(0x05, ds3231.getRegisterMth() + 1);
               if(ds3231.getRegisterMth() >= 13){
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() -12);
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() + 1);
               }
            }
            else if(!button1.read()){
               ds3231.writeToRegister(0x05, ds3231.getRegisterMth() - 1);
               if(ds3231.getRegisterMth() <= 0){
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() + 12);
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() - 1);
               }
            }                  
         }


         else if(state == 7){//years
            if(!button2.read()){
               ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() + 1);
               if(ds3231.getRegisterYrs() >= 11){
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() -10);
               }
            }
            else if(!button1.read()){
               ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() - 1);
               if(ds3231.getRegisterYrs() <= 0){
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() + 10);
               }
            }      
         }
         
         hwlib::cout << "SELECT_CHECK"  << '\n';
      } // end else if
         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min " << "\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day " << " \n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth " << " \n"
         << ds3231.getRegisterYrs() << " Yrs "
         << hwlib::flush; 

   } // end while

} // end main
