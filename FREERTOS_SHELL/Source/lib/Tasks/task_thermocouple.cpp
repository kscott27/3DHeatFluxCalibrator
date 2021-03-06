/*
 * task_thermocouple.cpp
 *
 * Created: 2/17/2018 8:31:52 PM
 *  Author: Kevin
 */ 

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "shared_data_sender.h"
#include "shared_data_receiver.h"
#include "task_thermocouple.h"                      // Header for this file


/** This constant sets how many RTOS ticks the task delays if the user's not talking.
 *  The duration is calculated to be about 5 ms.
 */
const portTickType ticks_to_delay = ((configTICK_RATE_HZ / 1000) * 5);


//-------------------------------------------------------------------------------------
/** This constructor creates a new data acquisition task. Its main job is to call the
 *  parent class's constructor which does most of the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */

task_thermocouple::task_thermocouple (const char* a_name, 
					  unsigned portBASE_TYPE a_priority, 
					  size_t a_stack_size,
					  emstream* p_ser_dev,
					  MAX31855* tc
					 )
	: frt_task (a_name, a_priority, a_stack_size, p_ser_dev), tc(tc)
{
	task_name = a_name;
}


//-------------------------------------------------------------------------------------
/** This task interacts with the thermocouple driver in order to monitor the digital 
 *  readout and relay it to the user interface. It will also cause the device to enter
 *  an emergency shutdown mode if the temperature exceeds a certain threshold.
 */

void task_thermocouple::run (void)
{
	char char_in;                           // Character read from serial device
	time_stamp a_time;                      // Holds the time so it can be displayed
	portTickType previous_ticks;
	

	// This is an infinite loop; it runs until the power is turned off. There is one 
	// such loop inside the code for each task
	for (;;)
	{
		// Run the finite state machine. The variable 'state' is kept by the parent class
		switch (state)
		{
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 0, the motor task is waiting for the user to enter data before 
			// proceeding to its routine.
			case (0):
			    
				current_temp = tc->get_temp_fahr();
				//if (current_temp > 120)
				//{
					//emergency_shutdown.put(true);
				//}
				//*p_serial << task_name << PMS (" Output Temp: ") << current_temp << PMS (" degrees C") << endl;
				*p_serial << task_name << current_temp << endl;
			
			    break;
			

		} // End switch state

		runs++;                             // Increment counter for debugging

		// No matter the state, wait for approximately a millisecond before we 
		// run the loop again. This gives lower priority tasks a chance to run
		vTaskDelay (configMS_TO_TICKS (500));
	}
}