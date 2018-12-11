#ifndef ICOMPONENT_HPP
# define ICOMPONENT_HPP

namespace RType {
    class IComponent {
        public:
            virtual ~IComponent() = default;

            virtual int getEntityId() = 0;

        private:
            int _id;
    };
} // RType

#endif  /* !ICOMPONENT_HPP  */