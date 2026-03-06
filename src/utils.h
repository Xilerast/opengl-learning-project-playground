#pragma once

long findFileSize(const char *fileName);
void printFileContents(const char *fileName, char **strOutput, long strOutputSize, bool printToConsole);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);