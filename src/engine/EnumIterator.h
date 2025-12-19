// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_ENUMITERATOR
#define AUX_ENUMITERATOR

namespace AuxEngine
{
    /*
    * Enum Iterator can only be used by enums that inherit from an int-type.
    * Each step(increment/decrement) is a value of +1/-1, so enum should have values ascending or descending with no more than 1 in difference between values.
    * Does not perform range checks.
    */
    template<typename EnumType>
    class EnumIterator
    {
        int position_;
    public:
        EnumIterator(EnumType startPosition)
            : position_(static_cast<int>(startPosition))
        {};

        EnumType operator*() const
        {
            return static_cast<EnumType>(position_);
        };

        EnumIterator& operator++()
        {
            ++position_; 
            return *this;
        };

        EnumIterator& operator--()
        {
            --position_;
            return *this;
        };

        EnumIterator operator++(int)
        {
            EnumIterator copy(*this);
            ++copy;
            return copy;
        }

        EnumIterator operator--(int)
        {
            EnumIterator copy(*this);
            --copy;
            return copy;
        }

        bool operator!=(const EnumIterator& other) const
        {
            return position_ != other.position_;
        };
    };

    /* --  Example -- 
        for (EnumIterator<GamepadId> Enumerator(GamepadId::Gamepad1); Enumerator != GamepadId::MAX; ++Enumerator)
        {
            GamepadId EnumValue = *Enumerator;
        }
    */
}

#endif