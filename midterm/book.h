#define START_ID 1
#define MAX 24
struct book {
	int id;
	char bookname[MAX];
	char author[MAX];
	int year;
	int numofborrow;
	char borrow[MAX];
};
