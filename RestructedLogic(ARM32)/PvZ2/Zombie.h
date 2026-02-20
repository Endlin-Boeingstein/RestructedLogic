#pragma once
#include "BoardEntity.h"
#include "ZombiePropertySheet.h"
#include "EntityConditions.h"
#include "Plant.h"
#include "ZombieType.h"

#define ZOMBIE_VFUNC_COUNT 204

//寻找该偏移方法：
//由于Zombie这个字符串遍布so，所以非常之刻要用非常之法
//HEX搜索16进制数值003F3F5A6F6D62696500，选中作为通配符，通配符填入3F
//然后比如你跳转到了诸如"15PlantfoodCursor...............6Zombie........."字样时候
//把鼠标单击Zombie的"Z"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01BA3260; `typeinfo name for'Zombie
//.rodata:01BA3260 36 5A 6F 6D 62 69 65 00       _ZTS6Zombie DCB "6Zombie", 0; DATA XREF : .data.rel.ro : 01CAE704↓o
//.rodata : 01BA3260; type descriptor name

//双击示例中DATA XREF: .data.rel.ro:01CAE704↓o位置
//跳转到该类虚表，具体如下：
//.data.rel.ro:01CAE3B0; `vtable for'Zombie
//.data.rel.ro:01CAE3B0 00 00 00 00                   _ZTV6Zombie DCD 0; DATA XREF : sub_8A2834 + 28↑o
//.data.rel.ro : 01CAE3B0; sub_8A2834 + 2C↑o
//.data.rel.ro:01CAE3B0;.text:off_8A2C64↑o
//.data.rel.ro : 01CAE3B0; sub_8A2D98 + 14↑o
//.data.rel.ro:01CAE3B0; sub_8A2D98 + 24↑o
//.data.rel.ro:01CAE3B0;.text:off_8A304C↑o
//.data.rel.ro : 01CAE3B0; offset to this
//.data.rel.ro:01CAE3B4 00 E7 CA 01                   DCD _ZTI6Zombie; `typeinfo for'Zombie
//.data.rel.ro:01CAE3B8 80 E2 89 00                   off_1CAE3B8 DCD sub_89E280
//.data.rel.ro : 01CAE3BC A8 F7 89 00                   DCD sub_89F7A8
//.data.rel.ro : 01CAE3C0 98 2D 8A 00                   DCD sub_8A2D98
//.data.rel.ro : 01CAE3C4 64 30 8A 00                   DCD sub_8A3064
//.data.rel.ro : 01CAE3C8 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01CAE3CC 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01CAE3D0 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01CAE3D4 50 3F 8A 00                   DCD sub_8A3F50
//.data.rel.ro : 01CAE3D8 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01CAE3DC 5C 49 8A 00                   DCD sub_8A495C
//.data.rel.ro : 01CAE3E0 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01CAE3E4 24 3B 8A 00                   DCD sub_8A3B24
//.data.rel.ro : 01CAE3E8 30 7B 8A 00                   DCD sub_8A7B30
//.data.rel.ro : 01CAE3EC EC 9D 2C 00                   DCD sub_2C9DEC
//.data.rel.ro : 01CAE3F0 F4 B4 CE 00                   DCD sub_CEB4F4
//.data.rel.ro : 01CAE3F4 DC 9C 2C 00                   DCD sub_2C9CDC
//.data.rel.ro : 01CAE3F8 E8 5F 8B 00                   DCD sub_8B5FE8
//.data.rel.ro : 01CAE3FC DC 9B 2C 00                   DCD sub_2C9BDC
//.data.rel.ro : 01CAE400 E8 5E 8B 00                   DCD sub_8B5EE8
//.data.rel.ro : 01CAE404 50 BA CE 00                   DCD sub_CEBA50
//.data.rel.ro : 01CAE408 A0 3E 8B 00                   DCD sub_8B3EA0
//.data.rel.ro : 01CAE40C 70 3A 8B 00                   DCD sub_8B3A70
//.data.rel.ro : 01CAE410 CC 22 25 00                   DCD sub_2522CC
//.data.rel.ro : 01CAE414 D4 22 25 00                   DCD sub_2522D4
//.data.rel.ro : 01CAE418 40 85 8A 00                   DCD sub_8A8540
//.data.rel.ro : 01CAE41C F0 22 25 00                   DCD nullsub_417
//.data.rel.ro : 01CAE420 F4 22 25 00                   DCD nullsub_418
//.data.rel.ro : 01CAE424 70 46 8B 00                   DCD sub_8B4670
//.data.rel.ro : 01CAE428 98 60 8B 00                   DCD sub_8B6098
//.data.rel.ro : 01CAE42C E8 4C 8A 00                   DCD sub_8A4CE8
//.data.rel.ro : 01CAE430 94 B6 CE 00                   DCD sub_CEB694
//.data.rel.ro : 01CAE434 7C DA 8B 00                   DCD sub_8BDA7C
//.data.rel.ro : 01CAE438 5C B9 CE 00                   DCD sub_CEB95C
//.data.rel.ro : 01CAE43C 54 F9 8A 00                   DCD sub_8AF954
//.data.rel.ro : 01CAE440 FC 2C 8B 00                   DCD sub_8B2CFC
//.data.rel.ro : 01CAE444 50 A8 8A 00                   DCD sub_8AA850
//.data.rel.ro : 01CAE448 54 CD 8A 00                   DCD sub_8ACD54
//.data.rel.ro : 01CAE44C 08 23 25 00                   DCD sub_252308
//.data.rel.ro:01CAE450 B4 D6 8A 00                   DCD sub_8AD6B4
//.data.rel.ro : 01CAE454 10 23 25 00                   DCD nullsub_424
//.data.rel.ro : 01CAE458 14 23 25 00                   DCD sub_252314
//.data.rel.ro : 01CAE45C 1C 23 25 00                   DCD sub_25231C
//.data.rel.ro : 01CAE460 24 23 25 00                   DCD sub_252324
//.data.rel.ro : 01CAE464 F8 A4 2C 00                   DCD sub_2CA4F8
//.data.rel.ro : 01CAE468 7C 3D 8B 00                   DCD sub_8B3D7C
//.data.rel.ro : 01CAE46C F0 A2 2C 00                   DCD sub_2CA2F0
//.data.rel.ro : 01CAE470 B8 99 86 00                   DCD sub_8699B8
//.data.rel.ro : 01CAE474 34 23 25 00                   DCD sub_252334
//.data.rel.ro : 01CAE478 C0 99 86 00                   DCD sub_8699C0
//.data.rel.ro : 01CAE47C 60 49 8A 00                   DCD sub_8A4960
//.data.rel.ro : 01CAE480 BC 7F 8A 00                   DCD sub_8A7FBC
//.data.rel.ro : 01CAE484 84 9A 86 00                   DCD sub_869A84
//.data.rel.ro : 01CAE488 8C 9A 86 00                   DCD sub_869A8C
//.data.rel.ro : 01CAE48C 94 82 8A 00                   DCD sub_8A8294
//.data.rel.ro : 01CAE490 24 84 8A 00                   DCD sub_8A8424
//.data.rel.ro : 01CAE494 08 C2 8A 00                   DCD sub_8AC208
//.data.rel.ro:01CAE498 94 9A 86 00                   DCD nullsub_703
//.data.rel.ro : 01CAE49C EC 2F 8B 00                   DCD sub_8B2FEC
//.data.rel.ro : 01CAE4A0 98 9A 86 00                   DCD nullsub_704
//.data.rel.ro : 01CAE4A4 5C 31 8B 00                   DCD sub_8B315C
//.data.rel.ro : 01CAE4A8 28 2D 8B 00                   DCD sub_8B2D28
//.data.rel.ro : 01CAE4AC F4 8E 8A 00                   DCD sub_8A8EF4
//.data.rel.ro : 01CAE4B0 00 8F 8A 00                   DCD sub_8A8F00
//.data.rel.ro : 01CAE4B4 0C 8F 8A 00                   DCD sub_8A8F0C
//.data.rel.ro : 01CAE4B8 9C 9A 86 00                   DCD nullsub_705
//.data.rel.ro : 01CAE4BC A0 9A 86 00                   DCD nullsub_706
//.data.rel.ro : 01CAE4C0 A4 9A 86 00                   DCD sub_869AA4
//.data.rel.ro : 01CAE4C4 B8 9A 86 00                   DCD nullsub_707
//.data.rel.ro : 01CAE4C8 48 F8 8A 00                   DCD sub_8AF848
//.data.rel.ro : 01CAE4CC BC 9A 86 00                   DCD sub_869ABC
//.data.rel.ro : 01CAE4D0 00 21 7B 00                   DCD sub_7B2100
//.data.rel.ro : 01CAE4D4 D0 96 78 00                   DCD nullsub_708
//.data.rel.ro : 01CAE4D8 5C 76 7C 00                   DCD nullsub_709
//.data.rel.ro : 01CAE4DC E0 BE 8B 00                   DCD sub_8BBEE0
//.data.rel.ro : 01CAE4E0 70 E3 8A 00                   DCD sub_8AE370
//.data.rel.ro : 01CAE4E4 48 F3 8A 00                   DCD sub_8AF348
//.data.rel.ro : 01CAE4E8 D0 33 8B 00                   DCD sub_8B33D0
//.data.rel.ro : 01CAE4EC E4 33 8B 00                   DCD sub_8B33E4
//.data.rel.ro : 01CAE4F0 CC 9A 86 00                   DCD sub_869ACC
//.data.rel.ro : 01CAE4F4 D4 9A 86 00                   DCD nullsub_710
//.data.rel.ro : 01CAE4F8 D8 9A 86 00                   DCD nullsub_711
//.data.rel.ro : 01CAE4FC 5C EF 8A 00                   DCD sub_8AEF5C
//.data.rel.ro : 01CAE500 A4 EF 8A 00                   DCD sub_8AEFA4
//.data.rel.ro : 01CAE504 DC 9A 86 00                   DCD sub_869ADC
//.data.rel.ro : 01CAE508 E4 9A 86 00                   DCD sub_869AE4
//.data.rel.ro : 01CAE50C 90 CF 8B 00                   DCD sub_8BCF90
//.data.rel.ro : 01CAE510 B8 CF 8B 00                   DCD sub_8BCFB8
//.data.rel.ro : 01CAE514 44 40 8B 00                   DCD sub_8B4044
//.data.rel.ro : 01CAE518 38 44 8B 00                   DCD sub_8B4438
//.data.rel.ro : 01CAE51C A8 45 8B 00                   DCD sub_8B45A8
//.data.rel.ro : 01CAE520 10 3C 8B 00                   DCD sub_8B3C10
//.data.rel.ro : 01CAE524 EC 8E 8A 00                   DCD sub_8A8EEC
//.data.rel.ro : 01CAE528 D8 EF 8A 00                   DCD sub_8AEFD8
//.data.rel.ro : 01CAE52C C0 D2 8B 00                   DCD sub_8BD2C0
//.data.rel.ro : 01CAE530 04 D3 8B 00                   DCD sub_8BD304
//.data.rel.ro : 01CAE534 24 7A 86 00                   DCD sub_867A24
//.data.rel.ro : 01CAE538 54 D4 8B 00                   DCD sub_8BD454
//.data.rel.ro : 01CAE53C A0 37 8B 00                   DCD sub_8B37A0
//.data.rel.ro : 01CAE540 B0 3B 8B 00                   DCD sub_8B3BB0
//.data.rel.ro : 01CAE544 EC 9A 86 00                   DCD sub_869AEC
//.data.rel.ro : 01CAE548 F4 9A 86 00                   DCD sub_869AF4
//.data.rel.ro : 01CAE54C FC 9A 86 00                   DCD sub_869AFC
//.data.rel.ro : 01CAE550 04 9B 86 00                   DCD sub_869B04
//.data.rel.ro : 01CAE554 38 86 8A 00                   DCD sub_8A8638
//.data.rel.ro : 01CAE558 0C 9B 86 00                   DCD sub_869B0C
//.data.rel.ro : 01CAE55C 14 9B 86 00                   DCD sub_869B14
//.data.rel.ro : 01CAE560 04 9C 86 00                   DCD sub_869C04
//.data.rel.ro : 01CAE564 9C DB 8B 00                   DCD sub_8BDB9C
//.data.rel.ro : 01CAE568 C4 8A 8A 00                   DCD sub_8A8AC4
//.data.rel.ro : 01CAE56C 0C 9C 86 00                   DCD sub_869C0C
//.data.rel.ro : 01CAE570 14 9C 86 00                   DCD sub_869C14
//.data.rel.ro : 01CAE574 1C 9C 86 00                   DCD nullsub_712
//.data.rel.ro : 01CAE578 20 9C 86 00                   DCD nullsub_713
//.data.rel.ro : 01CAE57C 24 9C 86 00                   DCD nullsub_714
//.data.rel.ro : 01CAE580 28 9C 86 00                   DCD sub_869C28
//.data.rel.ro : 01CAE584 F8 E5 85 00                   DCD nullsub_715
//.data.rel.ro : 01CAE588 3C 9C 86 00                   DCD sub_869C3C
//.data.rel.ro : 01CAE58C 44 9C 86 00                   DCD sub_869C44
//.data.rel.ro : 01CAE590 80 6C 73 00                   DCD sub_736C80
//.data.rel.ro : 01CAE594 4C 9C 86 00                   DCD sub_869C4C
//.data.rel.ro : 01CAE598 90 68 8B 00                   DCD sub_8B6890
//.data.rel.ro : 01CAE59C 3C 6C 8B 00                   DCD sub_8B6C3C
//.data.rel.ro : 01CAE5A0 88 6C 8B 00                   DCD nullsub_716
//.data.rel.ro : 01CAE5A4 8C 6C 8B 00                   DCD sub_8B6C8C
//.data.rel.ro : 01CAE5A8 48 70 8B 00                   DCD sub_8B7048
//.data.rel.ro : 01CAE5AC A4 70 8B 00                   DCD sub_8B70A4
//.data.rel.ro : 01CAE5B0 B4 70 8B 00                   DCD sub_8B70B4
//.data.rel.ro : 01CAE5B4 D4 71 8B 00                   DCD sub_8B71D4
//.data.rel.ro : 01CAE5B8 E8 7F 8B 00                   DCD nullsub_718
//.data.rel.ro : 01CAE5BC EC 7F 8B 00                   DCD sub_8B7FEC
//.data.rel.ro : 01CAE5C0 24 82 8B 00                   DCD sub_8B8224
//.data.rel.ro : 01CAE5C4 58 82 8B 00                   DCD sub_8B8258
//.data.rel.ro : 01CAE5C8 68 82 8B 00                   DCD sub_8B8268
//.data.rel.ro : 01CAE5CC E8 84 8B 00                   DCD sub_8B84E8
//.data.rel.ro : 01CAE5D0 40 86 8B 00                   DCD nullsub_719
//.data.rel.ro : 01CAE5D4 44 86 8B 00                   DCD sub_8B8644
//.data.rel.ro : 01CAE5D8 8C 8D 8B 00                   DCD sub_8B8D8C
//.data.rel.ro : 01CAE5DC 6C 8E 8B 00                   DCD nullsub_720
//.data.rel.ro : 01CAE5E0 70 8E 8B 00                   DCD sub_8B8E70
//.data.rel.ro : 01CAE5E4 98 92 8B 00                   DCD sub_8B9298
//.data.rel.ro : 01CAE5E8 68 93 8B 00                   DCD nullsub_721
//.data.rel.ro : 01CAE5EC 6C 93 8B 00                   DCD sub_8B936C
//.data.rel.ro : 01CAE5F0 C4 94 8B 00                   DCD sub_8B94C4
//.data.rel.ro : 01CAE5F4 44 95 8B 00                   DCD nullsub_722
//.data.rel.ro : 01CAE5F8 40 99 8B 00                   DCD sub_8B9940
//.data.rel.ro : 01CAE5FC B8 9A 8B 00                   DCD sub_8B9AB8
//.data.rel.ro : 01CAE600 48 9F 8B 00                   DCD nullsub_723
//.data.rel.ro : 01CAE604 04 CC 8B 00                   DCD sub_8BCC04
//.data.rel.ro : 01CAE608 24 CD 8B 00                   DCD sub_8BCD24
//.data.rel.ro : 01CAE60C 8C CF 8B 00                   DCD nullsub_724
//.data.rel.ro : 01CAE610 4C 9F 8B 00                   DCD sub_8B9F4C
//.data.rel.ro : 01CAE614 3C A0 8B 00                   DCD sub_8BA03C
//.data.rel.ro : 01CAE618 50 A5 8B 00                   DCD nullsub_726
//.data.rel.ro : 01CAE61C 54 A5 8B 00                   DCD sub_8BA554
//.data.rel.ro : 01CAE620 A0 A5 8B 00                   DCD nullsub_727
//.data.rel.ro : 01CAE624 A4 A5 8B 00                   DCD nullsub_728
//.data.rel.ro : 01CAE628 D0 AF 8B 00                   DCD sub_8BAFD0
//.data.rel.ro : 01CAE62C EC B1 8B 00                   DCD sub_8BB1EC
//.data.rel.ro : 01CAE630 FC B2 8B 00                   DCD sub_8BB2FC
//.data.rel.ro : 01CAE634 A8 A5 8B 00                   DCD sub_8BA5A8
//.data.rel.ro : 01CAE638 BC AE 8B 00                   DCD sub_8BAEBC
//.data.rel.ro : 01CAE63C B4 AF 8B 00                   DCD sub_8BAFB4
//.data.rel.ro : 01CAE640 30 B3 8B 00                   DCD sub_8BB330
//.data.rel.ro : 01CAE644 BC BD 8B 00                   DCD sub_8BBDBC
//.data.rel.ro : 01CAE648 40 C0 8B 00                   DCD sub_8BC040
//.data.rel.ro : 01CAE64C A8 CA 8B 00                   DCD sub_8BCAA8
//.data.rel.ro : 01CAE650 A0 CB 8B 00                   DCD sub_8BCBA0
//.data.rel.ro : 01CAE654 DC CB 8B 00                   DCD sub_8BCBDC
//.data.rel.ro : 01CAE658 08 4C 8A 00                   DCD sub_8A4C08
//.data.rel.ro:01CAE65C F8 8F 73 00                   DCD nullsub_764
//.data.rel.ro : 01CAE660 F4 64 8B 00                   DCD nullsub_729
//.data.rel.ro : 01CAE664 B8 85 7B 00                   DCD nullsub_730
//.data.rel.ro : 01CAE668 F0 88 8B 00                   DCD sub_8B88F0
//.data.rel.ro : 01CAE66C 74 90 8B 00                   DCD sub_8B9074
//.data.rel.ro : 01CAE670 64 9C 86 00                   DCD nullsub_733
//.data.rel.ro : 01CAE674 68 9C 86 00                   DCD nullsub_734
//.data.rel.ro : 01CAE678 C0 94 8B 00                   DCD nullsub_735
//.data.rel.ro : 01CAE67C 6C 9C 86 00                   DCD nullsub_736
//.data.rel.ro : 01CAE680 70 9C 86 00                   DCD nullsub_737
//.data.rel.ro : 01CAE684 E0 E2 8A 00                   DCD sub_8AE2E0
//.data.rel.ro : 01CAE688 94 5A 8A 00                   DCD sub_8A5A94
//.data.rel.ro : 01CAE68C 98 31 8B 00                   DCD sub_8B3198
//.data.rel.ro : 01CAE690 A0 7F 8A 00                   DCD sub_8A7FA0
//.data.rel.ro : 01CAE694 74 9C 86 00                   DCD nullsub_738
//.data.rel.ro : 01CAE698 2C 97 7D 00                   DCD nullsub_739
//.data.rel.ro : 01CAE69C 48 C3 75 00                   DCD nullsub_740
//.data.rel.ro : 01CAE6A0 50 31 74 00                   DCD nullsub_741
//.data.rel.ro : 01CAE6A4 B4 7F 8A 00                   DCD sub_8A7FB4
//.data.rel.ro : 01CAE6A8 64 CE 8A 00                   DCD sub_8ACE64
//.data.rel.ro : 01CAE6AC F8 8C 82 00                   DCD sub_828CF8
//.data.rel.ro : 01CAE6B0 F4 8D 82 00                   DCD sub_828DF4
//.data.rel.ro : 01CAE6B4 78 9C 86 00                   DCD sub_869C78
//.data.rel.ro : 01CAE6B8 80 9C 86 00                   DCD sub_869C80
//.data.rel.ro : 01CAE6BC 88 9C 86 00                   DCD sub_869C88
//.data.rel.ro : 01CAE6C0 B4 80 8A 00                   DCD sub_8A80B4
//.data.rel.ro : 01CAE6C4 A4 81 8A 00                   DCD sub_8A81A4
//.data.rel.ro : 01CAE6C8 8C 77 8B 00                   DCD sub_8B778C
//.data.rel.ro : 01CAE6CC 30 83 8B 00                   DCD sub_8B8330
//.data.rel.ro : 01CAE6D0 D0 9D 8A 00                   DCD sub_8A9DD0
//.data.rel.ro : 01CAE6D4 94 9C 86 00                   DCD sub_869C94
//.data.rel.ro : 01CAE6D8 9C 9C 86 00                   DCD sub_869C9C
//.data.rel.ro : 01CAE6DC A0 70 8B 00                   DCD sub_8B70A0
//.data.rel.ro : 01CAE6E0 38 6C 8B 00                   DCD sub_8B6C38
//.data.rel.ro : 01CAE6E4 50 79 8B 00                   DCD sub_8B7950
//.data.rel.ro : 01CAE6E8 F0 FF FF FF                   DCD - 16; offset to this
//.data.rel.ro:01CAE6EC 00 E7 CA 01                   DCD _ZTI6Zombie; `typeinfo for'Zombie
//.data.rel.ro:01CAE6F0 5C 30 8A 00                   off_1CAE6F0 DCD sub_8A305C
//.data.rel.ro : 01CAE6F4 78 30 8A 00                   DCD sub_8A3078
//.data.rel.ro : 01CAE6F8 D0 9D 2C 00                   DCD sub_2C9DD0
//.data.rel.ro : 01CAE6FC 98 3E 8B 00                   DCD sub_8B3E98
//.data.rel.ro : 01CAE700; public Zombie :
//.data.rel.ro : 01CAE700;   public /* offset 0x0 */ BoardEntity :
//.data.rel.ro : 01CAE700;     public /* offset 0x0 */ ModularRealObject :
//.data.rel.ro : 01CAE700;       public /* offset 0x0 */ RealObject :
//.data.rel.ro : 01CAE700;         public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01CAE700;           public /* offset 0x0 */ Sexy::RtObject,
//.data.rel.ro:01CAE700;         public /* offset 0x10 */ Renderable
//.data.rel.ro:01CAE700; `typeinfo for'Zombie
//.data.rel.ro:01CAE700 D8 74 DF 01                   _ZTI6Zombie DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01CAE700; DATA XREF : .data.rel.ro : 01C8C470↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8C860↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8CFBC↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8D108↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8DC48↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8E350↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8ECE0↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8F4F4↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8FBB4↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C8FF10↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C90424↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C90A74↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C90E54↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C92A90↑o
//.data.rel.ro : 01CAE700;.data.rel.ro:01C935E4↑o ...
//.data.rel.ro : 01CAE700; reference to RTTI's type class
//.data.rel.ro:01CAE704 60 32 BA 01                   DCD _ZTS6Zombie; reference to type's name
//.data.rel.ro:01CAE708 58 04 C6 01                   DCD _ZTI11BoardEntity; reference to parent's type name

//看右上角的偏移引用
//其中DATA XREF: sub_8A2834+28↑o或sub_8A2834+2C↑o的sub_8A2834为ZOMBIE_CTOR_ADDR
#define ZOMBIE_CTOR_ADDR Zombie_ZOMBIE_CTOR_ADDRAddr
//其中sub_8A2D98+14↑o或sub_8A2D98+24↑o的sub_8A2D98为ZOMBIE_DTOR_ADDR
#define ZOMBIE_DTOR_ADDR Zombie_ZOMBIE_DTOR_ADDRAddr
//接下来
//.data.rel.ro:01CAE3B4 00 E7 CA 01                   DCD _ZTI6Zombie; `typeinfo for'Zombie
//.data.rel.ro:01CAE3B8 80 E2 89 00                   off_1CAE3B8 DCD sub_89E280

//其中.data.rel.ro:01CAE3B8的01CAE3B8为ZOMBIE_VFTABLE_ADDR
#define ZOMBIE_VFTABLE_ADDR Zombie_ZOMBIE_VFTABLE_ADDRAddr
//双击示例中sub_89E280
//跳转后如下：
//.text:0089E280
//.text : 0089E280; ============== = S U B R O U T I N E ====================================== =
//.text:0089E280
//.text : 0089E280; Attributes: thunk
//.text : 0089E280
//.text : 0089E280                               sub_89E280; DATA XREF : .data.rel.ro : off_1CAE3B8↓o
//.text : 0089E280; __unwind{
//.text:0089E280 E1 FF FF EA                   B               sub_89E20C
//.text : 0089E280; } // starts at 89E280
//.text:0089E280
//.text : 0089E280; End of function sub_89E280
//.text:0089E280
//.text : 0089E284

//其中sub_89E20C为OFFSET_ZOMBIE_GETTYPE和ZOMBIE_GET_RTCLASS
#define OFFSET_ZOMBIE_GETTYPE Zombie_OFFSET_ZOMBIE_GETTYPEAddr
#define ZOMBIE_GET_RTCLASS Zombie_ZOMBIE_GET_RTCLASSAddr // they are basically the same??


#define ZOMBIE_ISDEADORDYING_ADDR Zombie_ZOMBIE_ISDEADORDYING_ADDRAddr





class Zombie : public BoardEntity
{
public:
	int m_helm;
	float m_helmHitpoints;
	char pad_006C[12];
	Sexy::RtWeakPtr<ZombieType> m_type;
	Sexy::RtWeakPtr<void> m_animRig;
	char pad_0088[88];
	double m_elapsedTimeInState;
	float m_stateMachineTimeScale;
	int32_t m_playingAnim;
	int32_t m_zombieFlags;
	int32_t m_facing;
	float m_hitpoints;
	float m_maxHitpoints;
	bool m_isTimeToKillActive;
	char pad_0101[3];
	float m_timeToKill;
	float m_speedScale;
	float m_dpsScale;
	float m_damageScale;
	float m_shrunkenDamageScale;
	float m_walkSpeed;
	float m_translationMultiplier;
	float m_maxHelmHitpoints;
	int32_t m_spawnedFromWave;
	float m_nextChewSoundTime;
	float m_mowedStartTime;
	float m_flickedStartTime;
	struct Sexy::SexyVector3 m_flickOffStartPosition;
	struct Sexy::SexyVector3 m_flickOffTarget;
	float m_flickOffTimeToTarget;
	float m_flickOffFinalRotation;
	float m_rotation;
	float m_scale;
	int32_t m_zombieRenderLayerOffset;
	Sexy::RtWeakPtr<void> m_ownerPlant;
	Sexy::RtWeakPtr<void> m_forcedTarget;
	char pad_0170[24];
	struct Sexy::SexyVector2 m_stormTargetLocation;
	int32_t m_stormType;
	std::vector<Sexy::RtWeakPtr<void>> m_armor;
	EntityConditionTracker m_conditionTracker;
	int trackerPad[21];
	char pad_0210[190];
	std::vector<int> m_familyResistances;
	std::vector<int> m_targetHistory;
	int32_t m_loot;
	char pad_02EC[16];
	bool m_isBeingDestroyed;
	bool m_wasMowedDown;
	Sexy::RtWeakPtr<ZombiePropertySheet> m_propertySheet;

	~Zombie() {
		typedef Zombie* (*zombieDtor)(Zombie*);
		((zombieDtor)getActualOffset(ZOMBIE_DTOR_ADDR))(this);
	}

	bool IsDeadOrDying() {
		typedef bool (*isDeadOrDying)(Zombie*);
		return ((isDeadOrDying)getActualOffset(ZOMBIE_ISDEADORDYING_ADDR))(this);
	}

	DEFINE_RT_CLASS_GET_CLASS_WRAPPER(OFFSET_ZOMBIE_GETTYPE);

	virtual Sexy::FPoint GetShadowScaling() {}
	virtual void Function51() {}
	virtual void Function52() {}
	virtual int UpdateHelmDegrades() {}
	virtual int GetTotalHitpoints() {}
	virtual void Function55() {}
	virtual void Function56() {}
	virtual void SpawnFromGround() {}
	virtual void Function58() {}
	virtual void RiseFromPod() {}
	virtual void SetFlagType() {} // for flag zombies
	virtual void EnterIdle() {}
	virtual void EnterWalk() {}
	virtual void EnterGrabbed() {}
	virtual void ActivateJam() {}
	virtual void DeactivateJam() {}
	virtual void Function66() {}
	virtual void Function67() {}
	virtual int ApplyStun(float duration, PlantFramework* instigator) {}
	virtual int ApplyStunWithoutInstigator(float duration) {}
	virtual bool IsStunned() {}
	virtual void Function71() {}
	virtual void Function72() {}
	virtual void Function73() {}
	virtual void Die(int unk) {}
	virtual void ThreatAlert() {} // runs when zombie is close to house
	virtual void Function76() {}
	virtual void Function77() {}
	virtual void Function78() {}
	virtual void Function79() {}
	virtual void Function80() {}
	virtual bool HasArmDrop() {}
	virtual void Function82() {}
	virtual void Function83() {}
	virtual void Function84() {}
	virtual void Function85() {}
	virtual void Function86() {}
	virtual void Function87(Sexy::Graphics* g) {}
	virtual void Function88() {}
	virtual void Function89() {}
	virtual void Function90() {}
	virtual void Function91() {}
	virtual void Function92() {}
	virtual void Function93() {}
	virtual void Function94() {}
	virtual void Function95() {}
	virtual void Function96() {}
	virtual void Function97() {}
	virtual void Function98() {}
	virtual void Function99() {}
	virtual void Function100() {}
	virtual void Function101() {}
	virtual void Function102() {}
	virtual void Function103() {}
	virtual void Function104() {}
	virtual void Function105() {}
	virtual void Function106() {}
	virtual int GetTideEffect() {}
	virtual void* FindAttackTarget() {}
	virtual void Function109() {}
	virtual void Function110() {}
	virtual void Function111() {}
	virtual void Function112() {}
	virtual void Function113() {}
	virtual void Function114() {}
	virtual void Function115() {}
	virtual void Function116() {}
	virtual void Function117() {}
	virtual float GetWalkSpeed() {}
	virtual void Function119() {}
	virtual void IdleOnEnter(int unk) {} // weird argument
	virtual void IdleOnLoop() {}
	virtual void IdleOnExit() {}
	virtual void WalkOnEnter() {}
	virtual void WalkOnLoop() {}
	virtual void WalkOnExit() {}
	virtual void EatOnEnter() {}
	virtual void EatOnLoop() {}
	virtual void EatOnExit() {}
	virtual void BleedingOutOnEnter() {}
	virtual void BleedingOutOnLoop() {}
	virtual void BleedingOutOnExit() {}
	virtual void DieOnEnter() {}
	virtual void DieOnLoop() {}
	virtual void DieOnExit() {}
	virtual void ElectrocuteOnEnter() {}
	virtual void ElectrocuteOnLoop() {}
	virtual void ElectrocuteOnExit() {}
	virtual void AshOnEnter() {}
	virtual void AshOnLoop() {}
	virtual void AshOnExit() {}
	virtual void MowedDownOnEnter() {}
	virtual void MowedDownOnLoop() {}
	virtual void MowedDownOnExit() {}
	virtual void FlickedOffOnEnter() {}
	virtual void FlickedOffOnLoop() {}
	virtual void FlickedOffOnExit() {}
	virtual void WinningOnEnter() {}
	virtual void WinningOnLoop() {}
	virtual void WinningOnExit() {}
	virtual void PlantifyOnEnter() {}
	virtual void PlantifyOnLoop() {}
	virtual void PlantifyOnExit() {}
	virtual void GrabbedOnEnter() {}
	virtual void GrabbedOnLoop() {}
	virtual void GrabbedOnExit() {}
	virtual void RiseFromGroundOnEnter() {}
	virtual void RiseFromGroundOnLoop() {}
	virtual void RiseFromGroundOnExit() {}
	virtual void RiseFromStormOnEnter() {}
	virtual void RiseFromStormOnLoop() {}
	virtual void RiseFromStormOnExit() {}
	virtual void StormEntranceOnEnter() {}
	virtual void StormEntranceOnLoop() {}
	virtual void StormEntranceOnExit() {}
	virtual void RiseFromPodOnEnter() {}
	virtual void RiseFromPodOnLoop() {}
	virtual void RiseFromPodOnExit() {}
	virtual void Function168() {}
	virtual void Function169() {}
	virtual void OnActionCommand(Sexy::SexyString* currentAnim, int unk1, Sexy::SexyString* actionName, int unk2) {}
	virtual void Function171() {}
	virtual void Electrocute() {}
	virtual void Ash() {}
	virtual void Function174() {}
	virtual void Function175() {}
	virtual void Function176() {}
	virtual void Function177() {}
	virtual void Function178() {}
	virtual void Function179() {}
	virtual void KillWithFatalDamage() {}
	virtual void Function181() {}
	virtual void Function182() {}
	virtual void Function183() {}
	virtual void Function184() {}
	virtual void Function185() {}
	virtual void Function186() {}
	virtual void Function187() {}
	virtual void Function188() {}
	virtual Sexy::SexyString GetElectrocuteEffectName() {}
	virtual Sexy::SexyString GetAshEffectName() {}
	virtual void Function191() {}
	virtual void Function192() {}
	virtual void Function193() {}
	virtual float GetArmDropFraction() {}
	virtual void Function195() {}
	virtual DamageInfo GetAttackDamage() {}
	virtual void OnDeath() {}
	virtual Sexy::SexyVector3 Function198() {} // get some offset of the zombie's position
	virtual void Function199() {}
	virtual void Function200() {}
	virtual void PlaySoundOnWalk() {}
	virtual void PlaySoundOnIdle() {}
	virtual void PlaySoundOnEat() {}
};

static_assert(offsetof(Zombie, m_conditionTracker) == 0x1A0);
static_assert(offsetof(Zombie, pad_0210) == 0x210);