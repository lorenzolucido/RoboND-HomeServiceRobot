#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

// Note the goals are slightly different than in pick_objects since we rotated the map by 180 degrees
#define pickup_x -6.8   // -3.0
#define pickup_y -3.0   // 6.8
#define dropoff_x 8.4  // -5.4
#define dropoff_y -5.4 // -8.4

// Using a global variable for the state. Encapsulating it in a class would be a cleaner solution
std::string state ("INIT"); // INIT, GO_PICK_OBJECT, GO_DELIVER_OBJECT, DONE
visualization_msgs::Marker marker;
ros::Publisher marker_pub;
uint32_t shape = visualization_msgs::Marker::CUBE;

float euclidean_dist(float x1, float y1, float x2, float y2) {
  return sqrtf(pow(x2-x1, 2) + pow(y2-y1, 2));
}

bool close_to_ref(geometry_msgs::Pose pose, float ref_x, float ref_y, float min_dist = 0.35) {
  float dist = euclidean_dist(pose.position.x, pose.position.y, ref_x, ref_y);
  // ROS_INFO("DISTANCE from (%f, %f): %f (current: %f, %f)", ref_x, ref_y, dist, pose.position.x, pose.position.y);  
  return dist < min_dist;
}

bool close_to_pickup(geometry_msgs::Pose pose) {  
  return close_to_ref(pose, pickup_x, pickup_y); 
}

bool close_to_dropoff(geometry_msgs::Pose pose) {
  return close_to_ref(pose, dropoff_x, dropoff_y); 
}

void odom_callback(const nav_msgs::Odometry::ConstPtr &msg) {
  geometry_msgs::Pose current = msg->pose.pose;
  
  if(state == "INIT") {
    ROS_INFO("Initialize: order to pickup object");
    state = "GO_PICK_OBJECT";
    marker.action = visualization_msgs::Marker::ADD; 
     
    marker.pose.position.x = pickup_y;
    marker.pose.position.y = -pickup_x;
    
  }
  else if(close_to_pickup(current) && state == "GO_PICK_OBJECT") {
    ROS_INFO("Object picked up!");
    state = "GO_DELIVER_OBJECT";
    marker.action = visualization_msgs::Marker::DELETE;    
    
  }
  else if(close_to_dropoff(current) && state == "GO_DELIVER_OBJECT") {
    ROS_INFO("Object delivered!");
    state = "DONE";
    marker.pose.position.x = dropoff_y;
    marker.pose.position.y = -dropoff_x;
    marker.action = visualization_msgs::Marker::ADD;    
    
  };
    
  marker.header.stamp = ros::Time::now();  
  marker_pub.publish(marker);
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);       
  ros::Subscriber odom_sub = n.subscribe("/odom", 1, &odom_callback);

  while (!ros::ok())
  {
    ROS_INFO("Waiting for ROS");
  }
  
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
  marker.action = visualization_msgs::Marker::DELETE;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = 0.0;
  marker.pose.position.y = 0.0;
  marker.pose.position.z = 0.0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.4;
  marker.scale.y = 0.4;
  marker.scale.z = 0.4;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  // ROS_INFO("Preparing to send marker.");  
  // ros::Duration(1.0).sleep();
  marker_pub.publish(marker);
    
  ros::spin();
}
