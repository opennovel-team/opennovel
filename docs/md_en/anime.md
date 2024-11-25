Anime
=====

Anime is a feature to play layer-based animations by the [@anime](reference.html#anime) command.

## Anime File

An anime file is a text file which describes "sequences" of layer transforms.

## Sequence

To move the message box 100px right in a second, write the following sequence in an anime file.

```
move {
    # This is a layer specifier.
    layer: msg;

    # These are time specifiers.
    start: 0.0;
    end: 1.0;

    # These are origin position specifiers. '+0' means relative '0'.
    from-x: +0;
    from-y: +0;

    # This is an origin alpha specifier.
    from-a: 255;

    # These are final position specifiers. '+100' means relative '100'.
    to-x: +100;
    to-y: +0;

    # This is a final alpha specifier.
    to-a: 255;
}
```

## Layer Structure

The following is our layer structure.

```
text8
text7
text6
text5
text4
text3
text2
text1 

chf        (character face)
name       (name box)
msg        (message box)

effect4
effect3
effect2
effect1
 
chc-lip    (center character - lip)
chc-eye    (center character - eye)
chc        (center character - body)
chrc-lip   (right center character - lip)
chrc-eye   (right center character - eye)
chrc       (right center character - body)
chr-lip    (right character - lip)
chr-eye    (right character - eye)
chr        (right character - body)
chlc-lip   (left center character - lip)
chlc-eye   (left center character - eye)
chlc       (left center character - body)
chl-lip    (left character - lip)
chl-eye    (left character - eye)
chl        (left character - body)
chb-lip    (center back character - lip)
chb-eye    (center back character - eye)
chb        (center back character)

effect8
effect7
effect6
effect5
 
bg2        (second background)
bg         (background)
```

`effect1-effect4` are typically for weather animations.

`text1-text8` are layers to draw text using the [@pencil](reference.html#pencil) command.

## Scaling and Rotation

```
test1 {
    layer: effect1;
 
    start: 0.0;
    end: 3.0;

    from-x: 0;
    from-y: 400;
    from-a: 255;

    to-x: 0;
    to-y: 400;
    to-a: 255;

    # Scaling and rotation origin
    center-x: 600;
    center-y: 100;

    # Scaling factors
    from-scale-x: 1.0;
    from-scale-y: 1.0;
    to-scale-x: 2.0;
    to-scale-y: 2.0;
 
    # Rotation (+ for right, - for left)
    from-rotate: 0.0;
    to-rotate: -360;
}
test2 {
    layer: effect1;

    start: 3.0;
    end: 6.0;

    from-x: 0;
    from-y: 400;
    from-a: 255;

    to-x: 0;
    to-y: 400;
    to-a: 255;

    center-x: 600;
    center-y: 100;

    from-scale-x: 2.0;
    to-scale-x: 1.0;

    from-scale-y: 2.0;
    to-scale-y: 1.0;

    from-rotate: -360;
    to-rotate: 0;
}
```

## Resetting Anime

You can use the `@anime reset` command to reset animation parameters.

```
@anime reset layer-bg,xy,scale,rotate
@anime reset layer-chc,xy,scale,rotate
@anime reset layer-all,xy,scale,rotate
```

`layer-bg` means resetting the background layer parameters.
`layer-chc` means resetting the center character layer parameters.
`layer-all` means resetting all layer parameters.

`xy` means resetting x and y parameters.
`scale` means resetting scaling parameters.
`rotate` means resetting rotation parameters.

For example, the following resets the scale factor of the background.

```
@anime reset layer-bg,scale
```

## Clearing Anime

If you want to force-quit an anime of a specific layer, use the <code>@anime clear</code> command.

```
@anime clear layer-bg,layer-chc
```

If you want to wait until all anime finish, use the <code>@anime finish-all</code> command.

```
@anime finish-all
```

If you want to cancel all animations, use the <code>layer-all</code> option.

```
@anime clear layer-all
```
