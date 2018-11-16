// *****************************************************************************
//
// Copyright (c) 2018, Eurecat
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Eurecat nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *****************************************************************************

#ifndef MAPVIZ_PLUGINS_GRID_PLUGIN_H_
#define MAPVIZ_PLUGINS_GRID_PLUGIN_H_

// C++ standard libraries
#include <string>
#include <list>

#include <mapviz/mapviz_plugin.h>

// QT libraries
#include <QGLWidget>
#include <QObject>
#include <QWidget>
#include <QTimer>

// ROS libraries
#include <ros/ros.h>
#include <tf/transform_datatypes.h>

#include <mapviz/map_canvas.h>
#include <nav_msgs/OccupancyGrid.h>
#include <map_msgs/OccupancyGridUpdate.h>

// QT autogenerated files
#include "ui_occupancy_grid_config.h"

namespace mapviz_plugins
{
  class OccupancyGridPlugin : public mapviz::MapvizPlugin
  {
    Q_OBJECT

    typedef std::array<uchar, 256*4> Palette;

  public:
    OccupancyGridPlugin();
    virtual ~OccupancyGridPlugin();

    bool Initialize(QGLWidget* canvas);
    void Shutdown();

    void Draw(double x, double y, double scale);

    void Transform();

    void LoadConfig(const YAML::Node& node, const std::string& path);
    void SaveConfig(YAML::Emitter& emitter, const std::string& path);

    QWidget* GetConfigWidget(QWidget* parent);

  protected:
    void PrintError(const std::string& message);
    void PrintInfo(const std::string& message);
    void PrintWarning(const std::string& message);

  protected Q_SLOTS:

    void SelectTopicGrid();
    void TopicGridEdited();
    void upgradeCheckBoxToggled(bool);
    void colorSchemeUpdated(const QString &);

    void DrawIcon();

    void FrameChanged(std::string);

  private:
    Ui::occupancy_grid_config ui_;
    QWidget* config_widget_;

    nav_msgs::OccupancyGridConstPtr grid_;

    ros::Subscriber grid_sub_;
    ros::Subscriber update_sub_;

    bool transformed_;
    swri_transform_util::Transform transform_;

    GLuint texture_id_;
    
    QPointF map_origin_;
    float texture_x_, texture_y_;
    std::vector<uchar> raw_buffer_;
    std::vector<uchar> color_buffer_;
    int32_t texture_size_;

    Palette map_palette_;
    Palette costmap_palette_;

    void Callback(const nav_msgs::OccupancyGridConstPtr& msg);
    void CallbackUpdate(const map_msgs::OccupancyGridUpdateConstPtr& msg);
    void updateTexture();

  };
}

#endif  // MAPVIZ_PLUGINS_GRID_PLUGIN_H_