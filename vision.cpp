#include "vision.h"
#include "analyze.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <algorithm>

static const double NODE_W = 100.0;
static const double NODE_H = 30.0;
static const double H_GAP  = 30.0;
static const double V_GAP  = 60.0;

static bool hasChild(TreeNode* n) {
  if (!n) return false;
  for (int i = 0; i < MAXCHILDREN; ++i) if (n->child[i]) return true;
  return false;
}

// 计算单个节点（不含兄弟链）的宽度（以“叶子单元”为单位）
static int widthNode(TreeNode* n) {
  if (!n) return 0;
  int sum = 0;
  for (int i = 0; i < MAXCHILDREN; ++i) sum += widthNode(n->child[i]);
  if (sum == 0) return 1; // 叶子节点
  return sum;
}

// 计算兄弟链的总宽度（以“叶子单元”为单位）
static int widthList(TreeNode* n) {
  int total = 0; TreeNode* cur = n;
  while (cur) { total += widthNode(cur); cur = cur->sibling; }
  if (total == 0) return 1;
  return total;
}

// 在场景中绘制一个节点（包含其子树），并返回其中心 X 坐标
static double drawNode(TreeNode* n, double left, double y, QGraphicsScene* scene) {
  int units = widthNode(n);
  double unitW = NODE_W + H_GAP;
  double xCenter = left + units * unitW / 2.0;
  double x = xCenter - NODE_W / 2.0;

  // 矩形与文本
  auto rect = scene->addRect(x, y, NODE_W, NODE_H, QPen(Qt::black), QBrush(QColor(240, 240, 255)));
  auto text = scene->addText(getTreeNodeInfo(n));
  text->setDefaultTextColor(Qt::darkBlue);
  QFont f = text->font(); f.setPointSize(9); text->setFont(f);
  QRectF tr = text->boundingRect();
  text->setPos(x + (NODE_W - tr.width())/2.0, y + (NODE_H - tr.height())/2.0);

  // 子节点与连线（虚线）
  QPen edgePen(QColor(120,120,120)); edgePen.setStyle(Qt::DashLine);
  double childLeft = left;
  for (int i = 0; i < MAXCHILDREN; ++i) {
    TreeNode* c = n->child[i];
    if (!c) continue;
    int cw = widthNode(c);
    double cxCenter = childLeft + cw * unitW / 2.0;
    // 父（底部中心）到子（顶部中心）的连线
    scene->addLine(xCenter, y + NODE_H, cxCenter, y + NODE_H + V_GAP, edgePen);
    drawNode(c, childLeft, y + NODE_H + V_GAP, scene);
    childLeft += cw * unitW;
  }

  return xCenter;
}

// 绘制兄弟链（同一层的多个语句），不返回值
static void drawList(TreeNode* n, double left, double y, QGraphicsScene* scene) {
  double unitW = NODE_W + H_GAP;
  TreeNode* cur = n; double l = left;
  while (cur) {
    int w = widthNode(cur);
    drawNode(cur, l, y, scene);
    l += w * unitW;
    cur = cur->sibling;
  }
}

QGraphicsScene* buildSyntaxScene(TreeNode* root) {
  auto scene = new QGraphicsScene();
  if (!root) return scene;

  int totalUnits = widthList(root);
  double unitW = NODE_W + H_GAP;
  double totalWidth = std::max<double>(totalUnits * unitW + 40.0, 800.0);
  double xLeft = 20.0;
  double yTop  = 20.0;

  // 顶部“start”节点
  double center = xLeft + totalUnits * unitW / 2.0;
  double startX = center - NODE_W / 2.0;
  auto startRect = scene->addRect(startX, yTop, NODE_W, NODE_H, QPen(Qt::black), QBrush(QColor(230, 255, 230)));
  auto startText = scene->addText("start");
  QFont f = startText->font(); f.setPointSize(9); startText->setFont(f);
  QRectF sr = startText->boundingRect();
  startText->setPos(startX + (NODE_W - sr.width())/2.0, yTop + (NODE_H - sr.height())/2.0);

  // start 到每个顶层语句的连线
  QPen edgePen(QColor(120,120,120)); edgePen.setStyle(Qt::DashLine);
  TreeNode* cur = root; double l = xLeft;
  while (cur) {
    int w = widthNode(cur);
    double childCenter = l + w * unitW / 2.0;
    scene->addLine(center, yTop + NODE_H, childCenter, yTop + NODE_H + V_GAP, edgePen);
    l += w * unitW;
    cur = cur->sibling;
  }

  // 绘制顶层语句链
  drawList(root, xLeft, yTop + NODE_H + V_GAP, scene);

  // 设定场景范围
  scene->setSceneRect(0, 0, totalWidth, 1200.0);
  return scene;
}