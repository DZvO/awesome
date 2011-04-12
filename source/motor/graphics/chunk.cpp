#include "chunk.hpp"
#include "motor/graphics/world.hpp" //"hack" for circular dependency

motor::Chunk::Chunk(){}

motor::Chunk::Chunk(unsigned int xDim, unsigned int yDim, unsigned int zDim)
{
	xSize = xDim;
	ySize = yDim;
	zSize = zDim;
	vertexCount = 0;
	vertexBuffer = 0;
	vertices = NULL;

	voxels = new block_t**[xDim];
	for(unsigned int i = 0; i < xDim; i++)
	{
		voxels[i] = new block_t*[yDim];
		for(unsigned int j = 0; j < yDim; j++)
		{
			voxels[i][j] = new block_t[zDim];
			for(unsigned int k = 0; k < zDim; k++)
			{
				voxels[i][j][k] = block_t(BLOCK_AIR, 0);
			}
		}
	}

	memoryAllocationRam = sizeof(block_t) * xDim * yDim * zDim;
}

motor::Chunk::~Chunk(){}

void motor::Chunk::setWorldRef(World *wrld)
{
	world = wrld;
}

void motor::Chunk::set(glm::ivec3 &coord, unsigned short blockType)
{
	voxels[coord.x][coord.y][coord.z].type = blockType;
}

void motor::Chunk::set(unsigned int x, unsigned int y, unsigned int z, unsigned short blockType)
{
	voxels[x][y][z].type = blockType;
}

motor::block_t& motor::Chunk::get(glm::ivec3 &coord)
{
	return get(coord.x, coord.y, coord.z);
}

//motor::block_t motor::Chunk::get(unsigned int x, unsigned int y, unsigned int z)
motor::block_t& motor::Chunk::get(int x, int y, int z)
{
	if((x >= xSize || y >= ySize || z >= zSize) || (x < 0 || y < 0 || z < 0))
	{
		//TODO 
		//-insert code for finding block in other chunk here
		//-make parameters signed
		//
		//world.get(xOff + x, ...
		//xOff is the number of blocks offset 
		//cout << "stepping out to world\n";
		return world->getBlock(xOff + x, yOff + y, zOff + z);
		//return block_t(BLOCK_DIRT, 0);
	}
	return voxels[x][y][z];
}

unsigned int motor::Chunk::calculateVisibleSides(unsigned int xOff, unsigned int yOff, unsigned int zOff, bool mergeFaces)
{
	this->xOff = xOff;
	this->yOff = yOff;
	this->zOff = zOff;

	memoryAllocationGfx = 0;

	vertexCount = 0;
	unsigned int steps = 0;
	for(int x = 0; x < xSize; x++)
		for(int y = 0; y < ySize; y++)
			for(int z = 0; z < zSize; z++)
			{
				//				cout << (int)get(x+1, y, z).type << " ";
				if(get(x,y,z).type != BLOCK_AIR)
				{
					//7				6					5			4		 3			2	   1   0
					//visible	handled?	right	left bottom back top front
					get(x,y,z).visible = 0b00000000;

					//right
					if(get(x+1, y, z).type == BLOCK_AIR)// || get(x+1, y, z).visible == 0)
					{
						get(x,y,z).visible |= 0b10100000;
						steps++;
						vertexCount += 4;

						memoryAllocationGfx += sizeof(float) * 4;
					}
					//left
					if(get(x-1, y, z).type == BLOCK_AIR)// || get(x-1, y, z).visible == 0)
					{
						get(x,y,z).visible |= 0b10010000;
						steps++;
						vertexCount += 4;

						memoryAllocationGfx += sizeof(float) * 4;
					}
					//bottom
					if(get(x, y-1, z).type == BLOCK_AIR)// || get(x, y-1, z).visible == 0)
					{
						get(x,y,z).visible |= 0b10001000;
						steps++;
						vertexCount += 4;

						memoryAllocationGfx += sizeof(float) * 4;
					}
					//back
					if(get(x, y, z-1).type == BLOCK_AIR)// || get(x, y, z-1).visible == 0)
					{
						get(x,y,z).visible |= 0b10000100;
						steps++;
						vertexCount += 4;

						memoryAllocationGfx += sizeof(float) * 4;
					}
					//top
					if(get(x, y+1, z).type == BLOCK_AIR)// || get(x, y+1, z).visible == 0)
					{
						get(x,y,z).visible |= 0b10000010;
						steps++;
						vertexCount += 4;

						memoryAllocationGfx += sizeof(float) * 4;
					}
					//front
					if(get(x, y, z+1).type == BLOCK_AIR)// || get(x, y, z+1).visible == 0)
					{
						get(x,y,z).visible |= 0b10000001;
						steps++;
						vertexCount += 4;

						memoryAllocationGfx += sizeof(float) * 4;
					}
				}
			}

	vertices = new vertex_t[vertexCount];

	unsigned int currentVertex = 0;
	for(int x = 0; x < xSize; x++)
		for(int y = 0; y < ySize; y++)
			for(int z = 0; z < zSize; z++)
			{
				//				cout << (int)get(x+1, y, z).type << " ";
				if(get(x,y,z).type != BLOCK_AIR)//we dont need to check air blocks, you dont see them anyway ;)
				{
					glm::vec3 pos = glm::vec3(x + xOff, y + yOff, z + zOff);
					//7				6	5			4		 3			2	   1   0
					//visible		right	left bottom back top front
					//get(x,y,z).visible = 0b10000000;

					//right
					if(get(x+1, y, z).type == BLOCK_AIR)// || get(x+1, y, z).visible == 0)
					{
						//get(x,y,z).visible |= 0b10100000;
						steps++;
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f,-.5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);//near lower
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f,-.5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);//far lower
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f, .5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);//far upper
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f, .5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);//near upper
					}
					//left
					if(get(x-1, y, z).type == BLOCK_AIR)// || get(x-1, y, z).visible == 0)
					{
						//get(x,y,z).visible |= 0b10010000;
						steps++;
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f,-.5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);//far lower
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f,-.5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);//near lower
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, .5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);//near upper
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, .5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);//far upper
					}
					//bottom
					if(get(x, y-1, z).type == BLOCK_AIR)// || get(x, y-1, z).visible == 0)
					{
						//get(x,y,z).visible |= 0b10001000;
						steps++;
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, -.5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);//far left
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f, -.5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);//far right
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f, -.5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);//near right
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, -.5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);//near left
					}
					//back
					if(get(x, y, z-1).type == BLOCK_AIR)// || get(x, y, z-1).visible == 0)
					{
						//get(x,y,z).visible |= 0b10000100;
						steps++;
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f,-.5f,-1.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);//lower right
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f,-.5f,-1.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);//lower left
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, .5f,-1.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);//upper left
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f, .5f,-1.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);//upper right
					}
					//top
					if(get(x, y+1, z).type == BLOCK_AIR)// || get(x, y+1, z).visible == 0)
					{
						if(mergeFaces)
						{
							if(!(get(x,y,z-1).visible & 0b00000010) && !(get(x,y,z-1).visible & 0b01000000)) //if top of previons block isnt visible(!!!) && block wasnt handled before
							{
								//get(x,y,z).visible |= 0b10000010;
								//7				6	5			4		 3			2	   1   0
								//visible		right	left bottom back top front
								//TODO
								steps++;

								int zMerge = 0;
								while((get(x,y,z + zMerge).visible & 0b00000010) || zMerge > zSize)//while end of plane not reached || zMerge > zSize
								{
									get(x,y,z + zMerge).visible |= 0b01000000;
									zMerge++;
								}
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
								vertices[currentVertex++] = vertex_t(glm::vec3( .5f,.5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);//near left
								vertices[currentVertex++] = vertex_t(glm::vec3(-.5f,.5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);//near right

								vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, .5f, 0.f)+pos+glm::vec3(0,0,zMerge-1), blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);//far right
								vertices[currentVertex++] = vertex_t(glm::vec3( .5f, .5f, 0.f)+pos+glm::vec3(0,0,zMerge-1), blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);//far left
							}
						}
						else
						{
							//vertices[currentVertex++] = vertex_t(glm::vec3( 0.f, 1.f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);//near left
							//vertices[currentVertex++] = vertex_t(glm::vec3( 1.f, 1.f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);//near right
							//vertices[currentVertex++] = vertex_t(glm::vec3( 1.f, 1.f, 1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);//far right
							//vertices[currentVertex++] = vertex_t(glm::vec3( 0.f, 1.f, 1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);//far left
							vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, .5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);
							vertices[currentVertex++] = vertex_t(glm::vec3( .5f, .5f, 0.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);
							vertices[currentVertex++] = vertex_t(glm::vec3( .5f, .5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);
							vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, .5f,-1.f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);
						}
					}
					//front
					if(get(x, y, z+1).type == BLOCK_AIR)// || get(x, y, z+1).visible == 0)
					{
						//get(x,y,z).visible |= 0b10000001;
						steps++;
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f,-.5f, 0.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERLEFT]);//lower left
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f,-.5f, 0.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + LOWERRIGHT]);//lower right
						vertices[currentVertex++] = vertex_t(glm::vec3( .5f, .5f, 0.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERRIGHT]);//upper right
						vertices[currentVertex++] = vertex_t(glm::vec3(-.5f, .5f, 0.0f) + pos, blockTexCoord[(get(x,y,z).type *4-4) + UPPERLEFT]);//upper left
					}
				}
			}
	//cout << "vertices allocated: " << vertexCount << endl;
	//cout << "vertices processed: " << currentVertex << endl;

	return currentVertex;
}

void motor::Chunk::uploadToVbo()
{
	GLsizeiptr const vertexSize = vertexCount * sizeof(vertex_t);

	glDeleteBuffers(1, &vertexBuffer);
	glGenBuffers(1, &vertexBuffer);
	//cout << vertexBuffer << endl;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//cout << "vertex size: " << vertexSize << " vertices:" << vertices << endl;
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int motor::Chunk::getVertexCount()
{
	return vertexCount;
}
