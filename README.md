# ZxEngine

The ZxEngine is a game engine in progress that aims to make C++ game development easier. It is designed to simplify code written by the end user while (hopefully) still providing a good performance boost compared to C# or other managed languages and still allowing you to dive deep into the graphics and window API to achieve anything you want. It also targets C++20 to use the modern features. However, because modules isn't fully complete yet and wont be for sometime, we are not writting the code to use them yet. However, once modules is feature complete, we will migrate a good portion of the code over to there to help will compile times and naming conflicts. 
 
Right now the engine only supports windows with opengl, and will be this way for a while, however, it is being designed with portability in mind allowing us to hook in other graphics and windows libraries into the language. 


# Libriaries We Use

 - glm as a math library, although it is wrapped with custom structures.
 - entt as the entity component system, however you will not need to write any code with entt.
 - glfw as a windows library
 - opengl for graphics rendering.
 
 
# Goals - Immediate

 - Reduce C++ code complexity while minimizing the compromises this inheritly brings. 
 - Intuitive and easy to learn surface API with more complex features under.
 - Separate thread renderering and multi-threaded system support.
 
 
# Goals - Long Term

 - Custom shader writting within C++
 - Editor for scene manipulation
 - Code editor that simplifies the code even more
 - C++ scripting
 - Code generation for easier integration with the editor
 
 
