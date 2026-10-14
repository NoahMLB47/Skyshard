# GDV4001 Assignment Template (2025-2026)

Template for WRIT1 / PRAC1 Game System Fundamentals (GDV4001). 

# Index #

1. [Documentation](documentation/Documentation.md)
   1. [Game Design Document](documentation/GDD.md)
   2. [Technical Design Document](documentation/TDD.md)
   3. [Closing Kit](documentation/CK.md)
2. Linux - Linux build (currently the base project)
3. Windows VS2022 - Windows VS build (currently the base project)

# Assignment Overview #

## WRIT 1 ##

For WRIT1 you are expected to complete the Game Design Document (GDD) only, though you may update the production plan and testing sections of the Technical Design Document (TDD) if you wish. 

Please see the brief on Moodle for more details!

## PRAC 1 ##

You are expected to complete the TDD and Closing Kit (CK), and provide a suitable prototype for your game. 

You have the option to build the assignment up as we go in this repository, or work in another repository and copy in the code when we finish building the little engine we create over the course of the workshops. 

Please see the brief on Moodle for more details!

# VERSION INFO #

|Operating System|SDL2 Version|SDL2_image Version|Status|
|:--|---|---|:-:|
|Linux|2.20.11|2.8.4|**DONE**|
|Windows|2.20.11|2.8.4|**DONE**| 

# INSTRUCTIONS #

At present I'm maintaining a version for Command Line Linux and Visual Studio 2022 only, if other versions are required let me know and I'll set them up.  

The build environment on Windows takes a bit of setting up if you want to do it all yourself, however, I will provide a video detailing the setup process for anyone who wants to setup their project from scratch. 

## Visual Studio 2022 ##
   
There should be no additional steps, a post-build process will copy the required dll files to the output directory and the debugger is set to run from there.  

## Linux ##

Make sure you have the these packages installed:
```
sdl2
sdl2-devel
sdl2_image
sdl2_image-devel
```

Package names may vary on other flavours of Linux (these are the Fedora ones). 

1. Open a terminal in the Linux folder (or via MS Code)
2. Compile ```make```
3. Run ```./game```

Debugging via gdb is possible but painful, consider using an editor if required. 


 
