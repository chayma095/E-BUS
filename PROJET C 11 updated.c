#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
struct BUS{
    int busId;
    int siegeDispo;
    char depart[100];
    char destination[100];
    struct BUS* next;
};
struct Voyageur {
    int ID;
    char nom[100];
    int reservationID;
    struct Voyageur* next;
};
typedef struct
{
struct Voyageur *Vhead;
struct Voyageur* Vtail;
} queueV;
struct Reservation {
    int reservationID;
    int busId;
    int  ID;
    struct Reservation* next;
};
typedef struct
{
struct Reservation *Rhead;
struct Reservation *Rtail;
} queueR;

struct BUS* B;
queueV* V=NULL;
queueR* R=NULL;



void menu(){
    printf("\nBIENVENUE DANS E-BUS\n");
    printf("°Creer un nouveau compte voyageur\n");
    printf("°Creer une nouvelle réservation\n");
    printf("°Voir les details des bus\n");
    printf("°Afficher et modifier les details d’une réservation\n");
    printf("°Annulation de reservation\n");
}




struct Voyageur* createTraveler(char* nom) {
    struct Voyageur* nvVoyageur = (struct Voyageur*)malloc(sizeof(struct Voyageur));
    if (nvVoyageur== NULL) {
        printf("Erreur lors de l'allocation de la mémoire pour le voyageur.\n");
        return NULL;
    }
    struct Voyageur* tempv;
    while (tempv!=NULL){
        tempv=tempv->next;
    }
    nvVoyageur->reservationID=++(tempv->reservationID);
    tempv->next=nvVoyageur;
    nvVoyageur->next=NULL;
    return nvVoyageur;
}
void creerUnNouveauCompteVoyageur(){
    char nom[100];
    printf("TAPEZ LE NOM DU VOYAGEUR:");
    scanf("%s",nom);
    struct Voyageur* nvVoyageur=createTraveler(nom);
    if (nvVoyageur==NULL) {
        printf("ERREUR!");
    }
    if (queueV->Vhead==NULL){
        queueV->Vhead=nvVoyageur;
        queueV->Vtail=nvVoyageur;

    }
    else{
        queueV->Vtail->next = nvVoyageur;
        queueV->Vtail=nvVoyageur;
    }

    printf("VOTRE COMPTE VOYAGEUR A ETE CREE! \n");

}
void enregistrerReservations() {
    FILE *fichierReservations = fopen("reservations.txt", "r");
    if (fichierReservations == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour chargement.\n");
        return;
    }

    fclose(fichierReservations);
}
struct Reservation* createReservation(int busId, int ID) {
    struct Reservation* nvReservation = (struct Reservation*)malloc(sizeof(struct Reservation));
    if (nvReservation == NULL) {
        printf("Erreur lors de l'allocation de la mémoire pour la réservation.\n");
        return NULL;
    }
    nvReservation->busId = busId;
    nvReservation->ID = ID;
    nvReservation->next = NULL;
    return nvReservation;
}



void reservation(){
    int busId,ID;
    printf("Entrez le numéro de bus pour la réservation : ");
    scanf("%d",&busId);
    printf("Entrez votre identificateur de reservation:");
    scanf("%d",&ID);
    struct Reservation* nvReservation=createReservation(busId,ID);
    if (B==NULL){
        printf("desole il n'y a pas de bus disponible");
    }
    struct BUS*tempo=B;
    while((tempo!=NULL) && (tempo->busId!=busId)){
        tempo=tempo->next;
    }
    if (tempo==NULL){
        printf("pas de reservation dispoible pour le moment!");

    }
    if (tempo->siegeDispo >0){
        tempo->siegeDispo--;
        (queueR->Rtail)->next=nvReservation;
        (queueR->Rtail)=nvReservation;
        printf("reservation réussite!");

    }
    else{
        printf("désolé c'est complet!");
    }


}
void detailsBus(){
    printf("°LES DETAILS DES BUS°\n");
    printf("le numéro du BUS\n");
    printf("le départ du bus\n");
    printf("la destination du bus\n");
    printf("les sièges disponibles dans le bus\n");
    struct BUS* tempo=B;
    while(tempo!=NULL){
        printf("%d",tempo->busId);
        printf("%s",tempo->depart);
        printf("%s",tempo->destination);
        printf("%d",tempo->siegeDispo);
        tempo=tempo->next;
    }

}
void detailsReservation(){
    int reservationID;
    printf("entrez votre identificateur de reservation:");
    scanf("%d",&reservationID);
    struct Reservation* auxR=queueR->Rhead;
    while ((auxR!=NULL) && (auxR->reservationID!=reservationID)){
        auxR=auxR->next;
    }
    if (auxR==NULL){
        printf("AUCUNE RESERVATION TROUVEE!!");
    }
    else{
        printf("VOICI LES DETAILS DE VOTRE RESERVATION:\n");
        printf("identificateur de reservation:%d\n",auxR->reservationID);
        printf("identifcateur du bus:%d\n",auxR->busId);
        printf("identificateur du voyageur:%d\n",auxR->ID);
    }


}
void annulationReservation(){
    int reservationID;
    printf("saisir votre identicateur de reservation ici:");
    scanf("%d",&reservationID);
    queueR* tempR=queueR->Rhead;
    queueR* p=queueR->Rhead;
    while((tempR!=NULL)&&(tempR->reservationID!=reservationID)){
        p=tempR;
        tempR=tempR->next;
    }
    if (tempR==NULL){
        printf("cette reservation n'existe pas!!");
    }
    else if (tempR=(queueR->Rhead)){
        free(tempR);
        (queueR->Rhead)=(tempR->next);
    }
    else if (tempR=(queueR->Rtail)){
        free(tempR);
        (queueR->Rtail)=p;
    }
    else{
        p=p->next;
        free(tempR);
        tempR=p->next;

    }
}


int main(){
    int option;
    do{
        menu();
        printf("quelle option vous voulez?");
        scanf("%d",&option);
        if (option==1){
            creerUnNouveauCompteVoyageur();
            break;
        }
        else if (option==2){
            reservation();
            break;
        }
        else if (option==3){
            detailsBus();
            break;
        }
        else if (option==4){
            detailsReservation();
            break;
        }
        else if (option==5){
            annulationReservation();
            break;
        }
        else{
            printf("ESSAYEZ DE NOUVEAU");
        }    
    }while (option!=6);


}

