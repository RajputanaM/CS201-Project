#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n;

struct node{
    int code;
    char ch[20];
    struct node *next;
};

struct list{
    int d;
    int vertex;
    struct list *pi;
    struct list *next;
};

struct graph{
    struct list *adj;
};

struct graph *G=NULL;

struct node *start=NULL;

struct distance{
    char ch1[20];
    char ch2[20];
    int d;
    struct distance *next;
};

struct distance *head=NULL;

struct list *queue_head=NULL;

struct list *source=NULL;

void create_queue(){
    for(int i=0; i<n; i++){
        struct list *temp = (struct list*)malloc(sizeof(struct list));
        temp->vertex=G->adj[i].vertex;
        temp->d=20000;
        temp->pi=NULL;
        temp->next=NULL;
        if(queue_head==NULL)
        queue_head=temp;
        else{
            struct list *t=queue_head;
            while(t->next!=NULL)
            t=t->next;
            t->next=temp;
        }
    }
}

int unique_name(char *ch){
    int temp;
    struct node *t=start;
    if(start==NULL)
    return 0;
    else{
        while(t!=NULL){
            temp=strcmp(t->ch,ch);
            if(temp==0)
            return 1;
            t=t->next;
        }
    }
    return 0;
}

int unique_code(int code){
    struct node *t=start;
    if(start==NULL)
    return 0;
    else{
        while(t!=NULL){
            if(t->code==code)
            return 1;
            t=t->next;
        }
    }
    return 0;
}

void insert(){
    struct node *t=(struct node*)malloc(sizeof(struct node));
    printf("Enter place name = ");
    scanf("%s",t->ch);
     while(unique_name(t->ch)){
        printf("This place name is already used.\n");
        printf("Please enter different name = ");
        scanf("%s",t->ch);
    }
    printf("Enter a unique code for this place = ");
    scanf("%d",&t->code);
     
    while(unique_code(t->code)){
         printf("This code is already used.\n");
         printf("Please enter a unique code = ");
         scanf("%d",&t->code);
    }
    t->next=NULL;
    if(start==NULL)
    start=t;
    else{
        struct node *temp=start;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=t;
    }
}


int find_code(char *ch){
    struct node *temp=start;
    while(temp!=NULL){
        if(!strcmp(ch,temp->ch)){
            return(temp->code);
        }
        temp=temp->next;
    }
    return(-1);
}

int find_weight(struct list *ptr1, struct list *ptr2){
    struct distance *temp=head;
     
    while(temp!=NULL){
        if((ptr1->vertex==find_code(temp->ch1)&&ptr2->vertex==find_code(temp->ch2))||(ptr2->vertex==find_code(temp->ch1)&&ptr1->vertex==find_code(temp->ch2)))
        return(temp->d);
        temp=temp->next;
    }
}


struct list* find_address(int x){
    for(int i=0; i<n; i++){
        if(G->adj[i].vertex==x)
        return(G->adj+i);
    }
}

void insertNode_in_source(struct list *p){
    if(source==NULL)
    source=p;
    else{
        struct list *t=source;
        while(t->next!=NULL)
        t=t->next;
        t->next=p;
    }
}


void update_queue() {  
        struct list *t = queue_head;  
        int temp,v;  
          struct list *s;
        if(queue_head == NULL) {  
            return;  
        }  
        else {
            while(t!= NULL) {  
                struct list *p=t->next;
                  
                while(p!= NULL) {  
                    if(t->d >p->d) {  
                        temp = t->d;  
                        t->d = p->d;  
                        p->d = temp;  
                        v=t->vertex;
                        t->vertex=p->vertex;
                        p->vertex=v;
                        s=t->pi;
                        t->pi=p->pi;
                        p->pi=s;
                    }  
                    p = p->next;  
                }  
                t = t->next;  
            }   
        }  
    }  

void dijkstra(){
    char s[20];
    printf("Enter starting point of your journey = ");
    scanf("%s",s);
    int c = find_code(s);
     
    struct list *t=queue_head;
    while(t!=NULL){
        if(t->vertex==c)
        break;
        t=t->next;
    }
     
    t->d=0;
     
    update_queue();
     
    while(queue_head!=NULL){
          
    struct list *delete=queue_head;
    queue_head=delete->next;
    delete->next=NULL;
    insertNode_in_source(delete);
    
    struct list *r=find_address(delete->vertex);
    r=r->next;
    
    while(r!=NULL){
         
        struct list *p=queue_head;
        while(p!=NULL){
            if(p->vertex==r->vertex)
            break;
            p=p->next;
        }
         if(p!=NULL){
         if(delete->d+find_weight(delete,p)<p->d){
             p->d=delete->d+find_weight(delete,p);
             p->pi=delete;
         }
         }
            r=r->next;
     }
    update_queue();
      
    }
    
}

void create_map(){
    int x=0;
    int y=0;
    G=(struct graph*)malloc(sizeof(struct graph));
    G->adj=(struct list*)malloc(n*sizeof(struct list));
    struct node *t=start;
    for(int i=0; i<n; i++){
        G->adj[i].vertex=t->code;
        G->adj[i].next=NULL;
        G->adj[i].pi=NULL;
        t=t->next;
    }
     
    char s1[20],s2[20];
    int dist;
    printf("Once you have entered all the path then enter 'Stop', 'Stop', and '-1' to stop.\n");
    while(1){
        printf("Enter starting point of path = ");
        scanf("%s",s1);
        if(strcmp(s1,"Stop")){
            x=find_code(s1);
        while(x==-1){
            if(!strcmp(s1,"Stop"))
            break;
            printf("No such place exist.\n");
            printf("Please enter another starting point of path = ");
            scanf("%s",s1);
            x=find_code(s1);
         }
        }
        printf("Enter destination point = ");
        scanf("%s",s2);
        if(strcmp("Stop",s2)){
            y=find_code(s2);
        while(y==-1){
            if(!strcmp(s2,"Stop"))
            break;
            printf("No such place exist.\n");
            printf("Please enter another destination point = ");
            scanf("%s",s2);
            y=find_code(s2);
         }
        }
        
        printf("Enter distance between %s and %s in Km = ",s1,s2);
        scanf("%d",&dist);
        if(dist==-1&&!strcmp("Stop",s1)&&!strcmp("Stop",s2))
        break;
        struct list *p1=find_address(x);
        struct list *p2=(struct list*)malloc(sizeof(struct list));
        p2->vertex=y;
        p2->next=NULL;
        while(p1->next!=NULL){
            p1=p1->next;
        }
        p1->next=p2;
        struct list *r1=find_address(y);
        struct list *r2=(struct list*)malloc(sizeof(struct list));
        r2->vertex=x;
        r2->next=NULL;
        while(r1->next!=NULL){
            r1=r1->next;
        }
        r1->next=r2;
        
        struct distance *a=(struct distance*)malloc(sizeof(struct distance));
        strcpy(a->ch1,s1);
        strcpy(a->ch2,s2);
        a->d=dist;
        
        if(head==NULL)
        head=a;
        else{
            struct distance *b=head;
            while(b->next!=NULL)
            b=b->next;
            b->next=a;
        }
    }
} 
       
     void print(){
    char ch[20],c[20];
    struct list *temp=source;
    struct node *t=start;
    while(t!=NULL){
        if(t->code==source->vertex){
            strcpy(ch,t->ch);
            break;
        }
        t=t->next;
    }
      
    while(temp!=NULL){
        struct node *p=start;
    while(p!=NULL){
        if(p->code==temp->vertex){
            strcpy(c,p->ch);
            break;
        }
        p=p->next;
    }
        printf("Minimum distance between %s and %s is = %d\n",ch,c,temp->d);;
        temp=temp->next;
    }
    
}
void display(){
    char s[20],c[20];
    printf("Enter place name where you want to go = ");
    scanf("%s",s);
    struct list *temp=source;
    int x=find_code(s);
    while(temp!=NULL){
        if(temp->vertex==x){
            break;
        }
        temp=temp->next;
    }
     while(temp!=source){
          struct node *p=start;
    while(p!=NULL){
        if(p->code==temp->vertex){
            strcpy(c,p->ch);
            break;
           }
            p=p->next;
 }
         printf("%s <- ",c);
         
         temp=temp->pi;
      }
      struct node *q=start;
    while(q!=NULL){
        if(q->code==temp->vertex){
            strcpy(c,q->ch);
            break;
           }
        q=q->next;
         }
      printf("%s",c);
}


int main(){
    printf("Enter number of places you want to add in Map = ");
    scanf("%d",&n);
     for(int i=0; i<n; i++){
         insert();
     }
     create_map();
     create_queue();
    
     dijkstra();
     print();
     display();
     
}
