<h1 align="center">
	<p>
		pipex
	</p>
</h1>
<h2 align="center">
	<p>
			This project is about handeling pipes!
	</p>
</h2>
<p align="center">
Coded in
	<a href="https://skillicons.dev">
		<img src="https://skillicons.dev/icons?i=c" />
	</a>
</p>

---
## The project:
### Basics:
- The program has to behave like this shell command:
```shell
< infile cmd1 | cmd2 > outfile
```
- The program gets executed the following way:
```shell
./pipex "infile" "cmd1" "cmd2" "outfile"
```
- The program only works for UNIX-like operating systems.
### Functioning:
- The program pipes the contents of the "infile" into the first command "cmd1".
- The first command gets executed, the results get piped into the second command "cmd2".
- The second command gets executed and the output is written to "outfile". All existing contents of the "outfile" are overwritten (If the program has no output, "outfile" will be empty").
- The "outfile" will get overwritten!
### Other functionality:
- In addition to the basic functioning of the project, you can insert as many commands as you want into the project:
```shell
./pipex "infile" "cmd1" "cmd2" "..." "cmdn" "outfile"
```
### Here_doc:
- The program can also simulate the following shell command:
```shell
cmd << LIMITER | cmd1 >> outfile
```
- For this the program has to be executed the following way:
```shell
./pipex here_doc "LIMITER" "cmd" "cmd1" "outfile"
```
- If the program is called with here_doc as first parameter, the User can input text into the command line, once a line is the same as specified, the program stops reading and executes the commands.
- In addition, with here_doc, the "outfile" will not be overwritten, but the results will be appended to it.
---
## Installation and Usage
1. Clone the repository:
```shell
git clone https://github.com/itseugen/pipex
```
2. Enter the directory and build the program:
```shell
cd pipex
make
```
Optional: Clean object files:
```shell
make clean
```
3. Create a input file (the program needs an existing input file, if the output file is missing it will be created):
```shell
touch input.txt
```
4. Run the program like explained above, you need at least for arguments.
Example:
```shell
./pipex "input.txt" "grep Hello" "wc -w" "output.txt"
```
---
<sub><sup>This project is part of my studies at 42 Heilbronn</sup></sub>