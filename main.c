#include <stdio.h>
#include <string.h> /* Pour faire des modif sur les tableaux de char */
#include <stdlib.h>
#include <time.h>    // pour initialiser rand
#include <math.h>    // pour floor() et ceil()

struct supemon {
char name[55];
int level;
int pointMax;
int exp;
int hp;
int hp_max;
int atk;
int atk_base;
int def;
int def_base;
int evasion;
int evasion_base;
int accuracy;
int accuracy_base;
int speed;
char move[150];
};

struct player {
char name[55];
struct supemon liste_sup[4];
int sele_Supemon;
int nb_supemon;
int supcoin;
char item[150];
};




void callMoveFunction (struct supemon *a, struct supemon *d, struct player *b, char *nom, int ordre);
int arrondiAleatoire(double damage);
void attackmove(double moveAttack, struct supemon *a, struct supemon *d); // N'oublie pas de changer ici aussi si tu changes en bas!
void accuracy_tester(double accu, double evas, struct supemon *a, struct supemon *d, int damage_arrondi);
void callMoveFunctionEnnemy (struct supemon *a, struct supemon *d);
void Affichage (struct supemon *a, struct supemon *d, struct player *b, char *nom, int ordre);
int capture_tester(struct player *b, struct supemon *d);
int escape_tester(struct supemon *a, struct supemon *d);
struct supemon* changeSupemon(struct supemon *a, struct player *b);
void testXp (struct supemon *a, struct player *b, char *nom);
int Affichage_Debut (struct supemon battle_sup[], struct player *b, char *nom);
void Affichage_Debut_continue (int choix1, struct supemon battle_sup[], struct player *b, char *nom);
void supemonCentre(struct player *b);


int main()
{
    srand(time(NULL)); // je le rajoute ici car il ne faut l'appeler qu'une seule fois et c'est pour génerer des nombres aléatoires
    char nom[50];

    printf("Entre ton Prenom : ");
    scanf("%49s", nom); /*Que je mette le '&' ou pas devant le 'nom', ca marche, je pensais il faut le '&' car c'etait un pointeur ca pointe vers la ou la valeur elle est sauvegarder. Mais pour un tableau, quand tu appelle le tableau, ca pointe directememnt vers le pointeur donc t a pas a t en faire. Et le '49' c'est pour dire tu prend un max de 49 char*/
    fflush(stdin); // important pour que la valeur donner dans le 'scanf' avant ne vienne pas reecrire la nouvelle valeur dans un autre 'scanf'

    printf("\nHello %s !\n", nom);
    printf("Welcome in Supemon World\n\n");
    int choix, choix1;
    char supe_depart[50]; /* Ici je définis sans aucun doute un pointeur vers le début du tableau 'sup_depart' (qui est utilisé d'ailleurs ici pour stoquer des chaine de caractere) */

    printf("+----------------------------+\n");
    printf("|Choose your starter Supemon:|\n");
    printf("|   1 - Supmander            |\n");
    printf("|   2 - Supasaur             |\n");
    printf("|   3 - Supirtle             |\n");
    printf("+----------------------------+\n");
    printf("1, 2 or 3: ");
    scanf("%d",&choix);
    fflush(stdin);
    switch (choix) {
        case 1:
            strcpy(supe_depart, "Supmander"); break; /* Ici je demande à aller à la 1er valeur que pointe le pointeur (1ere case du tablea 'sup_depart') et je vais écrire la chaine de caractere */
        case 2:
            strcpy(supe_depart, "Supasaur"); break;
        case 3:
            strcpy(supe_depart, "Supirtle"); break;
    }
    printf("\nVotre choix : %s\n", supe_depart);

    struct supemon supmander; // Je creer une instance de cet objet (ou var)
    strcpy(supmander.name, "supmander"); /* Comme j'ai mis le '*' devant 'supmander.name', je vais chercher le pointeur de 'supmander.name' -> etdonc je peux écrire du char dedans sans problèmes */
    supmander.level = 1;
    supmander.exp = 0;
    supmander.hp = 10;
    supmander.hp_max = 10;
    supmander.atk = 1;
    supmander.atk_base = 1;
    supmander.def = 1;
    supmander.def_base = 1;
    supmander.evasion = 1;
    supmander.evasion_base = 1;
    supmander.accuracy = 2;
    supmander.accuracy_base = 2;
    supmander.speed = 1;
    supmander.pointMax = 500;
    strcpy(supmander.move, "scratch grawl"); /* Pareil ici */

    struct supemon supasaur;
    strcpy(supasaur.name, "supasaur");
    supasaur.level = 1;
    supasaur.exp = 0;
    supasaur.hp = 9;
    supasaur.hp_max = 9;
    supasaur.atk = 1;
    supasaur.atk_base = 1;
    supasaur.def = 1;
    supasaur.def_base = 1;
    supasaur.evasion = 3;
    supasaur.evasion_base = 3;
    supasaur.accuracy = 2;
    supasaur.accuracy_base = 2;
    supasaur.speed = 2;
    supmander.pointMax = 500;
    strcpy(supasaur.move, "pound foliage");

    struct supemon supirtle;
    strcpy(supirtle.name, "supirtle");
    supirtle.level = 1;
    supirtle.exp = 0;
    supirtle.hp = 11;
    supirtle.hp_max = 11;
    supirtle.atk = 1;
    supirtle.atk_base= 1;
    supirtle.def = 2;
    supirtle.def_base =2;
    supirtle.evasion = 2;
    supirtle.evasion_base = 2;
    supirtle.accuracy = 1;
    supirtle.accuracy_base = 1;
    supirtle.speed = 2;
    supmander.pointMax = 500;
    strcpy(supirtle.move, "pound shell");

    struct supemon battle_sup[3];
    battle_sup[0] = supmander;
    battle_sup[1] = supasaur;
    battle_sup[2] = supirtle;

    struct player player1;
    strcpy(player1.name, nom);
    //player1.liste_sup[0] = supmander;
    printf("Je rajoute un supemon supplementaire pour permettre de voir le changement de supemon! (supirtle)\n\n");
    player1.liste_sup[1] = supirtle; // ici je rajoute un 2eme supemon a la liste du jouer
    player1.sele_Supemon = 0;
    player1.nb_supemon = 2; // j'oublie pas de changer le nb de suoemon
    player1.supcoin = 0;

    for (int i = 0; i<3; i++) {
        if ((choix-1) == i) {
            player1.liste_sup[0] = battle_sup[i];
        }
    }




    choix1 = Affichage_Debut(battle_sup, &player1, &nom); // je passe le pointeur du char 'nom'
    /*printf("choix : %d", choix1);*/


    /* BATTLE */


    return 0;
}


int Affichage_Debut (struct supemon battle_sup[], struct player *b, char *nom) {
    int choix1;
    printf("+----------------------------+\n");
    printf("|Where do you want to go?    |\n");
    printf("|   1 - Into the wild        |\n");
    printf("|   2 - In the shop          |\n");
    printf("|   3 - In the Supemon Center|\n");
    printf("|   4 - Leave the game       |\n");
    printf("+----------------------------+\n");
    printf("1, 2, 3 or 4: ");
    scanf("%d",&choix1);
    fflush(stdin);
    Affichage_Debut_continue(choix1, battle_sup, b, nom);
}

void Affichage_Debut_continue (int choix1, struct supemon battle_sup[], struct player *b, char *nom) {
    if (choix1 == 1) {
        int ordre1;
        struct supemon supe_aleat = battle_sup[1];
        supe_aleat.exp = 1;
        int varTemp = b->sele_Supemon;
        struct supemon *supe_actuel = &b->liste_sup[varTemp]; // Je donne l'instance (la ou ce trouve le supemon du player), n'oublie pas de rajouter le '&' pour bien préciser que c'est un pointeur
        if (supe_actuel->speed > supe_aleat.speed) {
            ordre1 = 1;
        }
        else {
            ordre1 = 2;
        }
        //printf("%s", player1.])
        Affichage(supe_actuel, &supe_aleat, b, nom, ordre1); // 'b' est l'instance du player 1

    }

    else if (choix1 == 2) {
        Affichage_Debut(battle_sup, b, nom);
    }

    else if (choix1 == 3) {
        supemonCentre(b);
        Affichage_Debut(battle_sup, b, nom);
    }

    else if (choix1 == 4) {
        printf("You are going to quit the game\n");
    }
}


void Affichage (struct supemon *a, struct supemon *d, struct player *b, char *nom, int ordre) {
    int tabPourStopperATourEnnemy;
    int ordre1 = ordre;
    int cond1 = 1;
    //printf("j'affiche le nom du sup aleatoire : %s, puis celui d'origine : %s\n\n", supe_aleat.name, battle_sup[1].name);
    /*
    if (conditEntreeSeconde == 1){
        if (a->speed > d->speed) {
            ordre = 1;
        }
        else {
            ordre = 2;
        }
    }
    */

    while (cond1) {
        int choix2 = 0;

        if (ordre1 == 1) {
            printf("\nYour turn...\n\n");
            printf("%s (%s)\n", a->name, nom);
            printf("HP: %d/%d           Lvl: %d\n", a->hp, a->hp_max, a->level);
            printf("atk: %d             def: %d\n", a->atk, a->def);
            printf("acc: %d             Eva: %d\n", a->accuracy, a->evasion);
            printf("----------------------------\n");
            printf("\n%s (enemy)", d->name);
            printf("\n----------------------------\n");
            printf("HP: %d/%d           Lvl: %d\n", d->hp, d->hp_max, d->level);
            printf("atk: %d             def: %d\n", d->atk, d->def);
            printf("acc: %d             Eva: %d\n", d->accuracy, d->evasion);
            printf("\n----------------------------\n");

            printf("\n\n");
            printf("+----------------------------+\n");
            printf("|What will you do ?          |\n");
            printf("|   1 - Move                 |\n");
            printf("|   2 - Change Supemon       |\n");
            printf("|   3 - Use item             |\n");
            printf("|   4 - Capture              |\n");
            printf("|   5 - Run away             |\n");
            printf("+----------------------------+\n");
            printf("1, 2, 3, 4 or 5: ");
            scanf("%d",&choix2);
            fflush(stdin);
            if (choix2 == 1) {
                callMoveFunction (a, d, b, nom, ordre1); // Je donne l'adresse c'est plus pratique pour les manip (du moins quand pendant la création de la fonction, en para ta rentrer '*' devant les var, t'es obliger de passer '&' quand t appel la fonction)
                if (a->hp < 1 || d->hp < 1) {
                    printf("Game over!\n");
                    if (a->hp < 1) {
                        printf("You lose...\n");
                        break;
                    }
                    else {
                        printf("You win!\n");
                        break;
                    }
                }
                ordre1 += 1;
            }

            else if (choix2 == 2) {
                struct supemon *varTemp = changeSupemon(a, b);
                if (a == varTemp) {
                    printf("Vous n'avez pas changer de Supemon...\n");
                }
                else {
                    a = varTemp;
                    ordre1 +=1;
                    //printf("La valeur de ordre1 : %d", ordre1);
                }
                //a = changeSupemon(a, b); // Permet de changer le pointeur du player sur le nv supemon que le player a choisi

            }

            else if (choix2 == 3) {

            }

            else if (choix2 == 4) {
                printf("You are trying to capture the ennemy supemon!\n");
                int resultat = capture_tester(b, d);
                if (resultat == 1) {
                    break;
                }
                ordre1 += 1;
                //printf("La valeur de ordre1 : %d", ordre1);
            }

            else if (choix2 == 5) {
                int resultat = escape_tester(a, d); // Ici 'a' est le supe du player et 'd' est celui de l'ennemi
                if (resultat == 1) {
                    break;
                }
                ordre1 += 1;
                //printf("La valeur de ordre1 : %d", ordre1);
            }
        }
        else {
            printf("\n\nEnemy turn...");
            printf("\n%s (enemy)", d->name);
            printf("\n----------------------------\n");
            printf("HP: %d/%d           Lvl: %d\n", d->hp, d->hp_max, d->level);
            printf("atk: %d             def: %d\n", d->atk, d->def);
            printf("acc: %d             Eva: %d\n", d->accuracy, d->evasion);
            printf("\n----------------------------\n");
            printf("%s (%s)\n", a->name, nom);
            printf("HP: %d/%d           Lvl: %d\n", a->hp, a->hp_max, a->level);
            printf("atk: %d             def: %d\n", a->atk, a->def);
            printf("acc: %d             Eva: %d\n", a->accuracy, a->evasion);
            printf("----------------------------\n");
            callMoveFunctionEnnemy(d, a);
            ordre1 -= 1;
            printf("L'ennemy a jouer!\n");
            scanf("%d", &tabPourStopperATourEnnemy);
            fflush(stdin);
            if (a->hp < 1 || d->hp < 1) {
                printf("Game over!\n");
                if (a->hp < 1) {
                    printf("You lose...\n");
                    break;
                }
                else {
                    printf("You win!\n");
                    break;
                }
            }
        }
    }
    if (d->hp < 1) {
        int n = 100*((rand() % 5) + 1); // je multiplie 100*'un nb compri entre  1 et 5'
        a->exp += n;
        b->supcoin += n; // Ajoute des supcoins
        //a->exp += 500;
        //printf("nvlle xp avant l'appel de la fonction: %d\n", a->exp);
        testXp(a, b, nom); // test si le koueur a gagné un niveau
    }






}
/*
int arrondiAleatoire(double valeur) {
    // sépare la partie entière et décimale
    double entier = floor(valeur);
    double decimal = valeur - entier;

    // si la valeur est déjà entière, pas besoin d'arrondir
    if (decimal == 0.0) {
        return (int)valeur;
    }

    // tire un nombre aléatoire : 0 ou 1
    int hasard = rand() % 2;

    // si hasard == 0 → arrondi vers le bas, sinon vers le haut
    if (hasard == 0)
        return (int)floor(valeur);
    else
        return (int)ceil(valeur);
}
*/

void testXp (struct supemon *a, struct player *b, char *nom) {
    printf("J'affiche la valeur de exp : %d et celui de pointMax : %d\n", a->exp, a->pointMax);
    if (a->exp >= a->pointMax) {
        a->pointMax += 1000;
        printf("VOici les valeurs du Supemon actuelle : \n");
        printf("\n----------------------------\n");
        printf("%s (%s)\n", a->name, nom);
        printf("HP: %d/%d           Lvl: %d\n", a->hp, a->hp_max, a->level);
        printf("atk: %d             def: %d\n", a->atk, a->def);
        printf("acc: %d             Eva: %d\n", a->accuracy, a->evasion);
        printf("----------------------------\n");
        a->level += 1;
        a->exp = arrondiAleatoire((double)(a->exp) * 1.3);
        //printf("Exp apres la fonction : %d\n", a->exp);
        a->hp = arrondiAleatoire((double)(a->hp) * 1.3);
        a->hp_max = arrondiAleatoire((double)(a->hp_max) * 1.3);
        a->atk = arrondiAleatoire((double)(a->atk) * 1.3);
        a->atk_base = arrondiAleatoire((double)(a->atk_base) * 1.3);
        a->def = arrondiAleatoire((double)(a->def) * 1.3);
        a->def_base = arrondiAleatoire((double)(a->def_base) * 1.3);
        a->evasion = arrondiAleatoire((double)(a->evasion) * 1.3);
        a->evasion_base = arrondiAleatoire((double)(a->evasion_base) * 1.3);
        a->accuracy = arrondiAleatoire((double)(a->accuracy) * 1.3);
        a->accuracy_base = arrondiAleatoire((double)(a->accuracy_base) * 1.3);
        a->speed = arrondiAleatoire((double)(a->speed) * 1.3);
        printf("VOici les nouvelles valeurs du Supemon : \n");
        printf("\n----------------------------\n");
        printf("%s (%s)\n", a->name, nom);
        printf("HP: %d/%d           Lvl: %d\n", a->hp, a->hp_max, a->level);
        printf("atk: %d             def: %d\n", a->atk, a->def);
        printf("acc: %d             Eva: %d\n", a->accuracy, a->evasion);
        printf("----------------------------\n");
        printf("Voici vos supcoins : %d", b->supcoin);
    }
}

void callMoveFunction (struct supemon *a, struct supemon *d, struct player *b, char *nom, int ordre) { // T'es obliger de mettre le struct quand tu passe une 'class' que t'a toi meme creer
    int choix3;
    char choix4[15];
    int val_j;
    char move1[15] = "scratch";
    char move2[15] = "grawl";
    char move3[15] = "pound";
    char move4[15] = "foliage";
    char move5[15] = "shell";
    char move_supe_actuel1[15]; // pour sauvegarder la texte avant l'espace
    char move_supe_actuel2[15]; // pour sauvegarder la texte avant l'espace
    int compte; // C'est pour compter la longeuur du 1er move pour des questions de avoir les bonnes valeurs de i et ainsi bien écrire dans le tableau du 2eme move
    for (int i = 0; a->move[i] != '\0'; i++) {
        if (a->move[i] == ' ') {
            move_supe_actuel1[i] = '\0'; // on termine la chaîne (très important !)
            //printf("les cara qu'il y a : \n");
            //printf("Ce qu'il y a dans a->move : %s\n", a->move);
            for (int j = i+1; a->move[j] != '\0'; j++) { // peu importe que je mette 'i+3' il choisiras tjr le 'i' en haut!
                //printf("%c", a->move[j]);
                //printf("Valeur de j : %d\n", j);
                //printf("Valeur de i : %d\n", i);
                //printf("Valeur de j-j : %d\n", j-j);
                move_supe_actuel2[j-i-1] = a->move[j];
                val_j = j;
            }
            //printf("\nCa s'affiche en haut:\n");
            move_supe_actuel2[val_j-i]= '\0';
            break; // on s'arrête au premier espace
        }
        move_supe_actuel1[i] = a->move[i]; // on copie chaque caractère
    }

    //printf("j'affiche le 1er move : %s et le 2eme move : %s\n", move_supe_actuel1, move_supe_actuel2);
    //printf("Valeur de choix3 avant: %d\n", choix3);
    printf("1 - %s\n", move_supe_actuel1);
    printf("2 - %s\n", move_supe_actuel2);
    printf("3 - Cancel\n");
    printf("1, 2 or 3 : ");
    scanf("%d", &choix3); // Attention tu ne peux pas mettre de '\n' dans un 'scanf'! si tu peux mais, il y a des residu dans le buffer donc met un espace avant le '%f' ou autre chose
    fflush(stdin);
    //printf("\nValeur de choix3 apres: %d\n", choix3);
    switch (choix3) {
        case 1:
            strcpy(choix4, move_supe_actuel1); break;
        case 2:
            //printf("Je suis bien rentrer dans le case 2 \n");
            strcpy(choix4, move_supe_actuel2); break;
        case 3:
            Affichage(a, d, b, nom, ordre);
            break;
    }
    //printf("Valeur de choix4 : %s\n", choix4);
    double db1 = 3.0;
    double db2 = 2.0;
    if (strcmp(choix4, move1) == 0) {
        attackmove(db1, a, d);
    }
    else if (strcmp(choix4, move2) == 0) {
        a->atk += 1;
        printf("This gives you one attack (yourself)!\n");
    }
    else if (strcmp(choix4, move3) == 0) {
        attackmove(db1, a, d);
    }
    else if (strcmp(choix4, move4) == 0) {
        a->evasion += 1;
        printf("This gives you one evasion (yourself)!\n");
    }
    else if (strcmp(choix4, move5) == 0) {
        a->def += 1;
        printf("This gives you one def (yourself)!\n");
    }

}

void callMoveFunctionEnnemy (struct supemon *a, struct supemon *d) {
    int choix3;
    char choix4[15];
    int val_j;
    char move1_[15] = "scratch";
    char move2_[15] = "grawl";
    //printf("j'affiche direct move2_ : %s", move2_);
    char move3_[15] = "pound";
    char move4_[15] = "foliage";
    char move5_[15] = "shell";
    char move_supe_actuel1[15]; // pour sauvegarder la texte avant l'espace
    char move_supe_actuel2[15]; // pour sauvegarder la texte avant l'espace
    for (int i = 0; a->move[i] != '\0'; i++) {
        if (a->move[i] == ' ') {
            move_supe_actuel1[i] = '\0'; // on termine la chaîne (très important !)
            //printf("les cara qu'il y a : \n");
            //printf("Ce qu'il y a dans a->move : %s\n", a->move);
            for (int j = i+1; a->move[j] != '\0'; j++) { // peu importe que je mette 'i+3' il choisiras tjr le 'i' en haut!
                //printf("%c", a->move[j]);
                //printf("Valeur de j : %d\n", j);
                //printf("Valeur de i : %d\n", i);
                //printf("Valeur de j-j : %d\n", j-j);
                move_supe_actuel2[j-i-1] = a->move[j];
                val_j = j;
            }
            //printf("\nCa s'affiche en haut:\n");
            move_supe_actuel2[val_j-i]= '\0';
            break; // on s'arrête au premier espace
        }
        move_supe_actuel1[i] = a->move[i]; // on copie chaque caractère
    }
    //printf("\nJ'affiche le move1 de ennemy : %s\n", move_supe_actuel1);
    //printf("J'affiche le move2 de ennemy : %s\n", move_supe_actuel2);
    double test1 = strcmp(move_supe_actuel1, move1_);
    double test2 = strcmp(move_supe_actuel2, move1_);
    //printf("j'affiche le resultat de la comparaison : %f et %f\n", test1, test2);
    int resultatComparaison = strcmp(move_supe_actuel1, move1_) == 0;
    //printf("j'affiche le resultat de la comparaison '==' : %d\n", resultatComparaison);
    double db1 = 3.0;
    double db2 = 2.0;
    int a1, b;
    if (rand() % 2 == 0) {
        a1 = 1;
        b = 0;
    } else {
        a1 = 0;
        b = 1;
    }
    //printf("J'affiche le nb aleatoire a1 : %d et b : %d\n", a1, b);

    if ((strcmp(move_supe_actuel1, move1_) == 0) || (strcmp(move_supe_actuel2, move1_) == 0)) { // Attention! En C, pour vérifier qu'une condition a bien été verifier : si la condition est respecter, ca renvoie '1' et si ce n'est pas respecter, sa renvoie '0'
        //printf("je rentre dans scratch\n");
        if (a1==1){
            attackmove(db1, a, d);
        }
    }
    if ((strcmp(move_supe_actuel1, move2_) == 0) || (strcmp(move_supe_actuel2, move2_) == 0)) {
        //printf("ou je rentre dans grawl\n");
        //printf("J'affiche les conditions, la 1er : %d et la 2eme : %d\n", strcmp(move_supe_actuel1, move2_) == 1, strcmp(move_supe_actuel2, move2_) == 1);
        //printf("j'affiche 'move_supe_actuel1' : %s et 'move_2' : %s\n", move_supe_actuel1, move2_);
        //printf("ce que renvoie le 'strcmp' : %f\n", strcmp(move_supe_actuel1, move2_));
        //printf("ce que renvoie le 'strcmp' qui marche : %f\n", strcmp(move_supe_actuel1, move3_));
        //printf("j'affiche move1Supe : %s, move2Supe : %s et j'affiche move2 : %s\n", move_supe_actuel1, move_supe_actuel2, move2_);
        if (b==1){
            a->atk += 1;
        printf("This gives one attack (ennemy)!\n");
        }
    }
    if ((strcmp(move_supe_actuel1, move3_) == 0) || (strcmp(move_supe_actuel2, move3_) == 0)) {
        //printf("je rentre dans Pound\n");
        if (a1==1){
            attackmove(db2, a, d);
        }
    }
    if ((strcmp(move_supe_actuel1, move4_) == 0) || (strcmp(move_supe_actuel2, move4_) == 0)) { // Oublie pas quand tu utilises 'strcmp()' si c'est égal il renvoie = 0
        //printf("Ou je rentre dans Foliage\n");
        if (b==1){
            a->evasion += 1;
            printf("This gives one evasion (ennemy)!\n");
        }
    }
    if ((strcmp(move_supe_actuel1, move5_) == 0) || (strcmp(move_supe_actuel2, move5_) == 0)) {
        if (b==1){
            a->def += 1;
            printf("This gives one def (ennemy)!\n");
        }
    }
}


int arrondiAleatoire(double damage) {
    int arrondi;

    int arrondiAleatoire(double x) {
    double entier = floor(x);        // partie entière
    double decimal = x - entier;     // partie décimale

    // ✅ Si le nombre est déjà entier → on ne touche à rien
    if (decimal == 0.0) {
        return (int)(x);
    }

    // Sinon, on arrondit aléatoirement
    if (rand() % 2 == 0)
        return (int)(floor(x));  // vers le bas
    else
        return (int)(ceil(x));   // vers le haut
    }
    arrondi = arrondiAleatoire(damage);
    //printf("Avant arrondi : %f et apres arrondi : %d\n", damage, arrondi);
    return arrondi;

}

void attackmove(double moveAttack, struct supemon *a, struct supemon *d) { // Je donne en para des var de type 'supemon' et je pointe vers la structure que je donne lorsque j'appel la fonction (style : attackmove(move(int), supausaur(supemon), supirttle(supemon)) et bah comme lorsque j'ai definis la fonction je l'ai écrite : 'attackmove(int moveAttack, supemon *a, supemon *d)', avec des '*', il prend le pointeur de ce var (et en plus tu a donne le type de var avant quand t'a definis la var (dans la fonction))
    double damage = ((double)(a->atk) * moveAttack) / (double)(d->def); // Il ne faut pas oublier le '()' autour du type ne lequel tu veux le changer!
    //printf("Valeur de damage : %f\n", damage);
    int damage_arrondi = arrondiAleatoire(damage); // Ici le calcul pour le damage infligé est arrondi grace à l'appel de la fonction 'arrondiAleatoire
    //printf("Valeur de damage-arrondi: %fd\n", damage_arrondi);
    double var_temp1 = a->accuracy;
    double var_temp2 = d->evasion;
    accuracy_tester(var_temp1, var_temp2, a, d, damage_arrondi);
}

void accuracy_tester(double accu, double evas, struct supemon *a, struct supemon *d, int damage_arrondi) {
    double proba_evas = accu / (accu+evas) + 0.1;
    double tirage = (double)rand() / RAND_MAX;
    if (tirage < proba_evas) {
        d->hp -= damage_arrondi;
        printf("L'attaque a reussi!\nVoici le nouveau hp de %s : %d\n", d->name, d->hp);
    } else {
        printf("L'attaque a echouer...\nhp de %s : %d\n", d->name, d->hp);
    }

}

int capture_tester(struct player *b, struct supemon *d) {
    double proba_evas = (((double)(d->hp_max) - (double)(d->hp)) / (double)(d->hp_max)) - 0.5;
    //printf("Valeur de max_hp : %d et hp : %d\n", d->hp_max, d->hp);
    //printf("proba d'evasion : %f\n", proba_evas);
    double tirage = (double)rand() / RAND_MAX;
    //printf("proba tirage : %f\n", tirage);
    //printf("Il faut que tirage< proba evasion\n");
    int resultat;
    if (tirage < proba_evas) {
        int nbTemp = b->nb_supemon;

        struct supemon copie1;
        copie1 = *d; // je met le '*' car je veux copier le contenu et non le pointeur
        b->liste_sup[nbTemp] = copie1;
        //pri
        printf("%s", b->liste_sup[b->nb_supemon].name); // tu accede à la liste a partir du pointeur (donc tu utilises '->') puis dans la liste, comme tu a des struct et tu veux le .name par exemple tu utilises : '.'
        b->nb_supemon += 1;
        printf("La capture a reussi! Vous retrouverez ce supemon dans votre liste de supemon\n");
        printf("Match over\n");
        printf("Vous avez gagner\n");
        resultat = 1;
        return resultat;
    } else {
        printf("La capture a echouer...\n");
        resultat = 0;
        return resultat;
    }

}

int escape_tester(struct supemon *a, struct supemon *d) {
    double proba_evas = ((double)(a->speed)) / ((double)(a->speed) + (double)(d->speed));
    //printf("Valeur de max_hp : %d et hp : %d\n", d->hp_max, d->hp);
    //printf("proba d'evasion : %f\n", proba_evas);
    double tirage = (double)rand() / RAND_MAX;
    //printf("proba tirage : %f\n", tirage);
    //printf("Il faut que tirage< proba evasion\n");
    int resultat;
    if (tirage < proba_evas) {
        printf("L' évasion est une réusite!\nVous aller retourner à l'écran d'acceuil\n");
        return resultat;
    } else {
        printf("L' evaion a echouer...\n");
        resultat = 0;
        return resultat;
    }

}

struct supemon* changeSupemon(struct supemon *a, struct player *b) {
    int varTemp;
    printf("\nVoici la lite de vos Supemon : \n");
    for(int i = 0; i< b->nb_supemon; i++) {
        printf("%d - %s \n", i+1, b->liste_sup[i].name);
    }
    printf("Si vous voulez sortir choisisser 9\n");
    printf("Choisissez le supemon que vous voulez : ");
    scanf("%d", &varTemp);
    fflush(stdin);
    if (varTemp == 9) {
        return a;
    }
    b->sele_Supemon = varTemp-1;
    printf("Vous avez choisi %s!\n", b->liste_sup[varTemp-1].name);
    return &b->liste_sup[varTemp-1]; // je retourne le pointeur vers le nv supemon

}

void supemonCentre(struct player *b) {
    int varTemp;
    printf("\nVoici vous supemon : \n");
    for(int i = 0; i< b->nb_supemon; i++) {
        printf("%d - %s \n", i+1, b->liste_sup[i].name);
    }
    printf("Voulez vous les guerir?\n");
    printf("1 - oui\n");
    printf("2 - non\n");
    scanf("%d", &varTemp);
    fflush(stdin);
    if (varTemp == 1) {
        for(int i = 0; i< b->nb_supemon; i++) {
            b->liste_sup[i].hp = b->liste_sup[i].hp_max; // je remplace la valeur des hp des supe par leur valeur max
        }
        printf("Vos supemons ont bien ete guerie!\n");
    }
    printf("Vous sortez du supemon Centre...\n");
}

