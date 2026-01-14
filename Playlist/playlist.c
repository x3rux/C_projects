#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void appendSongNode(Playlist* list, char* title, char* artist, float duration){
    Song* song = malloc(1*sizeof(Song));
    song->title    = strdup(title);
    song->artist   = strdup(artist);
    song->duration = duration;

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
}

void addSong(Playlist* list){
    Song* song = malloc(1*sizeof(Song));
    printf("Enter song details in order:\nTitle\nArtist\nDuration\n");
    //ms is not posix compliant it automatically allocates mem on runtime
    //without this would have to make a separate readline() function 
    char* title;
    char* artist;
    float duration;
    scanf("%ms", &title);
    scanf("%ms", &artist);
    scanf("%f", &duration);
    
    appendSongNode(list, title, artist, duration);
    displayList(list);
    free(title);
    free(artist);
}

void deleteSong(Playlist* list){
    Song* prev = NULL;
    Song* curr = list->head;
    printf("Enter title and artist name for song to delete:\n");
    char* title;
    char* artist;
    scanf("%ms", &title);
    scanf("%ms", &artist);
    int i;
    int found = 0;
    for(i = 0; i < list->count; i++){
	if(strcmp(title, curr->title) == 0 && strcmp(artist, curr->artist) == 0){
	    found = 1;
	    break;
	}
	prev = curr;
	curr = curr->next;
    }

    if(found == 0){
	printf("Song not found!\n");
	return;
    }

    if(i == 0){
	list->head = curr->next;
	if(list->head == NULL){
	    list->tail = NULL;
	}
    }
    else if(i == list->count - 1){
	list->tail = prev;
	list->tail->next = NULL;
    }
    else{
	prev->next = curr->next;
    }
    list->count--;
    printf("Printing current list\n");
    displayList(list);

    free(title);
    free(artist);
    free(curr->artist);
    free(curr->title);
    free(curr);
}

void exportToFile(Playlist* list){
    FILE* fplaylist = fopen("playlist.csv", "a");
    if(fplaylist == NULL){
	printf("Error opening file!\n");
	return;
    }
    
    Song* curr = list->head;
    for(int i = 0; i < list->count; i++){
	fprintf(fplaylist, "%s,%s,%0.0f\n", curr->title, curr->artist, curr->duration );
	curr = curr->next;
    }
    printf("Successfully exported playlist to 'playlist.csv'\n");
}

void importFromFile(char* filename, Playlist* list){
    FILE* fsongs = fopen(filename, "r");
    if(fsongs == NULL){
        printf("Error opening file!\n");
        exit(-1);
    }

    char line[1024];
    char* delims = ",\n";
    while(fgets(line, sizeof(line), fsongs) != NULL){
        char* title = strtok(line, delims);
        char* artist = strtok(NULL, delims);
        float duration = atof(strtok(NULL, delims)); 

        appendSongNode(list, title, artist, duration);
    }
    printf("Printing current list:\n");
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
	printf("5. Import from file\n");
	printf("6. Export to file\n");
	printf("7. Exit\n");

	scanf("%d", &choice);
	if(choice == 1){
	    addSong(list);
	}
	else if(choice == 2){
	    searchSong(list);
	}
	else if(choice == 3){
	    deleteSong(list);
	}
	else if(choice == 4){
	    displayList(list);
	}
	else if(choice == 5){
            char* filename = "playlist.csv";
	    importFromFile(filename, list);
	}
	else if(choice == 6){
	    exportToFile(list);
	}

    }while(choice != 7);

    return 0;
}
