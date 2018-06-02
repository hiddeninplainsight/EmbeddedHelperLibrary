#ifndef EMBEDDEDHELPERLIBRARY_CRTP_H
#define EMBEDDEDHELPERLIBRARY_CRTP_H

namespace ehl
{
	template <typename T, typename Tag>
	struct crtp
	{
		T& derived_object()
		{
			return static_cast<T&>(*this);
		}
		T const& derived_object() const
		{
			return static_cast<T const&>(*this);
		}
	};
}

#endif  // EMBEDDEDHELPERLIBRARY_CRTP_H
