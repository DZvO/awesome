#ifndef _BLOCKS_HPP
#define _BLOCKS_HPP
#include <iostream>
#include <motor/math/glm/glm.hpp>
#include <motor/math/glm/gtc/matrix_transform.hpp>
#include <motor/math/glm/gtx/projection.hpp>
#include <motor/math/glm/gtc/type_ptr.hpp>

namespace motor
{
	const int TILESET_WIDTH = 256;
	const int TILESET_HEIGHT = TILESET_WIDTH;

	enum blockType
	{
		BLOCK_AIR = 0,
		BLOCK_DIRT = 	1,
		BLOCK_STONE = 2,
		BLOCK_SAND = 3
	};

	enum blockTexCoordEnum
	{
		LOWERLEFT = 0,
		LOWERRIGHT = 1,
		UPPERRIGHT = 2, 
		UPPERLEFT = 3
	};

	/* 3---2
	 * |	 |
	 * |	 |
	 * 0---1
	 */
	const double TILESET_DISPLACEMENT = 16.0 / double(TILESET_WIDTH);
	const double OFFSET = 0.0001;

	const glm::vec2 blockTexCoord[] =
	{
		//grass
		glm::vec2(0.0f, TILESET_DISPLACEMENT - OFFSET),
		glm::vec2(TILESET_DISPLACEMENT - OFFSET, TILESET_DISPLACEMENT - OFFSET),
		glm::vec2(TILESET_DISPLACEMENT - OFFSET, 0.0f),
		glm::vec2(0.0f, 0.0f),

		//stone
		glm::vec2(TILESET_DISPLACEMENT + OFFSET, TILESET_DISPLACEMENT - OFFSET),
		glm::vec2(TILESET_DISPLACEMENT * 2 - OFFSET, TILESET_DISPLACEMENT - OFFSET),
		glm::vec2(TILESET_DISPLACEMENT * 2 - OFFSET, 0.0f),
		glm::vec2(TILESET_DISPLACEMENT + OFFSET, 0.0f),

		//sand
		glm::vec2(TILESET_DISPLACEMENT * 2 + OFFSET, TILESET_DISPLACEMENT - OFFSET),
		glm::vec2(TILESET_DISPLACEMENT * 3 - OFFSET, TILESET_DISPLACEMENT - OFFSET),
		glm::vec2(TILESET_DISPLACEMENT * 3 - OFFSET, 0.0f),
		glm::vec2(TILESET_DISPLACEMENT * 2 + OFFSET, 0.0f)
	};
}
#endif

//notes:
//16/256
//.0625000000
