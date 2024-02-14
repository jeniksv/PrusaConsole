#include "command_tree.hpp"

command_tree::command_tree()
    : _root()
{
}

command_tree::command_tree(std::shared_ptr<command> _root)
    : _root(_root)
{
}

std::vector<std::string> command_tree::get_complete_options(const std::string& path_tree)
{
    std::vector<std::string> options;

    auto [node, next_prefix] = get_parsed_tree_path(path_tree);

    return node->is_leaf()
        ? get_path_options(next_prefix)
        : get_composite_command_options(std::dynamic_pointer_cast<composite_command>(node), next_prefix);
}

void command_tree::complete_command(std::string& current)
{
    auto [node, next_prefix] = get_parsed_tree_path(current);

    if (node->is_leaf()) {
        complete_path(current, next_prefix);
    } else {
        complete_composite_command(std::dynamic_pointer_cast<composite_command>(node), current, next_prefix);
    }
}

void command_tree::complete_composite_command(const std::shared_ptr<composite_command> node, std::string& current,
    const std::string& prefix)
{
    std::set<std::string> children_subset;

    for (const auto& child : node->get_children()) {
        if (child->starts_with(prefix)) {
            children_subset.insert(child->get_name());
        }
    }

    auto suffix = longest_common_prefix(children_subset);
    current.append(suffix.length() < prefix.length() ? "" : suffix.substr(prefix.length()));
    current.append(children_subset.contains(suffix) ? " " : "");
}

void command_tree::complete_path(std::string& current, const std::string& prefix)
{
    std::filesystem::path input_path(prefix);
    std::filesystem::path directory = input_path.parent_path();
    std::string partial_name = input_path.filename().string();

    if (directory.empty() || directory.string() == ".") {
        directory = std::filesystem::current_path();
    }

    if (!std::filesystem::is_directory(directory)) {
        return;
    }

    std::set<std::string> options;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::string entry_name = entry.path().filename().string();

        if (entry_name.at(0) == '.') {
            continue;
        }

        if (!std::equal(partial_name.begin(), partial_name.end(), entry_name.begin())) {
            continue;
        }

        options.insert(directory == std::filesystem::current_path() ? std::filesystem::relative(entry.path()).string()
                                                                    : entry.path().string());
    }

    auto suffix = longest_common_prefix(options);
    current.append(suffix.length() < prefix.length() ? "" : suffix.substr(prefix.length()));

    if (std::filesystem::is_directory(suffix) && prefix != suffix) {
        current.append("/");
    }
}

std::vector<std::string> command_tree::get_composite_command_options(const std::shared_ptr<composite_command> node, const std::string& prefix)
{
    std::vector<std::string> options;

    for (const auto& child : node->get_children()) {
        if (child->starts_with(prefix)) {
            options.push_back(child->get_name());
        }
    }

    return options;
}

std::vector<std::string> command_tree::get_path_options(const std::string& prefix)
{
    std::vector<std::string> options;

    std::string current_directory(std::filesystem::path(prefix).parent_path().string());
    std::string current_prefix(std::filesystem::path(prefix).filename().string());

    current_directory = current_directory.empty() ? "." : current_directory;

    if (!std::filesystem::is_directory(current_directory)) {
        return std::vector<std::string>();
    }

    for (const auto& entry : std::filesystem::directory_iterator(current_directory)) {
        std::string filename = entry.path().filename().string();

        if (filename.at(0) == '.') {
            continue;
        }

        if (!std::equal(current_prefix.begin(), current_prefix.end(), filename.begin())) {
            continue;
        }

        if (std::filesystem::is_directory(entry) || std::filesystem::is_regular_file(entry)) {
            options.push_back(filename);
        }
    }

    return options;
}

std::tuple<std::shared_ptr<command>, std::string> command_tree::get_parsed_tree_path(const std::string& tree_path)
{
    std::stringstream ss(tree_path);
    std::shared_ptr<command> node = _root;
    std::string next;

    while (ss >> next && !node->is_leaf()) {
        auto composite_node = std::dynamic_pointer_cast<composite_command>(node);

        auto begin = composite_node->get_children().begin();
        auto end = composite_node->get_children().end();
        auto child_iterator = std::find_if(begin, end, [&next](const auto& child) { return child->get_name() == next; });

        if (child_iterator != composite_node->get_children().end()) {
            node = *child_iterator;
        } else {
            break;
        }
    }

    return std::make_tuple(node, next == node->get_name() && !node->is_leaf() ? "" : next);
}

std::string command_tree::longest_common_prefix(const std::set<std::string>& commands)
{
    if (commands.empty()) {
        return "";
    }

    std::string first = *(commands.begin());
    std::string last = *(commands.rbegin());
    std::string result;

    for (size_t i = 0; i < std::min(first.length(), last.length()); ++i) {
        if (first[i] != last[i]) {
            break;
        }

        result += first[i];
    }

    return result;
}

command_result command_tree::execute_command(const std::string& c)
{
    std::stringstream ss(c);

    return _root->execute(ss);
}
