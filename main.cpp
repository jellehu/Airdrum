//          Copyright Jelle van den Broek 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "mpu6050.hpp"

int main( void ){
   	namespace target = hwlib::target;
	
	// Assign variables to the GPIO pins
	auto scl = target::pin_oc(target::pins::scl);
	auto sda = target::pin_oc(target::pins::sda);
	auto buzzer = target::pin_out(target::pins::d2);
	
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
	auto mpu = mpu6050(i2c_bus);

	// Start receiving data from the gyroscope.
	mpu.wakeUp();

	for(;;){
		// If movement is detected, and if the gyroscope is tilted past a certain point, power the GPIO pin.
		if (mpu.getGyroscopeZ() < -30000){
			if ((mpu.getAcceleratorX() > 17000) && (mpu.getAcceleratorY() > -4000)){
				// Power the GPIO pin connected to the buzzer.
				buzzer.write( 1 );
				buzzer.flush();
				// Delay to decide how long the buzzer is on.
				hwlib::wait_ms( 100 );
				buzzer.write( 0 );
				buzzer.flush();
				// Delay to prevent the pin to be powered multiple times in a single movement.
				hwlib::wait_ms( 110 );
			}
		}
	}
}

