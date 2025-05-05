# [Project Name] - C Bitmap Steganography Tool

![C Badge](https://img.shields.io/badge/Language-C-blue.svg)
![Platform Badge](https://img.shields.io/badge/Platform-Linux-lightgrey.svg)
![License Badge](https://img.shields.io/badge/License-MIT-green.svg) <!-- Choose your license -->

A simple command-line tool written in C for embedding and extracting hidden data within BMP (Bitmap) image files using Least Significant Bit (LSB) steganography. This project was developed and tested on a Linux environment.

## Features

*   **Encode:** Hide text data within the pixels of a BMP cover image.
*   **Decode:** Extract hidden text data from a BMP stego-image.
*   Supports standard 24-bit BMP files.
*   Pure C implementation with standard libraries.
*   Command-line interface for easy scripting and usage.

## Prerequisites

*   A C compiler (like `gcc`) installed on your Linux system.
*   `make` (optional, but recommended for easier building).
*   Basic familiarity with the Linux command line.

## Building

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/[Your GitHub Username]/[Your Repo Name].git
    cd [Your Repo Name]
    ```

2.  **Compile using gcc directly:**
    ```bash
    gcc main.c [any_other_source_files.c] -o steganographer -lm # Add other .c files if you have them
    ```
    *(You might need `-lm` if you use math functions)*

    **OR**

3.  **Compile using Make (if a Makefile is provided):**
    *(If you don't have one, you can create a simple `Makefile` like the example below)*
    ```bash
    make
    ```
