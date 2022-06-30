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
    // Gets values in 0x00 register
    //Detail
    // Read the value in register 0x00 by calling the "readFromRegister(0x00)" function with 0x00 as input
    uint8_t getRegisterSec();

    //Brief
    // Gets values in 0x01 register
    //Detail
    // Read the value in register 0x01 by calling the "readFromRegister(0x01)" function with 0x01 as input
    uint8_t getRegisterMin();

    //Brief
    // Gets values in 0x02 register
    //Detail
    // Read the value in register 0x02 by calling the "readFromRegister(0x02)" function with 0x02 as input
    uint8_t getRegisterHrs();

    //Brief
    // Gets values in 0x03 register
    //Detail
    // Read the value in register 0x03 by calling the "readFromRegister(0x03)" function with 0x03 as input
    uint8_t getRegisterDay();

    //Brief
    // Gets values in 0x04 register
    //Detail
    // Read the value in register 0x04 by calling the "readFromRegister(0x04)" function with 0x04 as input
    uint8_t getRegisterDate();

    //Brief
    // Gets values in 0x05 register
    //Detail
    // Read the value in register 0x05 by calling the "readFromRegister(0x05)" function with 0x05 as input
    uint8_t getRegisterMth();

    //Brief
    // Gets values in 0x06 register
    //Detail
    // Read the value in register 0x06 by calling the "readFromRegister(0x06)" function with 0x06 as input
    uint8_t getRegisterYrs();

    //Brief
    // Gets all values in all registers.
    //Detail
    // Calls every "getRegister..." function
    void getAllRegisters();

    //Brief
    // Sets all parameters into correct register
    //Detail
    // Sets all paramters into the correct register, 0x00, 0x01, 0x02 etc..
    void setAllRegisters(uint8_t sec, uint8_t Min, uint8_t Hrs, uint8_t Day, uint8_t Date, uint8_t Mth, uint8_t Yrs);
};

#endif