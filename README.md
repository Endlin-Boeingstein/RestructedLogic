# RestructedLogic

Restructed Logic is a project which can help you create PvZ2's hooking by Visual Studio's C++ Mobile development module without any other operations to modify the path and the settings.

This project was compiled on April 11, 2024.

**It is recommended that general users with limited code reading ability and no special requirements use the lite version of this project: <https://github.com/MeteorFlower/RestructedLogic_Lite>**

## Acknowledgements

- **MeteorFlower** –For refining and simplifying the project, correcting the documentation, and diligently searching for function offsets to enable multi-version support.

## Credits

BreakfastBrainz2's lib.so hooking project: <https://github.com/BreakfastBrainz2/PVZ2ExampleMod>.

Djngo's hooking project for many platforms: <https://github.com/Djngo/Hooking-and-Patching-android-template>.

Rprop's ARM64 hooking project: <https://github.com/Rprop/And64InlineHook>.

XMDS's hooking project: <https://github.com/XMDS/GlossHook>.

Ookdshin's PicoSHA2: [GitHub - okdshin/PicoSHA2: a header-file-only, SHA256 hash generator in C++](https://github.com/okdshin/PicoSHA2).

Kokke's Tiny-AES-C: [GitHub - kokke/tiny-AES-c: Small portable AES128/192/256 in C](https://github.com/kokke/tiny-AES-c).

Rich Geldreich's miniz for portable unzipping: <https://github.com/richgel999/miniz>.

Yutaka Tsutano's axmldec for analysing AXML (Reference) : <https://github.com/ytsutano/axmldec>.

Antonin Hildebrand's boost for using axmldec (Unused) : <https://github.com/darwin/boost>.

Yann Collet's xxHash: <https://github.com/Cyan4973/xxHash>.

BlazeyLol's updated lib.so hooking project: <https://github.com/BlazeyLol/PVZ2ExampleMod>.

BlazeyLol's expansion hooking project: <https://github.com/BlazeyLol/PVZ2ExpansionMod>.

RenoJson's PvZ2-Libbing-Stuff-For-9.6- project: <https://github.com/RenoJson/PvZ2-Libbing-Stuff-For-9.6->.

RenoJson's Deprecated-Lib hooking project: <https://github.com/RenoJson/Deprecated-Lib>.

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
