#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <list>
#include <iostream>
using namespace std;

#include <noise/noise.h>
using namespace noise;

#include "motor/graphics/chunk.hpp"
#include "motor/math/perlinNoise.hpp"

#include "motor/math/glm/glm.hpp"

#include <SDL/SDL.h>

namespace motor
{
	class World
	{
		public:
			World();
			void load(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, unsigned int chunkSizeX = 16, unsigned int chunkSizeY = 16, unsigned int chunkSizeZ = 16);
			void generate();
			void recalculateChunck(unsigned int x, unsigned int y, unsigned int z);//with block position
			void draw(unsigned int, unsigned int);

			block_t& getBlock(unsigned int x, unsigned int y, unsigned int z);
			block_t& getBlock(glm::vec3 v);
			void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int type);

			unsigned int memoryAllocationGfx;
			unsigned int memoryAllocationRam;

		private:
			Chunk ***chunks;
			//prolly later list<Chunk> chunks;
			//module::Perlin perlin;
			unsigned int worldDimX, worldDimY, worldDimZ; //in chunks
			unsigned int chunkSizeX, chunkSizeY, chunkSizeZ; //in blocks
	};
}

#endif
