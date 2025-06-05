[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SEN5X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sen5x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SEN5x는 미세먼지, VOC, NOx, 습도, 온도 등 주요 대기질 측정 매개변수를 단일 패키지로 통합한 독창적인 센서 모듈 제품군입니다. 센시리온의 풍부한 환경 감지 경험을 바탕으로 개발된 이 모듈은 각 감지 매개변수에 대해 최상의 성능, 뛰어난 수명, 그리고 컴팩트한 사이즈를 제공합니다. SEN5x 센서는 디지털 인터페이스를 통해 완벽하게 보정된 출력을 제공합니다. 모든 측정 매개변수를 단일 장치에 통합함으로써 대기질 측정 장치 제조업체는 설계 및 통합에 드는 노력을 줄이고, 개발 시간을 단축하며, 공급망을 간소화할 수 있습니다. 독점 알고리즘을 통해 HVAC 및 대기질 애플리케이션에 간편하게 통합하여 리소스/시간을 절약하고 핵심 역량에 집중할 수 있습니다. 구현된 센시리온 온도 가속 루틴(STAR) 엔진은 주변 온도 변화에 대한 장치의 반응을 2~3배 가속화하여 최종 사용자에게 더 나은 사용자 경험과 더욱 정확한 측정값을 제공합니다.

LibDriver SEN5X는 LibDriver에서 출시한 SEN5X의 모든 기능을 갖춘 드라이버입니다. 공기질 측정, VOC 또는 NOx 지수 측정, 온도 및 습도 측정, 자동 청소 설정, ID 측정 및 기타 기능을 제공합니다. LibDriver는 MISRA 표준을 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver SEN5X의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver SEN5X용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver SEN5X드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver SEN5X프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver SEN5X오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 SEN5X데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/sen5x/index.html](https://www.libdriver.com/docs/sen5x/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.