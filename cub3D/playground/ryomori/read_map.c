#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

#define MAX_LINES 100  // ファイルの最大行数を定義（必要に応じて調整）

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newarray;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	newarray = malloc(sizeof(char) * (len + 1));
	if (newarray == NULL)
		return (NULL);
	while (*s1)
		newarray[i++] = *s1++;
	while (*s2)
		newarray[i++] = *s2++;
	newarray[i] = 0;
	return (newarray);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (0);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*newarray;
	char	*tmparray;
	size_t	i;

	newarray = malloc(sizeof(char) * (len + 1));
	if (!newarray)
		return (NULL);
	tmparray = (char *)str + start;
	i = 0;
	while (*tmparray && i < len)
		newarray[i++] = *tmparray++;
	newarray[i] = 0;
	return (newarray);
}

char	*ft_strdup(const char *str)
{
	return (ft_substr(str, 0, ft_strlen(str)));
}

static void	free_buffer(char **buffer)
{
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static char	*get_result(int nl_num, char **buffer_s)
{
	char	*result;
	char	*tmp;

	tmp = NULL;
	if (nl_num <= 0)
	{
		if (**buffer_s == '\0')
		{
			free(*buffer_s);
			*buffer_s = NULL;
			return (NULL);
		}
		result = *buffer_s;
		*buffer_s = NULL;
		return (result);
	}
	tmp = ft_substr(*buffer_s, nl_num, BUFFER_SIZE);
	result = *buffer_s;
	result[nl_num] = '\0';
	*buffer_s = tmp;
	return (result);
}

static char	*rd_file(int fd, char **buffer_save, char *buf)
{
	ssize_t	count_byt;
	char	*tmp;

	tmp = NULL;
	count_byt = 0;
	while (ft_strchr(*buffer_save, '\n') == NULL)
	{
		count_byt = read(fd, buf, BUFFER_SIZE);
		if (count_byt < 0)
		{
			free_buffer(buffer_save);
			return (NULL);
		}
		if (count_byt == 0)
			return (get_result(count_byt, buffer_save));
		buf[count_byt] = '\0';
		tmp = ft_strjoin(*buffer_save, buf);
		if (tmp == NULL)
			return (free_buffer(buffer_save), NULL);
		free_buffer(buffer_save);
		*buffer_save = tmp;
	}
	return (get_result((ft_strchr(*buffer_save, '\n')
				- *buffer_save) + 1, buffer_save));
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf_baket;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf_baket = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf_baket == NULL)
		return (NULL);
	if (!save)
	{
		save = ft_strdup("");
		if (save == NULL)
		{
			free(buf_baket);
			free(save);
			return (NULL);
		}
	}
	result = rd_file(fd, &save, buf_baket);
	free_buffer(&buf_baket);
	return (result);
}

// int main ()
// {
// 	int		fd;
// 	int		i;
// 	char	*s;

// 	fd = open("cat.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		s =  get_next_line(fd);
// 		printf("%s",s);
// 		free(s);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }


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
