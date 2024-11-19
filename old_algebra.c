
//prototypes
int **copiaMatriceStaticaInDinamica(int *pointerTo00, size_t numRighe, size_t numColonne);
int **copiaMatriceDinamica(int **matrice, size_t numRighe, size_t numColonne);
int *creaVettoreRiga(size_t dimensione);
int **creaMatrice(size_t numRighe, size_t numColonne);
int *copiaVettoreRiga(int riga[], size_t numColonne);

//eliminazione di non gauss.
void cancellaVettoreRiga(int *riga);
void cancellaMatrice(int **matrice, size_t numRighe);

//operazioni
int **MatriceTrasposta(int **matrice, size_t numRighe, size_t numColonne);


int *creaVettoreRiga(size_t dimensione)
{   int *ret = calloc(dimensione,  sizeof(int));
    if(ret == NULL)
    {   puts("Errore di allocazione della memoria in creaVettoreRiga");
    }
    return ret;
}

int **creaMatrice(size_t numRighe, size_t numColonne)
{   int **ret = calloc(numRighe,  sizeof(int*));
    if(ret == NULL)
    {   puts("Errore di allocazione della memoria in creaMatrice");
        return ret;
    }
    for(size_t i = 0; i < numRighe; i++)
    {   ret[i] = creaVettoreRiga(numColonne);
    }
    return ret;
}

int *copiaVettoreRiga(int riga[], size_t numColonne)
{   int *ret = creaVettoreRiga(numColonne);
    for(int i = 0; i < numColonne; i++)
    {   ret[i] = riga[i];
    }
    return ret;
}

int **copiaMatriceStaticaInDinamica(int *pointerTo00, size_t numRighe, size_t numColonne)
{   int **ret = creaMatrice(numRighe, numColonne);
    int offset = 0;
    for(size_t i = 0; i < numRighe; i++)
    {   for(size_t j = 0; j < numColonne; j++)
        {   ret[i][j] = pointerTo00[offset];
            offset++;
        }
    }
    return ret;   
}

int **copiaMatriceDinamica(int **matrice, size_t numRighe, size_t numColonne)
{
    int **ret = creaMatrice(numRighe, numColonne);
    for(size_t i = 0; i < numRighe; i++)
    {   for(size_t j = 0; j < numColonne; j++)
        {   ret[i][j] = matrice[i][j];
        }
    }
    return ret;
}

//-------------SVUOTA MEMORIA DINAMICA---------------------
void cancellaVettoreRiga(int *riga)
{   free(riga);
}

void cancellaMatrice(int **matrice, size_t numRighe)
{   for(size_t i = 0; i < numRighe; i++)
    {   cancellaVettoreRiga(matrice[i]);
    }
}
//---------------Operazioni--------------------
  
  
int **MatriceTrasposta(int **matrice, size_t numRighe, size_t numColonne)
{   int **ret = creaMatrice(numColonne, numRighe);
    for(size_t i = 0; i < numColonne; i++)
    {   for(size_t j = 0; j < numRighe; j++)
        {   ret[i][j] = matrice[j][i];
        }
    }
    return ret;
}
