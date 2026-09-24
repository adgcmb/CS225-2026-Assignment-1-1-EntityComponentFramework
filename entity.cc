#include "entity.hh"

int Entity::component_count()
{
    return components.size();
}

void Entity::attach(Component* rhs)
{
    components.push_back(rhs);
    rhs->set_owner(this);
}
void Entity::attach(Component& rhs)
{
    components.push_back(&rhs);
    rhs.set_owner(this);
}

Component& Entity::operator[](int index)
{
    return *components.at(index);
}