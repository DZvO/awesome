#ifndef _PERLIN_HPP
#define _PERLIN_HPP

namespace motor
{
	class PerlinNoise
	{
		public:

			// Constructor
			PerlinNoise();
			PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);

			// Get Height
			double getHeight(double x, double y) const;

			// Get
			double persistence() const { return m_persistence; }
			double frequency()   const { return m_frequency;   }
			double amplitude()   const { return m_amplitude;   }
			int    octaves()     const { return m_octaves;     }
			int    randomSeed()  const { return m_randomseed;  }

			// Set
			void set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);

			void setPersistence(double _persistence) { m_persistence = _persistence; }
			void setFrequency(  double _frequency)   { m_frequency = _frequency;     }
			void setAmplitude(  double _amplitude)   { m_amplitude = _amplitude;     }
			void setOctaves(    int    _octaves)     { m_octaves = _octaves;         }
			void setRandomSeed( int    _randomseed)  { m_randomseed = _randomseed;   }

		private:

			double total(double i, double j) const;
			double getValue(double x, double y) const;
			double interpolate(double x, double y, double a) const;
			double noise(int x, int y) const;

			double m_persistence, m_frequency, m_amplitude;
			int m_octaves, m_randomseed;
	};
}

#endif
