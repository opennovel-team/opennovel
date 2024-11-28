OpenNovel Tutorial
==================

## Introduction

This tutorial shows how to make a visual novel with OpenNovel.

It's very easy and takes just one hour.

## Setup

Download the latest release.

## Examining a Sample

Open a sample project folder.
It contains all necessary visual novel elements.
The following is our project folder structure.

|Name           |Role                                  |
|---------------|--------------------------------------|
|txt            |Story script files.                   |
|bg             |Background image files.               |
|ch             |Character image files.                |
|rule           |Transition rule image files.          |
|cg             |Other image files.                    |
|bgm            |BGM audio files.                      |
|se             |Sound effect audio files.             |
|cv             |Voice audio files.                    |
|anime          |Animation script files.               |
|gui            |GUI menu script files.                |
|font           |Font files.                           |
|wms            |WMS script files.                     |
|mov            |Video files.                          |
|project.txt    |Project setting file.                 |

## Showing a Background Image

The scenario file that is executed at boot time is `txt/init.txt`.
Here, we'll edit the file.
Remove the contents, then copy-and-paste the following.

```
@bg sakura.png 1.0
```

After that, run the game.

You'll see the rooftop image.

* `@bg` is a command to show backgrounds.
* `roof.png` is a file name in the `bg` folder.
* `1.0` indicates the transition takes one second.

## Showing a Character Image

Remove the content of `init.txt`, then copy-and-paste the following.

```
@bg roof.png 1.0
@ch center chara001.png 1.0
```

After that, run the game.

You'll first see the rooftop background image, then a character image.
After clicking the screen, game will close.

* `@ch` is a command to show a character.
* `center` means a horizontal position.
* `chara001.png` is a file name in the `ch` folder.
* `1.0` indicates the transition takes one second.

## Showing a Message

Remove the content of the `init.txt` file, then copy-and-paste the following.
After that, run the game.

```
@bg roof.png 1.0
@ch center chara001.png 1.0
A message shows a text in the message box.
*Name*A line shows a name in a name box and a text in a message box.
*Name*001.ogg*A voice file can be played.
```

You'll see messages.

## Playing a Music File

Remove the content of the `init.txt` file, then copy-and-paste the following.

```
@bgm adventure.ogg
@bg roof.png 1.0
@ch center chara001.png 1.0
```

After that, run the game.

You'll hear a background music.

* `@music` is a command to play a background music.
* `01.ogg` is a file name in the `bgm` folder.

Music files should be 44.1kHz Ogg Vorbis format.
Either stereo or monaural ones are acceptable.

## Showing options

Remove the content of the `init.txt` file, then copy-and-paste the following.

```
@bg roof.png 1.0
@ch center chara001.png 1.0
I'm going to my school.
@choose WALK "I'll take a walk." BIKE "I'll ride my bike."
:WALK
OK, I'll walk.
@goto end
:BIKE
OK, I'll ride my bike.
@goto end
:end
```

After that, run the game.

You'll see two options.

* `@choose` is a command to show options.
* `WALK` and `BIKE` are our option target labels for when a option is selected.
* A label and sine text next to it form a pair.
* `:WALK` is a label.

### Better Way to Write Options

You may ommit labels.

```
@bg roof.png 1.0
@ch center chara001.png 1.0
I'm going to my school.

<<<
switch "I'll have a walk." "I'll ride my bike." {
case "I'll have a walk.":
    Ok, I'll walk.
    break
case "I'll ride my bike.":
    Ok, I'll ride my bike.
    break
}
>>>
```

## Branching a Scenario

Next, we'll branch a story by using a flag.
Remove the content of the `init.txt` file, then copy-and-paste the following.

```
@bg roof.png 1.0
@ch center chara001.png 1.0

I'm going to my school.

<<<
switch "I'll have a walk." "I'll ride my bike." {
case "I'll have a walk.":
    Ok, I'll walk.
    @set $1 = true
    break
case "I'll ride my bike.":
    Ok, I'll ride my bike.
    break
}
>>>

@if $1 == false NO_MONEY

I found some money on the ground.

:NO_MONEY
```

After that, run the game.

You'll see "I found some money on the ground." when you chose "I'll have a walk."

### Flags

We used `@set` and `@if` here.

For `@set`:
* `@set` is a command to set a flag.
* `$1 = true` means raising a flag on the variable number `1`.
* The initial values of variables are all `0`.

For `@if`:
* `@if` is a command to branch by a condition.
* `$1 == false` means a condition where the variable `$1` is `false`.
* `NO_MONEY` is a destination to go to when the condition is met.

### Better Way to Write a Branch

You can write a branch without labels.

```
<<<
if $1 == 0 {
  I found some money.
}
>>>
```

## Showing a Menu Screen

Remove the content of the `init.txt` file, then copy-and-paste the following.

```
@menu title.txt
:START
:LOAD
:CONFIG
:QUIT
```

After that, run the game.

You'll see a menu screen.

* `@menu title.txt` is a command to call a menu script.
* Here, we call `title.txt` in the `gui/code> folder.

Refer to [GUI](gui.html) for more information.

## Dividing a scenario file

You can divide a scenario file.
Make a copy of the `init.txt` file in the `txt` folder, then rename it to `second.txt`.

Copy-and-paste the following, then run the game.

* `init.txt`:
```
@bg roof.png 1.0
@ch center chara001.png 1.0
We are in init.txt.
@story second.txt
```

* `second.txt:`
```
We move to second.txt.
```

You'll see that you have moved to `second.txt`.
