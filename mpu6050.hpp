//          Copyright Jelle van den Broek 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef MPU6050_HPP
#define MPU6050_HPP

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define GYRO_ADDRESS 0x68
#define PWR_MGMT_1 0x6B

#include "hwlib.hpp"

/// @file 
class mpu6050{
private:
    hwlib::i2c_bus & bus;

    /// \brief
	/// Read the value of the register address.
	/// \details
    /// Selects the selected register address using the hwlib write function. Next it starts reading the value from this address using the hwlib read function and returns the value.
    uint8_t readFromRegister(const uint8_t & registerAddress){
        uint8_t registerData;
        bus.i2c_bus::write(GYRO_ADDRESS).write(registerAddress);
        bus.i2c_bus::read(GYRO_ADDRESS).read(registerData);
        return registerData;
    }

public:
    mpu6050(hwlib::i2c_bus & bus): bus(bus){}

    /// \brief
	/// Wake up the MPU6050 gyroscope.
	/// \details
    /// Wakes up the MPU6050 gyroscope by setting the power management address bits to 0.
    void wakeUp();

    /// \brief
	/// Get the gyroscope Z value. 
	/// \details
    /// Using the readFromRegister funciton, this function will first read data from the high register. It will shift these bits 8 to the left. Next, using readFromRegister again, the function reads the data from the low register. These two values will then be added up.
    int16_t getGyroscopeZ();

    /// \brief
	/// Get the accelerator X value. 
	/// \details
    /// Using the readFromRegister funciton, this function will first read data from the high register. It will shift these bits 8 to the left. Next, using readFromRegister again, the function reads the data from the low register. These two values will then be added up.
    int16_t getAcceleratorX();

    /// \brief
	/// Get the accelerator X value. 
	/// \details
    /// Using the readFromRegister funciton, this function will first read data from the high register. It will shift these bits 8 to the left. Next, using readFromRegister again, the function reads the data from the low register. These two values will then be added up.
    int16_t getAcceleratorY();
};

#endif /* MPU6050_HPP */