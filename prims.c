
/*
Implement Breadth First Search of an undirected graph-> After taking number of vertices and details of the edges as input, represent the graph using an adjacency list representation-> Ask for the source vertex and print the BFS visit order of the vertices and the distances of each vertex from the source node->
*/


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//Node for adding linked list
struct node{

    int v_track ;
    int path_length ;
    int prede ;
    struct adjacent_node *next  ;

    //weight
};

struct adjacent_node {
    int ver ;
    int weight ;
    struct adjacent_node *next ;
};

struct heap_node {
    int ver ;
    int weight ;
}heap[10];


struct node a[51] ;


    int heap_size = 0 ;

void buildheap( );
void prims(int n , int source);
void minheapify(int index) ;


int extractmin(  ) ;
void decreasekey(int index , int key ) ;
void prims(int n , int source);

void main()
{

    struct adjacent_node *p ,*temp=NULL ;
    int i ,j,adjacent , n ,weight ,source;

    //entering the no-> of vertices
    printf("ENTER THE NO OF VERTICES     \n INPUT >\n") ;
    scanf("%d",&n);

    for(i=1 ;i<n+1;i++)
    {
        printf("Enter the no of adjacent vertices to %dth  vertex\n INPUT >\n",i);
        scanf("%d",&j);
        if(j==0)
            continue ;
        else
            printf("\nENTER ADJACENT VERTICES TO  %d and its weight w.r.t. this vertex \n INPUT >\n",i);


            adjacent = 0;
            while((adjacent <n+1) && j >0)
            {

                j-- ;

                scanf("%d %d",&adjacent ,&weight) ;

                p =malloc(sizeof(struct adjacent_node)) ;

                temp = a[i].next ;
                a[i].next = p ;
                p->next = temp ;

                p->ver = adjacent ;
                p->weight = weight ;

                p =malloc(sizeof(struct adjacent_node)) ;

                temp = a[adjacent].next ;
                a[adjacent].next = p ;
                p->next = temp ;

                p->ver = i ;
                p->weight = weight ;



            }



    }

    //checking whether graph is stored as expected
    printf("===============GRAPH IN ADJACENCY FORMAT===============\n");
    for (i = 1 ; i< n+1 ;i++ )
    {
        printf("the vertex %d   >>>>>>  ",i );
        temp=a[i].next ;
        while(temp!=NULL)
        {
            printf("%d (%d)     ",temp->ver, temp->weight) ;
            temp=temp->next ;
        }
        printf("\n");
    }
    printf("=======================================================\n");

    source =1 ;
    prims(n,source);


    return ;
}
//this function takes the graph in the adjancy list format and source vertex and
//find the minimum path from this vertex to all the other vertex
void prims(int n , int source)
{
    int i ,min ,flag=1;

    struct adjacent_node *tmp ;


    for(i=1 ;i<n+1;i++)
    {
        a[i].path_length=INT_MAX;
        a[i].prede = -1 ;
        //prede[i].ver=-1 ;
        a[i].v_track = i ;


        heap[i].ver=i;
        heap[i].weight=INT_MAX ;
    }

    a[source].path_length = INT_MIN ;

    i=1 ;


    heap_size = n ;
    //buildheap(  heap_size);

    a[source].prede = -1 ;
    //prede[source].ver=-1 ;
    //putting the source vertex  out of the heap
    decreasekey( a[source].v_track,INT_MIN ) ;

    while(heap_size!=0  )
    {

        min=extractmin(  ) ;
        if(heap[a[min].v_track].weight==INT_MAX)
        {
            flag=0 ;
            break ;
        }



        tmp=a[min].next ;
        while(tmp!=NULL)
        {
            if(a[tmp->ver].v_track > heap_size )
            {
                tmp=tmp->next ;
                continue ;
            }

            if(a[tmp->ver].path_length > tmp->weight)
            {
                a[tmp->ver].path_length = tmp->weight ;
                a[tmp->ver].prede = min ;
                //a[tmp->ver].weight =tmp->weight ;
                decreasekey(  a[tmp->ver].v_track ,tmp->weight );

            }

            tmp = tmp->next ;

        }

    }
        //printing the shortest path from the source vertex to every other vertex
        printf("====================== Shortest path length ===================\n");
        printf("    VERTEX                PATH LENGTH    \n");
        for(i=1 ;i<=n;i++)
        {

            printf("      %d                       %d                  \n" , i , a[i].path_length ) ;
        }
        printf( "===============================================================\n" ) ;

        if( flag==0 )
        {
            printf( "!!!!!!!!!!!!!!!!!!!!!!  NO MST POSSIBLE\n" ) ;
            return ;
        }
        printf("========================MST IS THE FOLLOWING===================\n");
        printf("   VERTEX1             VERTEX2             EDGE WEIGHT\n");
        for(i=1;i<=n;i++)
        {
            if(a[i].prede == -1 )
                continue ;
            printf("     %d                     %d                      %d\n" , i , a[i].prede , heap[a[i].v_track].weight );   //

        }

        printf("===============================================================\n");

        return ;

}

//this fuction takes an array and make it heap
void buildheap( )
{
    int i =1 ;
    //since the heap property  is already true for the n/2 vetices having no child
    for(i=heap_size/2;i> 0;i--)
    {

        minheapify(  i) ;
    }

    return ;
}

//it decrease key value at the index and again maintains heap properties
void decreasekey( int index ,int key )
{
        int t_key  ;
        struct heap_node tmp ;
        heap[index].weight=key ;
        t_key =index ;
        //since in this  block if the value is decreased then
        //it will defy with the parent
        while(t_key>1 && heap[t_key].weight < heap[t_key/2].weight)
        {
                tmp = heap[t_key] ;
                a[heap[t_key].ver].v_track = t_key/2 ;
                a[heap[ t_key/2 ].ver].v_track = t_key ;
                //v_track[heap[t_key/2].ver]=t_key ;

                heap[t_key] =heap[t_key/2];
                heap[t_key/2] = tmp  ;

                t_key =t_key/2 ;


        }

    return ;
}



//this function takes heap and pop the minimum element
//means deleting the the min element and maintaining  the heap property
int extractmin(  )
{
    //int t_key  ;
    struct heap_node tmp ;
    if(heap_size==0)
            return INT_MIN ;
    tmp =heap[1] ;

    //returning the top element in the heap and deleting it from the heap
    heap[1]=heap[heap_size] ;
    heap[heap_size]=tmp ;

    a[heap[heap_size].ver].v_track = heap_size ;//[heap[heap_size].ver]= heap_size;
    a[heap[1].ver].v_track = 1 ;
    //v_track[heap[1].ver]= 1;

    heap_size-- ;
    minheapify(1) ;



    return tmp.ver  ;
}

//this function takes the two child having heap properties and
// makes it heap with the given index having  given child
void minheapify(int index)
{
    int l_child ,r_child ;
    int s ;
    struct heap_node tmp  ;
    //initialising the right child and left child of the given parent
    l_child = index *2 ;
    r_child = index *2 +1 ;
        //since n/2 node does not have a single child so it already have the heap property
    if(index>(heap_size/2))
        return ;


    //assigning the s for which key value is mininmum of(right child ,left child)
    if(r_child <= heap_size  && heap[l_child].weight > heap[r_child].weight )
    {
        s = r_child ;

    }else
        s=l_child ;




        //swapping key value if it s is index of any of right child or left child
        //and then repeating the process (calling this function ) at its child
    if (s <= heap_size && heap[index]. weight > heap[s].weight)
    {
            tmp=heap[index] ;

            heap[index] =heap[s] ;

            heap[s] =tmp ;
            //v_track[s]= k  ;
            a[heap[index].ver].v_track = index ;
            a[heap[s].ver].v_track =  s ;

            minheapify(  s ) ;


    }
    return ;
}


/*

6 
2 
2 5 
3 3 
3 
3 4 
4 3 
5 8 
1 
6 6 
1 
5 7 
1 
 6 5 
 0 
 1 
 
*/



