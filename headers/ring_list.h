# ringlist.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech

typedef struct rlNode
{
    struct rlNode *prev;
    struct rlNode *next;
    void *data;
} rlNode;

/* 

	Before any use of ringlist, the rlInit function should be called to initialise the internal pointers used to manage list fragments

*/
void rlInit();

/* 

    To receive a new list, simply call rlCreateList, this will return a pointer to an rlNode object that describes the head of the list

*/
rlNode *rlCreateList();

/*

    Adding items to the head and the tail of the list is trivial...

    note, I realise that calls to tail as slightly slower than calls to head, as they are implemented as a secondary call to head.
    If this proves to be a problem, it is trivial to reimplement with its own implementation.

*/
rlNode *rlAddDataToTail(rlNode *list, void *data);
rlNode *rlAddDataToHead(rlNode *list, void *data);

/*

    returning a lists rlNodes to the 'pool' is simple, just call ... with any rlNode of the list.

*/
void rlReclaimList(rlNode *list);
/* 

    Note, it is not the responsibility of ringlist to allocate or free anything stored as data in a ringlist.
	there is NO PROVISION for actually FREEING memory allocated to slabs however, reclaimed rlNodes will be reused
	before new slabs are allocated. Should memory be exhausted, the ultimate slab allocation will fail and the
	whole program will exit.

*/