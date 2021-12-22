# philosophers
[Mutual Exclusion in Synchronization - GeeksforGeeks](https://www.geeksforgeeks.org/mutual-exclusion-in-synchronization/)

[Multithreading in C - GeeksforGeeks](https://www.geeksforgeeks.org/multithreading-c-2/)

[How to create and join threads in C (pthreads).](https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM&ab_channel=JacobSorber)

[What is a mutex?](https://stackoverflow.com/questions/34524/what-is-a-mutex)

[Reading 20: Thread Safety](http://web.mit.edu/6.031/www/fa17/classes/20-thread-safety/)

[Short introduction to threads (pthreads)](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&ab_channel=CodeVault)

[pthread_mutex_lock() - Wait for a lock on a mutex object](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-pthread-mutex-lock-wait-lock-mutex-object)

[https://cdn.intra.42.fr/pdf/pdf/33157/en.subject.pdf](https://cdn.intra.42.fr/pdf/pdf/33157/en.subject.pdf)

[http://index-of.es/OS/The Linux Programming Interface.pdf](http://index-of.es/OS/The%20Linux%20Programming%20Interface.pdf)

[https://docs.oracle.com/cd/E19205-01/820-0619/gepji/index.html](https://docs.oracle.com/cd/E19205-01/820-0619/gepji/index.html)

[https://docs.oracle.com/cd/E19205-01/820-0619/6ncbk8g78/index.html](https://docs.oracle.com/cd/E19205-01/820-0619/6ncbk8g78/index.html)

[https://www.youtube.com/watch?v=KCwNdtbiJPo&ab_channel=WadeFagen-Ulmschneider](https://www.youtube.com/watch?v=KCwNdtbiJPo&ab_channel=WadeFagen-Ulmschneider)

[https://courses.grainger.illinois.edu/cs240/fa2021/static/lectures/cs240fa21_09-slides.pdf](https://courses.grainger.illinois.edu/cs240/fa2021/static/lectures/cs240fa21_09-slides.pdf)


THREADS
Threads are a mechanism that permits an application to perform multiple tasks concurrently. A single process can contain multiple threads. All of these threads are independently executing the same program, and they all share the same global memory, including the initialized data, uninitialized data, and heap segments.

In particular, the location of the per-thread stacks may be intermingled with shared libraries and shared memory regions, depending on the order in which threads are created, shared libraries loaded, and shared memory regions attached. Furthermore, the location of the per-thread stacks can vary depending on the Linux distribution.

- Sharing information between threads is easy and fast. It is just a matter of copying data into shared (global or heap) variables - synchronization techniques -
- Thread creation is faster than process creation—typically, ten times faster or better, because many of the attributes that must be duplicated in a child created by fork() are instead shared between threads. In particular, copy-on-write duplication of pages of memory is not required, nor is duplication of page tables.

[Multithreading in C - GeeksforGeeks](https://www.geeksforgeeks.org/multithreading-c-2/)

[Operating Systems Notes](https://www.personal.kent.edu/~rmuhamma/OpSystems/Myos/threads.htm)

<aside>
💡 As the threads do share the same address space, so they may overwrite the data of each other. Due to this reason, there is no protection between the threads of the same process.

</aside>

[](https://www.geeksforgeeks.org/thread-functions-in-c-c/)

**Explanation:** Here two threads of execution are created in the code. The order of the lines of output of the two threads may be interchanged depending upon the thread processed earlier. The main thread waits on the newly created thread for exiting. Therefore, the final line of the output is printed only after the new thread exits. The threads can terminate independently of each other by not using the *pthread_join* function. If we want to terminate the new thread manually, we may use *pthread_cancel* to do it.

**Note:** If we use exit() instead of **pthread_exit()** to end a thread, the whole process with all associated threads will be terminated even if some of the threads may still be running

## Concurrency and parallelism:

[Safety and Speed Issues with Threads. (pthreads, mutex, locks)](https://youtu.be/9axu8CUvOKY?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM&t=292)

**Concurrency** is when two or more tasks can start, run, and complete in overlapping time **periods**. It doesn't necessarily mean they'll ever both be running **at the same instant**. For example, *multitasking* on a single-core machine.

**Parallelism** is when tasks *literally* run at the same time, e.g., on a multicore processor

[What is the difference between concurrency and parallelism?](https://stackoverflow.com/questions/1050222/what-is-the-difference-between-concurrency-and-parallelism)

## **Race condition:**

A race condition occurs when two threads access a shared variable at the same time. The first thread reads the variable, and the second thread reads the same value from the variable. Then the first thread and second thread perform their operations on the value, and they race to see which thread can write the value last to the shared variable. The value of the thread that writes its value last is preserved, because the thread is writing over the value that the previous thread wrote.

### **Symptoms for a race condition**

The most common symptom of a race condition is unpredictable values of variables that are shared between multiple threads. This results from the unpredictability of the order in which the threads execute. Sometime one thread wins, and sometime the other thread wins. At other times, execution works correctly. Also, if each thread is executed separately, the variable value behaves correctly.

### **When deadlocks occur**

A deadlock occurs when two threads each lock a different variable at the same time and then try to lock the variable that the other thread already locked. As a result, each thread stops executing and waits for the other thread to release the variable. Because each thread is holding the variable that the other thread wants, nothing occurs, and the threads remain deadlocked.

[What is a race condition?](https://stackoverflow.com/questions/34510/what-is-a-race-condition)

<aside>
💡 There is an important technical difference between race conditions and data races. Most answers seem to make the assumption that these terms are equivalent, but they are not.
A data race occurs when 2 instructions access the same memory location, at least one of these accesses is a write and there is no happens before ordering among these accesses. Now what constitutes a happens before ordering is subject to a lot of debate, but in general ulock-lock pairs on the same lock variable and wait-signal pairs on the same condition variable induce a happens-before order.
A race condition is a semantic error. It is a flaw that occurs in the timing or the ordering of events that leads to erroneous program behavior.

</aside>

## Atomic operation for thread safety

Atomic classes allow us to perform atomic operations, which are thread-safe, without using synchronization. An atomic operation is executed in one single machine level operation.

[Using Atomic Methods to Write Thread-Safe Classes - DZone Java](https://dzone.com/articles/using-atomic-methods-to-write-thread-safe-classes)

> **An atomic operation is an operation that cannot be interrupted.
A safe thread is a thread that can safely be interrupted.
Thread safety is obtained with atomic operations, in particular in the logic that prevents critical resources from being accessed multiple times.**
> 

# Mutex:

<aside>
💡 The mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.The behavior of a program is undefined if a mutex is destroyed while still owned by any threads, or a thread terminates while owning a mutex

</aside>

### example:

When I am having a big heated discussion at work, I use a rubber chicken which I keep in my desk for just such occasions. The person holding the chicken is the only person who is allowed to talk. If you don't hold the chicken you cannot speak. You can only indicate that you want the chicken and wait until you get it before you speak. Once you have finished speaking, you can hand the chicken back to the moderator who will hand it to the next person to speak. This ensures that people do not speak over each other, and also have their own space to talk.
Replace Chicken with Mutex and person with thread and you basically have the concept of a mutex.
Of course, there is no such thing as a rubber mutex. Only rubber chicken. My cats once had a rubber mouse, but they ate it.
Of course, before you use the rubber chicken, you need to ask yourself whether you actually need 5 people in one room and would it not just be easier with one person in the room on their own doing all the work. Actually, this is just extending the analogy, but you get the idea.

The chicken is the mutex. People hoilding the mu.. chicken are competing threads. The Moderator is the OS. When people requests the chicken, they do a lock request. When you call mutex.lock(), your thread stalls in lock() and makes a lock request to the OS. When the OS detects that the mutex was released from a thread, it merely gives it to you, and lock() returns - the mutex is now yours and only yours. Nobody else can steal it, because calling lock() will block him. There is also try_lock() that will block and return true when mutex is yours and immediately false if mutex is in use.

A Mutex is a mutually exclusive flag. It acts as a gate keeper to a section of code allowing one thread in and blocking access to all others. This ensures that the code being controlled will only be hit by a single thread at a time. Just be sure to release the mutex when you are done.

The Linux Programming Interface-Michael Kerrisk.pdf

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/27356ad6-6a6e-4b3e-b4e7-03f7f9a181e2/Screen_Shot_2021-07-07_at_11.40.05_AM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/27356ad6-6a6e-4b3e-b4e7-03f7f9a181e2/Screen_Shot_2021-07-07_at_11.40.05_AM.png)

# Spin locks:

*Spinlocks don't cause preemption but wait in a loop till the other core releases the lock.*

Spin locks are a low-level synchronization mechanism suitable primarily for use on shared memory multiprocessors. When the calling thread requests a spin lock that is already held by another thread, the second thread spins in a loop to test if the lock has become available. When the lock is obtained, it should be held only for a short time, as the spinning wastes processor cycles. Callers should unlock spin locks before calling sleep operations to enable other threads to obtain the lock.
\
Compared to spin locks, mutexes consume a larger amount of processor resources to block the thread. When a mutex lock is not available, the thread changes its scheduling state and adds itself to the queue of waiting threads. When the lock becomes available, these steps must be reversed before the thread obtains the lock. While the thread iuuuuuu

<aside>
💡 Therefore, spin locks and mutexes can be useful for different purposes. Spin locks might have lower overall overhead for very short-term blocking, and mutexes might have lower overall overhead when a thread will be blocked for longer periods of time.

</aside>
