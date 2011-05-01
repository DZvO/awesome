#ifndef _PLOT_HPP
#define _PLOT_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
using namespace std;

#include <motor/math/glm/glm.hpp>

namespace motor
{
	struct node_t
	{
		list<glm::vec2> points;
		bool showPoints;
		bool fill;
		float stepping;
		float delta;
	};

	class Plot
	{
		public:
			Plot();
			void addNode(string descr, bool showPoints = false, bool fill = false);
			void setStep(float stepping, string descr);

			void add(float y, string descr);
			void add(glm::vec2 v, string descr);
			void close();
			~Plot();
		private:
			map<string, node_t> nodes;
			fstream out;
			float yMin, yMax;
			float xMin, xMax;
	};
}

#endif
