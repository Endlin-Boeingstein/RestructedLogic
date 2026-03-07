#include "axml_parser.hpp"
#include <stdlib.h>
#include "../Logging.h"

#define RES_STRING_POOL_TYPE 0x0001
#define RES_XML_RESOURCE_MAP_TYPE 0x0180
#define RES_XML_START_ELEMENT_TYPE 0x0102

#define TYPE_STRING 0x03
#define TYPE_INT_DEC 0x10

#define UTF8_FLAG 0x00000100

static uint16_t r16(uint8_t* p)
{
    return *(uint16_t*)p;
}

static uint32_t r32(uint8_t* p)
{
    return *(uint32_t*)p;
}

static std::string get_utf16(uint8_t* base, uint32_t off)
{
    uint16_t len = r16(base + off);
    off += 2;

    std::string s;
    s.reserve(len);

    for (int i = 0; i < len; i++)
        s.push_back(base[off + i * 2]);

    return s;
}

static std::string get_utf8(uint8_t* base, uint32_t off)
{
    uint8_t* p = base + off;

    uint8_t u16len = *p++;
    if (u16len & 0x80) p++;

    uint8_t u8len = *p++;
    if (u8len & 0x80) p++;

    return std::string((char*)p, u8len);
}

AppInfo parse_manifest(uint8_t* data, size_t size)
{
    AppInfo info;

    std::vector<std::string> strings;

    uint16_t xmlHeaderSize = r16(data + 2);

    size_t cursor = xmlHeaderSize;   // 关键修复

    while (cursor + 8 <= size)
    {
        uint16_t type = r16(data + cursor);
        uint16_t headerSize = r16(data + cursor + 2);
        uint32_t chunkSize = r32(data + cursor + 4);
        //测试时候用，看AXML到底有没有被正确分块读取的
        /*LOGI("chunk type=%04x size=%d", type, chunkSize);*/
        if (chunkSize == 0 || cursor + chunkSize > size)
            break;

        if (type == RES_STRING_POOL_TYPE)
        {
            uint32_t stringCount = r32(data + cursor + 8);
            uint32_t flags = r32(data + cursor + 16);
            uint32_t stringsStart = r32(data + cursor + 20);

            uint32_t* offsets = (uint32_t*)(data + cursor + headerSize);
            uint8_t* strBase = data + cursor + stringsStart;

            strings.reserve(stringCount);

            for (uint32_t i = 0; i < stringCount; i++)
            {
                uint32_t off = offsets[i];

                if (flags & UTF8_FLAG)
                    strings.push_back(get_utf8(strBase, off));
                else
                    strings.push_back(get_utf16(strBase, off));
            }
        }

        else if (type == RES_XML_START_ELEMENT_TYPE)
        {
            uint32_t nameIdx = r32(data + cursor + 20);

            if (nameIdx >= strings.size())
            {
                cursor += chunkSize;
                continue;
            }

            std::string tag = strings[nameIdx];

            uint16_t attrStart = r16(data + cursor + 24);
            uint16_t attrSize = r16(data + cursor + 26);
            uint16_t attrCount = r16(data + cursor + 28);

            uint8_t* attr = data + cursor + headerSize + attrStart;

            for (int i = 0; i < attrCount; i++)
            {
                uint32_t attrNameIdx = r32(attr + 4);
                uint32_t rawValueIdx = r32(attr + 8);

                uint8_t dataType = *(attr + 15);
                uint32_t dataValue = r32(attr + 16);

                if (attrNameIdx >= strings.size())
                {
                    attr += attrSize;
                    continue;
                }

                const std::string& name = strings[attrNameIdx];

                std::string value;

                if (dataType == TYPE_STRING && rawValueIdx < strings.size())
                    value = strings[rawValueIdx];

                if (dataType == TYPE_INT_DEC)
                    value = std::to_string(dataValue);

                if (tag == "manifest")
                {
                    if (name == "package")
                        info.package = value;

                    else if (name == "versionName")
                        info.versionName = value;

                    else if (name == "versionCode")
                        info.versionCode = atoi(value.c_str());
                }

                if (tag == "uses-sdk")
                {
                    if (name == "minSdkVersion")
                        info.minSdk = atoi(value.c_str());

                    else if (name == "targetSdkVersion")
                        info.targetSdk = atoi(value.c_str());
                }

                attr += attrSize;
            }
        }

        cursor += chunkSize;
    }

    return info;
}