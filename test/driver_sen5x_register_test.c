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
 * @file      driver_sen5x_register_test.c
 * @brief     driver sen5x register test source file
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

#include "driver_sen5x_register_test.h"
#include <stdlib.h>

static sen5x_handle_t gs_handle;        /**< sen5x handle */

/**
 * @brief     register test
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sen5x_register_test(sen5x_type_t type)
{
    uint8_t res;
    uint32_t second;
    uint32_t second_check;
    char buf[32];
    int16_t reg16s0;
    int16_t reg16s0_check;
    int16_t reg16s1;
    int16_t reg16s1_check;
    int16_t reg16s2;
    int16_t reg16s2_check;
    int16_t reg16s3;
    int16_t reg16s3_check;
    int16_t reg16s4;
    int16_t reg16s4_check;
    int16_t reg16s5;
    int16_t reg16s5_check;
    uint16_t reg16u0;
    uint16_t reg16u0_check;
    uint8_t version;
    uint32_t status;
    uint16_t state[4];
    uint16_t state_check[4];
    float f0;
    float f0_check;
    float f1;
    float f1_check;
    float f2;
    float f2_check;
    sen5x_info_t info;
    sen5x_type_t type_check;
    sen5x_data_ready_flag_t flag;
    sen5x_rht_acceleration_mode_t mode;
    
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
    
    /* start register test */
    sen5x_interface_debug_print("sen5x: start register test.\n");
    
    /* sen5x_set_type/sen5x_get_type test */
    sen5x_interface_debug_print("sen5x: sen5x_set_type/sen5x_get_type test.\n");
    
    /* set type sen50 */
    res = sen5x_set_type(&gs_handle, SEN50);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set type failed.\n");
    
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set type sen50.\n");
    res = sen5x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get type failed.\n");
    
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check type %s.\n", SEN50 == type_check ? "ok" : "error");
    
    /* set type sen54 */
    res = sen5x_set_type(&gs_handle, SEN54);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set type failed.\n");
    
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set type sen54.\n");
    res = sen5x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get type failed.\n");
    
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check type %s.\n", SEN54 == type_check ? "ok" : "error");
    
    /* set type sen55 */
    res = sen5x_set_type(&gs_handle, SEN55);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set type failed.\n");
    
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set type sen55.\n");
    res = sen5x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get type failed.\n");
    
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check type %s.\n", SEN55 == type_check ? "ok" : "error");
    
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
    
    /* sen5x_set_auto_cleaning_interval/sen5x_get_auto_cleaning_interval test */
    sen5x_interface_debug_print("sen5x: sen5x_set_auto_cleaning_interval/sen5x_get_auto_cleaning_interval test.\n");
    
    second = rand() % 65536 + 65536;
    res = sen5x_set_auto_cleaning_interval(&gs_handle, second);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set auto cleaning interval failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set auto cleaning interval %d.\n", second);
    res = sen5x_get_auto_cleaning_interval(&gs_handle, (uint32_t *)&second_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get auto cleaning interval failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check interval %s.\n", second_check == second ? "ok" : "error");
    
    /* sen5x_disable_auto_cleaning_interval test */
    sen5x_interface_debug_print("sen5x: sen5x_disable_auto_cleaning_interval test.\n");
    res = sen5x_disable_auto_cleaning_interval(&gs_handle);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: disable auto cleaning interval failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check disable cleaning %s.\n", res == 0 ? "ok" : "error");
    
    /* sen5x_set_temperature_compensation/sen5x_get_temperature_compensation test */
    sen5x_interface_debug_print("sen5x: sen5x_set_temperature_compensation/sen5x_get_temperature_compensation test.\n");
    
    reg16s0 = rand() % 100;
    reg16s1 = -(rand() % 100);
    reg16u0 = rand() % 100;
    res = sen5x_set_temperature_compensation(&gs_handle, reg16s0, reg16s1, reg16u0);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set temperature compensation failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set temperature offset %d.\n", reg16s0);
    sen5x_interface_debug_print("sen5x: set normalized temperature offset slope %d.\n", reg16s1);
    sen5x_interface_debug_print("sen5x: set time constant %d.\n", reg16u0);
    res = sen5x_get_temperature_compensation(&gs_handle, &reg16s0_check, &reg16s1_check, &reg16u0_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get temperature compensation failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check temperature offset %s.\n", reg16s0 == reg16s0_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check normalized temperature offset slope %s.\n", reg16s1 == reg16s1_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check time constant %s.\n", reg16u0 == reg16u0_check ? "ok" : "error");
    
    /* restore */
    res = sen5x_set_temperature_compensation(&gs_handle, 0, 0, 0);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set temperature compensation failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* sen5x_set_warm_start/sen5x_get_warm_start test */
    sen5x_interface_debug_print("sen5x: sen5x_set_warm_start/sen5x_get_warm_start test.\n");
    
    reg16u0 = rand() % 100;
    res = sen5x_set_warm_start(&gs_handle, reg16u0);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set warm start failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set warm start %d.\n", reg16u0);
    res = sen5x_get_warm_start(&gs_handle, &reg16u0_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get warm start failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check warm start %s.\n", reg16u0 == reg16u0_check ? "ok" : "error");
    
    /* restore */
    res = sen5x_set_warm_start(&gs_handle, 0);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set warm start failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* sen5x_set_voc_algorithm_tuning/sen5x_get_voc_algorithm_tuning test */
    sen5x_interface_debug_print("sen5x: sen5x_set_voc_algorithm_tuning/sen5x_get_voc_algorithm_tuning test.\n");
    
    reg16s0 = (rand() % 100) + 1;
    reg16s1 = (rand() % 100) + 1;
    reg16s2 = (rand() % 100) + 1;
    reg16s3 = (rand() % 100) + 1;
    reg16s4 = (rand() % 100) + 10;
    reg16s5 = (rand() % 100) + 1;
    res = sen5x_set_voc_algorithm_tuning(&gs_handle, reg16s0, reg16s1, reg16s2,
                                         reg16s3, reg16s4, reg16s5);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set voc algorithm tuning failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set index offset %d.\n", reg16s0);
    sen5x_interface_debug_print("sen5x: set learning time offset hour %d.\n", reg16s1);
    sen5x_interface_debug_print("sen5x: set learning time gain hour %d.\n", reg16s2);
    sen5x_interface_debug_print("sen5x: set gating max duration minute %d.\n", reg16s3);
    sen5x_interface_debug_print("sen5x: set std initial %d.\n", reg16s4);
    sen5x_interface_debug_print("sen5x: set gain factor %d.\n", reg16s5);
    res = sen5x_get_voc_algorithm_tuning(&gs_handle, &reg16s0_check, &reg16s1_check, &reg16s2_check,
                                         &reg16s3_check, &reg16s4_check, &reg16s5_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get voc algorithm tuning failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check index offset %s.\n", reg16s0 == reg16s0_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check learning time offset hour %s.\n", reg16s1 == reg16s1_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check learning time gain hour %s.\n", reg16s2 == reg16s2_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check gating max duration minute %s.\n", reg16s3 == reg16s3_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check std initial %s.\n", reg16s4 == reg16s4_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check gain factor %s.\n", reg16s5 == reg16s5_check ? "ok" : "error");
    
    /* restore */
    res = sen5x_set_voc_algorithm_tuning(&gs_handle, 100, 12, 12, 180, 50, 230);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set voc algorithm tuning failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* sen5x_set_nox_algorithm_tuning/sen5x_get_nox_algorithm_tuning test */
    sen5x_interface_debug_print("sen5x: sen5x_set_nox_algorithm_tuning/sen5x_get_nox_algorithm_tuning test.\n");
    
    reg16s0 = (rand() % 100) + 1;
    reg16s1 = (rand() % 100) + 1;
    reg16s2 = 12;
    reg16s3 = (rand() % 100) + 1;
    reg16s4 = 50;
    reg16s5 = (rand() % 100) + 1;
    res = sen5x_set_nox_algorithm_tuning(&gs_handle, reg16s0, reg16s1, reg16s2,
                                         reg16s3, reg16s4, reg16s5);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set nox algorithm tuning failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set index offset %d.\n", reg16s0);
    sen5x_interface_debug_print("sen5x: set learning time offset hour %d.\n", reg16s1);
    sen5x_interface_debug_print("sen5x: set learning time gain hour %d.\n", reg16s2);
    sen5x_interface_debug_print("sen5x: set gating max duration minute %d.\n", reg16s3);
    sen5x_interface_debug_print("sen5x: set std initial %d.\n", reg16s4);
    sen5x_interface_debug_print("sen5x: set gain factor %d.\n", reg16s5);
    res = sen5x_get_nox_algorithm_tuning(&gs_handle, &reg16s0_check, &reg16s1_check, &reg16s2_check,
                                         &reg16s3_check, &reg16s4_check, &reg16s5_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get nox algorithm tuning failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check index offset %s.\n", reg16s0 == reg16s0_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check learning time offset hour %s.\n", reg16s1 == reg16s1_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check learning time gain hour %s.\n", reg16s2 == reg16s2_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check gating max duration minute %s.\n", reg16s3 == reg16s3_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check std initial %s.\n", reg16s4 == reg16s4_check ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check gain factor %s.\n", reg16s5 == reg16s5_check ? "ok" : "error");
    
    /* restore */
    res = sen5x_set_nox_algorithm_tuning(&gs_handle, 1, 12, 12, 720, 50, 230);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set nox algorithm tuning failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* sen5x_set_rht_acceleration_mode/sen5x_get_rht_acceleration_mode test */
    sen5x_interface_debug_print("sen5x: sen5x_set_rht_acceleration_mode/sen5x_get_rht_acceleration_mode test.\n");
    
    /* set rht acceleration mode low */
    res = sen5x_set_rht_acceleration_mode(&gs_handle, SEN5X_RHT_ACCELERATION_LOW);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set rht acceleration mode failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set rht acceleration mode low.\n");
    res = sen5x_get_rht_acceleration_mode(&gs_handle, &mode);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get rht acceleration mode failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check rht acceleration mode %s.\n", mode == SEN5X_RHT_ACCELERATION_LOW ? "ok" : "error");
    
    /* set rht acceleration mode high */
    res = sen5x_set_rht_acceleration_mode(&gs_handle, SEN5X_RHT_ACCELERATION_HIGH);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set rht acceleration mode failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set rht acceleration mode high.\n");
    res = sen5x_get_rht_acceleration_mode(&gs_handle, &mode);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get rht acceleration mode failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check rht acceleration mode %s.\n", mode == SEN5X_RHT_ACCELERATION_HIGH ? "ok" : "error");
    
    /* set rht acceleration mode medium */
    res = sen5x_set_rht_acceleration_mode(&gs_handle, SEN5X_RHT_ACCELERATION_MEDIUM);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set rht acceleration mode failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set rht acceleration mode medium.\n");
    res = sen5x_get_rht_acceleration_mode(&gs_handle, &mode);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get rht acceleration mode failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check rht acceleration mode %s.\n", mode == SEN5X_RHT_ACCELERATION_MEDIUM ? "ok" : "error");
    
    /* sen5x_set_voc_algorithm_state/sen5x_get_voc_algorithm_state test */
    sen5x_interface_debug_print("sen5x: sen5x_set_voc_algorithm_state/sen5x_get_voc_algorithm_state test.\n");
    
    state[0] = rand() % 0xFFFFU;
    state[1] = rand() % 0xFFFFU;
    state[2] = rand() % 0xFFFFU;
    state[3] = rand() % 0xFFFFU;
    res = sen5x_set_voc_algorithm_state(&gs_handle, state);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set voc algorithm state failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set state0 0x%04X.\n", state[0]);
    sen5x_interface_debug_print("sen5x: set state1 0x%04X.\n", state[1]);
    sen5x_interface_debug_print("sen5x: set state2 0x%04X.\n", state[2]);
    sen5x_interface_debug_print("sen5x: set state3 0x%04X.\n", state[3]);
    res = sen5x_get_voc_algorithm_state(&gs_handle, state_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get voc algorithm state failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check state0 %s.\n", state[0] == state_check[0] ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check state1 %s.\n", state[1] == state_check[1] ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check state2 %s.\n", state[2] == state_check[2] ? "ok" : "error");
    sen5x_interface_debug_print("sen5x: check state3 %s.\n", state[3] == state_check[3] ? "ok" : "error");
    
    /* sen5x_start_fan_cleaning test */
    sen5x_interface_debug_print("sen5x: sen5x_start_fan_cleaning test.\n");
    
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
    
    /* start fan cleaning */
    res = sen5x_start_fan_cleaning(&gs_handle);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: start fan cleaning failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 10000 ms */
    sen5x_interface_delay_ms(10000);
    
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
    
    /* sen5x_get_product_name test */
    sen5x_interface_debug_print("sen5x: sen5x_get_product_name test.\n");
    
    /* get product name */
    res = sen5x_get_product_name(&gs_handle, buf);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get product name failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: product name is %s.\n", buf);
    
    /* sen5x_get_serial_number test */
    sen5x_interface_debug_print("sen5x: sen5x_get_serial_number test.\n");
    
    /* get serial number */
    res = sen5x_get_serial_number(&gs_handle, buf);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get serial number failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: serial number is %s.\n", buf);
    
    /* sen5x_get_version test */
    sen5x_interface_debug_print("sen5x: sen5x_get_version test.\n");
    
    /* get the version */
    res = sen5x_get_version(&gs_handle, &version);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get version failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: version is 0x%02X.\n", version);
    
    /* sen5x_get_device_status test */
    sen5x_interface_debug_print("sen5x: sen5x_get_device_status test.\n");
    
    /* get device status */
    res = sen5x_get_device_status(&gs_handle, &status);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: get device status failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: device status is 0x%08X.\n", status);
    
    /* sen5x_clear_device_status test */
    sen5x_interface_debug_print("sen5x: sen5x_clear_device_status test.\n");
    
    /* clear device status */
    res = sen5x_clear_device_status(&gs_handle);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: clear device status failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check clear device status %s.\n", res == 0 ? "ok" : "error");
    
    /* sen5x_read_data_flag test */
    sen5x_interface_debug_print("sen5x: sen5x_read_data_flag test.\n");
    
    /* read data flag */
    res = sen5x_read_data_flag(&gs_handle, &flag);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: read data flag failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: data flag is 0x%02X.\n", (uint8_t)flag);
    
    /* sen5x_reset test */
    sen5x_interface_debug_print("sen5x: sen5x_reset test.\n");
    
    /* reset */
    res = sen5x_reset(&gs_handle);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: reset failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check reset %s.\n", res == 0 ? "ok" : "error");
    
    /* sen5x_temperature_compensation_convert_to_register/sen5x_temperature_compensation_convert_to_data test */
    sen5x_interface_debug_print("sen5x: sen5x_temperature_compensation_convert_to_register/sen5x_temperature_compensation_convert_to_data test.\n");
    
    f0 = (float)(rand() % 100) / 10.0f;
    f1 = (float)(rand() % 100) / 100.0f;
    f2 = (float)(rand() % 100);
    res = sen5x_temperature_compensation_convert_to_register(&gs_handle, f0, f1, f2, &reg16s0, &reg16s1, &reg16u0);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: temperature compensation convert to register failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: set temperature offset %0.2f.\n", f0);
    sen5x_interface_debug_print("sen5x: set normalized temperature offset slope %0.2f.\n", f1);
    sen5x_interface_debug_print("sen5x: set time constant %0.2f.\n", f2);
    res = sen5x_temperature_compensation_convert_to_data(&gs_handle, reg16s0, reg16s1, reg16u0, &f0_check, &f1_check, &f2_check);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: temperature compensation convert to data failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
        return 1;
    }
    sen5x_interface_debug_print("sen5x: check temperature offset %0.2f.\n", f0_check);
    sen5x_interface_debug_print("sen5x: check normalized temperature offset slope %0.2f.\n", f1_check);
    sen5x_interface_debug_print("sen5x: check time constant %0.2f.\n", f2_check);
    
    /* finish register test */
    sen5x_interface_debug_print("sen5x: finish register test.\n");
    (void)sen5x_deinit(&gs_handle);
    
    return 0;
}
