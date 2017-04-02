

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//Node for adding linked list
struct node{

    int v_track ;
    int path_length ;
    int prede ;
    struct adjacent_node *next  ;

};

struct adjacent_node {
    int ver ;
    int weight ;
    struct adjacent_node *next ;
};


#define INFINITY 1000

struct dis_node{
    int path ;
    int distance ;
};

struct dis_node mat[6][6] ;
struct node a[7] ;

void show_shortest_path(int n ) ;
void s_distance(int n ) ;

void main()
{

    struct adjacent_node *p ,*temp=NULL ;
    int i ,j,adjacent , n ,weight ;

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

    s_distance(  n );

    return ;
}

//shortest path implementation by Floyd Warshall
void s_distance(int n )
{
    int i , j , k ;
    struct adjacent_node *tmp ;


    for(i = 1 ;i <=n ; i++)
    {
        for(j = 1 ; j <=n ; j++   )
        {
            mat[i][j].distance = INFINITY ;
            mat[i][j].path =   n+1 ;
        }

    }


    for(i=1 ; i<=n ; i++ )
    {

        tmp = a[i].next;
        while(tmp != NULL ){

            mat[i][tmp->ver].distance = tmp->weight ;
            mat[i][tmp->ver ].path =  i ;
            tmp = tmp->next ;
        }
    }

    for(k = 1 ; k <=n ; k++)
    {
        for(i = 1 ;i <=n ; i++)
        {
                for(j = 1 ;j <=n ; j++)
            {
                if( mat[i][j].distance > mat[i][k].distance + mat[k][j].distance )
                {
                    mat[i][j].distance = mat[i][k].distance + mat[k][j].distance ;
                    mat[i][j].path = mat[k][j].path ;
                }

            }


        }

    }

    show_shortest_path( n ) ;

    return ;

}


void show_shortest_path(int n )
{

    int i , j , v ;

    for(i = 1 ;i <=n ; i++)
    {
        for(j = i+1 ;j <=n ; j++)
        {
            printf("\nPATH B/W %d     and     %d \n" ,i , j) ;
            if(mat[i][j].path == n+1 )
            {
                printf("NO PATH EXISTS \n ") ;
            }else
            {
                v = j ;

                do {

                    printf("%d  ", v ) ;

                    v = mat[i][v].path ;

                }while ( v!=i );
                printf("%d\npath length = %d\n",i , mat[i][j].distance);
            }
        }

    }

    return  ;

}

