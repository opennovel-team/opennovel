GUI
===

This page shows how to use the GUI feature of OpenNovel.

## Introduction

Let's dive into the sample project.

## Working With The Title Screen

In the `txt/init.txt` file, find `@gui title.txt`.
The title screen is created by the `@gui` command invoking the contents of `title.txt` file located within the `gui` folder.

## Contents of `title.txt`

Open the `gui/title.txt` file.
At the top of the file, you will see:

```
# Setting
global {
    # Use the following images.
    base:   title/idle.png;
    idle:   title/idle.png;
    hover:  title/hover.png;
    active: title/hover.png;

    # Fading-in time (seconds)
    fadein: 0.2;

    # Fading-out time (seconds)
    fadeout: 0.2;
}
```

|Command            |Meaning                                                         |
|-------------------|----------------------------------------------------------------|
|base:              |General basic layer. If not is specified, stage layers (e.g. background and characters) will be shown. If a file is specified, an image will be shown.|
|idle:              |An image to show when a the mouse cursor is not over a button.  |
|hover:             |An image to show when a button is pointed by a mouse.           |
|active:            |For sliders and toggle buttons. Not used in a simple title screen. Specify the same file as idle or hover if not used.|
|fadein:            |Fading-in time (second)                                         |
|fadeout:           |Fading-out time (second)                                        |
|clickcancel:       |Cancel the GUI when a non-button area is clicked.               |
|escapecancel:      |Cancel the GUI when the Esc key is pressed.                     |
|cancelse:          |Sound effect file for when canceled.                            |
|saveslots:         |Save data slots per screen. For the save and load screens.      |
|historyslots:      |History slots per screen. For the history screen.               |

### Base, Idle, and Hover Images

* We use images with a screen size instead of small per-button images.
* To create the images, use a painting software that supports image layers.

### Structure of title.txt

`title.txt` has descriptions for 3 buttons.

```
START {
    ...
}

LOAD {
    ....
}

CONFIG {
    ...
}
```

### Contents of the START Button

```
# START button
START {
    # Type: jump to a label
    type: goto;

    # Jump destination label
    label: START;

    # Position and size
    x: 2;
    y: 495;
    width: 314;
    height: 192;

    # Sound effect when pointed 
    pointse: btn-change.ogg;

    # Sound effect when clicked
    clickse: click.ogg;
}
```

### type: goto;

`type: goto;` means a goto jump will occur when the button is clicked.

`label: START;` means the jump destination is `:START`.

### Position and Size

Please check the position and size of your buttons on `Photoshop`, `CLIP STUDIO PAINT`, or similar software.

## Button Types

|Description                     |Meaning                                                                                                                                     |
|--------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
|type: goto;                     |Jumps to a label when pressed. A label must be specified by `label:`.                                                                       |
|type: gui;                      |Jumps to a GUI when pressed. A GUI must be specified by `file:`                                                                             |
|type: gallery;                  |Shown if a specified variable is not zero, jumps to a label when pressed. A variable must be specified by `var:`, and a label must be specified by `label:`.|
|type: mastervol;                |Shown as a master volume slider.                                                                                                            |
|type: bgmvol;                   |Shown as a BGM volume slider.                                                                                                               |
|type: sevol;                    |Shown as an SE volume slider.                                                                                                               |
|type: charactervol;             |Shown as a character volume slider. A character number must be specified by `index:`.                                                       |
|type: textspeed;                |Shown as a text speed slider.                                                                                                               |
|type: autospeed;                |Shown as an auto mode speed slider.                                                                                                         |
|type: preview;                  |Shown as a text preview area.                                                                                                               |
|type: fullscreen;               |Shown as a full screen mode button.                                                                                                         |
|type: window;                   |Shown as s windoe mode button.                                                                                                              |
|type: font;                     |Shown as a font-change button. A font file must be specified by `file:`.                                                                    |
|type: default;                  |Resets settings when pressed.                                                                                                               |
|type: savepage;                 |Shown as a save/load page button. A page number must be specified by `index:`.                                                              |
|type: save;                     |Shown as a save slot. A save slot number must be specified by `index:`.                                                                     |
|type: load;                     |Shown as a load slot. A load slot number must be specified by `index:`.                                                                     |
|type: auto;                     |Shown as an auto mode button.                                                                                                               |
|type: skip;                     |Shown as a skip mode button.                                                                                                                |
|type: title;                    |Shown as a back-to-title button.                                                                                                            |
|type: history;                  |Shown as a history button.                                                                                                                  |
|type: historyscroll;            |Shown as a vertical history scroll slider.                                                                                                  |
|type: historyscroll-horizontal; |Shown as a horizontal history scroll slider.                                                                                                |
|type: cancel;                   |Shown as a cancel button.                                                                                                                   |
|type: quit;                     |Shown as a quit button.                                                                                                                     |
|type: namevar;                  |Shown as a area to preview a name variable value. A name variable must be specified by `namevar:` (a-z)                                     |
|type: char;                     |Shown as a button to input a character. An input string must be specified by `msg:`. `msg:` is a free-form, and may be one of the special sequences, `[clear]`, `[backspace]`, and `[ok]`.|
|type: wms;                      |Calls a WMS when pressed. A WMS must be specified by `file:`.                                                                               |

## Button Options

|Description           |Meaning                                                                |
|----------------------|-----------------------------------------------------------------------|
|type:                 |Type of the button.                                                    |
|x:                    |X position of the button.                                              |
|y:                    |Y position of the button.                                              |
|width:                |Width of the button.                                                   |
|height:               |Height of the button.                                                  |
|label:                |Target label.                                                          |
|index:                |Index of a save/load/history slot.                                     |
|clear-r:              |Background clear color R. Use white for white buttons.                 |
|clear-g:              |Background clear color G. Use white for white buttons.                 |
|clear-b:              |Background clear color G. Use white for white buttons.                 |
|margin:               |Inner margin of save/load/history buttons.                             |
|pointse:              |Sound effect for when the button is pointed.                           |
|clickse:              |Sound effect for when the button is clicked.                           |

## Slider Buttons

For a slider button, please draw a knob on the "active" image.
See also the sample project.

The width and the height of the knob will be:
* the same as the button height for horizontal sliders.
* the same as the button width for vertical sliders.

## Color Adjustments

If a character fringe is shown in a save/load/history slot, please add the following settings.

```
# Clear color
clear-r: 255;
clear-g: 255;
clear-b: 255;`</pre>
<p>
  Sample:
</p>
<pre>`# Save data slot #1
SAVESLOT1 {
   # Type: Save
   type: save;

   # Save data index 0
   index: 0;

   # Clear color
   clear-r: 255;
   clear-g: 255;
   clear-b: 255;

   # Position and size
   x: 167;
   y: 153;
   width: 950;
   height: 162;

   # Margin between image and text
   margin: 20;

   # Sound effect when pointed
   pointse: btn-change.ogg;

   # Sound effect when clicked
   clickse: click.ogg;
}
```

### pointse:

`pointse: btn-change.ogg;` indicates a sound effect file is
played back when the mouse cursor enters the button.

### clickse:

`clickse: click.ogg;` indicates a sound effect file is
 played back when the button is clicked.

## Custom Menu

You can add custom menu buttons on the menu which is shown when the system button is pressed.

### Menu to Menu Jump

```
# Jump to a custom GUI
MY_MENU_1 {
   type: gui;
   file: my-menu-1.txt;
}
```

### Menu to Scenario Jump

```
# Jumps to label
MY_MENU_1 {
   type: goto;
   label: my-menu-1-label;
}
```

### Menu to Scenario Call and Return

```
global {
   ...
   pushstate: yes;
   ...
}
```

```
button {
   type: goto;
   label: my-menu-1-label;
   gosub-back: yes;
}
```

You can make a configuration that a button calls a scenario then returns to the calling point.

Firstly, add `pushstate: yes;` to the GUI.
Secondly, add `gosub-back: yes;` to the buttons.
Lastly, do `@return` from scenarios.

You can use `gosub-gui: yes;` instead of `gosub-back: yes;`.
In this convention, a user will return to a calling GUI.
