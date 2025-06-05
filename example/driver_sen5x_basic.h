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
 * @file      driver_sen5x_basic.h
 * @brief     driver sen5x basic header file
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

#ifndef DRIVER_SEN5X_BASIC_H
#define DRIVER_SEN5X_BASIC_H

#include "driver_sen5x_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup sen5x_example_driver sen5x example driver function
 * @brief    sen5x example driver modules
 * @ingroup  sen5x_driver
 * @{
 */
 
/**
 * @brief sen5x basic example default definition
 */
#define SEN5X_BASIC_DEFAULT_AUTO_CLEANING_INTERVAL        3600 * 24                      /**< 1 day */

/**
 * @brief     basic example init
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t sen5x_basic_init(sen5x_type_t type);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t sen5x_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *output pointer to a sen55_data_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen55_basic_read(sen55_data_t *output);

/**
 * @brief      basic example read
 * @param[out] *output pointer to a sen54_data_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen54_basic_read(sen54_data_t *output);

/**
 * @brief      basic example read
 * @param[out] *output pointer to a sen50_data_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen50_basic_read(sen50_data_t *output);

/**
 * @brief      basic example read pm value
 * @param[out] *pm pointer to a sen5x_pm_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen55_basic_read_pm_value(sen5x_pm_t *pm);

/**
 * @brief      basic example read raw value
 * @param[out] *raw pointer to a sen5x_raw_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sen55_basic_read_raw_value(sen5x_raw_t *raw);

/**
 * @brief  basic example start fan cleaning
 * @return status code
 *         - 0 success
 *         - 1 start fan cleaning failed
 * @note   none
 */
uint8_t sen5x_basic_start_fan_cleaning(void);

/**
 * @brief  basic example reset
 * @return status code
 *         - 0 success
 *         - 1 reset failed
 * @note   none
 */
uint8_t sen5x_basic_reset(void);

/**
 * @brief      basic example get the product name
 * @param[out] *name pointer to a name buffer
 * @return     status code
 *             - 0 success
 *             - 1 get product name failed
 * @note       none
 */
uint8_t sen5x_basic_get_product_name(char name[32]);

/**
 * @brief      basic example get the serial number
 * @param[out] *sn pointer to a sn buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial number failed
 * @note       none
 */
uint8_t sen5x_basic_get_serial_number(char sn[32]);

/**
 * @brief      basic example get the version
 * @param[out] *version pointer to a version buffer
 * @return     status code
 *             - 0 success
 *             - 1 get version failed
 * @note       none
 */
uint8_t sen5x_basic_get_version(uint8_t *version);

/**
 * @brief      basic example get the status
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 * @note       none
 */
uint8_t sen5x_basic_get_status(uint32_t *status);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
