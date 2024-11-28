Multilingualization
===================

In a scenario file, you can write a message with a language specifier.

```
+en+This is an English message.
+ja+日本語のメッセージです。
```

The same rule applies to lines with characters' names.

```
+en+*Hina*This is an English message.
+ja+*ひな*日本語のメッセージです。
```

The prefix `+en+` means a message will be shown only if the language configuration is set to English.

Available languages are the following.

|Code     |Language             |
|---------|---------------------|
|ja       |Japanese             |
|en       |English              |
|fr       |French               |
|it       |Italian              |
|es       |Spanish              |
|de       |German               |
|el       |Greek                |
|ru       |Russian              |
|zh       |Chinese (Simplified) |
|tw       |Chinese (Traditional)|
|other    |Other                |

If you wish to make a language selection while running a visual novel, write:

```
@config locale.force en
```

This will force the current language to English.
