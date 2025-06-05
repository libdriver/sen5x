/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_sen5x_read_test.c
 * @brief     driver sen5x read test source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-06-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/06/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_sen5x_read_test.h"

static sen5x_handle_t gs_handle;        /**< sen5x handle */

/**
 * @brief     read test
 * @param[in] type chip type
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sen5x_read_test(sen5x_type_t type, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    sen5x_info_t info;
    
    /* link functions */
    DRIVER_SEN5X_LINK_INIT(&gs_handle, sen5x_handle_t);
    DRIVER_SEN5X_LINK_IIC_INIT(&gs_handle, sen5x_interface_iic_init);
    DRIVER_SEN5X_LINK_IIC_DEINIT(&gs_handle, sen5x_interface_iic_deinit);
    DRIVER_SEN5X_LINK_IIC_WRITE_COMMAND(&gs_handle, sen5x_interface_iic_write_cmd);
    DRIVER_SEN5X_LINK_IIC_READ_COMMAND(&gs_handle, sen5x_interface_iic_read_cmd);
    DRIVER_SEN5X_LINK_DELAY_MS(&gs_handle, sen5x_interface_delay_ms);
    DRIVER_SEN5X_LINK_DEBUG_PRINT(&gs_handle, sen5x_interface_debug_print);
    
    /* get information */
    res = sen5x_info(&info);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        sen5x_interface_debug_print("sen5x: chip is %s.\n", info.chip_name);
        sen5x_interface_debug_print("sen5x: manufacturer is %s.\n", info.manufacturer_name);
        sen5x_interface_debug_print("sen5x: interface is %s.\n", info.interface);
        sen5x_interface_debug_print("sen5x: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sen5x_interface_debug_print("sen5x: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sen5x_interface_debug_print("sen5x: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sen5x_interface_debug_print("sen5x: max current is %0.2fmA.\n", info.max_current_ma);
        sen5x_interface_debug_print("sen5x: max temperature is %0.1fC.\n", info.temperature_max);
        sen5x_interface_debug_print("sen5x: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    sen5x_interface_debug_print("sen5x: start read test.\n");
    
    /* set the type */
    res = sen5x_set_type(&gs_handle, type);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set type failed.\n");
    
        return 1;
    }
    
    /* init the chip */
    res = sen5x_init(&gs_handle);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: init failed.\n");
        
        return 1;
    }
    
    /* start measurement */
    res = sen5x_start_measurement(&gs_handle);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: start measurement failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 2000 ms */
    sen5x_interface_delay_ms(2000);
    
    /* sen5x_read test */
    sen5x_interface_debug_print("sen5x: sen5x_read test.\n");
    for (i = 0; i < times; i++)
    {
        if (type == SEN50)
        {
            sen50_data_t output;
            
            /* read data */
            res = sen50_read(&gs_handle, &output);
            if (res != 0)
            {
                sen5x_interface_debug_print("sen50: read failed.\n");
                (void)sen5x_deinit(&gs_handle);
                
                return 1;
            }
            if (output.pm_valid != 0)
            {
                sen5x_interface_debug_print("sen50: pm1.0 is %0.2f ug/m3.\n", output.pm1p0_ug_m3);
                sen5x_interface_debug_print("sen50: pm2.5 is %0.2f ug/m3.\n", output.pm2p5_ug_m3);
                sen5x_interface_debug_print("sen50: pm4.0 is %0.2f ug/m3.\n", output.pm4p0_ug_m3);
                sen5x_interface_debug_print("sen50: pm10.0 is %0.2f ug/m3.\n", output.pm10_ug_m3);
            }
            else
            {
                sen5x_interface_debug_print("sen50: pm is invalid.\n");
            }
        }
        else if (type == SEN54)
        {
            sen54_data_t output;
            
            /* read data */
            res = sen54_read(&gs_handle, &output);
            if (res != 0)
            {
                sen5x_interface_debug_print("sen54: read failed.\n");
                (void)sen5x_deinit(&gs_handle);
                
                return 1;
            }
            if (output.pm_valid != 0)
            {
                sen5x_interface_debug_print("sen54: pm1.0 is %0.2f ug/m3.\n", output.pm1p0_ug_m3);
                sen5x_interface_debug_print("sen54: pm2.5 is %0.2f ug/m3.\n", output.pm2p5_ug_m3);
                sen5x_interface_debug_print("sen54: pm4.0 is %0.2f ug/m3.\n", output.pm4p0_ug_m3);
                sen5x_interface_debug_print("sen54: pm10.0 is %0.2f ug/m3.\n", output.pm10_ug_m3);
                sen5x_interface_debug_print("sen54: compensated ambient humidity is %0.2f%%.\n", output.compensated_ambient_humidity_percentage);
                sen5x_interface_debug_print("sen54: compensated ambient temperature is %0.2fC.\n", output.compensated_ambient_temperature_degree);
                sen5x_interface_debug_print("sen54: voc index is %0.2f.\n", output.voc_index);
            }
            else
            {
                sen5x_interface_debug_print("sen54: pm is invalid.\n");
                sen5x_interface_debug_print("sen54: compensated ambient humidity is %0.2f%%.\n", output.compensated_ambient_humidity_percentage);
                sen5x_interface_debug_print("sen54: compensated ambient temperature is %0.2fC.\n", output.compensated_ambient_temperature_degree);
                sen5x_interface_debug_print("sen54: voc index is %0.2f.\n", output.voc_index);
            }
        }
        else
        {
            sen55_data_t output;
            
            /* read data */
            res = sen55_read(&gs_handle, &output);
            if (res != 0)
            {
                sen5x_interface_debug_print("sen55: read failed.\n");
                (void)sen5x_deinit(&gs_handle);
                
                return 1;
            }
            if (output.pm_valid != 0)
            {
                sen5x_interface_debug_print("sen55: pm1.0 is %0.2f ug/m3.\n", output.pm1p0_ug_m3);
                sen5x_interface_debug_print("sen55: pm2.5 is %0.2f ug/m3.\n", output.pm2p5_ug_m3);
                sen5x_interface_debug_print("sen55: pm4.0 is %0.2f ug/m3.\n", output.pm4p0_ug_m3);
                sen5x_interface_debug_print("sen55: pm10.0 is %0.2f ug/m3.\n", output.pm10_ug_m3);
                sen5x_interface_debug_print("sen55: compensated ambient humidity is %0.2f%%.\n", output.compensated_ambient_humidity_percentage);
                sen5x_interface_debug_print("sen55: compensated ambient temperature is %0.2fC.\n", output.compensated_ambient_temperature_degree);
                sen5x_interface_debug_print("sen55: voc index is %0.2f.\n", output.voc_index);
                sen5x_interface_debug_print("sen55: nox index is %0.2f.\n", output.nox_index);
            }
            else
            {
                sen5x_interface_debug_print("sen55: pm is invalid.\n");
                sen5x_interface_debug_print("sen55: compensated ambient humidity is %0.2f%%.\n", output.compensated_ambient_humidity_percentage);
                sen5x_interface_debug_print("sen55: compensated ambient temperature is %0.2fC.\n", output.compensated_ambient_temperature_degree);
                sen5x_interface_debug_print("sen55: voc index is %0.2f.\n", output.voc_index);
                sen5x_interface_debug_print("sen55: nox index is %0.2f.\n", output.nox_index);
            }
        }
        
        /* delay 2000 ms */
        sen5x_interface_delay_ms(2000);
    }
    
    /* sen5x_read_pm_value test */
    sen5x_interface_debug_print("sen5x: sen5x_read_pm_value test.\n");
    for (i = 0; i < times; i++)
    {
        sen5x_pm_t pm;
        
        res = sen5x_read_pm_value(&gs_handle, &pm);
        if (res != 0)
        {
            sen5x_interface_debug_print("sen5x: read failed.\n");
            (void)sen5x_deinit(&gs_handle);
            
            return 1;
        }
        if (pm.pm_valid != 0)
        {
            sen5x_interface_debug_print("sen5x: pm1.0 is %0.2f ug/m3.\n", pm.pm1p0_ug_m3);
            sen5x_interface_debug_print("sen5x: pm2.5 is %0.2f ug/m3.\n", pm.pm2p5_ug_m3);
            sen5x_interface_debug_print("sen5x: pm4.0 is %0.2f ug/m3.\n", pm.pm4p0_ug_m3);
            sen5x_interface_debug_print("sen5x: pm10.0 is %0.2f ug/m3.\n", pm.pm10_ug_m3);
            sen5x_interface_debug_print("sen5x: pm0.5 is %0.2f cm3.\n", pm.pm0p5_cm3);
            sen5x_interface_debug_print("sen5x: pm1.0 is %0.2f cm3.\n", pm.pm1p0_cm3);
            sen5x_interface_debug_print("sen5x: pm2.5 is %0.2f cm3.\n", pm.pm2p5_cm3);
            sen5x_interface_debug_print("sen5x: pm4.0 is %0.2f cm3.\n", pm.pm4p0_cm3);
            sen5x_interface_debug_print("sen5x: pm10.0 is %0.2f cm3.\n", pm.pm10_cm3);
            sen5x_interface_debug_print("sen5x: typical is %0.2f um.\n", pm.typical_particle_um);
        }
        else
        {
            sen5x_interface_debug_print("sen5x: pm is invalid.\n");
        }
        
        /* delay 2000 ms */
        sen5x_interface_delay_ms(2000);
    }
    
    if (type != SEN50)
    {
        /* sen5x_read_raw_value test */
        sen5x_interface_debug_print("sen5x: sen5x_read_raw_value test.\n");
        for (i = 0; i < times; i++)
        {
            sen5x_raw_t raw;
            
            /* read raw value */
            res = sen5x_read_raw_value(&gs_handle, &raw);
            if (res != 0)
            {
                sen5x_interface_debug_print("sen5x: read raw value failed.\n");
                (void)sen5x_deinit(&gs_handle);
                
                return 1;
            }
            sen5x_interface_debug_print("sen5x: humidity is %0.2f%%.\n", raw.humidity_percentage);
            sen5x_interface_debug_print("sen5x: temperature is %0.2fC.\n", raw.temperature_degree);
            sen5x_interface_debug_print("sen5x: voc is %0.2f.\n", raw.voc);
            sen5x_interface_debug_print("sen5x: nox is %0.2f.\n", raw.nox);
            
            /* delay 2000 ms */
            sen5x_interface_delay_ms(2000);
        }
    }
    
    /* stop measurement */
    res = sen5x_stop_measurement(&gs_handle);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: stop measurement failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 2000 ms */
    sen5x_interface_delay_ms(2000);
    
    if (type != SEN50)
    {
        /* start measurement without pm test */
        sen5x_interface_debug_print("sen5x: start measurement without pm test.\n");
        
        /* start measurement without pm */
        res = sen5x_start_measurement_without_pm(&gs_handle);
        if (res != 0)
        {
            sen5x_interface_debug_print("sen5x: start measurement without pm failed.\n");
            (void)sen5x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* delay 2000 ms */
        sen5x_interface_delay_ms(2000);
        
        for (i = 0; i < times; i++)
        {
            if (type == SEN54)
            {
                sen54_data_t output;
                
                /* read data */
                res = sen54_read(&gs_handle, &output);
                if (res != 0)
                {
                    sen5x_interface_debug_print("sen54: read failed.\n");
                    (void)sen5x_deinit(&gs_handle);
                    
                    return 1;
                }
                sen5x_interface_debug_print("sen54: compensated ambient humidity is %0.2f%%.\n", output.compensated_ambient_humidity_percentage);
                sen5x_interface_debug_print("sen54: compensated ambient temperature is %0.2fC.\n", output.compensated_ambient_temperature_degree);
                sen5x_interface_debug_print("sen54: voc index is %0.2f.\n", output.voc_index);
            }
            else
            {
                sen55_data_t output;
                
                /* read data */
                res = sen55_read(&gs_handle, &output);
                if (res != 0)
                {
                    sen5x_interface_debug_print("sen55: read failed.\n");
                    (void)sen5x_deinit(&gs_handle);
                    
                    return 1;
                }
                sen5x_interface_debug_print("sen55: compensated ambient humidity is %0.2f%%.\n", output.compensated_ambient_humidity_percentage);
                sen5x_interface_debug_print("sen55: compensated ambient temperature is %0.2fC.\n", output.compensated_ambient_temperature_degree);
                sen5x_interface_debug_print("sen55: voc index is %0.2f.\n", output.voc_index);
                sen5x_interface_debug_print("sen55: nox index is %0.2f.\n", output.nox_index);
            }
            
            /* delay 2000 ms */
            sen5x_interface_delay_ms(2000);
        }
        
        /* stop measurement */
        res = sen5x_stop_measurement(&gs_handle);
        if (res != 0)
        {
            sen5x_interface_debug_print("sen5x: stop measurement failed.\n");
            (void)sen5x_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* finish read test */
    sen5x_interface_debug_print("sen5x: finish read test.\n");
    (void)sen5x_deinit(&gs_handle);
    
    return 0;
}
