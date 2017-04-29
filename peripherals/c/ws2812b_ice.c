#include "ws2812b.h"
#include <stdint.h>


void ws2812b_rotate( 
  WS2812B_t *base,
  uint8_t num_leds
  ){
	WS2812B_t temp = base[num_leds-1];\
	int i;
  for (i = 0; i < num_leds; i++){
		WS2812B_t temp2 = base[i];	//save original led[i]
		base[i] = temp;				//save led[i-1] to led[i]
		temp = temp2;					//prep led[i] for next swap
	};
  };

void ws2812b_pulse( 
  WS2812B_t *base,
  uint8_t num_leds
)
{
	static int direction = 1; //1 is incrementing; -1 is decrementing
	int i;
	for (i = 0; i < num_leds; i++) {
		WS2812B_t temp = base[i];		//load led[i]
		if ((temp.red < 0xFF) && (direction == 1)) {
			temp.red++;
	} else if ((temp.red == 0xFF) && (direction == 1)) {
			direction = -1;
			temp.red--;
	} else if ((temp.red > 0x00) && (direction == -1)) {
		temp.red--;
	} else if ((temp.red == 0x00) && (direction == -1)) {
		direction = 1;
		temp.red++;
	}
};
}
