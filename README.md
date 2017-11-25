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
* 設計軟體 [Altium Designer 17](http://www.altium.com/altium-designer/overview) ( PcbLib use AD [PcbLib v3.3](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v3.3) )

View
========
<img src="https://lh3.googleusercontent.com/jcZ--NzY1n5wwt5572ggELWxdBe5BOpmZK8N_IGAECsPmfrovsVIYeKPWctkLbKVIOkuCe065iONQHxwBNGAHXs6txLJDE2ufSuwidHeyodsD0G7tVleA-VVgP9MtwiRbWVwdrFcmrXhqcdrUr-fTjVaif8-Kpb3GUOP6CT0qLt_bTYjrdIZsX43Vyrg9QeZFgQkj_4EKBrd402j7nopKk8CWzVccDfswiaD04xtiYr47bRfKg_U1kZN-KhspUznDyy-HLky_vEbtJa5vvYq0pSVDDzAqRlGNE0Otc5xrYQxkEQdafFCqTT3g7UCVieBe-D4qSIPTXQU5-aBBTNGrHhrIw09QbhNadqlrwkXLXNUSWBBUZIzL9oKqUcC99zsJ2APR8DsOJQ7cNGC5zIuXtisu3DkNztSZ5Qfs4yDZpZ5C7hehLNK365QZRdCx88E2m46QrbG5OHVLohLdYlk1_EDknBNzRGfOaQ7Oplz4ypFvSXLtu0QW9coazsVprolqwgp_yfXukAW0-m0ApodfjXkfxuDJ0EO1NAjRBqW7djxXXQD-SIg4c_Gv-f43ol6YUSLA1qBiwg5sFZ8QBC8iiG2oEiN3WWvw8asJqEPH1R70L1yOhLWPDR2usiW1_G64JMXdvUBIQOy-LLGA3mI5q7qNjr6t9pjSFw=w962-h721-no"/>
<br />

[more photo ...](https://photos.app.goo.gl/Y5XqhwoiNbuzMt1m1)
