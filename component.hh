#pragma once

class Entity;

class ICloneable
{
    public:
        virtual ICloneable* clone() const = 0;
        virtual ~ICloneable();
};

class IPrintable
{
    public:
        virtual bool print() const = 0;
        virtual ~IPrintable();
};

class IComparable
{
    public:
        virtual bool compare_to(IComparable& rhs) const = 0;
        virtual ~IComparable();
};

class Component : public ICloneable, public IPrintable, public IComparable
{
    protected:
        int id;
        Entity* owner;
    public:
        Component() : id(0), owner(nullptr){}
        int get_id();
        Component* clone() const override;
        bool print() const override;
        bool compare_to(IComparable& rhs) const override;
        void set_owner(Entity* rhs);
        Entity* get_owner();
        virtual ~Component();
};