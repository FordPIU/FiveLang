# FiveLang
## A new language purpose built for Cfx.re's FiveM.
Though this is being built for CFX.re's FiveM, it's being built with a custom loader, allowing this language to go standalone.<br>
Idea is to have the language compile into LUA, JS, or C# for FiveM, and (Machine Code | C++ (Undecided)) for standalone.

<br>

## Example of the lang
```cs
var i = 0

function Hello()
{
    print("Hello World!")
}

thread Increment()
{
    i++
    print(i)
}

Increment[Tick=1s]()

/*
    Expected result:

    Hello World!
    1
    2
    3
    4
    5
    6
    7
    8
    9
    ...
*/
```

<br>

## Progress
| Status | Label | Progress |
| :---: | :---: | :---: |
| :white_check_mark: | [Design / Syntax]( https://github.com/FordPIU/FiveLang/blob/main/Examples/example.flang ) | ██████████ |
| :construction: | [Lexer]( https://github.com/FordPIU/FiveLang/pull/41 ) | █████░░░░░ |
| :x: | Praser | ░░░░░░░░░░ |
| :x: | Type Checker | ░░░░░░░░░░ |
| :x: | Code Gen (LUA) | ░░░░░░░░░░ |
| :x: | Code Gen (JS) | ░░░░░░░░░░ |
| :x: | Code Gen (C#) | ░░░░░░░░░░ |
| :x: | Code Gen (Machine Code or C++) | ░░░░░░░░░░ |
| :x: | Libraries | ░░░░░░░░░░ |
| :x: | VS Code/Tools | ░░░░░░░░░░ |
| :x: | FiveM Loader | ░░░░░░░░░░ |
| :x: | FiveM Loader Server | ░░░░░░░░░░ |
| :x: | FiveM Encryption | ░░░░░░░░░░ |
| :x: | Docs | ░░░░░░░░░░ |
| :x: | First Program | ░░░░░░░░░░ |
