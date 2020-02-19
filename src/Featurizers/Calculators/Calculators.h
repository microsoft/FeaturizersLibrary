// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \namespace     Calculators
///  \brief         Namespace containing calculators, or algorithms designed
///                 to process streaming data. A calculator's `update` method
///                 can be called while collecting data, and `commit` can be
///                 called once processing is complete. A Calculator may also
///                 implement functionality to `reset` its internal state to
///                 continue processing additional data.
///
namespace Calculators {

/////////////////////////////////////////////////////////////////////////
///  \class         CalculatorBase
///  \brief         Calculators are intended to be as light-weight as possible,
///                 yet still adhere to expected conventions (see the expected
///                 method list below). One option for this would be to make these
///                 Calculators polymorphic at runtime through the use of abstract
///                 methods. While this would help the compiler tell us when we haven't
///                 implemented some conventions (or the conventions themselves have
///                 changed), runtime polymorphism prevents the compiler/linker from
///                 making some aggressive optimizations spanning function invocations.
///                 So, we have introduced this class to enforce conventions at
///                 compile time and allow for more aggressive optimizations by
///                 the compiler/linker.
///
///                 Example Usage:
///
///                     class MyCalculator : public CalculatorBase<MyCalculator, int, int64> {
///                     private:
///                         friend class CalculatorBase<MyCalculator, int, int64>;
///
///                         // Implement these methods
///                         inline void update_impl(int value);
///                         inline int64 output_impl(void);
///                         inline void reset_impl(void);
///                     };
///
template <typename SuperClassT, typename InputT, typename OutputT>
class CalculatorBase {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CalculatorBase(void);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            update
    ///  \brief         Update the calculator's state with the provided data.
    ///
    template <typename ThisInputT>
    inline void update(ThisInputT && input);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            commit
    ///  \brief         Retrieve a result based on the calculator's current state.
    ///
    inline OutputT commit(void);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            reset
    ///  \brief         Reset the calculator's current state.
    ///
    inline void reset(void);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            execute
    ///  \brief         Convenience function that creates a local calculator
    ///                 instance, calls `update` for the provided range, then
    ///                 returns the result of `commit` on that calculator.
    ///
    template <typename InputIteratorT, typename... ConstructArgTs>
    static inline OutputT execute(InputIteratorT begin, InputIteratorT end, ConstructArgTs &&... constructArgs);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // Note that these methods will never be used, but they are declared here
    // so that super classes only have to declare friend access to this class rather
    // than a number of different helper classes (which is what would need to happen if
    // they weren't here).
    template <typename U> static constexpr std::false_type CheckForUpdateImpl(...);
    template <typename U>
    static constexpr std::true_type CheckForUpdateImpl(
        U *,
        typename std::enable_if<
            std::is_same<
                decltype(std::declval<U>().update_impl(std::declval<InputT>())),
                void
            >::value,
            void *
        >::type
    );

    template <typename U> static constexpr std::false_type CheckForCommitImpl(...);
    template <typename U>
    static constexpr std::true_type CheckForCommitImpl(
        U *,
        typename std::enable_if<
            std::is_same<
                decltype(std::declval<U>().commit_impl()),
                OutputT
            >::value,
            void *
        >::type
    );

    template <typename U> static constexpr std::false_type CheckForResetImpl(...);
    template <typename U>
    static constexpr std::true_type CheckForResetImpl(
        U *,
        typename std::enable_if<
            std::is_same<
                decltype(std::declval<U>().reset_impl()),
                void
            >::value,
            void *
        >::type
    );
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename SuperClassT, typename InputT, typename OutputT>
inline CalculatorBase<SuperClassT, InputT, OutputT>::CalculatorBase(void) {
    // Verify that the SuperClassT is valid now that the type is fully formed

    // update_impl
    static_assert(
        std::is_same<std::true_type, decltype(CheckForUpdateImpl<SuperClassT>(nullptr, nullptr))>::value,
        "'SuperClassT' must declare the member function 'inline void update_impl(InputT input)'"
    );

    // commit_impl
    static_assert(
        std::is_same<std::true_type, decltype(CheckForCommitImpl<SuperClassT>(nullptr, nullptr))>::value,
        "'SuperClassT' must declare the member function 'inline UpdateT commit_impl(void)'"
    );

    // reset_impl
    static_assert(
        std::is_same<std::true_type, decltype(CheckForResetImpl<SuperClassT>(nullptr, nullptr))>::value,
        "'SuperClassT' must declare the member function 'inline void reset_impl(void)'"
    );
}

template <typename SuperClassT, typename InputT, typename OutputT>
template <typename ThisInputT>
inline void CalculatorBase<SuperClassT, InputT, OutputT>::update(ThisInputT && input) {
    static_cast<SuperClassT &>(*this).update_impl(std::forward<ThisInputT>(input));
}

template <typename SuperClassT, typename InputT, typename OutputT>
inline OutputT CalculatorBase<SuperClassT, InputT, OutputT>::commit(void) {
    return static_cast<SuperClassT &>(*this).commit_impl();
}

template <typename SuperClassT, typename InputT, typename OutputT>
inline void CalculatorBase<SuperClassT, InputT, OutputT>::reset(void) {
    static_cast<SuperClassT &>(*this).reset_impl();
}

template <typename SuperClassT, typename InputT, typename OutputT>
template <typename InputIteratorT, typename... ConstructArgTs>
// static
inline OutputT CalculatorBase<SuperClassT, InputT, OutputT>::execute(InputIteratorT begin, InputIteratorT end, ConstructArgTs &&... constructArgs) {
    SuperClassT                             calculator(std::forward<ConstructArgTs>(constructArgs)...);

    while(begin != end)
        calculator.update(*begin++);

    return calculator.commit();
}

} // namespace Calculators
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
