COMPUTER SYSTEMS: A PROGRAMMER'S PERSPECTIVE
===========================================


## PREFACE

### x86
  - umbrella term for IA32 and its extension x86-64


## CHAPTER I

### 1.1 Elements of a Compilation System

- _preprocessor_ (`cpp`)
    - read contents of `hello.c`'s `#include`d files
    - insert contents directly into program text
    - output `hello.i` modified source file
- _compiler_ (`cc1`)
    - translate `hello.i` text to assembly
    - output `hello.s` as _assembly-language program_
- _assembler_ (`as`)
    - translate `hello.s` into machine-language instructions
    - output `hello.o` as _relocatable object program_ for x86
- _linker_ (`ld`)
    - merges `hello.o` with dependent object files (e.g. `printf.o`)
    - outputs `hello`, an _executable object file_
    - **Note:** link-time errors can often be the most perplexing

### 1.2 Hardware Organization of a Typical System

- buses
    - electrical conduits
    - transfer fixed-size chunks of bytes known as _words_
    - _word size_ is typically 4 or 8 bytes
- i/o devices
    - keyboards (input), displays (output) disks (storage)
    - connect to the _i/o_ bus in one of two ways
        - _controller_
            - chip sets on the motherboard
        - _adapter_
            - card that plugs in to a slot on the board
- main memory
    - temp storage holding state/data during program execution
    - collection of _dynamic random access memory (DRAM)_ chips
    - organized in linear byte arrays, each with a unique address

- processor
    - _central processing unit (CPU or processor)_
    - executes instructions stored in main memory
    - a _register_ is a word-sized storage device
    - the _program counter (PC)_ is a register at the core of the CPU
        - at any given moment the PC stores the address of some instruction
    - the _register file_ stores the word-sized registers
    - the _arithmetic/logic unit (ALU)_ computes data and address values

    - the CPU does the following:
        - read the instruction from memory pointed to by the PC
        - interprets the bits of the instruction
        - performs a simple operation
        - updates the PC to point to the next instruction
        - common instructions include:
            - _load_
                - copy byte or word from memory to register, overwriting
            - _store_
                - copy byte or word from register to memory, overwriting
            - _operate_
                - copy contents of two registers to ALU
                - perform arithmetic operation on two words
                - store result in register, overwriting
            - _jump_
                - extract word from instruction
                - copy word into PC, overwriting
        - **Note:**
            - modern processors have far more complex mechanisms
            - thus, we can distinguish between a processor's
                - _instruction set architecture (abstractions above)_
                - _microarchitecture (implementation)_
