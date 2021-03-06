#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qimagereader.h>
#include <QtSvg/QSvgGenerator>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    QImage image;
    //image.load("C:/Users/ytsuc/Desktop/Qt/Qt_Learn/Ch3Paint2D/tux.jpg");

    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Image"),
                                                        QDir::currentPath(),
                                                        tr("Image Files (*.png *.tga *.bmp)"));
    bool suc=image.load(fileName);
    suc=false;
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
   paintAll();
}

void MainWindow::paintAll(QSvgGenerator *generator/* = 0*/)
{
    QPainter painter;
    if (generator) painter.begin(generator);
    else painter.begin(this);

    painter.setFont(QFont("Times", 14, QFont::Bold));
    painter.drawText(QPoint(20, 50), "Testing");
    painter.drawLine(QPoint(50, 60), QPoint(100, 100));

    painter.setBrush(Qt::BDiagPattern);
    painter.drawRect(QRect(50, 120, 80, 150));
    QPen ellipsePen;
    ellipsePen.setColor(Qt::red);
    ellipsePen.setStyle(Qt::DashDotLine);
    painter.setPen(ellipsePen);
    painter.drawEllipse(QPoint(80, 200), 50, 20);

    QPainterPath rectPath;
    rectPath.addRect(QRect(150, 40, 100, 60));
    painter.setPen(QPen(Qt::red, 1, Qt::DashDotLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::yellow);
    painter.drawPath(rectPath);
    QPainterPath ellipsePath;
    ellipsePath.addEllipse(QPoint(200, 120), 50, 20);
    painter.setPen(QPen(QColor(79, 106, 25), 5, Qt::SolidLine,
    Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(QColor(122, 163, 39));
    painter.drawPath(ellipsePath);
    QImage image;
    image.load("tux.png");
    painter.drawImage(QPoint(100, 150), image);
    painter.end();
}

void MainWindow::on_actionSave_as_SVG_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save SVG", "", "SVG files (*.svg)");
    if (filePath == "") return;

    //save SVG //Test git
    QSvgGenerator generator;
     generator.setFileName(filePath);
     generator.setSize(QSize(this->width(), this->height()));
     generator.setViewBox(QRect(0, 0, this->width(), this->height()));
     generator.setTitle("SVG Example");
     generator.setDescription("This SVG file is generated by Qt.");
     paintAll(&generator);
}
