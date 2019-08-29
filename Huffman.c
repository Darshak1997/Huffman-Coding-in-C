// Rairakhia, Darshak Deepan
// ddr7657
// 2019-08-01
//--------#---------#---------#---------#--------#
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Huffman.h"


//--------#---------#---------#---------#--------#
static inline void exchangePtr( HuffmanNodePtr *a, HuffmanNodePtr *b ) \
  { /* PUT SOMETHING HERE */
  HuffmanNodePtr x;
  x = *a;
  *a = *b;
  *b = x;
  }

int top=0;
//--------#---------#---------#---------#--------#
static inline int LEFT(int i)   { /* PUT SOMETHING HERE */ return 2 * i + 1 ;}
static inline int RIGHT(int i)  { /* PUT SOMETHING HERE */ return 2 * i + 2; }
static inline int PARENT(int i) { /* PUT SOMETHING HERE */ return ((i + 1) / 2) - 1; }
//--------#---------#---------#---------#--------#
static void minHeapify( HuffmanHeapPtr h, int i )
{
  //***//**//**//**//***//
  // Put your MIN-HEAPIFY routine here.
  // h is a pointer to a HuffmanHeap structure, defined in
  //    Huffman.h.
  // i is the root of the subtree to minHeapify.
  //
  // There's an exchangePtr() routine above that will help.
  //***//**//**//**//***//
  int smallest = i;
  int ell = LEFT(i);
  int arr = RIGHT(i);
  if (ell < h->heapsize && h->A[ell]->frequency < h->A[smallest]->frequency)
  {
  smallest = ell;
  }
  if (arr < h->heapsize && h->A[arr]->frequency < h->A[smallest]->frequency)
  {
      smallest = arr;
  }
  if (smallest != i)
  {
        exchangePtr(&h->A[smallest], &h->A[i]);
        minHeapify(h, smallest);
  }
}

//--------#---------#---------#---------#--------#
void addElement( HuffmanHeapPtr h, HuffmanNodePtr newNodePtr )
{
  ++h->heapsize;
  int i = h->heapsize - 1;
  int count=0;
  while (i && (newNodePtr->frequency < h->A[(i - 1) / 2]->frequency))
  {
	h->A[i] = h->A[(i - 1) / 2];
        i = (i - 1) / 2;
  }
 
  h->A[i] = newNodePtr;
}
int temp=0;
//--------#---------#---------#---------#--------#
HuffmanNodePtr buildHuffmanCode( HuffmanHeapPtr h )
{
  //***//**//**//**//***//
  // Put your BUILD-HUFFMAN-CODE routine here.
  // h is a pointer to a HuffmanHeap structure, defined in
  //    Huffman.h.
  //
  // Return a pointer to the HuffmanNode that's the root of the
  //    code was built.
  //***//**//**//**//***//
  struct _HuffmanNode *top,*left,*right;
  while(h->heapsize > 1)
  {
  left = extractMin(h);
  right = extractMin(h);
  top = makeHuffmanNode(-1, left->frequency + right->frequency);
  top->left=left;
  top->right=right;
  addElement(h, top);
  }
  return extractMin(h);
 
}



int printArr(HuffmanNodePtr n, char arr[], int top)
{

if(!(n->left) && !(n->right))
{
	printf("%c : %3d : ", n->character, n->frequency);
	int i;
for (i = 0; i < top; ++i)
{
	printf("%c", arr[i]);
}

	printf("\n");
	temp=temp+(n->frequency)*top;
}

if (n->left) 
{
	arr[top] = '0';
	printArr(n->left, arr, top+1);
}
if (n->right) 
{
	arr[top] = '1';

	printArr(n->right, arr, top+1);
}

return(temp);
}

//--------#---------#---------#---------#--------#
int dumpHuffmanCode( HuffmanNodePtr n )
{
  //***//**//**//**//***//
  // Put your DUMP-HUFFMAN-CODE routine here.
  // n is a pointer to the root HuffmanNode struture that makes
  //    up this code.
  //
  // Each line that you print should be in this form:
  //
  //    <char> : <count> : <code>
  //
  // where:
  //    <char> is the character. When the character is printable,
  //        print it as 'c' (replace c with the particular
  //        character).  When the the character is not printable,
  //        print it as a three-digit decimal number, with leading
  //        zeroes.  [ FYI: In the "War and Peace" sample text,
  //        the only non-printable characters are carriage return
  //        (character 13, printed as 013) and line feed
  //        (character 10, printed as 010). ]
  //
  //    <count> is how many times the character occurs in the
  //        input file.
  //
  //    <code> is the computed Huffman code.
  //
  // For example, here are two of the output lines from the
  // "War and Peace" sample text.  One is a non-printable
  // character, the other is a printable character.
  //
  //    010  :  65656 : 111011
  //    'A'  :   6492 : 100110100
  //
  // Match this output format so your code can be checked!  Output
  // not in this format scores ZERO points!
  //
  // Return the total number of bits used by this code to
  //    represent the given text.  (This is just the sum of how
  //    often each character appears multiplied by how many bits
  //    used by the code of that character.)
  //***//**//**//**//***//

char *arr = (char *)malloc(sizeof(char));

int numofbits=printArr(n, arr, 0);

free(arr);

return(numofbits);
}


//--------#---------#---------#---------#--------#
HuffmanNodePtr extractMin( HuffmanHeapPtr h )
{
  //***//**//**//**//***//
  // Put your EXTRACT-MIN routine here.
  // h is a pointer to a HuffmanHeap structure, defined in
  //    Huffman.h.
  //
  // Return a pointer to the HuffmanNode that you extracted fro
  //    the heap.
  //***//**//**//**//***//
  HuffmanNodePtr temp = h->A[0];
  h->A[0] = h->A[h->heapsize - 1];
  --h->heapsize;
  minHeapify(h,0);
  return temp;  
}

//--------#---------#---------#---------#--------#
HuffmanHeapPtr makeHuffmanHeap( int size )
{
  //***//**//**//**//***//
  // Put your MAKE-HUFFMAN-HEAP routine here.
  // size is the maxium number of elements that will ever be in
  //    the heap.
  //
  // Return a pointer to the HuffmanHeap structure you allocate
  //    and initialize.  (calloc() will be useful.)
  //***//**//**//**//***//

  HuffmanHeapPtr h = (HuffmanHeapPtr)malloc(sizeof(struct _HuffmanHeap));
  h->heapsize = 0;
  h->size = size;
  h->A=(HuffmanNodePtr*)malloc((h->size)*sizeof(HuffmanNodePtr));
  return h;
}

//--------#---------#---------#---------#--------#
HuffmanNodePtr makeHuffmanNode( int character, int frequency )
{
  //***//**//**//**//***//
  // Put your MAKE-HUFFMAN-NODE routine here.
  // character is the ASCII code of the character to which this
  //    node corresponds or -1 if it's an interior node.
  // frequency is the number of times the character appears in
  //    the text or the sum of the frequencies of the subtrees
  //    when it's an interior node.
  //
  // Return a pointer to the Huffmanode structure you allocate and
  //    initialize.  (calloc() will be useful.)
  //***//**//**//**//***//
    HuffmanNodePtr m = (HuffmanNodePtr)malloc(sizeof(struct _HuffmanNode));
 
  m->character = character;
  m->frequency = frequency;
  m->left = NULL;
  m->right = NULL;
  return m;
}



//--------#---------#---------#---------#--------#
void dumpHuffmanHeap( HuffmanHeapPtr h )
{
  printf( "===== Huffman Heap =====\n" );
  printf( "size %d, heapsize %d\n", h->size, h->heapsize );
  for ( int i=0; i < h->heapsize; i++ ) {
    dumpHuffmanNode( h->A[i], 1 );
  }
}

//--------#---------#---------#---------#--------#
void dumpHuffmanNode( HuffmanNodePtr n, int indent )
{
  printf( "%*c", indent*2, ' ' );

  if ( n->character == -1 ) {
    printf( "[Interior] %d\n", n->frequency );
    dumpHuffmanNode( n->left, indent+1 );
    dumpHuffmanNode( n->right, indent+1 );
  } else {
    if ( isprint( n->character ) ) {
      printf( "'%c' %d\n", n->character, n->frequency );
    } else {
      printf( "%03d %d\n", n->character, n->frequency );
    }
  }
}

//--------#---------#---------#---------#--------#
