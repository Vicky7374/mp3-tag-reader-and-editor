# MP3 ID3v2 Tag Reader & Editor

A command-line utility written in C to view and modify ID3v2 metadata tags in MP3 files without corrupting the underlying audio stream. Built from scratch using standard C libraries, this project demonstrates low-level binary file I/O, pointer manipulation, and endianness conversion.

---

## Features

* **View Metadata:** Extracts and displays key song information (Title, Artist, Album, Year, Genre, and Comment) directly in the terminal.
* **Edit Metadata:** Modifies specific ID3v2 text frames via command-line arguments.
* **Non-Destructive Editing:** Writes updated headers, tags, and the remaining audio stream to a temporary file (`temp.mp3`) before replacing the original file to prevent data corruption.
* **Endianness Conversion:** Manually converts 4-byte tag sizes between Big Endian (ID3v2 standard) and Little Endian (host system) using pointer-based byte swapping.
* **Input Validation:** Verifies command-line argument counts, valid tag flags, and `.mp3` file extensions before processing.
* **Color-Coded Terminal UI:** Uses ANSI escape codes for clean screen clearing, aligned formatting, and color-coded output.

---

## Supported Tags

| Flag | ID3v2 Frame ID | Description |
| :--- | :--- | :--- |
| `-t` | `TIT2` | Song Title |
| `-a` | `TPE1` | Artist Name |
| `-A` | `TALB` | Album Name |
| `-y` | `TYER` | Release Year |
| `-g` | `TCON` | Song Genre |
| `-c` | `COMM` | Comment |

---

## Project Structure

* `main.c` – Entry point that parses command-line arguments (`-v`, `-e`, `--help`) and routes execution.
* `view.c` – Handles `.mp3` extension validation, skips the 10-byte header, parses and displays metadata frames, and prints the help menu.
* `edit.c` – Validates target tags and file extensions, updates the specified ID3v2 frame size and content, and copies the remaining binary audio data via `temp.mp3`.
* `header.h` – Contains ANSI color macros, `CLEAR_SCREEN()`, struct definitions, and function prototypes.
* `song.mp3` – Sample MP3 file for testing.

---

## Compilation & Usage

### 1. Compile the Project
Use `gcc` to compile all source files together:
```bash
gcc main.c view.c edit.c -o a.out
```

### 2. View MP3 Tags
```bash
./a.out -v song.mp3
```
*(Displays the Title, Artist, Album, Year, Genre, and Comment tags)*

### 3. Edit an MP3 Tag
```bash
./a.out -e <tag_flag> "<new_value>" song.mp3
```
**Example (Editing the Title):**
```bash
./a.out -e -t "New Song Title" song.mp3
```
*(Valid tag flags: `-t`, `-a`, `-A`, `-y`, `-g`, `-c`)*

### 4. Display Help Menu
```bash
./a.out --help
```
*(Lists all available command-line options and usage syntax)*

---

## How It Works

1. **Header Handling:** Every ID3v2 MP3 file starts with a 10-byte header. In view mode, the program skips these 10 bytes using `fseek()`. In edit mode, it reads and copies them directly to `temp.mp3`.
2. **Frame Parsing & Endianness:** Each metadata frame consists of a 4-byte Tag ID, a 4-byte Big Endian size, 2 flag bytes, and the frame data (starting with a 1-byte text encoding value). The program swaps the size bytes to Little Endian to allocate memory and read the exact data length.
3. **Safe Updating:** When the target tag is found during editing, the new string length (`strlen + 1` for the `0x00` encoding byte) is converted back to Big Endian and written along with the new text. The remaining bytes of the original file (including the raw audio data) are streamed in 1000-byte chunks into `temp.mp3`, which then replaces the original file.

---

## Author

**Vicky Kumar**  
ID: `26018_442`
