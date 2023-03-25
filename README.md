<style>
.markdown-body {
    font-family: "Helvetica";
}
.markdown-body code {
    font-family: "Iosevka Extended";
}
</style>

# SFRWENG 3A04: Individual Assignment 1
**Author**: Luigi Quattrociocchi (quattrl)  
**Date**: March 27, 2023  


#### (a) Introduction
This repository showcases the **observer pattern**, a software design pattern in which an object, named the **subject**, maintains a list of its dependents, called **observers**, and notifies them automatically of any state changes, usually by calling one of their methods[^1]. The included code 

#### (b) Design of system

The following diagram shows the structure of classes in `src`. The main file is omitted.

![UML Class Diagram](assets/class_diagram.png)

The following diagrams come from the famous book "Design Patterns: Elements of Reusable Object-Oriented Software"[^2], typically referred to as "The Gang of Four". Notice that the class diagram is nearly identical to the one above. The sequence diagram is also relevant to this design.
![gof uml](assets/observer_pattern.gif)
![gof sequence](assets/observersequence.gif)


#### (c\) User guide

Pre-built binaries `A1.exe` (for Windows users) and `A1.out` (for Linux users) are included. Open the root directory of this repository in a terminal, then run the executable for your platform.

##### Windows

Build:  
*NOTE: Run this from an MSVC enabled terminal (such as `Developer Command Prompt for VS 2022`)*
```console
> .\make.bat
```
Run:
```console
> .\A1.exe
```

##### Linux

Build:
```console
$ ./make.sh
```
Run:
```console
$ ./A1.out
```

#### References:
[^1]: https://en.wikipedia.org/wiki/Observer_pattern
[^2]: https://archive.org/details/designpatternsel00gamm/page/293
