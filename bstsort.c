#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

 

struct node {
  char word[10];
  struct node *left;
  struct node *right;
}*Root=NULL;

typedef struct node bstsort;
int check(char[],char[]);
void insert(bstsort *);
void view(bstsort *);

int check(char a[],char b[]){
     int i,j,c;
     for(i=0,j=0 ; a[i]!='\0'&&b[j]!='\0' ; i++,j++){
       if(a[i]>b[j]){
         c=1;
         break;
       }
        else if(b[j]>a[i]){
          c=-1;
          break;
        }
      else
         c=0;
     }
     if(c==1)
       return 1;
      else if(c==-1)
        return -1;
      else
        return 0;
}


void insert(bstsort *temp){
  int flag=0;
  bstsort *ptr,*par;
  ptr=Root;

  if(Root==NULL)
     Root=temp;
  else{
     while(ptr!=NULL ){
       if(check(temp->word,ptr->word)>0){
         par=ptr;
         ptr=ptr->right;
       }

       else if(check(temp->word,ptr->word)<0)
     {
       par=ptr;
       ptr=ptr->left;
     }
       else if(check(temp->word,ptr->word)==0){
          flag=1;
          return;
       }

   }
       if(flag==0 && ptr==NULL){

         if(check(par->word,temp->word)==1)
            par->left=temp;
         else if(check(par->word,temp->word)==-1)
            par->right=temp;
       }

     }

}

void view(bstsort *ptr){
  if(Root==NULL)
    printf("\nEmpty!!\n");

  else if(ptr !=NULL){
   view(ptr->left);
   printf("%s",ptr->word);
   view(ptr->right);
  }

}

void viewUpper(bstsort *ptr){
  if(Root==NULL)
    printf("\nThe input file has no words that are entirely uppercase!");

  else if(ptr !=NULL){
   viewUpper(ptr->left);
   printf("%s\n",ptr->word);
   viewUpper(ptr->right);
  }

}



int isBlank (char * line)
{
  char * ch;
  int is_blank = 0;

  // Iterate through each character.
  for (ch = line; *ch != '\0'; ++ch)
  {
    if (!isspace(*ch))
    {
      // Found a non-whitespace character.
      is_blank = 1;
      break;
    }
  }

  return is_blank;
}


bool isUpperCase(char *str) {
  int i;
  bool upperFlag = true;
  for(i=0; i<strlen(str); i++) {
      if (islower(str[i])) {
         upperFlag = false;
         return upperFlag;
      }
  }
  
}




void readFromFile (char *file) {
   char buf[512];
   bstsort *temp2;

   FILE *fptr = fopen(file, "r"); 

   if (fptr == NULL) {
     fprintf(stderr, "Cannot read file: %s",file);
     exit(1);
   }
 
   while( fscanf(fptr, "%s", buf) != EOF ) {
      //printf("%s\n", buf);
      temp2 = (bstsort*)malloc(sizeof(bstsort));
      temp2->left = NULL;
      temp2 -> right = NULL;
      strcpy(temp2->word, buf);
      insert(temp2);
   }

   free(temp2);
}

void readUpper (char *file) {
   char buf[512];
   int res;
   bstsort *temp3;

   FILE *fptr = fopen(file, "r"); 

   if (fptr == NULL) {
     fprintf(stderr, "Cannot read file: %s",file);
     exit(1);
   }
 
   while( fscanf(fptr, "%s", buf) != EOF ) {
      //printf("%s\n", buf);
      temp3 = (bstsort*)malloc(sizeof(bstsort));
      temp3->left = NULL;
      temp3 -> right = NULL;
      res = isUpperCase(buf);
      if (res) {
      	  strcpy(temp3->word, buf);
          insert(temp3);
      }
   }
  
  free(temp3);

}


void writeToFile(bstsort *pointer, FILE *fptr) {
    
  if(Root==NULL)
    printf("\nEmpty!!\n");

  else if(pointer !=NULL){
   writeToFile(pointer->left, fptr);
   fprintf(fptr,"%s\n",pointer->word);
   writeToFile(pointer->right, fptr);
  }


}

 
int main(int argc, char *argv[]) {

  char my_word[100];
  int opt;
  bstsort *temp;
  
  if (argc > 1) 
     goto ARGS;
  else
     goto NO_ARGS;
     
     
ARGS:
	
  while((opt = getopt(argc, argv, "c:o:")) != -1)
     {
	switch(opt)
	    {
		case 'c':
			//printf("optarg = %s\n",optarg);
			readUpper(optarg);
			goto VIEW_UPPER;
			break;
		case 'o':
			if (!argv[3]) {
			   fprintf(stderr, "Usage: ./bstsort -o OUTPUTFILE inputfile.");
			   goto END;
			}
			readFromFile(argv[3]);
		        FILE *fp = fopen(optarg, "w");
			if (fp == NULL) {
			   fprintf(stderr, "Failed to write to file: %s",fp);
			   goto END;
			}
		        writeToFile(Root, fp);
		        fclose(fp);
			break;
		case '?':
			if (optopt == 'c' || optopt == 'o') 
				fprintf(stderr, "option -%c needs an argument\n",optopt);
			else
				fprintf(stderr, "Unknown option -%c\n",optopt);
			break;
		default:
			fprintf(stderr, "getopt");
			break;
		}
	}
	goto END;

NO_ARGS:

  fgets(my_word, 100, stdin);
  while(isBlank(my_word)) {
      temp = (bstsort*)malloc(sizeof(bstsort));
      temp->left = NULL;
      temp -> right = NULL;
      strcpy(temp->word, my_word);
      insert(temp);
      fgets(my_word, 100, stdin);
      isBlank(my_word);
  }
free(temp);
view(Root);
goto END;
 
VIEW_UPPER:
   viewUpper(Root);
END:
  return 0;
}
