//**************************************************************************************
/** \file task_user.cpp
 *    This file contains source code for a user interface task for a ME405/FreeRTOS
 *    test suite. 
 *
 *  Revisions:
 *    \li 09-30-2012 JRR Original file was a one-file demonstration with two tasks
 *    \li 10-05-2012 JRR Split into multiple files, one for each task
 *    \li 10-25-2012 JRR Changed to a more fully C++ version with class task_user
 *    \li 11-04-2012 JRR Modified from the data acquisition example to the test suite
 *
 *  License:
 *    This file is copyright 2012 by JR Ridgely and released under the Lesser GNU 
 *    Public License, version 2. It intended for educational use only, but its use
 *    is not limited thereto. */
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUEN-
 *    TIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 *    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 *    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 *    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
//**************************************************************************************

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "shared_data_sender.h"
#include "shared_data_receiver.h"
#include "taskMotion.h"                      // Header for this file


/** This constant sets how many RTOS ticks the task delays if the user's not talking.
 *  The duration is calculated to be about 5 ms.
 */
const portTickType ticks_to_delay = ((configTICK_RATE_HZ / 1000) * 5);

taskMotion::taskMotion(const char* a_name,
unsigned portBASE_TYPE a_priority,
size_t a_stack_size,
emstream* p_ser_dev, DM542T* md,  
LimitSwitch* LS_min, LimitSwitch* LS_max,
frt_queue<uint32_t>* locations,
frt_queue<uint32_t>* max_velocity,
shared_data<uint8_t>* motor_operator,
shared_data<bool>* motor_complete,
uint16_t microstep_scaler
)
: frt_task (a_name, a_priority, a_stack_size, p_ser_dev),
task_name(a_name), md(md),
LS_min(LS_min), LS_max(LS_max),
locations(locations),
max_velocity(max_velocity),
motor_operator(motor_operator),
motor_complete(motor_complete),
microstep_scaler(microstep_scaler)
{
	float turns_per_inch;
	turns_per_inch = 3;
	inch_to_step = 200 * turns_per_inch * microstep_scaler;
	step_to_inch = 1 / inch_to_step;
}

// task_md::task_md ( const char * a_name, unsigned portBASE_TYPE a_priority,
//   size_t a_stack_size, emstream * p_ser_dev, uint16_t microstep_scaler )
//   : frt_task( a_name, a_priority, a_stack_size, p_ser_dev ),
//     DM542T( microstep_scaler )
// { }

// //-------------------------------------------------------------------------------------
// /** This constructor creates a new motor driver task. Its main job is to call the
//  *  parent class's constructor which does most of the work.
//  *  @param a_name A character string which will be the name of this task
//  *  @param a_priority The priority at which this task will initially run (default: 0)
//  *  @param a_stack_size The size of this task's stack in bytes 
//  *                      (default: configMINIMAL_STACK_SIZE)
//  *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
//  *                   be used by this task to communicate (default: NULL)
//  */

// task_md::task_md (const char* a_name,
// unsigned portBASE_TYPE a_priority,
// size_t a_stack_size,
// emstream* p_ser_dev,
// PORT_t* logic_port, 
// uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
// PORT_t* timer_port, TC0_t* timer0, uint8_t pin_bm, uint8_t int_lvl_bm,
// frt_queue<uint32_t>* locations,
// frt_queue<uint32_t>* max_velocity,
// shared_data<uint8_t>* motor_operator,
// shared_data<bool>* motor_complete,
// DeviceDriver::LimitSwitch * LS_min, DeviceDriver::LimitSwitch * LS_max
// )
// : frt_task (a_name, a_priority, a_stack_size, p_ser_dev),
//   DM542T ( logic_port, ena_bm, dir_bm, microstep_scaler,
//   timer_port, timer0, pin_bm, int_lvl_bm ),
// task_name(a_name),
// locations(locations),
// max_velocity(max_velocity),
// motor_operator(motor_operator),
// motor_complete(motor_complete),
// LS_min(LS_min),
// LS_max(LS_max)
// {
// 	float turns_per_inch;
// 	turns_per_inch = 3;
// 	inch_to_step = 200 * turns_per_inch * microstep_scaler;
// 	step_to_inch = 1 / inch_to_step;
// }


//-------------------------------------------------------------------------------------
/** This constructor creates a new motor driver task. Its main job is to call the
 *  parent class's constructor which does most of the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */
// task_md::task_md (const char* a_name,
// unsigned portBASE_TYPE a_priority,
// size_t a_stack_size,
// emstream* p_ser_dev,
// PORT_t* logic_port, 
// uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
// PORT_t* timer_port, TC1_t* timer1, uint8_t pin_bm, uint8_t int_lvl_bm,
// frt_queue<uint32_t>* locations,
// frt_queue<uint32_t>* max_velocity,
// shared_data<uint8_t>* motor_operator,
// shared_data<bool>* motor_complete,
// DeviceDriver::LimitSwitch * LS_min, DeviceDriver::LimitSwitch * LS_max
// )
// : frt_task (a_name, a_priority, a_stack_size, p_ser_dev),
//   DM542T ( logic_port, ena_bm, dir_bm, microstep_scaler,
//   timer_port, timer1, pin_bm, int_lvl_bm ),
// task_name(a_name),
// locations(locations),
// max_velocity(max_velocity),
// motor_operator(motor_operator),
// motor_complete(motor_complete),
// LS_min(LS_min),
// LS_max(LS_max)
// {
  
// }


//-------------------------------------------------------------------------------------
/** This task interacts with the motor driver object in order to control the motors
 *  in ways specified by the user.
 */

void taskMotion::run (void)
{
	char char_in;                           // Character read from serial device
	time_stamp a_time;                      // Holds the time so it can be displayed
	portTickType previous_ticks;
	uint16_t delay_counter = 0;
	uint16_t state_delay_counter = 0;
	

	// This is an infinite loop; it runs until the power is turned off. There is one 
	// such loop inside the code for each task
	for (;;)
	{		
		

		runs++;                             // Increment counter for debugging

		// No matter the state, wait for approximately a millisecond before we 
		// run the loop again. This gives lower priority tasks a chance to run
		vTaskDelay (configMS_TO_TICKS (20));
	}
}

void taskMotion::take_step (void)
{
	md->take_step();
}

void taskMotion::set_signal_low(void)
{
	md->set_signal_low();
}

void taskMotion::motorOff(void)
{
	md->motorOff();
	if(coordinate_mode.get() && (LS_min->getStatus() || LS_max->getStatus()))
	{
		reset_device();
	}
}

bool taskMotion::motorOn(void)
{
	if (md->get_direction() == 0)
	{
		if (!(LS_max->getStatus()))
		{
			md->motorOn();
			*p_serial << task_name << PMS ("F") << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!(LS_min->getStatus()))
		{
			md->motorOn();
			*p_serial << task_name << PMS ("R") << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
}

//bool task_md::motorOn(void)
//{
	//if (md->get_direction() == 0)
	//{
		//md->motorOn();
		//*p_serial << task_name << PMS ("F") << endl;
		//return true;
	//}
	//else
	//{
		//md->motorOn();
		//*p_serial << task_name << PMS ("R") << endl;
		//return true;
	//}
//}

void taskMotion::reset_device(void)
{
	*p_serial << PMS ("Resetting device.") << endl;
	wdt_enable (WDTO_120MS);
	for (;;);	
}

