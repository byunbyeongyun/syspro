#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int compare_books(const void *a, const void *b) {
    const struct book *bookA = (const struct book *)a;
    const struct book *bookB = (const struct book *)b;
    if (bookA->numofborrow < bookB->numofborrow) {
        return 1;
    } else if (bookA->numofborrow > bookB->numofborrow) {
        return -1;
    } else {
        return 0; 
	}
}

int main(int argc, char *argv[]) {
    int fd;
    struct book *records = NULL; 
    size_t record_size = sizeof(struct book);
    long num_records = 0; 
    int filter_option;

    if (argc < 2) {
        fprintf(stderr, "How to use: %s file\\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    if (file_size > 0 && record_size > 0) {
        num_records = file_size / record_size;
    } else {
        num_records = 0;
    }
    
    if (num_records == 0) {
        printf("---bookquery---\\n");
        printf("No records found in the file: %s\\n", argv[1]);
        close(fd);
        exit(0);
    }

    records = (struct book *)malloc(num_records * record_size);
    if (records == NULL) {
        perror("malloc failed");
        close(fd);
        exit(3);
    }

    if (read(fd, records, num_records * record_size) != num_records * record_size) {
        perror("read failed");
        free(records);
        close(fd);
        exit(4);
    }

    qsort(records, num_records, record_size, compare_books);
    printf("---bookquery---\n");
    printf("List of all books, sorted by numofborrow (descending):\n");
    printf("0: List all books\n");
    printf("1: List only borrowed books (borrow != 'F')\\n");
    printf("Enter option (0 or 1): ");
    if (scanf("%d", &filter_option) != 1) {
        fprintf(stderr, "Invalid input. Exiting.\\n");
        free(records);
        close(fd);
        exit(5);
    }
    while (getchar() != '\\n'); 
    printf("\\n--- Sorted Book List ---\\n");
    printf("%-3s %-10s %-10s %-6s %-12s %-6s\\n","id", "bookname", "author", "year", "numofborrow", "borrow");
           
    for (long i = 0; i < num_records; i++) {
        if (records[i].id == 0) { 
            continue;
        }

        int should_print = 0;
        
        if (filter_option == 0) {
            should_print = 1;
        } else if (filter_option == 1) {
            if (records[i].borrow[0] != 'F') { 
                should_print = 1;
            }
        }
        
        if (should_print) {
            printf("%3d %10s %10s %6d %12d %6s\\n",
                   records[i].id, 
                   records[i].bookname, 
                   records[i].author, 
                   records[i].year, 
                   records[i].numofborrow, 
                   records[i].borrow);
        }
    }
    free(records);
    close(fd);
    
    exit(0);
}
