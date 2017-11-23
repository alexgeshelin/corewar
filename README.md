# corewar

One of School 42 team projects. The goal of this project is to implement corewar game. It is a simple virtual machine 
in which champions written on Assembler-like language fight for their right to live and an interpreter for champions.
Part, which i have written in this project, is virtual machine and my teammates made interpreter and visualization.

![alt text](https://raw.githubusercontent.com/alexgeshelin/corewar/master/Example.png)

Champions source code is in *.s files. **asm** executable interprets them into byte-code and puts into *.cor files.
To start game use **corewar** executables *.cor champion files as arguments (up to 4 champions). To start it with visualization
use -v flag.
