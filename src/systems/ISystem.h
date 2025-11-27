
#pragma once
#include <entt/entt.hpp>
#include <entt/poly/poly.hpp>

struct ISystem : entt::type_list<>
{
    template <typename Base>
    struct type : Base
    {
        void registerEvents() { this->template invoke<0>(*this); }
        void unregisterEvents() { this->template invoke<1>(*this); }
    };

    template <typename T>
    using impl = entt::value_list<&T::registerEvents, &T::unregisterEvents>;
};