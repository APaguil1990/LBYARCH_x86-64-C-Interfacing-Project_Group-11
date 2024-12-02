# x86-to-C Interface Programming Project: Acceleration Computation  

## Overview  
This project implements a program that computes the acceleration of vehicles using initial velocity, final velocity, and time as inputs. 
The computation is performed using a combination of C for input and output and x86-64 assembly for calculations.  

## Programmers  
- James Archer B. Paguiligan  
- Kyle Adrian L. Bibon  
- Section: S15 - LBYARCH, Group 11  

## Compilation and Execution (enter these statements in the command line) 
1. Assemble the x86-64 assembly file:

     nasm -f win64 accelerations.asm -o accelerations.obj
   
2. Compile the C code and link it with the assembly code:
   
     gcc -o mp2.exe main.c accelerations.asm
   
3. Run the program:
   
     mp2

## Performance Testing Results and Analysis:
![image](https://github.com/user-attachments/assets/511f3af0-300a-46e5-9e17-da95dbd51b8d)


## Execution Time Trends:
1. Small input sizes (10^1 - 10^3)
  - Execution time for input sizes of 10, 100, and 1000 cars were effectvely 0.00000 seconds.
    This indicates that the computation overhead is negligible for small datasets.
2. Moderate input sizes (10^4 - 10^6)
 - For 10^4 (10,000 cars), the average execution time was 0.00003 seconds,
   showing an observable but still very small time of execution.
 - As the input size increased to 10^5 (100,000 cars) and 10^6 (1,000,000 cars),
   the average execution times rose to 0.00035 seconds and 0.00372 seconds, respectively.
   This increase suggests a nearly linear increase in execution time relative to the input size,
   highlighting the efficient handling of larger inputs.
3. Large input size (10^7 - 10^8)
  - For 10^7 (10,000,000 cars), the execution time was 0.03827 seconds and for 10^8 (100,000,000 cars),
    the executuon time reached 0.39046 seconds.
  - The steep increase in execution time at these sizes suggests that memory access and
    data handling overhead become significant contributors to performance.
4. Large input size (10^9)
  - Memory allocation failed for this input size, indicating that the system's available
    memory could not handle the large dataset.

## Example Input and Output:
Sample Input:

![image](https://github.com/user-attachments/assets/16699fa5-1ac4-4b89-8cf5-70a78440fcb7)

Output:

![image](https://github.com/user-attachments/assets/1645ef5b-b87d-4a94-bb38-3697d276d937)


## Screenshots of the Program Output
![image](https://github.com/user-attachments/assets/cc63c8ad-0dce-4b52-89f4-7a6668019c29)
![image](https://github.com/user-attachments/assets/1befe8b6-6b48-4c48-b4a4-e6029eca086e)
![image](https://github.com/user-attachments/assets/d3288a53-b5e8-4c2b-9554-1a42486942a0)
![image](https://github.com/user-attachments/assets/52498005-7e22-48f2-9e83-2e7be7a714cc)
![image](https://github.com/user-attachments/assets/b9c680cc-ea1b-444c-ad24-d6d98386934b)
![image](https://github.com/user-attachments/assets/300ca580-0698-46f6-b9f3-d3ea7d178abd)
![image](https://github.com/user-attachments/assets/a09e7d1e-668c-4a34-bde9-ca955cc36f27)
![image](https://github.com/user-attachments/assets/4c9b5d24-2581-40f9-9dc2-707c6f29a032)









    
