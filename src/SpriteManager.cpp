/**
 * @file        SpriteManager.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Map.hpp"
#include "SpriteManager.hpp"

using namespace Mario;

SpriteManager::~SpriteManager()
{
    for (SpriteInfoMap::iterator i = sprites.begin(); i != sprites.end(); ++i)
        delete i->second;

    for (PathToBitmapMap::iterator i = bitmaps.begin(); i != bitmaps.end(); ++i)
        DestroyBitmap(i->second);

    log_info("[Spr]\tSprite manager destroyed.");
}

void SpriteManager::Register()
{
    sprites[OBJECT_PLAYER]  = new SpriteInfo(ASSETS "mario.png", 30, 40, 15);
    sprites[OBJECT_GOOMBA]  = new SpriteInfo(ASSETS "goomba.png", 22, 26, 7);
    sprites[OBJECT_KOOPA]   = new SpriteInfo(ASSETS "koopa.png", 16, 28, 8);
    sprites[OBJECT_LAKITU]  = new SpriteInfo(ASSETS "enemies.png", 16, 32, 4);
    sprites[OBJECT_SPINY]   = new SpriteInfo(ASSETS "spiny.png", 16, 16, 4);
}

void SpriteManager::Load()
{
    for (SpriteInfoMap::iterator i = sprites.begin(); i != sprites.end(); ++i)
        if (!bitmaps[i->second->path])
            if (!(bitmaps[i->second->path] = LoadBitmap(i->second->path.c_str())))
                throw std::runtime_error(std::string("[Spr] Could not load sprite sheet ") + i->second->path);
}

void SpriteManager::Draw(Map* map)
{
    for (ObjectList::iterator obj = map->objs.begin(); obj != map->objs.end(); ++obj)
    {
        Object* o = *obj;
        SpriteInfo* info = sprites[o->type];

        if (!info)
        {
            DrawFilledRect(o->pos_x-TileSize/2, o->pos_y,
                o->pos_x + TileSize / 2, o->pos_y + TileSize, MakeCol(255, 255, 255));
            continue;
        }

        size_t tile = o->OnDraw();

        DrawScaledBitmap(bitmaps[info->path],
            tile % info->row_size * info->tile_width,
            tile / info->row_size * info->tile_height,
            info->tile_width, info->tile_height,
            o->pos_x-info->tile_width - map->offset,
            o->pos_y+info->tile_height*2,
            2*info->tile_width, 2*info->tile_height,
            0);
    }
}
