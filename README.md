# OS

Members:  
          
          Mustafa Ajanovic
          Zehra Grbovic

Files:     
                    
          shell.c
          task1Basic.c
          task1Advanced.c
          task2BasicCAT.c 
          task2BasicCLEAR.c 
          task2BasicCOWSAY.c 
          task2BasicRM.c 
          task2IntermediateCAT.c 
          task2IntermediateCOWSAY.c 
          task3Basic.c 
          task3Intermediate.c 
          task3Advanced.c
          task4.c 
          
Answers:  
          
          Q1 -  The mmap() function is a system call in Unix and Unix-like operating systems that allows a process to map a portion of 
                its virtual address space to a file or a device. This function can be used for various purposes, such as memory-mapped 
                I/O, inter-process communication, and loading executable code from shared libraries. By mapping a portion of a file or 
                device to memory, the process can directly access its contents as if they were in memory, without the need for 
                additional I/O operations. The mmap() function returns a pointer to the mapped area in memory, which can be used by the 
                process to read from or write to the file or device. The function takes several arguments, including the starting 
                address of the mapping, the length of the mapping, the protection flags, and the file descriptor or device to be mapped.
                
          Q2 -  During a context switch, the operating system saves the current context of a running process, including its register 
                values, program counter, and stack pointer, to memory and loads the context of another process from memory into the CPU. 
                This allows the CPU to switch between multiple processes and provide the illusion of concurrency to the user.
                Context switches are necessary for multitasking, where multiple processes are running concurrently on a single CPU. 
                Without context switches, the CPU would be monopolized by a single process, and other processes would not be able to 
                execute until the running process completes.
                Ideally, we want the OS to perform as few context switches as possible. This is because context switches are relatively 
                expensive operations that consume CPU cycles and memory bandwidth. The more frequently the OS performs context switches, 
                the less CPU time each process receives and the less  efficient the system becomes. Moreover, frequent context switches 
                can lead to cache thrashing and contention for shared resources, which can further degrade performance.
                However, we also want to avoid situations where a single process monopolizes the CPU for an extended period, preventing 
                other processes from executing. 
                This can lead to poor responsiveness and slow down the overall system performance. Therefore, a balance must be struck 
                between maximizing CPU utilization and minimizing context switches to achieve optimal system performance

Outline:        tbd

Instructions:   tbd

Challenges:     tbd

Sources:        
                
                ChatGPT

Problems:       tbd
