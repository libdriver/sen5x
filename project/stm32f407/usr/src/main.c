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
 * @file      main.c
 * @brief     main source file
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
#include "driver_sen5x_read_test.h"
#include "driver_sen5x_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];             /**< uart buffer */
volatile uint16_t g_len;        /**< uart buffer length */

/**
 * @brief     sen5x full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t sen5x(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"type", required_argument, NULL, 1},
        {"times", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    sen5x_type_t chip_type = SEN55;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* interface */
            case 1 :
            {
                /* set the interface */
                if (strcmp("sen50", optarg) == 0)
                {
                    chip_type = SEN50;
                }
                else if (strcmp("sen54", optarg) == 0)
                {
                    chip_type = SEN54;
                }
                else if (strcmp("sen55", optarg) == 0)
                {
                    chip_type = SEN55;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 2 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* reg test */
        if (sen5x_register_test(chip_type) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* read test */
        if (sen5x_read_test(chip_type, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 2000 ms */
        sen5x_interface_delay_ms(2000);
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            if (chip_type == SEN50)
            {
                sen50_data_t output;
                
                /* read data */
                res = sen50_basic_read(&output);
                if (res != 0)
                {
                    sen5x_interface_debug_print("sen50: read failed.\n");
                    (void)sen5x_basic_deinit();
                    
                    return 1;
                }
                sen5x_interface_debug_print("sen50: %d/%d.\n", i + 1, times);
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
            else if (chip_type == SEN54)
            {
                sen54_data_t output;
                
                /* read data */
                res = sen54_basic_read(&output);
                if (res != 0)
                {
                    sen5x_interface_debug_print("sen54: read failed.\n");
                    (void)sen5x_basic_deinit();
                    
                    return 1;
                }
                sen5x_interface_debug_print("sen54: %d/%d.\n", i + 1, times);
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
                res = sen55_basic_read(&output);
                if (res != 0)
                {
                    sen5x_interface_debug_print("sen55: read failed.\n");
                    (void)sen5x_basic_deinit();
                    
                    return 1;
                }
                sen5x_interface_debug_print("sen55: %d/%d.\n", i + 1, times);
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
        
        /* deinit */
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_pm", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 2000 ms */
        sen5x_interface_delay_ms(2000);
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            sen5x_pm_t pm;
            
            res = sen55_basic_read_pm_value(&pm);
            if (res != 0)
            {
                sen5x_interface_debug_print("sen5x: read failed.\n");
                (void)sen5x_basic_deinit();
                
                return 1;
            }
            sen5x_interface_debug_print("sen5x: %d/%d.\n", i + 1, times);
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
        
        /* deinit */
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_raw", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        if (chip_type == SEN50)
        {
            sen5x_interface_debug_print("sen5x: sen50 doesn't support this function.\n");
            
            return 0;
        }
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 2000 ms */
        sen5x_interface_delay_ms(2000);
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            sen5x_raw_t raw;
            
            /* read raw value */
            res = sen55_basic_read_raw_value(&raw);
            if (res != 0)
            {
                sen5x_interface_debug_print("sen5x: read raw value failed.\n");
                (void)sen5x_basic_deinit();
                
                return 1;
            }
            sen5x_interface_debug_print("sen5x: %d/%d.\n", i + 1, times);
            sen5x_interface_debug_print("sen5x: humidity is %0.2f%%.\n", raw.humidity_percentage);
            sen5x_interface_debug_print("sen5x: temperature is %0.2fC.\n", raw.temperature_degree);
            sen5x_interface_debug_print("sen5x: voc is %0.2f.\n", raw.voc);
            sen5x_interface_debug_print("sen5x: nox is %0.2f.\n", raw.nox);
            
            /* delay 2000 ms */
            sen5x_interface_delay_ms(2000);
        }
        
        /* deinit */
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_name", type) == 0)
    {
        uint8_t res;
        char name[32];
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* get the name */
        res = sen5x_basic_get_product_name((char *)name);
        if (res != 0)
        {
            (void)sen5x_basic_deinit();
            
            return 1;
        }
        
        /* print */
        sen5x_interface_debug_print("sen5x: product name is %s.\n", name);
        
        /* deinit */
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_sn", type) == 0)
    {
        uint8_t res;
        char sn[32];
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* get the sn */
        res = sen5x_basic_get_serial_number((char *)sn);
        if (res != 0)
        {
            (void)sen5x_basic_deinit();
            
            return 1;
        }
        
        /* print */
        sen5x_interface_debug_print("sen5x: sn is %s.\n", sn);
        
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_clean", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* print */
        sen5x_interface_debug_print("sen5x: start cleaning.\n");
        
        /* start fan cleaning */
        res = sen5x_basic_start_fan_cleaning();
        if (res != 0)
        {
            (void)sen5x_basic_deinit();
            
            return 1;
        }
        
        /* delay 10s */
        sen5x_interface_delay_ms(1000 * 10);
        
        /* print */
        sen5x_interface_debug_print("sen5x: stop cleaning.\n");
        
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_version", type) == 0)
    {
        uint8_t res;
        uint8_t version;
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* get the version */
        res = sen5x_basic_get_version((uint8_t *)&version);
        if (res != 0)
        {
            (void)sen5x_basic_deinit();
            
            return 1;
        }
        
        /* print */
        sen5x_interface_debug_print("sen5x: version is 0x%02X.\n", version);
        
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_status", type) == 0)
    {
        uint8_t res;
        uint32_t status;
        
        /* init */
        res = sen5x_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* get the status */
        res = sen5x_basic_get_status((uint32_t *)&status);
        if (res != 0)
        {
            (void)sen5x_basic_deinit();
            
            return 1;
        }
        
        /* print */
        sen5x_interface_debug_print("sen5x: status is %08X.\n", status);
        
        (void)sen5x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        sen5x_interface_debug_print("Usage:\n");
        sen5x_interface_debug_print("  sen5x (-i | --information)\n");
        sen5x_interface_debug_print("  sen5x (-h | --help)\n");
        sen5x_interface_debug_print("  sen5x (-p | --port)\n");
        sen5x_interface_debug_print("  sen5x (-t reg | --test=reg) [--type=<sen50 | sen54 | sen55>]\n");
        sen5x_interface_debug_print("  sen5x (-t read | --test=read) [--type=<sen50 | sen54 | sen55>] [--times=<num>]\n");
        sen5x_interface_debug_print("  sen5x (-e read | --example=read) [--type=<sen50 | sen54 | sen55>] [--times=<num>]\n");
        sen5x_interface_debug_print("  sen5x (-e pm | --example=pm) [--type=<sen50 | sen54 | sen55>] [--times=<num>]\n");
        sen5x_interface_debug_print("  sen5x (-e raw | --example=raw) [--type=<sen50 | sen54 | sen55>] [--times=<num>]\n");
        sen5x_interface_debug_print("  sen5x (-e name | --example=name) [--type=<sen50 | sen54 | sen55>]\n");
        sen5x_interface_debug_print("  sen5x (-e sn | --example=sn) [--type=<sen50 | sen54 | sen55>]\n");
        sen5x_interface_debug_print("  sen5x (-e clean | --example=clean) [--type=<sen50 | sen54 | sen55>]\n");
        sen5x_interface_debug_print("  sen5x (-e version | --example=version) [--type=<sen50 | sen54 | sen55>]\n");
        sen5x_interface_debug_print("  sen5x (-e status | --example=status) [--type=<sen50 | sen54 | sen55>]\n");
        sen5x_interface_debug_print("\n");
        sen5x_interface_debug_print("Options:\n");
        sen5x_interface_debug_print("  -e <read | pm | raw | name | sn | clean | version | status>,\n");
        sen5x_interface_debug_print("      --example=<read | pm | raw | name | sn | clean | version | status>\n");
        sen5x_interface_debug_print("                                          Run the driver example.\n");
        sen5x_interface_debug_print("  -h, --help                              Show the help.\n");
        sen5x_interface_debug_print("  -i, --information                       Show the chip information.\n");
        sen5x_interface_debug_print("  -p, --port                              Display the pin connections of the current board.\n");
        sen5x_interface_debug_print("  -t <reg | read>, --test=<reg | read>    Run the driver test.\n");
        sen5x_interface_debug_print("      --type=<sen50 | sen54 | sen55>      Set the sensor type.([default: sen55])\n");
        sen5x_interface_debug_print("      --times=<num>                       Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        sen5x_info_t info;
        
        /* print sen5x info */
        sen5x_info(&info);
        sen5x_interface_debug_print("sen5x: chip is %s.\n", info.chip_name);
        sen5x_interface_debug_print("sen5x: manufacturer is %s.\n", info.manufacturer_name);
        sen5x_interface_debug_print("sen5x: interface is %s.\n", info.interface);
        sen5x_interface_debug_print("sen5x: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sen5x_interface_debug_print("sen5x: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sen5x_interface_debug_print("sen5x: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sen5x_interface_debug_print("sen5x: max current is %0.2fmA.\n", info.max_current_ma);
        sen5x_interface_debug_print("sen5x: max temperature is %0.1fC.\n", info.temperature_max);
        sen5x_interface_debug_print("sen5x: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        sen5x_interface_debug_print("sen5x: IIC interface SCL connected to GPIOB PIN8.\n");
        sen5x_interface_debug_print("sen5x: IIC interface SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register sen5x function */
    shell_init();
    shell_register("sen5x", sen5x);
    uart_print("sen5x: welcome to libdriver sen5x.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("sen5x: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("sen5x: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("sen5x: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("sen5x: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("sen5x: param is invalid.\n");
            }
            else
            {
                uart_print("sen5x: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
