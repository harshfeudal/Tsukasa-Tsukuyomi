# Tsukasa Tsukuyomi

<div align="center">

A C++ anime moderation Discord bot, using D++ library version 10.0.23. For more information about this library's features, you can view them [here](https://github.com/brainboxdotcc/DPP).

</div>

### 📝 About this project

- This repository is under construction! I'll update it as soon as possible.
- This bot is currently working with deep learning using the OpenCV library. I am currently working on it with my team (a small team, not a big company; this project is just for fun).
- As always, I'm not recommending you to use C++ to code a Discord bot instead of JavaScript or other libraries. To understand how this project works, you should learn some basics about C++ so that you can know what I am doing.

### 📚 Libraries and versions

These are the libraries that we're using in this project:

- [Dpp](https://github.com/brainboxdotcc/DPP) - version `10.0.23` (latest)
- [Spdlog](https://github.com/gabime/spdlog) - version `1.11.0` (latest)
- [Base64 (extracted)](https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594)
- [OpenCV](https://github.com/opencv/opencv)

I myself coded the `dotenv.h` header. If you want to use it, please remember to copy the `MIT-LICENSE` below.

### 🚨 Build and run

#### I. Build on Visual Studio with Premake

To build on Visual Studio, you can just simply generate it using [Premake 5](https://premake.github.io/).

**Steps to follow:**

1. To download `premake5.exe`, you can click [here](https://premake.github.io/download).

2. Generate it. If you don't know how to use it, you can find instructions [here](https://premake.github.io/docs/Using-Premake/).

    - If you're still unable to generate it: After installing `premake5.exe`, please put it in the directory where you can find the `.env.example` file.

    - In the search bar from file explorer, type `cmd` to open the command prompt.

    - Because you are standing in the directory where `premake5.exe` is located, the command prompt is navigating in that directory. Simply type `premake5 [action]` to generate the `.sln` file for Visual Studio. Check your Visual Studio version and generate based on this table:

        | Action      | Description                                       |
        |-------------|---------------------------------------------------|
        | vs2022      | Generate Visual Studio 2022 project files         |
        | vs2019      | Generate Visual Studio 2019 project files         |
        | vs2017      | Generate Visual Studio 2017 project files         |
        | vs2015      | Generate Visual Studio 2015 project files         |
        | vs2013      | Generate Visual Studio 2013 project files         |
        | vs2012      | Generate Visual Studio 2012 project files         |
        | vs2010      | Generate Visual Studio 2010 project files         |
        | vs2008      | Generate Visual Studio 2008 project files         |
        | vs2005      | Generate Visual Studio 2005 project files         |
        | gmake       | Generate GNU Makefiles (This generator is deprecated by gmake2) |
        | gmake2      | Generate GNU Makefiles (including [Cygwin][1] and [MinGW][2]) |
        | xcode4      | XCode projects |
        | codelite    | CodeLite projects |

    For example, I'm using Visual Studio Enterprise 2022, so I will type:

    
        ```console
            premake5 vs2022
        ```
    
3. Edit the `.env.example` to `.env`. Put your Discord bot token that **has been encoded into Base64**.

4. Build and run it!

#### II. Build on Visual Studio Code with CMake

To build with CMake, follow these commands:

```console
$ mkdir build
$ cd build
$ cmake -G "Visual Studio 17 2022" -A x64 ..
$ cmake --build . --config Release
```

Please note that I'm using the `x64 Release` build. You can change it if you want a different build.

### 📝 Please note

The OCR Engine is currently working and training. It may update on this repository as soon as possible when finish. You no need to add `opencv` library and `.dll`
because we haven't imported the code on here, and it has no affect on this current code.