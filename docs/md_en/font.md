Font
====

You can specify up to 4 fonts in the `project.txt` file.

|Font Type      |Explanation                                             |
|---------------|--------------------------------------------------------|
|Font 1         |Default font to be selected at the config screen.       |
|Font 2         |A fixed font.                                           |
|Font 3         |A fixed font.                                           |
|Font 4         |A fixed font.                                           |

Choosing a message box font:

```
# Choose Font 1
@config msgbox.font 1
```

You can temporary choose fonts within messages.

```
In a message, \f{1}you can choose Font 1 like this.
In a message, \f{2}you can choose Font 2 like this.
In a message, \f{3}you can choose Font 3 like this.
In a message, \f{3}you can choose Font 4 like this.
```

Because 'Font 1' name is stored in the save file,
an error will be shown after changes to font file name of Font 1 in the <code>project.txt</code> file.
In that case, please remove your save files.
