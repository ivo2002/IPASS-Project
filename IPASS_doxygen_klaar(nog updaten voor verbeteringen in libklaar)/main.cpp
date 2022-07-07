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

   auto timeMinus = target::pin_in_out( target::pins::d22 );
   auto timePlus = target::pin_in_out( target::pins::d23 );
   auto select = target::pin_in_out( target::pins::d24 );
   auto stateMinus = target::pin_in_out( target::pins::d25 );
   auto statePlus = target::pin_in_out( target::pins::d26 );

   DS3231 ds3231(i2c_bus);

   int state = 1;
   ds3231.setAllRegisters(12,5,23,2,2,3,5); // set registers

   while(true){
      if(!statePlus.read() ){
         state += 1;
         if(state > 7){
            state = 1;
         }
      }   
      else if(!stateMinus.read()){
         state -= 1;
         if(state <= 0){
            state = 7;
         }
      }
      else if(!select.read()){
         if(state == 1){ // seconds

         display << "\f" << ds3231.getRegisterSec() << " sec<- " 
         << ds3231.getRegisterMin() << " min " << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day " << " \n\n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs " << "state = " << state<< hwlib::flush;

            if(!timePlus.read()){
               ds3231.writeToRegister(0x00, ds3231.getRegisterSec() + 1);
               if(ds3231.getRegisterSec() >= 60){
                  ds3231.writeToRegister(0x00, ds3231.getRegisterSec() -59);
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() + 1);
               }
            }
            else if(!timeMinus.read()){
               ds3231.writeToRegister(0x00, ds3231.getRegisterSec() - 2);
               if(ds3231.getRegisterSec() <= 0){
                  ds3231.writeToRegister(0x00, ds3231.getRegisterSec() + 59);
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() - 1);
               }
            }
         }
            
         else if(state == 2){ // minutes

         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min<-" << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day " << " \n\n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs " << "state = " << state<< hwlib::flush;
         
            if(!timePlus.read()){
               ds3231.writeToRegister(0x01, ds3231.getRegisterMin() + 1);
               if(ds3231.getRegisterMin() >= 60){
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() -59);
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() + 1);
               }
            }
            else if(!timeMinus.read()){
               ds3231.writeToRegister(0x01, ds3231.getRegisterMin() - 1);
               if(ds3231.getRegisterMin() <= 0){
                  ds3231.writeToRegister(0x01, ds3231.getRegisterMin() + 59);
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() - 1);
               }
            }          
         }

         else if(state == 3){ // hours

         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min " << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs<- "
         << ds3231.getRegisterDay() << " Day " << " \n\n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs " << "state = " << state<< hwlib::flush;

            if(!timePlus.read()){
               ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() + 1);
               if(ds3231.getRegisterHrs() >= 24){
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() -24);
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() + 1);
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() + 1);
               }
            }
            else if(!timeMinus.read()){
               ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() - 1);
               if(ds3231.getRegisterHrs() <= 0){
                  ds3231.writeToRegister(0x02, ds3231.getRegisterHrs() + 24); // bij 0 gaat die naar 15
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() - 1);
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() - 1);
               }
            }              
         }

         else if(state == 4){ // day

         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min " << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day<- " << " \n\n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs " << "state = " << state<< hwlib::flush;

            if(!timePlus.read()){
               ds3231.writeToRegister(0x03, ds3231.getRegisterDay() + 1);
               if(ds3231.getRegisterDay() >= 8){
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() -7);
               }
            }
            else if(!timeMinus.read()){
               ds3231.writeToRegister(0x03, ds3231.getRegisterDay() - 1);
               if(ds3231.getRegisterDay() <= 0){
                  ds3231.writeToRegister(0x03, ds3231.getRegisterDay() + 7);
               }
            }             
         }

         else if(state == 5){ // date

         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min " << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day " << " \n\n"
         << ds3231.getRegisterDate() << " Date<- "
         << ds3231.getRegisterMth() << " Mth " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs " << "state = " << state<< hwlib::flush;

            if(!timePlus.read()){
               ds3231.writeToRegister(0x04, ds3231.getRegisterDate() + 1);
               if(ds3231.getRegisterDate() >= 31){
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() -30);
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() + 1);
               }
            }
            else if(!timeMinus.read()){
               ds3231.writeToRegister(0x04, ds3231.getRegisterDate() - 1);
               if(ds3231.getRegisterDate() <= 0){
                  ds3231.writeToRegister(0x04, ds3231.getRegisterDate() + 30);
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() - 1);
               }
            }                
         }

         else if(state == 6){ // month

         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min " << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day " << " \n\n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth<- " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs " << "state = " << state<< hwlib::flush;

            if(!timePlus.read()){
               ds3231.writeToRegister(0x05, ds3231.getRegisterMth() + 1);
               if(ds3231.getRegisterMth() >= 13){
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() -12);
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() + 1);
               }
            }
            else if(!timeMinus.read()){
               ds3231.writeToRegister(0x05, ds3231.getRegisterMth() - 1);
               if(ds3231.getRegisterMth() <= 0){
                  ds3231.writeToRegister(0x05, ds3231.getRegisterMth() + 12);
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() - 1);
               }
            }                  
         }


         else if(state == 7){ // year

         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min " << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day " << " \n\n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs<- " << "state = " << state<< hwlib::flush;

            if(!timePlus.read()){
               ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() + 1);
               if(ds3231.getRegisterYrs() >= 11){
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() -10);
               }
            }
            else if(!timeMinus.read()){
               ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() - 1);
               if(ds3231.getRegisterYrs() <= 0){
                  ds3231.writeToRegister(0x06, ds3231.getRegisterYrs() + 10);
               }
            }      
         }
          
      } // end else if

         display << "\f" << ds3231.getRegisterSec() << " sec " 
         << ds3231.getRegisterMin() << " min " << "\n\n"
         << ds3231.getRegisterHrs() << " Hrs "
         << ds3231.getRegisterDay() << " Day " << " \n\n"
         << ds3231.getRegisterDate() << " Date "
         << ds3231.getRegisterMth() << " Mth " << " \n\n"
         << ds3231.getRegisterYrs() << " Yrs " 
         << "state = " << state
         << hwlib::flush; 

   } // end while

} // end main
