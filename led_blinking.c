
#include <stdlib.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#include "led_blinking.h"

/*
 * This module handles processes to perform random LED blinking for LEDs
 * connected to port pins connected to external transistors.
 */


/*
 * Port D blinker thread, times are in milliseconds.
 *  Blink the LEDs on port D
 *
 *  This is not the clearest or the quickest way to do this, but it is by
 *      far the most clear way to do it.
 *  We get a random number and assign it to a 16-bit variable.  We then
 *    check each bit and map it to an port pin that has a transistor
 *    driven LED connected to it.
 */
static WORKING_AREA(waPort_D0_Blinker, 128);
static msg_t Port_D0_Blinker(void *arg)
{
    uint32_t pattern;
    (void)arg;

    chRegSetThreadName("Port_D0_Blinker");

    srand( 93475 );

    while (TRUE)
    {
      pattern = rand() ;

      if( pattern & 0b0000000000000001 )
      {
          palSetPad(GPIOD, GPIOD_PIN0);
      }
      else
      {
        palClearPad(GPIOD, GPIOD_PIN0);
      }

      if( pattern & 0b0000000000000010 )
      {
          palSetPad(GPIOD, GPIOD_PIN1);
      }
      else
      {
        palClearPad(GPIOD, GPIOD_PIN1);
      }

      if( pattern & 0b0000000000000100 )
      {
          palSetPad(GPIOD, GPIOD_PIN2);
      }
      else
      {
        palClearPad(GPIOD, GPIOD_PIN2);
      }

      if( pattern & 0b0000000000001000 )
      {
          palSetPad(GPIOD, GPIOD_PIN3);
      }
      else
      {
        palClearPad(GPIOD, GPIOD_PIN3);
      }


      if( pattern & 0b0000000001000000 )
      {
          palSetPad(GPIOD, GPIOD_PIN6);
      }
      else
      {
        palClearPad(GPIOD, GPIOD_PIN6);
      }

      if( pattern & 0b0000000010000000 )
      {
          palSetPad(GPIOD, GPIOD_PIN7);
      }
      else
      {
        palClearPad(GPIOD, GPIOD_PIN7);
      }

      chThdSleepMilliseconds(8);

    }
    return 0;
}


/*
 * Port E blinker thread, times are in milliseconds.
 *  Blink some of the LEDs on port E
 *
 *  This is not the clearest or the quickest way to do this, but it is by
 *      far the most clear way to do it.
 *  We get a random number and assign it to a 16-bit variable.  We then
 *    check each bit and map it to an port pin that has a transistor
 *    driven LED connected to it.
 */
static WORKING_AREA(waPort_E0_Blinker, 128);
static msg_t Port_E0_Blinker(void *arg)
{
    (void)arg;
    uint32_t pattern;

    srand( 3764 );  // seed the random number generator

    chRegSetThreadName("Port_E0_Blinker");
    while (TRUE)
    {
      pattern = rand(); // get a new light pattern

      // check the bits and light the LEDs with set bits
      if( pattern & 0b0000000000010000 )
      {
          palSetPad(GPIOE, GPIOE_PIN4);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN4);
      }

      if( pattern & 0b0000000000100000 )
      {
          palSetPad(GPIOE, GPIOE_PIN5);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN5);
      }

      if( pattern & 0b0000000001000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN6);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN6);
      }

      if( pattern & 0b0000000010000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN7);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN7);
      }

      chThdSleepMilliseconds(4);

    }
    return 0;
}


/*
 * Port E blinker thread, times are in milliseconds.
 *  Blink some other LEDs on port E
 *
 *  This is not the clearest or the quickest way to do this, but it is by
 *      far the most clear way to do it.
 *  We get a random number and assign it to a 16-bit variable.  We then
 *    check each bit and map it to an port pin that has a transistor
 *    driven LED connected to it.
 */
static WORKING_AREA(waPort_E1_Blinker, 128);
static msg_t Port_E1_Blinker(void *arg)
{
    (void)arg;
    uint32_t pattern;

    srand( 23897 );

    chRegSetThreadName("Port_E1_Blinker");

    while (TRUE)
    {

      pattern = rand() ;

      if( pattern & 0b0000000100000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN8);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN8);
      }

      if( pattern & 0b0000001000000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN9);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN9);
      }

      if( pattern & 0b0000010000000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN10);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN10);
      }

      if( pattern & 0b00001000000000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN11);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN11);
      }

      if( pattern & 0b0001000000000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN12);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN12);
      }

      if( pattern & 0b0010000000000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN13);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN13);
      }

      if( pattern & 0b0100000000000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN14);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN14);
      }

      if( pattern & 0b10000000000000000 )
      {
          palSetPad(GPIOE, GPIOE_PIN15);
      }
      else
      {
        palClearPad(GPIOE, GPIOE_PIN15);
      }

      chThdSleepMilliseconds(3);

    }
    return 0;
}

/*
 * Port C blinker thread, times are in milliseconds.
 *  Blink some LEDs on port C
 *
 *  This is not the clearest or the quickest way to do this, but it is by
 *      far the most clear way to do it.
 *  We get a random number and assign it to a 16-bit variable.  We then
 *    check each bit and map it to an port pin that has a transistor
 *    driven LED connected to it.
 */
static WORKING_AREA(waPort_C1_Blinker, 128);
static msg_t Port_C1_Blinker(void *arg)
{
    (void)arg;
    uint32_t pattern;

    srand( 326 );

    chRegSetThreadName("Port_C1_Blinker");
    while (TRUE)
    {

      pattern = rand() ;

      if( pattern & 0b0000000000000010 )
      {
          palSetPad(GPIOC, GPIOC_PIN1);
      }
      else
      {
        palClearPad(GPIOC, GPIOC_PIN1);
      }

      if( pattern & 0b0000000000000100 )
      {
          palSetPad(GPIOC, GPIOC_PIN2);
      }
      else
      {
        palClearPad(GPIOC, GPIOC_PIN2);
      }

      if( pattern & 0b0000000000010000 )
      {
          palSetPad(GPIOC, GPIOC_PIN4);
      }
      else
      {
        palClearPad(GPIOC, GPIOC_PIN4);
      }

      if( pattern & 0b0000000000100000 )
      {
          palSetPad(GPIOC, GPIOC_PIN5);
      }
      else
      {
        palClearPad(GPIOC, GPIOC_PIN5);
      }

      if( pattern & 0b0000000001000000 )
      {
          palSetPad(GPIOC, GPIOC_PIN6);
      }
      else
      {
        palClearPad(GPIOC, GPIOC_PIN6);
      }

      chThdSleepMilliseconds(2);

    }
    return 0;
}

/*
 * perform configuration, then start threads for LED blinking
 */
void start_led_blinker(void)
{

/*
 * configure the port pins for output, this is not the way
 * you will want to configure pins whose configuration will
 * not change during execution, but we do it here as an example.
 * You will normally configure pin modes in board.h
 */

  palSetPadMode(GPIOD, GPIOD_PIN0, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN2, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN3, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN6, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN7, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN8, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN9, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN10, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_PIN11, PAL_MODE_OUTPUT_PUSHPULL);

/*
 * start the threads that will blink LEDs connected to the ports
 */
  chThdCreateStatic(waPort_D0_Blinker, sizeof(waPort_D0_Blinker), NORMALPRIO+10, Port_D0_Blinker, NULL);
  chThdCreateStatic(waPort_C1_Blinker, sizeof(waPort_C1_Blinker), NORMALPRIO+10, Port_C1_Blinker, NULL);
  chThdCreateStatic(waPort_E0_Blinker, sizeof(waPort_E0_Blinker), NORMALPRIO+10, Port_E0_Blinker, NULL);
  chThdCreateStatic(waPort_E1_Blinker, sizeof(waPort_E1_Blinker), NORMALPRIO+10, Port_E1_Blinker, NULL);
}

