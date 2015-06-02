/*
 * AP_HAL_Flying_Main.h
 *
 *  Created on: 2015-6-2
 *      Author: yl
 */

#ifndef AP_HAL_FLYING_MAIN_H_
#define AP_HAL_FLYING_MAIN_H_

#if CONFIG_HAL_BOARD == HAL_BOARD_Flying
#define AP_HAL_MAIN() extern "C" {\
    int main (void) {\
    hal.init(0, NULL);          \
        setup();\
        hal.scheduler->system_initialized(); \
        for(;;) loop();\
        return 0;\
    }\
    }
#endif // HAL_BOARD_Flying


#endif /* AP_HAL_FLYING_MAIN_H_ */
