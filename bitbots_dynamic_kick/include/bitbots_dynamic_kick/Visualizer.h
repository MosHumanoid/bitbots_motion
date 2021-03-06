//
// Created by ftsell on 6/19/19.
//

#ifndef BITBOTS_DYNAMIC_KICK_VISUALIZER_H
#define BITBOTS_DYNAMIC_KICK_VISUALIZER_H

#include <bitbots_msgs/KickGoal.h>
#include <string>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Path.h>
#include <bitbots_splines/SmoothSpline.hpp>
#include <bitbots_splines/SplineContainer.hpp>
#include <geometry_msgs/PoseStamped.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf/LinearMath/Vector3.h>

typedef bitbots_splines::SplineContainer<bitbots_splines::SmoothSpline> Trajectories;


namespace MarkerIDs {
    const int received_goal = 1;
    const int kick_windup_point = 2;
    const int kick_stabilizing_point = 3;
}

class VisualizationParams {
public:
    bool force_enable;
    int spline_smoothnes;
};


class Visualizer {
public:

    explicit Visualizer(std::string base_topic);

    void set_params(VisualizationParams params);

    void display_received_goal(const bitbots_msgs::KickGoalConstPtr &goal);

    void display_flying_splines(Trajectories &splines, std::string support_foot_frame);

    void display_windup_point(tf2::Vector3 kick_windup_point, std::string support_foot_frame);

    void display_stabilizing_point(tf::Vector3 kick_windup_point, std::string support_foot_frame);

private:
    ros::NodeHandle m_node_handle;
    ros::Publisher m_goal_publisher;
    ros::Publisher m_spline_publisher;
    ros::Publisher m_windup_publisher;
    ros::Publisher m_stabilizing_publisher;
    std::string m_base_topic;
    const std::string m_marker_ns = "bitbots_dynamic_kick";
    VisualizationParams m_params;
    bool m_param_debug_active;

    bool is_enabled();
};

#endif //BITBOTS_DYNAMIC_KICK_VISUALIZER_H
