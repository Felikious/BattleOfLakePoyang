#include "Ship.h"

#include "Defined.h"

#include "Circle.h"
#include "TwoFloats.h"
#include "Level.h"
#include "GameState.h"
#include <vector>
#include <cmath>

class GameObject;

Ship::Ship() {}

Ship::Ship(TwoFloats pos, TwoFloats size , std::vector <std::string*> fn, float v, float bullet_timer, float bv, bool p_side)
    :m_pos_x(pos.x), m_pos_y(pos.y), m_width(size.x), m_height(size.y), m_velocity(v), m_fire_timer(bullet_timer), m_bullet_velocity(bv),m_player_side(p_side)
{
    for (std::string* ptr : m_filename) {
        delete ptr; // Free the memory for each string
    }
    m_filename = fn;
}

Ship::~Ship()
{
 //   for (auto p_gob : myCollisionCircles)
 //       if (p_gob) delete p_gob;
}

void Ship::updateCC()
{
    CC1.changeLoc(m_pos_x + cos(m_rotation * 3.141592 / 180.0f), m_pos_y + sin(m_rotation * 3.141592 / 180.0f));
    CC2.changeLoc(m_pos_x, m_pos_y);
    CC3.changeLoc(m_pos_x - cos(m_rotation * 3.141592 / 180.0f), m_pos_y - sin(m_rotation * 3.141592 / 180.0f));
}

void Ship::move(int direction, float dt)
{
    if (!isActive())
        return;

    float m_radiants = m_rotation * 3.14159 / 180;
    float delta_time = dt / 1000.0f;

    if (direction == 1)
    {
        m_pos_x = m_pos_x + cos(m_radiants) * delta_time * m_velocity;
        m_pos_y = m_pos_y - sin(m_radiants) * delta_time * m_velocity;
    }
    if (direction == 0)
    {
        m_pos_x = m_pos_x - cos(m_radiants) * delta_time * m_velocity;
        m_pos_y = m_pos_y + sin(m_radiants) * delta_time * m_velocity;
    }
    NearMe.changeLoc(m_pos_x, m_pos_y);
}

void Ship::rotate(int direction, float dt, float rot_v)
{

    if (!isActive())
        return;

    float m_radiants = m_rotation * 3.14159 / 180;
    float delta_time = dt / 1000.0f;

    if (direction == 1)
    {
        m_rotation = m_rotation + delta_time * rot_v;
        m_rotation = fmod(m_rotation + 360.0f, 360.0f);
    }

    if (direction == 0)
    {
        m_rotation = m_rotation - delta_time * rot_v;
        m_rotation = fmod(m_rotation + 360.0f, 360.0f);
    }
    updateCC();
    
}

bool Ship::isColliding(Ship& ship)
{
    for (auto mycircle : myCollisionCircles) {
        for (auto theircircle : ship.myCollisionCircles) {
            if (mycircle->isOverlapping(theircircle)) {
                return true;
            }
        }
    }
    return false;
}

bool Ship::isColliding(TwoFloats& pos)
{
    for (auto mycircle : myCollisionCircles) {
        
        if (mycircle->isOverlapping(&pos)) {
            return true;
        }
    }
    return false;
}

void Ship::isCollidingFixPos(Ship& ship)
{        
    for (auto mycircle : myCollisionCircles) {
        for (auto theircircle : ship.myCollisionCircles) {
            if (mycircle->isOverlapping(theircircle)) {
                correct_Ship_position(*mycircle, *theircircle);
            }
        }
    }
    
}

void Ship::isCollidingFixPos(TwoFloats& max, TwoFloats& min)
{
    for (auto circle : myCollisionCircles) {
        if (circle->isInsideBox(max,min))
        {
            TwoFloats correction = circle->corr_Poss(max,min);
            m_pos_x = m_pos_x + correction.x;
            m_pos_y = m_pos_y + correction.y;
        }    
    }
}

bool Ship::isNear(Circle& circle)
{
    if (NearMe.isOverlapping(&circle)) {
        return true;
    }
    return false;
}

bool Ship::isNear(TwoFloats& point)
{
    if (NearMe.isOverlapping(&point)) {
        return true;
    }
    return false;
}

bool Ship::isNear(Ship& ship)
{
    if (NearMe.isOverlapping(&ship.NearMe)) {
        //std::cout << "Ship near Ship\n";
        return true;
    }
    return false;
}

void Ship::correct_Ship_position(Circle& myCircle,Circle& theirCircle)
{
    TwoFloats Correct_Position = myCircle.corr_Poss(&theirCircle);
    m_pos_x = Correct_Position.x + m_pos_x;
    m_pos_y = Correct_Position.y + m_pos_y;
    //std::cout << "Correction of X " << Correct_Position.x << "Correction of Y" << Correct_Position.y << "\n";
}

void Ship::init()
{
    m_brush.fill_opacity = 1.0f;
    SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f)
    m_brush.outline_opacity = 0.0f;
    m_brush.texture = GET_FULL_ASSET_PATH(*m_filename[0]);
    NearMe.setRadius(m_width / 2.0f);
    NearMe.changeLoc(m_pos_x, m_pos_y);
    CC1.setRadius(m_width * 3.0f / 16.0f);
    CC2.setRadius(m_width * 13.0f/ 64.0f);
    CC3.setRadius(m_width * 10.0f / 64.0f);


}

void Ship::draw()
{
    graphics::setOrientation(m_rotation+90);
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush);
    graphics::resetPose();
}

void Ship::update(float dt)
{
    if (!isActive())
        return;

    NearMe.changeLoc(m_pos_x, m_pos_y);
    updateCC();
    if (NearMe.isInsideBox(*max_coord, *min_coord))
        isCollidingFixPos(*max_coord, *min_coord);

        
}

void Ship::fire(float rotation) {
    if (!isActive())
        return;
    LevelFactory::getCurrentLevel()->createBullet(new TwoFloats(m_pos_x, m_pos_y), rotation, m_bullet_velocity, m_player_side);
}

void Ship::shipShot()
{
    m_HP = m_HP - 1;

    if (m_HP < ( m_full_HP/2)&&m_HP>0){
        m_brush.texture = GET_FULL_ASSET_PATH(*m_filename[1]);
    }
    if (m_HP == 0) {
        sinking();
    }
}

void Ship::sinking()
{
    m_brush.texture = GET_FULL_ASSET_PATH(*m_filename[2]);
    setActive(false);
}

