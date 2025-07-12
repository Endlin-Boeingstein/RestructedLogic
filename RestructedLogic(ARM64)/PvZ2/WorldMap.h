#pragma once

class WorldMap
{
public:
	char pad_0000[304]; //0x0000
	float m_posX; //0x0130
	float m_posY; //0x0134
	int m_boundaryX; //0x0138
	int m_boundaryY; //0x013C
	int m_boundaryWidth; //0x0140
	int m_boundaryHeight; //0x0144
};