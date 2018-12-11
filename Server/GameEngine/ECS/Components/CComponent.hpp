#ifndef CCOMPONENT_HPP
# define CCOMPONENT_HPP

namespace RType {
    enum EComponent {
        
    };

    class CComponent {
        public:
            static const int _defaultHealth = 50;
            static const int _maximumHealth = 100;
            static const int _minimumHealth = 0;

            static const bool _defaultMovable = true;
            static constexpr float _defaultSpeed = 1;
            static constexpr float _maximumSpeed = 2;
            static constexpr float _minimumSpeed = 0;
    };
} // RType

#endif  /* !CCOMPONENT_HPP  */