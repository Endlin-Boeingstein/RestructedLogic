#include "GridItemRaiserProjectileProps.h"
#include "../../PvZ2/GridItem.h"

void* GridItemRaiserProjectileProps::vftable = nullptr;
Sexy::RtClass* GridItemRaiserProjectileProps::s_rtClass = nullptr;

#pragma region hk SpawnGridItem Proj


void GridItemRaiserProjectileProps::modInit() {
    LOGI("GridItemRaiserProjectileProps init");
    //寻找该偏移方法：
    //由于Projectile这个字符串遍布so，所以非常之刻要用非常之法
    //HEX搜索16进制数值003F3F50726F6A656374696C6500，选中作为通配符，通配符填入3F
    //然后比如你跳转到了诸如"20EgyptStageProperties.10Projectile"字样时候
    //把鼠标单击Projectile的"P"上面，然后根据该偏移让ida pro跳转
    //这个时候，如下所示：
    /*.rodata:01BA44B7; `typeinfo name for'Projectile
        .rodata:01BA44B7 31 30 50 72 6F 6A 65 63 74 69 + _ZTS10Projectile DCB "10Projectile", 0; DATA XREF : .data.rel.ro : 01CB01C8↓o
        .rodata : 01BA44B7 6C 65 00; type descriptor name*/

    //双击示例中的DATA XREF: .data.rel.ro:01CB01C8↓o位置
    //跳转即为该类虚表，向上翻页，整体如下：
    //.data.rel.ro:01CB00D0; `vtable for'Projectile
    //    .data.rel.ro:01CB00D0 00 00 00 00                   _ZTV10Projectile DCD 0; DATA XREF : sub_907508 + 28↑o
    //    .data.rel.ro : 01CB00D0; sub_907508 + 30↑o
    //    .data.rel.ro:01CB00D0;.text:off_907718↑o
    //    .data.rel.ro : 01CB00D0; sub_90774C + 14↑o
    //    .data.rel.ro:01CB00D0; sub_90774C + 28↑o
    //    .data.rel.ro:01CB00D0;.text:off_907948↑o
    //    .data.rel.ro : 01CB00D0; offset to this
    //    .data.rel.ro:01CB00D4 C4 01 CB 01                   DCD _ZTI10Projectile; `typeinfo for'Projectile
    //    .data.rel.ro:01CB00D8 24 5A 90 00                   DCD sub_905A24
    //    .data.rel.ro : 01CB00DC 44 5B 90 00                   DCD sub_905B44
    //    .data.rel.ro : 01CB00E0 4C 77 90 00                   DCD sub_90774C
    //    .data.rel.ro : 01CB00E4 5C 79 90 00                   DCD sub_90795C
    //    .data.rel.ro : 01CB00E8 F0 01 25 01                   DCD sub_12501F0
    //    .data.rel.ro : 01CB00EC 1C 02 25 01                   DCD sub_125021C
    //    .data.rel.ro : 01CB00F0 20 F2 53 00                   DCD sub_53F220
    //    .data.rel.ro : 01CB00F4 84 3D 25 00                   DCD nullsub_339
    //    .data.rel.ro : 01CB00F8 88 3D 25 00                   DCD nullsub_340
    //    .data.rel.ro : 01CB00FC 8C 3D 25 00                   DCD nullsub_341
    //    .data.rel.ro : 01CB0100 B8 22 25 00                   DCD nullsub_342
    //    .data.rel.ro : 01CB0104 90 3D 25 00                   DCD nullsub_343
    //    .data.rel.ro : 01CB0108 9C 47 45 00                   DCD sub_45479C
    //    .data.rel.ro : 01CB010C 6C D6 29 00                   DCD sub_29D66C
    //    .data.rel.ro : 01CB0110 F4 B4 CE 00                   DCD sub_CEB4F4
    //    .data.rel.ro : 01CB0114 28 B6 CE 00                   DCD sub_CEB628
    //    .data.rel.ro : 01CB0118 10 BA 90 00                   DCD sub_90BA10
    //    .data.rel.ro : 01CB011C AC 8A 90 00                   DCD sub_908AAC
    //    .data.rel.ro : 01CB0120 54 B9 CE 00                   DCD sub_CEB954
    //    .data.rel.ro : 01CB0124 B4 D6 90 00                   DCD sub_90D6B4
    //    .data.rel.ro : 01CB0128 FC C7 90 00                   DCD sub_90C7FC
    //    .data.rel.ro : 01CB012C 44 D7 90 00                   DCD sub_90D744
    //    .data.rel.ro : 01CB0130 00 9A 90 00                   DCD sub_909A00
    //    .data.rel.ro : 01CB0134 7C D6 29 00                   DCD sub_29D67C
    //    .data.rel.ro : 01CB0138 E0 22 25 00                   DCD sub_2522E0
    //    .data.rel.ro : 01CB013C F0 22 25 00                   DCD nullsub_417
    //    .data.rel.ro : 01CB0140 F4 22 25 00                   DCD nullsub_418
    //    .data.rel.ro : 01CB0144 18 B3 90 00                   DCD sub_90B318
    //    .data.rel.ro : 01CB0148 38 BA 90 00                   DCD sub_90BA38
    //    .data.rel.ro : 01CB014C 00 4F 45 00                   DCD sub_454F00
    //    .data.rel.ro : 01CB0150 94 B6 CE 00                   DCD sub_CEB694
    //    .data.rel.ro : 01CB0154 38 BA CE 00                   DCD sub_CEBA38
    //    .data.rel.ro : 01CB0158 5C B9 CE 00                   DCD sub_CEB95C
    //    .data.rel.ro : 01CB015C 18 4C 45 00                   DCD nullsub_421
    //    .data.rel.ro : 01CB0160 0C 4F 45 00                   DCD sub_454F0C
    //    .data.rel.ro : 01CB0164 E0 9A 90 00                   DCD sub_909AE0
    //    .data.rel.ro : 01CB0168 C0 A3 90 00                   DCD sub_90A3C0
    //    .data.rel.ro : 01CB016C CC C6 90 00                   DCD sub_90C6CC
    //    .data.rel.ro : 01CB0170 84 D6 29 00                   DCD nullsub_800
    //    .data.rel.ro : 01CB0174 88 D6 29 00                   DCD nullsub_801
    //    .data.rel.ro : 01CB0178 5C 96 90 00                   DCD sub_90965C
    //    .data.rel.ro : 01CB017C 24 AC 90 00                   DCD sub_90AC24
    //    .data.rel.ro : 01CB0180 DC A4 90 00                   DCD sub_90A4DC
    //    .data.rel.ro : 01CB0184 94 D6 29 00                   DCD sub_29D694
    //    .data.rel.ro : 01CB0188 1C CC 90 00                   DCD sub_90CC1C
    //    .data.rel.ro : 01CB018C AC D6 90 00                   DCD sub_90D6AC
    //    .data.rel.ro : 01CB0190 70 9E 90 00                   DCD sub_909E70
    //    .data.rel.ro : 01CB0194 18 A0 90 00                   DCD sub_90A018
    //    .data.rel.ro : 01CB0198 9C D6 29 00                   DCD nullsub_802
    //    .data.rel.ro : 01CB019C A0 D6 29 00                   DCD nullsub_803
    //    .data.rel.ro : 01CB01A0 40 A1 90 00                   DCD sub_90A140
    //    .data.rel.ro : 01CB01A4 84 D5 90 00                   DCD sub_90D584
    //    .data.rel.ro : 01CB01A8 9C BD 90 00                   DCD sub_90BD9C
    //    .data.rel.ro : 01CB01AC F0 FF FF FF                   DCD - 16; offset to this
    //    .data.rel.ro:01CB01B0 C4 01 CB 01                   DCD _ZTI10Projectile; `typeinfo for'Projectile
    //    .data.rel.ro:01CB01B4 54 79 90 00                   DCD sub_907954
    //    .data.rel.ro : 01CB01B8 70 79 90 00                   DCD sub_907970
    //    .data.rel.ro : 01CB01BC 34 B6 CE 00                   DCD sub_CEB634
    //    .data.rel.ro : 01CB01C0 C4 D6 29 00                   DCD sub_29D6C4
    //    .data.rel.ro : 01CB01C4; public Projectile :
    //.data.rel.ro : 01CB01C4;   public /* offset 0x0 */ ModularRealObject :
    //.data.rel.ro : 01CB01C4;     public /* offset 0x0 */ RealObject :
    //.data.rel.ro : 01CB01C4;       public /* offset 0x0 */ GameObject :
    //.data.rel.ro : 01CB01C4;         public /* offset 0x0 */ Sexy::RtObject,
    //    .data.rel.ro:01CB01C4;       public /* offset 0x10 */ Renderable
    //    .data.rel.ro:01CB01C4; `typeinfo for'Projectile
    //    .data.rel.ro:01CB01C4 D8 74 DF 01                   _ZTI10Projectile DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
    //    .data.rel.ro : 01CB01C4; DATA XREF : .data.rel.ro : 01C5EDDC↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C64810↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C6F158↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C6F870↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C7BFA8↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C8CFB0↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C94E60↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C963D4↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C9DA94↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C9E258↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CA0EC0↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CA8E84↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CA9FCC↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CB00D4↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CB01B0↑o ...
    //    .data.rel.ro : 01CB01C4; reference to RTTI's type class
    //    .data.rel.ro:01CB01C8 B7 44 BA 01                   DCD _ZTS10Projectile; reference to type's name
    //    .data.rel.ro:01CB01CC C4 E1 C6 01                   DCD _ZTI17ModularRealObject; reference to parent's type name
    
    //其中偏移引用部分后面的
    /*.data.rel.ro:01CB00D4 C4 01 CB 01                   DCD _ZTI10Projectile                    ; `typeinfo for'Projectile
.data.rel.ro:01CB00D8 24 5A 90 00                   DCD sub_905A24*/
    //部分的.data.rel.ro:01CB00D8的01CB00D8即vftable = copyVFTable(getActualOffset(填入), 53);
    vftable = copyVFTable(getActualOffset(Customize_Projectile_GridItemRaiserProjectileProps_ProjectileVFTableAddr), 53);

    patchVFTable(vftable, (void*)GridItemRaiserProjectileProps::getRtClass, RTOBJECT_GETTYPE_INDEX);

    

    GridItemRaiserProjectileProps::getRtClass();

    LOGI("GridItemRaiserProjectileProps finish init");
}