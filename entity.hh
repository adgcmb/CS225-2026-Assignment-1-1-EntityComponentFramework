#pragma once

#include <vector>
#include "component.hh"

class Entity
{
    protected:
        std::vector <Component*> components;
 
    public:
        int component_count();
        void attach(Component* rhs);
        void attach(Component& rhs);
        Component& operator[](int index);
};