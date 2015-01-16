/*!
@file
Defines `boost::hana::models` and related syntactic sugar.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_MODELS_HPP
#define BOOST_HANA_CORE_MODELS_HPP

#include <boost/hana/core/datatype.hpp>
#include <boost/hana/core/method.hpp>
#include <boost/hana/detail/std/is_same.hpp>
#include <boost/hana/fwd/bool.hpp>


namespace boost { namespace hana {
    //! @anchor group-core-models
    //! @ingroup group-core
    //! Return whether a C++ type is a model of the given concept.
    //!
    //! Specifically, `models<Concept, T>` is a compile-time `Logical`
    //! representing whether the data type of `T` is a model of `Concept`.
    //! Note that in the case where `Concept` has semantic requirements
    //! (e.g. laws), those are not checked; only the syntactic requirements
    //! are checked.
    //!
    //! Also note that a data type `D` can be seen as a concept whose models
    //! are exactly the C++ types `T` such that `datatype<T>::type` is `D`.
    //! `models` is faithful to this interpretation of data types as concepts
    //! and hence `models<D, T>` is a compile-time `Logical` representing
    //! whether `datatype<T>::type` is `D` when `D` is a data type.
    //!
    //! ### Example
    //! @snippet example/core/models.cpp main
    //!
    //!
    //! For convenience, `models<DatatypeOrConcept>` (note the lack of a
    //! second template argument) is a function object applying `models`
    //! to the type of its argument. In other words,
    //! @code
    //!     models<Concept>(x) == models<Concept, decltype(x)>
    //! @endcode
    //!
    //! ### Example
    //! @snippet example/core/models.cpp as_function
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Concept [, typename T]>
    constexpr auto models = tag-dispatched;
#else
    BOOST_HANA_METHOD(models_impl);

    template <typename D, typename ...T>
    constexpr auto models = sizeof...(T) > 1 ?
        throw "too many template arguments to hana::models" : 0;

    template <typename D, typename T>
    constexpr auto models<D, T> = bool_<
        dispatch<models_impl<D>>::template apply<
            typename datatype<T>::type
        >
    >;

    template <typename D>
    struct _models {
        template <typename T>
        constexpr auto operator()(T const&) const
        { return models<D, T>; }
    };

    template <typename D>
    constexpr _models<D> models<D>{};

    template <typename D, typename Context>
    struct dispatch_impl<4, models_impl<D>, Context> {
        using type = dispatch_impl;
        template <typename T>
        static constexpr bool apply = detail::std::is_same<D, T>::value;
    };
#endif

    //! @ingroup group-core
    //! Syntactic sugar; equivalent to `models`.
    template <typename D, typename ...T>
    constexpr auto is_a = models<D, T...>;

    //! @ingroup group-core
    //! Syntactic sugar; equivalent to `models`.
    template <typename D, typename ...T>
    constexpr auto is_an = models<D, T...>;

    //! @ingroup group-core
    //! Syntactic sugar; equivalent to `models`.
    template <typename D, typename ...T>
    constexpr auto is = models<D, T...>;
}} // end namespace boost::hana

#endif // !BOOST_HANA_CORE_MODELS_HPP

#include <boost/hana/bool.hpp>
