# Assembler
The goal of this project is to be a translator from pseudo-assembler to pseudo-byte code.

## Install & Build & Run
```
git clone https://github.com/vsokh/assembler.git && \
cd assembler && \
git submodule update --init --recursive && \
make
```
The program takes filename.s([code specification](https://github.com/vsokh/assembler/blob/master/docs/en.subject.pdf)) file as an input and produces filename.cor file as an output in the root directory of the project.
```
./asm vm_champs/champs/examples/zork.s
```
You can execute the program with `-a` flag in order to observe program size, opcodes of instructions and parameters.
```
./asm -a vm_champs/champs/examples/zork.s
```
 
## Preview
For the sake of beauty I use [bat](https://github.com/sharkdp/bat) & [hexyl](https://github.com/sharkdp/hexyl) commands.
![preview of an input and output](https://github.com/vsokh/assembler/blob/master/images/preview.png)

## Coding style
Code written in C follows [Norminette](https://github.com/vsokh/assembler/blob/master/docs/norme.en.pdf)(42 coding style specification for C-based projects) rules.

## Author
vsokolog
