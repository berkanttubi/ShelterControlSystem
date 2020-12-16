/*

BERKANT TUGBERK DEMIRTAS 231523

When rehashing requires and you want to add a dog into the table, first time of entering (1) in the menu
does the rehashing and then again you again enter 1 for adding new dog.

*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Struct is for keeping information of the dog
// the date with begins with 'e' represent enter day, with 'l' one represents leave day.
struct info{

int dog_id;
char dog_name[30];
float dog_weight;
float dog_height;
int e_day;
int e_month;
int e_year;
int l_day;
int l_month;
int l_year;
};

int hashFunction(int,int); // Hash Function that returns key % size
void initializeStruct(int,struct info *); // Initialize the Struct
int isItValid(int,int,struct info *); // This function takes id,capacity and struct then checks if the cell is empty or not
void add_dog(struct info *,int,int,char*,float,float,int,int,int); // Add function
void display(struct info *,int); //Display the hash table to check if functions work
int isItPrime(int); // For rehashing operations checks the capacity is prime or not
int makePrime(int); // For rehashing operations, it makes the capacity prime
struct info * reHashing(struct info *,int); // Makes the rehashing operation
int searching(struct info *, int, int); // Searches the struct with given id
void adoptingDog(struct info *, int, int); // When dog is adapted, update the leave dates

int main(){

    int choice=0,dogCounter=0; // Choice is for user input, dogCounter is counts the number of dog registered for load factor
    int capacity=11; // Capacity of hash table
    struct info *dogs; // initialize the structure
    float load_factor; // to eveluate load factor
    int id,e_day,e_month,e_year;
    char dog_name[30];
    float dog_weight,dog_height;
    int i;

    dogs = (struct info *) malloc(sizeof(struct info)*capacity); //Malloc the struct
    initializeStruct(capacity,dogs); // Initialize the struct

    while(choice!=4){ // Menu loop, works until user enters 4

        printf("Add a dog (1), Search a dog(2),Adopt a dog (3), Exit(4) : ");
        scanf("%d",&choice);
        load_factor = (float)dogCounter/(float)capacity; // evaluate load factor to rehashing

        if(choice==1){

            if(load_factor<=0.5 ){ // If load factor is less than 0.5

                printf("Enter unique identifier: ");
                scanf("%d",&id);
                 fflush(stdin);
                printf("Name: ");
                gets(dog_name);
                printf("Weight: ");
                scanf("%f",&dog_weight);
                printf("Height: ");
                scanf("%f",&dog_height);
                printf("Entry Date: ");
                scanf("%d.%d.%d",&e_day,&e_month,&e_year);
                add_dog(dogs,capacity,id,dog_name,dog_weight,dog_height,e_day,e_month,e_year); // Adds dog to the hash table with informations
                printf("%s has been added to the dog shelter\n",dog_name);
                dogCounter++;
            }
            else{ // If load factor more than 0.5 makes rehashing

                dogs=reHashing(dogs,capacity); //Does the rehashing

                //Updates the capacity
                capacity=capacity*2;
                capacity=makePrime(capacity);

            }

        }

        if(choice==2){

            printf("Enter unique identifier: ");
            scanf("%d",&id);
            searching(dogs,capacity,id);


        }

        if(choice==3){
            printf("Enter unique identifier: ");
            scanf("%d",&id);
            adoptingDog(dogs,capacity,id);


        }



    }




    return 0;
}

//This function initialize the struct for searching easily.

void initializeStruct(int capacity,struct info *dog){
    int i;
    for(i=capacity;i>=0;i--){

        dog[i].dog_id=-1;
        dog[i].dog_height=0;
        strcpy(dog[i].dog_name,"NULL");
        dog[i].dog_weight=0;
        dog[i].e_day=0;
        dog[i].e_month=0;
        dog[i].e_year=0;
        dog[i].l_day=0;
        dog[i].l_month=0;
        dog[i].l_year=0;


    }

}
//This function display the table.
void display(struct info *dog,int capacity){

    int i;

    for(i=0;i<capacity;i++){

        printf("id: %d name: %s \n",dog[i].dog_id,dog[i].dog_name);


    }


}

//Returns the hash function given in assignment
int hashFunction(int key, int capacity){
    return key%capacity;
}

//This function checks if place is empty or not
//We initialized the struct id to -1, if it is still -1 that means this place is empty

int isItValid(int place, int capacity, struct info *dog){

    if(dog[place].dog_id==-1)
        return 0;

    return 1;

}

// Checks the number is empty or not for rehashing
int isItPrime(int n)
{
  int i;
  if (n == 1 || n == 0)
  {
    return 0;
  }
  for (i = 2; i < n / 2; i++)
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

// Round the number near prime number for rehashing
int makePrime(int n){

if (n % 2 == 0)
  {
    n++;
  }
  while (!isItPrime(n))
  {
    n += 2;
  }
  return n;

}

// This function adds dog to the table

void add_dog(struct info *dog,int capacity,int dog_id,char dog_name[30],float dog_weight,float dog_height,int e_day,int e_month,int e_year){

    int valid=0;
    int valid_id=0;
    double hash;
    double place;
    int counter=0;
    int i;

    hash= hashFunction(dog_id,capacity);// Hash variable gets the hash function value
    place=hash; // set place to this. If it is not empty do proper operations


        for(i=0;i<capacity;i++){ // This loops check if the id is repeated or not
            if(dog[i].dog_id == dog_id && dog_id!=-1){
                printf("ID can not be repeated. Please enter a new identifier: ");
                scanf("%d",&dog_id);
                i=-1; // If id is repeated makes i=-1 for begin the loop again from the beginning
            }
        }


    while(!valid){ // This loop works until finding proper place to store the values in hash table

        if(!isItValid((int)hash,capacity,dog)){ // If the place is not available, find the proper place according to the formula
            place = (hash + pow(counter,2));
            place = (int)place%capacity;
            dog[(int)place].dog_id = dog_id;
            valid=1;

        }
        else if (isItValid((int)hash,capacity,dog)){ // If the place is valid

            dog[(int)place].dog_id = dog_id;
            valid=1; // makes valid 1 for exit the loop

        }



    }

    // Then stores the values into proper place in table

    strcpy(dog[(int)place].dog_name,dog_name);
    dog[(int)place].dog_weight=dog_weight;
    dog[(int)place].dog_height=dog_height;
    dog[(int)place].e_day = e_day;
    dog[(int)place].e_month = e_month;
    dog[(int)place].e_year = e_year;


}

// This function makes the rehashing operation
struct info * reHashing(struct info * dogs,int capacity){
    int i;
    // determine the new prime capacity
    int newCapacity = capacity;
    newCapacity=newCapacity*2;
    newCapacity=makePrime(newCapacity);

    struct info * temp; // temporary struct
    temp= (struct info *) malloc(sizeof(struct info)*newCapacity);
    initializeStruct(newCapacity,temp); // initialize the temp struct


    // Copy the elements in the main hash table into temp hash table to avoiding info losing while resizing
    for(i=0;i<capacity;i++){
        add_dog(temp,newCapacity,dogs[i].dog_id,dogs[i].dog_name,dogs[i].dog_weight,dogs[i].dog_height,dogs[i].e_day,dogs[i].e_month,dogs[i].e_year);
    }

    // resize the main hash table
    dogs= (struct info *) realloc(dogs,sizeof(struct info)*newCapacity);
    initializeStruct(newCapacity,dogs);

    dogs=temp; // Copy the temp table into main hash table

    printf("Rehashing completed...");

    free(temp); // free the temp

return dogs; // return the table
}

// This function makes the searching operation

int searching(struct info * dogs,int capacity, int id){

    int i;

    for(i=0;i<capacity;i++){ // Traverse the table

        if(dogs[i].dog_id==id){ // If id is found writes the information of it
            printf("Name: %s \n Weight: %.2f \n Height: %.2f \n Entry Date: %d.%d.%d \n",dogs[i].dog_name,dogs[i].dog_weight,dogs[i].dog_height,dogs[i].e_day,dogs[i].e_month,dogs[i].e_year);
            return i;
        }
    }
        printf("\nNo dog is found\n");
        return -1;

}

// This function for adopting dogs

void adoptingDog(struct info * dogs,int capacity, int id){

    int l_day,l_month,l_year;
    int d= searching(dogs,capacity,id); //checks if the id is in the hash table

    if(d!=-1 && dogs[d].l_day ==0 ){ // If given id is in the hash table and it is not adopted
        printf("Enter leave date: ");
        scanf("%d.%d.%d",&l_day,&l_month,&l_year);
        dogs[d].l_day=l_day;
        dogs[d].l_month=l_month;
        dogs[d].l_year=l_year;
        printf("%s has been adopted.\n",dogs[d].dog_name);
    }
    else if(dogs[d].l_day !=0 && d!=-1){ // If id is in the table but it is leave day is 0 which means not adopted. Because we initially made it 0.

        printf("It is already adopted\n");
    }

}
