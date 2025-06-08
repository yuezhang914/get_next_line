# get_next_line

> A function that reads a file descriptor one line at a time — project from the 42 coding school curriculum.

## 📚 Description

`get_next_line()` is a C function that returns a line read from a file descriptor, including the newline character (`\n`) if one is present.

It reads from a file descriptor incrementally and is designed to work with files of any size, including those containing very long lines. It handles memory allocation internally and ensures that memory leaks and segmentation faults are avoided.


## 📄 Mandatory Features

- Read from any valid file descriptor.
- Return one line per call to `get_next_line()`.
- Efficient memory usage.
- Return `NULL` on end-of-file or error.

## 🌟 Bonus Features

- Support for multiple simultaneous file descriptors.

## ⚙️ Function Prototype

```c
char *get_next_line(int fd);
```

- `fd`: The file descriptor to read from.
- Returns the next line including the newline character if present.
- Returns `NULL` when there's nothing more to read or an error occurs.

## 🚀 Usage

1. **Clone the repository**:

```bash
git clone https://github.com/yourusername/get_next_line.git
cd get_next_line
```

2. **Compile the project**:

```bash
make        # Compiles mandatory version
make bonus  # Compiles bonus version
```

3. **Use it in your code**:

```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## 🧪 Testing

Test your implementation with:

- Empty files
- Files with long lines (e.g. `giant_line.txt`)
- Files without a trailing newline
- Simultaneous calls on multiple file descriptors (bonus)

### Useful Tools

- [francinette](https://github.com/xicodomingues/francinette)
- [42FileChecker](https://github.com/moka-guys/42FileChecker)

## 🛠️ Compilation Flags

```bash
-Wall -Wextra -Werror
```
Memory leaks and undefined behavior should be completely avoided.

