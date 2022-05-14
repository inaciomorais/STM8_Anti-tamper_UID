# STM8_Anti-tamper_UID

If we try to download the generated firmware directly to a second STM8S103 MCU it will not execute the main code due to UID inconsistency.


UID.c - Unique ID to EEPROM

ats.sh - Anti-tamper Shell-Script (Linux)

01_Led_delay_UID - Source Code Example


Terminal:
chmod +x ats.sh
./ats.sh
