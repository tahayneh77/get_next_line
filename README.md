*This project has been created as part of the 42 curriculum by maltahay.*

# get_next_line

## Description

The `get_next_line` project is a fundamental assignment in the 42 curriculum designed to introduce students to static variables and dynamic memory management in C. The goal of this project is to develop a function, `char *get_next_line(int fd)`, that reads and returns one line at a time from a given file descriptor until reaching the end of the file (EOF) or encountering an error.

Repeated calls to `get_next_line()` allow reading an entire file or standard input sequentially. Each returned line includes its terminating `\n` character, except when the end of the file is reached without a trailing newline. The function manages memory safely, avoids memory leaks, and handles arbitrary buffer sizes passed via the `-D BUFFER_SIZE=n` compilation flag.

## Instructions

### Compilation

The project is designed to be compiled with `cc` along with the standard 42 flags `-Wall -Wextra -Werror` and an optional `-D BUFFER_SIZE=n` flag:

```bash
# Compilation with default BUFFER_SIZE (defined as 42 in get_next_line.h)
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -o gnl

# Compilation with a custom BUFFER_SIZE (e.g., 1, 42, 9999, 10000000)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=32 main.c get_next_line.c get_next_line_utils.c -o gnl
```

### Basic Usage Example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
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

### Execution

```bash
./gnl
```

## Resources

### Documentation & References

1. **POSIX `read(2)` manual**: `man 2 read` — Detailed specification of UNIX file descriptor reads and return codes.
2. **Standard C Library memory functions**: `man 3 malloc`, `man 3 free` — Heap allocation lifecycle and avoidance of memory leaks.
3. **42 Norm Documentation**: 42 School standard coding style guidelines and constraints (Norminette v3).
4. **Static Variables in C**: Storage duration, scope, and persistence across consecutive function calls in C.

### AI Usage

In compliance with Chapter III & V of the 42 subject:
- **Tasks & Parts**: AI was utilized to analyze the subject PDF (`en.subject.get_next_line_6336c608.pdf`), verify standard 42 Header column alignments (exactly 80 characters wide for login `maltahay`), audit compliance against 42 Norminette v3 rules (variable counts $\le 4$, function lengths $\le 25$ lines, max 5 functions per file), and draft testing scenarios for edge cases (empty files, single characters, lines without newlines, and variable `BUFFER_SIZE` values from 1 to $10^7$).
- **Reasoning**: The underlying algorithm (accumulating chunks via `ft_strjoin` into a static stash, extracting up to `\n`, and pruning remaining bytes with `ft_strdup`) was rigorously validated for zero memory leaks on all error and completion branches.

## Algorithm Explanation & Justification

### Selected Architecture

The function operates around a **static stash buffer** (`static char *stash`) that preserves unread characters between successive calls to `get_next_line`. The algorithm consists of three logical stages:

1. **`ft_read_to_stash`**:
   - Allocates a temporary buffer of size `BUFFER_SIZE + 1`.
   - Reads from `fd` into the temporary buffer in a loop until a newline character (`\n`) is encountered in `stash` or `read` returns 0 (EOF) or -1 (error).
   - Each chunk read is concatenated to `stash` via `ft_strjoin`, which takes ownership of the previous stash and frees it.
   - If an error occurs during reading (`bytes_read == -1`), all allocated buffers are freed, `stash` is cleared, and `NULL` is returned.

2. **`ft_extract_line`**:
   - Scans `stash` up to the first newline character `\n` (inclusive) or the terminating null byte `\0`.
   - Allocates exact memory for the line and copies the substring.
   - Null-terminates and returns the line to the caller.

3. **`ft_clean_stash`**:
   - Identifies the remaining content in `stash` after the extracted newline.
   - If nothing remains after `\n` or if EOF was reached without further data, frees `stash` and returns `NULL`.
   - Otherwise, duplicates the remaining substring into a new stash using `ft_strdup`, frees the old stash, and returns the pruned buffer ready for the subsequent call.

### Justification & Benefits

- **Minimal Read Principle**: Per subject guidelines, `ft_read_to_stash` stops reading immediately as soon as a `\n` is detected in `stash`. It does not read the entire file into memory at once, avoiding excessive RAM usage on large files.
- **Extreme Buffer Size Robustness**:
  - `BUFFER_SIZE = 1`: Works by reading byte-by-byte until `\n`.
  - Large `BUFFER_SIZE` (e.g., $10^7$): Reads large chunks, extracts lines one-by-one from the stash without unnecessary I/O calls.
- **Memory Safety**: Every dynamic allocation is checked. In case of allocation failure or read error, existing buffers are freed and static pointers are safely reset to `NULL`, preventing leaks and dangling pointers.
