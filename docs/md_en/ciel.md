Ciel Direction System
=====================

`Ciel` is a direction system influenced by the visual novel engine `YU-RIS/ERIS`.

Ciel cannot be used with the regular commands such as
[@bg](reference.html#bg),
[@ch](reference.html#ch),
[@move](reference.html#move] and
[@chch](reference.html#chch).

## Usage

```
# Specify a background file. (Will not be shown at this point.)
@cl.file name=bg file=roof.png

# Enter a character named hina. (No position is specified.)
@cl.enter name=hina

# Specify a hina's image, position, and alpha. (Will not be shown at this point.)
@cl.file name=hina file=001-normal.png
@cl.pos name=hina align=center x+=100
@cl.alpha name=hina a=255

# Specify a fading type.
@cl.effect effect=normal

# Specify a fading time.
@cl.time t=0.5

# Run a fading and apply to the screen.
@cl.run
```

## Command List

|Command                              |Explanation                                                                                               |
|-------------------------------------|----------------------------------------------------------------------------------------------------------|
|@cl.enter name=NAME                  |Let a character enter the stage. The name will be valid until that character leaves.                      |
|@cl.leave name=NAME                  |Let a character leave the stage. If name=all, all characters will leave.                                  |
|@cl.file name=NAME file=chara001.png |Assign an image file to a character. If name=bg, the background will be changed.                          |
|@cl.pos name=NAME align=left x+=100  |Specify a position of a character. Use align=, valign=, x=, x+=, x-=, y=, y+=, and y-=                    |
|@cl.alpha name=NAME a=255            |Specify an alpha value of a character.                                                                    |
|@cl.dim name=NAME dim=true           |Specify a character dimming. Use dim=true or dim=false.                                                   |
|@cl.time t=0.5                       |Specify a time for fading or anime.                                                                       |
|@cl.effect effect=normal             |Specify a type of fading.                                                                                 |
|@cl.move name=NAME t=0.5 x+=100      |Queue an anime. Use x=, x+=, x-=, y=, y+=, y-=, and a=                                                    |
|@cl.run                              |Run a fading or an anime. If a move exists, the command will be an anime. Otherwise, it will be a fading. |
|@cl.async                            |Run an anime asynchronously and move to the next command.                                                 |

## Example of Anime

This will move a character named `hina`.

```
@cl.move name=hina t=0.3 y-=100
@cl.move name=hina t=0.3 y+=100
@cl.move name=hina t=0.3 y-=100
@cl.move name=hina t=0.3 y+=100
@cl.run
```

You can use <code>@cl.async</code> instead of <code>@cl.run</code> in order to show anime without waiting for it to finish.

## Macro

Ciel may be used with <code>@gosub</code>, or its abbreviation `&macro` form.

```
&hina happy
```

A macro should be defined as the following.
(Arguments may be reffered to as `&1`)

```
:hina
@cl.file name=hina file=001-&amp;1.png
@cl.run
@return
```
