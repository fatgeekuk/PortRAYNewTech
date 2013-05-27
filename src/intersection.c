/* intersection.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/vectors.h"
#include "../headers/ray.h"
#include "../headers/ring_list.h"
#include "../headers/material.h"
#include "../headers/object.h"
#include "../headers/intersection.h"

/* after the ring_list the intersection is probably the most important and heavily used area. literally BILLIONS of intersections will be created and passed around
   various parts of the renderer. So, this needs to be handled specially. Like rlNodes, these need to be allocated in slabs and reused agressively. */

#define IR_SLAB_WIDTH 64

intRec *irSlabPtr;
int irSlabSize;
int irSlabsUsed;
rlNode *irFreeList;

/* handling initialisation and allocation of ring nodes */
void irInit(){
	irSlabPtr = NULL;
	irSlabSize = 0;	
	irSlabsUsed = 0;
	irFreeList = rlCreateList();
};

void irAllocSlab(){
	irSlabPtr = malloc(sizeof(intRec) * IR_SLAB_WIDTH);
	if (irSlabPtr != NULL){
		irSlabSize = IR_SLAB_WIDTH;
		irSlabsUsed++;
	} else {
		printf("Unable to allocation irSlab\n");
		exit(1);
	}
};

intRec *irGetRecFromSlab(){
	intRec *answer;
	if (irSlabSize == 0) irAllocSlab();

	answer = irSlabPtr;
	irSlabPtr++;
	irSlabSize--;
	return answer;
}

void irReleaseRec(intRec *rec){
	rlAddDataToHead(irFreeList, rec);
}

void *irGetRecFromFreeList(){
	intRec *answer;
	
	if (rlListEmpty(irFreeList)){
		answer = NULL;
	} else {
		answer = rlPopDataFromHead(irFreeList);
	}
	return answer;
}

intRec *irGetRec(){
	intRec *answer;
	
	answer = irGetRecFromFreeList();
	if (answer == NULL) answer = irGetRecFromSlab();
	return answer;
}

rlNode *irCreateList(){
	return rlCreateList();
}

intRec *irAddRec(rlNode *list){
	intRec *answer = irGetRec();
	rlAddDataToTail(list, answer);
	return answer;
}

void irReclaimList(rlNode *list){
	while(rlListEmpty(list) == 0){
		irReleaseRec((intRec *)rlPopDataFromHead(list));
	}
	rlReclaimList(list);	
}

rlNode *irMergeLists(rlNode *a, rlNode *b){
	/* NOTE, this is destructive, lists a and b are released */
	rlNode *answer;
	intRec *rec;
	int done = 0;
	
	answer = irCreateList();
	
	while (!done){
		if(rlListEmpty(a)){
			/* copy over remains of b */
			while (rlListEmpty(b) == 0){
				rlAddDataToTail(answer, rlPopDataFromHead(b));
			}
			done = -1;
		}

		if (rlListEmpty(b)){
			/* copy over remains of a */
			while (rlListEmpty(a) == 0){
				rlAddDataToTail(answer, rlPopDataFromHead(a));
			}
			done = -1;
		}

		if (done == 0){
			/* both lists contain at least one item */
			if (((intRec *)(a->next->data))->dist > ((intRec *)(b->next->data))->dist){
				rlAddDataToTail(answer, rlPopDataFromHead(b));
			} else {
				rlAddDataToTail(answer, rlPopDataFromHead(a));
			}
		}
	}
	
	/* at this point, both a and b are empty */
	rlReclaimList(a);
	rlReclaimList(b);
	
	return answer;
}
