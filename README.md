# ft_ls

## Description
ft_ls is a custom implementation of the `ls` command in Unix-like operating systems. It lists the files and directories in a given directory, providing various options for sorting and formatting the output.

## Features
- List files and directories in a given directory
- Sort the output by name, size, or modification time
- Display file permissions, ownership, and other metadata
- Support for displaying hidden files
- Recursive listing of subdirectories

## Usage
To use ft_ls, simply compile the source code and run the executable with the desired options and arguments. For example:

```bash
$ ./ft_ls -l -R /path/to/directory
```

This will recursively list all files and directories in `/path/to/directory`, displaying detailed information for each file.

## Versions of the program

This program has two versions: the mandatory part and the bonus part.

### Mandatory Part
The mandatory part of the program includes the following features:

- When no options are passed, it prints a new line per every file (like using `ls -1`)
- Listing files and directories in a given directory
- Recursive listing of subdirectories
- Displaying hidden files and directories
- Sorting the output by modification time

### Bonus Part
The bonus part of the program includes additional features:

- List files in formatted columns when no options are used and the output is print out in a terminal, instead of a file or a pipe.
- Showing if a file has extended attributes or access control list (ACL)
- Showing the time of last access for each file
- Hiding the user ID in the detailed information
- Not sorting the output
- Using the `-d` flag to list directories themselves, rather than their contents

Feel free to choose which version of the program suits your needs.

## List of available options.
 
Here is a list of available options for ft_ls:

### Mandatory Part

- `-R`: Recursively list files and directories in subdirectories.
- `-a`: Display hidden files and directories.
- `-l`: Display detailed information for each file, including permissions, ownership, size, and modification time.
- `-r`: Reverse the order of the output.
- `-t`: Sort the output by modification time.

### Bonus part

Include the options mentioned above, but also it includes `he following extra ones:

- `-G`: Enable colorized output for improved readability. The colors chosen are based in the `macOS`version of the program `ls`.
- `-d`: List the directories as a text plain content. It does not expand them and no recursion is applied.
- `-f`: The program does not sort the name of files and folders. It overwrites any other sorting option.
- `-g`: It activates the listing option (`-l`). However, it does not show the userID's name when it is listing the files
- `-u`: When the option `-l` or `-g` are in use, it shows the time of last access of a file, instead of the time of last modification. If the `-t`option is in use, the time of last access of the files is used to sort the output
- `-@`: When the flags `-l`or `-g`are in use, it shows the extended attributes of a file or folder if they have them
- `-1`: It list the files, printing a new line, intead of columns

Feel free to combine these options to customize the output according to your needs.

## Installation
To install ft_ls, follow these steps:

1. Clone the repository:
```bash
$ git clone https://github.com/quiminbano/ft_ls.git
```

2. Change into the project directory:
```bash
$ cd ft_ls
```

3. Compile the source code:
- For mandatory part use:
```bash
$ make
```
- For bonus part use:
```bash
make bonus
```

4. Run the executable:
```bash
$ ./ft_ls
```

## License
This project is licensed under the 42 Network License.
