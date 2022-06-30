#include "DS3231.hpp"

DS3231::DS3231(hwlib::i2c_bus & i2cBus):
    i2cBus(i2cBus)
    {}

uint8_t DS3231::convertToDecimal(uint8_t binary){
    binary = (binary/16*10) + (binary%16);
    return binary;
}

uint8_t DS3231::convertToBinary(uint8_t decimal){
    decimal = (decimal/10*16) + (decimal%10);
    return decimal;
}

void DS3231::writeToRegister(uint8_t registers, uint8_t decimal){
    auto var = i2cBus.write(0x68);
    var.write(registers);
    var.write(convertToBinary(decimal));
}

uint8_t DS3231::readFromRegister(uint8_t registers){
    {auto var = i2cBus.write(0x68);
        var.write(registers);}
    return convertToDecimal(i2cBus.read(0x68).read_byte());
}

uint8_t DS3231::getRegisterSec(){
    return readFromRegister(regSec); // if(value < 0){ value == 0}
}
uint8_t DS3231::getRegisterMin(){
    return readFromRegister(regMin);
}
uint8_t DS3231::getRegisterHrs(){
    return readFromRegister(regHrs);
}
uint8_t DS3231::getRegisterDay(){
    return readFromRegister(regDay);
}
uint8_t DS3231::getRegisterDate(){
    return readFromRegister(regDate);
}
uint8_t DS3231::getRegisterMth(){
    return readFromRegister(regMth);
}
uint8_t DS3231::getRegisterYrs(){
    return readFromRegister(regYrs);
}

void DS3231::getAllRegisters(){
    hwlib::cout << "\n" <<getRegisterSec() << " sec \n ";
    hwlib::cout << getRegisterMin() << " min \n ";
    hwlib::cout << getRegisterHrs() << " hrs \n ";
    hwlib::cout << getRegisterDay() << " day \n ";
    hwlib::cout << getRegisterDate() << " date \n ";
    hwlib::cout << getRegisterMth() << " mth \n ";
    hwlib::cout << getRegisterYrs() << " yrs \n ";
    }

void DS3231::setAllRegisters(uint8_t sec, uint8_t Min, uint8_t Hrs, uint8_t Day, uint8_t Date, uint8_t Mth, uint8_t Yrs){
    writeToRegister(regSec, sec),writeToRegister(regMin, Min),writeToRegister(regHrs, Hrs),writeToRegister(regDay, Day),writeToRegister(regDate, Date),writeToRegister(regMth, Mth),writeToRegister(regYrs, Yrs);
}