#pragma once
#include <memory>

struct camera_pos_t
{
    
};

struct wombat_skybox
{
    virtual ~wombat_skybox() {};

    virtual void update_camera_pos(camera_pos_t const &pos) = 0;
    virtual uint32_t get_texture_id() = 0;

    virtual void render() = 0;

};

unique_ptr<wombat_skybox> create_wombat_skybox();