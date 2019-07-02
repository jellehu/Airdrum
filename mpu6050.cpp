//          Copyright Jelle van den Broek 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "mpu6050.hpp"

void mpu6050::wakeUp(){
    uint8_t data[2] = {PWR_MGMT_1, 0};
    bus.i2c_bus::write(GYRO_ADDRESS).write(data, 2);
}

int16_t mpu6050::getGyroscopeZ(){
    uint8_t data[2] = {GYRO_ZOUT_H, GYRO_ZOUT_L};
    return (readFromRegister (data[0]) << 8) + readFromRegister(data[1]);
}

int16_t mpu6050::getAcceleratorX(){
    uint8_t data[2] = {ACCEL_XOUT_H, ACCEL_XOUT_L};
    return (readFromRegister (data[0]) << 8) + readFromRegister(data[1]);
}

int16_t mpu6050::getAcceleratorY(){
    uint8_t data[2] = {ACCEL_YOUT_H, ACCEL_YOUT_L};
    return (readFromRegister (data[0]) << 8) + readFromRegister(data[1]);
}