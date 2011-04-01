#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <list>
#include <iostream>
using namespace std;

#include <noise/noise.h>
using namespace noise;

#include "motor/graphics/chunk.hpp"
#include "motor/math/perlinNoise.hpp"

namespace motor
{
	class World
	{
		public:
			World();
			void load(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ);
			void generate();
			void draw(unsigned int, unsigned int);

			block_t getBlock(unsigned int x, unsigned int y, unsigned int z);
			void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int type);

		private:
			Chunk ***chunks;
			//prolly later list<Chunk> chunks;
			//module::Perlin perlin;
			unsigned int xDim, yDim, zDim;
	};
}

#endif
