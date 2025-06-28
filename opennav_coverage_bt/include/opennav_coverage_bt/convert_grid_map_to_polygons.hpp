#ifndef OPENNAV_COVERAGE_BT__NAVIGATE_COMPLETE_COVERAGE_PATH_HPP_
#define OPENNAV_COVERAGE_BT__NAVIGATE_COMPLETE_COVERAGE_PATH_HPP_

#include <string>
#include <memory>
#include <vector>

#include <gridmap_to_polygon_msg/action/convert_gridmap_to_polygons.hpp>
#include "nav2_behavior_tree/bt_action_node.hpp"
#include "geometry_msgs/msg/polygon.hpp"
#include "opennav_coverage_bt/utils.hpp"

namespace opennav_coverage_bt
{

/**
 * @brief nav2_behavior_tree::BtActionNode class that wraps nav2_msgs::action::NavigateCompleteCoverage
 */
class ConvertGridMapToPolygonsAction
  : public nav2_behavior_tree::BtActionNode<
    gridmap_to_polygon_msg::action::ConvertGridmapToPolygons>
{
  using Action = gridmap_to_polygon_msg::action::ConvertGridmapToPolygons;
  using ActionResult = Action::Result;

public:
  /**
   * @brief A constructor for opennav_coverage_bt::ConvertGridMapToPolygonsAction
   * @param xml_tag_name Name for the XML tag for this node
   * @param action_name Action name this node creates a client for
   * @param conf BT node configuration
   */
  ConvertGridMapToPolygonsAction(
    const std::string & xml_tag_name,
    const std::string & action_name,
    const BT::NodeConfiguration & conf);

  /**
   * @brief Function to perform some user-defined operation on tick
   */
  void on_tick() override;

  /**
   * @brief Function to perform some user-defined operation upon successful completion of the action
   */
  BT::NodeStatus on_success() override;

  /**
   * @brief Function to perform some user-defined operation upon abortion of the action
   */
  BT::NodeStatus on_aborted() override;

  /**
   * @brief Function to perform some user-defined operation upon cancellation of the action
   */
  BT::NodeStatus on_cancelled() override;

  /**
   * \brief Override required by the a BT action. Cancel the action and set the path output
   */
  void halt() override;

  /**
   * @brief Creates list of BT ports
   * @return BT::PortsList Containing basic ports along with node-specific ports
   */
  static BT::PortsList providedPorts()
  {
    return providedBasicPorts(
      {
        BT::OutputPort<std::vector<geometry_msgs::msg::Polygon>>(
          "polygons", "Port-provided polygon, if not from file"),
      });
  }
};

}  // namespace opennav_coverage_bt

#endif // OPENNAV_COVERAGE_BT__NAVIGATE_COMPLETE_COVERAGE_PATH_HPP_