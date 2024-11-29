# Fuzzy Controller Design and Implementation for Process Regulation

## Project Overview
This project involves the design and implementation of a fuzzy controller for process regulation. It was carried out from October 2022 to February 2023 in collaboration with Universitatea Transilvania din Brașov.

The project aims to integrate and test control systems by designing and implementing a Mamdani-type fuzzy inference system. The system uses two input variables (error and derivative of error) and one output variable (command). It integrates Matlab-Simulink analysis with C/C++ programming for the controller implementation.

## Project Description
The fuzzy inference system uses the following:
- **Input variables:**
  - **Error (e)**
  - **Derivative of error (de)**
- **Output variable:**
  - **Command (c)**

### Mamdani Inference System
The system employs a Mamdani-type fuzzy inference method, where:
- The intersection and implication operations use the **min** operator.
- The union operation uses the **max** operator.
- The inference evaluation includes a **defuzzification** step (the specific defuzzification method is not predefined).

### Linguistic Terms
The linguistic terms for the input and output variables are defined as follows:
- **Error (e)**: [NB, N, Z, PS, PB]
- **Derivative of error (de)**: [NB, N, Z, PS, PB]
- **Command (c)**: [NB, N, Z, PS, PB]

The base set for all three variables is the interval [-1, +1].

### Rule Base
The rule base is represented in the following table (Tabel 1):

| Error / Derivative of Error | N  | Z  | B  |
|-----------------------------|----|----|----|
| **NB**                       | NB | NB | NB |
| **NS**                       | NS | NS | ZE |
| **ZE**                       | ZE | ZE | ZE |
| **PS**                       | ZE | PS | PS |
| **PB**                       | PS | PB | PB |

### Project Tasks

#### Task A: Implementation of the Fuzzy Inference System
The first task involves implementing the fuzzy inference system based on the rule base. The implementation must be compared with Matlab results for validation.

#### Task B: Optimization via Mamdani Inference Table
For optimization, the fuzzy inference system can be approximated using a Mamdani inference table. Discrete values are selected from the continuous base set for the input variables:
- **Error (E)**: `[-1, -0.8, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.8, 1]`
- **Derivative of error (DE)**: `[-1, -0.5, 0, 0.5, 1]`

The Mamdani inference table is created based on these discrete values. This table is then used in the next program for implementation.

#### Task C: Numerical Implementation of the Proportional-Derivative Regulator
Once the Mamdani inference table is created, a second program implements the fuzzy inference algorithm using the decision table. The results should be compared with the previous program's results to ensure correctness. 

The numerical derivative of the error is calculated using the following formula:
- `de[k] = (e[k] - e[k-1]) / T_e`
  where `T_e` is the sampling period (0.1).

A file named `date.txt` contains a set of recorded error values. Using these values, the derivative of the error is calculated, and the command signal is determined through both programs. The time interval for computing the command signal for all samples in the `date.txt` file is also measured.

## Skills Used
- **C++**
- **MATLAB/Simulink**
- **C Programming**

## Project Files
- **TICCP_PROIECT_Patrania_Bogdan_Andrei.pdf**: A report detailing the project design and results.
- **date.txt**: File containing recorded error values for testing the system.

## Requirements
- **MATLAB**: For Simulink modeling and verification.
- **C/C++ Compiler**: To compile the code for the fuzzy controller.
- **Text Editor**: To edit and modify the source code and data files.

## How to Run
1. **Step 1**: Clone or download the repository.
2. **Step 2**: Open the Matlab model in Simulink and run the simulation for verification.
3. **Step 3**: Compile the C/C++ code using your preferred compiler.
4. **Step 4**: Run the C/C++ implementation and compare the output with the Matlab results.
