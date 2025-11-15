# Get_Next_Line

A C function to read a line from a file descriptor, one at a time.
This implementation includes support for multiple file descriptors simultaneously, allowing each to maintain its own reading state.

---

## 📌 Table of Contents

* [About the Project](#about-the-project)
* [Project Structure](#project-structure)
* [Usage](#usage)
* [Author](#author)

---

## 📖 About the Project

`get_next_line` allows reading files line by line without loading the entire file into memory.
The implementation supports multiple file descriptors at the same time, ensuring each maintains its own reading state.

Key concepts reinforced:

* Dynamic memory allocation
* Pointer manipulation
* Static variables to maintain state across function calls
* File descriptor handling in C

---

## 📁 Project Structure

* `get_next_line.c` – Core function that reads from a file descriptor and returns the next line.
* `get_next_line_utils.c` – Helper functions for string manipulation and memory management (e.g., `ft_strlen`, `ft_strjoin`).
* `get_next_line_bonus.c` – Handles multiple file descriptors.
* `get_next_line_utils_bonus.c` – Helper functions for the bonus implementation.
* `get_next_line.h` – Header file containing prototypes for the main functions.
* `get_next_line_bonus.h` – Header file for the bonus implementation.

---

## ▶️ Usage

Example usage:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

* The function returns a string including the newline character `\n` if it exists.
* Returns `NULL` when the end of the file is reached or on error.

---

## 👤 Author

**Redouane Hssayn (Finn)/(rhssayn)**
Student at **1337 - 42 Network**

If this project helps you, feel free to ⭐ the repository on GitHub!
