# C Simple Line Editor — User Manual

All commands are entered interactively at the `editor>` prompt.

## Commands Reference

1. **display**
   * Prints all document lines with 1-based indexing.
   * Usage: `display`

2. **insert <line_number> <text>**
   * Inserts text at the target line position.
   * Usage: `insert 1 Hello World`

3. **delete <line_number>**
   * Removes line at specified number.
   * Usage: `delete 1`

4. **save <filename>**
   * Saves document in memory to text file.
   * Usage: `save doc.txt`

5. **load <filename>**
   * Loads document contents from a text file.
   * Usage: `load doc.txt`

6. **search <phrase>**
   * Searches for word or phrase occurrences.
   * Usage: `search Hello`

7. **stats**
   * Reports line count and word count statistics.
   * Usage: `stats`

8. **exit**
   * Terminates editor.
   * Usage: `exit`