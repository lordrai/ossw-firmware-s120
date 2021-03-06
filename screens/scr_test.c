#include <string.h>
#include "scr_test.h"
#include "nrf_delay.h"
#include "../scr_mngr.h"
#include "../mlcd_draw.h"
#include "../rtc.h"
#include "../mlcd.h"
#include "../utf8.h"
#include "../pawn/amxutil.h"
#include "../i18n/i18n.h"

#define DIGITS_Y_POS 80

static uint32_t lastValue = 0;

uint8_t testValue;

static void scr_test_handle_button_back(void) {
	  scr_mngr_show_screen(SCR_WATCHFACE);
}

static void scr_test_handle_button_pressed(uint32_t button_id) {
	  switch (button_id) {
			  case SCR_EVENT_PARAM_BUTTON_BACK:
					  scr_test_handle_button_back();
				    break;
		}
}

static void scr_test_refresh_value1() {
	  if(testValue == lastValue) {
			  return;
		}
		if(testValue < 100) {
			  mlcd_clear_rect(5, DIGITS_Y_POS, 40, 58);
		} else {
				mlcd_draw_digit(testValue/100, 5, DIGITS_Y_POS, 40, 58, 5);
		}
    mlcd_draw_digit((testValue%100)/10, 49, DIGITS_Y_POS, 40, 58, 5);
    mlcd_draw_digit(testValue%10, 93, DIGITS_Y_POS, 40, 58, 5);
	
    lastValue = testValue;
}

static void scr_test_refresh_screen() {
	  scr_test_refresh_value1();
	  mlcd_fb_flush();
}

static void scr_test_init() {
	  mlcd_fb_clear();
	                 
	  mlcd_draw_text(I18N_TRANSLATE(MESSAGE_HEART_RATE), 5, 13, NULL, NULL, FONT_OPTION_BIG);
	  mlcd_draw_rect(0, 50, MLCD_XRES, 2);
	
    scr_test_refresh_screen();
}

void scr_test_handle_event(uint32_t event_type, uint32_t event_param) {
	  switch(event_type) {
			  case SCR_EVENT_INIT_SCREEN:
				    scr_test_init();
				    break;
        case SCR_EVENT_REFRESH_SCREEN:
            scr_test_refresh_screen();
            break;
			  case SCR_EVENT_BUTTON_PRESSED:
				    scr_test_handle_button_pressed(event_param);
				    break;
		}
}
