### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. SEN5X

#### 3.1 Command Instruction

1. Show sen5x chip and driver information.

   ```shell
   sen5x (-i | --information)
   ```

2. Show sen5x help.

   ```shell
   sen5x (-h | --help)
   ```

3. Show sen5x pin connections of the current board.

   ```shell
   sen5x (-p | --port)
   ```

4. Run sen5x register test.

   ```shell
   sen5x (-t reg | --test=reg) [--type=<sen50 | sen54 | sen55>]
   ```

5. Run sen5x read test, num means the test times.

   ```shell
   sen5x (-t read | --test=read) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
   ```

6. Run sen5x basic read function, num means the read times.

   ```shell
   sen5x (-e read | --example=read) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
   ```

7. Run sen5x basic pm function, num means the read times.

   ```shell
   sen5x (-e pm | --example=pm) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
   ```

8. Run sen5x basic read raw data function, num means the read times.

   ```shell
   sen5x (-e raw | --example=raw) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
   ```

9. Run sen5x basic get chip name function. 

   ```shell
   sen5x (-e name | --example=name) [--type=<sen50 | sen54 | sen55>]
   ```

10. Run sen5x basic get sn function.

   ```shell
   sen5x (-e sn | --example=sn) [--type=<sen50 | sen54 | sen55>]
   ```

11. Run sen5x basic clean function.  

   ```shell
   sen5x (-e clean | --example=clean) [--type=<sen50 | sen54 | sen55>]
   ```

12. Run sen5x basic get version function.  

    ```shell
    sen5x (-e version | --example=version) [--type=<sen50 | sen54 | sen55>]
    ```

13. Run sen5x basic get status function.  

    ```shell
    sen5x (-e status | --example=status) [--type=<sen50 | sen54 | sen55>]
    ```

#### 3.2 Command Example

```shell
sen5x -i

sen5x: chip is Sensirion SEN5X.
sen5x: manufacturer is Sensirion.
sen5x: interface is IIC.
sen5x: driver version is 1.0.
sen5x: min supply voltage is 4.5V.
sen5x: max supply voltage is 5.5V.
sen5x: max current is 100.00mA.
sen5x: max temperature is 60.0C.
sen5x: min temperature is -10.0C.
```

```shell
sen5x -p

sen5x: IIC interface SCL connected to GPIOB PIN8.
sen5x: IIC interface SDA connected to GPIOB PIN9.
```

```shell
sen5x -t reg --type=sen55

sen5x: chip is Sensirion SEN5X.
sen5x: manufacturer is Sensirion.
sen5x: interface is IIC.
sen5x: driver version is 1.0.
sen5x: min supply voltage is 4.5V.
sen5x: max supply voltage is 5.5V.
sen5x: max current is 100.00mA.
sen5x: max temperature is 60.0C.
sen5x: min temperature is -10.0C.
sen5x: start register test.
sen5x: sen5x_set_type/sen5x_get_type test.
sen5x: set type sen50.
sen5x: check type ok.
sen5x: set type sen54.
sen5x: check type ok.
sen5x: set type sen55.
sen5x: check type ok.
sen5x: sen5x_set_auto_cleaning_interval/sen5x_get_auto_cleaning_interval test.
sen5x: set auto cleaning interval 106672.
sen5x: check interval ok.
sen5x: sen5x_disable_auto_cleaning_interval test.
sen5x: check disable cleaning ok.
sen5x: sen5x_set_temperature_compensation/sen5x_get_temperature_compensation test.
sen5x: set temperature offset 67.
sen5x: set normalized temperature offset slope -9.
sen5x: set time constant 60.
sen5x: check temperature offset ok.
sen5x: check normalized temperature offset slope ok.
sen5x: check time constant ok.
sen5x: sen5x_set_warm_start/sen5x_get_warm_start test.
sen5x: set warm start 83.
sen5x: check warm start ok.
sen5x: sen5x_set_voc_algorithm_tuning/sen5x_get_voc_algorithm_tuning test.
sen5x: set index offset 42.
sen5x: set learning time offset hour 61.
sen5x: set learning time gain hour 68.
sen5x: set gating max duration minute 8.
sen5x: set std initial 74.
sen5x: set gain factor 49.
sen5x: check index offset ok.
sen5x: check learning time offset hour ok.
sen5x: check learning time gain hour ok.
sen5x: check gating max duration minute ok.
sen5x: check std initial ok.
sen5x: check gain factor ok.
sen5x: sen5x_set_nox_algorithm_tuning/sen5x_get_nox_algorithm_tuning test.
sen5x: set index offset 48.
sen5x: set learning time offset hour 75.
sen5x: set learning time gain hour 12.
sen5x: set gating max duration minute 74.
sen5x: set std initial 50.
sen5x: set gain factor 58.
sen5x: check index offset ok.
sen5x: check learning time offset hour ok.
sen5x: check learning time gain hour ok.
sen5x: check gating max duration minute ok.
sen5x: check std initial ok.
sen5x: check gain factor ok.
sen5x: sen5x_set_rht_acceleration_mode/sen5x_get_rht_acceleration_mode test.
sen5x: set rht acceleration mode low.
sen5x: check rht acceleration mode ok.
sen5x: set rht acceleration mode high.
sen5x: check rht acceleration mode ok.
sen5x: set rht acceleration mode medium.
sen5x: check rht acceleration mode ok.
sen5x: sen5x_set_voc_algorithm_state/sen5x_get_voc_algorithm_state test.
sen5x: set state0 0x6C73.
sen5x: set state1 0x249B.
sen5x: set state2 0xDF1C.
sen5x: set state3 0xB3DC.
sen5x: check state0 ok.
sen5x: check state1 ok.
sen5x: check state2 ok.
sen5x: check state3 ok.
sen5x: sen5x_start_fan_cleaning test.
sen5x: sen5x_get_product_name test.
sen5x: product name is SEN55.
sen5x: sen5x_get_serial_number test.
sen5x: serial number is 4A06F2838CD94025.
sen5x: sen5x_get_version test.
sen5x: version is 0x02.
sen5x: sen5x_get_device_status test.
sen5x: device status is 0x00000000.
sen5x: sen5x_clear_device_status test.
sen5x: check clear device status ok.
sen5x: sen5x_read_data_flag test.
sen5x: data flag is 0x00.
sen5x: sen5x_reset test.
sen5x: check reset ok.
sen5x: sen5x_temperature_compensation_convert_to_register/sen5x_temperature_compensation_convert_to_data test.
sen5x: set temperature offset 3.30.
sen5x: set normalized temperature offset slope 0.50.
sen5x: set time constant 62.00.
sen5x: check temperature offset 3.30.
sen5x: check normalized temperature offset slope 0.50.
sen5x: check time constant 62.00.
sen5x: finish register test.
```

```shell
sen5x -t read --type=sen55 --times=3

sen5x: chip is Sensirion SEN5X.
sen5x: manufacturer is Sensirion.
sen5x: interface is IIC.
sen5x: driver version is 1.0.
sen5x: min supply voltage is 4.5V.
sen5x: max supply voltage is 5.5V.
sen5x: max current is 100.00mA.
sen5x: max temperature is 60.0C.
sen5x: min temperature is -10.0C.
sen5x: start read test.
sen5x: sen5x_read test.
sen55: pm1.0 is 1.40 ug/m3.
sen55: pm2.5 is 2.10 ug/m3.
sen55: pm4.0 is 2.60 ug/m3.
sen55: pm10.0 is 2.80 ug/m3.
sen55: compensated ambient humidity is 36.11%.
sen55: compensated ambient temperature is 28.17C.
sen55: voc index is 0.00.
sen55: nox index is 7.00.
sen55: pm1.0 is 1.80 ug/m3.
sen55: pm2.5 is 2.20 ug/m3.
sen55: pm4.0 is 2.40 ug/m3.
sen55: pm10.0 is 2.50 ug/m3.
sen55: compensated ambient humidity is 36.12%.
sen55: compensated ambient temperature is 28.17C.
sen55: voc index is 0.00.
sen55: nox index is 7.00.
sen55: pm1.0 is 2.30 ug/m3.
sen55: pm2.5 is 2.70 ug/m3.
sen55: pm4.0 is 2.90 ug/m3.
sen55: pm10.0 is 3.00 ug/m3.
sen55: compensated ambient humidity is 36.22%.
sen55: compensated ambient temperature is 28.17C.
sen55: voc index is 0.00.
sen55: nox index is 7.00.
sen5x: sen5x_read_pm_value test.
sen5x: pm1.0 is 2.50 ug/m3.
sen5x: pm2.5 is 3.00 ug/m3.
sen5x: pm4.0 is 3.30 ug/m3.
sen5x: pm10.0 is 3.40 ug/m3.
sen5x: pm0.5 is 16.40 cm3.
sen5x: pm1.0 is 19.40 cm3.
sen5x: pm2.5 is 19.80 cm3.
sen5x: pm4.0 is 19.90 cm3.
sen5x: pm10.0 is 19.90 cm3.
sen5x: typical is 0.56 um.
sen5x: pm1.0 is 2.80 ug/m3.
sen5x: pm2.5 is 3.20 ug/m3.
sen5x: pm4.0 is 3.50 ug/m3.
sen5x: pm10.0 is 3.60 ug/m3.
sen5x: pm0.5 is 18.20 cm3.
sen5x: pm1.0 is 21.50 cm3.
sen5x: pm2.5 is 21.90 cm3.
sen5x: pm4.0 is 22.00 cm3.
sen5x: pm10.0 is 22.00 cm3.
sen5x: typical is 0.56 um.
sen5x: pm1.0 is 3.10 ug/m3.
sen5x: pm2.5 is 3.60 ug/m3.
sen5x: pm4.0 is 3.90 ug/m3.
sen5x: pm10.0 is 4.00 ug/m3.
sen5x: pm0.5 is 20.50 cm3.
sen5x: pm1.0 is 24.20 cm3.
sen5x: pm2.5 is 24.60 cm3.
sen5x: pm4.0 is 24.70 cm3.
sen5x: pm10.0 is 24.70 cm3.
sen5x: typical is 0.56 um.
sen5x: sen5x_read_raw_value test.
sen5x: humidity is 37.79%.
sen5x: temperature is 28.29C.
sen5x: voc is 27719.00.
sen5x: nox is 17459.00.
sen5x: humidity is 37.53%.
sen5x: temperature is 28.33C.
sen5x: voc is 27840.00.
sen5x: nox is 17293.00.
sen5x: humidity is 37.47%.
sen5x: temperature is 28.38C.
sen5x: voc is 27943.00.
sen5x: nox is 17182.00.
sen5x: start measurement without pm test.
sen55: compensated ambient humidity is 36.49%.
sen55: compensated ambient temperature is 28.48C.
sen55: voc index is 0.00.
sen55: nox index is 0.00.
sen55: compensated ambient humidity is 36.48%.
sen55: compensated ambient temperature is 28.48C.
sen55: voc index is 0.00.
sen55: nox index is 0.00.
sen55: compensated ambient humidity is 36.43%.
sen55: compensated ambient temperature is 28.48C.
sen55: voc index is 0.00.
sen55: nox index is 0.00.
sen5x: finish read test.
```

```shell
sen5x -e read --type=sen55 --times=3

sen55: 1/3.
sen55: pm1.0 is 4.10 ug/m3.
sen55: pm2.5 is 7.00 ug/m3.
sen55: pm4.0 is 9.20 ug/m3.
sen55: pm10.0 is 10.30 ug/m3.
sen55: compensated ambient humidity is 35.89%.
sen55: compensated ambient temperature is 29.37C.
sen55: voc index is 0.00.
sen55: nox index is 7.00.
sen55: 2/3.
sen55: pm1.0 is 4.00 ug/m3.
sen55: pm2.5 is 5.00 ug/m3.
sen55: pm4.0 is 5.70 ug/m3.
sen55: pm10.0 is 6.10 ug/m3.
sen55: compensated ambient humidity is 35.85%.
sen55: compensated ambient temperature is 29.37C.
sen55: voc index is 0.00.
sen55: nox index is 7.00.
sen55: 3/3.
sen55: pm1.0 is 3.90 ug/m3.
sen55: pm2.5 is 4.70 ug/m3.
sen55: pm4.0 is 5.20 ug/m3.
sen55: pm10.0 is 5.40 ug/m3.
sen55: compensated ambient humidity is 35.76%.
sen55: compensated ambient temperature is 29.37C.
sen55: voc index is 0.00.
sen55: nox index is 7.00.
```

```shell
sen5x -e pm --type=sen55 --times=3

sen5x: 1/3.
sen5x: pm1.0 is 0.70 ug/m3.
sen5x: pm2.5 is 0.70 ug/m3.
sen5x: pm4.0 is 0.70 ug/m3.
sen5x: pm10.0 is 0.70 ug/m3.
sen5x: pm0.5 is 4.50 cm3.
sen5x: pm1.0 is 5.20 cm3.
sen5x: pm2.5 is 5.20 cm3.
sen5x: pm4.0 is 5.20 cm3.
sen5x: pm10.0 is 5.20 cm3.
sen5x: typical is 0.28 um.
sen5x: 2/3.
sen5x: pm1.0 is 0.70 ug/m3.
sen5x: pm2.5 is 0.80 ug/m3.
sen5x: pm4.0 is 0.80 ug/m3.
sen5x: pm10.0 is 0.80 ug/m3.
sen5x: pm0.5 is 5.00 cm3.
sen5x: pm1.0 is 5.80 cm3.
sen5x: pm2.5 is 5.80 cm3.
sen5x: pm4.0 is 5.80 cm3.
sen5x: pm10.0 is 5.80 cm3.
sen5x: typical is 0.35 um.
sen5x: 3/3.
sen5x: pm1.0 is 1.50 ug/m3.
sen5x: pm2.5 is 1.60 ug/m3.
sen5x: pm4.0 is 1.60 ug/m3.
sen5x: pm10.0 is 1.60 ug/m3.
sen5x: pm0.5 is 10.20 cm3.
sen5x: pm1.0 is 11.80 cm3.
sen5x: pm2.5 is 11.80 cm3.
sen5x: pm4.0 is 11.80 cm3.
sen5x: pm10.0 is 11.80 cm3.
sen5x: typical is 0.41 um.
```

```shell
sen5x -e raw --type=sen55 --times=3

sen5x: 1/3.
sen5x: humidity is 35.29%.
sen5x: temperature is 29.41C.
sen5x: voc is 27133.00.
sen5x: nox is 7.00.
sen5x: 2/3.
sen5x: humidity is 35.20%.
sen5x: temperature is 29.43C.
sen5x: voc is 28252.00.
sen5x: nox is 7.00.
sen5x: 3/3.
sen5x: humidity is 35.31%.
sen5x: temperature is 29.44C.
sen5x: voc is 28614.00.
sen5x: nox is 7.00.
```

```shell
sen5x -e name --type=sen55

sen5x: product name is SEN55.
```

```shell
sen5x -e sn --type=sen55

sen5x: sn is 4A06F2838CD94025.
```

```shell
sen5x -e version --type=sen55

sen5x: version is 0x02.
```

```shell
sen5x -e status --type=sen55

sen5x: status is 00000000.
```

```shell
sen5x -e clean --type=sen55

sen5x: start cleaning.
sen5x: stop cleaning.
```

```shell
sen5x -h

Usage:
  sen5x (-i | --information)
  sen5x (-h | --help)
  sen5x (-p | --port)
  sen5x (-t reg | --test=reg) [--type=<sen50 | sen54 | sen55>]
  sen5x (-t read | --test=read) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
  sen5x (-e read | --example=read) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
  sen5x (-e pm | --example=pm) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
  sen5x (-e raw | --example=raw) [--type=<sen50 | sen54 | sen55>] [--times=<num>]
  sen5x (-e name | --example=name) [--type=<sen50 | sen54 | sen55>]
  sen5x (-e sn | --example=sn) [--type=<sen50 | sen54 | sen55>]
  sen5x (-e clean | --example=clean) [--type=<sen50 | sen54 | sen55>]
  sen5x (-e version | --example=version) [--type=<sen50 | sen54 | sen55>]
  sen5x (-e status | --example=status) [--type=<sen50 | sen54 | sen55>]

Options:
  -e <read | pm | raw | name | sn | clean | version | status>,
      --example=<read | pm | raw | name | sn | clean | version | status>
                                          Run the driver example.
  -h, --help                              Show the help.
  -i, --information                       Show the chip information.
  -p, --port                              Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>    Run the driver test.
      --type=<sen50 | sen54 | sen55>      Set the sensor type.([default: sen55])
      --times=<num>                       Set the running times.([default: 3])
```

