#ifndef _CHUNK_HPP
#define _CHUNK_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GL/gl.h>
#include <motor/math/glm/glm.hpp>
#include <motor/math/glm/gtc/matrix_transform.hpp>
#include <motor/math/glm/gtx/projection.hpp>
#include <motor/math/glm/gtc/type_ptr.hpp>

#include "motor/utility/blocks.hpp"

namespace motor
{
	typedef struct vertex_t
	{
		vertex_t(glm::vec3 const & Position, glm::vec2 const & Texcoord):	Position(Position),	Texcoord(Texcoord) {}
		vertex_t() {}
		glm::vec3 Position;
		glm::vec2 Texcoord;
	} vertex_t;

	typedef struct block_t
	{
		unsigned char type;
		unsigned char visible;
		//7				6					5			4		 3			2	   1   0
		//visible	handled?	right	left bottom back top front
		block_t() : type(0), visible(0) {}
		block_t(unsigned char tp, unsigned char vs)
		{
			type = tp;
			visible = visible;
		}
	} block_t;

	class World; //hack for circular dependency
	class Chunk
	{
		public:
			Chunk();
			Chunk(unsigned int xDim, unsigned int yDim, unsigned int zDim);
			~Chunk();

			void setWorldRef(World *wrld);

			void set(glm::ivec3 &coord, unsigned short blockType);
			void set(unsigned int x, unsigned int y, unsigned int z, unsigned short blockType);
			block_t& get(glm::ivec3 &coord);
			//block_t get(unsigned int x, unsigned int y, unsigned int z);
			block_t& get(int x, int y, int z);

			unsigned int calculateVisibleSides(unsigned int, unsigned int, unsigned int, bool mergeFaces = false);
			void reCalculateVisibleSides(bool mergeFaces = false);
			void uploadToVbo();
			unsigned int getVertexCount();

			unsigned int vertexBuffer;

			unsigned int memoryAllocationGfx;
			unsigned int memoryAllocationRam;

		private:
			block_t ***voxels;
			int xSize, ySize, zSize;
			int xOff, yOff, zOff;
			vertex_t *vertices;
			unsigned int vertexCount;
			World *world;
	};
}
#endif
