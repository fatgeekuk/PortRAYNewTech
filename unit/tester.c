/* tester.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdio.h>
#include <stdlib.h>

#include "test_index.h"
char *description_stack[100];
int description_ptr = 0;

int total = 0;
int failed = 0;
int passed = 0;

char *colouredText = "\33[%dm%s\33[0m";
int RED = 31;
int GREEN = 32;

typedef struct failure {
	char *message;
	void *next;
	} failureNode;

typedef struct node {
	char *description;
	void *next;
	void *child;
	failureNode *failure;
} reportNode;

reportNode *reportBase = NULL;
reportNode *current = NULL;


void walkTree(reportNode *node, int depth){
	int i;
	failureNode *fail;
	
	for (i=0; i<depth; i++){
		printf("  ");
	}
	printf("%s",  node->description);
	
	if (treePassing(node, 0)){
		printf(colouredText, GREEN, " PASSED!");
		printf("\n");
	} else {
		printf("\n");
		fail = node->failure;
		while(fail != NULL){
			for (i=0; i<depth+2; i++){
				printf("  ");
			}
			printf(colouredText, RED,  fail->message);
			printf("\n");
			fail = fail->next;
		}

		if(node->child != NULL){
			walkTree(node->child, depth + 1);
		}
		
		
	}
	if(node->next != NULL){
		walkTree(node->next, depth);
	}
	
}

int treePassing(reportNode *node, int followSib){
	if (node->failure == NULL){
		if (node->child != NULL){
			if (treePassing(node->child, -1) == 0){
				return 0;
			}
		}
		if (followSib != 0 && node->next != NULL){
			if (treePassing(node->next, -1) == 0){
				return 0;
			}
		}
	} else {
		return 0;
	}
	return -1;
}

reportNode *get_new_node(char *description){
	reportNode *newNode;
	newNode = (reportNode *)malloc(sizeof(reportNode));
	newNode->description = description;
	newNode->next = NULL;
	newNode->child = NULL;
	newNode->failure = NULL;
	return newNode;	
}

failureNode *record_failure(char *message){
	failureNode *newFailure;
	newFailure = (failureNode *)malloc(sizeof(failureNode));
	newFailure->message = message;
	newFailure->next = current->failure;
	current->failure = newFailure;
}

void push_description(char *description){
	int i;
	reportNode *newNode;
	newNode = get_new_node(description);
	newNode->next = NULL;
	newNode->child = NULL;
	if (reportBase == NULL){
		reportBase = newNode;
	} else {
		current->child = newNode;
	}
	current = newNode;
}

void next_description(char *description){
	reportNode *newNode;
	newNode = get_new_node(description);
	current->next = newNode;
	current = newNode;
}

void pop_description(){
	if(description_ptr > 0) description_ptr--;
}

void expect(int value, char* description){
	total++;
	if (value != -1){
		printf(colouredText, RED, "F");
		record_failure(description);
		failed++;
	} else {
		printf(colouredText, GREEN, ".");
		passed++;
	}
}

void expect_not(int value, char* description){
	expect(value == -1 ? 0 : -1, description);
}

int main(){
	int i, result;
	char buffer[200];
	
	printf("We have %d tests\n", test_count);
	for(i=0; i<test_count; i++){
		(tests[i])();
	}
	printf("\n\n");
	
	sprintf(buffer, "Total(%d expectations)", total);
	printf(colouredText, 0, buffer);
	
	sprintf(buffer, " Passed(%d)", passed);
	printf(colouredText, GREEN, buffer);
	if (failed > 0){
		sprintf(buffer, " Failed(%d)", failed);
		printf(colouredText, RED, buffer);
	}
	printf("\n\n");

	walkTree(reportBase, 0);

	return(failed);
}
