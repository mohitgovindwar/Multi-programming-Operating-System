# Multi-programming-Operating-System

- This is my Operating System Course Project. 
- It is used for execution of multiple jobs
- Jobs should be defined and very well structured.
- For wrong Jobs, the system will generate proper error messages.
- Series of Jobs should be kept in input.txt or job.txt.
- Afer processing of jobs output can be seen in output.txt
- Random memory allocation for program card is done using paging.

### Job can consist of Instruction
- GD - Get Data
- PD - Print Data
- LR - Load the content into Register From Memory
- SR - Store the content from Register into Memory
- CR - Compare Register content and Memory
- BT - Branch Toggle(Checks Toggle Variable)
- H - Denotes end of job.
- Job should start with $AMJ
- There is $DTA after declaration of program cards
  and before data cards
- Job should end with $END
