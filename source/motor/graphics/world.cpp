#include "world.hpp"

motor::World::World()
{
	//perlin.SetOctaveCount(1);
	//perlin.SetFrequency(1.0);
	//perlin.SetPersistence(1.0);
	chunks = NULL;
}

void motor::World::load(unsigned int sizeX,unsigned int sizeY, unsigned int sizeZ, unsigned int chunkSizeX, unsigned int chunkSizeY, unsigned int chunkSizeZ)
{
	worldDimX = sizeX;
	worldDimY = sizeY;
	worldDimZ = sizeZ;
	this->chunkSizeX = chunkSizeX;
	this->chunkSizeY = chunkSizeY;
	this->chunkSizeZ = chunkSizeZ;

	chunks = new Chunk**[sizeX];
	for(unsigned int i = 0; i < sizeX; i++)
	{
		chunks[i] = new Chunk*[sizeY];
		for(unsigned int j = 0; j < sizeY; j++)
		{
			chunks[i][j] = new Chunk[sizeZ];
			for(unsigned int k = 0; k < sizeZ; k++)
			{
				chunks[i][j][k] = Chunk(chunkSizeX, chunkSizeY, chunkSizeZ);
				chunks[i][j][k].setWorldRef(this);
			}
		}
	}
}

motor::block_t& motor::World::getBlock(unsigned int x, unsigned int y, unsigned int z)
{
	static block_t outOfBorderBlock = block_t(BLOCK_DIRT, 0);
	if((x >= worldDimX * chunkSizeX || y >= worldDimY * chunkSizeY || z >= worldDimZ * chunkSizeZ))
	{
		//cout << "returning early!" << endl;
		return outOfBorderBlock;
	}
	//cout << "normal!" << endl;
	//cout << "x / 16:" << " y / 16:" << " z / 16:" << " x - ((x/16)*16):" << " y - ((y/16)*16):" << " z - ((z/16)*16):" << endl;
	//cout <<x / 16 << "  " << y / 16 << "  " << z / 16 << "  " << x - ((x/16)*16) << "  " << y - ((y/16)*16) << "  " << z - ((z/16)*16) << endl;
	
	//return block_t(BLOCK_DIRT, 0);
	return chunks[x / chunkSizeX][y / chunkSizeY][z / chunkSizeZ].get(x - ((x/chunkSizeX)*chunkSizeX), y - ((y/chunkSizeY)*chunkSizeY), z - ((z/chunkSizeZ)*chunkSizeZ));
}

void motor::World::setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int type)
{
	chunks[x / chunkSizeX][y / chunkSizeY][z / chunkSizeZ].set(x - ((x/chunkSizeX)*chunkSizeX), y - ((y/chunkSizeY)*chunkSizeY), z - ((z/chunkSizeZ)*chunkSizeZ), type);
}

void motor::World::generate()
{
	memoryAllocationRam = memoryAllocationGfx = 0;

	PerlinNoise base(0, 0, 0, 0, 123);
	base.setPersistence(0.4);
	base.setFrequency(0.4);
	base.setAmplitude(1.5);
	base.setOctaves(6);

	PerlinNoise mountains(0, 0, 0, 0, 321);
	mountains.setPersistence(1.0);
	mountains.setFrequency(0.1);
	mountains.setAmplitude(14.5);
	mountains.setOctaves(1);

	PerlinNoise sand(0.6, 0.15, 0.8, 3, 132);

	for (int z = 0; z < int(worldDimZ * chunkSizeZ); ++z)
		for (int x = 0; x < int(worldDimX * chunkSizeX); ++x)
		{
			float fBase = base.getHeight(x, z);
			float fMountains = mountains.getHeight(x, z);
			float fSand = sand.getHeight(x, z);

			float Height = (fBase) * worldDimY/ 4 + worldDimY / 2;
			Height += fMountains > 0 ? fMountains : 0;

			if(Height < 0)
				Height = 1;

			for (int y = 0; y < Height; ++y)
			{
				if(fMountains > 2)
					setBlock(x, y, z, BLOCK_DIRT);
				else if(Height == 1)
					setBlock(x, y, z, BLOCK_DIRT);
				else
					setBlock(x, y, z, BLOCK_STONE);
			}

			if(fSand > 0.5)
				setBlock(x, int(Height), z, BLOCK_SAND);
		}

	unsigned int vertices = 0;
	for(unsigned int i = 0; i < worldDimX; i++)
		for(unsigned int j = 0; j < worldDimY; j++)
			for(unsigned int k = 0; k < worldDimZ; k++)
			{
				vertices += chunks[i][j][k].calculateVisibleSides(i * chunkSizeX, j * chunkSizeY, k * chunkSizeZ);
				chunks[i][j][k].uploadToVbo();

				memoryAllocationRam += chunks[i][j][k].memoryAllocationRam;
				memoryAllocationGfx += chunks[i][j][k].memoryAllocationGfx;
			}
	cout << worldDimX * worldDimY * worldDimZ << " chunks, " << vertices << " vertices, with a ";
	cout << "total of " << float(memoryAllocationRam) / 1000.f << " kB RAM, " << float(memoryAllocationGfx) / 1000.f << " kB Gfx memory used (probably more :>)" << endl;
}

void motor::World::draw(unsigned int positionAttrib, unsigned int texcoordAttrib)
{
#define _OFFSET(i) ((char *)NULL + (i))
	//	glPolygonMode(GL_FRONT, GL_LINE);
	for(unsigned int i = 0; i < worldDimX; i++)
		for(unsigned int j = 0; j < worldDimY; j++)
			for(unsigned int k = 0; k < worldDimZ; k++)
			{
				glEnableVertexAttribArray(positionAttrib);
				glEnableVertexAttribArray(texcoordAttrib);

				glBindBuffer(GL_ARRAY_BUFFER, chunks[i][j][k].vertexBuffer);
				glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), _OFFSET(0));
				glVertexAttribPointer(texcoordAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), _OFFSET(sizeof(glm::vec3)));
				glDrawArrays(GL_QUADS, 0, chunks[i][j][k].getVertexCount());
			}
}
