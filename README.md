[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SEN5X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sen5x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The SEN5x is a unique sensor module family combining the measurement of critical air quality parameters particulate matter, VOC, NOx, humidity, and temperature – in a single package. The modules are a result of Sensirion’s extensive experience in environmental sensing and offers best possible performance of each sensing parameter, a superior lifetime, as well as a compact form factor. The SEN5x sensors provide fully calibrated outputs with a digital interface. The combination of all measurement parameters in a single device allows manufacturers of air quality devices to reduce design and integration efforts, shorten development times and simplify their supply chain. Proprietary algorithms enable straightforward integration into HVAC and air quality applications allowing resource/time savings and focus on core competencies. The implemented Sensirion Temperature Acceleration Routine (STAR) engine accelerates the device’s response to ambient temperature change by a factor of 2-3 to provide better UX and more accurate measurements to end users.

LibDriver SEN5X is a full-featured driver of SEN5X launched by LibDriver. It provides air quality reading, VOC or NOx index reading, temperature and humidity reading, automatic cleaning configuration, ID reading and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver SEN5X source files.

/interface includes LibDriver SEN5X IIC platform independent template.

/test includes LibDriver SEN5X driver test code and this code can test the chip necessary function simply.

/example includes LibDriver SEN5X sample code.

/doc includes LibDriver SEN5X offline document.

/datasheet includes SEN5X datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver. 

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_sen5x_basic.h"

uint8_t res;
uint32_t i;
char name[32];
char sn[32];
uint8_t version;
uint32_t status;

/* init */
res = sen5x_basic_init(SEN55);
if (res != 0)
{
    return 1;
}

/* delay 2000 ms */
sen5x_interface_delay_ms(2000);

...
    
/* loop */
for (i = 0; i < 3; i++)
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
        sen5x_interface_debug_print("sen50: %d/%d.\n", i + 1, 3);
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
        sen5x_interface_debug_print("sen54: %d/%d.\n", i + 1, 3);
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
        sen5x_interface_debug_print("sen55: %d/%d.\n", i + 1, 3);
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
    
    ...
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    sen5x_pm_t pm;

    res = sen55_basic_read_pm_value(&pm);
    if (res != 0)
    {
        sen5x_interface_debug_print("sen5x: read failed.\n");
        (void)sen5x_basic_deinit();

        return 1;
    }
    sen5x_interface_debug_print("sen5x: %d/%d.\n", i + 1, 3);
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
    
    ...
}

...
    
/* loop */
for (i = 0; i < 3; i++)
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
    sen5x_interface_debug_print("sen5x: %d/%d.\n", i + 1, 3);
    sen5x_interface_debug_print("sen5x: humidity is %0.2f%%.\n", raw.humidity_percentage);
    sen5x_interface_debug_print("sen5x: temperature is %0.2fC.\n", raw.temperature_degree);
    sen5x_interface_debug_print("sen5x: voc is %0.2f.\n", raw.voc);
    sen5x_interface_debug_print("sen5x: nox is %0.2f.\n", raw.nox);

    /* delay 2000 ms */
    sen5x_interface_delay_ms(2000);
    
    ...
}

...
    
/* get the name */
res = sen5x_basic_get_product_name((char *)name);
if (res != 0)
{
    (void)sen5x_basic_deinit();

    return 1;
}

/* print */
sen5x_interface_debug_print("sen5x: product name is %s.\n", name);

...
    
/* get the sn */
res = sen5x_basic_get_serial_number((char *)sn);
if (res != 0)
{
    (void)sen5x_basic_deinit();

    return 1;
}

/* print */
sen5x_interface_debug_print("sen5x: sn is %s.\n", sn);

...
    
/* start fan cleaning */
res = sen5x_basic_start_fan_cleaning();
if (res != 0)
{
    (void)sen5x_basic_deinit();

    return 1;
}

/* delay 10s */
sen5x_interface_delay_ms(1000 * 10);

...
    
/* get the version */
res = sen5x_basic_get_version((uint8_t *)&version);
if (res != 0)
{
    (void)sen5x_basic_deinit();

    return 1;
}

/* print */
sen5x_interface_debug_print("sen5x: version is 0x%02X.\n", version);

...

/* get the status */
res = sen5x_basic_get_status((uint32_t *)&status);
if (res != 0)
{
    (void)sen5x_basic_deinit();

    return 1;
}

/* print */
sen5x_interface_debug_print("sen5x: status is %08X.\n", status);

...
    
/* deinit */
(void)sen5x_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/sen5x/index.html](https://www.libdriver.com/docs/sen5x/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.