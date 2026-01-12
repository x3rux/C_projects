#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD_FLAG "--add"


typedef struct Song{
    char* title;
    char* artist;
    float duration;
    struct Song* next;
} Song;

typedef struct Playlist{
    Song* head;
    Song* tail;
    int count;
} Playlist;

void displayList(Playlist* list){
    Song* curr_song = list->head;
    for(int i = 0; i<list->count; i++){
	printf("Title: %s, Artist: %s, Duration: %0.0f\n", curr_song->title, curr_song->artist, curr_song->duration);
	curr_song = curr_song->next;
    }
}

void searchSong(Playlist* list){
    printf("Enter title and artist name:\n");
    char* title;
    char* artist;
    scanf("%ms", &title);
    scanf("%ms", &artist);

    Song* curr_song = list->head;
    for(int i = 0; i < list->count; i++){
	if(strcmp(title, curr_song->title) == 0 && strcmp(artist, curr_song->artist) == 0){
	    printf("Song found in list on index %d\n!", i);
	    return;
	}
	curr_song = curr_song->next;
    }
    printf("Song not found!\n");
}

void addSong(Playlist* list){
    Song* song = malloc(1*sizeof(Song));
    printf("Enter song details in order:\nTitle\nArtist\nDuration\n");
    //ms is not posix compliant it automatically allocates mem on runtime
    //without this would have to make a separate readline() function 
    scanf("%ms", &song->title);
    scanf("%ms", &song->artist);
    scanf("%f", &song->duration);

    if(list->count == 0){
	list->head = song;
	list->tail = song;
    }
    else{
	list->tail->next = song;
	list->tail = song;
    }
    song->next = NULL;
    list->count++;

    printf("Displaying current playlist:\n");
    displayList(list);
}

int main(){

    Playlist* list = calloc(1, sizeof(Playlist));
    if(list == NULL){
	printf("Error making list!\n");
	exit(-1);
    }
    list->count = 0;

    int choice;

    do {
	printf("Enter your choice:\n");
	printf("1. Add a song\n");
	printf("2. Search for a song\n");
	printf("3. Delete a song\n");
	printf("4. Display playlist\n");
	printf("5. Export to file\n");
	printf("6. Exit\n");

	scanf("%d", &choice);
	if(choice == 1){
	    addSong(list);
	}
	else if(choice == 2){
	    searchSong(list);
	}
	else if(choice == 4){
	    displayList(list);
	}

    }while(choice != 6);

    return 0;
}
