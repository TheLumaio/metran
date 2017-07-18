#include "engine.h"

Gamestate::Gamestate(Engine* e)
{
    m_engine = e;
    m_resource = e->m_resource;
    m_renderer = e->m_renderer;
}
