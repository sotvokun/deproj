#ifndef TMPLT_VARIABLE_VISITOR_H
#define TMPLT_VARIABLE_VISITOR_H
#include "inja.hpp"
#include <set>

namespace tmplt {
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
