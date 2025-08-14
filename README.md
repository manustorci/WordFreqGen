A project developed in C. The program performs text analysis by generating a word frequency table and uses it to produce random text based on calculated word frequencies. It supports both single-process and multi-process execution modes, demonstrating inter-process communication and concurrency.

**Features**
- Parses Italian text to compute word occurrence frequencies
- Generates random text based on word frequency data
- Supports CSV input/output for data processing
- Includes a Makefile and detailed documentation for easy compilation and usage

**Directory Structure**
- UniMonoC: Contains the single-process implementation of the project
- UniMultiC: Contains the multi-process implementation, featuring inter-process communication with at least three concurrent processes
