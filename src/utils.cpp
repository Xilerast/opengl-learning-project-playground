#include "config.h"

/**
 * @brief finds file size with fseek
 * 
 * @param fileName path to file
 * @return long file size
 */
long findFileSize(const char *fileName)
{
    FILE *fp = fopen(fileName, "r");

    if (!fp) {
        fprintf(stderr, "Could not open file!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    return ftell(fp);
}

/**
 * @brief Reads a file line by line on a 256 size char buffer and prints the context to the console
 * 
 * @param fileName 
 */
void printFileContents(const char *fileName, char **strOutput, long strOutputSize, bool printToConsole)
{
    FILE *fp;
    fp = fopen(fileName, "r");

    char line[256];

    size_t remaining = strOutputSize;
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (printToConsole) {
                printf("%s", line);
            }
            if (strOutput && strncmp(line, "\n", 2)) {
                strncat(*strOutput, line, remaining);
                remaining -= sizeof(line);
            }
        }

        if (printToConsole) {
            // Just in case we're reading a file without a newline character at the last line
            fflush(stdout);
        }

        fclose(fp);
    } else {
        fprintf(stderr, "Could not open file!\n");
    }
}

/**
 * @brief To be used as a callback each time the viewport is resized
 * 
 * @param window 
 * @param width 
 * @param height 
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}