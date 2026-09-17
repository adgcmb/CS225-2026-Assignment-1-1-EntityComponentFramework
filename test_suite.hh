/*! 
 * Test suite for the CS225 entity-component framework assigment.
 *
 * Contains the combined collection of tests for the assignment. 
 * Use this if you find it convenient to work with a single file that contains all the driver code.
 *
 * Modifications to this file are allowed only for development convenience (e.g. commenting out code
 * that fails to compile). This file will be used as provided during the grading process, so make sure
 * that your solution does not rely on any modification done on this file.
 *
 * If you want to disable a test, just comment it out. Bear in mind that the `TEST` macro makes it 
 * necessary to compile and run the test code, so both compilation and run time errors should
 * be taken into account.
 */
#include "test_helper.hh"
#include "testing.hh" // testing framework (ASSERT_THAT, etc.)
using namespace testing;

#include <string>       // std::string
#include <exception>    // std::exception
#include <stdexcept>    // std::out_of_range, std::invalid_argument
#include <typeinfo>     // std::bad_cast

// ===========================================================================
// ===========================================================================
// ===========================================================================

// Component, ICloneable, IPrintable, IComparable  
#include "component.hh" 

/*********************************************************************
 *                          Component tests                          *
 *********************************************************************/

namespace Tests 
{ 
    namespace Components
    {
        #ifdef ENABLE_COMPONENT_TEST1
        // minimum instantiable component
        class ConcreteComponent : public Component
        {
            public:
                ConcreteComponent(int i = 0) { id  = i; }
        };   

        // [ Test #1 ] -------------------------------------------------------
        TEST( "Component has a member property id that identifies the component",
            "Concrete components that inherits from Component class can access its id by the method get_id()" )
        {        
             printf("TEST1 Component class\n");

            ConcreteComponent cmp(1);
            cmp.get_id();
            
            printf("TEST1 Succeed!\n");
            SUCCEED();
        }
        #endif

        #ifdef ENABLE_COMPONENT_TEST2
        // [ Test #2 ] -------------------------------------------------------
        TEST( "Requirement description for making a component concrete and instantiable",
            "A ConcreteComponent class that inherites from Component class must be instantiable" )
        {
             printf("TEST2 Classes deriving from Component must be instantiable\n");

            ConcreteComponent concrete_component;
            
            // nothing to test, just make sure that this can compile and run
            printf("TEST2 Succeed!\n");
            SUCCEED();
        }
        #endif

        #ifdef ENABLE_COMPONENT_TEST3
        // [ Test #3 ] -------------------------------------------------------
        TEST( "Components can be cloned by overriding the corresponding function",
            "The cloning interface provides an operation that can act as a virtual constructor"  )
        {
             printf("TEST3 Components can be cloned\n");

            ConcreteComponent concrete_component(9);
            ICloneable * cloneable_interface = &concrete_component;

            ICloneable * cloned = cloneable_interface->clone();
            // cast so that we can access the 'type' method
            const Component * cloned_component = dynamic_cast<const Component *>(cloned);
            ASSERT_THAT( cloned_component != NULL );

            delete cloned_component;

            printf("TEST3 Succeed!\n");
            SUCCEED();
        }
        #endif

        #ifdef ENABLE_COMPONENT_TEST4
        // [ Test #4 ] -------------------------------------------------------
        TEST( "Components can be printed using an human readable string",
            "The IPrintable interface provides a print method" )
        {
            printf("TEST4 Components can be printable in a human readable text\n");

            ConcreteComponent concrete_component(9);
            IPrintable *printable = &concrete_component;

            // this is only for interface requirement purposes
            printable->print();

            printf("TEST4 Succeed!\n");
            SUCCEED();
        }
        #endif

        #ifdef ENABLE_COMPONENT_TEST5
        // [ Test #5 ] -------------------------------------------------------
        TEST( "Components can be compared to each other by overriding the corresponding function",
            "The comparison interface provides an entry point to compare all objects that belong to classes that implement it" )
        {
            printf("TEST5 Components can be comparable\n");

            ConcreteComponent concrete_component_a(3);
            ConcreteComponent concrete_component_b(3);

            IComparable& comparable = concrete_component_a;

            try
            {
                bool comparison_result = comparable.compare_to(concrete_component_b);
                ASSERT_THAT( comparison_result == true );

            } catch(const std::bad_cast&) {
                std::cerr << "operands are not compatible for comparison\n";
                FAIL();
            }
            
            printf("TEST5 Succeed!\n");
        }
        #endif
    } 
} // namespace Test::Component


// ===========================================================================
// ===========================================================================
// ===========================================================================

// Entity tests
#include "entity.hh" 

/*******************************************************************
 *                          Entity tests                           *
 *******************************************************************/

namespace Tests { 
    namespace Entities
    {
        #ifdef ENABLE_COMPONENT_TEST1
        using Tests::Components::ConcreteComponent;

        // concrete components for testing purposes
        class ConcreteComponentA : public ConcreteComponent
        {
            public:
            ConcreteComponent * clone() const { return new ConcreteComponentA(*this); }
            int a;
        };
        class ConcreteComponentB : public ConcreteComponent
        {
            public:
            ConcreteComponentB(int id) : ConcreteComponent(id) { b = id; }
            ConcreteComponent * clone() const { return new ConcreteComponentB(*this); }
            int b;
        };
        #endif

        #ifdef ENABLE_ENTITY_TEST6
        // [ Test #6 ] -------------------------------------------------------
        TEST( "Entities internally store a collection/container of components",
            "Entity method component_count() defines the number of components contained" )
        {
            printf("TEST6 Entities can contain components and their quantity can be obtained\n");

            Entity entity;
            
            // initially there should be 0 components
            ASSERT_THAT( entity.component_count() == 0u );

            printf("TEST6 Succeed!\n");
        }
        #endif

        #ifdef ENABLE_ENTITY_TEST7
        // [ Test #7 ] -------------------------------------------------------
        TEST( "Different concrete components can be attached to entities",
            "The attach function takes a pointer to a polymorphic instance, that internally is handled homogeneously" )
        {
            printf("TEST7 Components can be attached to Entities by pointer\n");

            Entity entity;

            entity.attach( new ConcreteComponentA() );
            entity.attach( new ConcreteComponentB(2) );
            entity.attach( new ConcreteComponentB(4) );

            ASSERT_THAT( entity.component_count() == 3u );

            printf("TEST7 Succeed!\n");
        }
        #endif

        #ifdef ENABLE_ENTITY_TEST8
        // [ Test #8 ] -------------------------------------------------------
        TEST( "Entity class provides an operation to inspect specific components",
            "The subscript operator [] is overloaded on the Entity class to provide access to components by index" )
        {
            printf("TEST8 Entities' subscript operator [] is overloaded \n");

            Entity entity;

            entity.attach( new ConcreteComponentA() );
            entity.attach( new ConcreteComponentB(2) );
            entity.attach( new ConcreteComponentB(4) );

            // check the component @ index 1
            Component& b2 = entity[1];
            
            ASSERT_THAT( b2.get_id() == 2);

            // downcast to access the derived data
            const ConcreteComponentB& ccb = dynamic_cast<const ConcreteComponentB&>(b2);
            ASSERT_THAT( ccb.b == 2 );

            printf("TEST8 Succeed!\n");
        }
        #endif

        #ifdef ENABLE_ENTITY_TEST9
        // [ Test #9 ] -------------------------------------------------------
        TEST( "Each entity has the responsibility of managing the components they get attached",
            "Cleaning up resources should be the owners responsibility. Check your memory leaks." )
        {
            printf("TEST9 Cleaning components attached to entities \n");

            Component * standalone_cmps[] =
            {
                new ConcreteComponentA, new ConcreteComponentB(1), new ConcreteComponentB(3),
                new ConcreteComponentB(11), new ConcreteComponentA, new ConcreteComponentB(0),
            };

            { // mind the scope
                Entity the_entity;
                for( unsigned int i = 0; i < 6; ++i )
                    the_entity.attach(standalone_cmps[i]);
            }

            printf("TEST9 Succeed!\n");
            SUCCEED();
        }
        #endif

        #ifdef ENABLE_ENTITY_TEST10
        // [ Test #10 ] -------------------------------------------------------
        TEST( "Components can be also attached by reference",
            "Provide an overloaded function for attach method that takes the appropriate type" )
        {
            printf("TEST10 Components can be also attached by reference \n");

            Entity the_entity;
            {
                ConcreteComponentA cmp_a;
                ConcreteComponentB cmp_b(2);
                the_entity.attach( cmp_a );
                the_entity.attach( cmp_b );
            }

            ASSERT_THAT( the_entity.component_count() == 2u );
            ASSERT_THAT(  the_entity[0].get_id() == 0 );
            ASSERT_THAT( the_entity[1].get_id()== 2 );

            printf("TEST10 Succeed!\n");
        }
        #endif

        #ifdef ENABLE_ENTITY_TEST11
        // [ Test #11 ] -------------------------------------------------------
        TEST( "Components can asign their respective owner entities",
            "All components internally store a pointer to their corresponding owners, for convenience" )
        {
            printf("TEST11 Components assign their respective owner entities \n");

            Entity the_entity;
            ConcreteComponentA cmpA;
            cmpA.set_owner(&the_entity);
        
            ASSERT_THAT( cmpA.get_owner() == &the_entity );

            printf("TEST11 Succeed!\n");
        }
        #endif

        #ifdef ENABLE_ENTITY_TEST12
        // [ Test #12 ] -------------------------------------------------------
        TEST( "Components can access their respective owner entities",
            "All components internally store a pointer to their corresponding owners, for convenience. An orphan component must return null" )
        {
            printf("TEST12 Components can obtain their respective owner entities, an orphan component must return null \n");

            Entity the_entity;
            the_entity.attach( new ConcreteComponentA() );
            the_entity.attach( new ConcreteComponentB(2) );

            ConcreteComponentA orphan_cmp;
            Component & owned_cmp = the_entity[0];

            ASSERT_THAT( orphan_cmp.get_owner() == nullptr );
            ASSERT_THAT( owned_cmp.get_owner() == &the_entity );

            printf("TEST12 Succeed!\n");
        }
        #endif
    } 
} // namespace Tests::Entity

