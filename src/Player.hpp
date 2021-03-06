/**
 * @file        Player.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __Player__
#define __Player__

#include "Common.hpp"
#include "Objects.hpp"

namespace Mario
{
    /// Player class.
    struct Player : public Object
    {
        /**
         * Player constructor.
         * @param map Owner map.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Player(Map* map, size_t tile_x, size_t tile_y) :
            Object(OBJECT_PLAYER, map, tile_x, tile_y), keys_down(0) {}

        ~Player() {}

        /// @copydoc Object::Kill
        void Kill(Object* enemy);

        /// @copydoc Object::OnAnimate
        void OnAnimate(float dt);

        /// @copydoc Object::OnDraw
        size_t OnDraw();

        /**
         * Key down handler.
         * @param key Pressed key.
         */
        void OnKeyDown(int key);

        /**
         * Key up handler.
         * @param key Released key.
         */
        void OnKeyUp(int key);

        unsigned keys_down;     ///< Holds information about keys being pressed

        const float RUN_BOOST = 1.5f;   ///< X key run boost
    };
}

#endif
