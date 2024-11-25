How To Build
============

## Prerequisite

* Windows 11
* Unity Editor 2022.3

## Instructions

* Open a project by Unity Editor
* In the `Player Settings` dialog, check the `Allow unsafe code` option
* In the `Player Settings` dialog, set the audio sampling rate to `44100`
* Double click and load the `MainScene` scene
* Tie the `OpenNovelScript` game object to the script `OpenNovelScript.cs`
* Run preview

## About Custom DLL

* To run a game on a gaming console, you need to build a custom DLL
* Please recompile `libopennovel.dll` by a target SDK
* There are some examples in `suika2/engines/unity/Makefile`
