#include <stdio.h>
#include <stdlib.h>


typedef struct Stop {
    char name[50];
    struct Line* lines;
    struct Stop* next;
} Stop;

typedef struct Line {
    char name[50];
    Stop* stops;
    struct Line* next;
} Line;

typedef struct Trip {
    Stop* start;
    Stop* end;
    Line** connections;
    int num_connections;
} Trip;

Stop* create_stop(char* name) {
    Stop* stop = (Stop*)malloc(sizeof(Stop));
    strcpy(stop->name, name);
    stop->lines = NULL;
    stop->next = NULL;
    return stop;
}

Line* create_line(char* name) {
    Line* line = (Line*)malloc(sizeof(Line));
    strcpy(line->name, name);
    line->stops = NULL;
    line->next = NULL;
    return line;
}

void add_stop_to_line(Line* line, Stop* stop) {
    Stop* current = line->stops;
    if (current == NULL) {
        line->stops = stop;
    } else {
        while (current->next!= NULL) {
            current = current->next;
        }
        current->next = stop;
    }
    stop->lines = line;
}

void add_line_to_stop(Stop* stop, Line* line) {
    Line* current = stop->lines;
    if (current == NULL) {
        stop->lines = line;
    } else {
        while (current->next!= NULL) {
            current = current->next;
        }
        current->next = line;
    }
    line->stops = stop;
}

Trip* create_trip(Stop* start, Stop* end) {
    Trip* trip = (Trip*)malloc(sizeof(Trip));
    trip->start = start;
    trip->end = end;
    trip->connections = NULL;
    trip->num_connections = 0;
    return trip;
}

void add_connection_to_trip(Trip* trip, Line* line) {
    Line** new_connections = (Line**)realloc(trip->connections, (trip->num_connections + 1) * sizeof(Line*));
    new_connections[trip->num_connections] = line;
    trip->connections = new_connections;
    trip->num_connections++;
}



int main(){ Stop* stop1 = create_stop("Gare de Lyon");
    Stop* stop2 = create_stop("Gare du Nord");
    Stop* stop3 = create_stop("Gare de l'Est");
    Stop* stop4 = create_stop("Gare Montparnasse");

    // Créer les lignes de train
    Line* line1 = create_line("Ligne 1");
    Line* line2 = create_line("Ligne 2");
    Line* line3 = create_line("Ligne 3");

    // Ajouter les arrêts aux lignes
    add_stop_to_line(line1, stop1);
    add_stop_to_line(line1, stop2);
    add_stop_to_line(line2, stop2);
    add_stop_to_line(line2, stop3);
    add_stop_to_line(line3, stop3);
    add_stop_to_line(line3, stop4);


    add_line_to_stop(stop1, line1);
    add_line_to_stop(stop2, line1);
    add_line_to_stop(stop2, line2);
    add_line_to_stop(stop3, line2);
    add_line_to_stop(stop3, line3);
    add_line_to_stop(stop4, line3);

    //cree la trajet
    Trip* trip = create_trip(stop1, stop4);

    // ce qui donne le trajet
    add_connection_to_trip(trip, line1);
    add_connection_to_trip(trip, line2);
    add_connection_to_trip(trip, line3);

    // Affiche le trajet
    printf("Le trajet optimal entre %s et %s est :\n", trip->start->name, trip->end->name);
    for (int i = 0; i < trip->num_connections; i++) {
        printf("Prendre la ligne %s à l'arrêt %s\n", trip->connections[i]->name, trip->connections[i]->stops->name);
    }

    return 0;
}