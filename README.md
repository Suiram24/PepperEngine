# Pepper Engine
___
## Description
PepperEngine is a simple game engine made for the UQAC 8INF935 course by Marius Bozane, Alexandre Viala and Benoît Miège.

## How to build
For now, you need to have the Vulkan SDK installed on your machine (will fix this later).
Then, just clone the repo, open the CMakeLists.txt with visual studio and generate the PepperEngine executable.

## Coding Standart (_WIP_)

A few simple rules to follow:


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
You can enable doxygen-style comments in visual studio (Tools > Options > Text Editor > C/C++ > General > "Doxygen (/\*\*)").   
You can then type " /\*\* " to generate a comment block.

Exemple:

```cpp

/**
 * @brief Singleton used to setup render libs and render frames.
*/
class CPeRenderer
{
public:
    /**
    * @brief Setup ImGui, GLFW and Vulkan
    * @return 0 if setup finished correctly, 1 otherwise
    */
    int RenderSetup();
    
protected:
private:


public:
    GLFWwindow* m_window = nullptr;	/// Pointer to the main GLFW window
    ImGuiIO* m_io = nullptr;		/// Pointer to the ImGUI I/O
protected:
private:
}
```

### Variables and Functions names

- Never start a variable with an underscore or put double underscore in it.
- Use camelCase
- Functions start with a capital letter 
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
