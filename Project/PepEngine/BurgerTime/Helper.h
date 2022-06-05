#pragma once

enum class Direction
{
	None,
	Up,
	down,
	left,
	right
};

enum class BurgerByte
{
	empty = 0,
	bunTop = 1,
	bunBottom = 2,
	meat = 4,
	cheese = 8,
	lettuce = 16,
	tomato = 32,
	plate = 64
};

enum class LevelByte
{
	empty = 0,
	platform = 1,
	ladder = 2,
	hotdog = 4,
	pickle = 8,
	egg = 16,
	pepper = 32,
	salt = 64
};

enum class Gamemode
{
	Single,
	Versus,
	Coop
};