# The sai C++ library
**sai** is a general purpose C++ library designed for usability. **sai** is written to be immediately useful and usable, and tries to not put a burden on the programmers using it.
**sai** does not require a *buy in*, in that unlike other libraries or frameworks like Qt or .NET, it tries
not to have interdependecies between its parts as much as it is technically feasible. Each module from **sai** is designed to be used and usable on its own, each is meant to be its own beautiful snowflake.

**sai** is being written with the belief that writting C++ code can be as productive, and as easy to write and as beatiful as C#, Python, or other high level programming languages, famous for their productivity. I believe that that productivity comes from the rich libraries available to those languages, and **sai** is an experiment towards that end.
I strongly believe that with the right, or more precisely, with a rich set of libraries that follow a consistent style, we can have productivity that rivals
that of the programming languages mentioned before.
I absolutely love C++, and I love being able to write more of it, in all sort of cases. I believe C++ should not be the language that we have to resort to
only when we need to write high performance code or when we need to maintain legacy code, whose authors often question their choices. C++ is a modern language, and C++ is evolving 
more than ever.

There are a lot of libraries for C++ out there, there is even a larger number of C libraries, that can be used directly from C++.
I think it's kind of sad that they all follow different styles and have different designs, and serve different purposes.
Each trying to introduce the same concept, or thing again, and again, for different reasons, or reinventing the wheel, because it's missing from the standard library. **sai** tries to provide a comprehensive and rich set of libraries, for everyone. On the other side, Windows for example provides a very large amount of APIs and features, C++ needs to tap into that in a modern, usable and easy way.

The name **sai** is a word play of the word "say", or "saying", which means we say, or express what we want to do, and the machine does it for us.

# The Philosphy of sai
- **sai** is open source, under a permissive license, and will remain that way
- **C++**. A driving factor from **sai** is creating awarness of **C++** and promote and increase C++ usage
- **Modularity**. **sai** is organized in **modules**, which is a header and/or a few source files each following the same name. Modules are meant to be standalone, with as little interdependencies as possible; a *file* does not depend on a *stopwatch* or *timer*
- **Usability** and composability with C++, pluggability into C++, as a priority; **sai** is design to complement the standard library, not replace it
- **Build systems, and sai integration in your projects**. No build system should be required. However, in some modules the reality is that even without dependencies, just writing code against the native platform might require a build system to resolve the system include headers, for example Windows.h. The compiler might also require specific include directories to even compile C++ code. In such cases, **sai** will offer build scripts for the native platform, and for CMake and other popular build systems. So that whatever build system you're using, you would not have to worry about it, and it should not be a bourden. On the other hand, today, the basic idea with supporting **sai** in your project, is that if you have code targeting Windows, for example, and it works, then inserting **sai** into your project should be as simple as including the **sai** source files into your project, with no additional configurations required to your build. In the long term, a more permamement solution will be required that fixes this problem.
- No external dependencies on other libraries
- **sai** is written to be immediately useful and usable, and not require a buy in, **sai** should be very cheap to use, integrate in other projects, or discard if not needed due to modularity and no dependencies goals
- **sai** follows the idea that simple things should be simple
- **Simplicity** and **simple complexity**. Althought I believe that simple thing should be simple, I also believe that large complex things can be made simple too, but possible at the expense of flexibility or performance. 
- **sai** is currently targetting C++17, and is always going to embrace the latest ISO C++ standard, as available in the compilers
- **sai** employs *simple* unit tests, and strongly believes in unit tests. Without unit tests you don't have an API or a library; Here by **simple unit tests**, I mean that I believe that the simplicty of the unit tests is important, and unit tests in a way are your documentation and your code samples. A lot of libraries are using fancy test frameworks and trying to automate things in the tests as much as they can, either through macros, or abstractions, and that's great. But in doing so, the unit tests are made less readable and leass easy to understand.
- **sai** is not stable, APIs might change
- performance is not the driving factor, but **sai** is not designed to be slow, if something is slower than expected it was not done intentionally so
- **sai** is meant to be comprehensive and rich
- **sai** is a work in progress, modules might be re-arranged 
- **Contributions**. contributions are welcomed, but at this time it's too early for that

## Other design choices
- Naming wise, **sai** follows a design similar to that of the C++ standard library, in that it uses short names, all lower_case names. 
- **Exceptions**. **sai** uses exceptions, but also accomodates code that uses error handling using return codes, when more predictability is needed; I also believe that in some places exceptions are unnatural, and error handling makes more sense, **sai** will support both models simultaneously without needing to set a global flag or anything of sorts. Not all modules currently support both models, but that support is coming the the goal is to have support for error handling with both exceptions and error codes
- **sai** uses and will use OOP where it makes sense, including multiple-inheritance, but favors small hierarchies
- **Unicode, character types and strings**. **sai** will support multiple Unicode encodings simultaneously, and does not need a global flag to choose or work with a specific encoding, or string type; **sai** will use either a descriptor when picking an encoding to use, or will use the standard library strings as a tag for the encoding, std::string for UTF8, std::wstring and std::u16string for UTF16 and so on; in some cases only specific encodings might be supported due to the underlying system limitations; for example it doesn't make much sense to support UTF32 when writing to the Win32 registry
- **sai** will use polymorphic value types, so users don't have to worry about pointers or references, object slicing, copies, memory etc.
- **Memory management**. **sai** will never return pointers to memory that users need to free or think about, **sai** will not require any memory management done by the users
- **sai** will not introduce new string types; I believe that C++ has a Unicode problem, not a string problem
- **sai** is meant to be cross-platform, but currently the focus is on adding modules as soon as possible, with cross platform support coming as it goes, some modules might be made cross platform sooner than others; currently the development focus is on Windows
- **Eventing** in **sai**. **sai** supports all sort of callback types, like function pointers, functors, std::function or lambdas. In some cases, as it's appropriate, the callback might be taken as templated arguments in the constructors, much like std::thread. There will also be member or non member functions using the following naming scheme: on_event_name, on_event_name_add, on_event_name_remove, on_event_name_clear, which will be responsible for adding and removing the event callbacks.
- **Properties** in **sai**. When getting or setting values, **sai** is simply using functions and names that do not start with get nor set. For example, for getting and setting a *name* in an object *obj*: *obj.name()*, *obj.name("name")*; The first function and call is the getter, and the second function is the setter.
- **sai** will rely on templates and metaprogramming to provide genericity and flexibility
- Some **sai** modules will be available as single header, the decision on that is mostly driven by the code size. And I'm still exploring if the modules that are not, should be made available in both flavors.

## Inspired by

Boost, .NET, Node.js, Python, Go, D, Rust, Qt

# Modules 
- **stopwatch**, measures and records time, compatible with *chrono*
- **guid**, generates global unique identifiers, can parse and covert them to string 
- **version**, stores version information, can parse and covert them to string
- **random_string**, generates random strings of varying length

The current modules being worked on are *timer* and *file*, which are going to be published next.

## Map of planned modules
- **test**, asserts, measurements, logging and reporting
- **build**, a build system as a library
- **camera**, a generic API for capturing images and streams from cameras, would support DirectShow, MediaFoundation, WIA and vendor specific APIs like Basler and Point Grey
- **imaging**, image transcoding and processing
- **crypto**, encryption and hashing
  - **hash**
- **json**
- **xml**
- **log**
- **net**
  - **socket**
  - **tcp**
  - **udp**
- **process**
- **registry**
- **env**
  - **args**
  - **environment_variable**
- **registry**
- **resources**, managing resources embedded into executables
- **uri**
- **unicode**
- **format**, simple string formatting
- **compression**
- **io**
  - **pipe**
  - **file**
  - **filesystem_watcher**
- **debug**
  - **pe**
  - **pdb**
  - **dwarf**
  - **elf**
  - **trace**, stack walker and logger
- **thread_pool**
- **timer**, execute functions at specific intervals

# License
**sai** is licensed under a permissive MIT license.
