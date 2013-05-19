/* test_helper.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#define FIRST_CONTEXT(description) next_description(description);
#define CONTEXT(description) push_description(description);
#define NEXT_CONTEXT(description) next_description(description);
#define END_CONTEXT pop_description();

int expect(int result, char *message);
int expect_not(int result, char *message);

int intEqual(int left, int right);

int dblEqual(double left, double right);
int ptrEqual(void *left, void *right);