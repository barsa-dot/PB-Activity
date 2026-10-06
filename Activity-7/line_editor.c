#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define INITIAL_CAPACITY 10

typedef struct {
    char **lines;
    int count;
    int capacity;
} LineEditor;

void initEditor(LineEditor *ed) {
    ed->count = 0;
    ed->capacity = INITIAL_CAPACITY;
    ed->lines = (char **)malloc(ed->capacity * sizeof(char *));
    if (!ed->lines) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

void freeEditor(LineEditor *ed) {
    for (int i = 0; i < ed->count; i++) {
        free(ed->lines[i]);
    }
    free(ed->lines);
}

void displayDocument(const LineEditor *ed) {
    if (ed->count == 0) {
        printf("--- Document is empty ---\n");
        return;
    }
    printf("\n--- Document Start ---\n");
    for (int i = 0; i < ed->count; i++) {
        printf("%3d | %s\n", i + 1, ed->lines[i]);
    }
    printf("--- Document End ---\n");
}

void insertLine(LineEditor *ed, int lineNum, const char *text) {
    if (lineNum < 1 || lineNum > ed->count + 1) {
        printf("Error: Line number %d out of bounds (Valid: 1 to %d).\n", lineNum, ed->count + 1);
        return;
    }

    if (ed->count >= ed->capacity) {
        ed->capacity *= 2;
        ed->lines = (char **)realloc(ed->lines, ed->capacity * sizeof(char *));
        if (!ed->lines) {
            perror("Reallocation failed");
            exit(EXIT_FAILURE);
        }
    }

    int idx = lineNum - 1;
    for (int i = ed->count; i > idx; i--) {
        ed->lines[i] = ed->lines[i - 1];
    }

    ed->lines[idx] = (char *)malloc(strlen(text) + 1);
    strcpy(ed->lines[idx], text);
    ed->count++;
    printf("Line inserted successfully at line %d.\n", lineNum);
}

void deleteLine(LineEditor *ed, int lineNum) {
    if (lineNum < 1 || lineNum > ed->count) {
        printf("Error: Line number %d out of bounds (Valid: 1 to %d).\n", lineNum, ed->count);
        return;
    }

    int idx = lineNum - 1;
    free(ed->lines[idx]);

    for (int i = idx; i < ed->count - 1; i++) {
        ed->lines[i] = ed->lines[i + 1];
    }

    ed->count--;
    printf("Line %d deleted successfully.\n", lineNum);
}

void saveFile(const LineEditor *ed, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < ed->count; i++) {
        fprintf(fp, "%s\n", ed->lines[i]);
    }

    fclose(fp);
    printf("Document saved to '%s' successfully.\n", filename);
}

void loadFile(LineEditor *ed, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Could not open file '%s'.\n", filename);
        return;
    }

    for (int i = 0; i < ed->count; i++) {
        free(ed->lines[i]);
    }
    ed->count = 0;

    char buffer[MAX_LINE_LEN];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        insertLine(ed, ed->count + 1, buffer);
    }

    fclose(fp);
    printf("Document loaded from '%s' successfully.\n", filename);
}

void searchPhrase(const LineEditor *ed, const char *phrase) {
    if (ed->count == 0) {
        printf("Document is empty.\n");
        return;
    }

    int matches = 0;
    printf("\n--- Search Results for '%s' ---\n", phrase);
    for (int i = 0; i < ed->count; i++) {
        if (strstr(ed->lines[i], phrase) != NULL) {
            printf("Line %d: %s\n", i + 1, ed->lines[i]);
            matches++;
        }
    }

    if (matches == 0) {
        printf("No matches found for phrase '%s'.\n", phrase);
    } else {
        printf("Found %d matching line(s).\n", matches);
    }
}

void printStats(const LineEditor *ed) {
    int totalWords = 0;

    for (int i = 0; i < ed->count; i++) {
        char temp[MAX_LINE_LEN];
        strcpy(temp, ed->lines[i]);
        char *token = strtok(temp, " \t\n");
        while (token != NULL) {
            totalWords++;
            token = strtok(NULL, " \t\n");
        }
    }

    printf("\n--- Document Statistics ---\n");
    printf("Total Lines: %d\n", ed->count);
    printf("Total Words: %d\n", totalWords);
}

int main() {
    LineEditor ed;
    initEditor(&ed);

    char input[MAX_LINE_LEN];
    char command[32];

    printf("=======================================\n");
    printf("      C Simple Line Editor v1.0        \n");
    printf("  Type 'help' for available commands.  \n");
    printf("=======================================\n");

    while (1) {
        printf("\neditor> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\r\n")] = 0;
        if (strlen(input) == 0) continue;

        sscanf(input, "%s", command);

        if (strcmp(command, "display") == 0) {
            displayDocument(&ed);
        } 
        else if (strcmp(command, "insert") == 0) {
            int lineNum;
            char text[MAX_LINE_LEN] = "";
            if (sscanf(input, "%*s %d %[^\n]", &lineNum, text) >= 1) {
                insertLine(&ed, lineNum, text);
            } else {
                printf("Usage: insert <line_number> <text>\n");
            }
        } 
        else if (strcmp(command, "delete") == 0) {
            int lineNum;
            if (sscanf(input, "%*s %d", &lineNum) == 1) {
                deleteLine(&ed, lineNum);
            } else {
                printf("Usage: delete <line_number>\n");
            }
        } 
        else if (strcmp(command, "save") == 0) {
            char filename[128];
            if (sscanf(input, "%*s %s", filename) == 1) {
                saveFile(&ed, filename);
            } else {
                printf("Usage: save <filename.txt>\n");
            }
        } 
        else if (strcmp(command, "load") == 0) {
            char filename[128];
            if (sscanf(input, "%*s %s", filename) == 1) {
                loadFile(&ed, filename);
            } else {
                printf("Usage: load <filename.txt>\n");
            }
        } 
        else if (strcmp(command, "search") == 0) {
            char phrase[MAX_LINE_LEN];
            if (sscanf(input, "%*s %[^\n]", phrase) == 1) {
                searchPhrase(&ed, phrase);
            } else {
                printf("Usage: search <phrase>\n");
            }
        } 
        else if (strcmp(command, "stats") == 0) {
            printStats(&ed);
        } 
        else if (strcmp(command, "help") == 0) {
            printf("\nCommands Summary:\n");
            printf("  display                   - Display current lines with line numbers\n");
            printf("  insert <line_no> <text>   - Insert text at given line number\n");
            printf("  delete <line_no>          - Delete specified line\n");
            printf("  save <filename>           - Save document to a file\n");
            printf("  load <filename>           - Load document from a file\n");
            printf("  search <phrase>           - Search for text across document\n");
            printf("  stats                     - Show line count and word count\n");
            printf("  exit                      - Exit the program\n");
        } 
        else if (strcmp(command, "exit") == 0) {
            printf("Exiting line editor. Goodbye!\n");
            break;
        } 
        else {
            printf("Unknown command '%s'. Type 'help' for instructions.\n", command);
        }
    }

    freeEditor(&ed);
    return 0;
}