### Installation

You can git clone the repository using https protocol

```
git clone https://github.com/Nihilantropy/get_next_line.git
```

access the directory

```bash
cd get_next_line
```

Take a look at the code :eyes:! To test it you can call this command:

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line utils.c -o test_gnl
```
and run the program with

```
./test_gnl
```

then try to modify the `sample.txt.` file to see the result. You can play with the BUFFER_SIZE in each compilation to see if it works :smile:

**IMPORTANT!**: `main.c` and `sample.txt` are just for testing. They must not go into the project repository!

You can even use a tester program like this one:

```
https://github.com/Tripouille/gnlTester
```

Biggest shotout to `Oceano` :ocean: (https://github.com/suspectedoceano) (https://www.youtube.com/watch?v=8E9siq7apUU). This project is based on his wise teaching :love_letter:!

Now let's get down to the meat :cut_of_meat:!

# Get Next Line 📜

Welcome to the **Get Next Line** project! 🎉 This project will add a handy function to your coding toolbox, allowing you to read lines from a file descriptor one at a time. Perfect for when you need to handle files or standard input in a neat and manageable way!

## 📚 Project Overview

The goal of this project is to develop a function that reads a single line from a file descriptor. You'll become familiar with static variables and gain a deeper understanding of file handling in C. 

## 🛠️ Getting Started

- **Function Name**: `get_next_line`
- **Prototype**: `char *get_next_line(int fd);`
- **File Names**: `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`
- **Parameters**: `fd` - The file descriptor to read from
- **Return Value**:
  - **Read Line**: Returns the line read from the file descriptor.
  - **NULL**: If there is nothing else to read or if an error occurred.

### Key Points

- **Buffer Size**: Define the buffer size using `-D BUFFER_SIZE=n` during compilation. Test with various sizes to ensure robustness.
- **Handling Files**: Ensure your function reads files and standard input correctly.
- **Line Termination**: Include the terminating `\n` character in the returned line unless it's the end of file.
- **No Global Variables**: Use static variables to maintain state across multiple calls.
- **Avoid lseek()**: Directly use `read()` without seeking.

## 🔍 Mandatory Part

1. **Function**: Implement `get_next_line()` to read a line from a file descriptor.
2. **Files**: Submit `get_next_line.c`, `get_next_line_utils.c`, and `get_next_line.h`.
3. **Compilation**: Compile with `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c`.

## 🎨 Bonus Part

If you're up for a challenge, here’s what you can do:

- **Single Static Variable**: Refactor `get_next_line()` to use only one static variable.
- **Multiple File Descriptors**: Enable `get_next_line()` to handle multiple file descriptors simultaneously.

**Bonus Files**:
- `get_next_line_bonus.c`
- `get_next_line_bonus.h`
- `get_next_line_utils_bonus.c`

## 📝 Submission and Peer Evaluation

- **Repository**: Submit your work to your Git repository.
- **Testing**: Prepare diverse test cases to ensure functionality across different scenarios.
- **Defense**: Be ready to explain your code and test results during your defense.

Feel free to test your implementation thoroughly and ensure it meets all requirements. Once you’re done, integrate `get_next_line()` into your libft if you wish!

Happy coding and good luck! 🚀

## Leave a strar :star:!

If you'd like to see an in-depth analisy of this code, leave a star to let us know! :love_letter:
