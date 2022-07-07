#ifndef DS3231_HPP
#define DS3231_HPP

#include "hwlib.hpp"

//Brief
//
//Detail
//
class DS3231{
private:
    hwlib::i2c_bus & i2cBus;

    uint8_t regSec = 0x00;
    uint8_t regMin = 0x01;
    uint8_t regHrs = 0x02;
    uint8_t regDay = 0x03;
    uint8_t regDate = 0x04;
    uint8_t regMth = 0x05;
    uint8_t regYrs = 0x06;

    //Brief
    // Converts binary to decimal
    //Detail
    // This function converts a binary input to a uint8_t decimal with a calculation
    uint8_t convertToDecimal(uint8_t binary);

    //Brief
    // Converts decimal to binary
    //Detail
    // This function converts a decimal input to a uint8_t binary with a calculation
    uint8_t convertToBinary(uint8_t decimal);

public:
    DS3231(hwlib::i2c_bus & i2cBus);

    //Brief
    // Write the input parameter to a chosen register
    //Detail
    // Write the input uint8_t to a selected register by writing to the i2c bus and converting the input to a binary number
    void writeToRegister(uint8_t registers, uint8_t decimal);

    //Brief
    // Read whats in a chosen register
    //Detail
    // Read whats currently in the selected register by reading from the i2c bus and converting the input to a decimal number
    uint8_t readFromRegister(uint8_t registers);

    //Brief
    // Gets values in regSec register
    //Detail
    // Read the value in register regSec by calling the "readFromRegister(regSec)" function with regSec as input
    uint8_t getRegisterSec();

    //Brief
    // Gets values in regMin register
    //Detail
    // Read the value in register regMin by calling the "readFromRegister(regMin)" function with regMin as input
    uint8_t getRegisterMin();

    //Brief
    // Gets values in regHrs register
    //Detail
    // Read the value in register regHrs by calling the "readFromRegister(regHrs)" function with regHrs as input
    uint8_t getRegisterHrs();

    //Brief
    // Gets values in regDay register
    //Detail
    // Read the value in register regDay by calling the "readFromRegister(regDay)" function with regDay as input
    uint8_t getRegisterDay();

    //Brief
    // Gets values in regDate register
    //Detail
    // Read the value in register regDate by calling the "readFromRegister(regDate)" function with regDate as input
    uint8_t getRegisterDate();

    //Brief
    // Gets values in regMth register
    //Detail
    // Read the value in register regMth by calling the "readFromRegister(regMth)" function with regMth as input
    uint8_t getRegisterMth();

    //Brief
    // Gets values in regYrs register
    //Detail
    // Read the value in register regYrs by calling the "readFromRegister(regYrs)" function with regYrs as input
    uint8_t getRegisterYrs();

    //Brief
    // Gets all values in all registers.
    //Detail
    // Calls every "getRegister..." function
    void getAllRegisters();

    //Brief
    // Sets all parameters into correct register
    //Detail
    // Sets all paramters into the correct register, regSec, regMin, regHrs etc..
    void setAllRegisters(uint8_t sec, uint8_t Min, uint8_t Hrs, uint8_t Day, uint8_t Date, uint8_t Mth, uint8_t Yrs);
};

#endif