/**
Copyright (C) 2024  Matthew Kosarek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef MIRACLEWM_WORKSPACE_CONTENT_H
#define MIRACLEWM_WORKSPACE_CONTENT_H

#include <memory>
#include <miral/minimal_window_manager.h>
#include <miral/window_manager_tools.h>
#include <glm/glm.hpp>

namespace miracle
{
class OutputContent;
class MiracleConfig;
class TilingWindowTree;
class WindowMetadata;
class TilingInterface;

class WorkspaceContent
{
public:
    WorkspaceContent(
        OutputContent* output,
        miral::WindowManagerTools const& tools,
        int workspace,
        std::shared_ptr<MiracleConfig> const& config,
        TilingInterface& node_interface);

    [[nodiscard]] int get_workspace() const;
    [[nodiscard]] std::shared_ptr<TilingWindowTree> get_tree() const;
    void show(std::vector<std::shared_ptr<WindowMetadata>> const&);
    std::vector<std::shared_ptr<WindowMetadata>> hide();
    void for_each_window(std::function<void(std::shared_ptr<WindowMetadata>)> const&);

    bool has_floating_window(miral::Window const&);
    void add_floating_window(miral::Window const&);
    void remove_floating_window(miral::Window const&);
    std::vector<miral::Window> const& get_floating_windows() const { return floating_windows; }
    glm::mat4 get_transform() const { return transform; }
    void set_transform(glm::mat4 const& in) { transform = in; }
    OutputContent* get_output() const { return output; }

private:
    OutputContent* output;
    miral::WindowManagerTools tools;
    std::shared_ptr<TilingWindowTree> tree;
    int workspace;
    std::vector<miral::Window> floating_windows;
    glm::mat4 transform = glm::mat4(1.f);
};

} // miracle

#endif // MIRACLEWM_WORKSPACE_CONTENT_H
