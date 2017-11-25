KSDK
========
[![GitHub version](https://img.shields.io/badge/version-v2.0-brightgreen.svg)](https://github.com/KitSprout/KSDK)
[![GitHub license](https://img.shields.io/badge/license-%20MIT%20%2F%20CC%20BY--SA%204.0-blue.svg)](https://github.com/KitSprout/KSDK/blob/master/LICENSE)
[![GitHub pcb library](https://img.shields.io/badge/pcb%20library-%20v3.3-yellow.svg)](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v3.3)

KSDK 是一款 STM32 / NRF52 與慣性感測器的開發板，主控採用 STM32F411CE 與 NRF52832 芯片，可透過 4 PIN 訊號線交換信號，
微控制器共同連接九軸慣性感測器、氣壓計，兩者皆可直接讀取感測器資料，供電部分除了 USB 連接外，亦可以透過 CR2032 水銀電池或是鋰電池供應，
燒錄部分透過板載的燒錄器來燒錄，並可依 JUMPER 來切換燒錄對象，亦可單純當成燒錄器來燒錄其他裝置。

Hardware
========
* 控制器 : [STM32F411CE](http://www.st.com/en/microcontrollers/stm32f411ce.html) 48Pin 100MHz DSP FPU / [nRF52832](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832) 48Pin 64MHz DSP FPU
* 感測器 : [ICM20948](https://www.invensense.com/products/motion-tracking/9-axis/icm-20948/) + [LPS22HB](http://www.st.com/content/st_com/en/products/mems-and-sensors/pressure-sensors/lps22hb.html) + [IST8308](http://www.isentek.com/zhtw/the_product.php?pid=4)
* 設計軟體 [Altium Designer 17](http://www.altium.com/altium-designer/overview) ( PcbLib use AD [PcbLib v3.2](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v3.3) )

View
========
<img src="https://lh3.googleusercontent.com/KRaXY9_y2c63khnaJd0I-xGH5iEMRpb-2Z_fGK9l7BGyx0Rf1Pl056yxfaVyXBTBp0xEtxJy4i_km8UMeoF-F89uhR6Vdl8gRwRiyPS5YZAB2STL9HnH9SjZXZJxjB6NQ0-YBtCm59OPHajSMVljYR5W6VPoy02LizebFrb2QY0QfHMR8B6VXgwYCf08mMXzpGqfWH5BG6h9dIWtF3WYut-rRiy1-NEpWizibhR_KpTSNNjNRtB4lTC1MSyoFcS46u92thEqHtUZ43dSTOzyhSJl1-4w5Zqc3bfDUU0fAfgj01oXDEU_4w22wFf-iOUAM7O9NKjf1eJ0WoxSH62kKQPrM93e4EshCEt_2wNoDYN7BdKYA7GAZC-Hg2lY93kn-K3rAY3VtuvuDuHsqgJo5VbQ-XpsYvLDrzNK2ABcIoN-S-1vNYEONYuOSG9wkv3XXPxl0aSqpUPyKF2YgvD3d2HoLGMSdEUnAvd5_pVxnzFBUPzy28wxMCoK8xX3hKb7F1LEAEJ6GynfHDKN3__bySXCAmDttj7ZGdzIi1IaKesoA3p-NE1Yg7uGJsRakFrf1peiLF9Mzh8m1PyptNnpL2LEWyJhCpUscsCzzOJFVQ=w1026-h769-no"/>
<br />
