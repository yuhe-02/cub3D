#include <stdio.h>
#include <stdlib.h>

// ファイルを読み込んで char** に格納する関数
char **read_file_to_char_array(const char *filename, int *line_count) {
    char **lines = malloc(MAX_LINES * sizeof(char *));
    if (!lines) {
        perror("Failed to allocate memory for lines");
        return NULL;
    }

    *line_count = 0;
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        free(lines);
        return NULL;
    }

    int fd = fileno(file); // ファイル記述子を取得
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        lines[*line_count] = line;
        (*line_count)++;

        // MAX_LINESを超えた場合のエラーチェック
        if (*line_count >= MAX_LINES) {
            fprintf(stderr, "File exceeds maximum line limit (%d lines)\n", MAX_LINES);
            free(line);
            break;
        }
    }

    fclose(file);
    return lines;
}

// メモリを解放する関数
void free_char_array(char **lines, int line_count) {
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main() {
    const char *filename = "test.txt"; // 読み込むファイル名
    int line_count = 0;

    // ファイルを読み込んで char** に格納
    char **lines = read_file_to_char_array(filename, &line_count);
    if (!lines) {
        return 1;
    }

    // 読み込んだ内容を表示
    printf("Loaded %d lines from file:\n", line_count);
    for (int i = 0; i < line_count; i++) {
        printf("Line %d: %s", i, lines[i]); // get_next_lineの結果には改行が含まれている
    }

    // 1文字ずつ確認
    printf("\nCharacter breakdown:\n");
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; lines[i][j] != '\0'; j++) {
            printf("lines[%d][%d] = '%c'\n", i, j, lines[i][j]);
        }
    }

    // メモリを解放
    free_char_array(lines, line_count);

    return 0;
}
