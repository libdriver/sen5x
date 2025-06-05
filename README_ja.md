[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SEN5X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sen5x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SEN5xは、粒子状物質、VOC、NOx、湿度、温度といった重要な空気質パラメータの測定機能を1つのパッケージに統合した、ユニークなセンサーモジュールファミリーです。このモジュールは、Sensirionの環境センシングにおける豊富な経験の結晶であり、各センシングパラメータの最高のパフォーマンス、優れた寿命、コンパクトなフォームファクタを提供します。SEN5xセンサーは、デジタルインターフェースを備えた完全に較正された出力を提供します。すべての測定パラメータを1つのデバイスに統合することで、空気質デバイスメーカーは、設計と統合の労力を軽減し、開発時間を短縮し、サプライチェーンを簡素化できます。独自のアルゴリズムにより、HVACおよび空気質アプリケーションへの簡単な統合が可能になり、リソースと時間を節約して、コアコンピテンシーに集中できます。実装されたSensirion温度加速ルーチン（STAR）エンジンは、デバイスの周囲温度変化への応答を2～3倍加速し、エンドユーザーに優れたUXとより正確な測定を提供します。

LibDriver SEN5Xは、LibDriverがリリースしたSEN5Xのフル機能ドライバです。空気質測定、VOCまたはNOx指数測定、温湿度測定、自動クリーニング設定、ID読み取りなどの機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver SEN5Xのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver SEN5X用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver SEN5Xドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver SEN5Xプログラミング例が含まれています。

/ docディレクトリには、LibDriver SEN5Xオフラインドキュメントが含まれています。

/ datasheetディレクトリには、SEN5Xデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/sen5x/index.html](https://www.libdriver.com/docs/sen5x/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。