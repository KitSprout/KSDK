IMUDevKit
========
[![GitHub version](https://img.shields.io/badge/version-v1.0-brightgreen.svg)](https://github.com/KitSprout/IMUDevKit)
[![GitHub license](https://img.shields.io/badge/license-%20MIT%20%2F%20CC%20BY--SA%204.0-blue.svg)](https://github.com/KitSprout/IMUDevKit/blob/master/LICENSE)
[![GitHub pcb library](https://img.shields.io/badge/pcb%20library-%20v2.15-yellow.svg)](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.15)


IMUDevKit 是一個集成微控制器（STM32F411C）、3-Axis 加速度計、3-Axis 陀螺儀（MPU6500 / ICM20602）、3-Axis 電子羅盤（IST8310）、氣壓計（LPS25HB）與燒錄器於一體的 10DOF 開發模組，設計分為燒錄器、控制器、感測器三部分，中間以排針隔離開來，目前有兩種版本，一種是 ICM20602 與 IST8310 分別以 SPI 與 I2C 獨立連接，另一種則是 MPU6500 透過 AUX_I2C 連接 IST8310，控制器僅透過 MPU6500 來訪問 IST8310。

Hardware
========
* 控制器　 : STM32F411C 48Pin 100MHz DSP FPU
* 感測器　 : [MPU6500](https://www.invensense.com/products/motion-tracking/6-axis/mpu-6500/) / [ICM20602](https://www.invensense.com/products/motion-tracking/6-axis/icm-20602/) + [IST8310](http://www.isentek.com/en/the_product.php?pid=4)+ [LPS25HB](http://www.st.com/en/mems-and-sensors/lps25hb.html)
* 設計軟體 [Altium Designer 17](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.15](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.15) )

View
========

Schematic
========

Get it
========
