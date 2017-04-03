#include <stdio.h>
#include <stdlib.h>
#define t 2
#define MAX 2*t-1


struct node{
    int a[2*t-1] ;
    int n ;
    int leaf_flag ;
    struct node* child[2*t] ;

};


struct node * insert(struct node *root,int key) ;
struct node * insert_leaf(struct node * leaf ,int key ) ;
struct node * split_root(struct node *root ) ;
struct node* split_child(struct node *root ,int  i ) ;
void print_b_tree(struct node * root);
void del_key(struct node *root , int key ) ;


void search(struct node *root, int key );

int main(void)
{
    struct node *root =NULL ;
    int  key ,option , k = 0 ;
    int inp[10]={1,2,3,4,5,6,7,9,10,10}  ;

    do
    {
        printf("ENTER OPTION\n") ;
        printf("1->ENTER KEY       \n2->SEARCH  \n3-> DELETE \n4->PRINT \n5->EXIT\n") ;
        scanf("%d" ,&option) ;

        if(option ==1)
        {
            printf("ENTER YOUR KEY   ") ;
            //scanf("%d",&key) ;
            k = 0 ;
            while(k<5)
                root = insert(root,inp[k++]) ;
            print_b_tree(root);
            del_key(root,2);
            printf("============================================================================\n");
            print_b_tree(root);
            printf("============================================================================\n");

        }else if(option ==2)
        {
            printf("ENTER YOUR KEY to search for   ") ;
            scanf("%d",&key) ;
            printf("============================================================================\n");
            search(root , key);
            printf("============================================================================\n");

        }else if(option == 3 )
        {
            printf("Enter the key to be deleted\n") ;
            scanf("%d" , &key ) ;
            del_key(root , key);
        }else if(option == 4)
        {
            print_b_tree(root );
        }else
        {

            return 0 ;

        }
    }while(option!=0) ;

    return 0 ;

}

struct node * insert(struct node *root,int key)
{
    struct node * p ;

    int i = 0  ;

    if(root==NULL)
    {//============================================================================
        /*
         * root is null and we are allocating  a memory space and return it
         * after inserting the key
         */

        p = (struct node *)malloc(sizeof(*p)) ;

        if(p!=NULL)
        {
            p->a[0] = key ;
            p->leaf_flag = 1 ;
            p->n = 1 ;

        }else
        {
            exit(111) ;
        }

        return p ;
    //============================================================================

    }
    else if(root->n == MAX)
    {
        /*
         * if root is at max degree then spliting it
         * by split_root() function
         */

        root = split_root(root ) ;
        root = insert(root , key ) ;

        return root ;

    }else
    {
        //===========================================================================
        while(key > root->a[i] && i < root->n)
        {
             i++ ;
        }

        if(root->leaf_flag == 1 )
        {
            insert_leaf(root , key) ;
            return root ;

        }else
        {//checking children
            if(root->child[i]->n == MAX )
            {

                split_child(root , i) ;
                if(key <= root->a[i] )
                {
                     insert(root->child[i ],key) ;
                }else{

                    insert(root->child[i+1] , key );
                }


            }else if(root->child[i]->leaf_flag == 0 )
            {
                //check about returning root
                insert(root->child[i] , key ) ;
            }
            else{
                //inserting to leaf only
                 insert_leaf(root->child[i] , key ) ;
            }



        }

        //===========================================================================
    }

    return root ;

}



struct node * insert_leaf(struct node *root , int key )
{
    int i , j  ;

    //================================================
               i=0 ;                  //positioning the key in sorted order
               while(key > root->a[i] && i < root->n)
                   i++ ;

               j=root->n ;
               while(j > i)
               {
                   root->a[j] = root->a[j-1] ;
                   j-- ;
               }
               root->a[i] = key ;
               root->n++ ;
    //=================================================

    return root ;

}


struct node * split_root(struct node *root ){


    struct node * p ;
    struct node *q ;
    int i   ;
    //========================================================
    p = (struct node *)malloc(sizeof(*p)) ;
    p->a[0] = root->a[t-1] ;
    p->n =1 ;
    p->leaf_flag = 0 ;
    p->child[0] = root ;
    //--------------------
    q = (struct node *)malloc(sizeof(*p));
    i = 0 ;                 //of which root is newly allocated one
    root->a[t-1] = 0 ;
    while(i < t-1)
    {
        q->a[i] = root->a[i+t] ;
        q->child[i] = root->child[i+t] ;

        root->child[i+t] = NULL ;   //deleting the link
        root->a[i+t] = 0;
        i++ ;
    }
    q->child[i] = root->child[i+t] ;

    q->leaf_flag = root->leaf_flag ;

    root->child[i+t] =NULL ;


//    if(root->child[i]==NULL)
//    {
//        q->leaf_flag =1 ;

//    }else
//    {
//        q->leaf_flag = 0 ;
//    }
    p->child[1] = q ;
    q->n = t-1 ;
    root->n = t-1 ;

    //========================================================



    return p ;



}


struct node* split_child(struct node *root ,int  i )
{
    struct node * p ;

    int    j ;
    //      inserting 3

           //              root                                                      root
           //               ||                                                        ||
           //               \/                                                        \/
           //             | 2-5 |                   ==>>                           | 2-3-5 |
           //          //    |    \\                                            //    /  \  \\
           //         \/    \/     \/                                          \/    \/  \/  \/
           //        |1| |2-3-4|  |5|                                          |1|   |2| |4| |5|

           /*                                                                        /\
           //                                                                        || >> calling again the insert function at this node as root
           */

           //shifting is done at root node
           j = root->n  ;
           while(j >  i  )
           {
               root->a[j] = root->a[j-1] ;
               //root->a[j-1] = 0 ;
               root->child[j+1] = root->child[j] ;
               j-- ;
           }

           //root->child[j+1] = root->child[j] ;
           root->a[j] = 0 ;
           // a key is pushed to root node
           root->a[i] = root->child[i]->a[t-1] ;
           root->n++ ;

           root->child[i]->n = t-1 ;
           root->child[i]->a[t-1]  = 0 ;
           //new node is created
           p = (struct node *)malloc(sizeof(*p)) ;
           j = 0 ;                 //of which root is newly allocated one
           while(j < t-1)
           {
               p->a[j] = root->child[i]->a[j+t] ;
               p->child[j] = root->child[i]->child[j+t] ;
               root->child[i]->child[j+t]  = 0 ;
               j++ ;
           }
           p->child[j] = root->child[i]->child[j+t] ;
           p->n = t-1 ;
           p->leaf_flag = root->child[i]->leaf_flag ;

           //assigning the new child to this new upwarded_key
           root->child[i+1] = p ;




           /*
           if(key > root->a[i])
           {
               insert(root->child[i+1],key) ;
           }else
           {
               insert(root->child[i],key) ;
           }

       */

    return p ;

}
void print_b_tree(struct node * root){

    static int space = 0;
    int i ;
    if(root->leaf_flag == 1)
    {


        for(i=0 ; i < space ;i++)
        {
            printf("                ") ;
        }
        for(i=0 ; i < root->n ;i++)
        {
            printf("%d(%d) " , root->a[i] , root->n) ;
        }
        printf("\n") ;

    }else
    {
        printf("-----------------------------------------------------------------------------------\n");
        space++ ;
        for(i = 0 ;i <= root->n/2 ; i++ )
        {
            print_b_tree(root->child[i]);
        }

        space= space -1 ;
        for(i=0 ; i < space ;i++)
        {
            printf("                ") ;
        }
        for(i=0 ; i < root->n ;i++)
        {
            printf("%d(%d) " , root->a[i] , root->n) ;
        }
        printf("\n")  ;
        space =space +1 ;

        for(i = root->n/2 +1;i <= root->n ; i++ )
        {
            print_b_tree(root->child[i]);
        }
        space-- ;
        printf("----------------------------------------------------------------------------------- \n");
    }

    return ;
}

void search(struct node *root ,int key )
{

    int i , j  ;
    i = 0 ;
    if(root==NULL)
    {

        printf("key not found found\n") ;
        return ;
    }

    while(root->a[i]< key && i < root->n)
        i++ ;
    if(root->a[i] ==key)
    {

        for(j = 0 ; j <root->n ; j++)
        {

            printf("%d " ,root->a[j] ) ;
        }
        printf("\n") ;

        printf("key found\n") ;
    }
    else
    {

        for(j = 0 ; j <root->n ; j++)

        {
            printf("%d " ,root->a[j] ) ;
        }
        printf("    \n") ;
        search(root->child[i] , key) ;

    }

   return ;
}



void del_key(struct node *root , int key )
{
    int i = 0 , k , j ,tmp_key;
    while(root->a[i]<key && i<root->n)
    {
        i++ ;
    }

    if(root->a[i]==key)   //key found
    {

        if( root->leaf_flag == 1)       //key found at leaf
        {                               //claiming that this condition will not come
            j= i;
            while(j < root->n )
            {
                root->a[j] = root->a[j+1] ;
                j++ ;
            }
            root->n-- ;

        }else{
            if(root->child[i]->n > t-1)
            {

                //findmax in child and replace it with a[i]
                tmp_key = root->child[i]->a[root->child[i]->n-1] ;
                root->child[i]->a[root->child[i]->n-1] = root->a[i] ;
                root->a[i] = tmp_key ;
                del_key(root->child[i] , key);

            }else if(root->child[i+1]->n > t-1)
            {
                //find min in child and again same
                tmp_key = root->child[i+1]->a[0] ;
                root->child[i+1]->a[0] = root->a[i] ;
                root->a[i] = tmp_key ;
                del_key(root->child[i+1] , key);
            }else
            {
                //========================================================================== merge
                    j = root->child[i]->n ;
                    k = 0 ;
                    while(k < root->child[i+1]->n )
                    {
                        root->child[i]->a[j+1] = root->child[i+1]->a[k] ;
                        root->child[i]->child[j+1] = root->child[i+1]->child[k] ;

                        j++ ;
                        k++ ;

                    }
                    root->child[i]->child[j+1] = root->child[i+1]->child[k] ;
                    root->child[i]->a[i] = key ;

                    //==========================================================================



                    j = i+1 ;
                    while(j < root->n) //shifting in parent node
                    {
                        root->a[j-1] = root->a[j] ;
                        root->child[j] =root->child[j+1] ;
                        j++ ;
                    }
                    del_key(root->child[i] , key );



            }
        }


    }else   //key not found at root
    {

            if(root->child[i]->n > t-1)
            {
                root->a[i] = root->child[i]->a[root->child[i]->n-1] ;
                root->child[i]->n-- ;
                root->child[i]->a[i] ;
                del_key(root->child[i] , key);

            }else if(root->child[i+1]->n > t-1)
            {
                root->a[i+1] = root->child[i+1]->a[root->child[i]->n-1] ;
                root->child[i+1]->n-- ;
                root->child[i]->a[i+1] ;
                del_key(root->child[i+1] ,key );


            }else
            {
                //delete and merge
                if(root->child[i]->n == t-1 && root->child[i+1]->n == t-1 )
                {
                   //========================================================================== merge
                    j = root->child[i]->n ;
                    k = 0 ;
                    while(k < root->child[i+1]->n )
                    {
                        root->child[i]->a[j+1] = root->child[i+1]->a[k] ;
                        root->child[i]->child[j+1] = root->child[i+1]->child[k] ;

                        j++ ;
                        k++ ;

                    }
                    root->child[i]->child[j+1] = root->child[i+1]->child[k] ;
                    root->child[i]->a[i] = key ;

                    //==========================================================================

                    j = i+1 ;
                    while(j < root->n) //shifting in parent node
                    {
                        root->a[j-1] = root->a[j] ;
                        root->child[j] =root->child[j+1] ;
                        j++ ;
                    }
                    del_key(root->child[i] , key );
                }


            }

    }
    return ;
}
