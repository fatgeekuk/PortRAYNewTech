/* intersection_tests.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include "../test_helper.h"
#include "../../headers/ring_list.h"
#include "../../src/intersection.c"

void test_intersection(){
	intRec *a, *b;
	rlNode *l, *l_a, *l_b;
	void *prev_ptr;
	int i;
	
	CONTEXT("Intersections")
		CONTEXT("initialisation")
			rlInit();
			irInit();
			expect(ptrEqual((void *)irSlabPtr, NULL), "slab pointer should be empty");
			expect_not(ptrEqual((void *)irFreeList, NULL), "free list should be allocated");
			expect(ptrEqual((void *)irFreeList, (void *)irFreeList->next), "free list should be empty");
			expect(intEqual(irSlabSize, 0), "slab should be empty");
			expect(intEqual(irSlabsUsed, 0), "no slabs should have been used");
			
		NEXT_CONTEXT("allocating slabs")
			irAllocSlab();
			expect_not(ptrEqual((void *)irSlabPtr, NULL), "there should now be a slab");
			expect(intEqual(irSlabSize, IR_SLAB_WIDTH), "the slab should have the right width");
			expect(intEqual(irSlabsUsed, 1), "one slab should now be used");
			
		NEXT_CONTEXT("allocating from the slab")
			prev_ptr = (void *)irSlabPtr;
			a = irGetRecFromSlab();
			expect_not(ptrEqual((void *)a, NULL), "we should have successfully grabbed from the slab");	
			expect(ptrEqual(prev_ptr + sizeof(intRec), (void *)irSlabPtr), "the slab should have moved");
			expect(intEqual(IR_SLAB_WIDTH - 1, irSlabSize), "size of remaining slab should have been recorded");
			
		NEXT_CONTEXT("exhausting a slab")
			for (i=0; i< 63; i++){
				a = irGetRecFromSlab();
			}
			expect(intEqual(irSlabsUsed, 1), "we should have fully used one slab");
			expect(intEqual(irSlabSize, 0), "and there should be nothing left");
			a = irGetRecFromSlab(); 
			expect(intEqual(irSlabsUsed, 2), "We should now have two slabs");
			
		NEXT_CONTEXT("release a node")
			irReleaseRec(a);
			expect(ptrEqual((void *)irFreeList->next->data, (void *)a), "it should have gone onto the free list");
			expect(ptrEqual((void *)irFreeList->next->next, (void *)irFreeList), "and it should be the only thing on the list");


			
		NEXT_CONTEXT("then request a new node, and get it back")
			b = irGetRec();
			expect(ptrEqual((void*)a, (void*)b), "we get it back");
			expect(ptrEqual((void*)irFreeList->next, (void *)irFreeList), "the free chain should now be empty");

			
		NEXT_CONTEXT("getting another node will pull from the slab")
			i = irSlabSize; 
			a = irGetRec();
			expect_not(ptrEqual((void *)a, NULL), "the newly allocated node should not be null");
			
		NEXT_CONTEXT("creating a list")
			l = irCreateList();
			expect(ptrEqual((void *)l, (void *)l->next), "next should get us back to the beginning");
			expect(ptrEqual((void *)l, (void *)l->prev), "prev should get us back again too");
			expect(ptrEqual((void *)l->data, NULL), "this should be the start node, so it's data should be empty");


		
		NEXT_CONTEXT("adding something to list should work")
			irAddRec(l);
			expect(ptrEqual((void *)l->next->next, (void *)l), "Going from head, forwards through one node and then the next should get back to head");
			expect(ptrEqual((void *)l->prev->prev, (void *)l), "Going from head, backwards through one node and then the next should get back to head");
			expect_not(ptrEqual(l->next->data, (void *)NULL), "The payload should have been recorded");

			
		NEXT_CONTEXT("adding a few more should be fine too")
			irAddRec(l);
			irAddRec(l);
			expect(intEqual(rlListLength(l), 3), "l should have three items");
			expect(intEqual(rlListLength(irFreeList), 0), "Free List should be empty");
			
		NEXT_CONTEXT("destroying a list should free everything")
			expect(intEqual(rlFreeChainLength(), 0), "rl free chain should be empty");
			irReclaimList(l);
			expect(intEqual(rlListLength(irFreeList), 3), "ir free list should now have 3 entries");
			expect(intEqual(rlFreeChainLength(), 1), "rl free chain should now have 1 entry, the other 3 freed entries have been used to carry the three reclaimed intRecs on the irFreeList Dummy!");
			
		NEXT_CONTEXT("it should be able to merge two equal length irLists")
			l_a = irCreateList();
			l_b = irCreateList();
			
			a = irAddRec(l_a); a->dist = 1.0;
			a = irAddRec(l_a); a->dist = 4.0;
			a = irAddRec(l_b); a->dist = 2.0;
			a = irAddRec(l_b); a->dist = 3.0;
			
			l = irMergeLists(l_a, l_b);
			expect(intEqual(rlListLength(l), 4), "list should be 4 items long");
			expect(dblEqual(((intRec *)(l->next->data))->dist, 1.0), "First should have dist of 1.0");
			expect(dblEqual(((intRec *)(l->next->next->data))->dist, 2.0), "Second should have dist of 2.0");
			expect(dblEqual(((intRec *)(l->next->next->next->data))->dist, 3.0), "Third should have dist of 3.0");
			expect(dblEqual(((intRec *)(l->next->next->next->next->data))->dist, 4.0), "First should have dist of 1.0");
			
		/*

			
		NEXT_CONTEXT("adding to the tail should work too")
			rlAddDataToTail(a, (void *)0x0d);
			rlAddDataToTail(a, (void *)0x0e);
			rlAddDataToTail(a, (void *)0x0f);
			expect(ptrEqual((void *)a->next->data, (void *)0x0a), "A should be first as it was last");
			expect(ptrEqual((void *)a->next->next->data, (void *)0x0b), "B should be next");
			expect(ptrEqual((void *)a->next->next->next->data, (void *)0x0c), "C should be last as it was first");
			expect(ptrEqual((void *)a->next->next->next->next->data, (void *)0x0d), "D was added from the tail first, so");
			expect(ptrEqual((void *)a->next->next->next->next->next->data, (void *)0x0e), "Then E");
			expect(ptrEqual((void *)a->next->next->next->next->next->next->data, (void *)0x0f), "and finally F");
			expect(ptrEqual((void *)a->next->next->next->next->next->next->next->data, NULL), "Going all the way round should get us back to the start again");
			
		NEXT_CONTEXT("reclaiming a list should be cheap, irrespective of length")
			i = rlFreeChainLength();
			expect(intEqual(i, 0), "free chain should be empty");
			
			rlReclaimList(a);
			expect(intEqual(i+7, rlFreeChainLength()), "the 6 items plus their header are 7!");
		
		NEXT_CONTEXT("pulling items of the head of the list is easy")
			a = rlCreateList();
			rlAddDataToTail(a, (void *)0x0a);
			rlAddDataToTail(a, (void *)0x0b);
			rlAddDataToTail(a, (void *)0x0c);
			expect(intEqual(0, rlListEmpty(a)), "List is not currently empty");
			expect(intEqual(3, rlListLength(a)), "in fact, list should be three long");
			
			i = (int)rlPopDataFromHead(a);
			expect(intEqual(i, 0x0a), "first thing pulled off is 'a'");
			
			i = (int)rlPopDataFromHead(a);
			expect(intEqual(i, 0x0b), "second thing pulled off is 'b'");

			i = (int)rlPopDataFromHead(a);
			expect(intEqual(i, 0x0c), "last thing pulled off is 'c'");
			
			expect(intEqual(-1, rlListEmpty(a)), "the list should now be empty");

		*/	
		END_CONTEXT
	END_CONTEXT
}