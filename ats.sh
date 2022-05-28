#!/bin/bash

﻿# A. Inácio Morais - 05/2022 
# anderson.morais@protonmail.com - Brazil

  # unlock
stm8flash -c stlinkv2 -p stm8s103f3 -u

sdcc -mstm8 --std-c99 UID.c

stm8flash -c stlinkv2 -p stm8s103f3 -w UID.ihx

sleep 2

stm8flash -c stlinkv2 -p stm8s103f3 -s eeprom -r UID.bin

uid=$(od -N12 -An -t x1 < UID.bin)

uid0=${uid:1:1}
uid1=${uid:2:1}
uid2=${uid:4:1}
uid3=${uid:5:1}
uid4=${uid:7:1}
uid5=${uid:8:1}
uid6=${uid:10:1}
uid7=${uid:11:1}
uid8=${uid:13:1}
uid9=${uid:14:1}
uid10=${uid:16:1}
uid11=${uid:17:1}
uid12=${uid:19:1}
uid13=${uid:20:1}
uid14=${uid:22:1}
uid15=${uid:23:1}
uid16=${uid:25:1}
uid17=${uid:26:1}
uid18=${uid:28:1}
uid19=${uid:29:1}
uid20=${uid:31:1}
uid21=${uid:32:1}
uid22=${uid:34:1}
uid23=${uid:35:1}

cp 01_Led_delay_UID.c 02_Led_delay_UID.c

sed -i "s/U_ID1 != 0x00/U_ID1 != 0x$uid0$uid1/g" 02_Led_delay_UID.c
sed -i "s/U_ID2 != 0x00/U_ID2 != 0x$uid2$uid3/g" 02_Led_delay_UID.c
sed -i "s/U_ID3 != 0x00/U_ID3 != 0x$uid4$uid5/g" 02_Led_delay_UID.c
sed -i "s/U_ID4 != 0x00/U_ID4 != 0x$uid6$uid7/g" 02_Led_delay_UID.c
sed -i "s/U_ID5 != 0x00/U_ID5 != 0x$uid8$uid9/g" 02_Led_delay_UID.c
sed -i "s/U_ID6 != 0x00/U_ID6 != 0x$uid10$uid11/g" 02_Led_delay_UID.c
sed -i "s/U_ID7 != 0x00/U_ID7 != 0x$uid12$uid13/g" 02_Led_delay_UID.c
sed -i "s/U_ID8 != 0x00/U_ID8 != 0x$uid14$uid15/g" 02_Led_delay_UID.c
sed -i "s/U_ID9 != 0x00/U_ID9 != 0x$uid16$uid17/g" 02_Led_delay_UID.c
sed -i "s/U_ID10 != 0x00/U_ID10 != 0x$uid18$uid19/g" 02_Led_delay_UID.c
sed -i "s/U_ID11 != 0x00/U_ID11 != 0x$uid20$uid21/g" 02_Led_delay_UID.c
sed -i "s/U_ID12 != 0x00/U_ID12 != 0x$uid22$uid23/g" 02_Led_delay_UID.c

sdcc -mstm8 --std-c99 02_Led_delay_UID.c

stm8flash -c stlinkv2 -p stm8s003f3 -w 02_Led_delay_UID.ihx

  # lock
#echo "AA" | xxd -r -p >ROP_ON.bin
#stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w ROP_ON.bin


