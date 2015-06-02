
#ifndef __AP_HAL_YUNEEC_UTIL_H__
#define __AP_HAL_YUNEEC_UTIL_H__

#include <AP_HAL.h>
#include "AP_HAL_YUNEEC_Namespace.h"

class YUNEEC::YUNEECUtil : public AP_HAL::Util {
public:
    bool run_debug_shell(AP_HAL::BetterStream *stream) { return false; }
};

#endif // __AP_HAL_YUNEEC_UTIL_H__
