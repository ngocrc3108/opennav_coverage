// Copyright (c) 2023 Open Navigation LLC
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

#include <memory>
#include <string>

#include "opennav_coverage_bt/convert_grid_map_to_polygons.hpp"

namespace opennav_coverage_bt
{

ConvertGridMapToPolygonsAction::ConvertGridMapToPolygonsAction(
  const std::string & xml_tag_name,
  const std::string & action_name,
  const BT::NodeConfiguration & conf)
: BtActionNode<Action>(xml_tag_name, action_name, conf)
{
}

void ConvertGridMapToPolygonsAction::on_tick()
{
}

BT::NodeStatus ConvertGridMapToPolygonsAction::on_success()
{
  setOutput("polygons", result_.result->polygons);
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus ConvertGridMapToPolygonsAction::on_aborted()
{
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus ConvertGridMapToPolygonsAction::on_cancelled()
{
  return BT::NodeStatus::SUCCESS;
}

void ConvertGridMapToPolygonsAction::halt()
{
  BtActionNode::halt();
}

}  // namespace opennav_coverage_bt

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  BT::NodeBuilder builder =
    [](const std::string & name, const BT::NodeConfiguration & config)
    {
      return std::make_unique<opennav_coverage_bt::ConvertGridMapToPolygonsAction>(
        name, "convert_grid_map_to_polygons", config);
    };

  factory.registerBuilder<opennav_coverage_bt::ConvertGridMapToPolygonsAction>(
    "ConvertGridMapToPolygons", builder);
}
