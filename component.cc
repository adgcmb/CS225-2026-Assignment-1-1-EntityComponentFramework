#include "component.hh"

ICloneable::~ICloneable()
{

}

IPrintable::~IPrintable()
{

}

IComparable::~IComparable()
{

}

Component::~Component()
{

}
Component* Component::clone() const
{
    return new Component(*this);
}
bool Component::print() const
{
    printf("class Component(id %d)\n",id);
    return true;
}
bool Component::compare_to(IComparable& rhs) const
{
    Component& comp = (Component&) rhs;
    return (this->id == comp.id);
}
int Component::get_id()
{
    return id;
}
void Component::set_owner(Entity* rhs)
{
    owner = rhs;
}
Entity* Component::get_owner()
{
    return owner;
}