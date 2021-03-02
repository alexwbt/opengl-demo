#pragma once

enum class Blocks
{
	STONE, DIRT, GRASS
};

class Chunk : public GameObject
{
public:
	const static int SIZE = 8;

	int data[SIZE][SIZE][SIZE];

	Chunk(Shader* shader);
};
