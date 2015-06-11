#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <AP_HAL.h>
#include <AP_InertialNav.h>
#include <AP_AHRS.h>
#include <AP_Math.h>
#include <inttypes.h>
#include <AP_Compass.h>
#include <AP_Airspeed.h>
#include <AP_GPS.h>
#include <AP_InertialSensor.h>
#include <AP_Baro.h>
#include <AP_Param.h>
#include <AP_Progmem.h>

bool AP_InertialSensor::calibrate_dynamic_accel(AP_InertialSensor_UserInteract* interact,
                                        float &trim_roll,
                                        float &trim_pitch)
{
    uint8_t num_accels = min(get_accel_count(), INS_MAX_INSTANCES);
    Vector3f samples[INS_MAX_INSTANCES][6];
    Vector3f new_offsets[INS_MAX_INSTANCES];
    Vector3f new_scaling[INS_MAX_INSTANCES];
    Vector3f orig_offset[INS_MAX_INSTANCES];
    Vector3f orig_scale[INS_MAX_INSTANCES];
    uint8_t num_ok = 0;

    for (uint8_t k=0; k<num_accels; k++) {
        // backup original offsets and scaling
        orig_offset[k] = _accel_offset[k].get();
        orig_scale[k]  = _accel_scale[k].get();

        // clear accelerometer offsets and scaling
        _accel_offset[k] = Vector3f(0,0,0);
        _accel_scale[k] = Vector3f(1,1,1);
    }

    // capture data from 6 positions
    for (uint8_t i=0; i<6; i++) {
        const prog_char_t *msg;

        // display message to user
        switch ( i ) {
            case 0:
                msg = PSTR("level");
                break;
            case 1:
                msg = PSTR("on its LEFT side");
                break;
            case 2:
                msg = PSTR("on its RIGHT side");
                break;
            case 3:
                msg = PSTR("nose DOWN");
                break;
            case 4:
                msg = PSTR("nose UP");
                break;
            default:    // default added to avoid compiler warning
            case 5:
                msg = PSTR("on its BACK");
                break;
        }
        interact->printf_P(
                PSTR("Place vehicle %S and press any key.\n"), msg);

        // wait for GPS input
        if (!GPS_ok()) {
            //if GPS is out of the status,it fails
            goto failed;
        }

        // clear out any existing samples from gps

        // average 32 samples
        for (uint8_t k=0; k<num_accels; k++) {
            samples[k][i] = Vector3f();
        }
        uint8_t num_samples = 0;
        while (num_samples < 32) {
            // read samples from gps
            // capture sample
           accel_update();
            for (uint8_t k=0; k<num_accels; k++) {
                samples[k][i] += get_gps_accel;
            }
            hal.scheduler->delay(10);
            num_samples++;
        }
        for (uint8_t k=0; k<num_accels; k++) {
            samples[k][i] /= num_samples;
        }
    }

    // run the calibration routine
    for (uint8_t k=0; k<num_accels; k++) {
        bool success = _calibrate_accel(samples[k], new_offsets[k], new_scaling[k]);

        interact->printf_P(PSTR("Offsets[%u]: %.2f %.2f %.2f\n"),
                           (unsigned)k,
                           new_offsets[k].x, new_offsets[k].y, new_offsets[k].z);
        interact->printf_P(PSTR("Scaling[%u]: %.2f %.2f %.2f\n"),
                           (unsigned)k,
                           new_scaling[k].x, new_scaling[k].y, new_scaling[k].z);
        if (success) num_ok++;
    }

    if (num_ok == num_accels) {
        interact->printf_P(PSTR("Calibration successful\n"));

        for (uint8_t k=0; k<num_accels; k++) {
            // set and save calibration
            _accel_offset[k].set(new_offsets[k]);
            _accel_scale[k].set(new_scaling[k]);
        }
        _save_parameters();

        check_3D_calibration();

        // calculate the trims as well from primary accels and pass back to caller
        _calculate_trim(samples[0][0], trim_roll, trim_pitch);

        return true;
    }

failed:
    interact->printf_P(PSTR("Calibration FAILED\n"));
    // restore original scaling and offsets
    for (uint8_t k=0; k<num_accels; k++) {
        _accel_offset[k].set(orig_offset[k]);
        _accel_scale[k].set(orig_scale[k]);
    }
    return false;
}
#endif

Vector3f get_gps_accel,temp;

 float velocity_x_off=0.0;
 float velocity_y_off=0.0;
 uint32_t last_time=0,delta_t;
 float velocity_x_off_last,velocity_y_off_last;

 void     accel_update()
{

 float now = hal.scheduler->millis()*0.001f;
 delta_t=now-last_time;
if (delta_t<1&&delta_t>200)
 {
     get_gps_accel=(0,0,0);
 }
else
{
 temp.x=_ahrs.get_home().lat;
 temp.y=_ahrs.get_home().lng;
 //temp.alt=0;
 // get position move in lat, lon coordinates
 int32_t lat_offset = _ahrs.get_location().lat - temp.x;
 int32_t lng_offset = _ahrs.get_location().lng - temp.y;
 temp.x=_ahrs.get_location().lat;
 temp.y=_ahrs.get_location().lng;

 if (lat_offset != 0||lng_offset != 0) {
     // calculate the position move in cm
     float x_offset_cm = lat_offset * LATLON_TO_CM*0.01;
      // calculate the position move in cm
     float y_offset_cm = lng_offset * _lon_to_cm_scaling*0.01;

     velocity_x_off=x_offset_cm/delta_t;
     velocity_y_off=y_offset_cm/delta_t;
     get_gps_accel.x=(velocity_x_off-velocity_x_off_last)/delta_t;
     get_gps_accel.y=(velocity_y_off-velocity_y_off_last)/delta_t;
     get_gps_accel.z=0;
     velocity_x_off_last=velocity_x_off;
     velocity_y_off_last=velocity_y_off;

 }
}
 last_time=now;
}

 static bool GPS_is_ok()
 {
     if (ap.home_is_set && gps.status() >= AP_GPS::GPS_OK_FIX_3D &&
         !gps_glitch.glitching() && !failsafe.gps &&
         !ekf_check_state.bad_compass && !failsafe.ekf) {
         return true;
     }else{
         return false;
     }
 }
