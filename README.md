# STM8_Anti-tamper_UID

If we try to download the generated firmware directly to a second STM8S103 MCU it will not execute the main code due to UID inconsistency.

UID - Unique ID - 96-bit unique key for each device

UID.c - Unique ID to device EEPROM

ats.sh - Anti-tamper Shell-Script (Linux Automated Programming Routine)

01_Led_delay_UID.c - Source Code Example


Terminal:

chmod +x ats.sh

./ats.sh
