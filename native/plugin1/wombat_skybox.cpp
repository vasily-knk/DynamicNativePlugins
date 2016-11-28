#include "stdafx.h"
#include "wombat_skybox.h"

#include "wombat/wombat.h"
#include "wombat/window.h"
#include "wombat/viewport.h"
#include "wombat/scene.h"
#include "wombat/render_context.h"
#include "wombat/database.h"
#include "wombat/scene_graph.h"
#include "wombat/base_nodes.h"
#include "wombat/industry_nodes.h"
#include "wombat/sfx_nodes.h"
#include "wombat/props.h"
#include "wombat/texture.h"

using namespace wombat;


struct wombat_skybox_impl
    : wombat_skybox
{
    wombat_skybox_impl()
//        : 
//        , viewport_(engine_ ? engine_->create_viewport() : nullptr)
//        , scene_(engine_ ? engine_->create_scene() : nullptr)
    {
        engine_ = create_wombat_engine();
        Verify(engine_);

        viewport_ = engine_->create_viewport();
        Verify(viewport_);
        
        viewport_->SetRect(rectangle_2i(point_2i(0, 0), point_2i(1024, 1024)));
        viewport_->set_enable_fbo(true);

        scene_ = engine_->create_scene();
        Verify(scene_);

        load_airport();
        
    }                          
    
    void update_camera_pos(camera_pos_t const& pos) override
    {
    }

    uint32_t get_texture_id() override
    {
        auto tex = viewport_->get_resolved_color();
        Verify(tex);
        return tex->glName();
    }

    void render() override
    {
        scene_->update(0.f);
        scene_->render(viewport_.get());

        auto tex = viewport_->get_resolved_color();
        int aaa = 5;
    }

private:
    void load_airport()
    {
        auto scenegraph = engine_->get_scenegraph();
        Verify(scenegraph);

        auto objects = scene_->get_objects();
        Verify(objects);

        auto ap = scenegraph->load("sheremetyevo/sheremetyevo.scg");
        Verify(ap);                                   
        objects->add(ap.get());        
    }

private:
    engine_ptr engine_;
    viewport_ptr viewport_;
    scene_ptr scene_;
    texture_ptr color_texture_;
};

unique_ptr<wombat_skybox> create_wombat_skybox()
{
    return std::make_unique<wombat_skybox_impl>();
}