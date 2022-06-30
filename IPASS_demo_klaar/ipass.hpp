#ifndef IPASS_HPP
#define IPASS_HPP

#include "hwlib.hpp"

class ipass{
private:
    hwlib::i2c_bus & i2cBus;

    uint8_t convertToDecimal(uint8_t binary);
    uint8_t convertToBinary(uint8_t decimal);

public:
    ipass(hwlib::i2c_bus & i2cBus);

    void writeToRegister(uint8_t registers, uint8_t decimal);
    uint8_t readFromRegister(uint8_t registers);

    uint8_t getRegisterSec();
    uint8_t getRegisterMin();
    uint8_t getRegisterHrs();
    uint8_t getRegisterDay();
    uint8_t getRegisterDate();
    uint8_t getRegisterMth();
    uint8_t getRegisterYrs();

    void getAllRegisters();
    void setAllRegisters(uint8_t sec, uint8_t Min, uint8_t Hrs, uint8_t Day, uint8_t Date, uint8_t Mth, uint8_t Yrs);
};

#endif