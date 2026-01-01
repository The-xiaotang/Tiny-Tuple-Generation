#include "dialog.h"
#include "cgen.h"
#include "QDebug"
#include "QDir"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include "ui_dialog.h"
#include "vision.h"
#include <QPainter>
#include <QCoreApplication>
#include <QResizeEvent>
#include <QFontMetrics>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  // 错误信息区域最多显示 10 行，超出滚动
  ui->error->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  updateErrorMaxHeight();
  /*
  // 尝试加载背景图片（相对应用目录）
  QString appDir = QDir(QCoreApplication::applicationDirPath()).absolutePath();
  QStringList candidates{
      QDir(appDir).filePath("images/background.jpg"),
      QDir(appDir).filePath("D:/Users/asus/Desktop/background.jpg"),
      QStringLiteral(":/images/background.jpg")
  };
  for (const QString &p : candidates) {
    QPixmap pix(p);
    if (!pix.isNull()) { bgPix = pix; break; }
  }
  if (!bgPix.isNull()) {
    QPalette pal = palette();
    pal.setBrush(QPalette::Window, QBrush(bgPix.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
    setPalette(pal);
    setAutoFillBackground(true);
  }
  */
  // 图形视图交互设置
  ui->graphResult->setRenderHint(QPainter::Antialiasing, true);
  ui->graphResult->setDragMode(QGraphicsView::ScrollHandDrag);
  ui->graphResult->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  // Add Intermediate Code Tab
  QWidget *tabCode = new QWidget();
  QVBoxLayout *layoutCode = new QVBoxLayout(tabCode);
  codeView = new QTextEdit(tabCode);
  codeView->setReadOnly(true);
  layoutCode->addWidget(codeView);
  ui->tabWidget->addTab(tabCode, "中间代码");
}

Dialog::~Dialog() { delete ui; }

void Dialog::on_chooseFile_clicked() {
  // 获取文件名
  QString fileName{
      QFileDialog::getOpenFileName(this, "打开源文件", ".", "源文件(*.tny);;文本文件(*.txt, *)")};
  // 构造文件对象
  QFile file{fileName};

  if (fileName.isEmpty())
    return;

  // 读取全部内容
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    ui->source->setText(file.readAll());
    QMessageBox::information(this, "提示", "读取成功");
    file.close();
  }

  // 文件打开失败
  else
    QMessageBox::information(this, "提示", "读取失败");
}

void Dialog::on_saveFile_clicked() {
  QString tempPath = QDir::homePath();
  QString savePath = QFileDialog::getSaveFileName(this, tr("SaveSourceCode"), tempPath, "TINY(*.tny);;TEXT(*.txt, *)");
  if (savePath.isEmpty())
    return;
  QFile file(savePath);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QMessageBox::information(this, "提示", "文件保存失败");
    return;
  }
  // 写文件
  QString content = ui->source->toPlainText().toUtf8();
  QTextStream out(&file);
  out << content << '\n';
  file.close();
  QMessageBox::information(this, "提示", "文件保存成功");
}

void Dialog::on_analyze_clicked() {
  QString sourcePath = QDir::tempPath() + "/TinySourceCode";
//  QString resPath = QDir::tempPath() + "/TinyResult";
  QString errPath = QDir::tempPath() + "/TinyError";
  QFile source(sourcePath);
  if (!source.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QMessageBox::information(this, "提示", "缺失文件访问权限");
    return;
  }
  qDebug() << "分析源程序：" << ui->source->toPlainText() << '\n' << "临时文件: " << sourcePath << '\n' ;

  QTextStream out(&source);
  out << ui->source->toPlainText().toUtf8();
  source.close();

  TreeNode* node = analyzeCode(sourcePath.toStdString().c_str(), errPath.toStdString().c_str());
  QFile error(errPath);
  if (!error.open(QIODevice::ReadWrite)) {
    QMessageBox::information(this, "提示", "结果解析失败");
    return;
  }
  QString parseErr = error.readAll().trimmed();
  ui->error->setText(parseErr.size() == 0 ? "未发现错误" : parseErr);
  updateErrorMaxHeight();
  error.close();

  ui->result->clear();
  traverseTree(node, 0);
  // 图形化展示
  if (ui->graphResult->scene()) {
    auto old = ui->graphResult->scene();
    ui->graphResult->setScene(nullptr);
    delete old;
  }
  QGraphicsScene* scene = buildSyntaxScene(node);
  ui->graphResult->setScene(scene);
  ui->graphResult->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

  // Generate Intermediate Code
  QString codePath = QDir::tempPath() + "/TinyCode.txt";
  codeGen(node, codePath.toLocal8Bit().data());
  QFile codeFile(codePath);
  if (codeFile.open(QIODevice::ReadOnly)) {
      codeView->setText(codeFile.readAll());
      codeFile.close();
  }
  QFile::remove(codePath);

  QMessageBox::information(this, "提示", "解析成功");
  // 删除临时文件
  QFile::remove(sourcePath);
  QFile::remove(errPath);
}

void Dialog::on_zoomIn_clicked() {
  ui->graphResult->scale(1.2, 1.2);
}

void Dialog::on_zoomOut_clicked() {
  ui->graphResult->scale(1.0/1.2, 1.0/1.2);
}

void Dialog::on_resetView_clicked() {
  if (ui->graphResult->scene())
    ui->graphResult->fitInView(ui->graphResult->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Dialog::traverseTree(TreeNode* tree, QTreeWidgetItem* p) {
  if (tree == NULL) return;
  QTreeWidgetItem *item;
  while (tree) {
    if (p == 0)
        item = new QTreeWidgetItem(ui->result);
    else
        item = new QTreeWidgetItem(p);
    item->setText(0, getTreeNodeInfo(tree));
    for (int i = 0; i < MAXCHILDREN; ++i)
        traverseTree(tree->child[i], item);
    tree = tree->sibling;
  }
}

void Dialog::resizeEvent(QResizeEvent *event) {
  QDialog::resizeEvent(event);
  // 背景图随窗口缩放
  if (!bgPix.isNull()) {
    QPalette pal = palette();
    pal.setBrush(QPalette::Window, QBrush(bgPix.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
    setPalette(pal);
  }
  // 图形视图在窗口变化时自适配
  if (ui->graphResult->scene()) {
    ui->graphResult->fitInView(ui->graphResult->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
  }
  // 根据当前字体重新计算错误区最大高度
  updateErrorMaxHeight();
}

void Dialog::updateErrorMaxHeight() {
  const int maxLines = 10;
  QFontMetrics fm(ui->error->font());
  int lineH = fm.lineSpacing();
  int frame = ui->error->frameWidth() * 2;
  int padding = 12; // 近似文本边距与滚动条空间
  int maxH = maxLines * lineH + frame + padding;
  ui->error->setMaximumHeight(maxH);
}
