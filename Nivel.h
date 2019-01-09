#ifndef NIVEL_H
#define NIVEL_H

#include "Cholo.h"
#include "Principal.h"

class Nivel
{
private:
    char **itemsMap,**wallsMap;
    int totalCholos;
    int rows;
    int cols;
    Cholo **cholos;
    Principal *principal;
    bool **collectedItems;
    string file;
    bool cleared;
    SDL_Surface *backgroundSurface;
    int totalItems;
    static SDL_Surface** Surfaces;
    //SDL_Surface ***backgroundItemsSurface;

public:
    Nivel(string);
    virtual ~Nivel(){}
    void readMaps();
    static void initNivel();
    static void freeNivel();
    ///GET Y SET
    char** getItemsMap(){return this->itemsMap;}
    char** getWallsMap(){return this->wallsMap;}
    bool** getCollectedItems(){return this->collectedItems;}
    int getTotalCholos(){return this->totalCholos;}
    Cholo** getCholos(){return this->cholos;}
    int getCols(){return this->cols;}
    int getRows(){return this->rows;}
    int getTotalItems(){return this->totalItems;}
    SDL_Surface* getBackgroundSurface(){return this->backgroundSurface;}
    bool getCleared(){return this->cleared;}
    void setCols(int rows){this->rows = rows;}
    void setRows(int cols){this->cols=cols;}
    void setItemsMap(char** itemsMap){this->itemsMap=itemsMap;}
    void setCholos(Cholo** cholos){this->cholos=cholos;}
    void setCollectedItems(bool** collectedItems){this->collectedItems=collectedItems;}
    void setCleared(bool cleared){this->cleared=cleared;}
    void setTotalItems(int totalItems){this->totalItems=totalItems;}
    ///FIN GET Y SET
    void deleteItem(int row,int col);
    SDL_Surface* createBackgroundSurface();
    void createBackgroundItemsSurface();
    void setItemBool(int column, int row){this->collectedItems[column][row]=false;}
    void setItemInMap(int column, int row, char item){this->itemsMap[column][row]=item;}
    void checkAtItem(Character*);
    bool atCross(Character*);
};

#endif // NIVEL_H
