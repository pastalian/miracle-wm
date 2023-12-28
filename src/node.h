#ifndef NODE_H
#define NODE_H

#include <mir/geometry/rectangle.h>
#include <vector>
#include <memory>
#include <miral/window.h>
#include <functional>

namespace geom = mir::geometry;

namespace miracle
{

enum class NodeState
{
    window ,
    lane
};

enum class NodeLayoutDirection
{
    horizontal,
    vertical
};

/// A node in the tree is either a single window or a lane.
class Node : public std::enable_shared_from_this<Node>
{
public:
    Node(geom::Rectangle, int gap_x, int gap_y);
    Node(geom::Rectangle, std::shared_ptr<Node> parent, miral::Window& window, int gap_x, int gap_y);

    /// The rectangle defined by the node can be retrieved dynamically
    /// by calculating the dimensions of the content in this node
    geom::Rectangle get_logical_area();

    /// Makes room for a new node on the lane.
    geom::Rectangle new_node_position(int index = -1);

    /// Append the node to the lane
    void add_window(miral::Window&);

    /// Recalculates the size of the nodes in the lane.
    void redistribute_size();

    void set_rectangle(geom::Rectangle target_rect);

    /// Walk the tree to find the lane that contains this window.
    std::shared_ptr<Node> find_node_for_window(miral::Window& window);

    /// Transform the window  in the list to a Node. Returns the
    /// new Node if the Window was found, otherwise null.
    std::shared_ptr<Node> window_to_node(miral::Window& window);

    bool move_node(int from, int to);

    void insert_node(std::shared_ptr<Node> node, int index);

    std::shared_ptr<Node> parent;

    bool is_root() { return parent == nullptr; }
    bool is_window() { return state == NodeState::window; }
    bool is_lane() { return state == NodeState::lane; }
    NodeLayoutDirection get_direction() { return direction; }
    miral::Window& get_window() { return window; }
    std::vector<std::shared_ptr<Node>>& get_sub_nodes() { return sub_nodes; }
    void set_direction(NodeLayoutDirection in_direction) { direction = in_direction; }

    int get_index_of_node(std::shared_ptr<Node>);
    int num_nodes();
    std::shared_ptr<Node> node_at(int i);

    /// Returns the window node from which this as created
    std::shared_ptr<Node> to_lane();
    std::shared_ptr<Node> find_nth_window_child(int i);

    void scale_area(double x_scale, double y_scale);
    void translate_by(int x, int y);

    static geom::Rectangle get_visible_area(geom::Rectangle const& logical_area, int gap_x, int gap_y);
    std::shared_ptr<Node> find_where(std::function<bool(std::shared_ptr<Node>)> func);

    int get_gap_x() { return gap_x; }
    int get_gap_y() { return gap_y; }

private:
    miral::Window window;
    std::vector<std::shared_ptr<Node>> sub_nodes;
    NodeState state;
    NodeLayoutDirection direction = NodeLayoutDirection::horizontal;

    /// The logical area includes the empty space filled by the gaps
    geom::Rectangle logical_area;
    int gap_x;
    int gap_y;

    int pending_index = -1;
};
}


#endif //MIRCOMPOSITOR_NODE_H
