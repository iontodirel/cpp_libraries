# sai
**sai** is a general purpose C++ library designed for usability. **sai** is written to be immediately useful and usable, and tries to not put a burden on the programmers using it.
**sai** does not require a *buy in*, in that unlike other libraries or frameworks like Qt or .NET, it tries
not to have interdependecies between its parts as much as it is technically feasible. Each module from **sai** is designed to be used and usable on its own, each is meant to be its own beautiful snowflake.

**sai** is being written with the beliefs that writting C++ code can be as productive, and as easy to write and as beatiful as C#, Python, or other high level programming languages, famous for their productivity. I believe that that productivity comes from the rich libraries available to those languages, and **sai** is an experiment towards that end.
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
- Create awarness of C++ and promote and increase C++ usage
- **Modularity**. Modules are meant to be standalone, with as little interdependencies as possible... a file does not depend on a stopwatch or timer
- **Usability** and composability with C++, pluggability into C++, as a priority; **sai** is design to complement the standard library, not completely replace it
- No build system should be required, some modules are available as single header
- No external dependencies on other libraries
- **sai** is written to be immediately useful and usable, and not require a buy in, **sai** should be very cheap to use, integrate in other projects, or discard if not needed due to modularity and no dependencies goals
- **sai** follows the idea that simple things should be simple
- **Simplicity**. Althought I believe that simple thing should be simple, I also believe that large complex things can be made simple too, but possible at the expense of flexibility or performance. 
- **sai** is currently targetting C++17, and is always going to embrace the latest ISO C++ standard, as available in the compilers
- **sai** employs *simple* unit tests, and strongly believes in unit tests, without unit tests you can't dare have others use your library; Simple unit tests, in that I believe that the simplicty of the unit tests is important and unit tests in a way is your documentation and your code samples. I see a lot of libraries using fancy test frameworks and trying to automate things as much as they can through mecros, that's great. But in doing so, you can't read the unit tests just as easy, and you can't understand as easy how to use the library or the code.
- **sai** is not stable, APIs might change, toward better I hope
- performance is not the driving factor, but **sai** is not designed to be slow, if something is slower than expected it was not done intentionally so
- **sai** is meant to be comprehensive and rich
- **sai** is a work in progress, modules might be re-arranged 

## Other design choices
- Naming wise, **sai** follows a design similar to that of the C++ standard library, in that it uses short names, all lower_case names. 
- **sai** uses exceptions, but also accomodates code that uses error handling using return codes, when more predictability is needed; I also believe that in some places exceptions are unnatural, and error handling makes sense, **sai** will support both models simultaneously without needing to set a global flag or anything of sorts. Not all modules currently support both models, but that support is coming the the goal is to have support for error handling with both exceptions and error codes
- **sai** uses and will use OOP where it makes sense, including multiple-inheritance, but favors small hierarchies
- **sai** will support multiple Unicode encodings simultaneously, and does not need a global flag to choose or work with a specific encoding, or string type, like some libraries do; **sai** will use either a descriptor when picking an encoding to use, or will use the standard library strings as a tag for the encoding, std::string for UTF8, std::wstring and std::u16string for UTF16 and so on; in some cases only specific encodings might be supported due to the underlying system limitations; for example it doesn't make much sense to support UTF32 when writing to the Win32 registry
- **sai** will use polymorthic value types, so users don't have to worry about pointers or references, object slicing, copies, memory etc.
- **sai** will never return pointers to memory that users need to free or think about, **sai** will not require any memory management done by the users
- **sai** will not, now nor ever, introduce new string types; C++ does not have a string problem, C++ has a Unicode problem

## Inspiration

Boost, .NET, Node.js, Python, Go, D, Rust, Qt

# Modules 
- **stopwatch**, measures and records time, compatible with *chrono*
- **guid**, generates global unique identifiers, can parse and covert them to string 
- **version**, stores version information, can parse and covert them to string
- **random_string**, generates random strings of varying length

The current modules being worked on are *timer* and *file*, which are going to be published next. The modules after *format* and *thread_pool*.

# License
**sai** is licensed under a permissive MIT license.
