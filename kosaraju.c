/*
 * Implement Kosaraju's Algorithm for computing strongly connected components in a directed graph.
 *
 * Input format:
 *
 * First line : n (number of vertices of the graph)
 *
 * Next line : neighbours of v1 separated by a space and ended by -1
 *
 * Next line : neighbours of v2 separated by a space and ended by -1 and so on..
 *
 * Output : List of vertices in each strongly connected component of G with their respective component numbers.
 *
 */
#include<stdio.h>
#include<stdlib.h>

//Node for adding linked list
struct node{

    int visited ;
    struct adjacent_node *next  ;

    //weight
};

struct adjacent_node {
    int ver ;
    struct adjacent_node *next ;
};

struct node a[51]  , adj_reverse[51] ;
int time_ver[51] , counter ;

void directedGraphInput(int n) ;
void reversegragh(struct node *a , int n) ;
void print_adjacency_list(struct  node a[], int n) ;
void kosaraju( struct node adj_reverse[]  ,int n ) ;
void subgraph(struct node *a , int n  ) ;
int main()
{

    struct adjacent_node  *temp=NULL ;
    int i ,  n   ;

    printf("ENTER THE NO OF VERTICES     \n INPUT >\n") ;
    scanf("%d",&n);

    //making the directed graph
    directedGraphInput(n) ;

    //printing adjacency list
    print_adjacency_list(a, n);

    //this function puts the vertex at top(lower index)in array time_ver which is visited at last
    subgraph( a ,n);

    printf("\n") ;

    //this reverses all the direction in the graph
    reversegragh(a ,n) ;

    print_adjacency_list(adj_reverse ,n);

    //finds all strongly connected component
    kosaraju(adj_reverse , n );

    return 0;
}


//adjacency list needed to be declared globally
//node contain only vertex and array contains visited flag
void directedGraphInput(int n )
{
    struct adjacent_node *p ,*temp=NULL ;
    int i ,j,adjacent   , k;

    //entering the no-> of vertices

    for(i=1 ;i<n+1;i++)
    {
        printf("Enter the no of adjacent vertices to %dth  vertex\n INPUT >\n",i);
        scanf("%d",&j);
        if(j==0)
            continue ;
        else
            printf("\nENTER ADJACENT VERTICES TO  %d   \n INPUT >",i);


            for(k= 0 ; k< j ;k++ )
            {
                scanf("%d", &adjacent );
                if((adjacent > n) )
                {
                    printf("\nYou have entered a wrong vertex\n");
                    k-- ;
                    continue ;
                }

                p =malloc(sizeof(struct adjacent_node)) ;
                if(p==NULL)
                {
                    return ;
                }
                temp = a[i].next ;
                a[i].next = p ;
                a[i].visited = 0 ;
                p->next = temp ;

                p->ver = adjacent ;
            }

            adj_reverse[i].visited = 0 ;


    }
    return ;
}



//requires a[] ,adj_reverse[] to be globally declared and no. of vertex to be given
void reversegragh(struct node *a , int n )

{
    int i , j , k ;
    struct adjacent_node *p ,*tmpa1 ,*tmp2 ;

    for(i=1 ; i<=n ;i++)
    {

       tmpa1 = a[i].next ;
       while(tmpa1!=NULL)
       {
           p = (struct adjacent_node *)malloc(sizeof(*p)) ;
           if(p==NULL)
               return ;

           tmp2 = adj_reverse[tmpa1->ver].next ;
           adj_reverse[tmpa1->ver].next = p ;
           p->next = tmp2 ;
           p->ver = i ;
           tmpa1= tmpa1->next ;
       }
        adj_reverse[i].visited = 0 ;
    }
    return ;

}
//it takes the adjacency list and no. ov vertices and prints it on the screen
void print_adjacency_list(struct node a[], int n)
{
    int i ;
    struct adjacent_node *temp ;
    //checking whether graph is stored as expected
    printf("===============GRAPH IN ADJACENCY FORMAT===============\n");
    for (i = 1 ; i< n+1 ;i++ )
    {
        printf("the vertex %d   >>>>>>  ",i );
        temp=a[i].next ;
        while(temp!=NULL)
        {
            printf("%d       ",temp->ver ) ;
            temp=temp->next ;
        }
        printf("\n");
    }
    printf("=======================================================\n");


    return ;

}

//this function visits all the component connected to vertex
void dfs(struct node *a , int vertex , int n)
{

    struct adjacent_node *tmp ;
    tmp = a[vertex].next ;
    while(tmp !=NULL)
    {
        if(a[tmp->ver].visited==0)
        {

            a[tmp->ver].visited = 1 ;
            dfs(a ,tmp->ver ,n) ;
        }

        tmp = tmp->next ;

    }
    printf("%d  ",vertex) ;
    time_ver[counter--] = vertex ;
    return ;
}


// this visits all the vertex by calling dfs()
void subgraph(struct node *a , int n  )
{
    counter = n ;
    int i= 1 , j ;
    for(i = 1 ; i <=n ; i++ )
    {
        if(a[i].visited == 0)
        {
            a[i].visited = 1 ;
            dfs(a ,i ,n) ;
        }
    }

    return ;

}


void kosaraju( struct node adj_reverse[]  ,int n )
{

    int i= 1 , j,component =1  ;
    if(adj_reverse ==NULL)
    {
        printf("NO component\n") ;
    }

    for(i = 1 ; i <=n ; i++ )
    {
        if(adj_reverse[time_ver[i]].visited == 0)
        {
            printf("%d Strongly Connected Component is     ",component++) ;

            adj_reverse[time_ver[i]].visited = 1 ;
            //subgraph(adj_reverse , n); ;
            dfs(adj_reverse , time_ver[i] , n ) ;
            printf("\n\n") ;
        }
    }

    return ;

}


/*
        input .......
        
12

1
2
1
3
1
1

1
5
1
6
1
7
1
4

1
9
1
10
1
8

1
12
1
11

*/
