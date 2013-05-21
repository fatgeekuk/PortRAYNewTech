/* ring_list_tests.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include "../test_helper.h"
#include "../../src/ring_list.c"

void test_ring_lists(){
	rlNode *a, *b;
	void *prev_ptr;
	int i;
	
	CONTEXT("RingLists")
		CONTEXT("initialisation")
			rlInit();
			expect(ptrEqual((void *)rlSlabPtr, NULL), "slab pointer should be empty");
			expect(ptrEqual((void *)rlFreeChainPtr, NULL), "free chain should be empty");
			expect(intEqual(rlSlabSize, 0), "slab should be empty");
			expect(intEqual(rlSlabsUsed, 0), "no slabs should have been used");
			
		NEXT_CONTEXT("allocating slabs")
			rlAllocSlab();
			expect_not(ptrEqual((void *)rlSlabPtr, NULL), "there should now be a slab");
			expect(intEqual(rlSlabSize, SLAB_WIDTH), "the slab should have the right width");
			expect(intEqual(rlSlabsUsed, 1), "one slab should now be used");
			
		NEXT_CONTEXT("allocating from the slab")
			prev_ptr = (void *)rlSlabPtr;
			a = rlGetNodeFromSlab();
			expect_not(ptrEqual((void *)a, NULL), "we should have successfully grabbed from the slab");	
			expect(ptrEqual(prev_ptr + sizeof(rlNode), (void *)rlSlabPtr), "the slab should have moved");
			expect(intEqual(SLAB_WIDTH - 1, rlSlabSize), "size of remaining slab should have been recorded");
			
			
		NEXT_CONTEXT("exhausting a slab")
			for (i=0; i< 1023; i++){
				a = rlGetNodeFromSlab();
			}
			expect(intEqual(rlSlabsUsed, 1), "we should have fully used one slab");
			expect(intEqual(rlSlabSize, 0), "and there should be nothing left");
			a = rlGetNodeFromSlab(); /* one more wafer thin mint! */
			expect(intEqual(rlSlabsUsed, 2), "We should now have two slabs");
			
		NEXT_CONTEXT("release a node")
			a->data = (void *) 0x12345678;
			prev_ptr = rlReleaseNode(a);
			expect(ptrEqual((void *) 0x12345678, prev_ptr), "should return the payload from the release");
			expect(ptrEqual((void *)rlFreeChainPtr, (void *)a), "it should have gone onto the free chain");
			expect(ptrEqual((void *)a->next, NULL), "and it should be the only thing on the chain");
			
		NEXT_CONTEXT("then request a new node, and get it back")
			b = rlGetNode();
			expect(ptrEqual((void*)a, (void*)b), "we get it back");
			expect(ptrEqual((void*)rlFreeChainPtr, NULL), "the free chain should now be empty");
			
		NEXT_CONTEXT("getting another node will pull from the slab")
			i = rlSlabSize; /* Remember how many items the slab has */
			a = rlGetNode();
			expect_not(ptrEqual((void *)a, NULL), "the newly allocated node should not be null");
			
		NEXT_CONTEXT("creating a list")
			a = rlCreateList();
			expect(ptrEqual((void *)a, (void *)a->next), "next should get us back to the beginning");
			expect(ptrEqual((void *)a, (void *)a->prev), "prev should get us back again too");
			expect(ptrEqual((void *)a->data, NULL), "this should be the start node, so it's data should be empty");
		
		NEXT_CONTEXT("adding something to list should work")
			rlAddDataToHead(a, (void *)0x0c);
			expect(ptrEqual((void *)a->next->next, (void *)a), "Going from head, forwards through one node and then the next should get back to head");
			expect(ptrEqual((void *)a->prev->prev, (void *)a), "Going from head, backwards through one node and then the next should get back to head");
			expect(ptrEqual(a->next->data, (void *)0x0c), "The payload should have been recorded");
			
		NEXT_CONTEXT("adding a few more should be fine too")
			rlAddDataToHead(a, (void *)0x0b);
			rlAddDataToHead(a, (void *)0x0a);
			expect(ptrEqual((void *)a->next->data, (void *)0x0a), "A should be first as it was last");
			expect(ptrEqual((void *)a->next->next->data, (void *)0x0b), "B should be next");
			expect(ptrEqual((void *)a->next->next->next->data, (void *)0x0c), "C should be last as it was first");
			expect(ptrEqual((void *)a->next->next->next->next->data, NULL), "Going all the way round should get us back to the start");
			
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

			
		END_CONTEXT
	END_CONTEXT
}