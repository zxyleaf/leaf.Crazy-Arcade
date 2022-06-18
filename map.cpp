#include "map.h"
#include <assert.h>
map::map()
{

}

int map::getmap(int i, int j)
{
    return MAP[i][j];
}

int map::getmaptool(int i, int j)
{
    return MAPTool[i][j];
}

void map::Updatemap(int i, int j, int id)
{
    MAP[i][j] = id;
}
