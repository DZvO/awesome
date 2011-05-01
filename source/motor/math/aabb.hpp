#include <motor/math/glm/glm.hpp>
#include <cmath>
using namespace std;

namespace motor
{
	class AABB
	{
		public:
			AABB();
			AABB(glm::vec3 min, glm::vec3 max);

			bool intersects(AABB& checkAgainst);
			static bool intersects(AABB& aabb1, AABB& aabb2);

			bool isVecInside(glm::vec3& v);
			static bool isVecInside(AABB& aabb, glm::vec3& v);
			glm::vec3 center();

			glm::vec3 min;
			glm::vec3 max;
	};
}

/*								max
 *							 /
 *		 o--------o 
 *		/				 /|
 *	 /				/ |
 *	o--------o  |
 *	|				 |  |
 *	|	 aabb	 |  o
 *	|				 | /
 *	|				 |/
 *	o--------o
 *  |
 *  min
 */
