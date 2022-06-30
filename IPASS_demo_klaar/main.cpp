#include "hwlib.hpp"
#include "ipass.hpp"

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

   ipass serano(i2c_bus);

   int state = 1;
   serano.setAllRegisters(56,5,23,2,2,3,5); // set registers

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
               serano.writeToRegister(0x00, serano.getRegisterSec() + 1);
               if(serano.getRegisterSec() >= 60){
                  serano.writeToRegister(0x00, serano.getRegisterSec() -59);
                  serano.writeToRegister(0x01, serano.getRegisterMin() + 1);
               }
            }
            else if(!button1.read()){
               serano.writeToRegister(0x00, serano.getRegisterSec() - 1);
               if(serano.getRegisterSec() <= 0){
                  serano.writeToRegister(0x00, serano.getRegisterSec() + 59);
                  serano.writeToRegister(0x01, serano.getRegisterMin() - 1);
               }
            }
         }
            
         else if(state == 2){//minutes
            if(!button2.read()){
               serano.writeToRegister(0x01, serano.getRegisterMin() + 1);
               if(serano.getRegisterMin() >= 60){
                  serano.writeToRegister(0x01, serano.getRegisterMin() -59);
                  serano.writeToRegister(0x02, serano.getRegisterHrs() + 1);
               }
            }
            else if(!button1.read()){
               serano.writeToRegister(0x01, serano.getRegisterMin() - 1);
               if(serano.getRegisterMin() <= 0){
                  serano.writeToRegister(0x01, serano.getRegisterMin() + 59);
                  serano.writeToRegister(0x02, serano.getRegisterHrs() - 1);
               }
            }          
         }

         else if(state == 3){//hours
            if(!button2.read()){
               serano.writeToRegister(0x02, serano.getRegisterHrs() + 1);
               if(serano.getRegisterHrs() >= 24){
                  serano.writeToRegister(0x02, serano.getRegisterHrs() -24);
                  serano.writeToRegister(0x03, serano.getRegisterDay() + 1);
                  serano.writeToRegister(0x04, serano.getRegisterDate() + 1);
               }
            }
            else if(!button1.read()){
               serano.writeToRegister(0x02, serano.getRegisterHrs() - 1);
               if(serano.getRegisterHrs() <= 0){
                  serano.writeToRegister(0x02, serano.getRegisterHrs() + 24); // bij 0 gaat die naar 15
                  serano.writeToRegister(0x03, serano.getRegisterDay() - 1);
                  serano.writeToRegister(0x04, serano.getRegisterDate() - 1);
               }
            }              
         }

         else if(state == 4){//day
            if(!button2.read()){
               serano.writeToRegister(0x03, serano.getRegisterDay() + 1);
               if(serano.getRegisterDay() >= 8){
                  serano.writeToRegister(0x03, serano.getRegisterDay() -7);
               }
            }
            else if(!button1.read()){
               serano.writeToRegister(0x03, serano.getRegisterDay() - 1);
               if(serano.getRegisterDay() <= 0){
                  serano.writeToRegister(0x03, serano.getRegisterDay() + 7);
               }
            }             
         }

         else if(state == 5){//date
            if(!button2.read()){
               serano.writeToRegister(0x04, serano.getRegisterDate() + 1);
               if(serano.getRegisterDate() >= 31){
                  serano.writeToRegister(0x04, serano.getRegisterDate() -30);
                  serano.writeToRegister(0x05, serano.getRegisterMth() + 1);
               }
            }
            else if(!button1.read()){
               serano.writeToRegister(0x04, serano.getRegisterDate() - 1);
               if(serano.getRegisterDate() <= 0){
                  serano.writeToRegister(0x04, serano.getRegisterDate() + 30);
                  serano.writeToRegister(0x05, serano.getRegisterMth() - 1);
               }
            }                
         }

         else if(state == 6){//month
            if(!button2.read()){
               serano.writeToRegister(0x05, serano.getRegisterMth() + 1);
               if(serano.getRegisterMth() >= 13){
                  serano.writeToRegister(0x05, serano.getRegisterMth() -12);
                  serano.writeToRegister(0x06, serano.getRegisterYrs() + 1);
               }
            }
            else if(!button1.read()){
               serano.writeToRegister(0x05, serano.getRegisterMth() - 1);
               if(serano.getRegisterMth() <= 0){
                  serano.writeToRegister(0x05, serano.getRegisterMth() + 12);
                  serano.writeToRegister(0x06, serano.getRegisterYrs() - 1);
               }
            }                  
         }


         else if(state == 7){//years
            if(!button2.read()){
               serano.writeToRegister(0x06, serano.getRegisterYrs() + 1);
               if(serano.getRegisterYrs() >= 11){
                  serano.writeToRegister(0x06, serano.getRegisterYrs() -10);
               }
            }
            else if(!button1.read()){
               serano.writeToRegister(0x06, serano.getRegisterYrs() - 1);
               if(serano.getRegisterYrs() <= 0){
                  serano.writeToRegister(0x06, serano.getRegisterYrs() + 10);
               }
            }      
         }
         
         hwlib::cout << "SELECT_CHECK"  << '\n';
      } // end else if
         display << "\f" << serano.getRegisterSec() << " sec " 
         << serano.getRegisterMin() << " min " << "\n"
         << serano.getRegisterHrs() << " Hrs "
         << serano.getRegisterDay() << " Day " << " \n"
         << serano.getRegisterDate() << " Date "
         << serano.getRegisterMth() << " Mth " << " \n"
         << serano.getRegisterYrs() << " Yrs "
         << hwlib::flush; 

   } // end while

} // end main
