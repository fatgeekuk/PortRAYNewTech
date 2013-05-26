/* ringlist.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdio.h>
#include "../headers/ring_list.h"

#define SLAB_WIDTH 1024

rlNode *rlSlabPtr;
int rlSlabSize;
int rlSlabsUsed;
rlNode *rlFreeChainPtr;

/* handling initialisation and allocation of ring nodes */
void rlInit(){
	rlSlabPtr = NULL;
	rlSlabSize = 0;	
	rlSlabsUsed = 0;
	rlFreeChainPtr = NULL;
};

void rlAllocSlab(){
	rlSlabPtr = malloc(sizeof(rlNode) * SLAB_WIDTH);
	if (rlSlabPtr != NULL){
		rlSlabSize = SLAB_WIDTH;
		rlSlabsUsed++;
	} else {
		printf("Unable to allocation rlSlab\n");
		exit(1);
	}
};

rlNode *rlGetNodeFromSlab(){
	rlNode *answer;
	if (rlSlabSize == 0) rlAllocSlab();

	answer = rlSlabPtr;
	rlSlabPtr++;
	rlSlabSize--;
	return answer;
}

void displayFreeChain(){
	rlNode *node;
	node = rlFreeChainPtr;
	printf("\n FREECHAIN ");
	while (node != NULL){
		printf(" -> %X ", node);
		node = node->next;
	}
	printf("\n");
}

void *rlReleaseNode(rlNode *node){
	void *answer;
	
	answer = node->data;
	node->next = rlFreeChainPtr;
	rlFreeChainPtr = node;
	
	return answer;
}

void *rlGetNodeFromFreeChain(){
	rlNode *answer;
	answer = rlFreeChainPtr;
	if (answer != NULL) rlFreeChainPtr = answer->next;
	return answer;
}

rlNode *rlGetNode(){
	rlNode *answer;
	
	answer = rlGetNodeFromFreeChain();
	if (answer == NULL) answer = rlGetNodeFromSlab();
	return answer;
}

rlNode *rlCreateList(){
	rlNode *answer;
	answer = rlGetNode();
	answer->prev=answer;
	answer->next=answer;
	answer->data=NULL;
	return answer;
}

rlNode *rlAddDataToHead(rlNode *list, void *a){
	rlNode *answer;
	
	answer = rlGetNode();
	answer->data = a;
	
	answer->next = list->next;
	answer->prev = list;
	list->next->prev = answer;
	list->next = answer;
	
	return answer;
}

rlNode *rlAddDataToTail(rlNode *list, void *a){
	return rlAddDataToHead(list->prev, a);
}

/* riding the free chain is linearly expensive, so don't do it. */
int rlFreeChainLength(){
	int answer = 0;
	rlNode *coaster;
	
	coaster = rlFreeChainPtr;
	while(coaster != NULL){
		answer++;
		coaster = coaster->next;
	}
	return answer;
}

int rlListLength(rlNode *list){
	int answer = 0;
	rlNode *coaster;
	
	coaster = list->next;
	while(coaster->data != NULL){
		answer++;
		coaster = coaster->next;
	}
	return answer;	
}

void rlReclaimList(rlNode *list){
	list->prev->next = rlFreeChainPtr;
	rlFreeChainPtr = list;
}

void *rlPopDataFromHead(rlNode *list){
	rlNode *firstNode = list->next;
	
	/* remove node from list */
	firstNode->prev->next = firstNode->next;
	firstNode->next->prev = firstNode->prev;
	
	return rlReleaseNode(firstNode);
}

int rlListEmpty(rlNode *list){
	if (list->next == list){
		return -1;
	}
	else
	{
		return 0;
	}
}