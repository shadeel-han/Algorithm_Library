/*
    Library: Heapsort
    Algorithm: basic max_heap operation
    Input: Unsorted integer sequence
    Output: Sorted integer sequence "max_heap"
    Operation:  max_insert  => insert an element into max_heap
                max_pop     => move the root element to the last element for sorting
                heapsort    => do Heapsort
*/

#include <cstdio>
#include <cstdlib>
#define USAGE 10000

using namespace std;
int max_heap[USAGE], heap_size=0;
/* Because min/max heap is a complete binary tree, use array instead of linked list for convenience */

void max_heapify( int index ){
    int next = index<<1, val, tmp;
    if( next <= heap_size ){
        if( next+1 <= heap_size )
            val = (max_heap[next]>max_heap[next+1])?(max_heap[next]):(max_heap[++next]);
        else
            val = max_heap[next];
        if( val > max_heap[index] ){
            tmp = max_heap[index];
            max_heap[index] = max_heap[next];
            max_heap[next] = tmp;
            max_heapify(next);
        }
    }
}

void build_max_heap(){
    for( int i=heap_size<<1; i>0; --i )
        max_heapify(i);
}

void max_insert( int in ){
    int now = ++heap_size, next = heap_size>>1;
    while( next && (max_heap[next] < in) ){
        max_heap[now] = max_heap[next];
        now = next;
        next >>= 1;
    }
    max_heap[now] = in;
}

void max_pop(){
    int tmp = max_heap[1];
    max_heap[1] = max_heap[heap_size];
    max_heap[heap_size--] = tmp;
    max_heapify(1);
}

void heapsort(){
    build_max_heap();	/* make sure array max_heap is stored as max heap */
    int i, tmp=heap_size;
    for( i=heap_size; i>1; --i )
        max_pop();
    heap_size = tmp;
}

int main(){
    
    int i;
    while(1){
        scanf("%d", &i);
        if( i==-1 ) break;
        max_insert(i);
        for( i=1; i<=heap_size; ++i )
            printf("%d ", max_heap[i]);
        putchar('\n');
    }
    
    /*while( heap_size ){
        max_pop();
        for( i=1; i<=heap_size; ++i )
            printf("%d ", max_heap[i]);
        putchar('\n');
    }*/
    
    heapsort();
    for( i=1; i<=heap_size; ++i )
        printf("%d ", max_heap[i]);
    putchar('\n');
    
    return 0;
}
