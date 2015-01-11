
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#include "myMisc.h"


#define MAXSPEED
#define MINSPEED


/*===========================================================================*/
/* Generic code.															 */
/*===========================================================================*/




void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[])
{
    size_t n, size;

    (void)argv;
    if (argc > 0)
    {
        chprintf(chp, "Usage: mem\r\n");
        return;
    }
    n = chHeapStatus(NULL, &size);
    chprintf(chp, "core free memory : %u bytes\r\n", chCoreStatus());
    chprintf(chp, "heap fragments    : %u\r\n", n);
    chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[])
{
	static const char *states[] = {THD_STATE_NAMES};
	Thread *tp;

	(void)argv;
	if (argc > 0)
	{
		chprintf(chp, "Usage: threads\r\n");
		return;
	}
	chprintf(chp, "%10s %10s %6s %6s %11s %7s %17s \r\n",
				"add", "stack", "prio", "refs", "state", "time", "name");
	tp = chRegFirstThread();
	do
	{
		chprintf(chp, "%.10lx %.10lx %6lu %6lu %11s %7lu %17.15s \r\n",
					(uint32_t)tp, (uint32_t)tp->p_ctx.r13,
					(uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
					states[tp->p_state], (uint32_t)tp->p_time,
					(uint32_t)tp->p_name);
		tp = chRegNextThread(tp);
	} while (tp != NULL);
}

void cmd_toggle(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
	{
		chprintf(chp, "Usage: toggle #led\r\n");
		return;
	}
	if(argv[0][0]=='1')
	{
		palTogglePad(GPIOD, GPIOD_LED3);
	}
	else if(argv[0][0]=='2')
	{
		palTogglePad(GPIOD, GPIOD_LED4);
	}
	else if(argv[0][0]=='3')
	{
		palTogglePad(GPIOD, GPIOD_LED5);
	}
	else if(argv[0][0]=='4')
	{
		palTogglePad(GPIOD, GPIOD_LED6);
	}
}

int blinkspeed = 50;
void cmd_blinkspeed(BaseSequentialStream *chp, int argc, char *argv[])
{

	(void)argv;
	int speed = 30;
	if (argc != 1)
	{

		return;
	}
	speed = atoi(argv[0]);
	if(speed > 5000)
	  speed = 5000;
	if(speed < 5)
	  speed = 5;
	blinkspeed = speed;
}

int cnt = 0;

void bsset(void)
{
    if (cnt == 0)
        {
        cnt = 1;
        blinkspeed = 500;
        return;
        }
     if (cnt == 1)
        {
        cnt = 0;
        blinkspeed = 50;
        return;
        }


}
int c = 0;
int counter()
{

    c++;
    return c;
}

int change()
{


        blinkspeed = counter+blinkspeed;
}


int count = 1;

void changeWay(void)
{
if(count == 1){
        count = 0;

        return;
    }
if(count == 0){
        count = 1;

        return;
    }

}
/*
 * Lightshow thread, times are in milliseconds.
 */
static WORKING_AREA(waThread1, 128);
//static WORKING_AREA(waThread2, 128);

static msg_t Thread1(void *arg)
{
	(void)arg;
	chRegSetThreadName("blinker");
	while (TRUE)
	{
	    while(count==1)
            {

		palSetPad(GPIOD, GPIOD_LED3);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED3);
		chThdSleepMilliseconds(blinkspeed);


		palSetPad(GPIOD, GPIOD_LED4);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED4);
		chThdSleepMilliseconds(blinkspeed);


		palSetPad(GPIOD, GPIOD_LED6);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED6);
		chThdSleepMilliseconds(blinkspeed);


		palSetPad(GPIOD, GPIOD_LED5);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED5);
		chThdSleepMilliseconds(blinkspeed);
	    }
	    while (count==0)
            {

		palSetPad(GPIOD, GPIOD_LED3);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED3);
		chThdSleepMilliseconds(blinkspeed);


		palSetPad(GPIOD, GPIOD_LED5);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED5);
		chThdSleepMilliseconds(blinkspeed);


		palSetPad(GPIOD, GPIOD_LED6);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED6);
		chThdSleepMilliseconds(blinkspeed);


		palSetPad(GPIOD, GPIOD_LED4);
		chThdSleepMilliseconds(blinkspeed);
		palClearPad(GPIOD, GPIOD_LED4);
		chThdSleepMilliseconds(blinkspeed);
	}
	}
	return 0;
}

/** static msg_t Thread2(void *arg)
{
	(void)arg;
	chRegSetThreadName("blinker2");

	return 0;
}
*/

void startBlinker(void)
{
	chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
}

/** void startReverseBlinker(void)
{
	chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
}
*/






