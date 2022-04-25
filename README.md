# OS-Proj2-KSU

## Description
This program simulates the Banker's Algorithm. The Banker's Algorithm is used to avoid deadlocks when there are multiple processes running using the same resources. This program will read the information from the input.txt.

## Command for Execution
``` 
g++ -o banker bankers.cpp 
./banker 
```
## Output
### Safe Sequence
![safe_output](https://user-images.githubusercontent.com/60279886/165036003-31dde428-b41f-46e4-8d66-ab71c7f91440.PNG)

### Unsafe Sequence
![unsafe_output](https://user-images.githubusercontent.com/60279886/165036037-78bec36a-2f95-4b69-ac84-266a880cf030.PNG)
