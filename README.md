
# Pipex

This program takes an input file, runs a command on it, pipes the result to another command, and writes the final output to a file. It mimics the shell command:

```bash
$ < input_file command1 | command2 > output_file
```
## Usage

Compile the project using:

```bash
make
```

## Regular pipex usage
You can execute two or more commands in a pipeline like this:

```bash
$ ./pipex input_file command1 command2 ... commandN output_file
```

The output file will be created or overwritten.

This replicates the shell behavior:
```bash
$ < input_file command1 | command2 | ... | commandN > output_file
```
Each command may include arguments, e.g.:
```bash
$ ./pipex infile "grep hello" "wc -l" outfile
```
## Here_doc mode
pipex supports a here_doc mode, where input is read from standard input until a limiter string is reached:
```bash
$ ./pipex here_doc LIMITER command1 command2 ... commandN output_file
```

Input is collected until LIMITER is entered on a line by itself.

Output is appended to the output file instead of overwritten, mimicking:
```bash
$ << LIMITER command1 | command2 | ... | commandN >> output_file
```
## Author
cgrasser
