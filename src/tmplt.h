#ifndef TMPLT_TMPLT_H
#define TMPLT_TMPLT_H
#include "inja.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <set>

namespace tmplt {
constexpr int VERSION_MAJOR = 0;
constexpr int VERSION_MINOR = 1;
constexpr int VERSION_PATCH = 0;

inline void die(const std::string &msg) {
  std::cerr << "\x1b[31m" << msg << "\x1b[0m" << std::endl;
  exit(1);
}

inline std::string version() {
  std::ostringstream oss;
  oss << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;
  return oss.str();
}

class VariableVisitor : public inja::NodeVisitor {
private:
  std::set<std::string> variables_;

  void visit(const inja::BlockNode &node) {
    for (const auto &n : node.nodes) {
      n->accept(*this);
    }
  }
  void visit(const inja::TextNode &) {}
  void visit(const inja::ExpressionNode &) {}
  void visit(const inja::LiteralNode &) {}
  void visit(const inja::DataNode &n) { variables_.insert(n.name); }

  void visit(const inja::FunctionNode &node) {
    for (const auto &n : node.arguments) {
      n->accept(*this);
    }
  }

  void visit(const inja::ExpressionListNode &node) { node.root->accept(*this); }

  void visit(const inja::StatementNode &) {}
  void visit(const inja::ForStatementNode &) {}

  void visit(const inja::ForArrayStatementNode &node) {
    node.condition.accept(*this);
    node.body.accept(*this);
  }

  void visit(const inja::ForObjectStatementNode &node) {
    node.condition.accept(*this);
    node.body.accept(*this);
  }

  void visit(const inja::IfStatementNode &node) {
    node.condition.accept(*this);
    node.true_statement.accept(*this);
    node.false_statement.accept(*this);
  }

  void visit(const inja::IncludeStatementNode &) {}

  void visit(const inja::ExtendsStatementNode &) {}

  void visit(const inja::BlockStatementNode &node) { node.block.accept(*this); }

  void visit(const inja::SetStatementNode &) {}

public:
  const decltype(variables_) &variables() const { return variables_; }
};
} // namespace tmplt

#endif
