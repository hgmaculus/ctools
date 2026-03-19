#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMINFO_PATH "/proc/meminfo"
#define BUFFER_SIZE 256

int main() {
    FILE *file = fopen(MEMINFO_PATH, "r");
    if (file == NULL) {
        perror("Error opening /proc/meminfo");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    long long mem_available_kb = 0;
    long long cached_kb = 0;
    int found_available = 0;
    int found_cached = 0;

    // Read the file line by line
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        // Check for "MemAvailable:"
        if (sscanf(buffer, "MemAvailable: %lld kB", &mem_available_kb) == 1) {
            found_available = 1;
        }
        // Check for "Cached:"
        if (sscanf(buffer, "Cached: %lld kB", &cached_kb) == 1) {
            found_cached = 1;
        }

        // Stop if both values are found
        if (found_available && found_cached) {
            break;
        }
    }

    fclose(file);

    if (found_available && found_cached) {
        printf("Available Memory: %lld kB (approx. %.2f MiB)\n", mem_available_kb, (double)mem_available_kb / 1024.0);
        printf("Cached Memory: %lld kB (approx. %.2f MiB)\n", cached_kb, (double)cached_kb / 1024.0);
    } else {
        printf("Could not find both MemAvailable and Cached fields in %s.\n", MEMINFO_PATH);
        printf("MemAvailable might not be available on very old kernel versions; use (MemFree + Buffers + Cached) instead.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
