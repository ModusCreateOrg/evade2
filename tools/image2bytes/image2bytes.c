#include "image2bytes.h"

int main(int argc, char **argv) {
    int i, opt;
    Bytes *bytes;
    arguments.verbosity = 0;

    /* Parse options */
    while ((opt = getopt(argc, argv, "hvo:")) != -1) {
        switch (opt) {
            case 'v': arguments.verbosity += 1; break;
            case 'o': arguments.output = optarg; break;
            case 'h':
            default: fprintf(stderr, USAGE "\n"); exit(1);
        }
    }

    /* Parse arguments */
    if (optind >= argc) {
        fprintf(stderr, USAGE "\n");
        exit(1);
    } else {
        arguments.images = &argv[optind];
    }

    for (i = 0; arguments.images[i]; i++) {
        bytes = image_to_bytes(arguments.images[i]);

        if (arguments.output) {
            export_bytes(bytes);
        } else {
            print_bytes(bytes);
        }

        if (arguments.verbosity > 1) {
            bytes_to_ascii(bytes);
        }

        free_bytes(bytes);
    }

    exit(0);
}

/**
 * Load image from file and convert to 1 byte per channel
 * Read pixel data starting from top left corner vertically
 * 1 byte at a time and shift right, repeat
 */
Bytes *image_to_bytes(char *const file) {
    Bytes *bytes;
    unsigned char *tmp_data;
    unsigned char byte = 0x00;
    unsigned long int bytes_index = 1;
    int i, x, y, width, height, channels;
    unsigned char *const image = stbi_load(file, &width, &height, &channels, STBI_grey);

    if (image == NULL) {
        fprintf(stderr, ERR RD_FAIL " %s\n" RST, file);
        exit(1);
    }

    if (width > 255 || height > 255) {
        fprintf(stderr, ERR SZ_FAIL " (%ix%i)\n" RST, width, height);
        stbi_image_free(image);
        exit(1);
    }

    bytes = malloc(sizeof(Bytes));

    if (bytes == NULL) {
        stbi_image_free(image);
        fprintf(stderr, ERR NO_MEM " %lu bytes\n" RST, sizeof(Bytes));
        exit(1);
    }

    bytes->file = basename(file);
    bytes->length = (ceil(height /  8.0) * width + 2) / sizeof(char);
    bytes->data = malloc(bytes->length);

    if (bytes->data == NULL) {
        free(bytes);
        stbi_image_free(image);
        fprintf(stderr, ERR NO_MEM " %lu bytes\n" RST, (bytes->length * sizeof(char*)));
        exit(1);
    }

    if (arguments.verbosity) {
        printf(OK "Loaded file: %s\n" RST, bytes->file);
    }

    // Use temp storage and set initial data
    tmp_data = bytes->data;
    tmp_data[0] = width;
    tmp_data[1] = height;

    // Byte pages
    for (i = 0; i < height; i += 8) {
        // Times to shift right
        for (x = 0; x < width; ++x) {
            // Fill byte
            for (y = (i * width) + x; y < (i + 8) * width; y += width) {
                // Bail if we overflow
                if (y > width * height) {
                    break;
                }

                if (image[y]) {
                    byte |= 1 << ((y / width) - i);
                }
            }

            // Append to bytes and RST
            tmp_data[++bytes_index] = byte;
            byte = 0x00;
        }
    }

    // Free memory and return
    stbi_image_free(image);
    return bytes;
}

/**
 * Write bytes to file
 */
void export_bytes(const Bytes *bytes) {
    char *renamed_file = replace_file_ext(bytes->file, ".h");
    char *path = build_path(arguments.output, renamed_file);
    FILE *file = fopen(path, "w");

    if (file == NULL) {
        // Don't exit(1) allow for cleanup
        fprintf(stderr, ERR WR_FAIL " %s\n" RST, path);
        return;
    }

    char *file_const = replace_file_ext(bytes->file, "");
    char *file_var = replace_file_ext(bytes->file, "");
    str_to_var(file_const, '_', 1);
    str_to_var(file_var, '_', 0);

    fprintf(file, "%s%s\n%s%s\n\n%s%s%s\n\t%s\n\t0x%02x, 0x%02x,\n\n\t%s\n\t",
            "#ifndef ", file_const,
            "#define ", file_const,
            "const PROGMEM uint8_t ", file_var, "[] = {",
            "// width, height",
            bytes->data[0], bytes->data[1],
            "//data");

    for (int i = 2; i < bytes->length; ++i) {
        fprintf(file, i == 2 ? "0x%02x" : ", 0x%02x", bytes->data[i]);
    }

    fprintf(file, "\n%s\n\n%s\n", "};", "#endif");
    fclose(file);

    if (arguments.verbosity) {
        printf(OK "Wrote to: %s\n" RST, path);
    }

    free(renamed_file);
    free(path);
}

/**
 * Print byte array to stdout
 */
void print_bytes(const Bytes *bytes) {
    for (int b = 0; b < bytes->length; ++b) {
        printf(b == 0 ? INF "{0x%02x" : ", 0x%02x", bytes->data[b]);
    }
    printf("}\n\n" RST);
}

/**
 * Print byte array as ASCII to stdout
 */
void bytes_to_ascii(const Bytes *bytes) {
    int row, offset, i, pixel;
    const unsigned char *data = bytes->data;

    // Byte pages
    for (row = 0; row < ((bytes->length - 2) / data[0]); ++row) {
        // Bits
        for (offset = 0; offset < 8; ++offset) {
            // Print pixel as char
            for (i = (row * data[0]); i < data[0] * (row + 1); ++i) {
                pixel = data[i + 2] >> offset & ((1 << 1) - 1);
                printf("%c", *(pixel ? "#" : " "));
            }
            printf("\n");
        }
    }
}

/**
 * Free memory allocated to Bytes struct
 */
void free_bytes(Bytes *bytes) {
    free(bytes->data);
    free(bytes);
}

/**
 * Replace file extension
 */
char *replace_file_ext(const char *file, const char *new_ext) {
    char *buffer = malloc((strlen(file) + strlen(new_ext) + 1) * sizeof(char));
    char *dest = buffer;

    if (file[0] == '.') {
        *dest++ = *file++;
    }

    const char *pos = strrchr(file, '.');
    int len = strlen(file);

    if (pos) {
        len = pos - file;
    }

    strncpy(dest, file, len);

    if (strlen(new_ext) > 0) {
        if (new_ext[0] != '.') {
            dest[len++] = '.';
        }
    }

    strcpy(&dest[len], new_ext);
    return buffer;
}

/**
 * Build path from DIR and FILE
 */
char *build_path(const char *dir, const char *file) {
    const int path_size = (strlen(dir) + strlen(file) + 2) * sizeof(char);
    char *path = malloc(path_size);

    if (path == NULL) {
        // Don't exit(1) allow for cleanup
        fprintf(stderr, ERR NO_MEM " %i bytes\n" RST, path_size);
        return NULL;
    }

    strcpy(path, dir);

    if (path[strlen(path) - 1] != *PATH_SEP) {
        strcat(path, PATH_SEP);
    }

    strcat(path, file);
    return path;
}

/**
 * Convert string to a variable-safe name
 */
void str_to_var(char* str, const char rep, const unsigned int is_const) {
    int i = 0;
    while (i < strlen(str)) {
        if (isalnum(str[i])) {
            if (is_const > 0) {
                str[i] = toupper(str[i]);
            }
        } else {
            str[i] = rep;
        }

        i++;
    }
}
