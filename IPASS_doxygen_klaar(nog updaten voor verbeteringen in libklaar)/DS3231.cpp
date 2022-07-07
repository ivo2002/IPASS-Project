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
    getRegisterSec();
    getRegisterMin();
    getRegisterHrs();
    getRegisterDay();
    getRegisterDate();
    getRegisterMth();
    getRegisterYrs();
    }

void DS3231::setRegisterSec(uint8_t sec){
    writeToRegister(regSec, sec);
}
void DS3231::setRegisterMin(uint8_t min){
    writeToRegister(regMin, min);
}
void DS3231::setRegisterHrs(uint8_t hrs){
    writeToRegister(regHrs, hrs);
}
void DS3231::setRegisterDay(uint8_t day){
    writeToRegister(regDay, day);
}
void DS3231::setRegisterDate(uint8_t date){
    writeToRegister(regDate, date);
}
void DS3231::setRegisterMth(uint8_t mth){
    writeToRegister(regMth, mth);
}
void DS3231::setRegisterYrs(uint8_t yrs){
    writeToRegister(regYrs, yrs);
}

void DS3231::setAllRegisters(uint8_t sec, uint8_t min, uint8_t hrs, uint8_t day, uint8_t date, uint8_t mth, uint8_t yrs){
    setRegisterSec(sec);
    setRegisterMin(min);
    setRegisterHrs(hrs);
    setRegisterDay(day);
    setRegisterDate(date);
    setRegisterMth(mth);
    setRegisterYrs(yrs);
}