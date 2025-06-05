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
 * @file      driver_sen5x_basic.c
 * @brief     driver sen5x basic source file
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

#include "driver_sen5x_basic.h"

static sen5x_handle_t gs_handle;        /**< sen5x handle */

/**
 * @brief     basic example init
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t sen5x_basic_init(sen5x_type_t type)
{
    uint8_t res;
    
    /* link functions */
    DRIVER_SEN5X_LINK_INIT(&gs_handle, sen5x_handle_t);
    DRIVER_SEN5X_LINK_IIC_INIT(&gs_handle, sen5x_interface_iic_init);
    DRIVER_SEN5X_LINK_IIC_DEINIT(&gs_handle, sen5x_interface_iic_deinit);
    DRIVER_SEN5X_LINK_IIC_WRITE_COMMAND(&gs_handle, sen5x_interface_iic_write_cmd);
    DRIVER_SEN5X_LINK_IIC_READ_COMMAND(&gs_handle, sen5x_interface_iic_read_cmd);
    DRIVER_SEN5X_LINK_DELAY_MS(&gs_handle, sen5x_interface_delay_ms);
    DRIVER_SEN5X_LINK_DEBUG_PRINT(&gs_handle, sen5x_interface_debug_print);
    
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
    
    /* set auto cleaning interval */
    res = sen5x_set_auto_cleaning_interval(&gs_handle, SEN5X_BASIC_DEFAULT_AUTO_CLEANING_INTERVAL);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: set auto cleaning interval failed.\n");
        (void)sen5x_deinit(&gs_handle);
        
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

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t sen5x_basic_deinit(void)
{
    uint8_t res;
    
    /* stop measurement */
    res = sen5x_stop_measurement(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* deinit */
    res = sen5x_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read raw value
 * @param[out] *raw pointer to a sen5x_raw_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen55_basic_read_raw_value(sen5x_raw_t *raw)
{
    uint8_t res;
    
    /* read raw value */
    res = sen5x_read_raw_value(&gs_handle, raw);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read pm value
 * @param[out] *pm pointer to a sen5x_pm_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen55_basic_read_pm_value(sen5x_pm_t *pm)
{
    uint8_t res;
    
    /* read pm value */
    res = sen5x_read_pm_value(&gs_handle, pm);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *output pointer to a sen55_data_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen55_basic_read(sen55_data_t *output)
{
    uint8_t res;
    
    /* read data */
    res = sen55_read(&gs_handle, output);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *output pointer to a sen54_data_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen54_basic_read(sen54_data_t *output)
{
    uint8_t res;
    
    /* read data */
    res = sen54_read(&gs_handle, output);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *output pointer to a sen50_data_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen50_basic_read(sen50_data_t *output)
{
    uint8_t res;
    
    /* read data */
    res = sen50_read(&gs_handle, output);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example start fan cleaning
 * @return status code
 *         - 0 success
 *         - 1 start fan cleaning failed
 * @note   none
 */
uint8_t sen5x_basic_start_fan_cleaning(void)
{
    if (sen5x_start_fan_cleaning(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example reset
 * @return status code
 *         - 0 success
 *         - 1 reset failed
 * @note   none
 */
uint8_t sen5x_basic_reset(void)
{
    if (sen5x_reset(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get the product name
 * @param[out] *name pointer to a name buffer
 * @return     status code
 *             - 0 success
 *             - 1 get product name failed
 * @note       none
 */
uint8_t sen5x_basic_get_product_name(char name[32])
{
    if (sen5x_get_product_name(&gs_handle, name) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get the serial number
 * @param[out] *sn pointer to a sn buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial number failed
 * @note       none
 */
uint8_t sen5x_basic_get_serial_number(char sn[32])
{
    if (sen5x_get_serial_number(&gs_handle, sn) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get the version
 * @param[out] *version pointer to a version buffer
 * @return     status code
 *             - 0 success
 *             - 1 get version failed
 * @note       none
 */
uint8_t sen5x_basic_get_version(uint8_t *version)
{
    if (sen5x_get_version(&gs_handle, version) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get the status
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 * @note       none
 */
uint8_t sen5x_basic_get_status(uint32_t *status)
{
    if (sen5x_get_device_status(&gs_handle, status) != 0)
    {
        return 1;
    }
    else
    {
        if (sen5x_clear_device_status(&gs_handle) != 0)
        {
            return 1;
        }
        
        return 0;
    }
}
