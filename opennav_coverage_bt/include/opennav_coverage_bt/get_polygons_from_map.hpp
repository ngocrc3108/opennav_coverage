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

#ifndef NAV2_BEHAVIOR_TREE__PLUGINS__ACTION__GET_POLYGONS_FROM_MAP_HPP_
#define NAV2_BEHAVIOR_TREE__PLUGINS__ACTION__GET_POLYGONS_FROM_MAP_HPP_

#include <vector>
#include <memory>
#include <string>

#include "nav2_util/geometry_utils.hpp"
#include "nav2_util/robot_utils.hpp"
#include "behaviortree_cpp_v3/action_node.h"
#include <geometry_msgs/msg/polygon.hpp>
#include <gridmap_to_polygon/gridmap_to_polygon.h>

namespace nav2_behavior_tree
{

class GetPolygonsFromMap : public BT::ActionNodeBase
{
public:
  GetPolygonsFromMap(
    const std::string & xml_tag_name,
    const BT::NodeConfiguration & conf);


  static BT::PortsList providedPorts()
  {
    return {
      BT::OutputPort<std::vector<geometry_msgs::msg::Polygon>>("polygons", "output polygons converted from map"),
    };
  }

private:
  void halt() override {}
  BT::NodeStatus tick() override;

  std::unique_ptr<std::thread> converter_thread_;
  std::shared_ptr<GridMapToPolygonConverter> gridMapConverter_;
};

}  // namespace nav2_behavior_tree

#endif  // NAV2_BEHAVIOR_TREE__PLUGINS__ACTION__GET_POLYGONS_FROM_MAP_HPP_
