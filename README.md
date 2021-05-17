# misc-c-utils

This is basically just a repository to host an assortment of small C programs
I've written, mostly as an aid to writing more portable shell scripts.

Some of these utilities are of my own design to simplify specific tasks.
For instance:

* `case-insensitive-pattern.c`:
  * given a string (either given as command-line
  argument(s) or on standard input), prints out a regex pattern that can be
  used with `sed` and the like to match the string, ignoring case.
  * This can be useful because, while `-i` works to do these matches in POSIX
    `grep`, POSIX `sed` has no such provisions. 
  * `example text` becomes `[Ee][Xx][Aa][Mm][Pp][Ll][Ee] [Tt][Ee][Xx][Tt]`

* `quotify.c`:
  * Somewhat intelligently replaces "double quotes" with “curly quotes” (in
    UTF-8).
  * Reads input from either a supplied file name or `stdin` (stdin is used if
    no arguments are passed or the argument `-` is passed).
  * This doesn't use any clever data structures to track the current state or
    anything, and it doesn't peek ahead, so it **will** fail if you have
    nested double quotes. **Caveat emptor**.
  * Handy for some simple cases, like while preparing text for conversion into
    an e-book.

* `wineify.c`:
  * This one is highly specific and probably not well suited for any task.
    It tries to guess what that is being passed to it is a command-line
    flag and what isn't; if it doesn't think something's a command-line
    flag it assumes it is a filename and runs it through `winepath -w`,
    printing a null-terminated result (suitable for GNU xargs' `xargs -0`).
    This exists solely to wrap around Photoshop in wine so that I can pass
    it unix file names/paths and have them open properly. If something is
    probably not a filename, it gets passed through unchanged with a null
    terminator on the end. This also uses `popen()`, so it's pretty much
    as insecure as the `system()` call is. Don't use this unless you really
    understand what it is doing.

Others tools are inspired by GNU-only, BSD-only, and other system-specific
programs or command options which I have found useful and wish to be able to
replicate in scripts on a wider array of Unix-like machines. 



Examples:

* `sleep-decimal`: pause for a number of seconds, which can be given in
  fractional seconds. POSIX `sleep` only guarantees second granularity.
  * GNU `sleep` can also idle for fractional seconds, but this is not a
    requirement for POSIX compliance and should not be counted on.
* `realpath-posix.c`: essentially a wrapper around POSIX's `realpath()` C
  function so it can be used in shell scripts.
  * GNU `readlink` can also do this with the `-f` parameter, but `readlink` is
  not a POSIX-defined program.
  * This should follow multiple symlinks until it finds an existing file or
  fails to resolve.

By the way, to this end (the ability to use the in shell scripts on many
kinds of machines), all of these C programs (currently) target POSIX-compliant
platforms, using only C standard library and POSIX-specified C functions.

I know this means Windows is left out in the cold, but if you really want to
I'm certain they will still work in Cygwin. Some might even work in plain MinGW
with the MS Visual C++ runtime, since not all of them even use POSIX functions
at all. One gotcha might be having to make sure '`b`' is included in the mode
string for `fopen()` calls, since Windows/DOS historically have liked to mess
with text files otherwise (mostly newline tampering). This has not been tested
here, but is still a common problem in other C programs.