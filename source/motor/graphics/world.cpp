#include "world.hpp"

motor::World::World()
{
	//perlin.SetOctaveCount(1);
	//perlin.SetFrequency(1.0);
	//perlin.SetPersistence(1.0);
	chunks = NULL;
}

void motor::World::load(unsigned int sizeX,unsigned int sizeY, unsigned int sizeZ)
{
	xDim = sizeX;
	yDim = sizeY;
	zDim = sizeZ;
	chunks = new Chunk**[sizeX];
	for(unsigned int i = 0; i < sizeX; i++)
	{
		chunks[i] = new Chunk*[sizeY];
		for(unsigned int j = 0; j < sizeY; j++)
		{
			chunks[i][j] = new Chunk[sizeZ];
			for(unsigned int k = 0; k < sizeZ; k++)
			{
				chunks[i][j][k] = Chunk(16, 16, 16);
				chunks[i][j][k].setWorldRef(this);
			}
		}
	}
}

motor::block_t motor::World::getBlock(unsigned int x, unsigned int y, unsigned int z)
{
	if((x >= xDim * 16 || y >= yDim * 16 || z >= zDim * 16))
	{
		//cout << "returning early!" << endl;
		return block_t(BLOCK_DIRT, 0);
	}
	//cout << "normal!" << endl;
	//cout << "x / 16:" << " y / 16:" << " z / 16:" << " x - ((x/16)*16):" << " y - ((y/16)*16):" << " z - ((z/16)*16):" << endl;
	//cout <<x / 16 << "  " << y / 16 << "  " << z / 16 << "  " << x - ((x/16)*16) << "  " << y - ((y/16)*16) << "  " << z - ((z/16)*16) << endl;
	
	//return block_t(BLOCK_DIRT, 0);
	return chunks[x / 16][y / 16][z / 16].get(x - ((x/16)*16), y - ((y/16)*16), z - ((z/16)*16));
}

void motor::World::setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int type)
{
	chunks[x / 16][y / 16][z / 16].set(x - ((x/16)*16), y - ((y/16)*16), z - ((z/16)*16), type);
}

void motor::World::generate()
{
	PerlinNoise base(0, 0, 0, 0, 123);
	base.setPersistence(0.4);
	base.setFrequency(0.4);
	base.setAmplitude(2.5);
	base.setOctaves(6);

	PerlinNoise mountains(0, 0, 0, 0, 321);
	mountains.setPersistence(1.0);
	mountains.setFrequency(0.1);
	mountains.setAmplitude(6.5);
	mountains.setOctaves(2);


	float WORLD_SIZE = xDim;
	for (int z = 0; z < WORLD_SIZE * 16; ++z)
		for (int x = 0; x < WORLD_SIZE * 16; ++x)
		{
			float Height = (base.getHeight(x, z)) * WORLD_SIZE / 4 + WORLD_SIZE / 2;
			Height += mountains.getHeight(x, z);
			if(Height < 0)
				Height = 1;
			//float Height = (perlin.GetValue(x + 0.7, z, 0.0f)  + WORLD_SIZE /2) * 1.5f;
			for (int y = 0; y < Height; ++y)
			{
				//if(y > 3)
				//	setBlock(x, y, z, BLOCK_DIRT);
				//else
				setBlock(x, y, z, BLOCK_STONE);
			}
		}

	unsigned int vertices = 0;
	for(unsigned int i = 0; i < xDim; i++)
		for(unsigned int j = 0; j < yDim; j++)
			for(unsigned int k = 0; k < zDim; k++)
			{
				vertices += chunks[i][j][k].calculateVisibleSides(i * 16, j * 16, k * 16);
				chunks[i][j][k].uploadToVbo();
			}
	cout << vertices << " vertices" << endl;
}

void motor::World::draw(unsigned int positionAttrib, unsigned int texcoordAttrib)
{
#define _OFFSET(i) ((char *)NULL + (i))
//	glPolygonMode(GL_FRONT, GL_LINE);
	for(unsigned int i = 0; i < xDim; i++)
		for(unsigned int j = 0; j < yDim; j++)
			for(unsigned int k = 0; k < zDim; k++)
			{
				glEnableVertexAttribArray(positionAttrib);
				glEnableVertexAttribArray(texcoordAttrib);

				glBindBuffer(GL_ARRAY_BUFFER, chunks[i][j][k].vertexBuffer);
				chunks[i][j][k].draw();
				glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), _OFFSET(0));
				glVertexAttribPointer(texcoordAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), _OFFSET(sizeof(glm::vec3)));
				glDrawArrays(GL_QUADS, 0, chunks[i][j][k].getVertexCount());
			}
}
