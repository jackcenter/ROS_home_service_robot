#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/Odometry.h>

geometry_msgs::Pose current_pose;
bool goal_1 = false;
bool goal_2 = false;

void odom_update(const geometry_msgs::PoseWithCovarianceStamped& odom_msg)
{
  ROS_INFO("Subscribed to robot pose");
  /*current_x = odom_msg.pose.pose.x;
  current_y = odom_msg.pose.pose.y;
  current_w = odom_msg.pose.pose.w;*/
  current_pose = odom_msg.pose.pose;
  //current_pos = current_pose.position.x;
}

bool check_if_at_goal(float x, float y, float w)
{
  float x_c = current_pose.position.x;
  float y_c = current_pose.position.y;
  float w_c = current_pose.orientation.w;

  if (abs(x_c - x) < 0.1 && abs(y_c - y) < 0.1 && abs(w_c - w < 0.1))
  {
    ROS_INFO("Found a goal");
    return true;
  }

  else
    return false;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(10);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  ros::Subscriber sub = n.subscribe("amcl_pose", 3, odom_update);

  float x_1 = 5.0;
  float y_1 = -2.0;
  float w_1 = 1;

  float x_2 = 3;
  float y_2 = -4;
  float w_2 = 1;
  
  uint32_t shape = visualization_msgs::Marker::CUBE;
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.id = 0;
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.x = x_1;
  marker.pose.position.y = y_1;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  marker.scale.x = .2;
  marker.scale.y = .2;
  marker.scale.z = .2;
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();

  while(ros::ok())
 {

  marker_pub.publish(marker);


  // check if robot reached a goal (1 or 2)
  if (goal_1 == false){
    goal_1 = check_if_at_goal(x_1, y_1, w_1);
    if (goal_1 == true){
      // robot reached the pickup site
      marker.action = visualization_msgs::Marker::DELETE;
    }
  }

  else if (goal_2 == false){
    goal_2 = check_if_at_goal(x_2, y_2, w_2);
    if (goal_2 == true){
    // robot reached the dropoff site
      marker.pose.position.x = x_2;
      marker.pose.position.y = y_2;
      marker.action = visualization_msgs::Marker::ADD;
    }
  }

  ros::spinOnce();
  r.sleep();
  

/*  if (current_pose.position.x > 1.0 && goal == false){
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    goal == true;
  }
*/
  
  }


/* while (ros::ok())
  {
    sleep(10); //wait for everything to load
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 3;
    marker.pose.position.y = -4;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = .2;
    marker.scale.y = .2;
    marker.scale.z = .2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
/*    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }


    marker_pub.publish(marker);
    sleep(5);
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    sleep(5);
    marker.pose.position.x = 1;
    marker.pose.position.y = -2;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);


    // Cycle between different shapes
/*
  switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }

    r.sleep();
  }
*/
}
