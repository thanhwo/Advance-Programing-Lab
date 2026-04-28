#include <stdio.h>
#include <string.h>
#include <dirent.h>

int contains_word(const char *filename, const char *word) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) return 0;
	char line[256];
	while (fgets(line, sizeof(line), fp)) {
		if (strstr(line, word) != NULL) {
		fclose(fp);
		return 1;
		}
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 3) { printf("Usage: %s <word> <directory>\n", argv[0]);
	return 1;
	}
	DIR *dir = opendir(argv[2]);
	if (dir == NULL) { perror("Cannot open directory");
	return 1;
	}
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
	// Bỏ qua . và ..
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		continue;
	// Kiểm tra file có chứa từ khóa không
		if (contains_word(entry->d_name, argv[1])) {
			printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
	return 0;
}
