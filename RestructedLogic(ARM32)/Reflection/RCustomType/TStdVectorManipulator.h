#pragma once
#include "../../Reflection/RType.h"
#include "../../Sexy/RtWeakPtr.h"

//寻找该偏移方法：
//HEX搜索文本TStdVectorManipulator
//然后比如你跳转到了诸如"TStdVectorManipulatorI15BoardEntityStatEE"字样时候
//把鼠标单击TStdVectorManipulatorI15BoardEntityStatEE的"T"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B8E530; `typeinfo name for'Reflection::RCustomType::TStdVectorManipulator<BoardEntityStat>
//.rodata:01B8E530 4E 31 30 52 65 66 6C 65 63 74 + _ZTSN10Reflection11RCustomType21TStdVectorManipulatorI15BoardEntityStatEE DCB "N10Reflection11RCustomType21TStdVectorManipulatorI15BoardEntityStatEE", 0
//.rodata : 01B8E530 69 6F 6E 31 31 52 43 75 73 74 + ; DATA XREF : .data.rel.ro : 01C5C4C4↓o
//.rodata : 01B8E530 6F 6D 54 79 70 65 32 31 54 53 + ; type descriptor name

//双击示例中.data.rel.ro : 01C5C4C4↓o位置，进行跳转
//界面朝上一点，你会发现这块整体长这样：
//.data.rel.ro:01C5C4A0; `vtable for'Reflection::RCustomType::TStdVectorManipulator<BoardEntityStat>
//.data.rel.ro:01C5C4A0 00 00 00 00                   _ZTVN10Reflection11RCustomType21TStdVectorManipulatorI15BoardEntityStatEE DCD 0
//.data.rel.ro : 01C5C4A0; DATA XREF : sub_253E00 + 50↑o
//.data.rel.ro : 01C5C4A0; sub_253E00 + 54↑o
//.data.rel.ro:01C5C4A0;.text:off_253ED0↑o
//.data.rel.ro : 01C5C4A0; offset to this
//.data.rel.ro:01C5C4A4 C0 C4 C5 01                   DCD _ZTIN10Reflection11RCustomType21TStdVectorManipulatorI15BoardEntityStatEE; `typeinfo for'Reflection::RCustomType::TStdVectorManipulator<BoardEntityStat>
//.data.rel.ro:01C5C4A8 00 41 25 00                   DCD nullsub_346
//.data.rel.ro : 01C5C4AC D8 3E 25 00                   DCD j__ZdlPv_4; operator delete(void*)
//.data.rel.ro:01C5C4B0 DC 3E 25 00                   DCD sub_253EDC
//.data.rel.ro : 01C5C4B4 F0 40 25 00                   DCD sub_2540F0
//.data.rel.ro : 01C5C4B8; public Reflection::RCustomType::IStdManipulator
//.data.rel.ro:01C5C4B8; `typeinfo for'Reflection::RCustomType::IStdManipulator
//.data.rel.ro:01C5C4B8 D4 74 DF 01                   _ZTIN10Reflection11RCustomType15IStdManipulatorE DCD _ZTVN10__cxxabiv117__class_type_infoE + 8
//.data.rel.ro : 01C5C4B8; DATA XREF : .data.rel.ro : 01C5C4C8↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5C984↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5C9A8↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5CC04↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5CD94↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5CDB8↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5DD50↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5DD74↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5DD98↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5E2D4↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5EBCC↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5EE00↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5EE70↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5EE94↓o
//.data.rel.ro : 01C5C4B8;.data.rel.ro:01C5EEB8↓o ...
//.data.rel.ro : 01C5C4B8; reference to RTTI's type class
//.data.rel.ro:01C5C4BC 80 E5 B8 01                   DCD _ZTSN10Reflection11RCustomType15IStdManipulatorE; reference to type's name
//.data.rel.ro:01C5C4C0; public Reflection::RCustomType::TStdVectorManipulator<BoardEntityStat> :
//.data.rel.ro : 01C5C4C0;   public /* offset 0x0 */ Reflection::RCustomType::IStdManipulator
//.data.rel.ro:01C5C4C0; `typeinfo for'Reflection::RCustomType::TStdVectorManipulator<BoardEntityStat>
//.data.rel.ro:01C5C4C0 D8 74 DF 01                   _ZTIN10Reflection11RCustomType21TStdVectorManipulatorI15BoardEntityStatEE DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C5C4C0; DATA XREF : .data.rel.ro : 01C5C4A4↑o
//.data.rel.ro : 01C5C4C0; reference to RTTI's type class
//.data.rel.ro:01C5C4C4 30 E5 B8 01                   DCD _ZTSN10Reflection11RCustomType21TStdVectorManipulatorI15BoardEntityStatEE; reference to type's name
//.data.rel.ro:01C5C4C8 B8 C4 C5 01                   DCD _ZTIN10Reflection11RCustomType15IStdManipulatorE; reference to parent's type name

//在这部分的偏上部分，你可以看到一个注释：; operator delete(void *)
//双击在这句话下面的那个sub_253EDC位置的函数
//跳转之后按F5，所得如下：
//int __fastcall sub_253EDC(int a1, int* a2, int* a3, int a4, int a5)
//{
//	int v7; // r5
//	int v8; // r7
//	int v9; // r6
//	unsigned int i; // r8
//	int v11; // r1
//	void(__fastcall * v12)(int, int, int*, int*); // r5
//	int v14; // r7
//	int v15; // r6
//	void(__fastcall * v16)(int, int, int*, int*); // r4
//	int v17; // r0
//	int v18; // [sp+0h] [bp-38h]
//	int* v19; // [sp+0h] [bp-38h]
//	unsigned int v20; // [sp+4h] [bp-34h] BYREF
//	int v21; // [sp+8h] [bp-30h] BYREF
//	int v22; // [sp+Ch] [bp-2Ch]
//	void* v23; // [sp+10h] [bp-28h]
//
//	if (*((_BYTE*)a3 + 8))
//	{
//		v7 = *a3;
//		v8 = 0;
//		v20 = 0;
//		if (sub_254210(v7, a4, &v20))
//		{
//			v18 = v7;
//			if (v20)
//			{
//				sub_2542E4(a2);
//				if (v20)
//				{
//					v9 = 0;
//					for (i = 0; i < v20; ++i)
//					{
//						v11 = *a2 + v9;
//						v12 = *(void(__fastcall**)(int, int, int*, int*))(*(_DWORD*)a5 + 44);
//						v23 = 0;
//						v22 = 0;
//						v21 = 0;
//						v12(a5, v11, a3, &v21);
//						if ((v21 & 1) != 0)
//							operator delete(v23);
//						v9 += 8;
//					}
//				}
//			}
//			v8 = 1;
//			*(_DWORD*)(v18 + 16) -= 8;
//		}
//		return v8;
//	}
//	else
//	{
//		v19 = (int*)a3[1];
//		sub_254104();
//		v14 = *a2;
//		v15 = a2[1];
//		if (*a2 != v15)
//		{
//			do
//			{
//				v16 = *(void(__fastcall**)(int, int, int*, int*))(*(_DWORD*)a5 + 44);
//				v23 = 0;
//				v22 = 0;
//				v21 = 0;
//				v16(a5, v14, a3, &v21);
//				if ((v21 & 1) != 0)
//					operator delete(v23);
//				v14 += 8;
//			} while (v15 != v14);
//		}
//		v17 = *v19;
//		--v19[2];
//		LOBYTE(v21) = -2;
//		sub_10E5340(v17, &v21, 1);
//		return 1;
//	}
//}

//这个函数里面对应位置则是接下来三个偏移的函数名称，记下对应的即可
#if GAME_VERSION<1000
//sub_254210对应OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1
#define OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1 TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1Addr
#endif
#if GAME_VERSION>=1000
//sub_254104对应OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2
#define OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2 TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2Addr
//sub_10E5340对应OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3
#define OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3 TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3Addr
//sub_2ED038对应OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tGetHandle
#define OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tGetHandle TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tGetHandle
//sub_149CC2C对应OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tReadFunc
#define OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tReadFunc TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tReadFunc
//sub_2ED188对应OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tStackExtend
#define OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tStackExtend TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tStackExtend
//sub_149CC70对应OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tVecSize
#define OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tVecSize TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tVecSize
#endif
namespace Reflection
{
	namespace RCustomType
	{
		struct UnkStruct
		{
		public:
			int unk1;
			int unk2;
			int unk3;
			int unk4;
			Sexy::RtWeakPtr<void>* weakPtrPtr;
		};

		struct VectorManipulatorStruct
		{
		public:
			UnkStruct* unkPtr;
			void* unkPtr2;
			bool unkBool;
		};

		template <typename T>
		class TStdVectorManipulator
		{
		public:
			using GenericVector = std::vector<T>;

			virtual void NullSub() {};

			virtual void DestroyEffect(void* a1) {
				operator delete(a1);
			};

#if GAME_VERSION<1000
			virtual bool Edit(GenericVector* vector,
				VectorManipulatorStruct* manipInfo,
				Sexy::RtWeakPtr<void>* unkWeakPtr,
				RType* reflectionType)
			{
				if (manipInfo->unkBool)
				{
					int vecSize = 0;

					typedef bool(*func)(void*, Sexy::RtWeakPtr<void>*, int&);
					func pFunc = (func)getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1);

					if (pFunc(manipInfo->unkPtr, unkWeakPtr, vecSize))
					{
						if (vecSize > 0)
						{
							LOGI("[ Reflection::RCustomType::TStdVectorManipulator::Edit ] [ Begin manip vector (size: %d) ]", vecSize);
							vector->resize(vecSize);

							for (int i = 0; i < vecSize; i++)
							{
								T* element = &vector->at(i);
								Sexy::SexyString str;
								reflectionType->Function11(element, manipInfo, str);
							}
						}

						manipInfo->unkPtr->weakPtrPtr--;
						return true;
					}

					return false;
				}
				else
				{
					int** v19 = *(int***)((int64_t)manipInfo + 4);
					typedef void (*sub254104)(int**, Sexy::RtWeakPtr<void>*, int, char);
					((sub254104)getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2))(v19, unkWeakPtr, vector->size(), 0xFD);

					if (!vector->empty()) {
						for (size_t i = 0; i < vector->size(); ++i) {
							T* element = &vector->at(i);
							Sexy::SexyString str;
							reflectionType->Function11(element, manipInfo, str);
						}
					}

					int* v17 = *v19;
					v19[2] = (int*)((char*)v19[2] - 1);

					uint8_t v21 = 254;
					typedef int (*sub10E5340)(int*, uint8_t*, int);
					((sub10E5340)getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3))(v17, &v21, 1);

					return true;

					LOGW("[ Reflection::RCustomType::TStdVectorManipulator::Edit ] [ Panic! Need to edit vector but manipInfo->unkBool is false ]");
				}
			}

#endif
#if GAME_VERSION>=1000
			// 2. 适配后的 Edit 函数
			virtual bool Edit(GenericVector* vector,
				VectorManipulatorStruct* manipInfo,
				Sexy::RtWeakPtr<void>* unkWeakPtr,
				RType* reflectionType)
			{
				// a3 是我们的 SerializationContext/State
				if (manipInfo->unkBool) // 读取模式 (sub_2EC6A0 前半段逻辑)
				{
					int ctxAddr = (int)manipInfo->unkPtr; // a3

					// 1. 获取 Handle (sub_2ED038)
					typedef int(*tGetHandle)(int, void*);
					int handle = ((tGetHandle)getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tGetHandle))(ctxAddr, unkWeakPtr);

					if (handle && ((bool(*)(int, int))getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tReadFunc))(ctxAddr, handle))
					{
						// --- 校准点 A: 入栈动作 (sub_2ED188 之前的逻辑) ---
						// 汇编里在获取长度前，把 handle 压入了 ctx+12 指向的栈里
						struct ScopeEntry { int handle; int unk; };
						ScopeEntry entry = { handle, 0 };

						int* stack_top = *(int**)(ctxAddr + 16);
						int* stack_end = *(int**)(ctxAddr + 20);

						if ((int)stack_top >= (int)stack_end) {
							// 栈满了，调用扩容
							((void(*)(int, ScopeEntry*))getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tStackExtend))(ctxAddr + 12, &entry);
						}
						else {
							// 直接压栈
							stack_top[0] = entry.handle;
							stack_top[1] = entry.unk;
							*(int*)(ctxAddr + 16) += 8; // 指针移动
						}

						// 2. 获取长度 (sub_149CC70)
						int vecSize = ((int(*)(int, int))getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tVecSize))(ctxAddr, handle);

						if (vecSize >= 0) {
							// 这里对应汇编 sub_2ED2C4 的逻辑，我们可以直接用 vector->resize
							vector->resize(vecSize);

							for (int i = 0; i < vecSize; i++) {
								T* element = &vector->at(i);
								Sexy::SexyString str;
								reflectionType->Function11(element, manipInfo, str);
							}
						}

						// --- 校准点 B: 退栈动作 (汇编末尾的 *(_DWORD *)(v25 + 16) -= 8) ---
						*(int*)(ctxAddr + 16) -= 8;
						return true;
					}
					return false;
				}
				else // 写入模式 (sub_2EC6A0 后半段逻辑)
				{
					// a3[1] 是 SerializationState
					int* state = (int*)((int*)manipInfo->unkPtr)[1];

					// 1. 写入 Tag 和 长度 (sub_2EC968)
					// 注意：汇编里传的是 253 (0xFD)
					typedef void (*tWriteTag)(int*, void*, int, int);
					((tWriteTag)getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2))(state, unkWeakPtr, vector->size(), 253);

					// 2. 遍历写入元素
					for (size_t i = 0; i < vector->size(); ++i) {
						T* element = &vector->at(i);
						Sexy::SexyString str;
						reflectionType->Function11(element, manipInfo, str);
					}

					// --- 校准点 C: 位图回退 (--v12[2]) ---
					state[2]--;

					// --- 校准点 D: 写入结束标记 254 (0xFE) ---
					// 对应汇编末尾的 LOBYTE(v26) = -2 (即 0xFE)
					uint8_t endTag = 254;
					int stream = *state;
					((void(*)(int, uint8_t*, int))getActualOffset(OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3))(stream, &endTag, 1);

					return true;
				}
			}





#endif

			virtual int GetSize(GenericVector* vector)
			{
				return vector->size();
			}
		};
	}
}