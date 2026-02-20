#pragma once

enum CollisionTypeFlags {
	none = 0,
	groundzombies = 1,
	offgroundzombies = 2,
	dyingzombies = 4,
	allzombies = 7,
	griditems = 8,
	lowplants = 0x20,
	normalplants = 0x40,
	allplants = 0x80,
	plants = 0xF0,
	ground = 0x100,
	instigator = 0x200,
	everything = 0x3FF
};