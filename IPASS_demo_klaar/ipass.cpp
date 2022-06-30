#include "ipass.hpp"

ipass::ipass(hwlib::i2c_bus & i2cBus):
    i2cBus(i2cBus)
    {}

uint8_t ipass::convertToDecimal(uint8_t binary){
    binary = (binary/16*10) + (binary%16);
    return binary;
}

uint8_t ipass::convertToBinary(uint8_t decimal){
    decimal = (decimal/10*16) + (decimal%10);
    return decimal;
}

void ipass::writeToRegister(uint8_t registers, uint8_t decimal){
    auto var = i2cBus.write(0x68);
    var.write(registers);
    var.write(convertToBinary(decimal));
}

uint8_t ipass::readFromRegister(uint8_t registers){
    {auto var = i2cBus.write(0x68);
        var.write(registers);}
    return convertToDecimal(i2cBus.read(0x68).read_byte());
}

uint8_t ipass::getRegisterSec(){
    return readFromRegister(0x00); // if(value < 0){ value == 0}
}
uint8_t ipass::getRegisterMin(){
    return readFromRegister(0x01);
}
uint8_t ipass::getRegisterHrs(){
    return readFromRegister(0x02);
}
uint8_t ipass::getRegisterDay(){
    return readFromRegister(0x03);
}
uint8_t ipass::getRegisterDate(){
    return readFromRegister(0x04);
}
uint8_t ipass::getRegisterMth(){
    return readFromRegister(0x05);
}
uint8_t ipass::getRegisterYrs(){
    return readFromRegister(0x06);
}

void ipass::getAllRegisters(){
    hwlib::cout << "\n" <<getRegisterSec() << " sec \n ";
    hwlib::cout << getRegisterMin() << " min \n ";
    hwlib::cout << getRegisterHrs() << " hrs \n ";
    hwlib::cout << getRegisterDay() << " day \n ";
    hwlib::cout << getRegisterDate() << " date \n ";
    hwlib::cout << getRegisterMth() << " mth \n ";
    hwlib::cout << getRegisterYrs() << " yrs \n ";
    }

void ipass::setAllRegisters(uint8_t sec, uint8_t Min, uint8_t Hrs, uint8_t Day, uint8_t Date, uint8_t Mth, uint8_t Yrs){
    writeToRegister(0x00, sec),writeToRegister(0x01, Min),writeToRegister(0x02, Hrs),writeToRegister(0x03, Day),writeToRegister(0x04, Date),writeToRegister(0x05, Mth),writeToRegister(0x06, Yrs);
}