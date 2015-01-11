/*
		ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
								 2011,2012 Giovanni Di Sirio.

		This file is part of ChibiOS/RT.

		ChibiOS/RT is free software; you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation; either version 3 of the License, or
		(at your option) any later version.

		ChibiOS/RT is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with this program.	If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "myMisc.h"

#include "chprintf.h"

#include "usbcfg.h"


static PWMConfig pwmcfg =
{
100000, /* 1kHz PWM clock frequency */
1000, /* PWM period 10 milli second */
NULL, /* No callback */
/* All 4 channels enabled */
{
{PWM_OUTPUT_ACTIVE_HIGH, NULL},
{PWM_OUTPUT_ACTIVE_HIGH, NULL},
{PWM_OUTPUT_ACTIVE_HIGH, NULL},
{PWM_OUTPUT_ACTIVE_HIGH, NULL},
},
0
};

palSetPadMode(GPIOD, GPIOD_LED3, PAL_MODE_ALTERNATE(2));
palSetPadMode(GPIOD, GPIOD_LED4, PAL_MODE_ALTERNATE(2));
palSetPadMode(GPIOD, GPIOD_LED5, PAL_MODE_ALTERNATE(2));
palSetPadMode(GPIOD, GPIOD_LED6, PAL_MODE_ALTERNATE(2));
pwmStart(&PWMD4, &pwmcfg);

pwmEnableChannel(&PWMD4, 0, 50);      //    50/10 = 5% duty cycle
pwmEnableChannel(&PWMD4, 1, 100);     //    100/10 = 10% duty cycle
pwmEnableChannel(&PWMD4, 2, 500);     //    500/10 = 50% duty cycle
pwmEnableChannel(&PWMD4, 3, 1000);    //    1000/10 = 100% duty cycle


/* Virtual serial port over USB.*/
static SerialUSBDriver SDU1;

/*
 * assert Shell Commands to functions
 */

static const ShellCommand commands[] =
{

    {"mem", cmd_mem},
    {"threads", cmd_threads},
    {"toggle", cmd_toggle},
    {"t", cmd_toggle},
    {"blinkspeed", cmd_blinkspeed},
    {"bs", cmd_blinkspeed},
    {NULL, NULL}
};

/*
 * Shell configuration
 */

#define SHELL_WA_SIZE	 THD_WA_SIZE(2048)

static const ShellConfig shell_cfg1 =
{
    (BaseSequentialStream *)&SDU1,
    commands
};


char msg[] = "Now is the time for all good men to come to the aid of their country";

/*
 * Application entry point.
 */
int main(void)
{



     /* Shell thread
     */
    Thread *shelltp = NULL;

    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *	 and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *	 RTOS is active.
     */
    halInit();
    chSysInit();

    /*
     * Initializes a serial-over-USB CDC driver.
     */
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(2000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    /*
     * Activate custom stuff
     */



    startBlinker();
    //chThdSleepMilliseconds(500);



    /*
     * Main loop, does nothing except
     */



    while (TRUE)
    {
        int i = 0;
        while (palReadPad(GPIOA, GPIOA_BUTTON))  {
                if ((i>30) && (i < 3000))
                {
                    changeWay();
                }
                else if ( i > 3001)
                {
                    bsset();
                }
                chThdSleepMilliseconds(1);
                i++;

                chprintf((BaseSequentialStream*)&SDU1, "value of i : %d \r\n", i);

        }
        //chThdSleepMilliseconds(1);
    }

    /**
    while (TRUE)
    {
        while (palReadPad(GPIOA, GPIOA_BUTTON))
        {
            counter();
            chprintf((BaseSequentialStream*)&SDU1, "value of c : %d \r\n", counter);


        }
        change();
    }

    */
    while (TRUE)
    {

		/* spawn a shell when the old one was terminated */
        if (!shelltp)
        {
            if (SDU1.config->usbp->state == USB_ACTIVE)
            {
                /* Spawns a new shell.*/
                shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO-10);
            }
        }
        else
        {
            /* If the previous shell exited.*/
            if (chThdTerminated(shelltp))
            {
                /* Recovers memory of the previous shell.*/
                chThdRelease(shelltp);
                shelltp = NULL;
            }
        }

        chThdSleepMilliseconds(500);

    }
  }
