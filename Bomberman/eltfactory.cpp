#include "eltfactory.h"
#include "eltfixedbrick.h"
#include "elttempbrick.h"
#include "eltplayer.h"
#include "eltbomb.h"
#include "eltbackground.h"

/* Element Graphic factory constructor.
Register the types of elements to be created by the factory.
*/
EltFactory::EltFactory()
{
    Register('I', &EltFixedBrick::Create); // Indestructible
    Register('D', &EltTempBrick::Create); // Destructible
    Register('P', &EltPlayer::Create); // Personnage
    Register('T', &EltBomb::Create); // Bomb = TNT
    Register('B', &EltBackground::Create); // Background
}

void EltFactory::Register(char brickCode, CreateElementFn pfnCreate)
{
    m_FactoryMap[brickCode] = pfnCreate;
}

EltBase *EltFactory::CreateElement(char brickCode, int ligne, int colonne)
{
    FactoryMap::iterator it = m_FactoryMap.find(brickCode);
    if( it != m_FactoryMap.end() )
    {
        EltBase *tmp = it->second();
        tmp->setLigne(ligne);
        tmp->setColonne(colonne);
        return tmp;
    }
    return 0;
}
