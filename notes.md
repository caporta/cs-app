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

### 1.3 Running the Program

- _reading `hello` command from keyboard_
    - shell program reads each character into a register
    - then stores each character in main memory
- _leading executable_
    - copy code and data in `hello` object file from disk to memory
    - data includes the output string `"hello, world\n"`
    - uses _direct memory access (DMA)_ to
        - move data directly from disk to main memory, bypassing CPU
    - executes `hello`'s `main` routine
        - copy bytes from output string in memory to register
        - move bytes from register to display device

### 1.4 Caching
- The system spends a lot of time moving info from one place to another
- Because of physical laws:
    - larger storage devices are slower than smaller ones
    - Faster devices are more expensive to build
    - e.g. disk drive may be 1000x larger than main memory
        - register may store a few hundred bytes, main memory stores billions
        - processor may take 10000000x longer to read a word from disk > mem
        - processor may take 100x longer to read from mem > regs
- _processor-memory gap_ continues to increase
    - i.e. it's easier/cheaper to increase speed of CPUs than main memory
- to address the above issues, systems include _cache memories_
    - _L1 cache_
        - on the processor chip
        - holds tens of thousands of bytes
        - can be accessed nearly as fast as the register file
    - _L2 cache_
        - connected to chip by special bus
        - holds hundreds of thousands to millions of bytes
        - may take 5x longer than L1, but still 5-10x faster than main mem
    - some newer systems may even inclued an _L3 cache_
    - These caches are implemented with _static random access memory (SRAM)_
    - Exploits _locality_
        - the tendency for programs to access data/code in localized regions

### 1.5 Memory Hierarchy

- The storage devices of a computer system are organized as a _memory hierarchy_
    - from top to bottom, devices become larger, slower, and cheaper per byte
    - register file occupies the top (L0), followed by caches/mem/disk
    - **storage at one level serves as a cache for the next lowest level**
    - in distributed systems, a local disk is a cache for remote disks
