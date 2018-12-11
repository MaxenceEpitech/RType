#ifndef CDAMAGING_HPP
# define CDAMAGING_HPP

#include "../../Interface/IComponent.hpp"

namespace RType {
    class CDamaging : public IComponent{
        public:
            virtual ~CDamaging() = default;
            CDamaging();
    };
} // RType

#endif  /* !CDAMAGING_HPP  */