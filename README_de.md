[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SEN5X
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sen5x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Die SEN5x-Sensoren sind eine einzigartige Familie von Sensormodulen, die die Messung kritischer Luftqualitätsparameter wie Feinstaub, flüchtige organische Verbindungen (VOC), NOx, Luftfeuchtigkeit und Temperatur in einem einzigen Gehäuse vereint. Die Module basieren auf Sensirions umfassender Erfahrung in der Umweltsensorik und bieten optimale Leistung für jeden Messparameter, eine überragende Lebensdauer sowie ein kompaktes Design. Die SEN5x-Sensoren bieten vollständig kalibrierte Ausgänge mit digitaler Schnittstelle. Die Kombination aller Messparameter in einem einzigen Gerät ermöglicht es Herstellern von Luftqualitätsgeräten, Design- und Integrationsaufwand zu reduzieren, Entwicklungszeiten zu verkürzen und ihre Lieferkette zu vereinfachen. Proprietäre Algorithmen ermöglichen die direkte Integration in HLK- und Luftqualitätsanwendungen und ermöglichen so Ressourcen- und Zeitersparnisse sowie die Konzentration auf Kernkompetenzen. Die implementierte Sensirion Temperature Acceleration Routine (STAR)-Engine beschleunigt die Reaktion des Geräts auf Änderungen der Umgebungstemperatur um den Faktor 2-3 und bietet Endanwendern so eine bessere Benutzererfahrung und genauere Messungen.

LibDriver SEN5X ist ein vollfunktionaler Treiber für SEN5X von LibDriver. Er bietet Informationen zur Luftqualität, zum VOC- oder NOx-Index, zur Temperatur und Luftfeuchtigkeit, zur automatischen Reinigungskonfiguration, zur ID-Anzeige und weitere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver SEN5X-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver SEN5X IIC.

/test enthält den Testcode des LibDriver SEN5X-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver SEN5X-Beispielcode.

/doc enthält das LibDriver SEN5X-Offlinedokument.

/Datenblatt enthält SEN5X-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/sen5x/index.html](https://www.libdriver.com/docs/sen5x/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.