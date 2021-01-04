#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 13
#define MIN 1

int main()
{
    int i=0;
    int Cards[13]; // Tableau représentant le nombre de card
    int Cards_P[19]; 	// historique card joueur
    int Cards_B[19];	// historique card banque
    int Victory_P=0;	// flag de Victoire Player
    int Victory_B=0;	// Flag de vitoire Bank
    int Total_P=0,Total_P2=0,Total_B=0,Total_B2=0;	//Total engrangé par le joueur
    int Comp_P=0,Comp_B=0; //Valeur de comparaison entre les deux, soit la plus haute valeur en dessous ou égal à 21
    int cpt_B=0,cpt_P=0;
    char c=' ';
    char c_card[]={'1','2','3','4','5','6','7','8','9','X','V','D','R'};
    //générateur nombre
    srand(time(NULL));

    //initialisation
    for(i=0;i<13;i++)
        Cards[i]=16;
    for(i=0;i<19;i++)
        Cards_B[i]=Cards_P[i]=0;

    do
    {
		printf("\nTour banque :");
		printf("\n*************");
		// Première Phase de jeux : tirage pour la banque
        for(i=0;i<2;i++)
        {
			do
			{
				Cards_B[i]=(rand() % (MAX - MIN + 1)) + MIN;
			}while(Cards[Cards_B[i]-1]==0);	//Verification du nombre restant d'une card spécifique
            Cards[Cards_B[i]-1]--;	//on décrémente le type de card qui vient de sortir (maximum 16)
            if(Cards_B[i]==11||Cards_B[i]==12||Cards_B[i]==13)
			{
				Total_B+=10;
				Total_B2+=10;
			}
			else
			{
				Total_B+=Cards_B[i]; //total si as vaut 1
				Total_B2+=Cards_B[i];
			}
			if(Cards_B[i]==1)
			{
				Total_B2+=10;
			}
        }

        //Attribution du meilleur des deux scores à la banque
		if(Total_B<=21)
		{
			Comp_B=Total_B;
			if(Total_B2<=21)
			{
				if(Comp_B<=Total_B2)
				{
					Comp_B=Total_B2;
				}
			}
		}

		//Afficher du résultat pour la banque
		printf("\nC1 : %c C2 : %c",c_card[Cards_B[0]-1],c_card[Cards_B[1]-1]);
		printf("\nB Total 1 : %d B Total 2 : %d",Total_B,Total_B2);
        if(Comp_B==21)
			Victory_B=1;

		//tirage du joueur
		for(i=0;i<2;i++)
		{
			do
			{
				Cards_P[i]=(rand() % (MAX - MIN + 1)) + MIN;
			}while(Cards[Cards_P[i]-1]==0);	//Verification du nombre restant d'une card spécifique
            Cards[Cards_P[i]-1]--;	//on décrémente le type de card qui vient de sortir (maximum 16)
			if(Cards_P[i]>=10)
			{
				Total_P+=10;
				Total_P2+=10;
			}
			else
			{
				Total_P+=Cards_P[i]; //total si as vaut 1
				Total_P2+=Cards_P[i];
			}
			if(Cards_P[i]==1)
			{
				Total_P2+=10;
			}
        }
		//Attribution du meilleur des deux scores au joueur
		if(Total_P<=21)
		{
			Comp_P=Total_P;
			if(Total_P2<=21)
			{
				if(Comp_P<=Total_P2)
				{
					Comp_P=Total_P2;
				}
			}
		}

        cpt_P=1;
		//tour du joueur
		printf("\nTour joueur :");
		printf("\n*************");
		do
		{
			printf("\nCartes joueur \n");
			for(i=0;i<cpt_P+1;i++)
			{
				//Afficher du résultat pour le joueur
				printf("C%d : %c ",(i+1),c_card[Cards_P[i]-1]);
            }
			printf("\n");
            printf("P total 1 : %d P total 2 : %d ",Total_P,Total_P2);

            if(Comp_P==21)
				Victory_P=1;
            printf("\nEncore ? : ");
			scanf("%c",&c);
            fflush(stdin);

            if(c=='o')
			{
				cpt_P++;
				do
				{
					Cards_P[cpt_P]=(rand() % (MAX - MIN + 1)) + MIN;;
				}while(Cards[Cards_P[cpt_P]-1]==0);	//Verification du nombre restant d'une card spécifique
                Cards[Cards_P[cpt_P]-1]--;	//on décrémente le type de card qui vient de sortir (maximum 16)
				if(Cards_P[cpt_P]>=10)
				{
					Total_P+=10;
					Total_P2+=10;
				}
				else
				{
					Total_P+=Cards_P[cpt_P]; //total si as vaut 1
					Total_P2+=Cards_P[cpt_P];
				}
				if(Cards_P[cpt_P]==1)
				{
					Total_P2+=10;
				}

				//Attribution du meilleur des deux scores au joueur
				Comp_P=Total_P2;
				if(Total_P<=21)
				{
					Comp_P=Total_P;
					if(Total_P2<=21)
					{
						if(Comp_P<=Total_P2)
						{
							Comp_P=Total_P2;
						}
					}
				}
				if(Comp_P>21)
				{
					Victory_B=1;
					printf("\nBOUM\n");
                    for(i=0;i<cpt_P+1;i++)
					{
						//Afficher du résultat pour le joueur
						printf("C%d : %c ",(i+1),c_card[Cards_P[i]-1]);
                    }
					printf("\n");
                    printf("P Total 1 : %d P Total 2 : %d",Total_P,Total_P2);
                }
            }
			//Condition de sortie en cas de victoire d'un des deux camps ou de décision du joueur
        }while((c=='o')&&(!Victory_P)&&(!Victory_B));

        cpt_B=1;
		printf("\nTour banque :");
		printf("\n*************");
		//Tour de la banque
		if(Comp_B>=Comp_P||Comp_P>21)
			Victory_B=1;
        else
        {
			do
			{
				cpt_B++;
				do
				{
					Cards_B[cpt_B]=(rand() % (MAX - MIN + 1)) + MIN;;
				}while(Cards[Cards_B[cpt_B]-1]==0);	//Verification du nombre restant d'une card spécifique
                Cards[Cards_B[cpt_B]-1]--;	//on décrémente le type de card qui vient de sortir (maximum 16)
				if(Cards_B[cpt_B]>=10)
				{
					Total_B+=10;
					Total_B2+=10;
				}
				else
				{
					Total_B+=Cards_B[cpt_B]; //total si as vaut 1
                    Total_B2+=Cards_B[cpt_B];
				}
				if(Cards_B[cpt_B]==1)
				{
					Total_B2+=10;
				}

				//Attribution du meilleur des deux scores au joueur
				Comp_B=Total_B;
				if(Total_B2<=21)
				{
					if(Comp_B<=Total_B2)
					{
						Comp_B=Total_B2;
					}
				}

				if((Comp_B==21||Comp_B>=Comp_P)&&(Comp_B<=21))
				{
					Victory_B=1;
				}
				if(Comp_B>21)
                {
                    Victory_P=1;
                }

                printf("\nCartes Banque :\n");
				for(i=0;i<cpt_B+1;i++)
				{
					//Afficher du résultat pour le joueur
					printf("C%d : %c ",(i+1),c_card[Cards_B[i]-1]);
				}
				printf("\n");
				printf("B total 1 : %d B total 2 : %d",Total_B,Total_B2);

            }while((!Victory_P)&&(!Victory_B));
        }

    }while((!Victory_P)&&(!Victory_B));

    if (Victory_B)
	{
		printf("\nVictoire de la Banque");
	}
	else
	{
		printf("\nVictoire du joueur");
	}

    return 0;
}
