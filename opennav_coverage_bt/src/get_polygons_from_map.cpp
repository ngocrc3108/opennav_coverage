// Copyright (c) 2024 Marc Morcos
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <memory>
#include <limits>

#include "opennav_coverage_bt/get_polygons_from_map.hpp"

namespace nav2_behavior_tree
{

GetPolygonsFromMap::GetPolygonsFromMap(
  const std::string & name,
  const BT::NodeConfiguration & conf)
: BT::ActionNodeBase(name, conf)
{
  auto convertNode = std::make_shared<rclcpp::Node>("gridmap_to_polygon");

  gridMapConverter_ = std::make_shared<GridMapToPolygonConverter>(convertNode);

  converter_thread_ = std::make_unique<std::thread>(
    [convertNode]() {
      rclcpp::spin(convertNode->get_node_base_interface());
    });
}

inline BT::NodeStatus GetPolygonsFromMap::tick()
{
  setStatus(BT::NodeStatus::RUNNING);

  setOutput("polygons", gridMapConverter_->getPolygons());

  return BT::NodeStatus::SUCCESS;
}

}  // namespace nav2_behavior_tree

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<nav2_behavior_tree::GetPolygonsFromMap>("GetPolygonsFromMap");
}
