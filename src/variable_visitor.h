#ifndef DEPROJ_VARIABLE_VISITOR_H
#define DEPROJ_VARIABLE_VISITOR_H

#include <unordered_set>

#include "inja.hpp"

namespace deproj {

/**
 * VariableVisitor is a visitor that visits all variables in a ast tree.
 */
class VariableVisitor final : public inja::NodeVisitor {
public:
    using variable_name_type = std::string;

    inline void visit(const inja::BlockNode& node) override
    {
        for (const auto &n : node.nodes) {
            n->accept(*this);
        }
    }

    inline void visit(const inja::TextNode& node) override { }
    inline void visit(const inja::ExpressionNode& node) override { }
    inline void visit(const inja::LiteralNode& node) override { }

    inline void visit(const inja::DataNode& node) override
    {
        variables_.insert(node.name);
    }

    inline void visit(const inja::FunctionNode& node) override
    {
        for (const auto& n : node.arguments) {
            n->accept(*this);
        }
    }

    inline void visit(const inja::ExpressionListNode& node) override
    {
        node.root->accept(*this);
    }

    inline void visit(const inja::StatementNode& node) override { }

    inline void visit(const inja::ForStatementNode& node) override
    {
        node.condition.accept(*this);
        node.body.accept(*this);
    }

    inline void visit(const inja::ForArrayStatementNode& node) override
    {
        node.condition.accept(*this);
        node.body.accept(*this);
    }

    inline void visit(const inja::ForObjectStatementNode& node) override
    {
        node.condition.accept(*this);
        node.body.accept(*this);
    }

    inline void visit(const inja::IfStatementNode& node) override
    {
        node.condition.accept(*this);
        node.true_statement.accept(*this);
        node.false_statement.accept(*this);
    }

    inline void visit(const inja::IncludeStatementNode& node) override { }
    inline void visit(const inja::ExtendsStatementNode& node) override { }

    inline void visit(const inja::BlockStatementNode& node) override
    {
        node.block.accept(*this);
    }

    inline void visit(const inja::SetStatementNode& node) override {  }

    inline const auto &variables() const noexcept
    {
        return variables_;
    }

private:
    std::unordered_set<variable_name_type> variables_;

};

} // namespace deproj

#endif
