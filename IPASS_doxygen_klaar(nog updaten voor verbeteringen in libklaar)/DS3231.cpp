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
    return readFromRegister(0x00); // if(value < 0){ value == 0}
}
uint8_t DS3231::getRegisterMin(){
    return readFromRegister(0x01);
}
uint8_t DS3231::getRegisterHrs(){
    return readFromRegister(0x02);
}
uint8_t DS3231::getRegisterDay(){
    return readFromRegister(0x03);
}
uint8_t DS3231::getRegisterDate(){
    return readFromRegister(0x04);
}
uint8_t DS3231::getRegisterMth(){
    return readFromRegister(0x05);
}
uint8_t DS3231::getRegisterYrs(){
    return readFromRegister(0x06);
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
    writeToRegister(0x00, sec),writeToRegister(0x01, Min),writeToRegister(0x02, Hrs),writeToRegister(0x03, Day),writeToRegister(0x04, Date),writeToRegister(0x05, Mth),writeToRegister(0x06, Yrs);
}