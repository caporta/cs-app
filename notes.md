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
    - some newer systems may even include an _L3 cache_
    - These caches are implemented with _static random access memory (SRAM)_
    - Exploits _locality_
        - the tendency for programs to access data/code in localized regions

### 1.5 Memory Hierarchy

- The storage devices of a computer system are organized as a _memory hierarchy_
    - from top to bottom, devices become larger, slower, and cheaper per byte
    - register file occupies the top (L0), followed by caches/mem/disk
    - **storage at one level serves as a cache for the next lowest level**
    - in distributed systems, a local disk is a cache for remote disks

### 1.6 The Operating System Manages the Hardware

- Any attempt by an application to manipulate hardware must go through the OS
- The OS has two primary purposes:
    - Protect the hardware from misuse by runaway applications
    - Provide applications with a simple, uniform interface to different hardware
- hierarchical abstractions of the OS: **processes>virtual mem>files_**
    - **NOTE** _virtual machine_ can also be included here
    - _processes_
        - abstractions for the processor, main memory, and I/O devices
        - a _process_ is the OS's abstraction for a running program
        - can be run _concurrently_ (i.e. interleaved) with other procs
            - concurrency is a result of _multi-core_ processors
            - interleaving is achieved through _context switching_
        - a process can be composed of multiple _threads_
            - multiple execution units within process control flow
            - run in the same context and share the same code/data
            - easier to share data between threads than between procs
            - concurrent execution is only _simulated_ in _uniprocessor systems_
    - _virtual memory_
        - abstraction for main memory and disk I/O devices
        - provides each process with the illusion of exclusive access to main mem
        - each process has its _virtual address space_, or uniform view of mem
        - address contents (from lowest to highest)
            - _program code and data_
                - code begins at same fixed address for all processes
                - followed by data locations corresponding to C globals
                - fixed in size once the process begins running
            - _run-time heap_
                - expands and contracts dynamically at run time
                    - result of calls to C stdlibs like `malloc` and `free`
            - _shared libraries_
                - storage for libs such as the C stdlib and the math lib
            - _user stack_
                - used by compiler to implement function calls
                - like the heap, expands and contracts dynamically
                - with each function call, the stack grows
                - each time a function returns, the stack contracts
            - _kernel virtual memory_
                - the _kernel_ always resides in memory
                - applications are not allowed to read/write or call from here
        - hardware translation of CPU-generated addresses must occur
            - in short, a process's virtual memory is stored on disk
            - then the main memory is used as a cache
    - _files_
        - abstractions for I/O devices
        - a sequence of bytes
        - every I/O device is modeled as a file
        - all system I/O is performed by reading/writing files
            - uses a small set of system calls called _Unix I/O_
        - provides a uniform interface for all the varied I/O devices

### 1.7 System Communication via Networks

- from the viewpoint of an individual system, the network is just another I/O device
- system copies a sequence of bytes from main memory to the network adapter
- email, messaging, www, ftp, and telnet are all based on networking

### 1.8 Concurrency and Parallelism

- _concurrency_ is a system with multiple, simultaneous activities
- _parallelism_ is the use of concurrency to make a system run faster
- three levels of parallelism abstraction:
    - _Thread-Level Concurrency_ (highest level):
        - used to context switch across multiple threads on a uniprocessor system
        - _multiprocessor_systems_ have become commonplace as a result of:
            - _multi-core_ processors
                several CPUs ("cores") integrated onto a single chip
            - _hyperthreading (aka simultaneous multi-threading)_
                - allows a single CPU to execute multiple flows of control
                    - multiple copies of some CPU hardware (e.g. PCs and regs)
                    - shared parts (e.g. ALU)
                - takes better advantage of processing resources
                    - "copied" resources allow for faster switching
                    - as the switch doesn't need to fully yield the process block
                - hyperthreaded CPU executes threads cycle-by-cycle
    - _Instruction-Level Parallelism_ (lower level)
        - processors can execute multiple instructions at a time
        - uses _pipelining_
            - execution actions are partitioned into a series of _steps_
            - processor hardware is organized as a series of _stages_
            - stages can operate in parallel
            - can sustain close to one instruction per clock cycle
        - _superscalar_ processors can sustain rates > 1 instruction/clock cycle
            - supported by most modern processors
    - _Single-Instruction, Multiple-Data (SIMD) Parallelism_ (lowest level)
        - modern processors allow a single instruction to execute multiple ops
            - e.g. adding 4 pairs of single-precision floating-points in parallel
        - mostly used to speed up image/audio/video data processing
        - while it can be used in C programs, more reliable to use _vector_ types
