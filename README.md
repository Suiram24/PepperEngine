# Pepper Engine
___
## Description
PepperEngine is a simple game engine made for the UQAC 8INF935 course by Marius Bozane and Alexandre Viala.

## How to build
For now, you need to have the Vulkan SDK installed on your machine (will fix this later).
Then, just clone the repo, open the CMakeLists.txt with visual studio and generate the PepperEngine executable.

## Coding Standart (_WIP_)

A few simple rules to follow:



### File Headers 

Files headers should look like that:

//TODO

### Namespaces

'using' should NEVER be used, as it may create collision in the future.
```cpp
using std //Wrong, never do this
```
Instead, you can safly use namespace aliases :
```cpp
namespace erv = engine::render::vulkan;

std::cout << "Hello" << '\n';
erv::AVulkanFunction();

// or 

namespace engine 
{
    namespace render 
    {
        std::cout << "Hello" << '\n';
        vulkan::AVulkanFunction();
    }
}
```



### Comments

You should always comment your classes/functions/variables.   
Exemple:

//TODO

### Variables names

- Never start a variable with an underscore or put double underscore in it.
- Use camelCase 
- Class member should start with 'm_'
- Function parameter should start with 'p_'
- Internal classes start with 'CPe'

CPeSomething.h :
```cpp
#ifndef PEENGINE_CPESOMETHING_H
#define PEENGINE_CPESOMETHING_H

namespace something
{
    namespace consts
    {
        int myConst = 21;
    }

    class CPeSomething
    {

    public:
        CPeSomething();

        DoSomething(int p_withThis);

    protected:
    private:
        InternalFunction();

    public:
        
        bool m_isThisTrue;
    protected:
    private:
        int m_count;
    }
}

#endif /* PEENGINE_CPESOMETHING_H */

```

CPeSomething.pp :
```cpp

#include "CPeSomething.h"

namespace something
{
    
    CPeSomething::CPeSomething(): m_isThisTrue(false), m_count(0)
    {

    }

    CPeSomething::DoSomething(int p_withThis)
    {
        if (p_withThis < consts::myConst)
        {
            InternalFunction();
        }
        else
        {
            m_isThisTrue = true;
        }
        
    }

    CPeSomething::InternalFunction()
    {
        ++m_count;
    }
}

```