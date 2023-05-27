<div align="center"><img src="https://github.com/harshfeudal/Tsukasa-Tsukuyomi/assets/87577447/c767ec10-283b-427a-8158-ceae05b86740" alt="Tsukasa-Tsukuyomi" width="150" />

<h1>Tsukasa Tsukuyomi</h1>

A C++ anime moderation Discord bot, using D++ library version 10.0.24 (BETA version) <br />
For more information about this library's features, you can view them [here](https://github.com/brainboxdotcc/DPP).

[![GitHub issues](https://img.shields.io/github/issues/harshfeudal/Tsukasa-Tsukuyomi)](https://github.com/harshfeudal/Tsukasa-Tsukuyomi/issues)
[![GitHub license](https://img.shields.io/github/license/harshfeudal/Tsukasa-Tsukuyomi?color=brightgreen)](https://github.com/https://github.com/harshfeudal/Tsukasa-Tsukuyomi/blob/main/LICENSE)
[![GitHub stars](https://img.shields.io/github/stars/harshfeudal/Tsukasa-Tsukuyomi?color=brightgreen)](https://github.com/harshfeudal/Tsukasa-Tsukuyomi/stargazers)
[![Visual Studio](https://badgen.net/badge/VS/2022/3d3d44?icon=visualstudio&labelColor=purple)](https://visualstudio.microsoft.com/) <br />
[![Build status](https://ci.appveyor.com/api/projects/status/yjn4if9toapw3h2n?svg=true)](https://ci.appveyor.com/project/harshfeudal/tsukasa-tsukuyomi)
[![CMake](https://github.com/harshfeudal/Tsukasa-Tsukuyomi/actions/workflows/cmake.yaml/badge.svg?branch=master)](https://github.com/harshfeudal/Tsukasa-Tsukuyomi/actions/workflows/cmake.yaml)
[![MSBuild](https://github.com/harshfeudal/Tsukasa-Tsukuyomi/actions/workflows/msbuild.yaml/badge.svg?branch=master)](https://github.com/harshfeudal/Tsukasa-Tsukuyomi/actions/workflows/msbuild.yaml)

</div>

### 📝 About this project

- This repository is under construction! I'll update it as soon as possible.
- This bot is currently working with deep learning using the OpenCV library. I am currently working on it with my team (a small team, not a big company; this project is just for fun).
- As always, I'm not recommending you to use C++ to code a Discord bot instead of JavaScript or other libraries. To understand how this project works, you should learn some basics about C++ so that you can know what I am doing.

### 📚 Libraries and versions

These are the libraries that we're using in this project:

- [Dpp](https://github.com/brainboxdotcc/DPP) - version `10.0.24` (BETA version)
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

### 💻 Contribution and Pull Request

I'd probably glad to see if you have anything new to help and support me. To do that, please make one and before you do that, just make sure you've tested the code by using your bot. I won't bite you if you do it wrong, but just make sure that you have to test it clearly before I merge it.

### 📝 Please note

The OCR Engine is currently working and training. It may update on this repository as soon as possible when finish. You no need to add `opencv` library and `.dll`
because we haven't imported the code on here, and it has no affect on this current code.

<sub>
    © 2023 - Harshfeudal
</sub>

<br />

<sub>
    © 2018 - Kenjiro HATA/SHOGAKUKAN
</sub>
