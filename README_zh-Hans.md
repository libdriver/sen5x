[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SEN5X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/sen5x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SEN5x是一个独特的传感器模块系列，将关键空气质量参数颗粒物、VOC、NOx、湿度和温度的测量结合在一个封装中。这些模块是Sensirion在环境传感方面丰富经验的结果，可提供每个传感参数的最佳性能、卓越的寿命和紧凑的外形。SEN5x传感器通过数字接口提供完全校准的输出。将所有测量参数组合在一个设备中，使空气质量设备制造商能够减少设计和集成工作，缩短开发时间，简化供应链。专有算法可以直接集成到暖通空调和空气质量应用中，从而节省资源时间，并专注于核心竞争力。Sensirion温度加速程序（STAR）引擎将设备对环境温度变化的响应速度提高了2-3倍，为最终用户提供更好的用户体验和更准确的测量结果。

LibDriver SEN5X是LibDriver推出的SEN5X的全功能驱动，该驱动提供空气质量读取、VOC或NOx指数读取、温度和湿度读取、自动清理配置和ID读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver SEN5X的源文件。

/interface目录包含了LibDriver SEN5X与平台无关的IIC总线模板。

/test目录包含了LibDriver SEN5X驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver SEN5X编程范例。

/doc目录包含了LibDriver SEN5X离线文档。

/datasheet目录包含了SEN5X数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/sen5x/index.html](https://www.libdriver.com/docs/sen5x/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。