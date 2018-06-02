#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_CONTAINER_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_CONTAINER_H

#include "is_type_base.h"

namespace ehl
{
	namespace type_traits
	{
		template <class Cont>
		struct is_container : protected is_type_base
		{
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#endif
			template <typename C>
			static yes& HasSize(
				FunctionSignatureMatches<typename C::size_type (C::*)() const,
										 &C::size>* /*unused*/)
			{
			}
			template <typename>
			static no& HasSize(...)
			{
			}

			template <typename C>
			static yes& HasBegin(
				FunctionSignatureMatches<typename C::iterator (C::*)(),
										 &C::begin>* /*unused*/)
			{
			}
			template <typename>
			static no& HasBegin(...)
			{
			}

			template <typename C>
			static yes& HasEnd(
				FunctionSignatureMatches<typename C::iterator (C::*)(),
										 &C::end>* /*unused*/)
			{
			}
			template <typename>
			static no& HasEnd(...)
			{
			}

			template <typename C>
			static yes& HasElementAccess(
				FunctionSignatureMatches <
					typename C::reference (C::*)(typename C::size_type),
				&C::operator[]>* /*unused*/)
			{
			}
			template <typename>
			static no& HasElementAccess(...)
			{
			}

#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif

			static const bool value =
				(sizeof(HasSize<Cont>(0)) == sizeof(yes)) &&
				(sizeof(HasBegin<Cont>(0)) == sizeof(yes)) &&
				(sizeof(HasEnd<Cont>(0)) == sizeof(yes)) &&
				(sizeof(HasElementAccess<Cont>(0)) == sizeof(yes));
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_CONTAINER_H
