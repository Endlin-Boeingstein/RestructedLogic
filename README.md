# RestructedLogic_Lite

Restructed Logic is a project which can help you create PvZ2's hooking by Visual Studio's C++ Mobile development module without any other operations to modify the path and the settings.

RestructedLogic_Lite is a simplified version based on RestructedLogic. It removes rarely used and untested features, while eliminating bloated and redundant parts of the code. The codebase has been reorganized in a more C++-style (rather than C-style) manner.

## Credits

BreakfastBrainz2's lib.so hooking project: <https://github.com/BreakfastBrainz2/PVZ2ExampleMod>.

Djngo's hooking project for many platforms: <https://github.com/Djngo/Hooking-and-Patching-android-template>.

Rprop's ARM64 hooking project: <https://github.com/Rprop/And64InlineHook>.

XMDS's hooking project: <https://github.com/XMDS/GlossHook>.

Ookdshin's PicoSHA2: [GitHub - okdshin/PicoSHA2: a header-file-only, SHA256 hash generator in C++](https://github.com/okdshin/PicoSHA2).

Kokke's Tiny-AES-C: [GitHub - kokke/tiny-AES-c: Small portable AES128/192/256 in C](https://github.com/kokke/tiny-AES-c).

BlazeyLol's updated lib.so hooking project: <https://github.com/BlazeyLol/PVZ2ExampleMod>.

BlazeyLol's expansion hooking project: <https://github.com/BlazeyLol/PVZ2ExpansionMod>.

RenoJson's PvZ2-Libbing-Stuff-For-9.6- project: <https://github.com/RenoJson/PvZ2-Libbing-Stuff-For-9.6->.

RenoJson's Deprecated-Lib hooking project: <https://github.com/RenoJson/Deprecated-Lib>.

Endlin-Boeingstein's multi-version hooking project (The full version of this project):  <https://github.com/Endlin-Boeingstein/RestructedLogic>

## Usage

Download and install Visual Studio 2022: <https://visualstudio.microsoft.com>.

Modify the Visual Studio 2022's Workloads and install `Mobile development with C++` module. And then, you can clone the repo and open the repo's `.sln` file by Visual Studio 2022.

If you want to generate ARM32 so. Select the `RestructedLogic(ARM32)` and click the triangle button that the `Release` `ARM` nearby.  If you want to generate ARM64 so. Select the `RestructedLogic(ARM64)` and click the triangle button that the `Release` `ARM64` nearby.

Then in the folder, you would found ARM and ARM64 folder. These so file may inside that name called `libRestructedLogic_ARM32_.so` in `ARM/Release` and `libRestructedLogic_ARM64_.so` in `ARM64/Release`.

Download APKToolGUI: <https://drive.google.com/file/u/0/d/1Zko59XeiX7DZENWaLDsPjvHPfk9dwHgi/view?usp=drive_link&pli=1>. Use APKToolGUI to decompile the apk that you want to hook.

Copy the .so file to the decompiled folder's `lib\armeabi-v7a` path when you want to use ARM32 or `lib\arm64-v8a` path when you want to use ARM64. Change the .so file's name to `libRestructedLogic.so`.

Delete the ARM lib version folder that you needn't use it.
Then modify `PvZ2GameActivity.smali` which is in the decompiled folder. Open it, and find this:

```
    .line 57  
    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V   
```

If you can not find this you would find:

```
    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V  
    const-string v0, "PVZ2"
```

The key statements behind this like:

```
    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

this key statements without const-string v0, "XXX"

Down there your paste this:

```
    const-string v0, "RestructedLogic"

    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

It should look like this:

```
    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V

    const-string v0, "RestructedLogic"

    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

Save and exit.  

If you think RestructedLogic is not cooooooool. You can modify `PvZ2GameActivity.smali`. Change `RestructedLogic` to what you want to change without `lib` header. Save and exit. And then, Change `libRestructedLogic.so` to `lib`+`ChangedName`+`.so`.  

Compile the decompiled folder. You will get a hooked apk. Install it in your device, enjoy it.

---

以下为原作者 Endlin-Boeingstein 对于圈内乱象在代码中写的一些锐评。为使代码精简，现移动至此：

```cpp
#pragma region PrimeGlyphCacheLimitationDescription
// 此代码为融小宝对RestructedLogic工程的私有化改造功能之一，并未根据RestructedLogic的GPL-3.0协议进行公开，我已拥有相关证据，你不守规矩，就别怪我强制公开了，并且我也没用你的写法，自己写的
// 也不是啥秘密，按照一般查找流程都能找到
// 再不济你去https://www.bilibili.com/opus/657868413102718978一路大佬的帖子，打开IDA PRO就知道怎么找了
// 实际上我是先去找RSB读取函数，然后再找这里的，一路大佬的帖子有一个地方会卡住人（实际上是你不会确认位置），所以使用RSB主读取函数寻找法就能找到了。
// 你要是恼羞成怒，还以为我偷别人的抢别人的，那好，这段的伪C代码（10.3版本）我贴在这了
// int __fastcall sub_1697E88(_DWORD* a1, int a2)
//{
//     int v4; // r7
//     int* v5; // r6
//     int v6; // r1
//     int v7; // r3
//     int v8; // r0
//     int v9; // r0
//     int v10; // r0
//     int v11; // r0
//     int v12; // r5
//     int v13; // r0
//     int v14; // r0
//     __int64 v15; // r0
//     __int64 v16; // r0
//     int v17; // r7
//     int v18; // r5
//     int v20[2]; // [sp+10h] [bp-2F8h] BYREF
//     void* v21; // [sp+18h] [bp-2F0h]
//     char v22[16]; // [sp+20h] [bp-2E8h] BYREF
//     char v23[536]; // [sp+30h] [bp-2D8h] BYREF
//     int v24; // [sp+248h] [bp-C0h]
//     int v25; // [sp+2A4h] [bp-64h]
//     int v26; // [sp+2ECh] [bp-1Ch]
//
//     sub_1716838(sub_169B238, sub_169B248, j_realloc);
//     v4 = *(_DWORD*)(a2 + 1304);
//     if (*(_DWORD*)(a2 + 1300) < v4)
//         v4 = *(_DWORD*)(a2 + 1300);
//     v5 = (int*)operator new(0x130u);
//     v6 = ((int (*)(void))sub_169B258)();
//     v7 = 2048;
//     if (v4 <= 1024)
//         v7 = 1024;
//     if (v4 <= 640)
//         v7 = 512;
//     sub_177ECF4(v5, v6, a2, v7);
//     a1[1] = v5;
//     v8 = *v5;
//     v5[59] = 1;
//     v9 = (*(int(__fastcall**)(int*, int, int))(v8 + 12))(v5, 1, 1);
//     v10 = sub_169B258(v9);
//     v11 = sub_16CF03C(v10);
//     sub_16CF08C(v11);
//     v12 = operator new(0xB500u);
//     v13 = sub_16D901C(v12, 0);
//     *a1 = v12;
//     v14 = sub_169B258(v13);
//     sub_16DA6F8(v12, v14);
//     sub_16CF418(*a1);
//     (*(void(__fastcall**)(_DWORD))(*(_DWORD*)*a1 + 8))(*a1);
//     v21 = 0;
//     v20[1] = 0;
//     v20[0] = 0;
//     sub_2F06A8((int)v20, (wchar_t*)&off_20381A8, 8u);
//     v15 = sub_14E138C(v22, 1);
//     sub_1698158(v23, HIDWORD(v15), v20, 7, v15);
//     if ((v20[0] & 1) != 0)
//         operator delete(v21);
//     v16 = sub_14E138C(v20, 0);
//     v25 = sub_14E1548(v16, HIDWORD(v16));
//     v24 = 1;
//     v17 = (*(int(__fastcall**)(_DWORD, char*, _DWORD, _DWORD, int, int, int))(*(_DWORD*)*a1 + 32))(
//         *a1,
//         v23,
//         0,
//         0,
//         0xFFFF,
//         -1,
//         1);
//     v18 = operator new(0x2C8u);
//     sub_1694728(v18, v17, v23);
//     a1[2] = v18;
//     a1[3] = v18;
//     return _stack_chk_guard - v26;
// }
// 还有这个，这个就是最终的地址，看看，看看，是不是和下面实装的代码很像？
// 我半年来我就看看，这破圈子把在国内打破so代码垄断的人赶走后，会发展成什么样
// 结果呢？维护垄断并攻击技术开放的人成了最大受益者，甚至RestructedLogic都变成了某些人私有的玩物！！！！！
// 这大半年来国内已经非常落后了！有些人都投奔国外了！国内的人都开始为这些垄断付费了！
// 故特实装该代码以大白于天下，勿忘开源之精神，与垄断者抗争到底！！！！！
//_DWORD* __fastcall sub_177ECF4(_DWORD* a1, int a2, int a3, int a4)
//{
//     _DWORD* result; // r0
//
//     sub_17A97BC();
//     *a1 = off_21E8698;
//     memset(a1 + 66, 0, 0x24u);
//     result = a1;
//     a1[22] = a4;
//     a1[75] = a3;
//     return result;
// }
#pragma endregion

#pragma region PrimeGlyphCacheLimitation
// 无语了，连Limitation都能打成Limination，还得我去修正
typedef uint *(*PrimeGlyphCacheLimitation)(uint *, int, int, int);
PrimeGlyphCacheLimitation oPrimeGlyphCacheLimitation = NULL;

// 一路：高端设备缓冲大小为2048，中端设备为1024，低端设备为512。经过测试，缓冲大小最大只能设为2048，设为更高值，会导致进入游戏后文字渲染全为空白，这与设为0的效果一致。
uint *hkPrimeGlyphCacheLimitation(uint *a1, int a2, int a3, int a4) {
  // typedef int(*Func1)(int a1, int a2);
  // Func1 func = (Func1)getActualOffset(0x141D75C);
  // func((uint)a1, a2);
  //*a1 = getActualOffset(0x1DDB7B8);
  // memset(a1 + 66, 0, 0x24u);
  // a1[22] = 2048; //缓冲区大小
  // a1[75] = a3;
  // return a1;
  // 你知不知道，你这样做是非常垃圾的做法？还是看我这个RL的创始人怎么改的吧！学着点！
  uint *result = oPrimeGlyphCacheLimitation(a1, a2, a3, a4);
  a1[22] = 2048;
  LOGI("Hooked sub_177ECF4: Modified a1[22] to %d", a1[22]);
  return result;
}

#pragma endregion

#pragma region BeforeReading
// 但是无所谓了，曾经第一个做出RSB加密的大佬在卖自己加密功能的时候，不少人持反对意见
// 我的原话如下：
// “也不要说垄断不垄断的，这玩意算另造引擎，已经超出pvz2修改范围
//  凡事需要付出代价，要么是金钱要么是精力
//  如果你们想要rsb加密宽视野加映射却对他收钱很不爽，你大可以不买。
//  甚至你大可以自己搞一个，你也可以收费。
//  你甚至可以自己搞出来把他饭碗砸了etc.”
// 现在，宽视野、加映射、RSB加密我全搞出来了，还开源了，但是又能怎么样呢？
// 我搞出来了RestructedLogic，谁会理解我测试上百遍失败才搞出来这个懒人开源工程呢？
// 当时做这个工程的时候，群被截图发到了国外，群成员被威胁，群内所有成员都被截图，那时候多苦？
// 最后下场是啥？作者被驱逐，别人拿过来改成自己的私人玩物，还说是那个老外做的
// 这次的RSB加密估计也是这样吧......我测试了上百遍，终于搞出来了
// 但是最终会被所有人使用吗？不会！因为他们会把这个据为己有！
// 他们会嫌弃这项工程，向外人表示他们的不齿，因为啥？因为他们为了数据包安全，已经向那位大佬付钱了（笑）！
// 我不仅砸了这位大佬的饭碗，我还砸了这群人的饭碗！
// 然后他们会根据这个工程去改装，变成自己的私人玩物
// 再次开启一段循环
// 现在啊，我等了半年，看看他们驱逐了曾经推广so的人，接下来国产so会怎么样？
// 结果啊，呵呵呵呵呵，不出所料，有个人，拿我的工程，搞了改渲染缓存的私活
// 他知道他注入成功了，但是那个语句有没有被调用？
// 他不知道！他只知道不闪退，就是成功！
// 他费尽心思把大多数的偏移给找了，但是他真的不知道他的函数实际上就是没用的
// 他还拙劣地复刻了那段原函数，实际上没必要，还得多找一段偏移
// 然后呢，他们狂欢，攻击被驱逐的人，显得自己赢了
// 他们这群废物，连LOGI干啥用的都不知道，ADB怕是也没碰过
// 找不出来什么原因，哪里错了？那就对了！
// 然后呢？他又做了什么？没了，没别的了
// 另外一群人呢？
// 他们曾经对被驱逐的人推崇的东西嗤之以鼻
// 现在却奉若圭臬，甚至做出了倒退版本的动作！
// 但是他们也不只是奉若圭臬啊！拿过来不好用还不忘嘲讽两句，踩两脚
// 最后一群人，是啊，和他们同流合污了啊
// 但是呢，他因为以前和那群人斗争过，所以他的思想比较先进
// 他找到了最初做这类工程的作者，和他合作
// 因为同流合污，所以他得到了大量资源和支持
// 因为找了国外，所以他得到了高端技术
// 这很好，不是吗？
// 阿三那样也很好吗？
// 那些小作者，为什么要屈服于那群人？
// 即使自己改版被骂，也得忍着
// 朋友同情他，他却捂着朋友的嘴，还得把朋友出卖以获得那群人的支持
// 然后整个圈子都去攻击那个放逐的人，知不知道真相不重要，重要的是要获取那群人支持
// 但是，一旦接受支持，那么，你就有了软肋，对方可以撤走在你身上的投入，你未完成的体系直接崩塌！
// 所以我再问一句，这很好，不是吗？
// 对此，我只能说
// 不独立自主，永远找不到出路！
#pragma endregion
```

