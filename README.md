# pico_lcd
---
## CMake 설정
cmake -S . -B build -G "Unix Makefiles" -DPICO_BOARD=pico

## CMake 빌드
cmake --build build -j4

## 다운로드
python tools\down.py

# 업데이트 내역
220901 lcd pwm motor 제어 베이스 코드 업데이트


