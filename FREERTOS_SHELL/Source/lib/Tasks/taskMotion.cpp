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

taskMotion::taskMotion(const char * a_name,
                       unsigned portBASE_TYPE a_priority,
                       size_t a_stack_size,
                       emstream * p_ser_dev
)
: frt_task (a_name, a_priority, a_stack_size, p_ser_dev)
{
	float turns_per_inch;
	turns_per_inch = 3;
	inch_to_step = 200 * turns_per_inch * microstep_scaler;
	step_to_inch = 1 / inch_to_step;
}


//-------------------------------------------------------------------------------------
/** This task interacts with the motor driver object in order to control the motors
 *  in ways specified by the user.
 */

void taskMotion::run (void)
{
	

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

void taskMotion::reset_device(void)
{
	*p_serial << PMS ("Resetting device.") << endl;
	wdt_enable (WDTO_120MS);
	for (;;);	
}

