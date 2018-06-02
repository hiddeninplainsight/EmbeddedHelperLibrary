#ifndef EMBEDDEDHELPERLIBRARY_LINEAR_INTERPOLATOR_H
#define EMBEDDEDHELPERLIBRARY_LINEAR_INTERPOLATOR_H

#include "span.h"
#include "algorithm.h"

namespace ehl
{
	template <typename Tx, typename Ty>
	struct linear_interpolator_coordinate
	{
		Tx x;
		Ty y;
	};

	template <typename Tx, typename Ty>
	class linear_interpolator
	{
	public:
		typedef linear_interpolator_coordinate<Tx, Ty> coordinate_type;
		typedef span<coordinate_type> coordinates_type;

	private:
		coordinates_type const coordinates;

		struct greater_than
		{
			Tx const x;
			greater_than(Tx x)
				: x(x)
			{
			}
			bool operator()(coordinate_type const& f) const
			{
				return f.x > x;
			}
		};

	public:
		linear_interpolator(coordinates_type coordinates)
			: coordinates(coordinates)
		{
		}

		Ty interpolate(Tx x) const
		{
			typename coordinates_type::const_iterator secondElement =
				ehl::find_if(coordinates.begin() + 1, coordinates.end() - 1,
							 greater_than(x));

			typename coordinates_type::const_iterator firstElement =
				secondElement - 1;

			Tx const x1 = firstElement->x;
			Ty const y1 = firstElement->y;

			Tx const dX = secondElement->x - x1;
			Ty const dY = secondElement->y - y1;

			Tx const xOffset = x - x1;

			Ty const numerator = static_cast<Ty>(xOffset) * dY;

			return y1 + (numerator / static_cast<Ty>(dX));
		}

		Ty operator()(Tx x) const
		{
			return interpolate(x);
		}
	};
}
#endif  // EMBEDDEDHELPERLIBRARY_LINEAR_INTERPOLATOR_H
