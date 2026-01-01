#pragma once

#include "globals.h"

class QGraphicsScene;

// 构建语法树的图形场景，用于在 QGraphicsView 中显示
QGraphicsScene* buildSyntaxScene(TreeNode* root);