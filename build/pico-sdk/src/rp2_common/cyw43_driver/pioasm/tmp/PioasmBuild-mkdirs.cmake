# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/pico/pico-sdk/tools/pioasm"
  "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pioasm"
  "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm"
  "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/tmp"
  "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src"
  "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/gitprj/mp_monitoringsystem/lcd_pwm_motor/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
